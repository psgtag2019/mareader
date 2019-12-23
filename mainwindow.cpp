#include <QtCore>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QXmlStreamReader>
#include <QScrollBar>
#include <QStandardPaths>
#include <QSqlQuery>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_aExit_triggered()
{
    if(db.isOpen()){
        db.close();
    }

    writeSettings();
    QApplication::quit();
}

void MainWindow::on_aOpen_triggered()
{
    ui->statusbar->clearMessage();
    QString name = QFileDialog::getOpenFileName(this, "открыть", QDir::currentPath(), "FB2 files (*.fb2);;All files (*.*)" );
    if(! name.isEmpty()) {
       readFB(name) ;
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
    fnt = ui->textBrowser->currentFont();
    pw->setValues(fontSize, fontColor, backgroundColor, fnt);
    pw->setModal(true);
    if (pw->exec() == QDialog::Accepted){
        pw->getValues(&fontSize, &fontColor, &backgroundColor, &fnt);
    }
    delete pw;
    setSettings();
    ui->textBrowser->show();
}

void MainWindow::init(QApplication* a)
{
    myOrganization = a->organizationName();
    myApplicationName = a->applicationName();
    fbFileName = a->arguments().size()>1 ? a->arguments().at(1) : "";
    readSettings();
    setSettings();
    QString fn  = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir dir;
    if (!dir.exists(fn)){
        dir.mkpath(fn);
    }
    fn += "/mareader.sqlite";
    qDebug() << "БД " << fn;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fn);
    db.open();
    if(!QDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)).exists("mareader.sqlite")){
        // Создадим базу для последних открытых книг
        QSqlQuery query;
        query.exec("create table recent ""(id integer primary key, ""filename varchar(250), ""name varchar(250))");
    }

    if (!fbFileName.isEmpty()) {
        readFB(fbFileName);
    }
}

void MainWindow::readFB(QString fbname)
{
    QString text;
    QStringList content;

    ui->statusbar->clearMessage();

    if(! fbname.isEmpty()) {
        ui->statusbar->showMessage(QFileInfo(fbname).baseName());
        //ReaderFBFiles rfb;
        fbFileName = fbname;
        if(fbname.endsWith(".zip"))
        {
            QString nameUn = QStandardPaths::standardLocations(QStandardPaths::TempLocation).at(0)
                    + "/mareader/" + QFileInfo(fbname).baseName();

            if(!ReaderFBFiles::UnZip(fbname, nameUn)) // распаковка архива
                qDebug() << "файл " << fbname << " не открыт";
            else
            {
                // извлекаем содержимое
                QString fname = QFileInfo(fbname).completeBaseName();
                nameUn += "/" + fname;
                ReaderFBFiles::readFBFile(nameUn, &text, &content, fontSize);
                // помещаем содержимое в окно textBrowser
                ui->textBrowser->setText(text);
                ui->textBrowser->verticalScrollBar()->setValue(0);
            }
        } else if(fbname.endsWith(".fb2")){

            ReaderFBFiles::readFBFile(fbname,&text,&content, fontSize);
            ui->textBrowser->setText(text);
            ui->textBrowser->verticalScrollBar()->setValue(0);
        }
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(myOrganization, myApplicationName);

    settings.beginGroup("MainWindow");
    settings.setValue("fontsize", fontSize);
    settings.setValue("font", fnt);
    settings.setValue("fontcolor", fontColor);
    settings.setValue("backgroundcolor", backgroundColor);
    settings.setValue("fbName", fbFileName);

    settings.setValue("pos", pos());
    settings.setValue("size", size());

    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings(myOrganization, myApplicationName);

    settings.beginGroup("MainWindow");
    fnt = settings.value("font", ui->textBrowser->currentFont()).value<QFont>();
    fontSize = settings.value("fontsize", 20).toInt();
    fontColor = settings.value("fontcolor", QColor(Qt::black)).value<QColor>();
    backgroundColor = settings.value("backgroundcolor", QColor(Qt::white)).value<QColor>();

    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    if (fbFileName.isEmpty()) {
        fbFileName = settings.value("fbName","").toString();
    }

    settings.endGroup();
    resize(size);

    move(pos);
}

void MainWindow::setSettings()
{
    ui->textBrowser->setFontPointSize(40);//fontSize);
    QString s;
    QTextStream(&s) << "QTextBrowser { background-color: " << backgroundColor.name() << "; color: "
                    << fontColor.name() << "; font-size: " << fontSize << "px; font-family:" << fnt.family() << ";}";
    ui->textBrowser->setStyleSheet(s);
}
