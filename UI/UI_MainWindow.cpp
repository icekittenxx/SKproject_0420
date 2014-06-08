#include "UI_MainWindow.h"
#include "ui_UI_MainWindow.h"

/*
UI_MainWindow::UI_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UI_MainWindow)
{
    ui->setupUi(this);
}

UI_MainWindow::~UI_MainWindow()
{
    delete ui;
}
*/

UI_MainWindow::UI_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UI_MainWindow)
{
    ui->setupUi(this);

    connect(ui->ACTION_EXPORT, SIGNAL(triggered()), this, SLOT(ACTION_EXPORT()));
    connect(ui->ACTION_IMPORT, SIGNAL(triggered()), this, SLOT(ACTION_IMPORT()));
    connect(ui->ACTION_PRINT, SIGNAL(triggered()), this, SLOT(ACTION_PRINT()));

    connect(ui->ACTION_ADD, SIGNAL(triggered()), this, SLOT(ACTION_ADD()));
    connect(ui->ACTION_DELETE, SIGNAL(triggered()), this, SLOT(ACTION_DELETE()));
    connect(ui->ACTION_SAVE, SIGNAL(triggered()), this, SLOT(ACTION_SAVE()));
    connect(ui->ACTION_ABORT, SIGNAL(triggered()), this, SLOT(ACTION_ABORT()));
    connect(ui->ACTION_REFRESH, SIGNAL(triggered()), this, SLOT(ACTION_REGRESH()));
    connect(ui->ACTION_DELETEALL, SIGNAL(triggered()), this, SLOT(ACTION_DELETEALL()));

    connect(ui->ACTION_SAVE_2, SIGNAL(triggered()), this, SLOT(ACTION_SAVE()));
    connect(ui->ACTION_PRINT_2, SIGNAL(triggered()), this, SLOT(ACTION_PRINT()));

    //-----------------------------------------------------------------------------------------------
    tabwidget_size = 0;
    sqltable_name.push_back("gaslog");
    sqltable_name.push_back("well");
    sqltable_name.push_back("well_basic");

    tabwidget_sqltable_list.push_back(-1);//need to be delete;

    init_widget();
}

UI_MainWindow::~UI_MainWindow()
{
    delete ui;
}


//---------------------------------------------------------------------------------------------------

