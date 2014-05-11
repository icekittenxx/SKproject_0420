#include "UI_MainWindow.h"
#include "ui_UI_MainWindow.h"

UI_MainWindow::UI_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UI_MainWindow)
{
    ui->setupUi(this);

    ui->LINEEDIT_QUERY_COLUMN->setEnabled(false);
    connect(ui->ACTION_SELECT_TABLE, SIGNAL(triggered()), this, SLOT(ACTION_SELECT_TABLE()));
    connect(ui->ACTION_EXPORT, SIGNAL(triggered()), this, SLOT(ACTION_EXPORT()));
    connect(ui->ACTION_IMPORT, SIGNAL(triggered()), this, SLOT(ACTION_IMPORT()));
    connect(ui->ACTION_PRINT, SIGNAL(triggered()), this, SLOT(ACTION_PRINT()));

    //ui->BUTTON_TABLE_1->setVisible(false);

    page_size = 5;
    current_page = 0;

    /*
    model_t = new QSqlTableModel(this);
    SET_MODEL();
    ui->TABLEVIEW->setModel(model_t);
    item_delegate = new ItemDelegate(this);
    ui->TABLEVIEW->setItemDelegate(item_delegate);

    query_column = model_t->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
    query_value = "";
    ui->LINEEDIT_QUERY_COLUMN->setText(query_column);


    ui->LABEL_TURN_PAGE->setText("/" + QString::number(page_num_size, 10));
    ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));

    QModelIndex latest_item = model_t->index(0, 0);
    latest_item_row = 0;
    latest_item_column = 0;
    //qDebug() << model_t->data(latest_item, 0);
    latest_item_data = model_t->data(latest_item).toString();
    */

    /*
    model_t_2 = new QSqlTableModel(this);
    model_t_2->setTable("Well_basic");
    model_t_2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_t_2->select();
    model_t_2->setSort(0, Qt::AscendingOrder);
    ui->tableView->setModel(model_t_2);
    ui->tableView->setItemDelegate(item_delegate);
    */
}

UI_MainWindow::~UI_MainWindow()
{
    delete ui;
}

/*
void UI_MainWindow::clickeitem(QModelIndex index)
{
    qDebug()<<"clicked"<<index;
    QWidget* w=new QWidget();
    QPalette p(Qt::green);

    w->setPalette(p);
    ui->TABLEVIEW->setIndexWidget(index, w);
}
*/

void UI_MainWindow::init()
{
    model_t = new QSqlTableModel(this);
    SET_MODEL();
    ui->TABLEVIEW->setModel(model_t);
    item_delegate = new ItemDelegate(this);
    ui->TABLEVIEW->setItemDelegate(item_delegate);

    query_column = model_t->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
    query_value = "";
    ui->LINEEDIT_QUERY_COLUMN->setText(query_column);

    ui->LABEL_TURN_PAGE->setText("/" + QString::number(page_num_size, 10));
    ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));

    QModelIndex latest_item = model_t->index(0, 0);
    latest_item_row = 0;
    latest_item_column = 0;
    //qDebug() << model_t->data(latest_item, 0);
    latest_item_data = model_t->data(latest_item).toString();
}

void UI_MainWindow::print(QPrinter* printer)
{
    QTableView* viewForPrint = new QTableView;
    viewForPrint->setModel(ui->TABLEVIEW->model()); //.tableView->model());
    viewForPrint->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewForPrint->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    viewForPrint->resize(printer->width(), printer->height());
    viewForPrint->render(printer);
}

