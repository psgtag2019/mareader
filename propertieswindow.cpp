#include "propertieswindow.h"
#include "ui_propertieswindow.h"


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

bool PropertiesWindow::setValues(int fontSize, QColor fontColor, QColor backgroundColor, QFont fnt)
{
    ui->spinBox->setValue(fontSize);
    setButtonColor(ui->pushButton, fontColor);
    setButtonColor(ui->pushButton_2, backgroundColor);
    ui->fontComboBox->setCurrentFont(fnt);

    return true;
}

bool PropertiesWindow::getValues(int *fontSize, QColor *fontColor, QColor *backgroundColor, QFont* fnt)
{
    *fontSize = ui->spinBox->value();
    *fontColor = ui->pushButton->palette().color(QPalette::ButtonText);
    *backgroundColor = ui->pushButton_2->palette().color(QPalette::ButtonText);
    *fnt = ui->fontComboBox->currentFont();
    return true;
}


void PropertiesWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(ui->pushButton->palette().color(QPalette::ButtonText));
    if (color.isValid() ) {
        setButtonColor(ui->pushButton, color);
        ui->pushButton->show();
    }
}

void PropertiesWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor(ui->pushButton_2->palette().color(QPalette::ButtonText));
    if (color.isValid() ) {
        setButtonColor(ui->pushButton_2, color);
        ui->pushButton_2->show();
    }
}

void PropertiesWindow::setButtonColor(QPushButton *btn, QColor color)
{
    QPalette qp = btn->palette();
    qp.setColor(QPalette::ButtonText, color);
    btn->setPalette(qp);
}
