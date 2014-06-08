#ifndef UI_IMPORT_DETAIL_H
#define UI_IMPORT_DETAIL_H

#include <QDialog>

namespace Ui {
class UI_IMPORT_DETAIL;
}

class UI_IMPORT_DETAIL : public QDialog
{
    Q_OBJECT

public:
    explicit UI_IMPORT_DETAIL(QWidget *parent = 0);
    ~UI_IMPORT_DETAIL();

private:
    Ui::UI_IMPORT_DETAIL *ui;
};

#endif // UI_IMPORT_DETAIL_H