QString UI_MainWindow::setFilterString()
{
    QString filter_string = "";
    QString primary_key_column = model_t->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
    //QString table_name = "Well";
    QString table_name = select_table[current_select_table];
    QString number_to_string;
    int num;

    if(query_value != "")
    {
        QString query_sql = query_column + " = '%1'";
        char *ch;
        QByteArray ba = query_sql.toLatin1();
        ch = ba.data();
        model_t->setFilter(QObject::tr(ch).arg(query_value));
        model_row_count = model_t->rowCount();
        //qDebug() << model_row_count;

        page_num_size = model_row_count / page_size;
        if(page_size * page_num_size != model_row_count)
        {
            page_num_size += 1;
        }
    }
    else
    {
        model_t->setFilter(QObject::tr(""));
        model_row_count = model_t->rowCount();
        page_num_size = model_row_count / page_size;
        if(page_size * page_num_size != model_row_count)
        {
            page_num_size += 1;
        }
    }

    if(query_value != "")
    {
        filter_string += query_column;
        filter_string += " = '%1' and ";
    }

    filter_string += primary_key_column;
    filter_string += " not in (select top ";
    num = current_page * page_size;
    number_to_string = QString::number(num, 10);
    filter_string += number_to_string;
    filter_string += " ";
    filter_string += primary_key_column;
    filter_string += " from ";
    filter_string += table_name;

    if(query_value != "")
    {
        filter_string += " where ";
        filter_string += query_column;
        filter_string += " = '%2'";
    }

    filter_string += " Order by ";
    filter_string += primary_key_column;
    filter_string += ") and ";
    filter_string += primary_key_column;
    filter_string += " not in (select top ";
    num = model_row_count - (current_page + 1) * page_size;
    if(num < 0)
        num = 0;
    //qDebug() << num;
    number_to_string = QString::number(num, 10);
    filter_string += number_to_string;
    filter_string += " ";
    filter_string += primary_key_column;
    filter_string += " from ";
    filter_string += table_name;

    if(query_value != "")
    {
        filter_string += " where ";
        filter_string += query_column;
        filter_string += " = '%3'";
    }

    filter_string += " Order by ";
    filter_string += primary_key_column;
    filter_string += " desc)";

    return filter_string;
}

void UI_MainWindow::SET_MODEL()
{
    //model_t->setTable("Well");
    //qDebug() << select_table[current_select_table];
    model_t->setTable(select_table[current_select_table]);
    model_t->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_t->select();
    model_t->setSort(0, Qt::AscendingOrder);

    model_row_count = model_t->rowCount();

    page_num_size = model_row_count / page_size;
    if(page_size * page_num_size != model_row_count)
    {
        page_num_size += 1;
    }

    current_page = 0;

    QString query_sql = setFilterString();
    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    model_t->setFilter(QObject::tr(ch));
}

void UI_MainWindow::ACTION_SELECT_TABLE()
{
    ui_select_table.exec();
    select_table = ui_select_table.select_table;
    ui_select_table.select_table.clear();

    current_select_table = 0;
    ui->BUTTON_CURRENT_TABLE_NAME->setText(select_table[current_select_table]);
    init();
    /*
    model_t = new QSqlTableModel(this);
    SET_MODEL();
    ui->TABLEVIEW->setModel(model_t);
    item_delegate = new ItemDelegate(this);
    ui->TABLEVIEW->setItemDelegate(item_delegate);

    query_column = model_t->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
    query_value = "";
    ui->LINEEDIT_QUERY_COLUMN->setText(query_column);

    ui->LABEL_TURN_PAGE->setText("/" + QString::number(page_num_size, 10));
    ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));

    QModelIndex latest_item = model_t->index(0, 0);
    latest_item_row = 0;
    latest_item_column = 0;
    //qDebug() << model_t->data(latest_item, 0);
    latest_item_data = model_t->data(latest_item).toString();
    */
}

void UI_MainWindow::ACTION_EXPORT()
{
    model_for_export = new QSqlTableModel(this);
    //model_for_export->setTable("Well");
    model_for_export->setTable(select_table[current_select_table]);
    model_for_export->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_for_export->select();
    //model_for_export->setSort(0, Qt::AscendingOrder);

    //qDebug() << current_page;

    if(query_value != "")
    {
        QString query_sql = query_column + " = '%1'";
        char *ch;
        QByteArray ba = query_sql.toLatin1();
        ch = ba.data();
        model_for_export->setFilter(QObject::tr(ch).arg(query_value));
    }

    ui_export.model = model_for_export;
    ui_export.exec();
}

void UI_MainWindow::ACTION_IMPORT()
{
    ui_import.model = model_t;
    ui_import.exec();
}

void UI_MainWindow::ACTION_PRINT()
{
    QPrinter printer(QPrinter::ScreenResolution);
    QPrintPreviewDialog dlg(&printer);

    connect(&dlg, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
    dlg.exec();
}

void UI_MainWindow::on_BUTTON_SAVE_clicked()
{
    model_t->database().transaction();
    if(model_t->submitAll())
    {
        model_t->database().commit();

        query_value = "";
        ui->LINEEDIT_QUERY_VALUE->setText(query_value);
        SET_MODEL();

        ui->LABEL_TURN_PAGE->setText("/" + QString::number(page_num_size, 10));
        ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));
    }
    else
    {
        model_t->database().rollback();
        QMessageBox::warning(this, tr("DataBase"), tr("DataBase Error: %1").arg(model_t->lastError().text()));
    }

    item_delegate->column.clear();
    item_delegate->row.clear();
}

void UI_MainWindow::on_BUTTON_ABORT_clicked()
{
    model_t->revertAll();

    item_delegate->column.clear();
    item_delegate->row.clear();
}

