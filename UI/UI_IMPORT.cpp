#include "UI_IMPORT.h"
#include "ui_UI_IMPORT.h"

UI_IMPORT::UI_IMPORT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_IMPORT)
{
    ui->setupUi(this);

    setWindowTitle("导入");

    //ui->LINEEDIT_FILEPATH->setText("d:\\test.xls");
    ui->LINEEDIT_FILEPATH->setText("d:/test.xls");
    ui->COMBOBOX_SPLITE->setEnabled(false);

    size = ".xls";
    splite = ",";
    make_preview_flag = false;
}

UI_IMPORT::~UI_IMPORT()
{
    delete ui;
}

void UI_IMPORT::on_BUTTON_IMPORT_clicked()
{
    if(make_preview_flag == false)
    {
        QMessageBox::warning(this, tr("DataBase"), tr("plese preview first"));
        return;
    }
    if(size == ".xls")
    {
        qDebug() << "xls";
        IMPORT_FROM_EXCEL();
    }
    else
    {
        qDebug() << "txt";
        IMPORT_FROM_TXT();
    }
    return;
}

void UI_IMPORT::IMPORT_FROM_EXCEL()
{
    /*
    QString file_path = ui->LINEEDIT_FILEPATH->text();
    char *ch;
    QByteArray ba = file_path.toLatin1();
    ch = ba.data();

    //QVector<QVector<QString>> data;

    QAxObject *excel = NULL;
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;
    excel = new QAxObject("Excel.Application");
    if(!excel)
    {
        QMessageBox::critical(this, "ERROR MESSAGE", "EXCEL OBJECT LOST");
        return;
    }
    excel->dynamicCall("SetVisible(bool)", false);
    workbooks = excel->querySubObject("WorkBooks");
    workbook = workbooks->querySubObject("Open(QString, QVariant)", QString(tr(ch)));
    QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);

    QAxObject * usedrange = worksheet->querySubObject("UsedRange");
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    for(int i = intRowStart; i < intRowStart + intRows; i ++)
    {
        QVector<QString> temp_data;
        for (int j = intColStart; j < intColStart + intCols; j ++)
        {
            QAxObject * cell = worksheet->querySubObject("Cells(int,int)", i, j );
            temp_data.push_back(cell->dynamicCall("Value2()").toString());
        }
        data_for_import.push_back(temp_data);
    }
    workbook->dynamicCall("Close (Boolean)", false);
    delete excel;//don't forget, else excel.exe will always exist
    */
    import_object.ImportFromExcel(column_for_import, data_for_import, model);
}

void UI_IMPORT::IMPORT_FROM_TXT()
{
    /*
    //ui->LINEEDIT_FILEPATH->setText("d:/test.txt");
    QString file_path = ui->LINEEDIT_FILEPATH->text();

    QFile file(file_path);
    file.open(QIODevice::ReadOnly);

    QTextStream fi(&file);

    QString line = fi.readLine();
    QStringList temp = line.split(splite);
    QVector<QString> temp_data_1;
    for(int i = 0; i < temp.size(); i ++)
    {
        temp_data_1.push_back(temp[i]);
    }
    data_for_import.push_back(temp_data_1);

    while(!fi.atEnd()){
        QString line = fi.readLine();
        QStringList temp_2 = line.split(splite);
        QVector<QString> temp_data_2;
        for(int i = 0; i < temp_2.size(); i ++)
        {
            temp_data_2.push_back(temp_2[i]);
        }
        data_for_import.push_back(temp_data_2);
    }
    */

    import_object.ImportFromTxt(column_for_import, data_for_import, model);
}

void UI_IMPORT::on_BUTTON_PREVIEW_clicked()
{
    //qDebug() << ui->TABLEWIDGET_IMPORT->item(1,1)->text();
    while(!change_column.empty())
    {
        change_column.pop_back();
    }
    while(!column_for_import.empty())
    {
        column_for_import.pop_back();
    }
    while(!data_for_import.empty())
    {
        data_for_import.pop_back();
    }

    for(int i = 0; i < column_count; i ++)
    {
        bool *ok = 0;
        QString flag = ui->TABLEWIDGET_IMPORT->item(1, i)->text();
        int temp = ui->TABLEWIDGET_IMPORT->item(1, i)->text().toInt(ok, 10);
        if(temp == 0 && flag == NULL)
        {
            //qDebug() << -1;
            change_column.push_back(-1);
        }
        else
        {
            //qDebug() << temp;
            change_column.push_back(temp);
        }
    }

    for(int i = 0; i < change_column.size(); i ++)
    {
        if(change_column[i] != -1)
        {
            column_for_import.push_back(model->headerData(change_column[i], Qt::Horizontal, Qt::DisplayRole).toString());
            //qDebug() << column_for_import[i];
        }
    }

    if(size == ".xls")
    {
        MAKE_PREVIEW_EXCEL();
    }
    else
    {
        MAKE_PREVIEW_TXT();
    }

    ui_import_preview.column_for_import = column_for_import;
    ui_import_preview.data_for_import = data_for_import;
    ui_import_preview.make_widget();
    ui_import_preview.exec();
    make_preview_flag = true;
}

