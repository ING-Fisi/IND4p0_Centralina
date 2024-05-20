#include "tooloptions.h"
#include "ui_tooloptions.h"
#include <QFileInfo>
#include <QTextStream>


/***************************/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#include <stdio.h>
/***************************/



ToolOptions::ToolOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolOptions)
{
    ui->setupUi(this);

    this->setWindowTitle("Tool Options Editor");


    /**************************************************
     * probabilmente va letto il file dei settings
     * per ottenere il toolNum corrente e settare
     * opportunamente la comboBox cB_toolSelected
     **************************************************/
     //toolNum = ui->cB_toolSelected->currentIndex()+1;


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
        QString dummyStr = in.readLine();
        /**********************************/

        /**********************************************************
         * legge la seconda riga, relativa
         * all'ultimo tool utilizzato, e associa a bumpsTH e
         * shakesTH gli opportuni valori
         **********************************************************/
        toolNum = in.readLine().toInt();
        /**********************************************************/

        /**********************************************
         * legge la terza riga, relativa al
         * tempo di campionamento delle vibrazioni,
         * e la assegna a shakesSamplingTime
         **********************************************/
        long dummyLong = in.readLine().toDouble();
        /**********************************************/

        /**************************************************************************
         * calcola shakesMonitorFunctionCounterLimit. Si moltiplica per 1000
         * per avere il valore in ms e si divide per 200(ms) che è il valore
         * del periodo con cui viene richiamata la funzione shakesMonitorFunction
         **************************************************************************/
        //int dummyInt = lround(shakesSamplingTime*1000/shakesMonitorTimerPeriod);
        /**************************************************************************/

        /**********************************************
         * legge la quarta riga, relativa all'offset
         * per il calcolo delle soglie automatiche
         **********************************************/
        double dumyDouble= in.readLine().toDouble();
        /**********************************************/

        /****************************************************
         * legge la quinta riga, relativa alla percentuale
         * per il calcolo delle soglie automatiche
         ****************************************************/
        dumyDouble= in.readLine().toDouble();
        /****************************************************/

        /*********************************************************
         * legge la sesta riga, relativa alla modalità di lavoro
         *********************************************************/
        WorkingModality=in.readLine();
        /*********************************************************/

        /*********************************************************
         * legge la settima riga, relativa alla tipo di materiale
         *********************************************************/
        MaterialType=in.readLine();
        /*********************************************************/

        /***********************************************
         * legge l'ottava riga, relativa alla soglia
         * nascosta (protetta da password) degli urti
         ***********************************************/
        dumyDouble=in.readLine().toDouble();
        /***********************************************/

        /**********************************
         * legge la nona riga, relativa
         * alla password
         **********************************/
        dummyStr = in.readLine();
        /**********************************/

        /**********************************************
         * legge la decima riga, relativa al valore
         * di acceptableShakes
         **********************************************/
        int dummyInt = in.readLine().toInt();
        /**********************************************/

        fileSettings.close();

        /******************************************************************************
         * Remove tmpSettings.3dc
         ******************************************************************************/
        remove("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
        /******************************************************************************/


    }

    /***************************************************
     * toolNum = valore letto dal file dei settings
     ***************************************************/
    ui->cB_toolSelected->setCurrentIndex(toolNum-1);
    /***************************************************/


    /*************************************************
     * Legge il file _ToolOptions.3dc
     *************************************************/
    QFile file("/home/fisitron/IND4p0/ToolOptions/_ToolOptions.3dc"); //QFile file("_ToolOptions.3dc");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);

        Description1 = in.readLine();
        BumpsTh1 = in.readLine().toDouble();
        ShakeTh1 = in.readLine().toDouble();
        BumpsThmedium1 = in.readLine().toDouble();
        ShakeThmedium1 = in.readLine().toDouble();
        BumpsThhard1 = in.readLine().toDouble();
        ShakeThhard1 = in.readLine().toDouble();

        Description2 = in.readLine();
        BumpsTh2 = in.readLine().toDouble();
        ShakeTh2 = in.readLine().toDouble();
        BumpsThmedium2 = in.readLine().toDouble();
        ShakeThmedium2 = in.readLine().toDouble();
        BumpsThhard2 = in.readLine().toDouble();
        ShakeThhard2 = in.readLine().toDouble();

        Description3 = in.readLine();
        BumpsTh3 = in.readLine().toDouble();
        ShakeTh3 = in.readLine().toDouble();
        BumpsThmedium3 = in.readLine().toDouble();
        ShakeThmedium3 = in.readLine().toDouble();
        BumpsThhard3 = in.readLine().toDouble();
        ShakeThhard3 = in.readLine().toDouble();

        Description4 = in.readLine();
        BumpsTh4 = in.readLine().toDouble();
        ShakeTh4 = in.readLine().toDouble();
        BumpsThmedium4 = in.readLine().toDouble();
        ShakeThmedium4 = in.readLine().toDouble();
        BumpsThhard4 = in.readLine().toDouble();
        ShakeThhard4 = in.readLine().toDouble();

        Description5 = in.readLine();
        BumpsTh5 = in.readLine().toDouble();
        ShakeTh5 = in.readLine().toDouble();
        BumpsThmedium5 = in.readLine().toDouble();
        ShakeThmedium5 = in.readLine().toDouble();
        BumpsThhard5 = in.readLine().toDouble();
        ShakeThhard5 = in.readLine().toDouble();

        Description6 = in.readLine();
        BumpsTh6 = in.readLine().toDouble();
        ShakeTh6 = in.readLine().toDouble();
        BumpsThmedium6 = in.readLine().toDouble();
        ShakeThmedium6 = in.readLine().toDouble();
        BumpsThhard6 = in.readLine().toDouble();
        ShakeThhard6 = in.readLine().toDouble();

        Description7 = in.readLine();
        BumpsTh7 = in.readLine().toDouble();
        ShakeTh7 = in.readLine().toDouble();
        BumpsThmedium7 = in.readLine().toDouble();
        ShakeThmedium7 = in.readLine().toDouble();
        BumpsThhard7 = in.readLine().toDouble();
        ShakeThhard7 = in.readLine().toDouble();

        Description8 = in.readLine();
        BumpsTh8 = in.readLine().toDouble();
        ShakeTh8 = in.readLine().toDouble();
        BumpsThmedium8 = in.readLine().toDouble();
        ShakeThmedium8 = in.readLine().toDouble();
        BumpsThhard8 = in.readLine().toDouble();
        ShakeThhard8 = in.readLine().toDouble();

        Description9 = in.readLine();
        BumpsTh9 = in.readLine().toDouble();
        ShakeTh9 = in.readLine().toDouble();
        BumpsThmedium9 = in.readLine().toDouble();
        ShakeThmedium9 = in.readLine().toDouble();
        BumpsThhard9 = in.readLine().toDouble();
        ShakeThhard9 = in.readLine().toDouble();

        Description10 = in.readLine();
        BumpsTh10 = in.readLine().toDouble();
        ShakeTh10 = in.readLine().toDouble();
        BumpsThmedium10 = in.readLine().toDouble();
        shakeThmedium10 = in.readLine().toDouble();
        bumpsThhard10 = in.readLine().toDouble();
        shakeThhard10 = in.readLine().toDouble();

        Description11 = in.readLine();
        BumpsTh11 = in.readLine().toDouble();
        ShakeTh11 = in.readLine().toDouble();
        BumpsThmedium11 = in.readLine().toDouble();
        shakeThmedium11 = in.readLine().toDouble();
        bumpsThhard11 = in.readLine().toDouble();
        shakeThhard11 = in.readLine().toDouble();

        Description12 = in.readLine();
        BumpsTh12 = in.readLine().toDouble();
        ShakeTh12 = in.readLine().toDouble();
        BumpsThmedium12 = in.readLine().toDouble();
        shakeThmedium12 = in.readLine().toDouble();
        bumpsThhard12 = in.readLine().toDouble();
        shakeThhard12 = in.readLine().toDouble();

        Description13 = in.readLine();
        BumpsTh13 = in.readLine().toDouble();
        ShakeTh13 = in.readLine().toDouble();
        BumpsThmedium13 = in.readLine().toDouble();
        shakeThmedium13 = in.readLine().toDouble();
        bumpsThhard13 = in.readLine().toDouble();
        shakeThhard13 = in.readLine().toDouble();

        Description14 = in.readLine();
        BumpsTh14 = in.readLine().toDouble();
        ShakeTh14 = in.readLine().toDouble();
        BumpsThmedium14 = in.readLine().toDouble();
        shakeThmedium14 = in.readLine().toDouble();
        bumpsThhard14 = in.readLine().toDouble();
        shakeThhard14 = in.readLine().toDouble();

        Description15 = in.readLine();
        BumpsTh15 = in.readLine().toDouble();
        ShakeTh15 = in.readLine().toDouble();
        BumpsThmedium15 = in.readLine().toDouble();
        shakeThmedium15 = in.readLine().toDouble();
        bumpsThhard15 = in.readLine().toDouble();
        shakeThhard15 = in.readLine().toDouble();

        Description16 = in.readLine();
        BumpsTh16 = in.readLine().toDouble();
        ShakeTh16 = in.readLine().toDouble();
        BumpsThmedium16 = in.readLine().toDouble();
        shakeThmedium16 = in.readLine().toDouble();
        bumpsThhard16 = in.readLine().toDouble();
        shakeThhard16 = in.readLine().toDouble();

        Description17 = in.readLine();
        BumpsTh17 = in.readLine().toDouble();
        ShakeTh17 = in.readLine().toDouble();
        BumpsThmedium17 = in.readLine().toDouble();
        shakeThmedium17 = in.readLine().toDouble();
        bumpsThhard17 = in.readLine().toDouble();
        shakeThhard17 = in.readLine().toDouble();

        Description18 = in.readLine();
        BumpsTh18 = in.readLine().toDouble();
        ShakeTh18 = in.readLine().toDouble();
        BumpsThmedium18 = in.readLine().toDouble();
        shakeThmedium18 = in.readLine().toDouble();
        bumpsThhard18 = in.readLine().toDouble();
        shakeThhard18 = in.readLine().toDouble();

        Description19 = in.readLine();
        BumpsTh19 = in.readLine().toDouble();
        ShakeTh19 = in.readLine().toDouble();
        BumpsThmedium19 = in.readLine().toDouble();
        shakeThmedium19 = in.readLine().toDouble();
        bumpsThhard19 = in.readLine().toDouble();
        shakeThhard19 = in.readLine().toDouble();

        Description20 = in.readLine();
        BumpsTh20 = in.readLine().toDouble();
        ShakeTh20 = in.readLine().toDouble();
        BumpsThmedium20 = in.readLine().toDouble();
        ShakeThmedium20 = in.readLine().toDouble();
        BumpsThhard20 = in.readLine().toDouble();
        ShakeThhard20 = in.readLine().toDouble();

        Description21 = in.readLine();
        BumpsTh21 = in.readLine().toDouble();
        ShakeTh21 = in.readLine().toDouble();
        BumpsThmedium21 = in.readLine().toDouble();
        ShakeThmedium21 = in.readLine().toDouble();
        BumpsThhard21 = in.readLine().toDouble();
        ShakeThhard21 = in.readLine().toDouble();

        Description22 = in.readLine();
        BumpsTh22 = in.readLine().toDouble();
        ShakeTh22 = in.readLine().toDouble();
        BumpsThmedium22 = in.readLine().toDouble();
        ShakeThmedium22 = in.readLine().toDouble();
        BumpsThhard22 = in.readLine().toDouble();
        ShakeThhard22 = in.readLine().toDouble();

        Description23 = in.readLine();
        BumpsTh23 = in.readLine().toDouble();
        ShakeTh23 = in.readLine().toDouble();
        BumpsThmedium23 = in.readLine().toDouble();
        ShakeThmedium23 = in.readLine().toDouble();
        BumpsThhard23 = in.readLine().toDouble();
        ShakeThhard23 = in.readLine().toDouble();

        Description24 = in.readLine();
        BumpsTh24 = in.readLine().toDouble();
        ShakeTh24 = in.readLine().toDouble();
        BumpsThmedium24 = in.readLine().toDouble();
        ShakeThmedium24 = in.readLine().toDouble();
        BumpsThhard24 = in.readLine().toDouble();
        ShakeThhard24 = in.readLine().toDouble();

        Description25 = in.readLine();
        BumpsTh25 = in.readLine().toDouble();
        ShakeTh25 = in.readLine().toDouble();
        BumpsThmedium25 = in.readLine().toDouble();
        ShakeThmedium25 = in.readLine().toDouble();
        BumpsThhard25 = in.readLine().toDouble();
        ShakeThhard25 = in.readLine().toDouble();

        Description26 = in.readLine();
        BumpsTh26 = in.readLine().toDouble();
        ShakeTh26 = in.readLine().toDouble();
        BumpsThmedium26 = in.readLine().toDouble();
        ShakeThmedium26 = in.readLine().toDouble();
        BumpsThhard26 = in.readLine().toDouble();
        ShakeThhard26 = in.readLine().toDouble();

        Description27 = in.readLine();
        BumpsTh27 = in.readLine().toDouble();
        ShakeTh27 = in.readLine().toDouble();
        BumpsThmedium27 = in.readLine().toDouble();
        ShakeThmedium27 = in.readLine().toDouble();
        BumpsThhard27 = in.readLine().toDouble();
        ShakeThhard27 = in.readLine().toDouble();

        Description28 = in.readLine();
        BumpsTh28 = in.readLine().toDouble();
        ShakeTh28 = in.readLine().toDouble();
        BumpsThmedium28 = in.readLine().toDouble();
        ShakeThmedium28 = in.readLine().toDouble();
        BumpsThhard28 = in.readLine().toDouble();
        ShakeThhard28 = in.readLine().toDouble();

        Description29 = in.readLine();
        BumpsTh29 = in.readLine().toDouble();
        ShakeTh29 = in.readLine().toDouble();
        BumpsThmedium29 = in.readLine().toDouble();
        ShakeThmedium29 = in.readLine().toDouble();
        BumpsThhard29 = in.readLine().toDouble();
        ShakeThhard29 = in.readLine().toDouble();

        Description30 = in.readLine();
        BumpsTh30 = in.readLine().toDouble();
        ShakeTh30 = in.readLine().toDouble();
        BumpsThmedium30 = in.readLine().toDouble();
        ShakeThmedium30 = in.readLine().toDouble();
        BumpsThhard30 = in.readLine().toDouble();
        ShakeThhard30 = in.readLine().toDouble();

        Description31 = in.readLine();
        BumpsTh31 = in.readLine().toDouble();
        ShakeTh31 = in.readLine().toDouble();
        BumpsThmedium31 = in.readLine().toDouble();
        ShakeThmedium31 = in.readLine().toDouble();
        BumpsThhard31 = in.readLine().toDouble();
        ShakeThhard31 = in.readLine().toDouble();

        Description32 = in.readLine();
        BumpsTh32 = in.readLine().toDouble();
        ShakeTh32 = in.readLine().toDouble();
        BumpsThmedium32 = in.readLine().toDouble();
        ShakeThmedium32 = in.readLine().toDouble();
        BumpsThhard32 = in.readLine().toDouble();
        ShakeThhard32 = in.readLine().toDouble();


        file.close();

    }
    /*************************************************/

    /*****************************
     * riempie gli edit fields
     *****************************/
    fillEditFields();
    /*****************************/

}

