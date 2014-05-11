#ifndef UI_EXPORT_H
#define UI_EXPORT_H

#include <QDialog>
#include <QDebug>
#include <Qtsql/qsqltablemodel.h>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QDateTime>

#include "../INTERFACE/EXPORT.h"

namespace Ui {
class UI_EXPORT;
}

class UI_EXPORT : public QDialog
{
    Q_OBJECT

public:
    explicit UI_EXPORT(QWidget *parent = 0);
    ~UI_EXPORT();

    QSqlTableModel *model;
    EXPORT export_object;

private slots:
    void on_BUTTON_EXPORT_clicked();

    void on_COMBOBOX_activated(const QString &arg1);

private:
    Ui::UI_EXPORT *ui;

    QString size;
};

#endif // UI_EXPORT_H
