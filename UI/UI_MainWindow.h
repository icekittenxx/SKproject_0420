#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDebug>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QColor>
#include <QItemDelegate>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QAxObject>

#include "UI_SELECT_TABLE.h"
#include "UI_EXPORT.h"
#include "UI_IMPORT.h"
#include "../INTERFACE/ItemDelegate.h"

namespace Ui {
class UI_MainWindow;
}

class UI_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UI_MainWindow(QWidget *parent = 0);
    ~UI_MainWindow();

private:
    Ui::UI_MainWindow *ui;

    ItemDelegate *item_delegate;

    QSqlTableModel *model_t;
    QSqlTableModel *model_for_export;
    //QSqlTableModel *model_t_2;

    QString query_value, query_column;
    int current_page, page_size, page_num_size;
    int model_row_count;

    QString latest_item_data;
    int latest_item_row, latest_item_column;

    UI_EXPORT ui_export;
    UI_IMPORT ui_import;
    UI_SELECT_TABLE ui_select_table;

    QVector<QString> select_table;
    int current_select_table;

private slots:
    //void clickeitem(QModelIndex index);

    void init();
    void print(QPrinter* printer);
    QString setFilterString();
    void SET_MODEL();

    void ACTION_SELECT_TABLE();
    void ACTION_EXPORT();
    void ACTION_IMPORT();
    void ACTION_PRINT();
    void ACTION_ADD();
    void ACTION_DELETE();
    void ACTION_SAVE();
    void ACTION_ABORT();
    void ACTION_REGRESH();
    void ACTION_DELETEALL();

    void on_BUTTON_SAVE_clicked();
    void on_BUTTON_ABORT_clicked();
    void on_BUTTON_ADD_clicked();
    void on_BUTTON_REFRESH_clicked();
    void on_BUTTON_DELETE_clicked();
    void on_BUTTON_DELETEALL_clicked();
    void on_BUTTON_QUERY_clicked();
    void on_TABLEVIEW_clicked(const QModelIndex &index);
    //void on_TABLEVIEW_doubleClicked(const QModelIndex &index);
    void on_COMBOBOX_PAGE_SIZE_activated(const QString &arg1);
    void on_BUTTON_FIRST_PAGE_clicked();
    void on_BUTTON_LAST_PAGE_clicked();
    void on_BUTTON_TURN_PAGE_clicked();
    void on_BUTTON_PREVIOUS_PAGE_clicked();
    void on_BUTTON_NEXT_PAGE_clicked();
    void on_BUTTON_EXEC_SQL_clicked();
    void on_BUTTON_TURN_TO_LEFT_TABLE_clicked();
    void on_BUTTON_TURN_TO_RIGHT_TABLE_clicked();
};

#endif // UI_MAINWINDOW_H
