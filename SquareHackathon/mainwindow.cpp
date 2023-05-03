#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "httprequests.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <iostream>
#include <string>
#include <QJsonValue>
#include <QtNetwork>
#include <fstream>
#include <QListWidget>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Start Contact List Hidden
    ui->staffProfile->hide();
//    connect(ui, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(largars(QListWidgetItem *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_clicked()
{
    /*
    JSON FORMAT:

    "team_member": {
        "family_name": "",
        "email_address": "",
        "given_name": "",
        "phone_number": ""
    }
    */

    QJsonObject teamMember;
    QJsonObject parent;

    // jsonVarName[key] = value;
    teamMember["family_name"] = ui->lastName->text();
    teamMember["email_address"] = ui->email->text();
    teamMember["given_name"] = ui->firstName->text();
    teamMember["phone_number"] = ui->phoneNumber->text();
    parent["team_member"] = teamMember;

    rq.addTeamMember(parent);

    showStaffList();
//     ui->staffProfile->show();

//     Print JSON Contents (also converts to string)
//        QJsonDocument Doc(parent);
//        QByteArray ba = Doc.toJson();
//        QString q = QString(ba);
//        std::cout << q.toStdString() << std::endl;
}

void MainWindow::showStaffList(){

    //complete http request
    QJsonObject teamMembersJson = rq.getTeamMembers();

    //gets the teamMember's array
    QJsonArray listOfMembers = teamMembersJson["team_members"].toArray();

    ui->staffList->clear();

    //make loop
    for (int i = 0; i < listOfMembers.size(); i++){
        //converts first item of array to object
        QJsonObject member1 = listOfMembers[i].toObject(); //gets the ith index of the array (ie gets each sector)

        //converts first member to string
        QString name = member1["given_name"].toString() + " " + member1["family_name"].toString();
        QString status = member1["status"].toString();
        QString email = member1["email_address"].toString();
        QString phoneNum = member1["phone_number"].toString();

        if(status[0] == 'I'){
            continue;
        }

        //does the ui part to print to screen
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(name);
        item->setData(1, email);
        item->setData(3, phoneNum);



        ui->staffList->addItem(item);
    }

    //    cout << "Type of team_members : " << typeid(teamMembersJson["team_members"]).name() << endl;

//    item->setText(QString(teamMembersJson["team_members"]));



//    QListWidgetItem* item = new QListWidgetItem();
//    item->setText(QString("Python"));

//    ui->staffList->addItem(item);

//    std::cout << "Item Added" << std::endl;
}


void MainWindow::on_pushButton_clicked()
{
    rq.inactivateTeamMember(QString("TMsTxtV7JpLEbYoY"));
}

void MainWindow::on_staffList_itemDoubleClicked(QListWidgetItem *item){
    ui->staffProfile->show();
}



