#include "UI_IMPORT_PREVIEW.h"
#include "ui_UI_IMPORT_PREVIEW.h"

UI_IMPORT_PREVIEW::UI_IMPORT_PREVIEW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_IMPORT_PREVIEW)
{
    ui->setupUi(this);
}

UI_IMPORT_PREVIEW::~UI_IMPORT_PREVIEW()
{
    delete ui;
}

void UI_IMPORT_PREVIEW::make_widget()
{
    qDebug() << column_for_import;
    qDebug() << data_for_import;
    ui->TABLEWIDGET->clear();
    ui->TABLEWIDGET->setRowCount(data_for_import.size() + 1);
    ui->TABLEWIDGET->setColumnCount(column_for_import.size());

    for(int i = 0; i < column_for_import.size(); i ++)
    {
        ui->TABLEWIDGET->setItem(0, i, new QTableWidgetItem(column_for_import[i]));
    }

    for(int i = 0; i < data_for_import.size(); i ++)
    {
        for(int j = 0; j < data_for_import[i].size(); j ++)
        {
            ui->TABLEWIDGET->setItem(i + 1, j, new QTableWidgetItem(data_for_import[i][j]));
        }
    }
}
