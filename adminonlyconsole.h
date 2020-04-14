#ifndef ADMINONLYCONSOLE_H
#define ADMINONLYCONSOLE_H

#include <QDialog>
#include <QtSql>


namespace Ui {
class AdminOnlyConsole;
}

class AdminOnlyConsole : public QDialog
{
    Q_OBJECT

public:
    explicit AdminOnlyConsole(QWidget *parent = nullptr);
    ~AdminOnlyConsole();

    QSqlDatabase myDatabase;

    void connClose(){
        myDatabase.close();
        myDatabase.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(){
        myDatabase = QSqlDatabase::addDatabase("QSQLITE");
        myDatabase.setDatabaseName("/Users/austinm/BaseballParks.db");

        if(!myDatabase.open()){
            qDebug()<<("Database Status: Not Connected");
            return false;
        }
        else{
            qDebug()<<("Database Status: Connected");
            return true;
        }
    }

    bool priceIsNumber(QString price)
    {
        bool check = true;
        if(price == "")
            check = false;

        for(int i = 0; i < price.size(); i++){
            if(!((price[i] <= 58 && price[i] >= 48) || price[i] == 46))
                check = false;
        }

        return check;
    }

    bool souvCanAdd(QString team, QString SouvenirName){
        connOpen();
        QSqlQuery qry;
        int count = 0;
        qry.prepare("SELECT * FROM Souvenirs WHERE Team = :Team AND Souvenir = :Souvenir");
        qry.bindValue(":Team", team);
        qry.bindValue(":Souvenir", SouvenirName);
        qry.exec();
        while(qry.next()){
            count++;
        }
        connClose();
        return (count == 1);

    }

    bool dotOnce(QString price){
        int number = 0;
        for(int i = 0; i < price.size(); i++){
            if(price[i] == 46)
                number++;
        }

        return number <= 1;
    }


private slots:
    void on_addSouvButton_clicked();

    void on_deleteButton_clicked();

    void on_editSouvButton_clicked();

    void on_addBallparkButton_clicked();

    void on_deleteSouvStadList_activated(const QString &arg1);

    void on_editSouvStadList_activated(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::AdminOnlyConsole *ui;
};

#endif // ADMINONLYCONSOLE_H
