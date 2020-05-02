#include "startupscreen.h"
#include "ui_startupscreen.h"
#include "adminloginscreen.h"
#include "fanscreen.h"

StartupScreen::StartupScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartupScreen)
{
    ui->setupUi(this);
}

StartupScreen::~StartupScreen()
{
    delete ui;
}

void StartupScreen::on_AdminLoginButton_clicked()
{
    AdminLoginScreen *screen = new AdminLoginScreen(this);
    screen->show();
    hide();

}

void StartupScreen::on_FanPageButton_clicked()
{
    FanScreen *newScreen = new FanScreen(this);
    newScreen->show();
    hide();
}
