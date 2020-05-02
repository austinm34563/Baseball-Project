#include "adminloginscreen.h"
#include "ui_adminloginscreen.h"
#include "startupscreen.h"
#include "adminonlyconsole.h"

AdminLoginScreen::AdminLoginScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLoginScreen)
{
    ui->setupUi(this);
}

AdminLoginScreen::~AdminLoginScreen()
{
    delete ui;
}

void AdminLoginScreen::on_backButton_clicked()
{
    StartupScreen *screen = new StartupScreen(this);
    screen->show();
    hide();
}

void AdminLoginScreen::on_loginButton_clicked()
{
    if(ui->username->text() == "Admin" && ui->password->text() == "123"){
        AdminOnlyConsole *screen = new AdminOnlyConsole(this);
        screen->show();
        hide();
    }
}
