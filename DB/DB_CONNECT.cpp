#include "DB_CONNECT.h"

DB_CONNECT::DB_CONNECT()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    qDebug()<<"ODBC driver?"<<db.isValid();

    db.setHostName("127.0.0.1");
    QString dsn = QString::fromLocal8Bit("MS_SQL_FOR_CHANGE");
    db.setDatabaseName(dsn);
    db.setUserName("sa");
    db.setPassword("finegold");
    if(!db.open()){
        qDebug()<<db.lastError().text();
        QMessageBox::critical(0,QObject::tr("Database Error"),db.lastError().text());
    }
}

void DB_CONNECT::DB_TEST()
{
    /*
    QSqlQuery query;
    query.exec("select * from [Well]");
    while(query.next()){
        qDebug() << query.value(1).toString() << query.value(7).toString() << query.value(8).toString();
    }
    */
}
