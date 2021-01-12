#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include "animal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnSave_clicked();
    void on_btnClear_clicked();
    void on_btnLoad_clicked();
    void error(QString message);
    void finished();

private:
    Ui::Dialog *ui;

    Animal m_animal;
    void update();
};
#endif // DIALOG_H