void UI_MainWindow::on_BUTTON_ADD_clicked()
{
    int row_num = model_t->rowCount();

    model_t->insertRow(row_num);

    for(int i = 0; i < model_t->columnCount(); i ++)
    {
        item_delegate->column.push_back(i);
        item_delegate->row.push_back(row_num);
    }
}

void UI_MainWindow::on_BUTTON_DELETE_clicked()
{
    int row_num = ui->TABLEVIEW->currentIndex().row();

    model_t->removeRow(row_num);

    /*
    int qmessagebox = QMessageBox::warning(this, tr("Delete current row"),
                                           tr("Delete operation can't be revert, are you sure to delete"),
                                           QMessageBox::Yes, QMessageBox::No);
    if(qmessagebox == QMessageBox::Yes)
    {
        model_t->submitAll();
    }
    else
    {
        model_t->revertAll();
    }
    */

    for(int i = 0; i < model_t->columnCount(); i ++)
    {
        item_delegate->column.push_back(i);
        item_delegate->row.push_back(row_num);
    }
}

void UI_MainWindow::on_BUTTON_REFRESH_clicked()
{
    query_value = "";
    ui->LINEEDIT_QUERY_VALUE->setText(query_value);

    SET_MODEL();
    ui->LABEL_TURN_PAGE->setText("/" + QString::number(page_num_size, 10));
    ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));

    item_delegate->column.clear();
    item_delegate->row.clear();
}

void UI_MainWindow::on_BUTTON_QUERY_clicked()
{

    query_value = ui->LINEEDIT_QUERY_VALUE->text();

    current_page = 0;

    QString query_sql = setFilterString();
    //qDebug() << query_sql;
    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    model_t->setFilter(QObject::tr(ch).arg(query_value, query_value, query_value));

    ui->LABEL_TURN_PAGE->setText("/" + QString::number(page_num_size, 10));

    item_delegate->column.clear();
    item_delegate->row.clear();
}

void UI_MainWindow::on_BUTTON_DELETEALL_clicked()
{
    int row_num = model_t->rowCount();
    int col_num = model_t->columnCount();
    model_t->removeRows(0, row_num);

    for(int i = 0; i < row_num; i ++)
    {
        for(int j = 0; j < col_num; j ++)
        {
            item_delegate->column.push_back(i);
            item_delegate->row.push_back(j);
        }
    }

    ui->LABEL_TURN_PAGE->setText("/" + QString::number(page_num_size, 10));
}

void UI_MainWindow::on_TABLEVIEW_clicked(const QModelIndex &index)
{

    int column = index.column();
    query_column = model_t->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
    ui->LINEEDIT_QUERY_COLUMN->setText(query_column);

    QModelIndex latest_item = model_t->index(latest_item_row, latest_item_column);
    //qDebug() << latest_item_row << latest_item_column << model_t->data(latest_item, 0);
    QString compare_string = model_t->data(latest_item).toString();
    //qDebug() << "compare string is : " << latest_item_data;
    if(compare_string != latest_item_data)
    {
        item_delegate->row.push_back(latest_item_row);
        item_delegate->column.push_back(latest_item_column);
    }

    latest_item_row = index.row();
    latest_item_column = index.column();
    latest_item = model_t->index(latest_item_row, latest_item_column);
    latest_item_data = model_t->data(latest_item).toString();
    //qDebug() << latest_item_row << latest_item_column << model_t->data(latest_item, 0);
    //qDebug() << "-----------------";
}

/*
void UI_MainWindow::on_TABLEVIEW_doubleClicked(const QModelIndex &index)
{
    item_delegate->column.push_back(index.column());
    item_delegate->row.push_back(index.row());
}
*/

void UI_MainWindow::on_COMBOBOX_PAGE_SIZE_activated(const QString &arg1)
{
    bool change_flag;
    page_size = arg1.toInt(&change_flag, 10);

    QString query_sql = setFilterString();
    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(query_value != "")
    {
        model_t->setFilter(QObject::tr(ch).arg(query_value, query_value, query_value));
    }
    else
    {
        model_t->setFilter(QObject::tr(ch));
    }

    item_delegate->column.clear();
    item_delegate->row.clear();

    ui->LABEL_TURN_PAGE->setText("/" + QString::number(page_num_size, 10));
    ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));
}

