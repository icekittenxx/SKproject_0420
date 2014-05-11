#ifndef UI_IMPORT_H
#define UI_IMPORT_H

#include <QDialog>
#include <QDebug>
#include <Qtsql/qsqltablemodel.h>
#include <QAxObject>
#include <QMessageBox>

#include "../INTERFACE/IMPORT.h"

namespace Ui {
class UI_IMPORT;
}

class UI_IMPORT : public QDialog
{
    Q_OBJECT

public:
    explicit UI_IMPORT(QWidget *parent = 0);
    ~UI_IMPORT();

    QSqlTableModel *model;
    IMPORT import_object;

private slots:
    void on_BUTTON_IMPORT_clicked();

private:
    Ui::UI_IMPORT *ui;
};

#endif // UI_IMPORT_H
