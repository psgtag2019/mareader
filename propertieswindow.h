#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class PropertiesWindow;
}

class PropertiesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesWindow(QWidget *parent = nullptr);
    ~PropertiesWindow();
    bool setValues(int fontSize, QColor fontColor, QColor backgroundColor, QFont fnt);
    bool getValues(int* fontSize, QColor* fontColor, QColor* backgroundColor, QFont* fnt);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void setButtonColor(QPushButton* btn, QColor color);

private:
    Ui::PropertiesWindow *ui;
};

#endif // PROPERTIESWINDOW_H
