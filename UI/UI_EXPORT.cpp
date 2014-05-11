#include "UI_EXPORT.h"
#include "ui_UI_EXPORT.h"

UI_EXPORT::UI_EXPORT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_EXPORT)
{
    ui->setupUi(this);

    size = ".xls";
}

UI_EXPORT::~UI_EXPORT()
{
    delete ui;
}

void UI_EXPORT::on_BUTTON_EXPORT_clicked()
{
    QString file_name = "D:/test" + size;

    ui->lineEdit->setText(file_name);

    QString path = ui->lineEdit->text();

    if(size == ".xls")
    {
        export_object.ExportToExcel(path, model, "well");
    }
    else if(size == ".pdf")
    {
        export_object.ExportToPdf(path, model, "well");
    }
    else
    {
        export_object.ExportToTxt(path, model, "well");
    }
}

void UI_EXPORT::on_COMBOBOX_activated(const QString &arg1)
{
    qDebug() << arg1;
    size = arg1;
}
