#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QDialog>

namespace Ui {
class PropertiesWindow;
}

class PropertiesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesWindow(QWidget *parent = nullptr);
    ~PropertiesWindow();
    bool setValues(int fontSize, QColor fontColor, QColor backgroundColor);
    bool getValues(int* fontSize, QColor* fontColor, QColor* backgroundColor);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PropertiesWindow *ui;
};

#endif // PROPERTIESWINDOW_H
