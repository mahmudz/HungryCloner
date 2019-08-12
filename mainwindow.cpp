#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->getReposBTN->setEnabled(false);
    ui->downloadSelectedBTN->setEnabled(false);
    ui->allCheck->setEnabled(false);

    ui->inDownloadPath->setText(downloadPath);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void shellStatusPrint(QString &msg);

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
    QString username = ui->inName->text();
    QString reposURL;

    if (ui->inType->currentIndex() == 0) {
        reposURL = "https://api.github.com/users/" + username + "/repos";
    }else {
        reposURL = "https://api.github.com/orgs/" + username + "/repos";
    }

    ui->console->append("Fetching repo list...");

    QNetworkRequest request((QUrl(reposURL)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QNetworkReply *reply = manager.get(request);

    ui->console->append("Sending request...");

    while (!reply->isFinished()) {
        qApp->processEvents();
    }


    QByteArray response_data = reply->readAll();
    QJsonDocument repos = QJsonDocument::fromJson(response_data);

    reply->close();
    repoArray = repos.array();
    ui->repoTable->setRowCount(0);
    for(const QJsonValue& val: repoArray) {
        QJsonObject loopObj = val.toObject();

        QString repoName = loopObj["name"].toString();
        QString gitURL = loopObj["clone_url"].toString();

        QTableWidgetItem *repoNameItem = new QTableWidgetItem();
        repoNameItem->setCheckState(Qt::Checked);
        repoNameItem->setText(repoName);

        int rowCount = ui->repoTable->rowCount();
        ui->repoTable->insertRow(rowCount);

        ui->repoTable->setItem(rowCount, 0, repoNameItem);
        ui->repoTable->setItem(rowCount, 1, new QTableWidgetItem(gitURL));

    }
    ui->allCheck->setEnabled(true);
    ui->downloadSelectedBTN->setEnabled(true);
    ui->allCheck->setCheckState(Qt::Checked);
    ui->console->append("Data Loaded.");

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox about;
    about.setText("About");
    about.exec();
}


void MainWindow::on_allCheck_stateChanged(int status)
{
    if (status == 2) {
        for (int row = 0; row < ui->repoTable->rowCount(); row++) {
            ui->repoTable->item(row, 0)->setCheckState(Qt::Checked);
        }
    }else {
        for (int row = 0; row < ui->repoTable->rowCount(); row++) {
            ui->repoTable->item(row, 0)->setCheckState(Qt::Unchecked);
        }
    }


}

void MainWindow::on_dirChoserBTN_clicked()
{
    QFileDialog dialog(this);
    dialog.setDirectory(downloadPath);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.exec();
    ui->inDownloadPath->setText(dialog.directoryUrl().path().remove(0,1));
}
