#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->getReposBTN->setEnabled(false);
    ui->downloadSelectedBTN->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inName_textChanged(const QString &data)
{
    if (data != "") {
        ui->getReposBTN->setEnabled(true);
    }else{
        ui->getReposBTN->setEnabled(false);
    }
}

void MainWindow::on_getReposBTN_clicked()
{
    QString username =  ui->inName->text();

    QString subStr(":user");
    if (ui->inType->currentIndex() == 1) {
        QString userReposURL = "https://api.github.com/users/" + username + "/repos";
    }else {
        QString orgReposURL = "https://api.github.com/orgs/" + username + "/repos";
    }

}
