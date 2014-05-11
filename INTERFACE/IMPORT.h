#ifndef IMPORT_H
#define IMPORT_H

#include <QtSql/QSqlTableModel>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QtSql>

class IMPORT
{
public:
    IMPORT();

    void InsertToTable(QVector<QString> ins_column, QVector<QString> ins_value, QString table_name);
    void ImportFromExcel(QVector<QVector<QString>> data, QSqlTableModel *model);
};

#endif // IMPORT_H
