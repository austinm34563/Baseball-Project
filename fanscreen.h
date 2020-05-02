#ifndef FANSCREEN_H
#define FANSCREEN_H

#include <QDialog>

namespace Ui {
class FanScreen;
}

class FanScreen : public QDialog
{
    Q_OBJECT

public:
    explicit FanScreen(QWidget *parent = nullptr);
    ~FanScreen();

private slots:
    void on_viewAllButton_clicked();

    void on_viewAmericanButton_clicked();

    void on_viewNatButton_clicked();

    void on_chronOrderButton_clicked();

    void on_capOrderButton_clicked();

    void on_viewAllButtonStad_clicked();

private:
    Ui::FanScreen *ui;

    QString addComma(int num);
};

#endif // FANSCREEN_H
