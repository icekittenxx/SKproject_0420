#ifndef UI_SELECT_TABLE_H
#define UI_SELECT_TABLE_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QVector>

#include "../LOGIC/LOGIC_TABLE.h"

namespace Ui {
class UI_SELECT_TABLE;
}

class UI_SELECT_TABLE : public QDialog
{
    Q_OBJECT

public:
    explicit UI_SELECT_TABLE(QWidget *parent = 0);
    ~UI_SELECT_TABLE();

    bool flag;
    QVector<QString> select_table;
    QVector<QString> table;

private slots:
    void on_BUTTON_CONFIRM_clicked();

private:
    Ui::UI_SELECT_TABLE *ui;
};

#endif // UI_SELECT_TABLE_H
