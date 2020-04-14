#include "adminonlyconsole.h"
#include "ui_adminonlyconsole.h"
#include <QMessageBox>

AdminOnlyConsole::AdminOnlyConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminOnlyConsole)
{
    ui->setupUi(this);

    QSqlQueryModel * modal = new QSqlQueryModel();
    connOpen();
    QSqlQuery *qry = new QSqlQuery(myDatabase);
    qry->prepare("SELECT * FROM Parks ORDER BY Name Asc");
    qry->exec();
    modal->setQuery(*qry);
    ui->newSouvStadBox->setModel(modal);
    ui->deleteSouvStadList->setModel(modal);
    ui->editSouvStadList->setModel(modal);
    ui->souvViewComboBox->setModel(modal);


}

AdminOnlyConsole::~AdminOnlyConsole()
{
    delete ui;
}

void AdminOnlyConsole::on_addSouvButton_clicked()
{
    QString price = ui->addSouvPrice->text();
    QString souvName = ui->addSouvName->text();
    QString stadName = ui->newSouvStadBox->currentText();
    if(priceIsNumber(price) && price != "" && dotOnce(price) && !souvCanAdd(stadName, souvName)){
        connOpen();
        QSqlQuery qry;
        qry.prepare("INSERT INTO Souvenirs(Team, Souvenir, Price) VALUES(:Name, :Souvenir, :Price)");
        qry.bindValue(":Name", stadName);
        qry.bindValue(":Souvenir", souvName);
        qry.bindValue(":Price", price);
        qry.exec();
        connClose();
        QMessageBox::information(this, tr("Message"), "Souvenir Added successfully!");

    }
    else{
        if(souvCanAdd(stadName, souvName))
            QMessageBox::critical(this, tr("Invalid"), "Souvenir already exists! Please Try again!");
        else
            QMessageBox::critical(this, tr("Invalid"), "Invalid input for price, Please try again!");
    }
}

void AdminOnlyConsole::on_deleteButton_clicked()
{
    QString deleteSouv = ui->souvNameListDelete->currentText();
    QString teamName = ui->deleteSouvStadList->currentText();
    connOpen();
    QSqlQuery deleteQry;
    deleteQry.prepare("DELETE FROM Souvenirs WHERE Souvenir = :Souvenir AND Team = :Team");
    deleteQry.bindValue(":Souvenir", deleteSouv);
    deleteQry.bindValue(":Team", teamName);
    deleteQry.exec();
    QMessageBox::information(this, tr("Message"), "Souvenir Deleted successfully!");

    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(myDatabase);
    qry->prepare("SELECT Souvenir FROM Souvenirs WHERE Team = :Team");
    qry->bindValue(":Team", teamName);
    qry->exec();
    modal->setQuery(*qry);
    ui->souvNameListDelete->setModel(modal);
    connClose();

}

void AdminOnlyConsole::on_editSouvButton_clicked()
{
    QString team = ui->editSouvStadList->currentText();
    QString price = ui->newPriceInput->text();
    QString souvName = ui->editSouvNameList->currentText();
    if(price != "" && priceIsNumber(price) && dotOnce(price)){
        connOpen();
        QSqlQuery editQry;
        editQry.prepare("UPDATE Souvenirs SET Price = :Price WHERE Team = :Team AND Souvenir = :Souvenir");
        editQry.bindValue(":Price", price);
        editQry.bindValue(":Team", team);
        editQry.bindValue(":Souvenir", souvName);
        editQry.exec();
        connClose();
        QMessageBox::information(this, tr("Message"), "Souvenir Edited successfully!");
    }
    else
        QMessageBox::critical(this, tr("Invalid"), "Invalid input for price, Please try again!");


}

void AdminOnlyConsole::on_addBallparkButton_clicked()
{

}

void AdminOnlyConsole::on_deleteSouvStadList_activated(const QString &arg1)
{
    QSqlQueryModel * modal = new QSqlQueryModel();
    connOpen();
    QSqlQuery *qry = new QSqlQuery(myDatabase);
    qry->prepare("SELECT Souvenir FROM Souvenirs WHERE Team = :Team");
    qry->bindValue(":Team", arg1);
    qry->exec();
    modal->setQuery(*qry);
    ui->souvNameListDelete->setModel(modal);
    connClose();
}

void AdminOnlyConsole::on_editSouvStadList_activated(const QString &arg1)
{
    QSqlQueryModel * modal = new QSqlQueryModel();
    connOpen();
    QSqlQuery *qry = new QSqlQuery(myDatabase);
    qry->prepare("SELECT Souvenir FROM Souvenirs WHERE Team = :Team");
    qry->bindValue(":Team", arg1);
    qry->exec();
    modal->setQuery(*qry);
    ui->editSouvNameList->setModel(modal);
    connClose();
}

void AdminOnlyConsole::on_pushButton_clicked()
{

    QString team = ui->souvViewComboBox->currentText();

    //set up a Model pointer - Austin Murphy
    QSqlQueryModel * modal = new QSqlQueryModel();

    //open the database - Austin Murphy
    connOpen();
    QSqlQuery* qry = new QSqlQuery(myDatabase);

    //retreive the information from the database - Austin Murphy
    qry->prepare("SELECT Souvenir, Price FROM Souvenirs WHERE Team = :Team");
    qry->bindValue(":Team", team);

    //execute the query and show the model in the Admin Only Console - Austin Murphy
    qry->exec();
    modal->setQuery(*qry);
    ui->souvenirTableView->setModel(modal);

    //Close the connection - Austin Murphy
    connClose();
}
