#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonRefresh_clicked(bool checked);

    void on_buttonToggle_clicked(bool checked);

    void on_radioButtonFT232_clicked(bool checked);

    void on_radioButtonUSB_clicked(bool checked);

private:
    Ui::MainWindow *ui;

    void setTogglingEnabled(bool val);

    void updateDevices();
};

#endif // MAINWINDOW_H