ToolOptions::~ToolOptions()
{
    delete ui;
}


void ToolOptions::on_pB_DefaultOpt_clicked()
{
    /********************************
     * setta i valori di default
     * per ciascuno dei 32 tool
     ********************************/
    Description1 = defaultDescription;
    BumpsTh1 = defaultBumpsTh;
    ShakeTh1 = defaultShakeTh;
    BumpsThmedium1 = defaultBumpsTh;
    ShakeThmedium1 = defaultShakeTh;
    BumpsThhard1 = defaultBumpsTh;
    ShakeThhard1 = defaultShakeTh;

    Description2 = defaultDescription;
    BumpsTh2 = defaultBumpsTh;
    ShakeTh2 = defaultShakeTh;
    BumpsThmedium2 = defaultBumpsTh;
    ShakeThmedium2 = defaultShakeTh;
    BumpsThhard2 = defaultBumpsTh;
    ShakeThhard2 = defaultShakeTh;

    Description3 = defaultDescription;
    BumpsTh3 = defaultBumpsTh;
    ShakeTh3 = defaultShakeTh;
    BumpsThmedium3 = defaultBumpsTh;
    ShakeThmedium3 = defaultShakeTh;
    BumpsThhard3 = defaultBumpsTh;
    ShakeThhard3 = defaultShakeTh;

    Description4 = defaultDescription;
    BumpsTh4 = defaultBumpsTh;
    ShakeTh4 = defaultShakeTh;
    BumpsThmedium4 = defaultBumpsTh;
    ShakeThmedium4 = defaultShakeTh;
    BumpsThhard4 = defaultBumpsTh;
    ShakeThhard4 = defaultShakeTh;

    Description5 = defaultDescription;
    BumpsTh5 = defaultBumpsTh;
    ShakeTh5 = defaultShakeTh;
    BumpsThmedium5 = defaultBumpsTh;
    ShakeThmedium5 = defaultShakeTh;
    BumpsThhard5 = defaultBumpsTh;
    ShakeThhard5 = defaultShakeTh;

    Description6 = defaultDescription;
    BumpsTh6 = defaultBumpsTh;
    ShakeTh6 = defaultShakeTh;
    BumpsThmedium6 = defaultBumpsTh;
    ShakeThmedium6 = defaultShakeTh;
    BumpsThhard6 = defaultBumpsTh;
    ShakeThhard6 = defaultShakeTh;

    Description7 = defaultDescription;
    BumpsTh7 = defaultBumpsTh;
    ShakeTh7 = defaultShakeTh;
    BumpsThmedium7 = defaultBumpsTh;
    ShakeThmedium7 = defaultShakeTh;
    BumpsThhard7 = defaultBumpsTh;
    ShakeThhard7 = defaultShakeTh;

    Description8 = defaultDescription;
    BumpsTh8 = defaultBumpsTh;
    ShakeTh8 = defaultShakeTh;
    BumpsThmedium8 = defaultBumpsTh;
    ShakeThmedium8 = defaultShakeTh;
    BumpsThhard8 = defaultBumpsTh;
    ShakeThhard8 = defaultShakeTh;

    Description9 = defaultDescription;
    BumpsTh9 = defaultBumpsTh;
    ShakeTh9 = defaultShakeTh;
    BumpsThmedium9 = defaultBumpsTh;
    ShakeThmedium9 = defaultShakeTh;
    BumpsThhard9 = defaultBumpsTh;
    ShakeThhard9 = defaultShakeTh;

    Description10 = defaultDescription;
    BumpsTh10 = defaultBumpsTh;
    ShakeTh10 = defaultShakeTh;
    BumpsThmedium10 = defaultBumpsTh;
    shakeThmedium10 = defaultShakeTh;
    bumpsThhard10 = defaultBumpsTh;
    shakeThhard10 = defaultShakeTh;

    Description11 = defaultDescription;
    BumpsTh11 = defaultBumpsTh;
    ShakeTh11 = defaultShakeTh;
    BumpsThmedium11 = defaultBumpsTh;
    shakeThmedium11 = defaultShakeTh;
    bumpsThhard11 = defaultBumpsTh;
    shakeThhard11 = defaultShakeTh;

    Description12 = defaultDescription;
    BumpsTh12 = defaultBumpsTh;
    ShakeTh12 = defaultShakeTh;
    BumpsThmedium12 = defaultBumpsTh;
    shakeThmedium12 = defaultShakeTh;
    bumpsThhard12 = defaultBumpsTh;
    shakeThhard12 = defaultShakeTh;

    Description13 = defaultDescription;
    BumpsTh13 = defaultBumpsTh;
    ShakeTh13 = defaultShakeTh;
    BumpsThmedium13 = defaultBumpsTh;
    shakeThmedium13 = defaultShakeTh;
    bumpsThhard13 = defaultBumpsTh;
    shakeThhard13 = defaultShakeTh;

    Description14 = defaultDescription;
    BumpsTh14 = defaultBumpsTh;
    ShakeTh14 = defaultShakeTh;
    BumpsThmedium14 = defaultBumpsTh;
    shakeThmedium14 = defaultShakeTh;
    bumpsThhard14 = defaultBumpsTh;
    shakeThhard14 = defaultShakeTh;

    Description15 = defaultDescription;
    BumpsTh15 = defaultBumpsTh;
    ShakeTh15 = defaultShakeTh;
    BumpsThmedium15 = defaultBumpsTh;
    shakeThmedium15 = defaultShakeTh;
    bumpsThhard15 = defaultBumpsTh;
    shakeThhard15 = defaultShakeTh;

    Description16 = defaultDescription;
    BumpsTh16 = defaultBumpsTh;
    ShakeTh16 = defaultShakeTh;
    BumpsThmedium16 = defaultBumpsTh;
    shakeThmedium16 = defaultShakeTh;
    bumpsThhard16 = defaultBumpsTh;
    shakeThhard16 = defaultShakeTh;

    Description17 = defaultDescription;
    BumpsTh17 = defaultBumpsTh;
    ShakeTh17 = defaultShakeTh;
    BumpsThmedium17 = defaultBumpsTh;
    shakeThmedium17 = defaultShakeTh;
    bumpsThhard17 = defaultBumpsTh;
    shakeThhard17 = defaultShakeTh;

    Description18 = defaultDescription;
    BumpsTh18 = defaultBumpsTh;
    ShakeTh18 = defaultShakeTh;
    BumpsThmedium18 = defaultBumpsTh;
    shakeThmedium18 = defaultShakeTh;
    bumpsThhard18 = defaultBumpsTh;
    shakeThhard18 = defaultShakeTh;

    Description19 = defaultDescription;
    BumpsTh19 = defaultBumpsTh;
    ShakeTh19 = defaultShakeTh;
    BumpsThmedium19 = defaultBumpsTh;
    shakeThmedium19 = defaultShakeTh;
    bumpsThhard19 = defaultBumpsTh;
    shakeThhard19 = defaultShakeTh;

    Description20 = defaultDescription;
    BumpsTh20 = defaultBumpsTh;
    ShakeTh20 = defaultShakeTh;
    BumpsThmedium20 = defaultBumpsTh;
    ShakeThmedium20 = defaultShakeTh;
    BumpsThhard20 = defaultBumpsTh;
    ShakeThhard20 = defaultShakeTh;

    Description21 = defaultDescription;
    BumpsTh21 = defaultBumpsTh;
    ShakeTh21 = defaultShakeTh;
    BumpsThmedium21 = defaultBumpsTh;
    ShakeThmedium21 = defaultShakeTh;
    BumpsThhard21 = defaultBumpsTh;
    ShakeThhard21 = defaultShakeTh;

    Description22 = defaultDescription;
    BumpsTh22 = defaultBumpsTh;
    ShakeTh22 = defaultShakeTh;
    BumpsThmedium22 = defaultBumpsTh;
    ShakeThmedium22 = defaultShakeTh;
    BumpsThhard22 = defaultBumpsTh;
    ShakeThhard22 = defaultShakeTh;

    Description23 = defaultDescription;
    BumpsTh23 = defaultBumpsTh;
    ShakeTh23 = defaultShakeTh;
    BumpsThmedium23 = defaultBumpsTh;
    ShakeThmedium23 = defaultShakeTh;
    BumpsThhard23 = defaultBumpsTh;
    ShakeThhard23 = defaultShakeTh;

    Description24 = defaultDescription;
    BumpsTh24 = defaultBumpsTh;
    ShakeTh24 = defaultShakeTh;
    BumpsThmedium24 = defaultBumpsTh;
    ShakeThmedium24 = defaultShakeTh;
    BumpsThhard24 = defaultBumpsTh;
    ShakeThhard24 = defaultShakeTh;

    Description25 = defaultDescription;
    BumpsTh25 = defaultBumpsTh;
    ShakeTh25 = defaultShakeTh;
    BumpsThmedium25 = defaultBumpsTh;
    ShakeThmedium25 = defaultShakeTh;
    BumpsThhard25 = defaultBumpsTh;
    ShakeThhard25 = defaultShakeTh;

    Description26 = defaultDescription;
    BumpsTh26 = defaultBumpsTh;
    ShakeTh26 = defaultShakeTh;
    BumpsThmedium26 = defaultBumpsTh;
    ShakeThmedium26 = defaultShakeTh;
    BumpsThhard26 = defaultBumpsTh;
    ShakeThhard26 = defaultShakeTh;

    Description27 = defaultDescription;
    BumpsTh27 = defaultBumpsTh;
    ShakeTh27 = defaultShakeTh;
    BumpsThmedium27 = defaultBumpsTh;
    ShakeThmedium27 = defaultShakeTh;
    BumpsThhard27 = defaultBumpsTh;
    ShakeThhard27 = defaultShakeTh;

    Description28 = defaultDescription;
    BumpsTh28 = defaultBumpsTh;
    ShakeTh28 = defaultShakeTh;
    BumpsThmedium28 = defaultBumpsTh;
    ShakeThmedium28 = defaultShakeTh;
    BumpsThhard28 = defaultBumpsTh;
    ShakeThhard28 = defaultShakeTh;

    Description29 = defaultDescription;
    BumpsTh29 = defaultBumpsTh;
    ShakeTh29 = defaultShakeTh;
    BumpsThmedium29 = defaultBumpsTh;
    ShakeThmedium29 = defaultShakeTh;
    BumpsThhard29 = defaultBumpsTh;
    ShakeThhard29 = defaultShakeTh;

    Description30 = defaultDescription;
    BumpsTh30 = defaultBumpsTh;
    ShakeTh30 = defaultShakeTh;
    BumpsThmedium30 = defaultBumpsTh;
    ShakeThmedium30 = defaultShakeTh;
    BumpsThhard30 = defaultBumpsTh;
    ShakeThhard30 = defaultShakeTh;

    Description31 = defaultDescription;
    BumpsTh31 = defaultBumpsTh;
    ShakeTh31 = defaultShakeTh;
    BumpsThmedium31 = defaultBumpsTh;
    ShakeThmedium31 = defaultShakeTh;
    BumpsThhard31 = defaultBumpsTh;
    ShakeThhard31 = defaultShakeTh;

    Description32 = defaultDescription;
    BumpsTh32 = defaultBumpsTh;
    ShakeTh32 = defaultShakeTh;
    BumpsThmedium32 = defaultBumpsTh;
    ShakeThmedium32 = defaultShakeTh;
    BumpsThhard32 = defaultBumpsTh;
    ShakeThhard32 = defaultShakeTh;
    /********************************/

    /********************************
     * riempie i campi
     ********************************/
    fillEditFields();
    /********************************/

    /*******************************************
     * salva i valori nel file _ToolOptions.3dc
     *******************************************/
    saveToolOptions();
    /*******************************************/

    /*******************************************
     * crea il file di log
     *******************************************/
    createLogFile_2("DEFAULT_SAVE   ");
    /*******************************************/

}