void UI_MainWindow::init_widget()
{
    //number 5 need to be modify
    int num = 5;

    tabwidget_current_page = 0;

    for(int i = 0; i < num; i ++)
    {
        QTableView *temp = new QTableView;
        tab_tableview.push_back(temp);

        connect(tab_tableview[i], SIGNAL(clicked(const QModelIndex)), this, SLOT(on_TABLEVIEW_TAB_clicked(const QModelIndex)));
    }

    for(int i = 0; i < num; i ++)
    {
        QLabel *temp_label_1 = new QLabel("每页");
        temp_label_1->setFixedWidth(25);
        tab_label_1.push_back(temp_label_1);

        QComboBox *temp_combobox = new QComboBox;
        temp_combobox->setFixedWidth(50);
        temp_combobox->addItem("5");
        temp_combobox->addItem("10");
        temp_combobox->addItem("20");
        temp_combobox->addItem("50");
        tab_combobox.push_back(temp_combobox);

        connect(tab_combobox[i], SIGNAL(activated(const QString)), this, SLOT(on_COMBOBOX_TAB_PAGE_SIZE_activated(const QString)));

        QLabel *temp_label_2 = new QLabel("记录");
        temp_label_2->setFixedWidth(50);
        tab_label_2.push_back(temp_label_2);

        QPushButton *temp_button1 = new QPushButton(tr("首页"));
        temp_button1->setFixedWidth(50);
        tab_button_first_page.push_back(temp_button1);

        connect(tab_button_first_page[i], SIGNAL(clicked()), this, SLOT(on_BUTTON_TAB_FIRST_PAGE_clicked()));

        QPushButton *temp_button2 = new QPushButton(tr("上页"));
        temp_button2->setFixedWidth(50);
        tab_button_previous_page.push_back(temp_button2);

        connect(tab_button_previous_page[i], SIGNAL(clicked()), this, SLOT(on_BUTTON_TAB_PREVIOUS_PAGE_clicked()));

        QPushButton *temp_button3 = new QPushButton(tr("下页"));
        temp_button3->setFixedWidth(50);
        tab_button_next_page.push_back(temp_button3);

        connect(tab_button_next_page[i], SIGNAL(clicked()), this, SLOT(on_BUTTON_TAB_NEXT_PAGE_clicked()));

        QPushButton *temp_button4 = new QPushButton(tr("尾页"));
        temp_button4->setFixedWidth(50);
        tab_button_last_page.push_back(temp_button4);

        connect(tab_button_last_page[i], SIGNAL(clicked()), this, SLOT(on_BUTTON_TAB_LAST_PAGE_clicked()));

        QLineEdit *temp_lineedit = new QLineEdit;
        temp_lineedit->setFixedWidth(50);
        tab_lineedit.push_back(temp_lineedit);

        QLabel *temp_label_3 = new QLabel(tr("/"));
        temp_label_3->setFixedWidth(50);
        tab_label_3.push_back(temp_label_3);

        QPushButton *temp_button5 = new QPushButton(tr("跳转"));
        temp_button5->setFixedWidth(50);
        tab_button_turn_page.push_back(temp_button5);

        connect(tab_button_turn_page[i], SIGNAL(clicked()), this, SLOT(on_BUTTON_TAB_TURN_PAGE_clicked()));
    }

    for(int i = 0; i < num; i ++)
    {
        QPushButton *temp_button = new QPushButton(tr("关闭"));
        temp_button->setFixedWidth(50);
        tab_button_close.push_back(temp_button);

        connect(tab_button_close[i], SIGNAL(clicked()), this, SLOT(on_BUTTON_TAB_CLOSE_clicked()));
    }

    for(int i = 0; i < num; i ++)
    {
        QLabel *temp_label_1 = new QLabel(tr("查询"));
        temp_label_1->setFixedWidth(25);
        tab_label_query_column.push_back(temp_label_1);

        QLineEdit *temp_lineedit_1 = new QLineEdit;
        temp_lineedit_1->setFixedWidth(100);
        temp_lineedit_1->setEnabled(false);
        tab_lineedit_query_column.push_back(temp_lineedit_1);

        QLabel *temp_label_2 = new QLabel(tr("内容"));
        temp_label_2->setFixedWidth(25);
        tab_label_query_value.push_back(temp_label_2);

        QLineEdit *temp_lineedit_2 = new QLineEdit;
        temp_lineedit_2->setFixedWidth(100);
        tab_lineedit_query_value.push_back(temp_lineedit_2);

        QPushButton *temp_button = new QPushButton(tr("搜索"));
        temp_button->setFixedWidth(50);
        tab_button_query.push_back(temp_button);

        connect(tab_button_query[i], SIGNAL(clicked()), this, SLOT(on_BUTTON_TAB_QUERY_clicked()));
    }

    for(int i = 0; i < num; i ++)
    {
        QWidget *temp = new QWidget;

        QVBoxLayout *top_layout = new QVBoxLayout;
        top_layout->addWidget(tab_tableview[i]);

        QHBoxLayout *bottom_layout = new QHBoxLayout;
        bottom_layout->setAlignment(Qt::AlignLeft);
        bottom_layout->addWidget(tab_label_1[i]);
        bottom_layout->addWidget(tab_combobox[i]);
        bottom_layout->addWidget(tab_label_2[i]);
        bottom_layout->addWidget(tab_button_first_page[i]);
        bottom_layout->addWidget(tab_button_previous_page[i]);
        bottom_layout->addWidget(tab_button_next_page[i]);
        bottom_layout->addWidget(tab_button_last_page[i]);
        bottom_layout->addWidget(tab_lineedit[i]);
        bottom_layout->addWidget(tab_label_3[i]);
        bottom_layout->addWidget(tab_button_turn_page[i]);

        QHBoxLayout *close_layout = new QHBoxLayout;
        close_layout->setAlignment(Qt::AlignRight);
        close_layout->addWidget(tab_button_close[i]);

        QHBoxLayout *query_layout = new QHBoxLayout;
        query_layout->setAlignment(Qt::AlignLeft);
        query_layout->addWidget(tab_label_query_column[i]);
        query_layout->addWidget(tab_lineedit_query_column[i]);
        query_layout->addWidget(tab_label_query_value[i]);
        query_layout->addWidget(tab_lineedit_query_value[i]);
        query_layout->addWidget(tab_button_query[i]);

        QVBoxLayout *main_layout = new QVBoxLayout;
        main_layout->addLayout(close_layout);
        main_layout->addLayout(top_layout);
        main_layout->addLayout(bottom_layout);
        main_layout->addLayout(query_layout);

        temp->setLayout(main_layout);

        tabwidget.push_back(temp);
    }

    for(int i = 0; i < num; i ++)
    {
        QSqlTableModel *temp;
        tab_model.push_back(temp);
        tab_model_current_page.push_back(0);
        tab_model_page_size.push_back(5);
        tab_model_page_num_size.push_back(1);
        tab_model_row_count.push_back(0);
    }

    for(int i = 0; i < num; i ++)
    {
        tab_model_query_column.push_back("");
        tab_model_query_value.push_back("");
    }

    for(int i = 0; i < num; i ++)
    {
        ItemDelegate *temp = new ItemDelegate(this);
        tab_item_delegate.push_back(temp);

        tab_latest_item_data.push_back("");
        tab_latest_item_row.push_back(0);
        tab_latest_item_column.push_back(0);
    }
}

