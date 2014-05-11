#include "UI_IMPORT.h"
#include "ui_UI_IMPORT.h"

UI_IMPORT::UI_IMPORT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UI_IMPORT)
{
    ui->setupUi(this);

    //ui->LINEEDIT_FILEPATH->setText("d:\\test.xls");
    ui->LINEEDIT_FILEPATH->setText("d:/test.xls");
}

UI_IMPORT::~UI_IMPORT()
{
    delete ui;
}

void UI_IMPORT::on_BUTTON_IMPORT_clicked()
{
    QString file_path = ui->LINEEDIT_FILEPATH->text();
    char *ch;
    QByteArray ba = file_path.toLatin1();
    ch = ba.data();

    QVector<QVector<QString>> data;

    QAxObject *excel = NULL;
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;
    excel = new QAxObject("Excel.Application");
    if(!excel)
    {
        QMessageBox::critical(this, "ERROR MESSAGE", "EXCEL OBJECT LOST");
        return;
    }
    excel->dynamicCall("SetVisible(bool)", false);
    workbooks = excel->querySubObject("WorkBooks");
    workbook = workbooks->querySubObject("Open(QString, QVariant)", QString(tr(ch)));
    //workbook = workbooks->querySubObject("Open(QString, QVariant)", QString(tr("d:\\test.xls")));
    QAxObject * worksheet = workbook->querySubObject("WorkSheets(int)", 1);//open first sheet
    //QAxObject * worksheet = workbook->querySubObject("WorkSheets");//get sheets point set
    //int intCount = worksheet->property("Count").toInt();//get sheets number

    QAxObject * usedrange = worksheet->querySubObject("UsedRange");//get sheet USEAGE
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");
    //get row and column
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    //get excel context
    for(int i = intRowStart; i < intRowStart + intRows; i ++)  //row
    {
        QVector<QString> temp_data;
        for (int j = intColStart; j < intColStart + intCols; j ++)  //column
        {
            QAxObject * cell = worksheet->querySubObject("Cells(int,int)", i, j );  //get cell
            // qDebug() << i << j << cell->property("Value");         //***something error!!!!!
            temp_data.push_back(cell->dynamicCall("Value2()").toString());
            //qDebug() << i << j << cell->dynamicCall("Value2()").toString(); //correct
            //qDebug() << i << j << temp_data[j - 1];
        }
        data.push_back(temp_data);
    }
    workbook->dynamicCall("Close (Boolean)", false);
    //for set, also use dynamimcCall("SetValue(const QVariant&)", QVariant(QString("Help!")))
    //excel->dynamicCall("Quit (void)");
    delete excel;//don't forget, else excel.exe will always exist

    /*
    for(int i = 0; i < data.size(); i ++)
    {
        for(int j = 0; j < data[i].size(); j ++)
        {
            qDebug() << data[i][j];
        }
        qDebug() << "-----";
    }
    */
    //qDebug() << model->tableName();
    import_object.ImportFromExcel(data, model);
}
