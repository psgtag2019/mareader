#include <QtCore>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QXmlStreamReader>
#include <QScrollBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"
#include "readerfbfiles.h"
#include "propertieswindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textBrowser->clear();
    ui->textBrowser->setFontPointSize(20);

//    ui->textBrowser->setStyleSheet("QTextBrowser { background-color: rgb(109, 255, 99); color: white;}");

    //ui->textBrowser->setTextBackgroundColor(Qt::yellow);
    //ui->textBrowser->setTextColor(0xfffff);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_aExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_aOpen_triggered()
{
   QString text;
   QStringList content;

   ui->statusbar->clearMessage();
    QString name = QFileDialog::getOpenFileName(this, "открыть", QDir::currentPath(), "FB2 files (*.fb2);;All files (*.*)" );

    if(! name.isEmpty()) {
        ui->statusbar->showMessage(QFileInfo(name).baseName());
        //ReaderFBFiles rfb;
        if(name.endsWith(".zip"))
        {
            QString nameUn = QStandardPaths::standardLocations(QStandardPaths::TempLocation).at(0)
                            + "/mareader/" + QFileInfo(name).baseName();

            if(!ReaderFBFiles::UnZip(name, nameUn)) // распаковка архива
                qDebug() << "файл " << name << " не открыт";
            else
            {
                // извлекаем содержимое
                QString fname = QFileInfo(name).completeBaseName();
                nameUn += "/" + fname;
                ReaderFBFiles::readFBFile(nameUn, &text, &content, 20);
                // помещаем содержимое в окно textBrowser
                ui->textBrowser->setText(text);
                ui->textBrowser->verticalScrollBar()->setValue(0);
            }
        } else if(name.endsWith(".fb2")){

            ReaderFBFiles::readFBFile(name,&text,&content, 20);
            ui->textBrowser->setText(text);
            ui->textBrowser->verticalScrollBar()->setValue(0);
        }
    }
}


void MainWindow::on_aAbout_triggered()
{
    //QMessageBox::information(this, "О программе","Тут будет информация о программе...");
    AboutWindow* aw = new AboutWindow(this);
    aw->setModal(true);
    aw->exec();
    delete aw;
}

void MainWindow::on_aTextProperties_triggered()
{
    PropertiesWindow* pw = new PropertiesWindow(this);
    pw->setModal(true);
    if (pw->exec() == QDialog::Accepted){

    }
    delete pw;
}