void UI_MainWindow::init_model(int index)
{
    tab_model[index] = new QSqlTableModel(this);

    tab_model_query_value[index] = "";
    tab_lineedit_query_value[index]->setText("");

    init_set_model(index);
    tab_tableview[index]->setModel(tab_model[index]);
    tab_tableview[index]->setItemDelegate(tab_item_delegate[index]);
    tab_item_delegate[index]->row.clear();
    tab_item_delegate[index]->column.clear();

    tab_model_query_column[index] = tab_model[index]->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
    tab_lineedit_query_column[index]->setText(tab_model_query_column[index]);

    tab_label_3[index]->setText("/" + QString::number(tab_model_page_num_size[index], 10));
    tab_lineedit[index]->setText(QString::number(tab_model_current_page[index] + 1, 10));

    QModelIndex latest_item = tab_model[index]->index(0, 0);
    tab_latest_item_row[index] = 0;
    tab_latest_item_column[index] = 0;
    tab_latest_item_data[index] = tab_model[index]->data(latest_item).toString();
}

void UI_MainWindow::init_set_model(int index)
{
    tab_model[index]->setTable(sqltable_name[index]);
    tab_model[index]->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tab_model[index]->select();
    tab_model[index]->setSort(0, Qt::AscendingOrder);

    tab_model_row_count[index] = tab_model[index]->rowCount();

    tab_model_page_num_size[index] = tab_model_row_count[index] / tab_model_page_size[index];
    if(tab_model_page_size[index] * tab_model_page_num_size[index] != tab_model_row_count[index])
    {
        tab_model_page_num_size[index] += 1;
    }

    tab_model_current_page[index] = 0;

    QString query_sql = set_filter_string(index);
    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    tab_model[index]->setFilter(QObject::tr(ch));
}