void UI_MainWindow::on_BUTTON_FIRST_PAGE_clicked()
{
    current_page = 0;
    ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));

    QString query_sql = setFilterString();
    //qDebug() << query_sql;

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(query_value != "")
    {
        model_t->setFilter(QObject::tr(ch).arg(query_value, query_value, query_value));
    }
    else
    {
        model_t->setFilter(QObject::tr(ch));
    }

    item_delegate->column.clear();
    item_delegate->row.clear();

    QModelIndex latest_item = model_t->index(0, 0);
    latest_item_row = 0;
    latest_item_column = 0;
    latest_item_data = model_t->data(latest_item).toString();
}

void UI_MainWindow::on_BUTTON_LAST_PAGE_clicked()
{
    current_page = page_num_size - 1;
    ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));

    QString query_sql = setFilterString();
    //qDebug() << query_sql;

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(query_value != "")
    {
        model_t->setFilter(QObject::tr(ch).arg(query_value, query_value, query_value));
    }
    else
    {
        model_t->setFilter(QObject::tr(ch));
    }

    item_delegate->column.clear();
    item_delegate->row.clear();

    QModelIndex latest_item = model_t->index(0, 0);
    latest_item_row = 0;
    latest_item_column = 0;
    latest_item_data = model_t->data(latest_item).toString();
}


void UI_MainWindow::on_BUTTON_PREVIOUS_PAGE_clicked()
{

    int temp_page = current_page - 1;
    if(temp_page >= 0)
    {
        current_page -= 1;
        ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));
    }
    else
    {
        return;
    }

    QString query_sql = setFilterString();
    //qDebug() << query_sql;

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(query_value != "")
    {
        model_t->setFilter(QObject::tr(ch).arg(query_value, query_value, query_value));
    }
    else
    {
        model_t->setFilter(QObject::tr(ch));
    }

    item_delegate->column.clear();
    item_delegate->row.clear();

    QModelIndex latest_item = model_t->index(0, 0);
    latest_item_row = 0;
    latest_item_column = 0;
    latest_item_data = model_t->data(latest_item).toString();
}

void UI_MainWindow::on_BUTTON_NEXT_PAGE_clicked()
{

    int temp_page = current_page + 1;
    if(temp_page < page_num_size)
    {
        current_page += 1;
        ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));
    }
    else
    {
        return;
    }

    QString query_sql = setFilterString();
    //qDebug() << query_sql;

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(query_value != "")
    {
        model_t->setFilter(QObject::tr(ch).arg(query_value, query_value, query_value));
    }
    else
    {
        model_t->setFilter(QObject::tr(ch));
    }

    item_delegate->column.clear();
    item_delegate->row.clear();

    //qDebug() << "start here -------";
    QModelIndex latest_item = model_t->index(0, 0);
    latest_item_row = 0;
    latest_item_column = 0;
    //qDebug() << model_t->data(latest_item, 0);
    latest_item_data = model_t->data(latest_item).toString();
    //qDebug() << latest_item_data;
    //qDebug() << "------------";
}

void UI_MainWindow::on_BUTTON_TURN_PAGE_clicked()
{

    current_page = ui->LINEEDIT_TURN_PAGE->text().toInt() - 1;

    if(current_page < 0 || current_page >= page_num_size)
    {
        return;
    }

    ui->LINEEDIT_TURN_PAGE->setText(QString::number(current_page + 1, 10));

    QString query_sql = setFilterString();
    //qDebug() << query_sql;

    char *ch;
    QByteArray ba = query_sql.toLatin1();
    ch = ba.data();
    if(query_value != "")
    {
        model_t->setFilter(QObject::tr(ch).arg(query_value, query_value, query_value));
    }
    else
    {
        model_t->setFilter(QObject::tr(ch));
    }

    item_delegate->column.clear();
    item_delegate->row.clear();

    QModelIndex latest_item = model_t->index(0, 0);
    latest_item_row = 0;
    latest_item_column = 0;
    latest_item_data = model_t->data(latest_item).toString();
}

void UI_MainWindow::on_BUTTON_EXEC_SQL_clicked()
{
    QString temp = "select * from well";

    QSqlQuery query;
    query.prepare(temp);
    query.exec();
    while(query.next()){
        qDebug() << query.value(1).toString() << query.value(2).toString();
    }
}

void UI_MainWindow::on_BUTTON_TURN_TO_LEFT_TABLE_clicked()
{
    if(current_select_table > 0)
    {
        current_select_table -= 1;
        ui->BUTTON_CURRENT_TABLE_NAME->setText(select_table[current_select_table]);
    }
    init();
}

void UI_MainWindow::on_BUTTON_TURN_TO_RIGHT_TABLE_clicked()
{
    if(current_select_table < select_table.size() - 1)
    {
        current_select_table += 1;
        ui->BUTTON_CURRENT_TABLE_NAME->setText(select_table[current_select_table]);
    }
    init();
}
