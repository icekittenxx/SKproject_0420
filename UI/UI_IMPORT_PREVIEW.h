#ifndef UI_IMPORT_PREVIEW_H
#define UI_IMPORT_PREVIEW_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QDebug>

namespace Ui {
class UI_IMPORT_PREVIEW;
}

class UI_IMPORT_PREVIEW : public QDialog
{
    Q_OBJECT

public:
    explicit UI_IMPORT_PREVIEW(QWidget *parent = 0);
    ~UI_IMPORT_PREVIEW();

    void make_widget();

    QVector<QString> column_for_import;
    QVector<QVector<QString>> data_for_import;

private:
    Ui::UI_IMPORT_PREVIEW *ui;
};

#endif // UI_IMPORT_PREVIEW_H
