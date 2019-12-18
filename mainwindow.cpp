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
    readSettings();
    setSettings();

    //ui->textBrowser->setTextBackgroundColor(Qt::yellow);
    //ui->textBrowser->setTextColor(0xfffff);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_aExit_triggered()
{
    writeSettings();
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
    pw->setValues(fontSize, fontColor, backgroundColor);
    pw->setModal(true);
    if (pw->exec() == QDialog::Accepted){
        pw->getValues(&fontSize, &fontColor, &backgroundColor);
    }
    delete pw;
    setSettings();
    ui->textBrowser->show();
}

void MainWindow::writeSettings()
{
    QSettings settings("PSG_tag", "MaReader");

    settings.beginGroup("MainWindow");
    settings.setValue("fontsize", fontSize);
    settings.setValue("fontcolor", fontColor);
    settings.setValue("backgroundcolor", backgroundColor);

    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings("PSG_tag", "MaReader");

    settings.beginGroup("MainWindow");
    fontSize = settings.value("fontsize", 20).toInt();
    fontColor = settings.value("fontcolor", QColor(Qt::black)).value<QColor>();
    backgroundColor = settings.value("backgroundcolor", QColor(Qt::white)).value<QColor>();

    settings.endGroup();
}

void MainWindow::setSettings()
{
    ui->textBrowser->setFontPointSize(fontSize);
    QString s = "QTextBrowser { background-color: " + backgroundColor.name() +
                "; color: "+ fontColor.name() + ";}";
    ui->textBrowser->setStyleSheet(s);
}
