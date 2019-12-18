#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
//#include <QXml>
#include <QMainWindow>
#include <QtGui/private/qzipwriter_p.h>
#include <QtGui/private/qzipreader_p.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_aExit_triggered();

    void on_aOpen_triggered();

    void on_aAbout_triggered();

    void on_aTextProperties_triggered();

    void writeSettings();
    void readSettings();
    void setSettings();


private:
    Ui::MainWindow *ui;
//
    int fontSize = 20;
    QColor fontColor;
    QColor backgroundColor;
};
#endif // MAINWINDOW_H
