#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->listWidget);
    ui->listWidget->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    create();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    checkSave();
    create();
}

void MainWindow::on_actionOpen_triggered()
{
    checkSave();
    QString path = QFileDialog::getOpenFileName(this,"Open","","To-Do (*.td)");
    if(path.isEmpty()) return;
    open(path);
}

void MainWindow::on_actionSave_triggered()
{
    if(m_filename.isEmpty())
    {
        on_actionSave_As_triggered();
        return;
    }

    save(m_filename);
}

void MainWindow::on_actionSave_As_triggered()
{
    QString path = QFileDialog::getSaveFileName(this,"Open","","To-Do (*.td)");
    if(path.isEmpty()) return;
    save(path);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAdd_triggered()
{
    createItem(Qt::CheckState::Unchecked,QString("New Item"));
    m_changed = true;
}

void MainWindow::on_actionRemove_triggered()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *itm, list)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(itm));
    }
    m_changed = true;
}

void MainWindow::on_actionClear_triggered()
{
    ui->listWidget->clear();
    m_changed = true;
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->listWidget->selectAll();
}

void MainWindow::on_actionSelect_None_triggered()
{
    ui->listWidget->clearSelection();
}

void MainWindow::on_actionChecked_triggered()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *itm, list)
    {
        itm->setCheckState(Qt::CheckState::Checked);
    }
    m_changed = true;
}

void MainWindow::on_actionUnchecked_triggered()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *itm, list)
    {
        itm->setCheckState(Qt::CheckState::Unchecked);
    }
    m_changed = true;
}

void MainWindow::on_actionPartially_triggered()
{
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    foreach(QListWidgetItem *itm, list)
    {
        itm->setCheckState(Qt::CheckState::PartiallyChecked);
    }
    m_changed = true;
}

void MainWindow::create()
{
    m_changed = false;
    m_filename.clear();
    ui->listWidget->clear();
}

void MainWindow::open(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    QDataStream stream(&file);
    int count;
    stream >> count;

    for (int i = 0;i < count;i++)
    {
        int state = 0;
        QString name;
        stream >> state;
        stream >> name;
        Qt::CheckState checkstate = static_cast<Qt::CheckState>(state);
        createItem(checkstate,name);
    }
    file.close();
    m_filename = path;
    m_changed = false;
}

void MainWindow::save(QString path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    QDataStream stream(&file);

    stream << ui->listWidget->count();
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        int state = static_cast<int>(item->checkState());
        stream << state;
        stream << item->text();
    }

    file.close();
    m_filename = path;
    m_changed = false;
}

void MainWindow::checkSave()
{
    if(!m_changed) return;
    QMessageBox::StandardButton btn = QMessageBox::question(this,"Save File?","Do you want to save your changes?");
    if(btn == QMessageBox::StandardButton::Yes) save(m_filename);
}

void MainWindow::createItem(Qt::CheckState state, QString name)
{
    QListWidgetItem *item = new QListWidgetItem(name,ui->listWidget);
    item->setCheckState(state);
    //item->setFlags(Qt::ItemIsEnabled | Qt::ItemFlag::ItemIsEditable | Qt::ItemFlag::ItemIsTristate | Qt::ItemFlag::ItemIsUserCheckable | Qt::ItemIsSelectable);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemFlag::ItemIsEditable | Qt::ItemFlag::ItemIsAutoTristate | Qt::ItemFlag::ItemIsUserCheckable | Qt::ItemIsSelectable);
    ui->listWidget->addItem(item);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