QString UI_MainWindow::set_filter_string(int index)
{
    QString filter_string = "";
    QString primary_key_column = tab_model[index]->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
    QString table_name = sqltable_name[index];
    QString number_to_string;
    int num;

    if(tab_model_query_value[index] != "")
    {
        QString query_sql = tab_model_query_column[index] + " = '%1'";
        char *ch;
        QByteArray ba = query_sql.toLatin1();
        ch = ba.data();
        tab_model[index]->setFilter(QObject::tr(ch).arg(tab_model_query_value[index]));
        tab_model_row_count[index] = tab_model[index]->rowCount();

        tab_model_page_num_size[index] = tab_model_row_count[index] / tab_model_page_size[index];
        if(tab_model_page_size[index] * tab_model_page_num_size[index] != tab_model_row_count[index])
        {
            tab_model_page_num_size[index] += 1;
        }
    }
    else
    {
        tab_model[index]->setFilter(QObject::tr(""));
        tab_model_row_count[index] = tab_model[index]->rowCount();
        tab_model_page_num_size[index] = tab_model_row_count[index] / tab_model_page_size[index];
        if(tab_model_page_size[index] * tab_model_page_num_size[index] != tab_model_row_count[index])
        {
            tab_model_page_num_size[index] += 1;
        }
    }

    if(tab_model_query_value[index] != "")
    {
        filter_string += tab_model_query_column[index];
        filter_string += " = '%1' and ";
    }

    filter_string += primary_key_column;
    filter_string += " not in (select top ";
    num = tab_model_current_page[index] * tab_model_page_size[index];
    number_to_string = QString::number(num, 10);
    filter_string += number_to_string;
    filter_string += " ";
    filter_string += primary_key_column;
    filter_string += " from ";
    filter_string += table_name;

    if(tab_model_query_value[index] != "")
    {
        filter_string += " where ";
        filter_string += tab_model_query_column[index];
        filter_string += " = '%2'";
    }

    filter_string += " Order by ";
    filter_string += primary_key_column;
    filter_string += ") and ";
    filter_string += primary_key_column;
    filter_string += " not in (select top ";
    num = tab_model_row_count[index] - (tab_model_current_page[index] + 1) * tab_model_page_size[index];
    if(num < 0)
        num = 0;
    number_to_string = QString::number(num, 10);
    filter_string += number_to_string;
    filter_string += " ";
    filter_string += primary_key_column;
    filter_string += " from ";
    filter_string += table_name;

    if(tab_model_query_value[index] != "")
    {
        filter_string += " where ";
        filter_string += tab_model_query_column[index];
        filter_string += " = '%3'";
    }

    filter_string += " Order by ";
    filter_string += primary_key_column;
    filter_string += " desc)";

    return filter_string;
}

void UI_MainWindow::on_LISTWIDGET_ONE_itemClicked(QListWidgetItem *item)
{
    QString current_sqltable_name = item->text();
    int current_sqltable_index = sqltable_name.indexOf(current_sqltable_name);

    for(int i = 0; i < tabwidget_sqltable_list.size(); i ++)
    {
        if(tabwidget_sqltable_list[i] == current_sqltable_index)
        {
            return;
        }
    }

    tabwidget_sqltable_list.push_back(current_sqltable_index);
    ui->TABWIDGET->addTab(tabwidget[current_sqltable_index], current_sqltable_name);
    init_model(current_sqltable_index);
}

void UI_MainWindow::on_TABWIDGET_currentChanged(int index)
{
    tabwidget_current_page = index;
    qDebug() << tabwidget_current_page;
}

void UI_MainWindow::on_BUTTON_TAB_CLOSE_clicked()
{
    tabwidget_sqltable_list.removeAt(tabwidget_current_page);
    ui->TABWIDGET->removeTab(tabwidget_current_page);
}

