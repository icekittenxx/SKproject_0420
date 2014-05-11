#include "IMPORT.h"

IMPORT::IMPORT()
{
}

void IMPORT::InsertToTable(QVector<QString> ins_column, QVector<QString> ins_value, QString table_name)
{
    QString select_sql = "";
    select_sql += "insert into ";
    select_sql += table_name;
    select_sql += " ( ";
    int ins_size = ins_column.size();
    for(int i = 0; i < ins_size; i ++)
    {
        if(i > 0)
        {
            select_sql += ", ";
        }
        select_sql += ins_column[i];
    }
    select_sql += " ) values ( ";
    for(int i = 0; i < ins_size; i ++)
    {
        if(i > 0)
        {
            select_sql += ", ";
        }
        select_sql += "?";
    }
    select_sql += ")";
    qDebug() << select_sql;

    QSqlQuery query;
    query.prepare(select_sql);

    for(int i = 0; i < ins_size; i ++)
    {
        query.addBindValue(ins_value[i]);
        qDebug() << ins_value[i];
    }
    query.exec();
}

void IMPORT::ImportFromExcel(QVector<QVector<QString> > data, QSqlTableModel *model)
{
    /*
    for(int i = 0; i < data.size(); i ++)
    {
        for(int j = 0; j < data[i].size(); j ++)
        {
            qDebug() << data[i][j];
        }
        qDebug() << "-----";
    }
    qDebug() << model->tableName();
    */

    int col_num = model->columnCount();
    QVector<QString> column;

    for(int i = 0; i < col_num; i ++)
    {
        column.push_back(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
    }

    for(int i = 1; i < data.size(); i ++)
    {
        InsertToTable(column, data[i], model->tableName());
    }
}