void ToolOptions::on_pB_SaveOpt_clicked()
{
    /*******************************************
     * salva i valori nel file _ToolOptions.3dc
     *******************************************/
    saveToolOptions();
    /*******************************************/

    /*******************************************
     * crea il file di log
     *******************************************/
    createLogFile_2("PERMANENT_SAVE ");
    /*******************************************/

}


void ToolOptions::fillEditFields(){

    /*****************************************************************
     * riempie gli edit fields relativi al tool selezionato
     *****************************************************************/
    switch (toolNum)
    {
    case 1:
        ui->tE_toolDescription->setText(Description1);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh1));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh1));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium1));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium1));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard1));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard1));
        }
        break;
    case 2:
        ui->tE_toolDescription->setText(Description2);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh2));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh2));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium2));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium2));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard2));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard2));
        }
        break;
    case 3:
        ui->tE_toolDescription->setText(Description3);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh3));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh3));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium3));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium3));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard3));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard3));
        }
        break;
    case 4:
        ui->tE_toolDescription->setText(Description4);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh4));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh4));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium4));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium4));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard4));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard4));
        }
        break;
    case 5:
        ui->tE_toolDescription->setText(Description5);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh5));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh5));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium5));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium5));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard5));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard5));
        }
        break;
    case 6:
        ui->tE_toolDescription->setText(Description6);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh6));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh6));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium6));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium6));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard6));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard6));
        }
        break;
    case 7:
        ui->tE_toolDescription->setText(Description7);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh7));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh7));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium7));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium7));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard7));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard7));
        }
        break;
    case 8:
        ui->tE_toolDescription->setText(Description8);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh8));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh8));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium8));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium8));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard8));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard8));
        }
        break;
    case 9:
        ui->tE_toolDescription->setText(Description9);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh9));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh9));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium9));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium9));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard9));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard9));
        }
        break;
    case 10:
        ui->tE_toolDescription->setText(Description10);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh10));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh10));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium10));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium10));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard10));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard10));
        }
        break;
    case 11:
        ui->tE_toolDescription->setText(Description11);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh11));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh11));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium11));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium11));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard11));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard11));
        }
        break;
    case 12:
        ui->tE_toolDescription->setText(Description12);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh12));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh12));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium12));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium12));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard12));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard12));
        }
        break;
    case 13:
        ui->tE_toolDescription->setText(Description13);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh13));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh13));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium13));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium13));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard13));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard13));
        }
        break;
    case 14:
        ui->tE_toolDescription->setText(Description14);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh14));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh14));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium14));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium14));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard14));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard14));
        }
        break;
    case 15:
        ui->tE_toolDescription->setText(Description15);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh15));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh15));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium15));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium15));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard15));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard15));
        }
        break;
    case 16:
        ui->tE_toolDescription->setText(Description16);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh16));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh16));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium16));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium16));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard16));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard16));
        }
        break;
    case 17:
        ui->tE_toolDescription->setText(Description17);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh17));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh17));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium17));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium17));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard17));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard17));
        }
        break;
    case 18:
        ui->tE_toolDescription->setText(Description18);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh18));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh18));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium18));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium18));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard18));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard18));
        }
        break;
    case 19:
        ui->tE_toolDescription->setText(Description19);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh19));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh19));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium19));
            ui->lE_toolShakeTh->setText(QString::number(shakeThmedium19));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(bumpsThhard19));
            ui->lE_toolShakeTh->setText(QString::number(shakeThhard19));
        }
        break;
    case 20:
        ui->tE_toolDescription->setText(Description20);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh20));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh20));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium20));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium20));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard20));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard20));
        }
        break;
    case 21:
        ui->tE_toolDescription->setText(Description21);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh21));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh21));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium21));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium21));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard21));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard21));
        }
        break;
    case 22:
        ui->tE_toolDescription->setText(Description22);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh22));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh22));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium22));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium22));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard22));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard22));
        }
        break;
    case 23:
        ui->tE_toolDescription->setText(Description23);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh23));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh23));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium23));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium23));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard23));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard23));
        }
        break;
    case 24:
        ui->tE_toolDescription->setText(Description24);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh24));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh24));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium24));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium24));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard24));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard24));
        }
        break;
    case 25:
        ui->tE_toolDescription->setText(Description25);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh25));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh25));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium25));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium25));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard25));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard25));
        }
        break;
    case 26:
        ui->tE_toolDescription->setText(Description26);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh26));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh26));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium26));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium26));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard26));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard26));
        }
        break;
    case 27:
        ui->tE_toolDescription->setText(Description27);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh27));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh27));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium27));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium27));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard27));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard27));
        }
        break;
    case 28:
        ui->tE_toolDescription->setText(Description28);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh28));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh28));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium28));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium28));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard28));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard28));
        }
        break;
    case 29:
        ui->tE_toolDescription->setText(Description29);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh29));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh29));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium29));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium29));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard29));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard29));
        }
        break;
    case 30:
        ui->tE_toolDescription->setText(Description30);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh30));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh30));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium30));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium30));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard30));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard30));
        }
        break;
    case 31:
        ui->tE_toolDescription->setText(Description31);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh31));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh31));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium31));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium31));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard31));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard31));
        }
        break;
    case 32:
        ui->tE_toolDescription->setText(Description32);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh32));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh32));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium32));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium32));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard32));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard32));
        }
        break;

    default:
        ui->tE_toolDescription->setText(Description1);
        if(MaterialType=="Soft"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsTh1));
            ui->lE_toolShakeTh->setText(QString::number(ShakeTh1));
        } else if(MaterialType=="Medium"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThmedium1));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThmedium1));
        } else if(MaterialType=="Hard"){
            ui->lE_toolBumpTh->setText(QString::number(BumpsThhard1));
            ui->lE_toolShakeTh->setText(QString::number(ShakeThhard1));
        }
        break;
    }
    /*****************************************************************/

}