void UI_MainWindow::on_BUTTON_TAB_QUERY_clicked()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];
    tab_model_query_value[current_sqltable] = tab_lineedit_query_value[current_sqltable]->text();

    tab_model_current_page[current_sqltable] = 0;

    QString query_sql = set_filter_string(current_sqltable);
    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    tab_model[current_sqltable]->setFilter(QObject::tr(ch).arg(tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable]));

    tab_label_3[current_sqltable]->setText("/" + QString::number(tab_model_page_num_size[current_sqltable], 10));

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();
}

void UI_MainWindow::on_TABLEVIEW_TAB_clicked(const QModelIndex &index)
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    int column = index.column();
    tab_model_query_column[current_sqltable] = tab_model[current_sqltable]->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
    tab_lineedit_query_column[current_sqltable]->setText(tab_model_query_column[current_sqltable]);

    QModelIndex latest_item = tab_model[current_sqltable]->index(tab_latest_item_row[current_sqltable], tab_latest_item_column[current_sqltable]);
    QString compare_string = tab_model[current_sqltable]->data(latest_item).toString();
    if(compare_string != tab_latest_item_data[current_sqltable])
    {
        tab_item_delegate[current_sqltable]->row.push_back(tab_latest_item_row[current_sqltable]);
        tab_item_delegate[current_sqltable]->column.push_back(tab_latest_item_column[current_sqltable]);
    }

    tab_latest_item_row[current_sqltable] = index.row();
    tab_latest_item_column[current_sqltable] = index.column();
    latest_item = tab_model[current_sqltable]->index(tab_latest_item_row[current_sqltable], tab_latest_item_column[current_sqltable]);
    tab_latest_item_data[current_sqltable] = tab_model[current_sqltable]->data(latest_item).toString();
}

void UI_MainWindow::on_COMBOBOX_TAB_PAGE_SIZE_activated(const QString &arg1)
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    bool change_flag;
    tab_model_page_size[current_sqltable] = arg1.toInt(&change_flag, 10);

    QString query_sql = set_filter_string(current_sqltable);
    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(tab_model_query_value[current_sqltable] != "")
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch).arg(tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable]));
    }
    else
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch));
    }

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();

    tab_label_3[current_sqltable]->setText("/" + QString::number(tab_model_page_num_size[current_sqltable], 10));
    tab_lineedit[current_sqltable]->setText(QString::number(tab_model_current_page[current_sqltable] + 1, 10));
}

void UI_MainWindow::on_BUTTON_TAB_FIRST_PAGE_clicked()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    tab_model_current_page[current_sqltable] = 0;
    tab_lineedit[current_sqltable]->setText(QString::number(tab_model_current_page[current_sqltable] + 1, 10));

    QString query_sql = set_filter_string(current_sqltable);

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(tab_model_query_value[current_sqltable] != "")
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch).arg(tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable]));
    }
    else
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch));
    }

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();

    QModelIndex latest_item = tab_model[current_sqltable]->index(0, 0);
    tab_latest_item_row[current_sqltable] = 0;
    tab_latest_item_column[current_sqltable] = 0;
    tab_latest_item_data[current_sqltable] = tab_model[current_sqltable]->data(latest_item).toString();
}

void UI_MainWindow::on_BUTTON_TAB_PREVIOUS_PAGE_clicked()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    int temp_page = tab_model_current_page[current_sqltable] - 1;
    if(temp_page >= 0)
    {
        tab_model_current_page[current_sqltable] -= 1;
        tab_lineedit[current_sqltable]->setText(QString::number(tab_model_current_page[current_sqltable] + 1, 10));
    }
    else
    {
        return;
    }

    QString query_sql = set_filter_string(current_sqltable);

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(tab_model_query_value[current_sqltable] != "")
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch).arg(tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable]));
    }
    else
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch));
    }

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();

    QModelIndex latest_item = tab_model[current_sqltable]->index(0, 0);
    tab_latest_item_row[current_sqltable] = 0;
    tab_latest_item_column[current_sqltable] = 0;
    tab_latest_item_data[current_sqltable] = tab_model[current_sqltable]->data(latest_item).toString();
}

