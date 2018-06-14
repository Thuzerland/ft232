#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "USBBus.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonRefresh_clicked(bool checked)
{
    USBDevice **devices;
    size_t cnt;

    USBBus* bus = new USBBus();
    bus->enumerateDevices(&devices, &cnt);

    ui->listViewUSBDevices->clear();
    for (int i = 0; i < cnt; i++) {
        ui->listViewUSBDevices->addItem(devices[i]->toString());
    }
}
