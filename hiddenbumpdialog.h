#ifndef HIDDENBUMPDIALOG_H
#define HIDDENBUMPDIALOG_H

#include <QDialog>
#include <QFile>
#include <QDateTime>


namespace Ui {
class HiddenBumpDialog;
}


class HiddenBumpDialog : public QDialog
{

    Q_OBJECT



public:
    explicit HiddenBumpDialog(QWidget *parent = nullptr);
    ~HiddenBumpDialog();

private slots:

    void on_pB_login_clicked();

    void getHiddenBumpTh();

    void on_pB_saveGeneralBumpTh_clicked();

    void on_pB_EditPassword_clicked();

private:
    Ui::HiddenBumpDialog *ui;
};

#endif // HIDDENBUMPDIALOG_H