void UI_MainWindow::on_BUTTON_TAB_NEXT_PAGE_clicked()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    int temp_page = tab_model_current_page[current_sqltable] + 1;
    if(temp_page < tab_model_page_num_size[current_sqltable])
    {
        tab_model_current_page[current_sqltable] += 1;
        tab_lineedit[current_sqltable]->setText(QString::number(tab_model_current_page[current_sqltable] + 1, 10));
    }
    else
    {
        return;
    }

    QString query_sql = set_filter_string(current_sqltable);

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(tab_model_query_value[current_sqltable] != "")
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch).arg(tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable]));
    }
    else
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch));
    }

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();

    QModelIndex latest_item = tab_model[current_sqltable]->index(0, 0);
    tab_latest_item_row[current_sqltable] = 0;
    tab_latest_item_column[current_sqltable] = 0;
    tab_latest_item_data[current_sqltable] = tab_model[current_sqltable]->data(latest_item).toString();
}

void UI_MainWindow::on_BUTTON_TAB_LAST_PAGE_clicked()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    tab_model_current_page[current_sqltable] = tab_model_page_num_size[current_sqltable] - 1;
    tab_lineedit[current_sqltable]->setText(QString::number(tab_model_current_page[current_sqltable] + 1, 10));

    QString query_sql = set_filter_string(current_sqltable);

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(tab_model_query_value[current_sqltable] != "")
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch).arg(tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable]));
    }
    else
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch));
    }

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();

    QModelIndex latest_item = tab_model[current_sqltable]->index(0, 0);
    tab_latest_item_row[current_sqltable] = 0;
    tab_latest_item_column[current_sqltable] = 0;
    tab_latest_item_data[current_sqltable] = tab_model[current_sqltable]->data(latest_item).toString();
}

void UI_MainWindow::on_BUTTON_TAB_TURN_PAGE_clicked()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    tab_model_current_page[current_sqltable] = tab_lineedit[current_sqltable]->text().toInt() - 1;

    if(tab_model_current_page[current_sqltable] < 0 || tab_model_current_page[current_sqltable] >= tab_model_page_num_size[current_sqltable])
    {
        return;
    }

    tab_lineedit[current_sqltable]->setText(QString::number(tab_model_current_page[current_sqltable] + 1, 10));

    QString query_sql = set_filter_string(current_sqltable);

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(tab_model_query_value[current_sqltable] != "")
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch).arg(tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable], tab_model_query_value[current_sqltable]));
    }
    else
    {
        tab_model[current_sqltable]->setFilter(QObject::tr(ch));
    }

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();

    QModelIndex latest_item = tab_model[current_sqltable]->index(0, 0);
    tab_latest_item_row[current_sqltable] = 0;
    tab_latest_item_column[current_sqltable] = 0;
    tab_latest_item_data[current_sqltable] = tab_model[current_sqltable]->data(latest_item).toString();
}

void UI_MainWindow::ACTION_EXPORT()
{
    int current_sqltable = tabwidget_current_page;
    QString current_table_name = sqltable_name[tabwidget_sqltable_list[current_sqltable]];

    model_for_export = new QSqlTableModel(this);
    model_for_export->setTable(current_table_name);
    model_for_export->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_for_export->select();

    if(tab_model_query_value[current_sqltable] != "")
    {
        QString query_sql = tab_model_query_column[current_sqltable] + " = '%1'";
        char *ch;
        QByteArray ba = query_sql.toLatin1();
        ch = ba.data();
        model_for_export->setFilter(QObject::tr(ch).arg(tab_model_query_column[current_sqltable]));
    }

    ui_export.model = model_for_export;
    ui_export.exec();
}

void UI_MainWindow::ACTION_IMPORT()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    ui_import.model = tab_model[current_sqltable];
    ui_import.MAKE_TABLEWIDGET();
    ui_import.exec();
}

