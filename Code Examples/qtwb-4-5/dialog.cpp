#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //Allow resize
    //Qt::WindowFlags flags = 0;
    Qt::WindowFlags flags;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowContextHelpButtonHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    QPushButton *btnCopy = new QPushButton("Copy",this);
    QPushButton *btnCut = new QPushButton("Cut",this);
    QPushButton *btnPaste = new QPushButton("Paste",this);
    QPushButton *btnUndo = new QPushButton("Undo",this);
    QPushButton *btnRedo = new QPushButton("Redo",this);

    ui->buttonBox->addButton(btnCopy,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnCut,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnPaste,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnUndo,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnRedo,QDialogButtonBox::ActionRole);

    connect(btnCopy,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::copy);
    connect(btnCut,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::cut);
    connect(btnPaste,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::paste);
    connect(btnUndo,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::undo);
    connect(btnRedo,&QPushButton::clicked,ui->plainTextEdit,&QPlainTextEdit::redo);

    load();

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_plainTextEdit_textChanged()
{
    m_saved = false;
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button->text().contains("Open"))
    {
        load();
        return;
    }

    if(button->text().contains("Save"))
    {
        save();
        return;
    }
}

void Dialog::load()
{
    ui->plainTextEdit->clear();
    QFile file("file.txt");
    if(!file.exists()) return;

    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    QTextStream stream(&file);
    ui->plainTextEdit->setPlainText(stream.readAll());

    file.close();
    m_saved = true;
}

void Dialog::save()
{
    QFile file("file.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    QTextStream stream(&file);
    stream << ui->plainTextEdit->toPlainText();

    file.close();
    m_saved = true;

    QMessageBox::information(this,"Saved!","We saved the file!!!");
}

void Dialog::closeEvent(QCloseEvent *event)
{
    //TO DO - our code
    event->accept();
}
