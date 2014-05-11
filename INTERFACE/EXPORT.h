#ifndef EXPORT_H
#define EXPORT_H

#include <QString>
#include <QVector>
#include <Qtsql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QDebug>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QDateTime>
#include <QTextCodec>
#include <QFile>

class EXPORT
{
public:
    EXPORT();
    void ExportToExcel(QString file_name, QSqlTableModel *model, QString table_name);
    void ExportToPdf(QString file_name, QSqlTableModel *model, QString table_name);
    void ExportToTxt(QString file_name, QSqlTableModel *model, QString table_name);
};

#endif // EXPORT_H
