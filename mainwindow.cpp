#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "USBBus.h"
#include "FT232.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setTogglingEnabled(false);
    updateDevices();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonRefresh_clicked(bool checked)
{
    updateDevices();
}

void MainWindow::on_buttonToggle_clicked(bool checked)
{
    int idx = ui->listViewUSBDevices->currentRow();
    if (idx < 0) {
        /* Device not selected in list. */
        return;
    }
    FT232 *ft232 = new FT232(idx);
    ft232->togglePin(ui->spinBox->value());
}

void MainWindow::setTogglingEnabled(bool val)
{
    ui->spinBox->setEnabled(val);
    ui->label->setEnabled(val);
    ui->buttonToggle->setEnabled(val);
}

void MainWindow::on_radioButtonFT232_clicked(bool checked)
{
    setTogglingEnabled(true);
    updateDevices();
}

void MainWindow::on_radioButtonUSB_clicked(bool checked)
{
    setTogglingEnabled(false);
    updateDevices();
}

void MainWindow::updateDevices()
{
    USBDevice **devices;
    size_t cnt;

    USBBus* bus = new USBBus();

    ui->listViewUSBDevices->clear();


    if (ui->radioButtonUSB->isChecked()) {
        bus->enumerateDevices(&devices, &cnt);
        for (int i = 0; i < cnt; i++) {
            ui->listViewUSBDevices->addItem(devices[i]->toString());
        }
    } else {
        /* FT232 devices only. */
        cnt = bus->enumerateFT232();
        for (int i = 0; i < cnt; i++) {
            ui->listViewUSBDevices->addItem((new FT232(i))->toString());
        }
    }
}