void ToolOptions::saveToolOptions(){

    /*******************************************************************************
     * Aggiorna il file _ToolOptions.3dc
     *******************************************************************************/
    QFile outFile("/home/fisitron/IND4p0/ToolOptions/_ToolOptions.3dc"); //QFile outFile("_ToolOptions.3dc");
    outFile.remove();
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);


    QString txt;

    txt=Description1;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh1);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh1);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium1);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium1);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard1);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard1);
    ts<<txt<<Qt::endl;

    txt=Description2;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh2);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh2);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium2);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium2);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard2);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard2);
    ts<<txt<<Qt::endl;

    txt=Description3;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh3);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh3);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium3);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium3);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard3);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard3);
    ts<<txt<<Qt::endl;

    txt=Description4;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh4);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh4);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium4);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium4);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard4);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard4);
    ts<<txt<<Qt::endl;

    txt=Description5;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh5);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh5);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium5);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium5);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard5);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard5);
    ts<<txt<<Qt::endl;

    txt=Description6;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh6);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh6);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium6);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium6);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard6);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard6);
    ts<<txt<<Qt::endl;

    txt=Description7;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh7);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh7);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium7);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium7);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard7);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard7);
    ts<<txt<<Qt::endl;

    txt=Description8;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh8);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh8);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium8);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium8);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard8);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard8);
    ts<<txt<<Qt::endl;

    txt=Description9;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh9);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh9);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium9);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium9);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard9);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard9);
    ts<<txt<<Qt::endl;

    txt=Description10;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh10);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh10);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium10);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium10);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard10);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard10);
    ts<<txt<<Qt::endl;

    txt=Description11;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh11);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh11);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium11);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium11);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard11);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard11);
    ts<<txt<<Qt::endl;

    txt=Description12;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh12);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh12);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium12);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium12);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard12);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard12);
    ts<<txt<<Qt::endl;

    txt=Description13;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh13);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh13);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium13);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium13);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard13);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard13);
    ts<<txt<<Qt::endl;

    txt=Description14;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh14);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh14);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium14);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium14);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard14);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard14);
    ts<<txt<<Qt::endl;

    txt=Description15;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh15);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh15);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium15);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium15);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard15);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard15);
    ts<<txt<<Qt::endl;

    txt=Description16;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh16);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh16);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium16);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium16);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard16);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard16);
    ts<<txt<<Qt::endl;

    txt=Description17;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh17);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh17);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium17);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium17);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard17);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard17);
    ts<<txt<<Qt::endl;

    txt=Description18;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh18);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh18);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium18);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium18);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard18);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard18);
    ts<<txt<<Qt::endl;

    txt=Description19;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh19);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh19);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium19);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium19);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard19);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard19);
    ts<<txt<<Qt::endl;

    txt=Description20;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh20);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh20);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium20);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium20);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard20);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard20);
    ts<<txt<<Qt::endl;

    txt=Description21;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh21);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh21);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium21);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium21);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard21);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard21);
    ts<<txt<<Qt::endl;

    txt=Description22;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh22);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh22);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium22);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium22);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard22);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard22);
    ts<<txt<<Qt::endl;

    txt=Description23;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh23);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh23);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium23);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium23);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard23);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard23);
    ts<<txt<<Qt::endl;

    txt=Description24;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh24);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh24);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium24);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium24);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard24);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard24);
    ts<<txt<<Qt::endl;

    txt=Description25;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh25);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh25);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium25);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium25);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard25);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard25);
    ts<<txt<<Qt::endl;

    txt=Description26;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh26);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh26);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium26);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium26);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard26);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard26);
    ts<<txt<<Qt::endl;

    txt=Description27;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh27);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh27);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium27);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium27);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard27);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard27);
    ts<<txt<<Qt::endl;

    txt=Description28;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh28);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh28);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium28);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium28);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard28);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard28);
    ts<<txt<<Qt::endl;

    txt=Description29;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh29);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh29);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium29);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium29);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard29);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard29);
    ts<<txt<<Qt::endl;

    txt=Description30;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh30);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh30);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium30);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium30);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard30);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard30);
    ts<<txt<<Qt::endl;

    txt=Description31;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh31);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh31);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium31);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium31);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard31);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard31);
    ts<<txt<<Qt::endl;

    txt=Description32;
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsTh32);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeTh32);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThmedium32);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThmedium32);
    ts<<txt<<Qt::endl;
    txt=QString::number(BumpsThhard32);
    ts<<txt<<Qt::endl;
    txt=QString::number(ShakeThhard32);
    ts<<txt<<Qt::endl;

    ts<<Qt::flush;


    outFile.close();
    /********************************************************************************/

}


