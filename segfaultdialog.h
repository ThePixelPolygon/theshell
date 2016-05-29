#ifndef SEGFAULTDIALOG_H
#define SEGFAULTDIALOG_H

#include <QDialog>

namespace Ui {
class SegfaultDialog;
}

class SegfaultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SegfaultDialog(QWidget *parent = 0);
    ~SegfaultDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SegfaultDialog *ui;
};

#endif // SEGFAULTDIALOG_H
