#ifndef ADMINLOGINSCREEN_H
#define ADMINLOGINSCREEN_H

#include <QDialog>

namespace Ui {
class AdminLoginScreen;
}

class AdminLoginScreen : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLoginScreen(QWidget *parent = nullptr);
    ~AdminLoginScreen();

private slots:
    void on_backButton_clicked();

    void on_loginButton_clicked();


private:
    Ui::AdminLoginScreen *ui;
};

#endif // ADMINLOGINSCREEN_H