void UI_MainWindow::ACTION_PRINT()
{
    QPrinter printer(QPrinter::ScreenResolution);
    QPrintPreviewDialog dlg(&printer);

    connect(&dlg, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    dlg.exec();
}

void UI_MainWindow::print(QPrinter* printer)
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    QTableView* viewForPrint = new QTableView;
    viewForPrint->setModel(tab_tableview[current_sqltable]->model());
    viewForPrint->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewForPrint->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    viewForPrint->resize(printer->width(), printer->height());
    viewForPrint->render(printer);
}

void UI_MainWindow::ACTION_ADD()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    int row_num = tab_model[current_sqltable]->rowCount();

    tab_model[current_sqltable]->insertRow(row_num);

    for(int i = 0; i < tab_model[current_sqltable]->columnCount(); i ++)
    {
        tab_item_delegate[current_sqltable]->column.push_back(i);
        tab_item_delegate[current_sqltable]->row.push_back(row_num);
    }
}

void UI_MainWindow::ACTION_DELETE()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    int row_num = tab_tableview[current_sqltable]->currentIndex().row();

    tab_model[current_sqltable]->removeRow(row_num);

    for(int i = 0; i < tab_model[current_sqltable]->columnCount(); i ++)
    {
        tab_item_delegate[current_sqltable]->column.push_back(i);
        tab_item_delegate[current_sqltable]->row.push_back(row_num);
    }
}

void UI_MainWindow::ACTION_SAVE()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    tab_model[current_sqltable]->database().transaction();
    if(tab_model[current_sqltable]->submitAll())
    {
        tab_model[current_sqltable]->database().commit();

        tab_model_query_value[current_sqltable] = "";
        tab_lineedit_query_value[current_sqltable]->setText(tab_model_query_value[current_sqltable]);
        init_set_model(current_sqltable);

        tab_label_3[current_sqltable]->setText("/" + QString::number(tab_model_page_num_size[current_sqltable], 10));
        tab_lineedit[current_sqltable]->setText(QString::number(tab_model_current_page[current_sqltable] + 1, 10));
    }
    else
    {
        tab_model[current_sqltable]->database().rollback();
        QMessageBox::warning(this, tr("DataBase"), tr("DataBase Error: %1").arg(tab_model[current_sqltable]->lastError().text()));
    }

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();
}

void UI_MainWindow::ACTION_ABORT()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    tab_model[current_sqltable]->revertAll();

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();
}

void UI_MainWindow::ACTION_REGRESH()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    tab_model_query_value[current_sqltable] = "";
    tab_lineedit_query_value[current_sqltable]->setText(tab_model_query_value[current_sqltable]);

    init_set_model(current_sqltable);

    tab_label_3[current_sqltable]->setText("/" + QString::number(tab_model_page_num_size[current_sqltable], 10));
    tab_lineedit[current_sqltable]->setText(QString::number(tab_model_current_page[current_sqltable] + 1, 10));

    tab_item_delegate[current_sqltable]->column.clear();
    tab_item_delegate[current_sqltable]->row.clear();
}

void UI_MainWindow::ACTION_DELETEALL()
{
    int current_sqltable = tabwidget_sqltable_list[tabwidget_current_page];

    int row_num = tab_model[current_sqltable]->rowCount();
    int col_num = tab_model[current_sqltable]->columnCount();
    tab_model[current_sqltable]->removeRows(0, row_num);

    for(int i = 0; i < row_num; i ++)
    {
        for(int j = 0; j < col_num; j ++)
        {
            tab_item_delegate[current_sqltable]->column.push_back(i);
            tab_item_delegate[current_sqltable]->row.push_back(j);
        }
    }

    tab_label_3[current_sqltable]->setText("/" + QString::number(tab_model_page_num_size[current_sqltable], 10));
}
