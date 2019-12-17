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


void PropertiesWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(ui->pushButton->palette().text().color());
    if (color.isValid() ) {

     QPalette qp = ui->pushButton->palette();
     qp.setColor(QPalette::ButtonText, color);
     ui->pushButton->setPalette(qp);
     ui->pushButton->show();
    }
}

void PropertiesWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(ui->pushButton->palette().color(QPalette::Button));
    if (color.isValid() ) {

     QPalette qp = ui->pushButton_2->palette();
     qp.setColor(QPalette::ButtonText, color);
     ui->pushButton_2->setPalette(qp);
     ui->pushButton_2->show();
    }
}