void ToolOptions::on_cB_toolSelected_currentIndexChanged(int index)
{
    /*********************************
     * individua il tool selezionato
     *********************************/
    toolNum = index+1;
    /*********************************/

    /********************************
     * riempie i campi
     ********************************/
    fillEditFields();
    /********************************/
}


void ToolOptions::on_lE_toolBumpTh_editingFinished()
{
    /*****************************************************************
     * aggiorna la soglia degli urti relativa al tool selezionato
     *****************************************************************/
    switch (toolNum)
    {
    case 1:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh1 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium1 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard1 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh1 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium1 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard1 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 2:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh2 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium2 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard2 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh2 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium2 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard2 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 3:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh3 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium3 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard3 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh3 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium3 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard3 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 4:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh4 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium4 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard4 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh4 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium4 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard4 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 5:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh5 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium5 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard5 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh5 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium5 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard5 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 6:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh6 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium6 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard6 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh6 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium6 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard6 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 7:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh7 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium7 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard7 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh7 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium7 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard7 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 8:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh8 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium8 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard8 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh8 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium8 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard8 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 9:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh9 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium9 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard9 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh9 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium9 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard9 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 10:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh10 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium10 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard10 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh10 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium10 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard10 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 11:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh11 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium11 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard11 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh11 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium11 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard11 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 12:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh12 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium12 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard12 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh12 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium12 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard12 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 13:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh13 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium13 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard13 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh13 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium13 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard13 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 14:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh14 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium14 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard14 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh14 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium14 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard14 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 15:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh15 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium15 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard15 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh15 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium15 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard15 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 16:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh16 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium16 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard16 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh16 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium16 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard16 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 17:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh17 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium17 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard17 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh17 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium17 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard17 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 18:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh18 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium18 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard18 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh18 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium18 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard18 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 19:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh19 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium19 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                bumpsThhard19 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh19 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium19 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                bumpsThhard19 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 20:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh20 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium20 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard20 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh20 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium20 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard20 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 21:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh21 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium21 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard21 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh21 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium21 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard21 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 22:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh22 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium22 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard22 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh22 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium22 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard22 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 23:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh23 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium23 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard23 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh23 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium23 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard23 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 24:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh24 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium24 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard24 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh24 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium24 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard24 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 25:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh25 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium25 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard25 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh25 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium25 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard25 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 26:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh26 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium26 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard26 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh26 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium26 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard26 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 27:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh27 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium27 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard27 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh27 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium27 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard27 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 28:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh28 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium28 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard28 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh28 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium28 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard28 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 29:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh29 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium29 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard29 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh29 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium29 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard29 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 30:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh30 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium30 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard30 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh30 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium30 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard30 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 31:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh31 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium31 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard31 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh31 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium31 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard31 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    case 32:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh32 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium32 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard32 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh32 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium32 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard32 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;

    default:
        if( ui->lE_toolBumpTh->text().isEmpty() || ui->lE_toolBumpTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                BumpsTh1 = defaultBumpsTh;
            }
            if(MaterialType=="Medium"){
                BumpsThmedium1 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                BumpsThhard1 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                BumpsTh1 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                BumpsThmedium1 = ui->lE_toolBumpTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                BumpsThhard1 = ui->lE_toolBumpTh->text().toDouble();
            }
        }
        break;
    }
    /*****************************************************************/

}


