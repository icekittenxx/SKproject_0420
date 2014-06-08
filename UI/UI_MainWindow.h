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
#include <QLabel>
#include <QTableView>
#include <QListWidgetItem>
#include <QPushButton>
#include <QLineEdit>

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

    UI_EXPORT ui_export;
    UI_IMPORT ui_import;
    UI_SELECT_TABLE ui_select_table;

    QSqlTableModel *model_for_export;

    //------------------------------------------------------------------------------------------------
    int tabwidget_size, tabwidget_current_page;
    QVector<int> tabwidget_sqltable_list;
    QVector<QString> sqltable_name;

    QVector<QWidget *> tabwidget;
    QVector<QTableView *> tab_tableview;
    QVector<QLabel *> tab_label_1, tab_label_2, tab_label_3;
    QVector<QLabel *> tab_label_query_column, tab_label_query_value;
    QVector<QComboBox *> tab_combobox;
    QVector<QPushButton *> tab_button_first_page, tab_button_last_page;
    QVector<QPushButton *> tab_button_previous_page, tab_button_next_page;
    QVector<QPushButton *> tab_button_turn_page;
    QVector<QPushButton *> tab_button_close;
    QVector<QPushButton *> tab_button_query;
    QVector<QLineEdit *> tab_lineedit;
    QVector<QLineEdit *> tab_lineedit_query_column, tab_lineedit_query_value;

    QVector<QSqlTableModel *> tab_model;
    QVector<int> tab_model_current_page, tab_model_page_size, tab_model_page_num_size;
    QVector<int> tab_model_row_count;
    QVector<QString> tab_model_query_value, tab_model_query_column;

    QVector<ItemDelegate *> tab_item_delegate;
    QVector<QString> tab_latest_item_data;
    QVector<int> tab_latest_item_row, tab_latest_item_column;

private slots:

    void print(QPrinter* printer);

    void ACTION_EXPORT();
    void ACTION_IMPORT();
    void ACTION_PRINT();
    void ACTION_ADD();
    void ACTION_DELETE();
    void ACTION_SAVE();
    void ACTION_ABORT();
    void ACTION_REGRESH();
    void ACTION_DELETEALL();

    //---------------------------------------------------------------------------
    void on_LISTWIDGET_ONE_itemClicked(QListWidgetItem *item);
    void init_widget();
    void init_model(int index);
    void init_set_model(int index);
    QString set_filter_string(int index);

    void on_TABWIDGET_currentChanged(int index);
    void on_BUTTON_TAB_CLOSE_clicked();

    void on_BUTTON_TAB_QUERY_clicked();
    void on_TABLEVIEW_TAB_clicked(const QModelIndex &index);
    void on_COMBOBOX_TAB_PAGE_SIZE_activated(const QString &arg1);
    void on_BUTTON_TAB_FIRST_PAGE_clicked();
    void on_BUTTON_TAB_LAST_PAGE_clicked();
    void on_BUTTON_TAB_TURN_PAGE_clicked();
    void on_BUTTON_TAB_PREVIOUS_PAGE_clicked();
    void on_BUTTON_TAB_NEXT_PAGE_clicked();

};

#endif // UI_MAINWINDOW_H
