#include "UI_IMPORT_DETAIL.h"
#include "ui_UI_IMPORT_DETAIL.h"

UI_IMPORT_DETAIL::UI_IMPORT_DETAIL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_IMPORT_DETAIL)
{
    ui->setupUi(this);
}

UI_IMPORT_DETAIL::~UI_IMPORT_DETAIL()
{
    delete ui;
}
