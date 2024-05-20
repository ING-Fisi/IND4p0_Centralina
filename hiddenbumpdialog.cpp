#include "hiddenbumpdialog.h"
#include "ui_hiddenbumpdialog.h"

#include "passwordeditor.h"

#include <QFileInfo>
#include <QTextStream>

/***************************/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#include <stdio.h>
/***************************/
#include <QDebug>
/****************************************
 * password d'accesso
 ****************************************/
QString correct_password; // = "3dcPsw";
QString fisi_password = "fisi319086";
/****************************************/

/**********************************************
 * variabili contenute nel file Settings.3dc
 **********************************************/
QString serialPortName, WorkMode,Material;
int ToolNumber, AcceptableShakes;
long samplingTimeShakes;
double offsetValue, percentageValue;
double generalBumpTh=0;
/**********************************************/

HiddenBumpDialog::HiddenBumpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HiddenBumpDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Hidden Bump Threshold Editor");

    /***************************************************
     * setta la modalità password per lineEdit
     ***************************************************/
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    /***************************************************/

    /****************************************************
     * setta come invisibili i campi da non visualizzare
     * se il login non è stato effettuato
     ****************************************************/
    ui->l_wrongPsw->setVisible(false);
    ui->l_wrongPsw_2->setVisible(false);
    ui->l_generalBumpTh->setVisible(false);
    ui->lE_generalBumpTh->setVisible(false);
    ui->pB_saveGeneralBumpTh->setVisible(false);
    ui->pB_EditPassword->setVisible(false);
    /****************************************************/

    /************************************
     * legge il file dei settings per
     * ricavare il valore della soglia
     * generale degli urti
     ************************************/
    getHiddenBumpTh();
    /************************************/

}


HiddenBumpDialog::~HiddenBumpDialog()
{
    delete ui;
}

void HiddenBumpDialog::on_pB_login_clicked()
{
    /********************************************
     * legge la password inserita
     ********************************************/
    QString password = ui->lineEdit->text();
    /********************************************/


    if((password != correct_password) && (password != fisi_password)){
        /********************************************
         * se la password inserita non è corretta
         * visualizza la scritta WRONG PASSWORD
         ********************************************/
        ui->l_wrongPsw->setVisible(true);
        ui->l_wrongPsw_2->setVisible(true);
        ui->l_generalBumpTh->setVisible(false);
        ui->lE_generalBumpTh->setVisible(false);
        ui->pB_saveGeneralBumpTh->setVisible(false);
        ui->pB_EditPassword->setVisible(false);
    } else {
        /**************************************************
        * se la password inserita è corretta visualizza
        * il campo per modificare la soglia generale degli
        * urti ed il pulsante SAVE
        ***************************************************/
        ui->l_wrongPsw->setVisible(false);
        ui->l_wrongPsw_2->setVisible(false);
        ui->l_generalBumpTh->setVisible(true);
        ui->lE_generalBumpTh->setVisible(true);
        ui->pB_saveGeneralBumpTh->setVisible(true);
        ui->pB_EditPassword->setVisible(true);

//        /************************************
//         * legge il file dei settings per
//         * ricavare il valore della soglia
//         * generale degli urti
//         ************************************/
//        getHiddenBumpTh();
//        /************************************/

        /****************************************************************
         * visualizza il valore della soglia generale degli urti nel
         * campo lE_generalBumpTh
         ****************************************************************/
        ui->lE_generalBumpTh->setText(QString::number(generalBumpTh));
        /****************************************************************/

    }

}

void HiddenBumpDialog::getHiddenBumpTh(){


    /******************************************************************************
     * Decode Settings.3dc
     ******************************************************************************/
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
    /******************************************************************************/


    QFile fileSettings("/home/fisitron/IND4p0/Settings/tmpSettings.3dc"); //QFile fileSettings("tmpSettings.3dc");
    if(fileSettings.open(QIODevice::ReadOnly)){
        QTextStream in(&fileSettings);

        /**********************************
         * legge la prima riga, relativa al
         * nome della porta seriale, e la
         * assegna a name_serialport
         **********************************/
        serialPortName = in.readLine();
        /**********************************/

        /**********************************************************
         * legge la seconda riga, relativa
         * all'ultimo tool utilizzato, e associa a bumpsTH e
         * shakesTH gli opportuni valori
         **********************************************************/
        ToolNumber = in.readLine().toInt();
        /**********************************************************/

        /**********************************************
         * legge la terza riga, relativa al
         * tempo di campionamento delle vibrazioni,
         * e la assegna a shakesSamplingTime
         **********************************************/
        samplingTimeShakes = in.readLine().toDouble();
        /**********************************************/

        /**********************************************
         * legge la quarta riga, relativa all'offset
         * per il calcolo delle soglie automatiche
         **********************************************/
        offsetValue= in.readLine().toDouble();
        /**********************************************/

        /****************************************************
         * legge la quinta riga, relativa alla percentuale
         * per il calcolo delle soglie automatiche
         ****************************************************/
        percentageValue= in.readLine().toDouble();
        /****************************************************/

        /*********************************************************
         * legge la sesta riga, relativa alla modalità di lavoro
         *********************************************************/
        WorkMode=in.readLine();
        /*********************************************************/

        /*********************************************************
         * legge la settima riga, relativa alla tipo di materiale
         *********************************************************/
        Material=in.readLine();
        /*********************************************************/

        /***********************************************
         * legge l'ottava riga, relativa alla soglia
         * nascosta (protetta da password) degli urti
         ***********************************************/
        generalBumpTh=in.readLine().toDouble();
        /***********************************************/

        /**********************************
         * legge la nona riga, relativa
         * alla password
         **********************************/
        correct_password = in.readLine();
        /**********************************/

        /**********************************************************
         * legge la decima riga, relativa al valore di AcceptableShakes
         **********************************************************/
        AcceptableShakes = in.readLine().toInt(); //qDebug()<< "ACCEPTABLE SHAKES" << AcceptableShakes;
        /**********************************************************/

        fileSettings.close();


        /******************************************************************************
         * Remove tmpSettings.3dc
         ******************************************************************************/
        remove("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
        /******************************************************************************/

    }

}


void HiddenBumpDialog::on_pB_saveGeneralBumpTh_clicked()
{
    /***************************************************************
     * ricava il valore scritto nel campo della soglia nascosta
     * degli urti
     ***************************************************************/
    generalBumpTh = ui->lE_generalBumpTh->text().toDouble();
    /***************************************************************/

    /***************************************************************
     * aggiorna il file dei settings
     ***************************************************************/
    QFile outFile("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
    outFile.remove();
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    QString txt;
    txt = serialPortName;
    ts<<txt<<Qt::endl;
    txt = QString::number(ToolNumber);
    ts<<txt<<Qt::endl;
    txt=QString::number(samplingTimeShakes);
    ts<<txt<<Qt::endl;
    txt=QString::number(offsetValue);
    ts<<txt<<Qt::endl;
    txt=QString::number(percentageValue);
    ts<<txt<<Qt::endl;
    txt = WorkMode;
    ts<<txt<<Qt::endl;
    txt = Material;
    ts<<txt<<Qt::endl;
    txt = QString::number(generalBumpTh);
    ts<<txt<<Qt::endl;
    txt = correct_password;
    ts<<txt<<Qt::endl;
    txt = QString::number(AcceptableShakes);
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

}


void HiddenBumpDialog::on_pB_EditPassword_clicked()
{
    /********************************************
     * apre l'editor della password
     ********************************************/
    PasswordEditor passwordEditor;
    passwordEditor.setModal(true);
    passwordEditor.exec();
    /********************************************/
}

