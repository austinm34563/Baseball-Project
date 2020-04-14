#ifndef STARTUPSCREEN_H
#define STARTUPSCREEN_H

#include <QMainWindow>

namespace Ui {
class StartupScreen;
}

class StartupScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartupScreen(QWidget *parent = nullptr);
    ~StartupScreen();

private slots:
    void on_AdminLoginButton_clicked();

private:
    Ui::StartupScreen *ui;
};

#endif // STARTUPSCREEN_H
