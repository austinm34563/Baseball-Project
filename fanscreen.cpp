#include "fanscreen.h"
#include "ui_fanscreen.h"
#include "adminonlyconsole.h"
#include <QQueue>

FanScreen::FanScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FanScreen)
{
    ui->setupUi(this);
    AdminOnlyConsole admin;
    admin.connOpen();
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(admin.myDatabase);
    qry->prepare("SELECT Team, Stadium FROM ParkInformation ORDER BY Team Asc");
    qry->exec();
    model->setQuery(*qry);
    ui->teamList->setModel(model);

    //showing typology
    QSqlQueryModel * typModel = new QSqlQueryModel();
    QSqlQuery *getTypQry = new QSqlQuery(admin.myDatabase);
    getTypQry->prepare("SELECT Team, Stadium, Typology FROM ParkInformation ORDER BY Typology ASC");
    getTypQry->exec();
    typModel->setQuery(*getTypQry);
    ui->typologyViewTable->setModel(typModel);

    //showing open roof type
    QSqlQueryModel *roofModel = new QSqlQueryModel();
    QSqlQuery *getRoofQry = new QSqlQuery(admin.myDatabase);
    getRoofQry->prepare("SELECT Team FROM ParkInformation WHERE RoofType = 'Open' ORDER BY Team ASC");
    getRoofQry->exec();
    roofModel->setQuery(*getRoofQry);
    ui->openRoofList->setModel(roofModel);

    //get amount of roofs
    QSqlQuery numOfOpenQry;
    int numOpen = 0;
    numOfOpenQry.prepare("SELECT COUNT(*) From ParkInformation WHERE RoofType = 'Open'");
    numOfOpenQry.exec();
    while(numOfOpenQry.next()){
        numOpen = numOfOpenQry.value(0).toInt();
    }
    ui->openRoofNumLable->setText("Number of Teams with Open Roof: " + QString::number(numOpen));

    admin.connOpen();
    QSqlQueryModel * stadModel = new QSqlQueryModel();
    QSqlQuery *getStadiumQry = new QSqlQuery(admin.myDatabase);
    getStadiumQry->prepare("SELECT Team, Stadium, Opened FROM ParkInformation ORDER BY Opened ASC");
    getStadiumQry->exec();
    stadModel->setQuery(*getStadiumQry);
    ui->capacityAndChronTable->setModel(stadModel);
    admin.connClose();
    ui->typeLable->setText("Dates Opened in Chronological Order");

    admin.connClose();
}

FanScreen::~FanScreen()
{
    delete ui;
}

void FanScreen::on_viewAllButton_clicked()
{
    ui->whichButtonHitLable->setText("MLB Teams & Stadiums Sorted By Team Name");
    AdminOnlyConsole admin;
    admin.connOpen();
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(admin.myDatabase);
    qry->prepare("SELECT Team, Stadium FROM ParkInformation ORDER BY Team Asc");
    qry->exec();
    model->setQuery(*qry);
    ui->teamList->setModel(model);
    admin.connClose();
}

void FanScreen::on_viewAmericanButton_clicked()
{
    ui->whichButtonHitLable->setText("American League Teams & Stadiums Sorted By Team Name");
    AdminOnlyConsole admin;
    admin.connOpen();
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(admin.myDatabase);
    qry->prepare("SELECT Team, Stadium FROM ParkInformation WHERE League = :League ORDER BY Team Asc");
    qry->bindValue(":League", "American");
    qry->exec();
    model->setQuery(*qry);
    ui->teamList->setModel(model);
    admin.connClose();
}

void FanScreen::on_viewNatButton_clicked()
{
    ui->whichButtonHitLable->setText("National League Teams & Stadiums Sorted By Stadium Name");
    AdminOnlyConsole admin;
    admin.connOpen();
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(admin.myDatabase);
    qry->prepare("SELECT Stadium, Team FROM ParkInformation WHERE League = :League ORDER BY Stadium Asc");
    qry->bindValue(":League", "National");
    qry->exec();
    model->setQuery(*qry);
    ui->teamList->setModel(model);
    admin.connClose();
}


void FanScreen::on_chronOrderButton_clicked()
{

    ui->totalCapLable->setText(" ");
    AdminOnlyConsole admin;
    admin.connOpen();
    QSqlQueryModel * stadModel = new QSqlQueryModel();
    QSqlQuery *getStadiumQry = new QSqlQuery(admin.myDatabase);
    getStadiumQry->prepare("SELECT Team, Stadium, Opened FROM ParkInformation ORDER BY Opened ASC");
    getStadiumQry->exec();
    stadModel->setQuery(*getStadiumQry);
    ui->capacityAndChronTable->setModel(stadModel);
    admin.connClose();
    ui->typeLable->setText("Dates Opened in Chronological Order");
}

void FanScreen::on_capOrderButton_clicked()
{
    AdminOnlyConsole admin;
    admin.connOpen();
    QSqlQueryModel * stadModel = new QSqlQueryModel();
    QSqlQuery *getStadiumQry = new QSqlQuery(admin.myDatabase);
    getStadiumQry->prepare("SELECT Team, Stadium, Capacity FROM ParkInformation ORDER BY Capacity ASC");
    getStadiumQry->exec();
    stadModel->setQuery(*getStadiumQry);
    ui->capacityAndChronTable->setModel(stadModel);

    //getting the total amount now
    int totalCap = 0;
    QSqlQuery totalQry;
    totalQry.prepare("SELECT SUM(Capacity) FROM ParkInformation");
    totalQry.exec();
    while(totalQry.next())
        totalCap = totalQry.value(0).toInt();
    admin.connClose();

    QString totalCapStr = addComma(totalCap);
    //display info
    ui->typeLable->setText("Capacity of parks ordered from smallest to largest");
    ui->totalCapLable->setText("Total Capacity = " + totalCapStr);
}

QString FanScreen::addComma(int num){
    QString numHolder = QString::number(num);
    QQueue<QChar> digits;
    int counter = 1;
    int index = numHolder.size() - 1;

    while (index >= 0){
        if(counter%4 == 0){
            digits.push_front(',');
        }
        else{
            digits.push_front(numHolder[index]);
            index--;
        }

        counter++;
    }

    QString str;

    for(int i = 0; i < digits.size(); i++)
        str.append(digits.at(i));

    return str;
}


void FanScreen::on_viewAllButtonStad_clicked()
{
    ui->whichButtonHitLable->setText("MLB Teams & Stadiums Sorted By Stadium Name");
    AdminOnlyConsole admin;
    admin.connOpen();
    QSqlQueryModel * model = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(admin.myDatabase);
    qry->prepare("SELECT Stadium, Team FROM ParkInformation ORDER BY Stadium Asc");
    qry->exec();
    model->setQuery(*qry);
    ui->teamList->setModel(model);
    admin.connClose();
}
