#include "EXPORT.h"

EXPORT::EXPORT()
{
}

void EXPORT::ExportToExcel(QString file_name, QSqlTableModel *model, QString table_name)
{
    if(file_name.isEmpty())
    {
        qDebug() << "fileName is empty";
    }
    QString sheet_name = table_name;

    qDebug() << "fileName" << file_name;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "excelexport");
    if(!db.isValid())
    {
        qDebug() << "export2Excel failed: QODBC not supported.";
    }

    QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%1\";DBQ=%2").arg(file_name).arg(file_name);
    db.setDatabaseName(dsn);

    if(!db.open())
    {
        qDebug() << "export2Excel failed: Create Excel file failed by DRIVER={Microsoft Excel Driver (*.xls)}.";
        //QSqlDatabase::removeDatabase("excelexport");
    }

    QSqlQuery query(db);
    QString sql_exec = QString("DROP TABLE %1 ").arg(sheet_name);
    query.exec(sql_exec);

    sql_exec = QString("CREATE TABLE [%1] (").arg(sheet_name);
    int column_num = model->columnCount();

    for(int i = 0; i < column_num; i ++)
    {
        if(i)
            sql_exec += ", ";
        sql_exec += "[";
        sql_exec += model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        sql_exec += "] char(128) ";
    }

    sql_exec += ")";
    qDebug()<<"sql_exec"<<sql_exec;
    query.prepare(sql_exec);

    qDebug() << "debug 1";
    if(!query.exec())
    {
        qDebug() << "export2Excel failed: Create Excel sheet failed.";
        db.close();
        //QSqlDatabase::removeDatabase("excelexport");
    }


    int row_num = model->rowCount();

    for(int i = 0; i < row_num; i ++)
    {
        sql_exec = QString("INSERT INTO [%1] (").arg(sheet_name);
        QVector<QString> variable;
        //for(int i = 0; i < column_name.size(); i ++)
        for(int j = 0; j < column_num; j ++)
        {
            if(j)
                sql_exec += ", ";
            sql_exec += "[";
            sql_exec += model->headerData(j, Qt::Horizontal, Qt::DisplayRole).toString();
            sql_exec += "]";
            QString temp_string = ":variable";
            temp_string += QString::number(j, 10);
            variable.push_back(temp_string);
        }
        sql_exec += ")";
        sql_exec += " VALUES (";
        for(int j = 0; j < column_num; j ++)
        {
            if(j)
                sql_exec += ", ";
            sql_exec += variable[j];
        }
        sql_exec += ")";
        qDebug() << sql_exec;
        query.prepare(sql_exec);

        for(int j = 0; j < column_num; j ++)
        {
            QModelIndex index = model->index(i, j);
            QString val = model->data(index).toString();
            query.bindValue(variable[j], val);
        }

        query.exec();
    }
}

void EXPORT::ExportToPdf(QString file_name, QSqlTableModel *model, QString table_name)
{
    QPrinter printer_text;
    printer_text.setOutputFormat(QPrinter::PdfFormat);
    printer_text.setOutputFileName(file_name);
    QPainter painter_text;
    painter_text.begin(&printer_text);

    QVector<QString> head_data;

    int col_size = model->columnCount();
    int row_size = model->rowCount();

    QString head_message = "";
    for(int i = 0; i < col_size; i ++)
    {
        if(i)
        {
            head_message += ",";
        }
        head_data.push_back(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        QString temp = "";
        QString temp2 = QString::fromUtf8(head_data[i].toUtf8().data());
        temp.sprintf("%s", temp2.toUtf8().data());
        head_message += temp;
    }

    QPoint point(10, 10);
    for(int i = 0; i < row_size; i ++)
    {
        if(i % 50 == 0)
        {
            point.setX(10);
            point.setY(10);
            painter_text.drawText(point, head_message);
        }
        if(i % 50 == 0 && i)
        {
            printer_text.newPage();
        }

        QString message = "";
        for(int j = 0; j < col_size; j ++)
        {
            if(j)
            {
                message += ",";
            }
            QModelIndex index = model->index(i, j);
            QString val = model->data(index).toString();

            QString temp = "";
            QString temp2 = QString::fromUtf8(val.toUtf8().data());
            temp.sprintf("%s", temp2.toUtf8().data());
            message += temp;
        }

        int y = point.y();
        point.setY(y + 20);
        painter_text.drawText(point, message);
    }
    painter_text.end();
}

void EXPORT::ExportToTxt(QString file_name, QSqlTableModel *model, QString table_name)
{
    QFile file(file_name);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);

    QString message = "";

    int col_size = model->columnCount();
    int row_size = model->rowCount();
    QVector<QString> head_data;

    QString head_message = "";
    for(int i = 0; i < col_size; i ++)
    {
        if(i)
        {
            head_message += ",";
        }
        head_data.push_back(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        QString temp = "";
        QString temp2 = QString::fromUtf8(head_data[i].toUtf8().data());
        temp.sprintf("%s", temp2.toUtf8().data());
        head_message += temp;
    }
    message += head_message;
    message += "\n";

    for(int i = 0; i < row_size; i ++)
    {
        for(int j = 0; j < col_size; j ++)
        {
            QModelIndex index = model->index(i, j);
            QString val = model->data(index).toString();

            QString temp = "";
            QString temp2 = QString::fromUtf8(val.toUtf8().data());
            temp.sprintf("%s", temp2.toUtf8().data());
            message += temp;
            if(j < col_size - 1)
            {
                message += ",";
            }
        }
        message += "\n";
    }

    text_stream << message;
    file.close();
}
