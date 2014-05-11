#include "UI_SELECT_TABLE.h"
#include "ui_UI_SELECT_TABLE.h"

UI_SELECT_TABLE::UI_SELECT_TABLE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_SELECT_TABLE)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& Qt::WindowMaximizeButtonHint& Qt::WindowMinimizeButtonHint);

    flag = true;

    //LOGIC_TABLE for_table_name;
    //table = for_table_name.table_name;
}

UI_SELECT_TABLE::~UI_SELECT_TABLE()
{
    delete ui;
}

void UI_SELECT_TABLE::on_BUTTON_CONFIRM_clicked()
{
   //qDebug() << ui->CHECKBOX_1->checkState();
   //qDebug() << ui->CHECKBOX_2->checkState();

   if(ui->C_DrillingLithology->checkState() == Qt::CheckState(2))
   {
        select_table.push_back("DrillingLithology");
        ui->C_DrillingLithology->setCheckState(Qt::CheckState(0));
   }

   if(ui->C_EngineerData->checkState() == Qt::CheckState(2))
   {
       select_table.push_back("EngineerData");
       ui->C_EngineerData->setCheckState(Qt::CheckState(0));
   }

   if(ui->C_GasLog->checkState() == Qt::CheckState(2))
   {
       select_table.push_back("GasLog");
       ui->C_GasLog->setCheckState(Qt::CheckState(0));
   }

   if(ui->C_Well->checkState() == Qt::CheckState(2))
   {
       select_table.push_back("Well");
       ui->C_Well->setCheckState(Qt::CheckState(0));
   }

   close();
}