void ToolOptions::on_lE_toolShakeTh_editingFinished()
{
    /***************************************************************************
     * aggiorna la soglia delle vibrazioni relativa al tool selezionato
     ***************************************************************************/
    switch (toolNum)
    {
    case 1:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh1 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium1 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard1 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh1 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium1 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard1 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 2:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh2 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium2 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard2 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh2 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium2 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard2 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 3:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh3 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium3 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard3 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh3 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium3 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard3 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 4:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh4 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium4 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard4 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh4 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium4 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard4 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 5:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh5 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium5 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard5 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh5 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium5 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard5 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 6:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh6 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium6 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard6 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh6 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium6 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard6 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 7:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh7 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium7 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard7 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh7 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium7 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard7 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 8:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh8 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium8 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard8 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh8 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium8 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard8 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 9:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh9 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium9 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard9 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh9 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium9 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard9 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 10:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh10 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium10 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard10 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh10 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium10 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard10 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 11:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh11 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium11 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard11 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh11 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium11 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard11 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 12:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh12 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium12 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard12 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh12 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium12 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard12 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 13:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh13 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium13 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard13 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh13 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium13 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard13 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 14:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh14 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium14 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard14 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh14 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium14 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard14 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 15:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh15 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium15 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard15 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh15 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium15 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard15 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 16:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh16 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium16 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard16 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh16 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium16 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard16 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 17:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh17 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium17 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard17 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh17 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium17 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard17 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 18:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh18 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium18 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard18 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh18 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium18 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard18 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 19:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh19 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                shakeThmedium19 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                shakeThhard19 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh19 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                shakeThmedium19 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                shakeThhard19 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 20:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh20 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium20 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard20 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh20 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium20 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard20 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 21:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh21 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium21 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard21 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh21 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium21 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard21 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 22:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh22 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium22 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard22 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh22 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium22 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard22 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 23:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh23 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium23 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard23 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh23 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium23 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard23 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 24:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh24 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium24 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard24 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh24 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium24 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard24 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 25:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh25 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium25 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard25 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh25 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium25 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard25 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 26:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh26 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium26 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard26 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh26 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium26 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard26 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 27:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh27 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium27 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard27 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh27 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium27 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard27 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 28:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh28 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium28 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard28 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh28 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium28 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard28 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 29:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh29 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium29 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard29 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh29 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium29 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard29 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 30:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh30 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium30 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard30 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh30 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium30 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard30 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 31:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh31 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium31 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard31 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh31 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium31 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard31 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    case 32:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh32 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium32 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard32 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh32 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium32 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard32 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;

    default:
        if(ui->lE_toolShakeTh->text().isEmpty() || ui->lE_toolShakeTh->text().toDouble()==0 ){
            if(MaterialType=="Soft"){
                ShakeTh1 = defaultShakeTh;
            }
            if(MaterialType=="Medium"){
                ShakeThmedium1 = defaultBumpsTh;
            }
            if(MaterialType=="Hard"){
                ShakeThhard1 = defaultBumpsTh;
            }
        } else {
            if(MaterialType=="Soft"){
                ShakeTh1 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Medium"){
                ShakeThmedium1 = ui->lE_toolShakeTh->text().toDouble();
            }
            if(MaterialType=="Hard"){
                ShakeThhard1 = ui->lE_toolShakeTh->text().toDouble();
            }
        }
        break;
    }
    /***************************************************************************/

}


