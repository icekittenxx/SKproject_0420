#include <QApplication>

#include "UI/UI_MainWindow.h"

#include "DB/DB_CONNECT.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DB_CONNECT my_db_connect;
    my_db_connect.DB_TEST();

    UI_MainWindow w;
    w.show();
    return a.exec();
}