void UI_IMPORT::on_COMBOBOX_SIZE_activated(const QString &arg1)
{
    qDebug() << arg1;
    size = arg1;

    if(size == ".xls")
    {
        ui->COMBOBOX_SPLITE->setEnabled(false);
    }
    else
    {
        ui->COMBOBOX_SPLITE->setEnabled(true);
    }
}

void UI_IMPORT::MAKE_TABLEWIDGET()
{
    //QStringList header;
    //header.append("database");
    //header.append("file");
    //ui->TABLEWIDGET_IMPORT->setVerticalHeaderLabels(QStringList() << tr("标题1") << tr("标题2"));// setHorizontalHeaderLabels(header);

    column_count = model->columnCount();
    ui->TABLEWIDGET_IMPORT->setRowCount(2);
    ui->TABLEWIDGET_IMPORT->setColumnCount(column_count);

    for(int i = 0; i < column_count; i ++)
    {
        QString temp = model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
        ui->TABLEWIDGET_IMPORT->setItem(0, i, new QTableWidgetItem(temp));
    }


    for(int i = 0; i < column_count; i ++)
    {
        QString temp = QString::number(i, 10);
        ui->TABLEWIDGET_IMPORT->setItem(1, i, new QTableWidgetItem(temp));
    }

    while(!column_for_import.empty())
    {
        column_for_import.pop_back();
    }
    while(!data_for_import.empty())
    {
        data_for_import.pop_back();
    }
    size = ".xls";
    splite = ",";
    make_preview_flag = false;
}


void UI_IMPORT::on_COMBOBOX_SPLITE_activated(const QString &arg1)
{
    splite = arg1;
}

void UI_IMPORT::MAKE_PREVIEW_EXCEL()
{
    QString file_path = ui->LINEEDIT_FILEPATH->text();
    char *ch;
    QByteArray ba = file_path.toLatin1();
    ch = ba.data();

    QAxObject *excel = NULL;
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;
    excel = new QAxObject("Excel.Application");
    if(!excel)
    {
        QMessageBox::critical(this, "ERROR MESSAGE", "EXCEL OBJECT LOST");
        return;
    }
    excel->dynamicCall("SetVisible(bool)", false);
    workbooks = excel->querySubObject("WorkBooks");
    workbook = workbooks->querySubObject("Open(QString, QVariant)", QString(tr(ch)));
    QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);

    QAxObject * usedrange = worksheet->querySubObject("UsedRange");
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    //qDebug() << "lalala" << intRowStart;
    for(int i = intRowStart + 1; i < intRowStart + intRows; i ++)
    {
        QVector<QString> temp_data;
        for (int j = intColStart; j < intColStart + intCols; j ++)
        {
            QAxObject * cell = worksheet->querySubObject("Cells(int,int)", i, j );
            temp_data.push_back(cell->dynamicCall("Value2()").toString());
        }
        data_for_import.push_back(temp_data);
    }
    workbook->dynamicCall("Close (Boolean)", false);
    delete excel;
}

void UI_IMPORT::MAKE_PREVIEW_TXT()
{
    //ui->LINEEDIT_FILEPATH->setText("d:/test.txt");
    QString file_path = ui->LINEEDIT_FILEPATH->text();
    qDebug() << ui->LINEEDIT_FILEPATH->text();

    QFile file(file_path);
    file.open(QIODevice::ReadOnly);

    QTextStream fi(&file);

    QString line = fi.readLine();
    QStringList temp = line.split(splite);
    QVector<QString> temp_data_1;
    for(int i = 0; i < temp.size(); i ++)
    {
        temp_data_1.push_back(temp[i]);
    }
    data_for_import.push_back(temp_data_1);

    while(!fi.atEnd()){
        QString line = fi.readLine();
        QStringList temp_2 = line.split(splite);
        QVector<QString> temp_data_2;
        for(int i = 0; i < temp_2.size(); i ++)
        {
            temp_data_2.push_back(temp_2[i]);
        }
        data_for_import.push_back(temp_data_2);
    }
}
