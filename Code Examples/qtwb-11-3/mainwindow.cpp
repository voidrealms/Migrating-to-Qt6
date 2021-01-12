#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->listView);
    auto toolbar = ui->toolBar;
    removeToolBar(toolbar);
    addToolBar(Qt::RightToolBarArea, toolbar);
    toolbar->show();

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    checkSaved();
    m_list.clear();
    m_path.clear();
    m_changed = false;
    m_model.setStringList(m_list);
}

void MainWindow::on_actionOpen_triggered()
{
    checkSaved();
    QString tmp;
    tmp = QFileDialog::getOpenFileName(this,"Open File");
    if(tmp.isEmpty()) return;

    m_path = tmp;
    m_list.clear();

    QFile file(m_path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    //QDataStream instead to load and save multi-line
    QTextStream stream(&file);
    while(!stream.atEnd())
    {
        m_list.append(stream.readLine());
    }


    file.close();
    m_changed = false;
    m_model.setStringList(m_list);
    ui->statusbar->showMessage("Opened",2000);
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(m_path);
    if(m_path.isEmpty())
    {
        on_actionSave_As_triggered();
        return;
    }

    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,"Error",file.errorString());
        return;
    }

    //QDataStream instead to load and save multi-line
    QTextStream stream(&file);
    foreach(QString line, m_list)
    {
        stream << line << "\r\n";
    }
    file.close();
    m_changed = false;
    ui->statusbar->showMessage("Saved",2000);
}

void MainWindow::on_actionSave_As_triggered()
{
    QString tmp = QFileDialog::getSaveFileName(this,"Save File");
    if(tmp.isEmpty()) return;

    m_path = tmp;
    on_actionSave_triggered();
}

void MainWindow::on_actionStart_triggered()
{
    m_timer.start();
    ui->statusbar->showMessage("Listening to the clipboard", 2000);
}

void MainWindow::on_actionStop_triggered()
{
    m_timer.stop();
    ui->statusbar->showMessage("Manual mode", 2000);
}

void MainWindow::on_actionCopy_triggered()
{
    QClipboard *clipboard = QApplication::clipboard();
    int index = ui->listView->currentIndex().row();

    clipboard->setText(m_list.at(index));
    ui->statusbar->showMessage("Copied", 2000);
}

void MainWindow::on_actionCut_triggered()
{
    QClipboard *clipboard = QApplication::clipboard();
    int index = ui->listView->currentIndex().row();

    clipboard->setText(m_list.at(index));
    m_list.removeAt(index);
    m_model.setStringList(m_list);
    m_changed = true;

    ui->statusbar->showMessage("Copied", 2000);
}

void MainWindow::on_actionPaste_triggered()
{
    timeout();
}

void MainWindow::on_actionDelete_triggered()
{
   int index = ui->listView->currentIndex().row();
   m_list.removeAt(index);
   m_model.setStringList(m_list);
   m_changed = true;
   ui->statusbar->showMessage("Deleted", 2000);
}

void MainWindow::timeout()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString data = clipboard->text();
    if(data.compare(this->m_last))
    {
        m_last = data;
        qDebug() << "YES: " << m_last;
        if(!m_list.contains(m_last))
        {
            m_list.append(m_last);
            m_model.setStringList(m_list);
            ui->statusbar->showMessage("Added form the clipboard",2000);
        }
    }

}

void MainWindow::init()
{
    m_changed = false;
    m_path = "";
    m_model.setStringList(m_list);
    ui->listView->setModel(&m_model);
    connect(&m_timer, &QTimer::timeout,this,&MainWindow::timeout);
    m_timer.setInterval(500);
    m_timer.start();
}

void MainWindow::checkSaved()
{
    if(!m_changed) return;
    QMessageBox::StandardButton btn = QMessageBox::question(this,"Save Changes?","Would like to save your  changes?");
    if(btn == QMessageBox::StandardButton::Yes) on_actionSave_triggered();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    checkSaved();
    event->accept();
}