void ToolOptions::on_tE_toolDescription_textChanged()
{
    /*********************************************************************************************
     * aggiorna la descrizione relativa al tool selezionato
     *********************************************************************************************/
    switch (toolNum)
    {
    case 1:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description1 = defaultDescription;
        Description1 = ui->tE_toolDescription->toPlainText();
        break;
    case 2:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description2 = defaultDescription;
        Description2 = ui->tE_toolDescription->toPlainText();
        break;
    case 3:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description3 = defaultDescription;
        Description3 = ui->tE_toolDescription->toPlainText();
        break;
    case 4:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description4 = defaultDescription;
        Description4 = ui->tE_toolDescription->toPlainText();
        break;
    case 5:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description5 = defaultDescription;
        Description5 = ui->tE_toolDescription->toPlainText();
        break;
    case 6:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description6 = defaultDescription;
        Description6 = ui->tE_toolDescription->toPlainText();
        break;
    case 7:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description7 = defaultDescription;
        Description7 = ui->tE_toolDescription->toPlainText();
        break;
    case 8:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description8 = defaultDescription;
        Description8 = ui->tE_toolDescription->toPlainText();
        break;
    case 9:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description9 = defaultDescription;
        Description9 = ui->tE_toolDescription->toPlainText();
        break;
    case 10:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description10 = defaultDescription;
        Description10 = ui->tE_toolDescription->toPlainText();
        break;
    case 11:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description11 = defaultDescription;
        Description11 = ui->tE_toolDescription->toPlainText();
        break;
    case 12:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description12 = defaultDescription;
        Description12 = ui->tE_toolDescription->toPlainText();
        break;
    case 13:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description13 = defaultDescription;
        Description13 = ui->tE_toolDescription->toPlainText();
        break;
    case 14:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description14 = defaultDescription;
        Description14 = ui->tE_toolDescription->toPlainText();
        break;
    case 15:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description15 = defaultDescription;
        Description15 = ui->tE_toolDescription->toPlainText();
        break;
    case 16:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description16 = defaultDescription;
        Description16 = ui->tE_toolDescription->toPlainText();
        break;
    case 17:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description17 = defaultDescription;
        Description17 = ui->tE_toolDescription->toPlainText();
        break;
    case 18:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description18 = defaultDescription;
        Description18 = ui->tE_toolDescription->toPlainText();
        break;
    case 19:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description19 = defaultDescription;
        Description19 = ui->tE_toolDescription->toPlainText();
        break;
    case 20:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description20 = defaultDescription;
        Description20 = ui->tE_toolDescription->toPlainText();
        break;
    case 21:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description21 = defaultDescription;
        Description21 = ui->tE_toolDescription->toPlainText();
        break;
    case 22:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description22 = defaultDescription;
        Description22 = ui->tE_toolDescription->toPlainText();
        break;
    case 23:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description23 = defaultDescription;
        Description23 = ui->tE_toolDescription->toPlainText();
        break;
    case 24:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description24 = defaultDescription;
        Description24 = ui->tE_toolDescription->toPlainText();
        break;
    case 25:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description25 = defaultDescription;
        Description25 = ui->tE_toolDescription->toPlainText();
        break;
    case 26:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description26 = defaultDescription;
        Description26 = ui->tE_toolDescription->toPlainText();
        break;
    case 27:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description27 = defaultDescription;
        Description27 = ui->tE_toolDescription->toPlainText();
        break;
    case 28:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description28 = defaultDescription;
        Description28 = ui->tE_toolDescription->toPlainText();
        break;
    case 29:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description29 = defaultDescription;
        Description29 = ui->tE_toolDescription->toPlainText();
        break;
    case 30:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description30 = defaultDescription;
        Description30 = ui->tE_toolDescription->toPlainText();
        break;
    case 31:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description31 = defaultDescription;
        Description31 = ui->tE_toolDescription->toPlainText();
        break;
    case 32:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description32 = defaultDescription;
        Description32 = ui->tE_toolDescription->toPlainText();
        break;

    default:
        if(ui->tE_toolDescription->toPlainText().isEmpty())
            Description1 = defaultDescription;
        Description1 = ui->tE_toolDescription->toPlainText();
        break;
    }
    /********************************************************************************************/

}


