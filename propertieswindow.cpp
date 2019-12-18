#include "propertieswindow.h"
#include "ui_propertieswindow.h"
#include <QColorDialog>

PropertiesWindow::PropertiesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertiesWindow)
{
    ui->setupUi(this);
}

PropertiesWindow::~PropertiesWindow()
{
    delete ui;
}

bool PropertiesWindow::setValues(int fontSize, QColor fontColor, QColor backgroundColor)
{
    ui->spinBox->setValue(fontSize);
//!!! Вынести
    QPalette qp = ui->pushButton->palette();
    qp.setColor(QPalette::ButtonText, fontColor);
    ui->pushButton->setPalette(qp);
//!!! Вынести
    qp = ui->pushButton_2->palette();
    qp.setColor(QPalette::ButtonText, backgroundColor);
    ui->pushButton_2->setPalette(qp);

    return true;
}

bool PropertiesWindow::getValues(int *fontSize, QColor *fontColor, QColor *backgroundColor)
{
    *fontSize = ui->spinBox->value();
    *fontColor = ui->pushButton->palette().color(QPalette::ButtonText);
    *backgroundColor = ui->pushButton_2->palette().color(QPalette::ButtonText);
    return true;
}


void PropertiesWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(ui->pushButton->palette().color(QPalette::ButtonText));
    if (color.isValid() ) {

     //!!! Вынести
     QPalette qp = ui->pushButton->palette();
     qp.setColor(QPalette::ButtonText, color);
     ui->pushButton->setPalette(qp);

     ui->pushButton->show();
    }
}

void PropertiesWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(ui->pushButton_2->palette().color(QPalette::ButtonText));
    if (color.isValid() ) {

     //!!! Вынести
     QPalette qp = ui->pushButton_2->palette();
     qp.setColor(QPalette::ButtonText, color);
     ui->pushButton_2->setPalette(qp);

     ui->pushButton_2->show();
    }
}
