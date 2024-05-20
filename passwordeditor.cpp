#include "passwordeditor.h"
#include "ui_passwordeditor.h"

#include <QFileInfo>
#include <QTextStream>


/***************************/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#include <stdio.h>
/***************************/

/*****************************************
 * password d'accesso fisitron
 *****************************************/
QString fisi_passwordTmp = "fisi319086";
/*****************************************/

/****************************************
 * nuova password d'accesso
 ****************************************/
QString new_password;
/****************************************/

/****************************************************************************
 * variabili contenute nel file Settings.3dc
 ****************************************************************************/
QString serialPortNameTmp, WorkModeTmp,MaterialTmp, correct_passwordTmp;
int ToolNumberTmp, acceptableShakesTmp;
long samplingTimeShakesTmp;
double offsetValueTmp, percentageValueTmp;
double generalBumpThTmp;
/****************************************************************************/

PasswordEditor::PasswordEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordEditor)
{
    ui->setupUi(this);
    this->setWindowTitle("Password Editor");


    /*******************************************
     * decodifica e legge il file Settings.3dc
     *******************************************/
    fstream fin, fout;
    int encKey = 0x4DE6E;
    string encFile = "/home/fisitron/IND4p0/Settings/Settings.3dc"; // file da decriptare
    char c;

    fin.open(encFile,fstream::in);
    fout.open("/home/fisitron/IND4p0/Settings/tmpSettings.3dc",fstream::out); // file decriptato

    while (fin >> noskipws >> c) {
        int temp = (c - encKey);

        // Write temp as char in
        // output file
        fout << (char)temp;
    }

    // Closing both files
    fin.close();
    fout.close();

    QFile fileSettings("/home/fisitron/IND4p0/Settings/tmpSettings.3dc"); //QFile fileSettings("tmpSettings.3dc");
    if(fileSettings.open(QIODevice::ReadOnly)){
        QTextStream in(&fileSettings);

        /**********************************
         * legge la prima riga, relativa al
         * nome della porta seriale, e la
         * assegna a name_serialport
         **********************************/
        serialPortNameTmp = in.readLine();
        /**********************************/

        /**********************************************************
         * legge la seconda riga, relativa
         * all'ultimo tool utilizzato, e associa a bumpsTH e
         * shakesTH gli opportuni valori
         **********************************************************/
        ToolNumberTmp = in.readLine().toInt();
        /**********************************************************/

        /**********************************************
         * legge la terza riga, relativa al
         * tempo di campionamento delle vibrazioni,
         * e la assegna a shakesSamplingTime
         **********************************************/
        samplingTimeShakesTmp = in.readLine().toDouble();
        /**********************************************/

        /**********************************************
         * legge la quarta riga, relativa all'offset
         * per il calcolo delle soglie automatiche
         **********************************************/
        offsetValueTmp = in.readLine().toDouble();
        /**********************************************/

        /****************************************************
         * legge la quinta riga, relativa alla percentuale
         * per il calcolo delle soglie automatiche
         ****************************************************/
        percentageValueTmp = in.readLine().toDouble();
        /****************************************************/

        /*********************************************************
         * legge la sesta riga, relativa alla modalità di lavoro
         *********************************************************/
        WorkModeTmp = in.readLine();
        /*********************************************************/

        /*********************************************************
         * legge la settima riga, relativa alla tipo di materiale
         *********************************************************/
        MaterialTmp = in.readLine();
        /*********************************************************/

        /***********************************************
         * legge l'ottava riga, relativa alla soglia
         * nascosta (protetta da password) degli urti
         ***********************************************/
        generalBumpThTmp = in.readLine().toDouble();
        /***********************************************/

        /**********************************
         * legge la nona riga, relativa
         * alla password
         **********************************/
        correct_passwordTmp = in.readLine();
        /**********************************/

        /**********************************************
         * legge la decima riga, relativa
         * al valore di acceptableShakes
         **********************************************/
        acceptableShakesTmp = in.readLine().toInt();
        /**********************************************/

        fileSettings.close();


        /******************************************************************************
         * Remove tmpSettings.3dc
         ******************************************************************************/
        remove("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
        /******************************************************************************/


    /*******************************************/
    }

}

PasswordEditor::~PasswordEditor()
{
    delete ui;
}

void PasswordEditor::on_pB_saveNewPassword_clicked()
{
    /*******************************************
     * ricava la nuova password
     *******************************************/
    new_password = ui->lE_NewPassword->text();
    /*******************************************/


    /*******************************************************************
     * aggiorna il file tmpSettings.3dc
     *******************************************************************/
    QFile outFile("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
    outFile.remove();
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    QString txt;
    txt = serialPortNameTmp;
    ts<<txt<<Qt::endl;
    txt = QString::number(ToolNumberTmp);
    ts<<txt<<Qt::endl;
    txt=QString::number(samplingTimeShakesTmp);
    ts<<txt<<Qt::endl;
    txt=QString::number(offsetValueTmp);
    ts<<txt<<Qt::endl;
    txt=QString::number(percentageValueTmp);
    ts<<txt<<Qt::endl;
    txt = WorkModeTmp;
    ts<<txt<<Qt::endl;
    txt = MaterialTmp;
    ts<<txt<<Qt::endl;
    txt = QString::number(generalBumpThTmp);
    ts<<txt<<Qt::endl;
    txt = new_password;
    ts<<txt<<Qt::endl;
    txt = QString::number(acceptableShakesTmp);
    ts<<txt<<Qt::endl;

    ts<<Qt::flush;
    //ts<<txt<<Qt::endl<<Qt::flush;

    outFile.close();
    /***************************************************************/

    /******************************************************************************
     * Encode tmpSettings.3dc in Settings.3dc
     ******************************************************************************/
    fstream fin, fout;
    int encKey = 0x4DE6E;
    string file = "/home/fisitron/IND4p0/Settings/tmpSettings.3dc"; // file da criptare
    char c;

    fin.open(file,fstream::in);
    fout.open("/home/fisitron/IND4p0/Settings/Settings.3dc",fstream::out); // file criptato

    while (fin >> noskipws >> c) {
        int temp = (c + encKey);

        // Write temp as char in
        // output file
        fout << (char)temp;
    }

    // Closing both files
    fin.close();
    fout.close();
    /******************************************************************************/

    /******************************************************************************
     * Remove tmpSettings.3dc
     ******************************************************************************/
    remove("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
    /******************************************************************************/

    /***************************************************
     * disabilita il pulsante di salvataggio
     ***************************************************/
    ui->pB_saveNewPassword->setEnabled(false);
    /***************************************************/
}


void PasswordEditor::on_lE_CurrentPassword_editingFinished()
{
    if( ( (ui->lE_CurrentPassword->text()==correct_passwordTmp) || (ui->lE_CurrentPassword->text()==fisi_passwordTmp) )
            && (ui->lE_NewPassword->text().isEmpty()==false) ){
        ui->pB_saveNewPassword->setEnabled(true);
    } else {
        ui->pB_saveNewPassword->setEnabled(false);
    }
}


void PasswordEditor::on_lE_NewPassword_editingFinished()
{
    if( ( (ui->lE_CurrentPassword->text()==correct_passwordTmp) || (ui->lE_CurrentPassword->text()==fisi_passwordTmp) )
            && (ui->lE_NewPassword->text().isEmpty()==false) ){
        ui->pB_saveNewPassword->setEnabled(true);
    } else {
        ui->pB_saveNewPassword->setEnabled(false);
    }

}

//void enableSaveButton(){
//    if( ( (ui->lE_CurrentPassword->text()==correct_passwordTmp) || (ui->lE_CurrentPassword->text()==fisi_passwordTmp) )
//            && (ui->lE_NewPassword->text().isEmpty()==false) ){
//        ui->pB_saveNewPassword->setEnabled(true);
//    } else {
//        ui->pB_saveNewPassword->setEnabled(false);
//    }
//}

