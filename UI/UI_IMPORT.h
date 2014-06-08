#ifndef UI_IMPORT_H
#define UI_IMPORT_H

#include <QDialog>
#include <QDebug>
#include <Qtsql/qsqltablemodel.h>
#include <QAxObject>
#include <QMessageBox>
#include <QTextStream>
#include <QString>

#include "UI_IMPORT_PREVIEW.h"
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
    bool make_preview_flag;

    void MAKE_TABLEWIDGET();

private:
    Ui::UI_IMPORT *ui;

    UI_IMPORT_PREVIEW ui_import_preview;

    QString size;
    QString splite;
    int column_count;
    QVector<int> change_column;
    QVector<QString> column_for_import;
    QVector<QVector<QString>> data_for_import;

    void IMPORT_FROM_EXCEL();
    void IMPORT_FROM_TXT();

    void MAKE_PREVIEW_EXCEL();
    void MAKE_PREVIEW_TXT();

private slots:
    void on_BUTTON_IMPORT_clicked();

    void on_BUTTON_PREVIEW_clicked();

    void on_COMBOBOX_SIZE_activated(const QString &arg1);
    void on_COMBOBOX_SPLITE_activated(const QString &arg1);
};

#endif // UI_IMPORT_H
