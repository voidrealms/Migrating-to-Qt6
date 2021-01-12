#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    update();
    connect(&m_animal,&Animal::finished,this, &Dialog::finished);
    connect(&m_animal,&Animal::error,this, &Dialog::error);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_btnSave_clicked()
{
   QString path = QFileDialog::getSaveFileName(this,"Save As...");
   if(path.isEmpty()) return;

   m_animal.setName(ui->txtName->text());
   m_animal.setSpecies(ui->txtSpecies->text());
   m_animal.setAge(ui->sbAge->value());
   m_animal.setFed(ui->dtFed->dateTime());

   m_animal.toFile(path);

}

void Dialog::on_btnClear_clicked()
{
    m_animal.clear();
    update();
}

void Dialog::on_btnLoad_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Open");
    if(path.isEmpty()) return;

    m_animal.clear();
    m_animal.fromFile(path);
}

void Dialog::error(QString message)
{
    update();
    QMessageBox::warning(this,"Error",message);
}

void Dialog::finished()
{
    update();
    QMessageBox::information(this,"Complete","Concurrent IO Complete");

}

void Dialog::update()
{
    ui->txtName->setText(m_animal.name());
    ui->txtSpecies->setText(m_animal.species());
    ui->sbAge->setValue(m_animal.age());
    ui->dtFed->setDateTime(m_animal.fed());
}