void ToolOptions::createLogFile_2(QString eventType)
{
    /************************************************************
     * Crea/Aggiorna il file dei log
     ************************************************************/
    /**************************************
     * nome parziale del file
     **************************************/
    QString LogFileName = "_log.txt";
    /**************************************/

    /********************************
     * acquisisce la data corrente
     ********************************/
    QDateTime date;
    /********************************/

    /**************************************************************************
     * Completa il nome del file. ESEMPIO:
     * "/home/fisitron/IND4p0/Logs/20240301_log.txt"
     **************************************************************************/
    LogFileName.prepend(date.currentDateTime().toString("yyyyMMdd"));
    LogFileName.prepend("/home/fisitron/IND4p0/Logs/");
    /**************************************************************************/

    /************************************************************
     * scrive il file di log
     ***********************************************************/
    QString txt;

    txt.append(date.currentDateTime().toString("yyyy/MM/dd-hh:mm:ss")); // txt.prepend(date.currentDateTime().toString());
    txt.append(" - Event:" + eventType);
    txt.append(" - Working Modality: " + WorkingModality);
    txt.append(" - Tool: " + QString::number(toolNum));
    txt.append(" - Material Type: " + MaterialType);
    txt.append(" - Bump Threshold: " + ui->lE_toolBumpTh->text()); //txt.append(" - Bump Threshold: " + QString::number(bumpsTH));
    txt.append(" - Shake Threshold: " + ui->lE_toolShakeTh->text()); //txt.append(" - Shake Threshold: " + QString::number(shakesTH));

    QFile outFile(LogFileName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts<<txt<<Qt::endl<<Qt::flush;
    outFile.close();
    /************************************************************/

}
