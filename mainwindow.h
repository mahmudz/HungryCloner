#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_inName_textChanged(const QString &arg1);

    void on_getReposBTN_clicked();

    void on_actionAbout_triggered();

    void on_allCheck_stateChanged(int arg1);

    void on_downloadSelectedBTN_clicked();

    void on_dirChoserBTN_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QJsonArray repoArray;
    QObject *gitShell = nullptr;
    QString downloadPath = QDir::currentPath();
    void cloneRepo(const QString repoURL);
};

#endif // MAINWINDOW_H
