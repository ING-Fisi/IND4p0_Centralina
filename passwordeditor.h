#ifndef PASSWORDEDITOR_H
#define PASSWORDEDITOR_H

#include <QDialog>

namespace Ui {
class PasswordEditor;
}

class PasswordEditor : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordEditor(QWidget *parent = nullptr);
    ~PasswordEditor();

private slots:
    void on_pB_saveNewPassword_clicked();

    void on_lE_CurrentPassword_editingFinished();

    void on_lE_NewPassword_editingFinished();

private:
    Ui::PasswordEditor *ui;
};

#endif // PASSWORDEDITOR_H
