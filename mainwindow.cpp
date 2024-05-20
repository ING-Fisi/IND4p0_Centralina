#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "protocollo.h"
#include "tooloptions.h"
#include "hiddenbumpdialog.h"
#include <QTimer>
#include <cmath>
#include <QFileInfo>
#include <QDirIterator>
#include <QThread>

/***************************/
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#include <stdio.h>
/***************************/


int onOff = 0;

#define MAX_BUFFER_LENGHT 8192
int32_t index_buffer = 0;
char receive_buffer[MAX_BUFFER_LENGHT];
int size_packet = 0;

static bool crc_tab16_init = false;
static uint16_t crc_tab16[256];
#define		CRC_START_16		0x0000
#define		CRC_POLY_16		0xA001


/*****************************************
 * soglia nascosta (protetta da password)
 * degli urti
 *****************************************/
double hiddenBumpTh=0;
/*****************************************/

/***********************************
 * soglia e contatore di urti
 ***********************************/
double bumpsTH=0;
double bumpsEventCounter=0;
double bumpSignalX=0;
double bumpSignalY=0;
double bumpSignalZ=0;
/***********************************/

/*****************************************************
 * soglia, sampling time e contatore di vibrazioni
 *****************************************************/
double shakesTH=0;
long int shakesSamplingTime=0;
double shakesEventCounter=0;
double shakesEventCounterX=0;
double shakesEventCounterY=0;
double shakesEventCounterZ=0;
int acceptableShakes=1;
/*****************************************************/

/********************************************************
 * soglia automatica vibrazioni
 * percentuale per il calcolo della soglia automatica
 * offset per il calcolo delle soglie automatiche
 ********************************************************/
double automaticShakeTh = 0;
double shakeThPercent = 250;
double shakeThOffset = 0;
/********************************************************/

/********************************
 * tool description
 ********************************/
QString toolDescription;
/********************************/

/*********************************
 * modalità di lavoro; può essere
 * MANUAL o AUTOMATIC
 *********************************/
QString workingModality;
/*********************************/

/*********************************
 * tipo di materiale; può essere
 * Soft, Medium o Hard
 *********************************/
QString materialType;
/*********************************/

/*********************************
 * tipo di materiale; può essere
 * Soft, Medium o Hard
 *********************************/
QString password;
/*********************************/

/****************************************
 * Variabili salvate in _ToolOptions.3dc
 ****************************************/
QString toolDescription1;
double bumpsTh1=0;
double shakeTh1=0;
double bumpsThmedium1=0;
double shakeThmedium1=0;
double bumpsThhard1=0;
double shakeThhard1=0;

QString toolDescription2;
double bumpsTh2=0;
double shakeTh2=0;
double bumpsThmedium2=0;
double shakeThmedium2=0;
double bumpsThhard2=0;
double shakeThhard2=0;

QString toolDescription3;
double bumpsTh3=0;
double shakeTh3=0;
double bumpsThmedium3=0;
double shakeThmedium3=0;
double bumpsThhard3=0;
double shakeThhard3=0;

QString toolDescription4;
double bumpsTh4=0;
double shakeTh4=0;
double bumpsThmedium4=0;
double shakeThmedium4=0;
double bumpsThhard4=0;
double shakeThhard4=0;

QString toolDescription5;
double bumpsTh5=0;
double shakeTh5=0;
double bumpsThmedium5=0;
double shakeThmedium5=0;
double bumpsThhard5=0;
double shakeThhard5=0;

QString toolDescription6;
double bumpsTh6=0;
double shakeTh6=0;
double bumpsThmedium6=0;
double shakeThmedium6=0;
double bumpsThhard6=0;
double shakeThhard6=0;

QString toolDescription7;
double bumpsTh7=0;
double shakeTh7=0;
double bumpsThmedium7=0;
double shakeThmedium7=0;
double bumpsThhard7=0;
double shakeThhard7=0;

QString toolDescription8;
double bumpsTh8=0;
double shakeTh8=0;
double bumpsThmedium8=0;
double shakeThmedium8=0;
double bumpsThhard8=0;
double shakeThhard8=0;

QString toolDescription9;
double bumpsTh9=0;
double shakeTh9=0;
double bumpsThmedium9=0;
double shakeThmedium9=0;
double bumpsThhard9=0;
double shakeThhard9=0;

QString toolDescription10;
double bumpsTh10=0;
double shakeTh10=0;
double bumpsThmedium10=0;
double shakeThmedium10=0;
double bumpsThhard10=0;
double shakeThhard10=0;

QString toolDescription11;
double bumpsTh11=0;
double shakeTh11=0;
double bumpsThmedium11=0;
double shakeThmedium11=0;
double bumpsThhard11=0;
double shakeThhard11=0;

QString toolDescription12;
double bumpsTh12=0;
double shakeTh12=0;
double bumpsThmedium12=0;
double shakeThmedium12=0;
double bumpsThhard12=0;
double shakeThhard12=0;

QString toolDescription13;
double bumpsTh13=0;
double shakeTh13=0;
double bumpsThmedium13=0;
double shakeThmedium13=0;
double bumpsThhard13=0;
double shakeThhard13=0;

QString toolDescription14;
double bumpsTh14=0;
double shakeTh14=0;
double bumpsThmedium14=0;
double shakeThmedium14=0;
double bumpsThhard14=0;
double shakeThhard14=0;

QString toolDescription15;
double bumpsTh15=0;
double shakeTh15=0;
double bumpsThmedium15=0;
double shakeThmedium15=0;
double bumpsThhard15=0;
double shakeThhard15=0;

QString toolDescription16;
double bumpsTh16=0;
double shakeTh16=0;
double bumpsThmedium16=0;
double shakeThmedium16=0;
double bumpsThhard16=0;
double shakeThhard16=0;

QString toolDescription17;
double bumpsTh17=0;
double shakeTh17=0;
double bumpsThmedium17=0;
double shakeThmedium17=0;
double bumpsThhard17=0;
double shakeThhard17=0;

QString toolDescription18;
double bumpsTh18=0;
double shakeTh18=0;
double bumpsThmedium18=0;
double shakeThmedium18=0;
double bumpsThhard18=0;
double shakeThhard18=0;

QString toolDescription19;
double bumpsTh19=0;
double shakeTh19=0;
double bumpsThmedium19=0;
double shakeThmedium19=0;
double bumpsThhard19=0;
double shakeThhard19=0;

QString toolDescription20;
double bumpsTh20=0;
double shakeTh20=0;
double bumpsThmedium20=0;
double shakeThmedium20=0;
double bumpsThhard20=0;
double shakeThhard20=0;

QString toolDescription21;
double bumpsTh21=0;
double shakeTh21=0;
double bumpsThmedium21=0;
double shakeThmedium21=0;
double bumpsThhard21=0;
double shakeThhard21=0;

QString toolDescription22;
double bumpsTh22=0;
double shakeTh22=0;
double bumpsThmedium22=0;
double shakeThmedium22=0;
double bumpsThhard22=0;
double shakeThhard22=0;

QString toolDescription23;
double bumpsTh23=0;
double shakeTh23=0;
double bumpsThmedium23=0;
double shakeThmedium23=0;
double bumpsThhard23=0;
double shakeThhard23=0;

QString toolDescription24;
double bumpsTh24=0;
double shakeTh24=0;
double bumpsThmedium24=0;
double shakeThmedium24=0;
double bumpsThhard24=0;
double shakeThhard24=0;

QString toolDescription25;
double bumpsTh25=0;
double shakeTh25=0;
double bumpsThmedium25=0;
double shakeThmedium25=0;
double bumpsThhard25=0;
double shakeThhard25=0;

QString toolDescription26;
double bumpsTh26=0;
double shakeTh26=0;
double bumpsThmedium26=0;
double shakeThmedium26=0;
double bumpsThhard26=0;
double shakeThhard26=0;

QString toolDescription27;
double bumpsTh27=0;
double shakeTh27=0;
double bumpsThmedium27=0;
double shakeThmedium27=0;
double bumpsThhard27=0;
double shakeThhard27=0;

QString toolDescription28;
double bumpsTh28=0;
double shakeTh28=0;
double bumpsThmedium28=0;
double shakeThmedium28=0;
double bumpsThhard28=0;
double shakeThhard28=0;

QString toolDescription29;
double bumpsTh29=0;
double shakeTh29=0;
double bumpsThmedium29=0;
double shakeThmedium29=0;
double bumpsThhard29=0;
double shakeThhard29=0;

QString toolDescription30;
double bumpsTh30=0;
double shakeTh30=0;
double bumpsThmedium30=0;
double shakeThmedium30=0;
double bumpsThhard30=0;
double shakeThhard30=0;

QString toolDescription31;
double bumpsTh31=0;
double shakeTh31=0;
double bumpsThmedium31=0;
double shakeThmedium31=0;
double bumpsThhard31=0;
double shakeThhard31=0;

QString toolDescription32;
double bumpsTh32=0;
double shakeTh32=0;
double bumpsThmedium32=0;
double shakeThmedium32=0;
double bumpsThhard32=0;
double shakeThhard32=0;
/****************************************/

/*********************
 * tool selezionato
 *********************/
int tool = 0;
/*********************/

/*******************************************
 * booleano che indica se la modifica
 * del comboBox_toolSelection è la prima.
 * Serve per bypassare il settaggio del
 * sensore quando non è ancora stabilita
 * la connessione
 *******************************************/
bool firstChange=true;
/*******************************************/

/*******************************
 * booleano per funzione muting
 *******************************/
bool toolChangingFlag = false;
/*******************************/

/*************************************************************
 * Timer per il monitoraggio periodico delle vibrazioni
 *************************************************************/
QTimer *shakesMonitorTimer = new QTimer;
/*************************************************************/

/*********************************************
 * Periodo in ms del timer shakesMonitorTimer
 *********************************************/
int shakesMonitorTimerPeriod = 50;
/*********************************************/

/*********************************************
 * Variabili che  intervengono nella funzione
 * shakesMonitorFunction legata al timer
 * shakesMonitorTimer
 *********************************************/
int shakesMonitorFunctionCounter = 0;
int shakesMonitorFunctionCounterLimit = 0;
bool rawDataEnableFlag=false;
/*********************************************/

/*******************************************
 * booleano che indica se è in corso
 * l'acquisizione dei raw data per il
 * calcolo automatico delle soglie
 *******************************************/
bool acqRunningFlag=false;
/*******************************************/

/************************************
 * variabili d'appoggio per il
 * calcolo automatico delle soglie
 ************************************/
int sampleIndex = 0;
double SumXsamples = 0;
double SumYsamples = 0;
double SumZsamples = 0;
/************************************/

/************************************
 * numero di campioni per il
 * calcolo automatico delle soglie
 ************************************/
double SAMPLES_NUM = 100;
/************************************/

/*************************************************************
 * Timer per il filtraggio dei "rimbalzi" da urto
 *************************************************************/
QTimer *bumpTimer = new QTimer;
/*************************************************************/

/******************************************
 * flag che indica che è avvenuto un urto
 ******************************************/
bool bumpFlag = false;
/******************************************/


/****************************************************
 * flag per selezionare la modalità di settaggio.
 * Se settingsFileFlag=true il settaggio avviene
 * attraverso la lettura del file Settings.3dc
 ****************************************************/
bool settingsFileFlag = true;
/****************************************************/


/*****************************************************
 * Nomi parziali dei due file di log
 * I nomi vengono completati in seguito
 * con il prepend della data corrente
 *****************************************************/
QString BumpFileName = "_BumpEventLog.txt";
QString ShakeFileName = "_ShakeEventLog.txt";
/*****************************************************/


/***************************************************************************************
 * funzioni per il calcolo del CRC
 ***************************************************************************************/
static void init_crc16_tab( void ) {

    uint16_t i;
    uint16_t j;
    uint16_t crc;
    uint16_t c;

    for (i=0; i<256; i++) {

        crc = 0;
        c   = i;

        for (j=0; j<8; j++) {

            if ( (crc ^ c) & 0x0001 ) crc = ( crc >> 1 ) ^ CRC_POLY_16;
            else                      crc =   crc >> 1;

            c = c >> 1;
        }

        crc_tab16[i] = crc;
    }

    crc_tab16_init = true;

}  /* init_crc16_tab */

uint16_t crc_16( const unsigned char *input_str, size_t num_bytes ) {

    uint16_t crc;
    const unsigned char *ptr;
    size_t a;

    if ( ! crc_tab16_init ) init_crc16_tab();

    crc = CRC_START_16;
    ptr = input_str;

    if ( ptr != NULL ) for (a=0; a<num_bytes; a++) {

        crc = (crc >> 8) ^ crc_tab16[ (crc ^ (uint16_t) *ptr++) & 0x00FF ];
    }

    return crc;

}  /* crc_16 */
/***************************************************************************************/


/*******************************************************
 * funzione per la lettura del file _ToolOptions.3dc
 *******************************************************/
void readToolOptionFile(void){
    //QFile file("_ToolOptions.3dc");
    QFile file("/home/fisitron/IND4p0/ToolOptions/_ToolOptions.3dc");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);

        toolDescription1 = in.readLine();
        bumpsTh1 = in.readLine().toDouble();
        shakeTh1 = in.readLine().toDouble();
        bumpsThmedium1 = in.readLine().toDouble();
        shakeThmedium1 = in.readLine().toDouble();
        bumpsThhard1 = in.readLine().toDouble();
        shakeThhard1 = in.readLine().toDouble();

        toolDescription2 = in.readLine();
        bumpsTh2 = in.readLine().toDouble();
        shakeTh2 = in.readLine().toDouble();
        bumpsThmedium2 = in.readLine().toDouble();
        shakeThmedium2 = in.readLine().toDouble();
        bumpsThhard2 = in.readLine().toDouble();
        shakeThhard2 = in.readLine().toDouble();

        toolDescription3 = in.readLine();
        bumpsTh3 = in.readLine().toDouble();
        shakeTh3 = in.readLine().toDouble();
        bumpsThmedium3 = in.readLine().toDouble();
        shakeThmedium3 = in.readLine().toDouble();
        bumpsThhard3 = in.readLine().toDouble();
        shakeThhard3 = in.readLine().toDouble();

        toolDescription4 = in.readLine();
        bumpsTh4 = in.readLine().toDouble();
        shakeTh4 = in.readLine().toDouble();
        bumpsThmedium4 = in.readLine().toDouble();
        shakeThmedium4 = in.readLine().toDouble();
        bumpsThhard4 = in.readLine().toDouble();
        shakeThhard4 = in.readLine().toDouble();

        toolDescription5 = in.readLine();
        bumpsTh5 = in.readLine().toDouble();
        shakeTh5 = in.readLine().toDouble();
        bumpsThmedium5 = in.readLine().toDouble();
        shakeThmedium5 = in.readLine().toDouble();
        bumpsThhard5 = in.readLine().toDouble();
        shakeThhard5 = in.readLine().toDouble();

        toolDescription6 = in.readLine();
        bumpsTh6 = in.readLine().toDouble();
        shakeTh6 = in.readLine().toDouble();
        bumpsThmedium6 = in.readLine().toDouble();
        shakeThmedium6 = in.readLine().toDouble();
        bumpsThhard6 = in.readLine().toDouble();
        shakeThhard6 = in.readLine().toDouble();

        toolDescription7 = in.readLine();
        bumpsTh7 = in.readLine().toDouble();
        shakeTh7 = in.readLine().toDouble();
        bumpsThmedium7 = in.readLine().toDouble();
        shakeThmedium7 = in.readLine().toDouble();
        bumpsThhard7 = in.readLine().toDouble();
        shakeThhard7 = in.readLine().toDouble();

        toolDescription8 = in.readLine();
        bumpsTh8 = in.readLine().toDouble();
        shakeTh8 = in.readLine().toDouble();
        bumpsThmedium8 = in.readLine().toDouble();
        shakeThmedium8 = in.readLine().toDouble();
        bumpsThhard8 = in.readLine().toDouble();
        shakeThhard8 = in.readLine().toDouble();

        toolDescription9 = in.readLine();
        bumpsTh9 = in.readLine().toDouble();
        shakeTh9 = in.readLine().toDouble();
        bumpsThmedium9 = in.readLine().toDouble();
        shakeThmedium9 = in.readLine().toDouble();
        bumpsThhard9 = in.readLine().toDouble();
        shakeThhard9 = in.readLine().toDouble();

        toolDescription10 = in.readLine();
        bumpsTh10 = in.readLine().toDouble();
        shakeTh10 = in.readLine().toDouble();
        bumpsThmedium10 = in.readLine().toDouble();
        shakeThmedium10 = in.readLine().toDouble();
        bumpsThhard10 = in.readLine().toDouble();
        shakeThhard10 = in.readLine().toDouble();

        toolDescription11 = in.readLine();
        bumpsTh11 = in.readLine().toDouble();
        shakeTh11 = in.readLine().toDouble();
        bumpsThmedium11 = in.readLine().toDouble();
        shakeThmedium11 = in.readLine().toDouble();
        bumpsThhard11 = in.readLine().toDouble();
        shakeThhard11 = in.readLine().toDouble();

        toolDescription12 = in.readLine();
        bumpsTh12 = in.readLine().toDouble();
        shakeTh12 = in.readLine().toDouble();
        bumpsThmedium12 = in.readLine().toDouble();
        shakeThmedium12 = in.readLine().toDouble();
        bumpsThhard12 = in.readLine().toDouble();
        shakeThhard12 = in.readLine().toDouble();

        toolDescription13 = in.readLine();
        bumpsTh13 = in.readLine().toDouble();
        shakeTh13 = in.readLine().toDouble();
        bumpsThmedium13 = in.readLine().toDouble();
        shakeThmedium13 = in.readLine().toDouble();
        bumpsThhard13 = in.readLine().toDouble();
        shakeThhard13 = in.readLine().toDouble();

        toolDescription14 = in.readLine();
        bumpsTh14 = in.readLine().toDouble();
        shakeTh14 = in.readLine().toDouble();
        bumpsThmedium14 = in.readLine().toDouble();
        shakeThmedium14 = in.readLine().toDouble();
        bumpsThhard14 = in.readLine().toDouble();
        shakeThhard14 = in.readLine().toDouble();

        toolDescription15 = in.readLine();
        bumpsTh15 = in.readLine().toDouble();
        shakeTh15 = in.readLine().toDouble();
        bumpsThmedium15 = in.readLine().toDouble();
        shakeThmedium15 = in.readLine().toDouble();
        bumpsThhard15 = in.readLine().toDouble();
        shakeThhard15 = in.readLine().toDouble();

        toolDescription16 = in.readLine();
        bumpsTh16 = in.readLine().toDouble();
        shakeTh16 = in.readLine().toDouble();
        bumpsThmedium16 = in.readLine().toDouble();
        shakeThmedium16 = in.readLine().toDouble();
        bumpsThhard16 = in.readLine().toDouble();
        shakeThhard16 = in.readLine().toDouble();

        toolDescription17 = in.readLine();
        bumpsTh17 = in.readLine().toDouble();
        shakeTh17 = in.readLine().toDouble();
        bumpsThmedium17 = in.readLine().toDouble();
        shakeThmedium17 = in.readLine().toDouble();
        bumpsThhard17 = in.readLine().toDouble();
        shakeThhard17 = in.readLine().toDouble();

        toolDescription18 = in.readLine();
        bumpsTh18 = in.readLine().toDouble();
        shakeTh18 = in.readLine().toDouble();
        bumpsThmedium18 = in.readLine().toDouble();
        shakeThmedium18 = in.readLine().toDouble();
        bumpsThhard18 = in.readLine().toDouble();
        shakeThhard18 = in.readLine().toDouble();

        toolDescription19 = in.readLine();
        bumpsTh19 = in.readLine().toDouble();
        shakeTh19 = in.readLine().toDouble();
        bumpsThmedium19 = in.readLine().toDouble();
        shakeThmedium19 = in.readLine().toDouble();
        bumpsThhard19 = in.readLine().toDouble();
        shakeThhard19 = in.readLine().toDouble();

        toolDescription20 = in.readLine();
        bumpsTh20 = in.readLine().toDouble();
        shakeTh20 = in.readLine().toDouble();
        bumpsThmedium20 = in.readLine().toDouble();
        shakeThmedium20 = in.readLine().toDouble();
        bumpsThhard20 = in.readLine().toDouble();
        shakeThhard20 = in.readLine().toDouble();

        toolDescription21 = in.readLine();
        bumpsTh21 = in.readLine().toDouble();
        shakeTh21 = in.readLine().toDouble();
        bumpsThmedium21 = in.readLine().toDouble();
        shakeThmedium21 = in.readLine().toDouble();
        bumpsThhard21 = in.readLine().toDouble();
        shakeThhard21 = in.readLine().toDouble();

        toolDescription22 = in.readLine();
        bumpsTh22 = in.readLine().toDouble();
        shakeTh22 = in.readLine().toDouble();
        bumpsThmedium22 = in.readLine().toDouble();
        shakeThmedium22 = in.readLine().toDouble();
        bumpsThhard22 = in.readLine().toDouble();
        shakeThhard22 = in.readLine().toDouble();

        toolDescription23 = in.readLine();
        bumpsTh23 = in.readLine().toDouble();
        shakeTh23 = in.readLine().toDouble();
        bumpsThmedium23 = in.readLine().toDouble();
        shakeThmedium23 = in.readLine().toDouble();
        bumpsThhard23 = in.readLine().toDouble();
        shakeThhard23 = in.readLine().toDouble();

        toolDescription24 = in.readLine();
        bumpsTh24 = in.readLine().toDouble();
        shakeTh24 = in.readLine().toDouble();
        bumpsThmedium24 = in.readLine().toDouble();
        shakeThmedium24 = in.readLine().toDouble();
        bumpsThhard24 = in.readLine().toDouble();
        shakeThhard24 = in.readLine().toDouble();

        toolDescription25 = in.readLine();
        bumpsTh25 = in.readLine().toDouble();
        shakeTh25 = in.readLine().toDouble();
        bumpsThmedium25 = in.readLine().toDouble();
        shakeThmedium25 = in.readLine().toDouble();
        bumpsThhard25 = in.readLine().toDouble();
        shakeThhard25 = in.readLine().toDouble();

        toolDescription26 = in.readLine();
        bumpsTh26 = in.readLine().toDouble();
        shakeTh26 = in.readLine().toDouble();
        bumpsThmedium26 = in.readLine().toDouble();
        shakeThmedium26 = in.readLine().toDouble();
        bumpsThhard26 = in.readLine().toDouble();
        shakeThhard26 = in.readLine().toDouble();

        toolDescription27 = in.readLine();
        bumpsTh27 = in.readLine().toDouble();
        shakeTh27 = in.readLine().toDouble();
        bumpsThmedium27 = in.readLine().toDouble();
        shakeThmedium27 = in.readLine().toDouble();
        bumpsThhard27 = in.readLine().toDouble();
        shakeThhard27 = in.readLine().toDouble();

        toolDescription28 = in.readLine();
        bumpsTh28 = in.readLine().toDouble();
        shakeTh28 = in.readLine().toDouble();
        bumpsThmedium28 = in.readLine().toDouble();
        shakeThmedium28 = in.readLine().toDouble();
        bumpsThhard28 = in.readLine().toDouble();
        shakeThhard28 = in.readLine().toDouble();

        toolDescription29 = in.readLine();
        bumpsTh29 = in.readLine().toDouble();
        shakeTh29 = in.readLine().toDouble();
        bumpsThmedium29 = in.readLine().toDouble();
        shakeThmedium29 = in.readLine().toDouble();
        bumpsThhard29 = in.readLine().toDouble();
        shakeThhard29 = in.readLine().toDouble();

        toolDescription30 = in.readLine();
        bumpsTh30 = in.readLine().toDouble();
        shakeTh30 = in.readLine().toDouble();
        bumpsThmedium30 = in.readLine().toDouble();
        shakeThmedium30 = in.readLine().toDouble();
        bumpsThhard30 = in.readLine().toDouble();
        shakeThhard30 = in.readLine().toDouble();

        toolDescription31 = in.readLine();
        bumpsTh31 = in.readLine().toDouble();
        shakeTh31 = in.readLine().toDouble();
        bumpsThmedium31 = in.readLine().toDouble();
        shakeThmedium31 = in.readLine().toDouble();
        bumpsThhard31 = in.readLine().toDouble();
        shakeThhard31 = in.readLine().toDouble();

        toolDescription32 = in.readLine();
        bumpsTh32 = in.readLine().toDouble();
        shakeTh32 = in.readLine().toDouble();
        bumpsThmedium32 = in.readLine().toDouble();
        shakeThmedium32 = in.readLine().toDouble();
        bumpsThhard32 = in.readLine().toDouble();
        shakeThhard32 = in.readLine().toDouble();

        file.close();
    }
}
/*******************************************************/


/*********************************************************************
 * funzione per l'aggiornamento del file Settings.3dc
 *********************************************************************/
void MainWindow::updateSettingsFile(void){

    //QFile outFile("tmpSettings.3dc");
    QFile outFile("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
    outFile.remove();
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    QString txt;
    txt = name_serialport;
    ts<<txt<<Qt::endl;
    txt = QString::number(tool);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakesSamplingTime);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThOffset);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThPercent);
    ts<<txt<<Qt::endl;
    txt = workingModality;
    ts<<txt<<Qt::endl;
    txt = materialType;
    ts<<txt<<Qt::endl;
    txt = QString::number(hiddenBumpTh);
    ts<<txt<<Qt::endl;
    txt = password;
    ts<<txt<<Qt::endl;
    txt = QString::number(acceptableShakes);
    ts<<txt<<Qt::endl;

    ts<<Qt::flush;
    //ts<<txt<<Qt::endl<<Qt::flush;

    outFile.close();

/********************************************************************************************************************************/
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

/********************************************************************************************************************************/


}
/*********************************************************************/



/********************************************************************************
 * funzione per la lettura del file Settings.3dc
 ********************************************************************************/
void MainWindow::readSettingsFile(void){


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




    //QFile file("tmpSettings.3dc");
    QFile file("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);

        /**********************************
         * legge la prima riga, relativa al
         * nome della porta seriale, e la
         * assegna a name_serialport
         **********************************/
        name_serialport = in.readLine();
        /**********************************/

        /**********************************************************
         * legge la seconda riga, relativa
         * all'ultimo tool utilizzato, e associa a bumpsTH e
         * shakesTH gli opportuni valori
         **********************************************************/
        tool = in.readLine().toInt();

        //ui->comboBox_toolSelection->setCurrentIndex(tool-1);

        /**********************************************************/

        /**********************************************
         * legge la terza riga, relativa al
         * tempo di campionamento delle vibrazioni,
         * e la assegna a shakesSamplingTime
         **********************************************/
        shakesSamplingTime= in.readLine().toDouble();
        /**********************************************/

        /**************************************************************************
         * calcola shakesMonitorFunctionCounterLimit. Si moltiplica per 1000
         * per avere il valore in ms e si divide per 200(ms) che è il valore
         * del periodo con cui viene richiamata la funzione shakesMonitorFunction
         **************************************************************************/
        shakesMonitorFunctionCounterLimit = lround(shakesSamplingTime*1000/shakesMonitorTimerPeriod);
        /**************************************************************************/

        /**********************************************
         * legge la quarta riga, relativa all'offset
         * per il calcolo delle soglie automatiche
         **********************************************/
        shakeThOffset= in.readLine().toDouble();
        /**********************************************/

        /****************************************************
         * legge la quinta riga, relativa alla percentuale
         * per il calcolo delle soglie automatiche
         ****************************************************/
        shakeThPercent= in.readLine().toDouble();
        /****************************************************/

        /*********************************************************
         * legge la sesta riga, relativa alla modalità di lavoro
         *********************************************************/
        workingModality=in.readLine();
        /*********************************************************/

        /*********************************************************
         * legge la settima riga, relativa al tipo di materiale
         *********************************************************/
        materialType=in.readLine();
        /*********************************************************/

        /***********************************************
         * legge l'ottava riga, relativa alla soglia
         * nascosta (protetta da password) degli urti
         ***********************************************/
        hiddenBumpTh=in.readLine().toDouble();
        /***********************************************/

        /**********************************
         * legge la nona riga, relativa
         * alla password
         **********************************/
        password = in.readLine();
        /**********************************/

        /******************************************
         * legge la decima riga, relativa
         * al valore di acceptableShakes
         ******************************************/
        acceptableShakes = in.readLine().toInt();
        /******************************************/

        /*********************************************************
         * assegna le soglie in base al tool e al materiale
         *********************************************************/
        switch (tool)
        {
        case 1:
            toolDescription = toolDescription1;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh1;
                shakesTH =shakeTh1;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium1;
                shakesTH =shakeThmedium1;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard1;
                shakesTH =shakeThhard1;
            } else {
                bumpsTH = bumpsThmedium1;
                shakesTH =shakeThmedium1;
            }
            break;
        case 2:
            toolDescription = toolDescription2;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh2;
                shakesTH =shakeTh2;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium2;
                shakesTH =shakeThmedium2;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard2;
                shakesTH =shakeThhard2;
            } else {
                bumpsTH = bumpsThmedium2;
                shakesTH =shakeThmedium2;
            }
            break;
        case 3:
            toolDescription = toolDescription3;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh3;
                shakesTH =shakeTh3;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium3;
                shakesTH =shakeThmedium3;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard3;
                shakesTH =shakeThhard3;
            } else {
                bumpsTH = bumpsThmedium3;
                shakesTH =shakeThmedium3;
            }
            break;
        case 4:
            toolDescription = toolDescription4;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh4;
                shakesTH =shakeTh4;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium4;
                shakesTH =shakeThmedium4;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard4;
                shakesTH =shakeThhard4;
            } else {
                bumpsTH = bumpsThmedium4;
                shakesTH =shakeThmedium4;
            }
            break;
        case 5:
            toolDescription = toolDescription5;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh5;
                shakesTH =shakeTh5;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium5;
                shakesTH =shakeThmedium5;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard5;
                shakesTH =shakeThhard5;
            } else {
                bumpsTH = bumpsThmedium5;
                shakesTH =shakeThmedium5;
            }
            break;
        case 6:
            toolDescription = toolDescription6;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh6;
                shakesTH =shakeTh6;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium6;
                shakesTH =shakeThmedium6;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard6;
                shakesTH =shakeThhard6;
            } else {
                bumpsTH = bumpsThmedium6;
                shakesTH =shakeThmedium6;
            }
            break;
        case 7:
            toolDescription = toolDescription7;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh7;
                shakesTH =shakeTh7;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium7;
                shakesTH =shakeThmedium7;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard7;
                shakesTH =shakeThhard7;
            } else {
                bumpsTH = bumpsThmedium7;
                shakesTH =shakeThmedium7;
            }
            break;
        case 8:
            toolDescription = toolDescription8;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh8;
                shakesTH =shakeTh8;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium8;
                shakesTH =shakeThmedium8;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard8;
                shakesTH =shakeThhard8;
            } else {
                bumpsTH = bumpsThmedium8;
                shakesTH =shakeThmedium8;
            }
            break;
        case 9:
            toolDescription = toolDescription9;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh9;
                shakesTH =shakeTh9;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium9;
                shakesTH =shakeThmedium9;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard9;
                shakesTH =shakeThhard9;
            } else {
                bumpsTH = bumpsThmedium9;
                shakesTH =shakeThmedium9;
            }
            break;
        case 10:
            toolDescription = toolDescription10;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh10;
                shakesTH =shakeTh10;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium10;
                shakesTH =shakeThmedium10;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard10;
                shakesTH =shakeThhard10;
            } else {
                bumpsTH = bumpsThmedium10;
                shakesTH =shakeThmedium10;
            }
            break;
        case 11:
            toolDescription = toolDescription11;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh11;
                shakesTH =shakeTh11;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium11;
                shakesTH =shakeThmedium11;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard11;
                shakesTH =shakeThhard11;
            } else {
                bumpsTH = bumpsThmedium11;
                shakesTH =shakeThmedium11;
            }
            break;
        case 12:
            toolDescription = toolDescription12;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh12;
                shakesTH =shakeTh12;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium12;
                shakesTH =shakeThmedium12;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard12;
                shakesTH =shakeThhard12;
            } else {
                bumpsTH = bumpsThmedium12;
                shakesTH =shakeThmedium12;
            }
            break;
        case 13:
            toolDescription = toolDescription13;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh13;
                shakesTH =shakeTh13;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium13;
                shakesTH =shakeThmedium13;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard13;
                shakesTH =shakeThhard13;
            } else {
                bumpsTH = bumpsThmedium13;
                shakesTH =shakeThmedium13;
            }
            break;
        case 14:
            toolDescription = toolDescription14;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh14;
                shakesTH =shakeTh14;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium14;
                shakesTH =shakeThmedium14;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard14;
                shakesTH =shakeThhard14;
            } else {
                bumpsTH = bumpsThmedium14;
                shakesTH =shakeThmedium14;
            }
            break;
        case 15:
            toolDescription = toolDescription15;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh15;
                shakesTH =shakeTh15;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium15;
                shakesTH =shakeThmedium15;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard15;
                shakesTH =shakeThhard15;
            } else {
                bumpsTH = bumpsThmedium15;
                shakesTH =shakeThmedium15;
            }
            break;
        case 16:
            toolDescription = toolDescription16;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh16;
                shakesTH =shakeTh16;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium16;
                shakesTH =shakeThmedium16;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard16;
                shakesTH =shakeThhard16;
            } else {
                bumpsTH = bumpsThmedium16;
                shakesTH =shakeThmedium16;
            }
            break;
        case 17:
            toolDescription = toolDescription17;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh17;
                shakesTH =shakeTh17;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium17;
                shakesTH =shakeThmedium17;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard17;
                shakesTH =shakeThhard17;
            } else {
                bumpsTH = bumpsThmedium17;
                shakesTH =shakeThmedium17;
            }
            break;
        case 18:
            toolDescription = toolDescription18;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh18;
                shakesTH =shakeTh18;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium18;
                shakesTH =shakeThmedium18;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard18;
                shakesTH =shakeThhard18;
            } else {
                bumpsTH = bumpsThmedium18;
                shakesTH =shakeThmedium18;
            }
            break;
        case 19:
            toolDescription = toolDescription19;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh19;
                shakesTH =shakeTh19;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium19;
                shakesTH =shakeThmedium19;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard19;
                shakesTH =shakeThhard19;
            } else {
                bumpsTH = bumpsThmedium19;
                shakesTH =shakeThmedium19;
            }
            break;
        case 20:
            toolDescription = toolDescription20;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh20;
                shakesTH =shakeTh20;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium20;
                shakesTH =shakeThmedium20;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard20;
                shakesTH =shakeThhard20;
            } else {
                bumpsTH = bumpsThmedium20;
                shakesTH =shakeThmedium20;
            }
            break;
        case 21:
            toolDescription = toolDescription21;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh21;
                shakesTH =shakeTh21;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium21;
                shakesTH =shakeThmedium21;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard21;
                shakesTH =shakeThhard21;
            } else {
                bumpsTH = bumpsThmedium21;
                shakesTH =shakeThmedium21;
            }
            break;
        case 22:
            toolDescription = toolDescription22;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh22;
                shakesTH =shakeTh22;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium22;
                shakesTH =shakeThmedium22;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard22;
                shakesTH =shakeThhard22;
            } else {
                bumpsTH = bumpsThmedium22;
                shakesTH =shakeThmedium22;
            }
            break;
        case 23:
            toolDescription = toolDescription23;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh23;
                shakesTH =shakeTh23;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium23;
                shakesTH =shakeThmedium23;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard23;
                shakesTH =shakeThhard23;
            } else {
                bumpsTH = bumpsThmedium23;
                shakesTH =shakeThmedium23;
            }
            break;
        case 24:
            toolDescription = toolDescription24;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh24;
                shakesTH =shakeTh24;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium24;
                shakesTH =shakeThmedium24;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard24;
                shakesTH =shakeThhard24;
            } else {
                bumpsTH = bumpsThmedium24;
                shakesTH =shakeThmedium24;
            }
            break;
        case 25:
            toolDescription = toolDescription25;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh25;
                shakesTH =shakeTh25;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium25;
                shakesTH =shakeThmedium25;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard25;
                shakesTH =shakeThhard25;
            } else {
                bumpsTH = bumpsThmedium25;
                shakesTH =shakeThmedium25;
            }
            break;
        case 26:
            toolDescription = toolDescription26;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh26;
                shakesTH =shakeTh26;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium26;
                shakesTH =shakeThmedium26;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard26;
                shakesTH =shakeThhard26;
            } else {
                bumpsTH = bumpsThmedium26;
                shakesTH =shakeThmedium26;
            }
            break;
        case 27:
            toolDescription = toolDescription27;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh27;
                shakesTH =shakeTh27;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium27;
                shakesTH =shakeThmedium27;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard27;
                shakesTH =shakeThhard27;
            } else {
                bumpsTH = bumpsThmedium27;
                shakesTH =shakeThmedium27;
            }
            break;
        case 28:
            toolDescription = toolDescription28;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh28;
                shakesTH =shakeTh28;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium28;
                shakesTH =shakeThmedium28;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard28;
                shakesTH =shakeThhard28;
            } else {
                bumpsTH = bumpsThmedium28;
                shakesTH =shakeThmedium28;
            }
            break;
        case 29:
            toolDescription = toolDescription29;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh29;
                shakesTH =shakeTh29;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium29;
                shakesTH =shakeThmedium29;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard29;
                shakesTH =shakeThhard29;
            } else {
                bumpsTH = bumpsThmedium29;
                shakesTH =shakeThmedium29;
            }
            break;
        case 30:
            toolDescription = toolDescription30;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh30;
                shakesTH =shakeTh30;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium30;
                shakesTH =shakeThmedium30;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard30;
                shakesTH =shakeThhard30;
            } else {
                bumpsTH = bumpsThmedium30;
                shakesTH =shakeThmedium30;
            }
            break;
        case 31:
            toolDescription = toolDescription31;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh31;
                shakesTH =shakeTh31;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium31;
                shakesTH =shakeThmedium31;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard31;
                shakesTH =shakeThhard31;
            } else {
                bumpsTH = bumpsThmedium31;
                shakesTH =shakeThmedium31;
            }
            break;
        case 32:
            toolDescription = toolDescription32;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh32;
                shakesTH =shakeTh32;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium32;
                shakesTH =shakeThmedium32;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard32;
                shakesTH =shakeThhard32;
            } else {
                bumpsTH = bumpsThmedium32;
                shakesTH =shakeThmedium32;
            }
            break;

        default:
            toolDescription = toolDescription1;
            if(materialType=="Soft"){
                bumpsTH = bumpsTh1;
                shakesTH =shakeTh1;
            } else if(materialType=="Medium"){
                bumpsTH = bumpsThmedium1;
                shakesTH =shakeThmedium1;
            } else if(materialType=="Hard"){
                bumpsTH = bumpsThhard1;
                shakesTH =shakeThhard1;
            } else {
                bumpsTH = bumpsThmedium1;
                shakesTH =shakeThmedium1;
            }
            break;
        }
        /*********************************************************/

        file.close();

        /******************************************************************************
         * Remove tmpSettings.3dc
         ******************************************************************************/
         remove("/home/fisitron/IND4p0/Settings/tmpSettings.3dc");
         /******************************************************************************/

    }
}
/********************************************************************************/

/*********************************************************************
 * funzione per la creazione del file di log (*.txt)
 *********************************************************************/
void MainWindow::createLogFile(QString eventType){

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
    txt.append(" - Working Modality: " + workingModality);
    txt.append(" - Tool: " + QString::number(tool));
    txt.append(" - Material Type: " + materialType);
    txt.append(" - Bump Threshold: " + QString::number(bumpsTH));
    txt.append(" - Shake Threshold: " + QString::number(shakesTH));

    QFile outFile(LogFileName);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts<<txt<<Qt::endl<<Qt::flush;
    outFile.close();
    /************************************************************/

//    /**************************************
//     * nome parziale del file
//     **************************************/
//    QString LogFileName = "_log.txt";
//    /**************************************/
//
//    /********************************
//     * acquisisce la data corrente
//     ********************************/
//    QDateTime date;
//    /********************************/
//
//    /**************************************************************************
//     * Completa il nome del file. ESEMPIO:
//     * "/home/fisitron/IND4p0/Logs/20240301_115025_START_log.txt"
//     **************************************************************************/
//    LogFileName.prepend(eventType);
//    LogFileName.prepend(date.currentDateTime().toString("yyyyMMdd_hhmmss_"));
//    LogFileName.prepend("/home/fisitron/IND4p0/Logs/");
//    /**************************************************************************/
//
//    /************************************************************
//     * crea il file di log
//     ***********************************************************/
//    QFile outFile(LogFileName);
//    //outFile.remove();
//    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream ts(&outFile);
//    QString txt;

//    txt = "Event: " + eventType;
//    ts<<txt<<Qt::endl;
//    txt = "Modality: " + workingModality;
//    ts<<txt<<Qt::endl;
//    txt = "Tool: " + QString::number(tool);
//    ts<<txt<<Qt::endl;
//    txt = "Material Type: " + materialType;
//    ts<<txt<<Qt::endl;
//    txt="Bump Threshold: " + QString::number(bumpsTH);
//    ts<<txt<<Qt::endl;
//    txt="Shake Threshold: " + QString::number(shakesTH);
//    ts<<txt<<Qt::endl;
//    ts<<Qt::flush;
//    //ts<<txt<<Qt::endl<<Qt::flush;

//    outFile.close();
    /***********************************************************/

}
/*********************************************************************/


/********************************************************************************
 * funzione per l'abilitazione/disabilitazione della sezione settaggi
 ********************************************************************************/
void MainWindow::enableSettingsSection(bool enFlag){

    //    if(!enFlag){
    //        bumpsEventCounter=0;
    //        ui->l_bumpsEvents->setText(QString::number(bumpsEventCounter));

    //        shakesEventCounter=0;
    //        ui->l_shakesEvents->setText(QString::number(shakesEventCounter));
    //    }

    ui->label->setEnabled(enFlag);
    ui->lE_bumpsTh->setEnabled(enFlag);

    ui->pB_setConfig->setEnabled(enFlag);
    ui->pB_saveConfig->setEnabled(enFlag);

    ui->label_5->setEnabled(enFlag);
    ui->l_bumpsEvents->setEnabled(enFlag);
    ui->pB_resetBumps->setEnabled(enFlag);

    ui->label_6->setEnabled(enFlag);
    ui->label_7->setEnabled(enFlag);
    ui->label_8->setEnabled(enFlag);
    ui->label_9->setEnabled(enFlag);
    ui->label_10->setEnabled(enFlag);
    ui->lE_shakesTh->setEnabled(enFlag);
    ui->lE_shakesSamplingTime->setEnabled(enFlag);
    ui->l_shakesEvents->setEnabled(enFlag);
    ui->pB_resetShakes->setEnabled(enFlag);
    ui->label_25->setEnabled(enFlag);
    ui->lE_acceptableShakes->setEnabled(enFlag);

    ui->label_11->setEnabled(enFlag);
    ui->l_AxisShakesX->setEnabled(enFlag);
    ui->label_12->setEnabled(enFlag);
    ui->l_AxisShakesY->setEnabled(enFlag);
    ui->label_13->setEnabled(enFlag);
    ui->l_AxisShakesZ->setEnabled(enFlag);

    //    ui->label_14->setEnabled(enFlag);
    //    ui->l_bumpX->setEnabled(enFlag);
    //    ui->label_15->setEnabled(enFlag);
    //    ui->l_bumpY->setEnabled(enFlag);
    //    ui->label_16->setEnabled(enFlag);
    //    ui->l_bumpZ->setEnabled(enFlag);

    ui->label_17->setEnabled(enFlag);
    ui->comboBox_toolSelection->setEnabled(enFlag);
    ui->l_toolDescription->setEnabled(enFlag);
    ui->pB_toolOptions->setEnabled(enFlag);
    ui->checkBox_RawData->setEnabled(enFlag);
    ui->label_22->setEnabled(enFlag);
    ui->radioButton_Manual->setEnabled(enFlag);
    ui->radioButton_Automatic->setEnabled(enFlag);

}
/********************************************************************************/

#define RELE0 26
#define RELE1 19
#define RELE2 13
#define RELE3 6


#define INGRESS0_0 4
#define INGRESS0_1 27
#define INGRESS0_2 22
#define INGRESS0_3 10
#define INGRESS0_4 9
#define INGRESS0_5 11
#define INGRESS0_6 0
#define INGRESS0_7 5


#define MAX_Y 100//1000
#define X_RANGE 1200//1500


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Bumps&Shakes");

    /************************************************
     * Rende invisibili la progress bar
     * ed il pulsante di arresto autoapprendimento
     ************************************************/
    ui->progressBar->setVisible(false);
    ui->pB_abortAcq->setVisible(false);
    ui->pB_saveSuggested->setVisible(false);
    /************************************************/

    //ui->lE_acceptableShakes->setText(QString::number(acceptableShakes));

    //***************** GPIO ***********************//

    // Open GPIO chip
    chip = gpiod_chip_open_by_name(chipname);

    // Open GPIO lines
    rele00 = gpiod_chip_get_line(chip, RELE0);
    rele01 = gpiod_chip_get_line(chip, RELE1);
    rele02 = gpiod_chip_get_line(chip, RELE2);
    rele03 = gpiod_chip_get_line(chip, RELE3);


    //struct gpiod_line *cts = gpiod_chip_get_line(chip, 16);
    //gpiod_line_request_output(cts, "CTS", 1);

    //struct gpiod_line *rts = gpiod_chip_get_line(chip, 17);
    //gpiod_line_request_output(rts, "RTS", 0);


    ingressi_dig[0] = gpiod_chip_get_line(chip, INGRESS0_0);
    ingressi_dig[1] = gpiod_chip_get_line(chip, INGRESS0_1);
    ingressi_dig[2] = gpiod_chip_get_line(chip, INGRESS0_2);
    ingressi_dig[3] = gpiod_chip_get_line(chip, INGRESS0_3);
    ingressi_dig[4] = gpiod_chip_get_line(chip, INGRESS0_4);
    ingressi_dig[5] = gpiod_chip_get_line(chip, INGRESS0_5);
    ingressi_dig[6] = gpiod_chip_get_line(chip, INGRESS0_6);
    ingressi_dig[7] = gpiod_chip_get_line(chip, INGRESS0_7);


    // Open LED lines for output
    gpiod_line_request_output(rele00, "RELE00", 0);
    gpiod_line_request_output(rele01, "RELE01", 0);
    gpiod_line_request_output(rele02, "RELE02", 0);
    gpiod_line_request_output(rele03, "RELE03", 0);


    // Open switch line for input

    gpiod_line_request_input(ingressi_dig[0],"INGRESSO00");
    gpiod_line_request_input(ingressi_dig[1],"INGRESSO01");
    gpiod_line_request_input(ingressi_dig[2],"INGRESSO02");
    gpiod_line_request_input(ingressi_dig[3],"INGRESSO03");
    gpiod_line_request_input(ingressi_dig[4],"INGRESSO04");
    gpiod_line_request_input(ingressi_dig[5],"INGRESSO05");
    gpiod_line_request_input(ingressi_dig[6],"INGRESSO06");
    gpiod_line_request_input(ingressi_dig[7],"INGRESSO07");


    // QUESTI PER SETTARE I RELE ///
    //gpiod_line_set_value(rele00, 1);
    //gpiod_line_set_value(rele01, 1);
    //gpiod_line_set_value(rele02, 1);

    //gpiod_line_set_value(rele00, 0);
    //gpiod_line_set_value(rele01, 0);
    //gpiod_line_set_value(rele02, 0);

    // QUESTI PER LEGGERE GLI INGRESSI ///
    //int ingresso_00 = gpiod_line_get_value(ingressi_dig[0]);


    /******************************************************************************
     * Timer per la lettura degli ingressi digitali
     ******************************************************************************/
    QTimer *acquisitionTimer = new QTimer();
    connect(acquisitionTimer, SIGNAL(timeout()), this, SLOT(acquisitionTask()));
    acquisitionTimer->start(1000);
    /******************************************************************************/

    /*************************************************************
     * sezione grafico
     *************************************************************/
    chart = new Chart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->addSeries(series4);


    chart->setTitle("");
    //chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();

    chart->axisX()->setRange(0, X_RANGE);
    //    QtCharts::QValueAxis *axisX = new QtCharts::QValueAxis();
    //    axisX->setRange(X_RANGE, 0);
    //    chart->addAxis(axisX,Qt::AlignLeft);

    //chart->axisY()->setRange(-RANGE, RANGE);
    chart->axisY()->setRange(0, MAX_Y);

    /*************************************
     * Dimensioni grafico
     *************************************/
    //chart->setGeometry(0,0,550,520);
    chart->setGeometry(0,0,670,540);
    /*************************************/


    chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QGridLayout layout;
    layout.addWidget(chartView);
    ui->GRAPH->setLayout(&layout);
    //grabGesture(Qt::PanGesture);
    //grabGesture(Qt::PinchGesture);
    show();
    /**************************************************************/



    /*******************************************
     *              ATTENZIONE!
     * rende invisibile il pulsante di SAVE
     * perché per il momento non c'è nessuna
     * memoria su cui salvare effettivamente i
     * parametri di configurazione
     *******************************************/
    ui->pB_saveConfig->setVisible(false);
    /*******************************************/


    green_led = new QPixmap(":/image/Image/green_led.jpg");
    red_led = new QPixmap(":/image/Image/red_led.jpg");

    ui->label_led_ack->setPixmap(*green_led);
    ui->label_led_nack->setPixmap(*red_led);
    ui->alarm_led->setPixmap(*red_led);

    ui->label_led_nack->setEnabled(true);

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->comboBox_serialport->addItem(serialPortInfo.portName());
    }


    /*************************************
     * Disabilita sezione settaggi
     *************************************/
    enableSettingsSection(false);
    /*************************************/

    /******************************************************/
    /**************************************
     * disabilita i valori degli assi
     **************************************/
    ui->label_14->setEnabled(false);
    ui->l_bumpX->setEnabled(false);
    ui->label_15->setEnabled(false);
    ui->l_bumpY->setEnabled(false);
    ui->label_16->setEnabled(false);
    ui->l_bumpZ->setEnabled(false);
    /**************************************/

    /********************************************
     * disabilita label_19, lE_acqTime e pB_startAcq
     ********************************************/
    ui->label_19->setEnabled(false);
    ui->lE_acqTime->setEnabled(false);
    ui->pB_startAcq->setEnabled(false);
    /********************************************/

    /**************************************
     * disabilita
     **************************************/
    ui->label_2->setEnabled(false);
    ui->label_18->setEnabled(false);
    ui->l_suggBumpTh->setEnabled(false);

    ui->label_20->setEnabled(false);
    ui->label_21->setEnabled(false);
    ui->l_suggShakeTh->setEnabled(false);

    ui->pB_saveSuggested->setEnabled(false);
    /**************************************/

    /******************************************************/

    /*************************************************
     * Rende invisibile la label BUMP EVENT DETECTED
     *************************************************/
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    /*************************************************/
    /*************************************************
     * Rende invisibile la label Maximum Value Reached
     *************************************************/
    ui->label_24->setVisible(false);
    /*************************************************/

    /*************************************************
     * Rende invisibile la label ACCEPTABLE SHAKES EXCEEDED
     *************************************************/
    ui->label_26->setVisible(false);
    ui->label_27->setVisible(false);
    /*************************************************/


    /*******************************************************************************************
     * connette il timer shakesMonitorTimer alla funzione shakesMonitorFunction
     *******************************************************************************************/
    connect(shakesMonitorTimer, SIGNAL(timeout()), this, SLOT(shakesMonitorFunction()));
    /*******************************************************************************************/

    /*******************************************************************************************
     * connette il timer bumpTimer alla funzione bumpFilterFunction
     *******************************************************************************************/
    connect(bumpTimer, SIGNAL(timeout()), this, SLOT(bumpFilterFunction()));
    /*******************************************************************************************/


    /********************************************************************
     * Completamento dei nomi dei file di log con la data corrente
     ********************************************************************/
    QDateTime date;
    BumpFileName.prepend(date.currentDateTime().toString("yyyyMMdd"));
    BumpFileName.prepend("/home/fisitron/IND4p0/BumpEvents/");

    ShakeFileName.prepend(date.currentDateTime().toString("yyyyMMdd"));
    ShakeFileName.prepend("/home/fisitron/IND4p0/ShakeEvents/");
    /********************************************************************/


//    /***************************************************************************************************
//     * Eliminazione dei file di log di oltre 15 giorni
//     * lettura del file _ToolOptions.3dc contenente le opzioni di 5 tool differenti
//     * lettura del file Settings.3dc se è stata selezionata la modalità di settaggio da file
//     ***************************************************************************************************/
//    /**************************************************************************
//     * Calcola la data corrispondente a 15 giorni prima della data attuale
//     **************************************************************************/
//    QDateTime TwoWeeksAgo = date.currentDateTime().addDays(-15);
//    //    QString sTwoWeeksAgo = TwoWeeksAgo.toString("yyyyMMdd");
//    //    QDateTime date2 = QDateTime::fromString(date.currentDateTime().toString("yyyyMMdd"), "yyyyMMdd");
//    /**************************************************************************/
//
//    /****************************************************
//     * ottiene la directory in cui si trovano i file
//     * contenenti gli eventi di urto e di vibrazione
//     ****************************************************/
//    QFileInfo fi(BumpFileName);
//    QDir fileDir = fi.dir();
//    /****************************************************/
//
//    /******************************************************
//     * ottiene la lista dei file contenuti nella directory
//     ******************************************************/
//    QStringList fileList = fileDir.entryList();
//    /******************************************************/
//
//    /**************************************************************
//     * finchè ci sono file nella directory...
//     **************************************************************/
//    for (int i = 0; i < fileList.size(); ++i) {
//        /*************************************************
//         * ottiene il nome del file in esame
//         *************************************************/
//        QString FileName = fileList[i];
//        /*************************************************/
//
//        /********************************************************
//         * se il file in esame è uno dei file contenente
//         * gli eventi di urto o di vibrazione
//         ********************************************************/
//        //if( (FileName.contains("BumpEventLog.txt")) ||
//        //        (FileName.contains("ShakeEventLog.txt"))  ){
//        //    /*************************************************
//        //    * ottiene le info del file in esame dalle quali
//        //    * ricava la data di creazine del file stesso
//        //    **************************************************/
//        //    QFileInfo fi(FileName);
//        //    QDateTime birthTime = fi.birthTime();
//        //    /*************************************************/
//
//        //    /**********************************************
//        //     * se il file è stato creato prima di
//        //     * TwoWeeksAgo allora viene eliminato
//        //     **********************************************/
//        //    if(birthTime<=TwoWeeksAgo){
//        //        QFile file(FileName);
//        //        file.remove();
//        //    }
//        //    /**********************************************/
//        //}
//        /********************************************************/
//
//
//        /********************************************************
//         * se il file in esame è _ToolOptions.3dc
//         ********************************************************/
//        //if( FileName.contains("_ToolOptions.3dc")  ){
//        //    /*************************************************
//        //    * Legge il contenuto del file _ToolOptions.3dc
//        //    **************************************************/
//        //    readToolOptionFile();
//        //    /*************************************************/
//        //
//        //
//        //}
//        /********************************************************/
//
//
//        /***************************************************************************************************
//         * Se è stata selezionata la modalità di settaggio da file
//         ***************************************************************************************************/
//        //if(settingsFileFlag == true){
//        //    /*************************************************************************************
//        //     * Se il file in esame è quello dei Settings
//        //     *************************************************************************************/
//        //    if( FileName.contains("Settings.3dc")  ){
//        //        readSettingsFile();
//        //
//        //        /***********************************************************
//        //         * Working Modality
//        //         **********************************************************/
//        //        if (workingModality == "MANUAL"){
//        //            /******************************************
//        //             * setta il radioButton_Manual
//        //             ******************************************/
//        //            ui->radioButton_Manual->setChecked(true);
//        //            /******************************************/
//        //
//        //        } else {
//        //            if(workingModality == "AUTOMATIC"){
//        //                /**********************************************
//        //                 * setta il radioButton_Automatic
//        //                 **********************************************/
//        //                ui->radioButton_Automatic->setChecked(true);
//        //                /**********************************************/
//        //
//        //            }
//        //        }
//        //        /****************************************************************/
//        //
//        //
//        //        /***********************************************************
//        //         * Material Type
//        //         **********************************************************/
//        //        if (materialType == "Soft"){
//        //            /******************************************
//        //             * setta il rB_soft
//        //             ******************************************/
//        //            ui->rB_soft->setChecked(true);
//        //            /******************************************/
//        //        } else if (materialType == "Medium"){
//        //            /******************************************
//        //             * setta il rB_medium
//        //             ******************************************/
//        //            ui->rB_medium->setChecked(true);
//        //            /******************************************/
//        //        } else if (materialType == "Hard"){
//        //            /******************************************
//        //             * setta il rB_hard
//        //             ******************************************/
//        //            ui->rB_hard->setChecked(true);
//        //            /******************************************/
//        //        } else {
//        //            /******************************************
//        //             * setta il rB_medium come default
//        //             ******************************************/
//        //            ui->rB_medium->setChecked(true);
//        //            /******************************************/
//        //        }
//        //        /************************************************************/
//        //
//        //        /**********************************************************
//        //         * setta la comboBox_toolSelection
//        //         **********************************************************/
//        //        ui->comboBox_toolSelection->setCurrentIndex(tool-1);
//        //        /**********************************************************/
//        //
//        //        /*********************************
//        //         * Simula il toggle del pulsante
//        //         * di connessione alla seriale
//        //         *********************************/
//        //        on_pushButton_toggled(true);
//        //        /*********************************/
//        //
//        //        //                /*********************************
//        //        //                 * Escamotage ?
//        //        //                 *********************************/
//        //        //                unsigned long secs = 1;
//        //        //                QThread::sleep(secs);
//        //        //                on_pushButton_toggled(true);
//        //        //                /*********************************/
//        //
//        //    }
//        //    /*************************************************************************************/
//        //}
//        /**************************************************************************************************/
//
//    }
//    /**************************************************************/
//    /***************************************************************************************************/


    /*************************************************
    * Legge il contenuto del file _ToolOptions.3dc
    **************************************************/
    readToolOptionFile();
    /*************************************************/

    /***************************************************************************************************
     * Se è stata selezionata la modalità di settaggio da file
     ***************************************************************************************************/
    if(settingsFileFlag == true){
        /*************************************************************************************
         * Legge il contenuto del file Settings.3dc
         *************************************************************************************/
            readSettingsFile();
            ui->lE_acceptableShakes->setText(QString::number(acceptableShakes));
            /***********************************************************
             * Working Modality
             **********************************************************/
            if (workingModality == "MANUAL"){
                /******************************************
                 * setta il radioButton_Manual
                 ******************************************/
                ui->radioButton_Manual->setChecked(true);
                /******************************************/

            } else {
                if(workingModality == "AUTOMATIC"){
                    /**********************************************
                     * setta il radioButton_Automatic
                     **********************************************/
                    ui->radioButton_Automatic->setChecked(true);
                    /**********************************************/

                }
            }
            /****************************************************************/


            /***********************************************************
             * Material Type
             **********************************************************/
            if (materialType == "Soft"){
                /******************************************
                 * setta il rB_soft
                 ******************************************/
                ui->rB_soft->setChecked(true);
                /******************************************/
            } else if (materialType == "Medium"){
                /******************************************
                 * setta il rB_medium
                 ******************************************/
                ui->rB_medium->setChecked(true);
                /******************************************/
            } else if (materialType == "Hard"){
                /******************************************
                 * setta il rB_hard
                 ******************************************/
                ui->rB_hard->setChecked(true);
                /******************************************/
            } else {
                /******************************************
                 * setta il rB_medium come default
                 ******************************************/
                ui->rB_medium->setChecked(true);
                /******************************************/
            }
            /************************************************************/

            /**********************************************************
             * setta la comboBox_toolSelection
             **********************************************************/
            ui->comboBox_toolSelection->setCurrentIndex(tool-1);
            /**********************************************************/

            /*********************************
             * Simula il toggle del pulsante
             * di connessione alla seriale
             *********************************/
            on_pushButton_toggled(true);
            /*********************************/

            //                /*********************************
            //                 * Escamotage ?
            //                 *********************************/
            //                unsigned long secs = 1;
            //                QThread::sleep(secs);
            //                on_pushButton_toggled(true);
            //                /*********************************/

        //}
        /*************************************************************************************/
    }
    /**************************************************************************************************/


    /**************************
     * crea il file di log
     **************************/
    createLogFile("START");
    /**************************/


}

MainWindow::~MainWindow()
{
    /**************************
     * crea il file di log
     **************************/
    createLogFile("CLOSE");
    /**************************/

    delete ui;
}

void MainWindow::acquisitionTask(){
    /******************************************
     * ACCENSIONE E SPEGNIMENTO RELE PER DEBUG
     ******************************************/
//    if(onOff==0){
//        onOff=1;
//    } else {
//        if(onOff==1){
//        onOff=0;
//        }
//    }
//    gpiod_line_set_value(rele00, onOff);
//    gpiod_line_set_value(rele01, onOff);
//    gpiod_line_set_value(rele02, onOff);
    /******************************************/

    if (ui->radioButton_Automatic->isEnabled() && ui->radioButton_Automatic->isChecked()){

        /*************************************************
         * Disabilita la selezione dei tool e
         * la possibilità di editare le soglie ed il
         * commento
         *************************************************/
        ui->comboBox_toolSelection->setEnabled(false);
        //ui->pB_toolOptions->setEnabled(false);
        /*************************************************/

        /**********************************************************
         * Acquisisce i segnali digitali in ingresso
         **********************************************************/
        int ingresso_00 = gpiod_line_get_value(ingressi_dig[0]);
        int ingresso_01 = gpiod_line_get_value(ingressi_dig[1]);
        int ingresso_02 = gpiod_line_get_value(ingressi_dig[2]);
        int ingresso_03 = gpiod_line_get_value(ingressi_dig[3]);
        int ingresso_04 = gpiod_line_get_value(ingressi_dig[4]);
        int ingresso_05 = gpiod_line_get_value(ingressi_dig[5]);
        int ingresso_06 = gpiod_line_get_value(ingressi_dig[6]);
        int ingresso_07 = gpiod_line_get_value(ingressi_dig[7]);


        qDebug()<< ingresso_00 << ingresso_01 << ingresso_02  << ingresso_03  << ingresso_04  << ingresso_05  << ingresso_06  << ingresso_07 ;
        /**********************************************************/

        if(ingresso_07==0){
            /**************************
             * abilita il muting
             **************************/
            toolChangingFlag = true;
            /**************************/
        }else{
            /**************************
             * disabilita il muting
             **************************/
            toolChangingFlag = false;
            /**************************/
        }

        /***************************************************************************************************************************************************
         * Decodifica gli ingressi e li "traduce" nel numero del tool da utilizzare
         **************************************************************************************************************************************************/
        //int ingressi = (ingresso_07<<7)+(ingresso_06<<6)+(ingresso_05<<5)+(ingresso_04<<4)+(ingresso_03<<3)+(ingresso_02<<2)+(ingresso_01<<1)+ingresso_00;
        //tool = 255-ingressi;
        /***************************************************************************************************************************************************/
        /***************************************************************************************************************************************************
         * Decodifica gli ingressi e li "traduce" nel numero del tool da utilizzare
         **************************************************************************************************************************************************/
        int ingressi = (ingresso_06<<6)+(ingresso_05<<5)+(ingresso_04<<4)+(ingresso_03<<3)+(ingresso_02<<2)+(ingresso_01<<1)+ingresso_00;
        tool = 127-ingressi;
        /***************************************************************************************************************************************************/

        /********************************************************
         * Radio Buttons di debug
         ********************************************************/
        ui->radioButton_IN00->setChecked(!(bool)ingresso_00);
        ui->radioButton_IN01->setChecked(!(bool)ingresso_01);
        ui->radioButton_IN02->setChecked(!(bool)ingresso_02);
        ui->radioButton_IN03->setChecked(!(bool)ingresso_03);
        ui->radioButton_IN04->setChecked(!(bool)ingresso_04);
        ui->radioButton_IN05->setChecked(!(bool)ingresso_05);
        ui->radioButton_IN06->setChecked(!(bool)ingresso_06);
        ui->radioButton_IN07->setChecked(!(bool)ingresso_07);
        /********************************************************/

        /****************************************************
         * Setta il tool derivato dagli ingressi
         ****************************************************/
        ui->comboBox_toolSelection->setCurrentIndex(tool-1);
        /****************************************************/

    }
    else{
        if(ui->radioButton_Manual->isEnabled() && ui->radioButton_Manual->isChecked()){
            /*************************************************
             * Abilita la selezione dei tool e
             * la possibilità di editare le soglie ed il
             * commento
             *************************************************/
            ui->comboBox_toolSelection->setEnabled(true);
            ui->pB_toolOptions->setEnabled(true);
            /*************************************************/

            /**************************
             * disabilita il muting
             **************************/
            //toolChangingFlag = false;
            /**************************/

            /******************************************************************
             * Acquisisce il segnale digitale in ingresso relativo al MUTING
             ******************************************************************/
            int ingresso_07 = gpiod_line_get_value(ingressi_dig[7]);
            /******************************************************************/

            /******************************************************************
             * Decodifica il segnale digitale in ingresso relativo al MUTING
             ******************************************************************/
            if(ingresso_07==0){
                /**************************
                 * abilita il muting
                 **************************/
                toolChangingFlag = true;
                /**************************/
            }else{
                /**************************
                 * disabilita il muting
                 **************************/
                toolChangingFlag = false;
                /**************************/
            }
            /******************************************************************/

            /******************************************************************
             * Setta opportunamente il radioButton relativo al MUTING
             ******************************************************************/
            ui->radioButton_IN07->setChecked(!(bool)ingresso_07);
            /******************************************************************/
        }
    }

}


void MainWindow::on_pushButton_toggled(bool checked)
{
    if(checked)
    {
        /*******************************************************************************************************************
         * Se non è stata selezionata la modalità di settaggio da file, la seriale va selezionata manualmente attraverso
         * la comboBox presente sull'interfaccia, pertanto ...
         *******************************************************************************************************************/
        if(settingsFileFlag == false){
            name_serialport = ui->comboBox_serialport->currentText(); // ottiene il nome della porta seriale selezionata
        }
        /*******************************************************************************************************************/

        //name_serialport = ui->comboBox_serialport->currentText(); // ottiene il nome della porta seriale selezionata
        init_serial_port(name_serialport,115200); // inizializza la porta seriale selezionata con Baud Rate pari a 115200

    }
    else
    {
        closeSerialPort(); // chiude la porta seriale
    }
}


void MainWindow::init_serial_port(QString name,uint32_t baud)
{

    if(m_serial_port==NULL)
    {
        m_serial_port = new QSerialPort();
    }
    else
    {
        closeSerialPort();
        delete m_serial_port;
        m_serial_port = new QSerialPort();
    }

    settings.name = name;
    settings.baudRate = baud;
    settings.dataBits = QSerialPort::Data8;
    settings.parity = QSerialPort::NoParity;
    settings.stopBits = QSerialPort::OneStop;
    settings.flowControl = QSerialPort::NoFlowControl;
    settings.localEchoEnabled = false;

    connect(m_serial_port, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
    connect(m_serial_port, &QSerialPort::readyRead, this, &MainWindow::readData);

    openSerialPort();
}


void MainWindow::openSerialPort()
{
    m_serial_port->setPortName(settings.name);
    m_serial_port->setBaudRate(settings.baudRate);
    m_serial_port->setDataBits(settings.dataBits);
    m_serial_port->setParity(settings.parity);
    m_serial_port->setStopBits(settings.stopBits);
    m_serial_port->setFlowControl(settings.flowControl);

    if (m_serial_port->open(QIODevice::ReadWrite)) {

        /*****************************************************
         * Disabilita e rende invisibile il LED ROSSO
         * Abilita e rende visibile il LED VERDE
         *****************************************************/
        ui->label_led_nack->setEnabled(false); //led rosso
        ui->label_led_nack->setVisible(false); //led rosso
        ui->label_led_ack->setEnabled(true); //led verde
        ui->label_led_ack->setVisible(true); //led verde
        /*****************************************************/

        /***************************************
         * Scrive DISCONNECT sul pulsante
         ***************************************/
        ui->pushButton->setText("DISCONNECT");
        /***************************************/

        /*****************************************************
         * Disabilita la selezione di un'altra porta seriale
         * finchè si è già connessi
         *****************************************************/
        ui->comboBox_serialport->setDisabled(true);
        ui->pushButton_refresh_serial->setDisabled(true);
        /*****************************************************/

        /*************************************
         * Abilita sezione settaggi
         *************************************/
        enableSettingsSection(true);
        /*************************************/

        /************************************
         * Se è stata selezionata la modalità
         * di settaggio da file, setta i
         * valori di configurazione letti nel
         * file Settings.3dc
         ************************************/
        if(settingsFileFlag == true){
            setConfiguration();
        }
        /************************************/

        //        /*********************************
        //         * PAUSA ?
        //         *********************************/
        //        unsigned long secs = 1;
        //        QThread::sleep(secs);
        //        /*********************************/

        /****************************************
         * Richiede i valori di configurazione
         ****************************************/
        getConfiguration();
        /****************************************/


        //        qDebug()<< "SERIAL PORT CONNECTED" << m_serial_port->errorString();
        qDebug()<< "SERIAL PORT CONNECTED";


    } else {

        /*****************************************************
         * Disabilita e rende invisibile il LED VERDE
         * Abilita e rende visibile il LED ROSSO
         *****************************************************/
        ui->label_led_ack->setEnabled(false); //led verde
        ui->label_led_ack->setVisible(false); //led verde
        ui->label_led_nack->setEnabled(true); //led rosso
        ui->label_led_nack->setVisible(true); //led rosso
        /******************************************************/

        /***************************************
         * scrive CONNECT sul pulsante
         ***************************************/
        ui->pushButton->setText("CONNECT");
        /***************************************/

        /*********************************************
         * Abilita la selezione delle porte seriali
         *********************************************/
        ui->comboBox_serialport->setEnabled(true);
        ui->pushButton_refresh_serial->setEnabled(true);
        /*********************************************/

        /*************************************
         * Disabilita sezione settaggi
         * ***********************************/
        enableSettingsSection(false);
        /*************************************/

        //qDebug()<< "SERIAL PORT ERROR" << m_serial_port->errorString();
        qDebug()<< "SERIAL PORT FAILED TO CONNECT";

    }
}


void MainWindow::closeSerialPort()
{
    if (m_serial_port->isOpen()){

        /**********************************
         * Chiude la porta seriale aperta
         **********************************/
        m_serial_port->close();
        /**********************************/

        /*****************************************************
         * Disabilita e rende invisibile il LED VERDE
         * Abilita e rende visibile il LED ROSSO
         *****************************************************/
        ui->label_led_ack->setEnabled(false); //led verde
        ui->label_led_ack->setVisible(false); //led verde
        ui->label_led_nack->setEnabled(true); //led rosso
        ui->label_led_nack->setVisible(true); //led rosso
        /*****************************************************/

        /***************************************
         * scrive CONNECT sul pulsante
         ***************************************/
        ui->pushButton->setText("CONNECT");
        /***************************************/

        /*********************************************
         * Abilita la selezione delle porte seriali
         *********************************************/
        ui->comboBox_serialport->setEnabled(true);
        ui->pushButton_refresh_serial->setEnabled(true);
        /*********************************************/

        /*************************************
         * Disabilita sezione settaggi
         *************************************/
        enableSettingsSection(false);
        /*************************************/

        //        qDebug()<< "SERIAL PORT DISCONNECTED" << m_serial_port->errorString();
        qDebug()<< "SERIAL PORT DISCONNECTED";


        /***********************************
         * ferma il timer per il check
         * delle vibrazioni
         ***********************************/
        shakesMonitorTimer->stop();
        /***********************************/

    }

}


/***************************************************************************************************
 * funzione per la lettura dei dati ricevuti attraverso la seriale
 ***************************************************************************************************/
void MainWindow::readData()
{
    /********************************************************
     * Legge i dati provenienti dalla seriale
     ********************************************************/
    const QByteArray data = m_serial_port->readAll();
    /********************************************************/

    //qDebug() << data;
    qDebug()<< " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> RECEIVED DATA " << data;


    foreach (uint8_t var, data) {

        /**************************************
         * riempie il buffer coi dati ricevuti
         **************************************/
        receive_buffer[index_buffer] = var;
        /**************************************/

        /************************************************
         * calcola la dimensione del pacchetto ricevuto
         ************************************************/
        int size_of_packet = sizeof(protocollo_uart);
        /************************************************/


        /******************************************************************
         * Se è arrivato tutto il pacchetto entra nell'IF
         ******************************************************************/
        if((var == ETX_TAG) && (index_buffer >= size_of_packet - 1))
        {
            /*********************************************
             * crea una variabile d'appoggio dummy
             * nella quale copia i dati ricevuti
             *********************************************/
            protocollo_uart dummy;
            memcpy(&dummy,receive_buffer,size_of_packet);
            /*********************************************/

            //if((dummy.stx == STX_TAG)&&(dummy.etx == ETX_TAG))
            //{

            //                /***********************************************************
            //                 * Se è arrivata una segnalazione di allarme
            //                 ***********************************************************/
            //                if(dummy.cmd == bump_event_cmd)
            //                {
            //                    if(ui->alarm_led->isEnabled()){
            //                        ui->alarm_led->setEnabled(false);
            //                        /*******************************************
            //                         * Rende invisibile la label ALARM DETECTED
            //                         *******************************************/
            //                        ui->label_3->setVisible(false);
            //                        ui->label_4->setVisible(false);
            //                        /*******************************************/
            //                        qDebug()<< "ALARM DISABLED";
            //                    } else {
            //                        ui->alarm_led->setEnabled(true);
            //                        /*******************************************
            //                         * Rende visibile la label ALARM DETECTED
            //                         *******************************************/
            //                        ui->label_3->setVisible(true);
            //                        ui->label_4->setVisible(true);
            //                        /*******************************************/

            //                        /************************************************************
            //                         * Incrementa
            //                         ************************************************************/
            //                        bumpsEventCounter++;
            //                        ui->l_bumpsEvents->setText(QString::number(bumpsEventCounter));
            //                        /************************************************************/

            //                        /***************************
            //                         * Fa partire il beep
            //                         ***************************/
            //                        QApplication::beep();
            //                        /***************************/

            //                        qDebug()<< "ALARM EVENT DETECTED";
            //                    }

            //                }
            //                /***********************************************************/


            /***************************************************************************************************
             * Se è arrivata una segnalazione di evento di urto dovuto al superamento dell'hidden bump threshold
             ***************************************************************************************************/
            if(dummy.cmd == hidden_bump_event_cmd && toolChangingFlag==false) //&& rawDataEnableFlag==false && toolChangingFlag==false)
            {
                if(!bumpFlag){

                    /**********************************
                     * mette a true il bumpFlag per
                     * indicare che è avvenuto un urto
                     * così da filtrare i "rimbalzi"
                     **********************************/
                    bumpFlag = true;
                    /**********************************/

                    gpiod_line_set_value(rele00, 1);

                    ui->alarm_led->setEnabled(true);
                    /*******************************************
                     * Rende visibile la label EVENT DETECTED
                     *******************************************/
                    ui->label_3->setVisible(true);
                    ui->label_4->setVisible(true);
                    /*******************************************/
                    /*************************************************
                     * Rende visibile la label Maximum Value Reached
                     *************************************************/
                    ui->label_24->setVisible(true);
                    /*************************************************/

                    /************************************************************
                     * Incrementa il contatore degli urti
                     ************************************************************/
                    bumpsEventCounter++;
                    ui->l_bumpsEvents->setText(QString::number(bumpsEventCounter));
                    /************************************************************/

                    /******************************************************************
                     * Aggiorna i valori del segnale sugli assi
                     ******************************************************************/
                    //bumpSignalX = dummy.payload[7];
                    bumpSignalX = dummy.pay.output_X;
                    ui->l_bumpX->setText(QString::number(bumpSignalX));

                    //bumpSignalY = dummy.payload[8];
                    bumpSignalY = dummy.pay.output_Y;
                    ui->l_bumpY->setText(QString::number(bumpSignalY));

                    //bumpSignalZ = dummy.payload[9];
                    bumpSignalZ = dummy.pay.output_Z;
                    ui->l_bumpZ->setText(QString::number(bumpSignalZ));
                    /*****************************************************************/

                    /***************************
                     * Fa partire il beep
                     ***************************/
                    QApplication::beep();
                    /***************************/

                    qDebug()<< "HIDDEN BUMP EVENT DETECTED";


                    /*******************************************************************************
                     * Aggiorna il file BumpEventLog.txt
                     *******************************************************************************/
                    QString txt;
                    QDateTime date;

                    txt = "HIDDEN BUMP EVENT DETECTED";
                    txt.append(" - "); // txt.prepend(" - ");
                    txt.append(date.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")); // txt.prepend(date.currentDateTime().toString());
                    txt.append(" - ");
                    txt.append("Tool:");
                    txt.append(QString::number(tool)); // tool selezionato
                    txt.append(" - ");
                    txt.append("Hidden Threshold:");
                    //txt.append(QString::number((int)dummy.payload[0])); // bump threshold
                    txt.append(QString::number((int)dummy.pay.hiddenBumpsThreshold)); // bump threshold
                    txt.append(" - ");
                    txt.append(" (X:");
                    //txt.append(QString::number((int)dummy.payload[7])); // X axis value
                    txt.append(QString::number((int)dummy.pay.output_X)); // X axis value
                    txt.append("  Y:");
                    //txt.append(QString::number((int)dummy.payload[8])); // Y axis value
                    txt.append(QString::number((int)dummy.pay.output_Y)); // Y axis value
                    txt.append("  Z:");
                    //txt.append(QString::number((int)dummy.payload[9])); // Z axis value
                    txt.append(QString::number((int)dummy.pay.output_Z)); // Z axis value
                    txt.append(")");

                    //BumpFileName.prepend(date.currentDateTime().toString("yyyyMMdd"));
                    QFile outFile(BumpFileName); // QFile outFile("BumpEventLog.txt");
                    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
                    QTextStream ts(&outFile);
                    ts<<txt<<Qt::endl<<Qt::flush;
                    /********************************************************************************/

                    /*******************************
                     * Avvia il bumpTimer così che,
                     * per 2000ms, vengano ignorati
                     * i "rimbalzi" dovuti all'urto
                     * che è stato rilevato
                     *******************************/
                    bumpTimer->start(2000);
                    /*******************************/

                }


            }
            /***************************************************************************************************/



            /***************************************************************************************************
             * Se è arrivata una segnalazione di evento di urto
             ***************************************************************************************************/
            if(dummy.cmd == bump_event_cmd && rawDataEnableFlag==false && toolChangingFlag==false)
            {
                if(!bumpFlag){

                    /**********************************
                     * mette a true il bumpFlag per
                     * indicare che è avvenuto un urto
                     * così da filtrare i "rimbalzi"
                     **********************************/
                    bumpFlag = true;
                    /**********************************/

                    gpiod_line_set_value(rele00, 1);

                    ui->alarm_led->setEnabled(true);
                    /*******************************************
                     * Rende visibile la label EVENT DETECTED
                     *******************************************/
                    ui->label_3->setVisible(true);
                    ui->label_4->setVisible(true);
                    /*******************************************/

                    /************************************************************
                     * Incrementa il contatore degli urti
                     ************************************************************/
                    bumpsEventCounter++;
                    ui->l_bumpsEvents->setText(QString::number(bumpsEventCounter));
                    /************************************************************/

                    /******************************************************************
                     * Aggiorna i valori del segnale sugli assi
                     ******************************************************************/
                    //bumpSignalX = dummy.payload[7];
                    bumpSignalX = dummy.pay.output_X;
                    ui->l_bumpX->setText(QString::number(bumpSignalX));

                    //bumpSignalY = dummy.payload[8];
                    bumpSignalY = dummy.pay.output_Y;
                    ui->l_bumpY->setText(QString::number(bumpSignalY));

                    //bumpSignalZ = dummy.payload[9];
                    bumpSignalZ = dummy.pay.output_Z;
                    ui->l_bumpZ->setText(QString::number(bumpSignalZ));
                    /*****************************************************************/

                    /***************************
                     * Fa partire il beep
                     ***************************/
                    QApplication::beep();
                    /***************************/

                    qDebug()<< "BUMP EVENT DETECTED";


                    /*******************************************************************************
                     * Aggiorna il file BumpEventLog.txt
                     *******************************************************************************/
                    QString txt;
                    QDateTime date;

                    txt = "BUMP EVENT DETECTED";
                    txt.append(" - "); // txt.prepend(" - ");
                    txt.append(date.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")); // txt.prepend(date.currentDateTime().toString());
                    txt.append(" - ");
                    txt.append("Tool:");
                    txt.append(QString::number(tool)); // tool selezionato
                    txt.append(" - ");
                    txt.append("Threshold:");
                    //txt.append(QString::number((int)dummy.payload[0])); // bump threshold
                    txt.append(QString::number((int)dummy.pay.bumpsThreshold)); // bump threshold
                    txt.append(" - ");
                    txt.append(" (X:");
                    //txt.append(QString::number((int)dummy.payload[7])); // X axis value
                    txt.append(QString::number((int)dummy.pay.output_X)); // X axis value
                    txt.append("  Y:");
                    //txt.append(QString::number((int)dummy.payload[8])); // Y axis value
                    txt.append(QString::number((int)dummy.pay.output_Y)); // Y axis value
                    txt.append("  Z:");
                    //txt.append(QString::number((int)dummy.payload[9])); // Z axis value
                    txt.append(QString::number((int)dummy.pay.output_Z)); // Z axis value
                    txt.append(")");

                    //BumpFileName.prepend(date.currentDateTime().toString("yyyyMMdd"));
                    QFile outFile(BumpFileName); // QFile outFile("BumpEventLog.txt");
                    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
                    QTextStream ts(&outFile);
                    ts<<txt<<Qt::endl<<Qt::flush;
                    /********************************************************************************/

                    /*******************************
                     * Avvia il bumpTimer così che,
                     * per 2000ms, vengano ignorati
                     * i "rimbalzi" dovuti all'urto
                     * che è stato rilevato
                     *******************************/
                    bumpTimer->start(2000);
                    /*******************************/

                }


            }
            /***************************************************************************************************/


            /***********************************************************
             * Se è arrivata una segnalazione di evento di vibrazione
             ***********************************************************/
            if(dummy.cmd == shake_event_cmd && rawDataEnableFlag==false && toolChangingFlag==false)
            {

                /************************************************************************
                 * Ricava dal payload del pacchetto ricevuto il valore delle vibrazioni
                 * calcolate dal FW e le visualizza sull'interfaccia
                 ************************************************************************/
                //shakesEventCounter = dummy.payload[3];
                shakesEventCounter = dummy.pay.shakesCount;
                ui->l_shakesEvents->setText(QString::number(shakesEventCounter));

                //shakesEventCounterX = dummy.payload[4];
                shakesEventCounterX = dummy.pay.xShakesCount;
                ui->l_AxisShakesX->setText(QString::number(shakesEventCounterX));

                //shakesEventCounterY = dummy.payload[5];
                shakesEventCounterY = dummy.pay.yShakesCount;
                ui->l_AxisShakesY->setText(QString::number(shakesEventCounterY));

                //shakesEventCounterZ = dummy.payload[6];
                shakesEventCounterZ = dummy.pay.zShakesCount;
                ui->l_AxisShakesZ->setText(QString::number(shakesEventCounterZ));
                /************************************************************************/


                qDebug()<< "SHAKE COUNTER UPDATED"; qDebug()<< "acceptableShakes" << acceptableShakes;
                //qDebug()<< "HIDDEN BUMP TH FROM SENSOR" << hiddenBumpTh;


                /************************************************************
                 * Aggiorna il file ShakeEventLog.txt
                 ************************************************************/
                QString txt;
                QDateTime date;

                txt = "SHAKE EVENT DETECTED";
                txt.append(" - "); // txt.prepend(" - ");
                txt.append(date.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")); // txt.prepend(date.currentDateTime().toString());
                txt.append(" - ");
                txt.append("Tool:");
                txt.append(QString::number(tool)); // tool selezionato
                txt.append(" - ");
                txt.append("Threshold:");
                //txt.append(QString::number((int)dummy.payload[1])); // shake threshold
                txt.append(QString::number((int)dummy.pay.shakesThreshold)); // shake threshold
                txt.append(" - ");
                txt.append("Sampling Time [s]:");
                //txt.append(QString::number((int)dummy.payload[2])); // sampling time
                txt.append(QString::number((int)dummy.pay.shakesSamplingTime)); // sampling time
                txt.append(" - ");
                txt.append("Shakes Count:");
                //txt.append(QString::number((int)dummy.payload[3])); // counter
                txt.append(QString::number((int)dummy.pay.shakesCount)); // counter
                txt.append(" (X Shakes:");
                //txt.append(QString::number((int)dummy.payload[4])); // X counter
                //txt.append(QString::number((int)dummy.pay.xShakesCount)); // X counter
                txt.append(QString::number((int)dummy.pay.output_X)); // X value
                txt.append("  Y Shakes:");
                //txt.append(QString::number((int)dummy.payload[5])); // Y counter
                //txt.append(QString::number((int)dummy.pay.yShakesCount)); // Y counter
                txt.append(QString::number((int)dummy.pay.output_Y)); // Y value
                txt.append("  Z Shakes:");
                //txt.append(QString::number((int)dummy.payload[6])); // Z counter
                //txt.append(QString::number((int)dummy.pay.zShakesCount)); // Z counter
                txt.append(QString::number((int)dummy.pay.output_Z)); // Z value
                txt.append(")");

                //ShakeFileName.prepend(date.currentDateTime().toString("yyyyMMdd"));
                QFile outFile(ShakeFileName); // QFile outFile("ShakeEventLog.txt"); //QFile(const QString &name);
                outFile.open(QIODevice::WriteOnly | QIODevice::Append);
                QTextStream ts(&outFile);
                ts<<txt<<Qt::endl<<Qt::flush;
                /************************************************************/

                /***************************************************
                 * Se il contatore degli shake supera il numero
                 * accettabile di vibrazioni, compare la scritta
                 * ACCEPTABLE SHAKES EXCEEDED e fa scattare il relè01
                 ***************************************************/
                if(shakesEventCounter>=acceptableShakes){
                    ui->label_26->setVisible(true);
                    ui->label_27->setVisible(true);
                    gpiod_line_set_value(rele01, 1);
                } else {
                    ui->label_26->setVisible(false);
                    ui->label_27->setVisible(false);
                    gpiod_line_set_value(rele01, 0);
                }



            }
            /***********************************************************/



            /***********************************************************
             *           (COMANDO NON IMPLEMENTATO A LIVELLO FW)
             * Se l'allarme è stato disabilitato
             ***********************************************************/
            //            if(dummy.cmd == alarm_disabled_cmd)
            //            {
            //                ui->alarm_led->setEnabled(false);
            //                /*******************************************
            //                 * Rende invisibile la label EVENT DETECTED
            //                 *******************************************/
            //                ui->label_3->setVisible(false);
            //                ui->label_4->setVisible(false);
            //                /*******************************************/
            //                qDebug()<< "ALARM DISABLED";
            //            }
            /***********************************************************/


            /******************************************************************
             * Se sono stati ricevuti i valori dei parametri di configurazione
             ******************************************************************/
            if(dummy.cmd == getConfiguration_cmd)
            {
                /**********************************************************************
                * Scrive negli appositi campi i valori delle soglie
                * e dei contatori appena ricevuti
                **********************************************************************/
                //ui->lE_bumpsTh->setText(QString::number((int)dummy.payload[0]));
                ui->lE_bumpsTh->setText(QString::number((int)dummy.pay.bumpsThreshold));

                //ui->lE_shakesTh->setText(QString::number((int)dummy.payload[1]));
                ui->lE_shakesTh->setText(QString::number((int)dummy.pay.shakesThreshold));

                //ui->lE_shakesSamplingTime->setText(QString::number((int)dummy.payload[2]));
                ui->lE_shakesSamplingTime->setText(QString::number((int)dummy.pay.shakesSamplingTime));

                //ui->l_shakesEvents->setText(QString::number((int)dummy.payload[3]));
                ui->l_shakesEvents->setText(QString::number((int)dummy.pay.shakesCount));

                //ui->l_AxisShakesX->setText(QString::number((int)dummy.payload[4]));
                ui->l_AxisShakesX->setText(QString::number((int)dummy.pay.xShakesCount));

                //ui->l_AxisShakesY->setText(QString::number((int)dummy.payload[5]));
                ui->l_AxisShakesY->setText(QString::number((int)dummy.pay.yShakesCount));

                //ui->l_AxisShakesZ->setText(QString::number((int)dummy.payload[6]));
                ui->l_AxisShakesZ->setText(QString::number((int)dummy.pay.zShakesCount));


                //ui->l_bumpX->setText(QString::number((int)dummy.payload[7]));
                ui->l_bumpX->setText(QString::number((int)dummy.pay.output_X));

                //ui->l_bumpY->setText(QString::number((int)dummy.payload[8]));
                ui->l_bumpY->setText(QString::number((int)dummy.pay.output_Y));

                //ui->l_bumpZ->setText(QString::number((int)dummy.payload[9]));
                ui->l_bumpZ->setText(QString::number((int)dummy.pay.output_Z));
                /**********************************************************************/

                //hiddenBumpTh = (double) dummy.pay.hiddenBumpsThreshold;
                //qDebug()<< "HIDDEN BUMP TH FROM SENSOR" << hiddenBumpTh;


                /***************************************************************************
                * avvia il timer per il check delle vibrazioni
                * sull'interfaccia viene passato il valore in secondi, il timer vuole
                * il parametro in millisecondi quindi è necessario moltiplicare per 1000
                ***************************************************************************/
                //               double shakesSamplingTime = ui->lE_shakesSamplingTime->text().toDouble();
                shakesSamplingTime = lround(ui->lE_shakesSamplingTime->text().toDouble()  );
                if(shakesSamplingTime<=2) {shakesSamplingTime = 2; ui->lE_shakesSamplingTime->setText(QString::number((int)shakesSamplingTime));}
                //shakesMonitorTimer->start((int)shakesSamplingTime*1000);
                shakesMonitorTimer->start(shakesMonitorTimerPeriod);
                /**********************************/
                /***************************************************************************/

            }
            /******************************************************************/

            //}




            /*************************************************************************************
             * Se sono stati ricevuti i valori dei dati grezzi
             *************************************************************************************/
            if(dummy.cmd == getRawData_cmd)
            {
                /******************************************************************
                 * Scrive nei campi X, Y e Z i valori ottenuti dal FW
                 ******************************************************************/
                //bumpSignalX = dummy.payload[7];
                bumpSignalX = dummy.pay.output_X;
                if(bumpSignalX>=1000) bumpSignalX=0;
                ui->l_bumpX->setText(QString::number(bumpSignalX));

                //bumpSignalY = dummy.payload[8];
                bumpSignalY = dummy.pay.output_Y;
                if(bumpSignalY>=1000) bumpSignalY=0;
                ui->l_bumpY->setText(QString::number(bumpSignalY));

                //bumpSignalZ = dummy.payload[9];
                bumpSignalZ = dummy.pay.output_Z;
                if(bumpSignalZ>=1000) bumpSignalZ=0;
                ui->l_bumpZ->setText(QString::number(bumpSignalZ));
                /*****************************************************************/


                //                ui->l_bumpX->setText(QString::number((int)dummy.payload[7]));
                //                ui->l_bumpY->setText(QString::number((int)dummy.payload[8]));
                //                ui->l_bumpZ->setText(QString::number((int)dummy.payload[9]));
                //                QPointF p1(graph_index,dummy.payload[7]);
                //                QPointF p2(graph_index,dummy.payload[8]);
                //                QPointF p3(graph_index,dummy.payload[9]);
                //                if(p1.ry()>1000) p1.ry()=0;
                //                if(p2.ry()>1000) p2.ry()=0;
                //                if(p3.ry()>1000) p3.ry()=0;


                /*******************************************************************************
                 * Crea i grafici
                 *******************************************************************************/
                QPointF p1(graph_index,(int)bumpSignalX);
                QPointF p2(graph_index,(int)bumpSignalY);
                QPointF p3(graph_index,(int)bumpSignalZ);

                QPointF p4(graph_index,(int)automaticShakeTh);

                *series1 << p1;
                *series2 << p2;
                *series3 << p3;

                *series4 << p4;

                //graph_index = (graph_index + 1) % MAX_Y;
                graph_index = (graph_index + 1) % X_RANGE;

                if(graph_index == 0)
                {
                    series1->clear(); series2->clear(); series3->clear(); series4->clear();
                }
                /*******************************************************************************/

                /************************************************************
                 * se è stato clickato il pulsante START ACQUISITION
                 * (quindi acqRunningFlag=true)
                 ************************************************************/
                if(acqRunningFlag==true){

                    /***************************
                     * incrementa sampleIndex
                     ***************************/
                    sampleIndex++;
                    /***************************/


                    /*************************************************************
                     * aggiornamento progress bar
                     *************************************************************/
                    ui->progressBar->setValue( (sampleIndex/SAMPLES_NUM)*100 );
                    //qApp->processEvents(QEventLoop::AllEvents);
                    /*************************************************************/

                    /******************************************
                     * fa la somma dei campioni ricevuti
                     ******************************************/
                    SumXsamples = SumXsamples + bumpSignalX;
                    SumYsamples = SumYsamples + bumpSignalY;
                    SumZsamples = SumZsamples + bumpSignalZ;
                    /******************************************/

                    /*******************************************************
                     * una volta acquisiti tutti i campioni
                     *******************************************************/
                    if(sampleIndex==SAMPLES_NUM){

                        /****************************************
                         * mette a false il flag acqRunningFlag
                         * per indicare che la fase di
                         * acquisizione è terminata
                         ****************************************/
                        acqRunningFlag=false;
                        /****************************************/

                        /**********************************************
                         * calcola le medie
                         **********************************************/
                        double AvgXsamples = SumXsamples/SAMPLES_NUM;
                        double AvgYsamples = SumYsamples/SAMPLES_NUM;
                        double AvgZsamples = SumZsamples/SAMPLES_NUM;
                        /**********************************************/

                        /**********************************************
                         * ottiene il valore massimo delle medie
                         **********************************************/
                        double AvgMax = AvgXsamples;
                        if(AvgYsamples>AvgMax) AvgMax = AvgYsamples;
                        if(AvgZsamples>AvgMax) AvgMax = AvgZsamples;
                        /**********************************************/

                        /****************************************************************************
                         * calcola le soglie suggerite secondo il seguente
                         * principio:
                         * 1. la soglia delle vibrazioni è del shakeThPercent % più alta di AvgMax
                         * 2. la soglia degli urti è 3 volte la soglia delle vibrazioni
                         *****************************************************************************/
                        //double shakeThPercent = 250;
                        double bumpThPercent = 3*shakeThPercent;
                        double bumpThOffset = shakeThOffset;
                        double automaticBumpTh = lround(AvgMax+( (AvgMax*bumpThPercent/100) + bumpThOffset ) );
                        automaticShakeTh = lround(AvgMax+( (AvgMax*shakeThPercent/100) + shakeThOffset ) );
                        //double automaticBumpTh = 3*automaticShakeTh;
                        /*****************************************************************************/

                        /****************************************************************
                         * mostra sull'interfaccia i valori calcolati
                         ****************************************************************/
                        ui->l_suggBumpTh->setText(QString::number(automaticBumpTh));
                        ui->l_suggShakeTh->setText(QString::number(automaticShakeTh));
                        /****************************************************************/

                        /************************************
                         * azzera sampleIndex, SumXsamples,
                         * SumYsamples e SumZsamples
                         ************************************/
                        sampleIndex = 0;
                        SumXsamples = 0;
                        SumYsamples = 0;
                        SumZsamples = 0;
                        /************************************/

                        /************************************
                         * abilita il pulsante pB_startAcq
                         ************************************/
                        ui->label_19->setEnabled(true);
                        ui->lE_acqTime->setEnabled(true);
                        ui->pB_startAcq->setEnabled(true);
                        /************************************/

                        /*************************************
                         * Riabilita checkBox_RawData
                         *************************************/
                        ui->checkBox_RawData->setEnabled(true);
                        /*************************************/

                        /*************************************
                         * Riabilita pB_saveSuggested
                         *************************************/
                        ui->pB_saveSuggested->setEnabled(true);
                        ui->pB_saveSuggested->setVisible(true);
                        /*************************************/

                        /*************************************
                         * Riabilita pB_toolOptions
                         *************************************/
                        //ui->pB_toolOptions->setEnabled(true);
                        /*************************************/

                        /*************************************
                         * Riabilita pB_resetBumps
                         *************************************/
                        //ui->pB_resetBumps->setEnabled(true);
                        /*************************************/

                        /*************************************
                         * Riabilita lE_bumpsTh
                         *************************************/
                        //ui->lE_bumpsTh->setEnabled(true);
                        /*************************************/

                        /*************************************
                         * Riabilita pB_resetShakes
                         *************************************/
                        //ui->pB_resetShakes->setEnabled(true);
                        /*************************************/

                        /*************************************
                         * Riabilita lE_shakesTh
                         *************************************/
                        //ui->lE_shakesTh->setEnabled(true);
                        /*************************************/

                        /*********************************************
                         * Riabilita lE_shakesSamplingTime
                         *********************************************/
                        //ui->lE_shakesSamplingTime->setEnabled(true);
                        /*********************************************/

                        /*************************************
                         * Riabilita pB_setConfig
                         *************************************/
                        //ui->pB_setConfig->setEnabled(true);
                        /*************************************/

                        /*********************************************
                         * Riabilita radioButton_Automatic
                         *********************************************/
                        //ui->radioButton_Automatic->setEnabled(true);
                        /*********************************************/

                        /*********************************************
                         * Riabilita radioButton_Manual
                         *********************************************/
                        //ui->radioButton_Manual->setEnabled(true);
                        /*********************************************/

                        /*********************************************
                         * Riabilita rB_soft, rB_medium e rB_hard
                         *********************************************/
                        //ui->rB_soft->setEnabled(true);
                        //ui->rB_medium->setEnabled(true);
                        //ui->rB_hard->setEnabled(true);
                        /*********************************************/

                        /**********************************************
                         * Rende invisibile il pulsante pB_abortAcq
                         **********************************************/
                        ui->pB_abortAcq->setVisible(false);
                        /**********************************************/

                    }
                    /*******************************************************/



                } else {
                    /*******************************************
                     * mantiene azzerati sampleIndex,
                     * SumXsamples, SumYsamples e SumZsamples
                     *******************************************/
                    sampleIndex = 0;
                    SumXsamples = 0;
                    SumYsamples = 0;
                    SumZsamples = 0;
                    /*******************************************/
                }
                /************************************************************/


            }
            /*************************************************************************************/







            /**************************************************
             * Azzera il buffer receive_buffer
             * Azzera l'indice index_buffer
             * e continua
             **************************************************/
            memset(receive_buffer,0,sizeof(receive_buffer));
            index_buffer = 0;
            continue;
            /**************************************************/

        }

        /***********************************************************
         * Incrementa l'indice index_buffer
         ***********************************************************/
        index_buffer = (index_buffer + 1) % MAX_BUFFER_LENGHT;
        //index_buffer = (index_buffer + 1);
        /***********************************************************/

    }


}
/***************************************************************************************************/


/***************************************************************************************************
 * gesione errore
 ***************************************************************************************************/
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        qDebug()<< "SERIAL PORT ERROR" << m_serial_port->errorString();
        closeSerialPort();
    }
}
/***************************************************************************************************/

////void MainWindow::send_edge_limit()
////{
////    protocollo_uart send_pkt;
////    send_pkt.stx = STX_TAG;
////    send_pkt.cmd = (uint8_t)set_edge_level;
////    memcpy(send_pkt.payload,sensor_configuration,end_of_byte);
////    send_pkt.crc = crc_16((unsigned char *)&send_pkt.payload,sizeof(sensor_configuration));
////    send_pkt.etx = ETX_TAG;

////    int size_of_packet = sizeof(protocollo_uart);

////    writeData((const char *)&send_pkt, size_of_packet);
////}

/***************************************************************************************************
 * Funzione per la scrittura sulla seriale
 ***************************************************************************************************/
void MainWindow::writeData(const char *data, qint64 len)
{
    qint64 byte = m_serial_port->write(data,len);
    qDebug()<< " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BYTE SEND " << byte << QByteArray(QByteArray::fromRawData(data, len));
}
/***************************************************************************************************/

////void MainWindow::on_verticalSlider_limit_valueChanged(int value)
////{
////    sensor_configuration[conf_limit_value] = (uint16_t)value;
////    send_edge_limit();
////}


void MainWindow::on_pushButton_refresh_serial_clicked()
{
    ui->comboBox_serialport->clear();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        ui->comboBox_serialport->addItem(serialPortInfo.portName());
    }
}



void MainWindow::on_pB_setConfig_clicked()
{
    setConfigProcess();

    /**********************************
     * crea il file di log
     **********************************/
    createLogFile("TEMPORARY_SET");
    /**********************************/
}

void MainWindow::setConfigProcess() {
    /**************************************************
     * ferma il timer per il check delle vibrazioni
     **************************************************/
    shakesMonitorTimer->stop();
    qDebug()<<"shakesMonitorTimer stoppato";
    /*************************************************/


    /************************************************************
     * Ricava il valore di bumps threshold impostato
     * Se minore di 0 lo setta a 0
     ************************************************************/
    bumpsTH = ui->lE_bumpsTh->text().toDouble();
    if(bumpsTH<0){
        bumpsTH=0;
        ui->lE_bumpsTh->setText(QString::number(bumpsTH));
    }
    /************************************************************/

    /************************************************************
     * Ricava il valore di shake threshold impostato
     * Se minore di 0 lo setta a 0
     ************************************************************/
    shakesTH = ui->lE_shakesTh->text().toDouble();
    if(shakesTH<0){
        shakesTH=0;
        ui->lE_shakesTh->setText(QString::number(shakesTH));
    }
    /************************************************************/


    /************************************************************
     * Ricava il valore di shakesSamplingTime impostato
     * Se minore di 0 lo setta a 1
     ************************************************************/
    //    double shakesSamplingTime = ui->lE_shakesSamplingTime->text().toDouble();
    shakesSamplingTime = lround(ui->lE_shakesSamplingTime->text().toDouble()  );
    if(shakesSamplingTime<2){
        shakesSamplingTime=2;
        ui->lE_shakesSamplingTime->setText(QString::number(shakesSamplingTime));
    }
    /************************************************************/

    /***********************************************************
     * assegna shakesTH e shakesSamplingTime a due attributi da
     * passare al sensore attraverso setConfiguration()
     ***********************************************************/
    //sensor_configuration[1] = (uint16_t)shakesTH;
    //sensor_configuration[2] = (uint16_t)shakesSamplingTime;
    /***********************************************************/

    /*****************************************************************************************************
     * ricalcola shakesMonitorFunctionCounterLimit e azzera shakesMonitorFunctionCounter
     *****************************************************************************************************/
    shakesMonitorFunctionCounterLimit = lround(shakesSamplingTime*1000/shakesMonitorTimerPeriod);
    shakesMonitorFunctionCounter=0;
    /*****************************************************************************************************/

    /************************************************************
     * Ricava il valore di acceptableShakes dal campo
     ************************************************************/
    acceptableShakes = ui->lE_acceptableShakes->text().toInt();
    /************************************************************/

    /***************************************
     * Setta i parametri di configurazione
     ***************************************/
    setConfiguration();
    /***************************************/

    /********************************************************************
     * Resetta i contatori degli urti
     ********************************************************************/
    resetBumpCounters();
    /********************************************************************/

    /******************************************
     * resetta i contatori delle vibrazioni
     ******************************************/
    resetShakesCounters();
    /******************************************/


    //        /*********************************
    //         * PAUSA ?
    //         *********************************/
    //        unsigned long secs = 1;
    //        QThread::sleep(secs);
    //        /*********************************/

    /****************************************
     * Richiede i valori di configurazione
     ****************************************/
    getConfiguration();
    /****************************************/


    /**************************************************************************
     * Riavvia il timer per il check delle vibrazioni.
     * Sull'interfaccia viene passato il valore in secondi, il timer vuole
     * il parametro in millisecondi quindi è necessario moltiplicare per 1000
     **************************************************************************/
    if(shakesSamplingTime<=2) {shakesSamplingTime = 2; ui->lE_shakesSamplingTime->setText(QString::number((int)shakesSamplingTime));}
    //shakesMonitorTimer->start((int)shakesSamplingTime*1000);
    shakesMonitorTimer->start(shakesMonitorTimerPeriod);
    /**********************************/


    /********************************
     * update file Settings.3dc
     ********************************/
    updateSettingsFile();
    /********************************/


    qDebug()<<"shakesMonitorTimer riavviato";
    /**************************************************************************/

}

void MainWindow::setConfiguration()
{
    qDebug()<<"SET CONFIGURATION";

    protocollo_uart send_pkt;
    send_pkt.stx = STX_TAG;
    send_pkt.cmd = (uint8_t)setConfiguration_cmd;

    //send_pkt.payload[0]=(uint16_t)bumpsTH; //sensor_configuration[0];
    send_pkt.pay.bumpsThreshold=(uint16_t)bumpsTH; //sensor_configuration[0];
    //send_pkt.payload[1]=(uint16_t)shakesTH; //sensor_configuration[1];
    send_pkt.pay.shakesThreshold=(uint16_t)shakesTH; //sensor_configuration[1];
    //send_pkt.payload[2]=(uint16_t)shakesSamplingTime; //sensor_configuration[2];
    send_pkt.pay.shakesSamplingTime=(uint16_t)shakesSamplingTime; //sensor_configuration[2];
    //send_pkt.payload[3]=(uint16_t)shakesEventCounter; //sensor_configuration[3];
    send_pkt.pay.shakesCount=(uint16_t)shakesEventCounter; //sensor_configuration[3];
    //send_pkt.payload[4]=(uint16_t)shakesEventCounterX;
    send_pkt.pay.xShakesCount=(uint8_t)shakesEventCounterX;
    //send_pkt.payload[5]=(uint16_t)shakesEventCounterY;
    send_pkt.pay.yShakesCount=(uint8_t)shakesEventCounterY;
    //send_pkt.payload[6]=(uint16_t)shakesEventCounterZ;
    send_pkt.pay.zShakesCount=(uint8_t)shakesEventCounterZ;
    //send_pkt.payload[7]=(uint16_t)bumpSignalX;
    send_pkt.pay.output_X=(float)bumpSignalX;
    //send_pkt.payload[8]=(uint16_t)bumpSignalY;
    send_pkt.pay.output_Y=(float)bumpSignalY;
    //send_pkt.payload[9]=(uint16_t)bumpSignalZ;
    send_pkt.pay.output_Z=(float)bumpSignalZ;
    send_pkt.pay.hiddenBumpsThreshold=(uint16_t)hiddenBumpTh; //sensor_configuration[0];

    //send_pkt.crc = crc_16((unsigned char *)&send_pkt.payload,sizeof(send_pkt.payload));
    send_pkt.crc = crc_16((unsigned char *)&send_pkt.pay,sizeof(send_pkt.pay));
    send_pkt.etx = ETX_TAG;


    int size_of_packet = sizeof(protocollo_uart);

    writeData((const char *)&send_pkt, size_of_packet);

}

// ATTENZIONE: CALLBACK PER IL MOMENTO NON RICHIAMATA PERCHE' TASTO SAVE NASCOSTO
void MainWindow::on_pB_saveConfig_clicked()
{
    /**************************************************
     * ferma il timer per il check delle vibrazioni
     **************************************************/
    shakesMonitorTimer->stop();
    qDebug()<<"shakesMonitorTimer stoppato";
    /*************************************************/

    /************************************************************
     * Ricava il valore di bumps threshold impostato
     * Se minore di 0 lo setta a 0
     * Se maggiore di 500 lo setta a 500
     ************************************************************/
    bumpsTH = ui->lE_bumpsTh->text().toDouble();
    if(bumpsTH<0){
        bumpsTH=0;
        ui->lE_bumpsTh->setText(QString::number(bumpsTH));
    }
    //    if(bumpsTH>500){
    //        bumpsTH=500;
    //        ui->lE_bumpsTh->setText(QString::number(bumpsTH));
    //    }
    /************************************************************/


    /***********************************************************
     * assegna bumpsTH a un attributo da passare al sensore
     * attraverso setConfiguration()
     ***********************************************************/
    //    sensor_configuration[conf_limit_value] = (uint16_t)bumpsTH;
    //sensor_configuration[0] = (uint16_t)bumpsTH;
    /***********************************************************/


    /************************************************************
     * Ricava il valore di shake threshold impostato
     * Se minore di 0 lo setta a 0
     * Se maggiore di 500 lo setta a 500
     ************************************************************/
    shakesTH = ui->lE_shakesTh->text().toDouble();
    if(shakesTH<0){
        shakesTH=0;
        ui->lE_shakesTh->setText(QString::number(shakesTH));
    }
    //    if(shakesTH>500){
    //        shakesTH=500;
    //        ui->lE_shakesTh->setText(QString::number(shakesTH));
    //    }
    /************************************************************/


    /************************************************************
     * Ricava il valore di shakesSamplingTime impostato
     * Se minore di 0 lo setta a 0
     * Se maggiore di 50 lo setta a 50
     ************************************************************/
    //    double shakesSamplingTime = ui->lE_shakesSamplingTime->text().toDouble();
    shakesSamplingTime = lround(ui->lE_shakesSamplingTime->text().toDouble()  );
    if(shakesSamplingTime<2){
        shakesSamplingTime=2;
        ui->lE_shakesSamplingTime->setText(QString::number(shakesSamplingTime));
    }
    //    if(shakesSamplingTime>50){
    //        shakesSamplingTime=50;
    //        ui->lE_shakesSamplingTime->setText(QString::number(shakesSamplingTime));
    //    }
    /************************************************************/

    /***********************************************************
     * assegnare shakesTH a un attributo da passare al sensore
     * attraverso setConfiguration()
     ***********************************************************/
    //    sensor_configuration[conf_limit_value] = (uint16_t)bumpsTH;
    //sensor_configuration[1] = (uint16_t)shakesTH;
    //sensor_configuration[2] = (uint16_t)shakesSamplingTime;
    /***********************************************************/

    acceptableShakes = ui->lE_acceptableShakes->text().toInt();

    /***************************************
     * Salva i parametri di configurazione
     ***************************************/
    saveConfiguration();
    /***************************************/

    /************************************************************
     * Resetta i contatori degli urti
     ************************************************************/
    resetBumpCounters();
    /************************************************************/

    /******************************************
     * Resetta i contatori delle vibrazioni
     ******************************************/
    resetShakesCounters();
    /******************************************/


    /****************************************************************************
     * Riavvia il timer per il check delle vibrazioni
     * sull'interfaccia viene passato il valore in secondi, il timer vuole
     * il parametro in millisecondi quidni è necessario moltiplicare per 1000
     ****************************************************************************/
    if(shakesSamplingTime<=2) {shakesSamplingTime = 2; ui->lE_shakesSamplingTime->setText(QString::number((int)shakesSamplingTime));}
    //shakesMonitorTimer->start((int)shakesSamplingTime*1000);
    /**********************************
     * debug test
     **********************************/
    shakesMonitorTimer->start(shakesMonitorTimerPeriod);
    /**********************************/

    qDebug()<<"shakesMonitorTimer riavviato";
    /****************************************************************************/

}


/**********************************************************************************************
 * Funzione associata al timer il cui timeout è di 200ms
 **********************************************************************************************/
void MainWindow::shakesMonitorFunction(){

    if(shakesMonitorFunctionCounter==shakesMonitorFunctionCounterLimit){

        shakesMonitorFunctionCounter=0;

        qDebug()<<"shakesMonitorFunction";

        protocollo_uart send_pkt;
        send_pkt.stx = STX_TAG;
        send_pkt.cmd = (uint8_t)shake_monitor_cmd;

        //send_pkt.payload[0]=(uint16_t)bumpsTH; //sensor_configuration[0];
        send_pkt.pay.bumpsThreshold=(uint16_t)bumpsTH; //sensor_configuration[0];
        //send_pkt.payload[1]=(uint16_t)shakesTH; //sensor_configuration[1];
        send_pkt.pay.shakesThreshold=(uint16_t)shakesTH; //sensor_configuration[1];
        //send_pkt.payload[2]=(uint16_t)shakesSamplingTime; //sensor_configuration[2];
        send_pkt.pay.shakesSamplingTime=(uint16_t)shakesSamplingTime; //sensor_configuration[2];
        //send_pkt.payload[3]=(uint16_t)shakesEventCounter; //sensor_configuration[3];
        send_pkt.pay.shakesCount=(uint16_t)shakesEventCounter; //sensor_configuration[3];
        //send_pkt.payload[4]=0; //(uint16_t)shakesEventCounterX;
        send_pkt.pay.xShakesCount=0; //(uint16_t)shakesEventCounterX;
        //send_pkt.payload[5]=0; //(uint16_t)shakesEventCounterY;
        send_pkt.pay.yShakesCount=0; //(uint16_t)shakesEventCounterY;
        //send_pkt.payload[6]=0; //(uint16_t)shakesEventCounterZ;
        send_pkt.pay.zShakesCount=0; //(uint16_t)shakesEventCounterZ;
        //send_pkt.payload[7]=0; //(uint16_t)bumpSignalX;
        send_pkt.pay.output_X=0; //(uint16_t)bumpSignalX;
        //send_pkt.payload[8]=0; //(uint16_t)bumpSignalY;
        send_pkt.pay.output_Y=0; //(uint16_t)bumpSignalY;
        //send_pkt.payload[9]=0; //(uint16_t)bumpSignalZ;
        send_pkt.pay.output_Z=0; //(uint16_t)bumpSignalZ;
        send_pkt.pay.hiddenBumpsThreshold=0;

        //send_pkt.crc = crc_16((unsigned char *)&send_pkt.payload,sizeof(send_pkt.payload));
        send_pkt.crc = crc_16((unsigned char *)&send_pkt.pay,sizeof(send_pkt.pay));
        send_pkt.etx = ETX_TAG;

        int size_of_packet = sizeof(protocollo_uart);

        writeData((const char *)&send_pkt, size_of_packet);

    } else {

        shakesMonitorFunctionCounter++;

        //shakesMonitorFunctionCounter = (shakesMonitorFunctionCounter+1)%shakesMonitorFunctionCounterLimit;
        //        shakesMonitorFunctionCounter = (shakesMonitorFunctionCounter+1);
        if(shakesMonitorFunctionCounter>=shakesMonitorFunctionCounterLimit) shakesMonitorFunctionCounter=shakesMonitorFunctionCounterLimit;


        if(rawDataEnableFlag==true){
            qDebug()<<"getRawData_cmd";

            protocollo_uart send_pkt;
            send_pkt.stx = STX_TAG;
            send_pkt.cmd = (uint8_t)getRawData_cmd;

            //send_pkt.payload[0]=(uint16_t)bumpsTH; //sensor_configuration[0];
            send_pkt.pay.bumpsThreshold=(uint16_t)bumpsTH; //sensor_configuration[0];
            //send_pkt.payload[1]=(uint16_t)shakesTH; //sensor_configuration[1];
            send_pkt.pay.shakesThreshold=(uint16_t)shakesTH; //sensor_configuration[1];
            //send_pkt.payload[2]=(uint16_t)shakesSamplingTime; //sensor_configuration[2];
            send_pkt.pay.shakesSamplingTime=(uint16_t)shakesSamplingTime; //sensor_configuration[2];
            //send_pkt.payload[3]=(uint16_t)shakesEventCounter; //sensor_configuration[3];
            send_pkt.pay.shakesCount=(uint16_t)shakesEventCounter; //sensor_configuration[3];
            //send_pkt.payload[4]=0; //(uint16_t)shakesEventCounterX;
            send_pkt.pay.xShakesCount=0; //(uint16_t)shakesEventCounterX;
            //send_pkt.payload[5]=0; //(uint16_t)shakesEventCounterY;
            send_pkt.pay.yShakesCount=0; //(uint16_t)shakesEventCounterY;
            //send_pkt.payload[6]=0; //(uint16_t)shakesEventCounterZ;
            send_pkt.pay.zShakesCount=0; //(uint16_t)shakesEventCounterZ;
            //send_pkt.payload[7]=0; //(uint16_t)bumpSignalX;
            send_pkt.pay.output_X=0; //(uint16_t)bumpSignalX;
            //send_pkt.payload[8]=0; //(uint16_t)bumpSignalY;
            send_pkt.pay.output_Y=0; //(uint16_t)bumpSignalY;
            //send_pkt.payload[9]=0; //(uint16_t)bumpSignalZ;
            send_pkt.pay.output_Z=0; //(uint16_t)bumpSignalZ;
            send_pkt.pay.hiddenBumpsThreshold=0;

            //send_pkt.crc = crc_16((unsigned char *)&send_pkt.payload,sizeof(send_pkt.payload));
            send_pkt.crc = crc_16((unsigned char *)&send_pkt.pay,sizeof(send_pkt.pay));
            send_pkt.etx = ETX_TAG;

            int size_of_packet = sizeof(protocollo_uart);

            writeData((const char *)&send_pkt, size_of_packet);

        }
    }


}
/**********************************************************************************************/


void MainWindow::bumpFilterFunction(){
    /*******************************************
     * mette a false bumpFlag per indicare che
     * l'evento di urto è finito
     *******************************************/
    bumpFlag = false;
    /*******************************************/

    /*******************************************
     * stoppa il timer di filtraggio dei
     * "rimbalzi da urto"
     *******************************************/
    bumpTimer->stop();
    /*******************************************/

    /*******************************************
     * Disabilita il led
     ******************************************/
    ui->alarm_led->setEnabled(false);
    /******************************************/
    /**************************************************
     * Rende invisibile la label BUMP EVENT DETECTED
     **************************************************/
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    /**************************************************/
    /*************************************************
     * Rende invisibile la label Maximum Value Reached
     *************************************************/
    ui->label_24->setVisible(false);
    /*************************************************/
    gpiod_line_set_value(rele00, 0);
}


void MainWindow::saveConfiguration()
{
    protocollo_uart send_pkt;
    send_pkt.stx = STX_TAG;
    send_pkt.cmd = (uint8_t)saveConfiguration_cmd;
    //    memcpy(send_pkt.payload,sensor_configuration,end_of_byte);
    //memcpy(send_pkt.payload[conf_limit_value],sensor_configuration[conf_limit_value],end_of_byte);
    //    send_pkt.payload[conf_limit_value]=sensor_configuration[conf_limit_value];

    //send_pkt.payload[0]=(uint16_t)bumpsTH; //sensor_configuration[0];
    send_pkt.pay.bumpsThreshold=(uint16_t)bumpsTH; //sensor_configuration[0];
    //send_pkt.payload[1]=(uint16_t)shakesTH; //sensor_configuration[1];
    send_pkt.pay.shakesThreshold=(uint16_t)shakesTH; //sensor_configuration[1];
    //send_pkt.payload[2]=(uint16_t)shakesSamplingTime; //sensor_configuration[2];
    send_pkt.pay.shakesSamplingTime=(uint16_t)shakesSamplingTime; //sensor_configuration[2];
    //send_pkt.payload[3]=0; //(uint16_t)shakesEventCounter; //sensor_configuration[3];
    send_pkt.pay.shakesCount=0; //(uint16_t)shakesEventCounter; //sensor_configuration[3];
    //send_pkt.payload[4]=0; //(uint16_t)shakesEventCounterX;
    send_pkt.pay.xShakesCount=0; //(uint16_t)shakesEventCounterX;
    //send_pkt.payload[5]=0; //(uint16_t)shakesEventCounterY;
    send_pkt.pay.yShakesCount=0; //(uint16_t)shakesEventCounterY;
    //send_pkt.payload[6]=0; //(uint16_t)shakesEventCounterZ;
    send_pkt.pay.zShakesCount=0; //(uint16_t)shakesEventCounterZ;
    //send_pkt.payload[7]=0; //(uint16_t)bumpSignalX;
    send_pkt.pay.output_X=0; //(uint16_t)bumpSignalX;
    //send_pkt.payload[8]=0; //(uint16_t)bumpSignalY;
    send_pkt.pay.output_Y=0; //(uint16_t)bumpSignalY;
    //send_pkt.payload[9]=0; //(uint16_t)bumpSignalZ;
    send_pkt.pay.output_Z=0; //(uint16_t)bumpSignalZ;
    send_pkt.pay.hiddenBumpsThreshold=0;

    //send_pkt.crc = crc_16((unsigned char *)&send_pkt.payload,sizeof(send_pkt.payload));
    send_pkt.crc = crc_16((unsigned char *)&send_pkt.pay,sizeof(send_pkt.pay));
    send_pkt.etx = ETX_TAG;

    int size_of_packet = sizeof(protocollo_uart);

    writeData((const char *)&send_pkt, size_of_packet);

}


void MainWindow::getConfiguration()
{
    qDebug()<<"GET CONFIGURATION";

    protocollo_uart send_pkt;
    send_pkt.stx = STX_TAG;
    send_pkt.cmd = (uint8_t)getConfiguration_cmd;

    //send_pkt.payload[0]=0;
    send_pkt.pay.bumpsThreshold=0;
    //send_pkt.payload[1]=0;
    send_pkt.pay.shakesThreshold=0;
    //send_pkt.payload[2]=0;
    send_pkt.pay.shakesSamplingTime=0;
    //send_pkt.payload[3]=0;
    send_pkt.pay.shakesCount=0;
    //send_pkt.payload[4]=0;
    send_pkt.pay.xShakesCount=0;
    //send_pkt.payload[5]=0;
    send_pkt.pay.yShakesCount=0;
    //send_pkt.payload[6]=0;
    send_pkt.pay.zShakesCount=0;
    //send_pkt.payload[7]=0;
    send_pkt.pay.output_X=0;
    //send_pkt.payload[8]=0;
    send_pkt.pay.output_Y=0;
    //send_pkt.payload[9]=0;
    send_pkt.pay.output_Z=0;
    send_pkt.pay.hiddenBumpsThreshold=0;

    //send_pkt.crc = crc_16((unsigned char *)&send_pkt.payload,sizeof(send_pkt.payload));
    send_pkt.crc = crc_16((unsigned char *)&send_pkt.pay,sizeof(send_pkt.pay));
    send_pkt.etx = ETX_TAG;

    int size_of_packet = sizeof(protocollo_uart);

    writeData((const char *)&send_pkt, size_of_packet);

}


void MainWindow::on_pB_resetBumps_clicked()
{
    /***********************************
     * Resetta i contatori degli urti
     ***********************************/
    resetBumpCounters();
    /***********************************/
}

void MainWindow::resetBumpCounters(){
    /************************************************************
     * Resetta il contatore ed i valori dei segnali su X, Y e Z
     ************************************************************/
    bumpsEventCounter=0;
    ui->l_bumpsEvents->setText(QString::number(bumpsEventCounter));

    bumpSignalX=0;
    ui->l_bumpX->setText(QString::number(bumpSignalX));

    bumpSignalY=0;
    ui->l_bumpY->setText(QString::number(bumpSignalY));

    bumpSignalZ=0;
    ui->l_bumpZ->setText(QString::number(bumpSignalZ));
    /************************************************************/
}


void MainWindow::on_pB_resetShakes_clicked()
{
    /************************************************************
     * Resetta i contatori delle vibrazioni
     ************************************************************/
    resetShakesCounters();
    /************************************************************/
}

void MainWindow::resetShakesCounters()
{
    /************************************************************
     * Resetta i contatori delle vibrazioni
     ************************************************************/
    shakesEventCounter=0;
    ui->l_shakesEvents->setText(QString::number(shakesEventCounter));

    shakesEventCounterX=0;
    ui->l_AxisShakesX->setText(QString::number(shakesEventCounterX));

    shakesEventCounterY=0;
    ui->l_AxisShakesY->setText(QString::number(shakesEventCounterY));

    shakesEventCounterZ=0;
    ui->l_AxisShakesZ->setText(QString::number(shakesEventCounterZ));
    /************************************************************/
}


void MainWindow::on_pB_toolOptions_clicked()
{
    ToolOptions toolOptions;
    toolOptions.setModal(true);
    toolOptions.exec();

    /******************************************
     * legge _ToolOptions.3dc
     ******************************************/
    readToolOptionFile();
    /******************************************/

    /**********************************************************
     * setta bumpsTH e shakesTH in base al tool selezionato
     **********************************************************/
    //    int tool = ui->comboBox_toolSelection->currentIndex()+1;
    tool = ui->comboBox_toolSelection->currentIndex()+1;

    /*********************************************************
     * assegna le soglie in base al tool e al materiale
     *********************************************************/
    switch (tool)
    {
    case 1:
        toolDescription = toolDescription1;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh1;
            shakesTH =shakeTh1;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium1;
            shakesTH =shakeThmedium1;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard1;
            shakesTH =shakeThhard1;
        } else {
            bumpsTH = bumpsThmedium1;
            shakesTH =shakeThmedium1;
        }
        break;
    case 2:
        toolDescription = toolDescription2;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh2;
            shakesTH =shakeTh2;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium2;
            shakesTH =shakeThmedium2;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard2;
            shakesTH =shakeThhard2;
        } else {
            bumpsTH = bumpsThmedium2;
            shakesTH =shakeThmedium2;
        }
        break;
    case 3:
        toolDescription = toolDescription3;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh3;
            shakesTH =shakeTh3;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium3;
            shakesTH =shakeThmedium3;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard3;
            shakesTH =shakeThhard3;
        } else {
            bumpsTH = bumpsThmedium3;
            shakesTH =shakeThmedium3;
        }
        break;
    case 4:
        toolDescription = toolDescription4;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh4;
            shakesTH =shakeTh4;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium4;
            shakesTH =shakeThmedium4;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard4;
            shakesTH =shakeThhard4;
        } else {
            bumpsTH = bumpsThmedium4;
            shakesTH =shakeThmedium4;
        }
        break;
    case 5:
        toolDescription = toolDescription5;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh5;
            shakesTH =shakeTh5;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium5;
            shakesTH =shakeThmedium5;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard5;
            shakesTH =shakeThhard5;
        } else {
            bumpsTH = bumpsThmedium5;
            shakesTH =shakeThmedium5;
        }
        break;
    case 6:
        toolDescription = toolDescription6;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh6;
            shakesTH =shakeTh6;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium6;
            shakesTH =shakeThmedium6;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard6;
            shakesTH =shakeThhard6;
        } else {
            bumpsTH = bumpsThmedium6;
            shakesTH =shakeThmedium6;
        }
        break;
    case 7:
        toolDescription = toolDescription7;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh7;
            shakesTH =shakeTh7;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium7;
            shakesTH =shakeThmedium7;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard7;
            shakesTH =shakeThhard7;
        } else {
            bumpsTH = bumpsThmedium7;
            shakesTH =shakeThmedium7;
        }
        break;
    case 8:
        toolDescription = toolDescription8;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh8;
            shakesTH =shakeTh8;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium8;
            shakesTH =shakeThmedium8;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard8;
            shakesTH =shakeThhard8;
        } else {
            bumpsTH = bumpsThmedium8;
            shakesTH =shakeThmedium8;
        }
        break;
    case 9:
        toolDescription = toolDescription9;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh9;
            shakesTH =shakeTh9;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium9;
            shakesTH =shakeThmedium9;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard9;
            shakesTH =shakeThhard9;
        } else {
            bumpsTH = bumpsThmedium9;
            shakesTH =shakeThmedium9;
        }
        break;
    case 10:
        toolDescription = toolDescription10;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh10;
            shakesTH =shakeTh10;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium10;
            shakesTH =shakeThmedium10;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard10;
            shakesTH =shakeThhard10;
        } else {
            bumpsTH = bumpsThmedium10;
            shakesTH =shakeThmedium10;
        }
        break;
    case 11:
        toolDescription = toolDescription11;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh11;
            shakesTH =shakeTh11;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium11;
            shakesTH =shakeThmedium11;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard11;
            shakesTH =shakeThhard11;
        } else {
            bumpsTH = bumpsThmedium11;
            shakesTH =shakeThmedium11;
        }
        break;
    case 12:
        toolDescription = toolDescription12;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh12;
            shakesTH =shakeTh12;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium12;
            shakesTH =shakeThmedium12;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard12;
            shakesTH =shakeThhard12;
        } else {
            bumpsTH = bumpsThmedium12;
            shakesTH =shakeThmedium12;
        }
        break;
    case 13:
        toolDescription = toolDescription13;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh13;
            shakesTH =shakeTh13;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium13;
            shakesTH =shakeThmedium13;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard13;
            shakesTH =shakeThhard13;
        } else {
            bumpsTH = bumpsThmedium13;
            shakesTH =shakeThmedium13;
        }
        break;
    case 14:
        toolDescription = toolDescription14;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh14;
            shakesTH =shakeTh14;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium14;
            shakesTH =shakeThmedium14;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard14;
            shakesTH =shakeThhard14;
        } else {
            bumpsTH = bumpsThmedium14;
            shakesTH =shakeThmedium14;
        }
        break;
    case 15:
        toolDescription = toolDescription15;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh15;
            shakesTH =shakeTh15;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium15;
            shakesTH =shakeThmedium15;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard15;
            shakesTH =shakeThhard15;
        } else {
            bumpsTH = bumpsThmedium15;
            shakesTH =shakeThmedium15;
        }
        break;
    case 16:
        toolDescription = toolDescription16;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh16;
            shakesTH =shakeTh16;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium16;
            shakesTH =shakeThmedium16;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard16;
            shakesTH =shakeThhard16;
        } else {
            bumpsTH = bumpsThmedium16;
            shakesTH =shakeThmedium16;
        }
        break;
    case 17:
        toolDescription = toolDescription17;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh17;
            shakesTH =shakeTh17;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium17;
            shakesTH =shakeThmedium17;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard17;
            shakesTH =shakeThhard17;
        } else {
            bumpsTH = bumpsThmedium17;
            shakesTH =shakeThmedium17;
        }
        break;
    case 18:
        toolDescription = toolDescription18;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh18;
            shakesTH =shakeTh18;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium18;
            shakesTH =shakeThmedium18;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard18;
            shakesTH =shakeThhard18;
        } else {
            bumpsTH = bumpsThmedium18;
            shakesTH =shakeThmedium18;
        }
        break;
    case 19:
        toolDescription = toolDescription19;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh19;
            shakesTH =shakeTh19;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium19;
            shakesTH =shakeThmedium19;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard19;
            shakesTH =shakeThhard19;
        } else {
            bumpsTH = bumpsThmedium19;
            shakesTH =shakeThmedium19;
        }
        break;
    case 20:
        toolDescription = toolDescription20;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh20;
            shakesTH =shakeTh20;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium20;
            shakesTH =shakeThmedium20;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard20;
            shakesTH =shakeThhard20;
        } else {
            bumpsTH = bumpsThmedium20;
            shakesTH =shakeThmedium20;
        }
        break;
    case 21:
        toolDescription = toolDescription21;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh21;
            shakesTH =shakeTh21;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium21;
            shakesTH =shakeThmedium21;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard21;
            shakesTH =shakeThhard21;
        } else {
            bumpsTH = bumpsThmedium21;
            shakesTH =shakeThmedium21;
        }
        break;
    case 22:
        toolDescription = toolDescription22;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh22;
            shakesTH =shakeTh22;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium22;
            shakesTH =shakeThmedium22;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard22;
            shakesTH =shakeThhard22;
        } else {
            bumpsTH = bumpsThmedium22;
            shakesTH =shakeThmedium22;
        }
        break;
    case 23:
        toolDescription = toolDescription23;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh23;
            shakesTH =shakeTh23;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium23;
            shakesTH =shakeThmedium23;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard23;
            shakesTH =shakeThhard23;
        } else {
            bumpsTH = bumpsThmedium23;
            shakesTH =shakeThmedium23;
        }
        break;
    case 24:
        toolDescription = toolDescription24;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh24;
            shakesTH =shakeTh24;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium24;
            shakesTH =shakeThmedium24;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard24;
            shakesTH =shakeThhard24;
        } else {
            bumpsTH = bumpsThmedium24;
            shakesTH =shakeThmedium24;
        }
        break;
    case 25:
        toolDescription = toolDescription25;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh25;
            shakesTH =shakeTh25;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium25;
            shakesTH =shakeThmedium25;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard25;
            shakesTH =shakeThhard25;
        } else {
            bumpsTH = bumpsThmedium25;
            shakesTH =shakeThmedium25;
        }
        break;
    case 26:
        toolDescription = toolDescription26;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh26;
            shakesTH =shakeTh26;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium26;
            shakesTH =shakeThmedium26;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard26;
            shakesTH =shakeThhard26;
        } else {
            bumpsTH = bumpsThmedium26;
            shakesTH =shakeThmedium26;
        }
        break;
    case 27:
        toolDescription = toolDescription27;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh27;
            shakesTH =shakeTh27;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium27;
            shakesTH =shakeThmedium27;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard27;
            shakesTH =shakeThhard27;
        } else {
            bumpsTH = bumpsThmedium27;
            shakesTH =shakeThmedium27;
        }
        break;
    case 28:
        toolDescription = toolDescription28;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh28;
            shakesTH =shakeTh28;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium28;
            shakesTH =shakeThmedium28;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard28;
            shakesTH =shakeThhard28;
        } else {
            bumpsTH = bumpsThmedium28;
            shakesTH =shakeThmedium28;
        }
        break;
    case 29:
        toolDescription = toolDescription29;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh29;
            shakesTH =shakeTh29;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium29;
            shakesTH =shakeThmedium29;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard29;
            shakesTH =shakeThhard29;
        } else {
            bumpsTH = bumpsThmedium29;
            shakesTH =shakeThmedium29;
        }
        break;
    case 30:
        toolDescription = toolDescription30;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh30;
            shakesTH =shakeTh30;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium30;
            shakesTH =shakeThmedium30;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard30;
            shakesTH =shakeThhard30;
        } else {
            bumpsTH = bumpsThmedium30;
            shakesTH =shakeThmedium30;
        }
        break;
    case 31:
        toolDescription = toolDescription31;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh31;
            shakesTH =shakeTh31;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium31;
            shakesTH =shakeThmedium31;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard31;
            shakesTH =shakeThhard31;
        } else {
            bumpsTH = bumpsThmedium31;
            shakesTH =shakeThmedium31;
        }
        break;
    case 32:
        toolDescription = toolDescription32;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh32;
            shakesTH =shakeTh32;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium32;
            shakesTH =shakeThmedium32;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard32;
            shakesTH =shakeThhard32;
        } else {
            bumpsTH = bumpsThmedium32;
            shakesTH =shakeThmedium32;
        }
        break;

    default:
        toolDescription = toolDescription1;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh1;
            shakesTH =shakeTh1;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium1;
            shakesTH =shakeThmedium1;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard1;
            shakesTH =shakeThhard1;
        } else {
            bumpsTH = bumpsThmedium1;
            shakesTH =shakeThmedium1;
        }
        break;
    }
    /*********************************************************/

    /*******************************************************************************
     * aggiorna i campi tool description, bumpsTH, shakesTH e shakesSamplingTime
     *******************************************************************************/
    ui->l_toolDescription->setText(toolDescription);
    ui->lE_bumpsTh->setText(QString::number((int)bumpsTH));
    ui->lE_shakesTh->setText(QString::number((int)shakesTH));
    ui->lE_shakesSamplingTime->setText(QString::number((int)shakesSamplingTime));
    /*******************************************************************************/

    /****************************************************************
     * Resetta il contatore ed i valori dei segnali su X, Y e Z
     ****************************************************************/
    resetBumpCounters();
    /****************************************************************/

    /****************************************************************
     * Resetta i contatori delle vibrazioni
     ****************************************************************/
    resetShakesCounters();
    /****************************************************************/


    /***************************************
     * Setta i parametri di configurazione
     ***************************************/
    setConfiguration();
    /***************************************/

    /***********************
     * PAUSA
     ***********************/
    //    unsigned long secs = 1;
    //    QThread::sleep(secs);
    /***********************/

    /****************************************
     * Richiede i valori di configurazione
     ****************************************/
    getConfiguration();
    /****************************************/


}


void MainWindow::on_comboBox_toolSelection_currentIndexChanged(int index)
{
    /*********************************
     * individua il tool selezionato
     *********************************/
    //    int tool = index+1;
    tool = index+1;
    /*********************************/

    /*********************************************************
     * assegna le soglie in base al tool e al materiale
     *********************************************************/
    switch (tool)
    {
    case 1:
        toolDescription = toolDescription1;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh1;
            shakesTH =shakeTh1;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium1;
            shakesTH =shakeThmedium1;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard1;
            shakesTH =shakeThhard1;
        } else {
            bumpsTH = bumpsThmedium1;
            shakesTH =shakeThmedium1;
        }
        break;
    case 2:
        toolDescription = toolDescription2;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh2;
            shakesTH =shakeTh2;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium2;
            shakesTH =shakeThmedium2;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard2;
            shakesTH =shakeThhard2;
        } else {
            bumpsTH = bumpsThmedium2;
            shakesTH =shakeThmedium2;
        }
        break;
    case 3:
        toolDescription = toolDescription3;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh3;
            shakesTH =shakeTh3;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium3;
            shakesTH =shakeThmedium3;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard3;
            shakesTH =shakeThhard3;
        } else {
            bumpsTH = bumpsThmedium3;
            shakesTH =shakeThmedium3;
        }
        break;
    case 4:
        toolDescription = toolDescription4;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh4;
            shakesTH =shakeTh4;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium4;
            shakesTH =shakeThmedium4;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard4;
            shakesTH =shakeThhard4;
        } else {
            bumpsTH = bumpsThmedium4;
            shakesTH =shakeThmedium4;
        }
        break;
    case 5:
        toolDescription = toolDescription5;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh5;
            shakesTH =shakeTh5;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium5;
            shakesTH =shakeThmedium5;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard5;
            shakesTH =shakeThhard5;
        } else {
            bumpsTH = bumpsThmedium5;
            shakesTH =shakeThmedium5;
        }
        break;
    case 6:
        toolDescription = toolDescription6;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh6;
            shakesTH =shakeTh6;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium6;
            shakesTH =shakeThmedium6;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard6;
            shakesTH =shakeThhard6;
        } else {
            bumpsTH = bumpsThmedium6;
            shakesTH =shakeThmedium6;
        }
        break;
    case 7:
        toolDescription = toolDescription7;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh7;
            shakesTH =shakeTh7;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium7;
            shakesTH =shakeThmedium7;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard7;
            shakesTH =shakeThhard7;
        } else {
            bumpsTH = bumpsThmedium7;
            shakesTH =shakeThmedium7;
        }
        break;
    case 8:
        toolDescription = toolDescription8;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh8;
            shakesTH =shakeTh8;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium8;
            shakesTH =shakeThmedium8;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard8;
            shakesTH =shakeThhard8;
        } else {
            bumpsTH = bumpsThmedium8;
            shakesTH =shakeThmedium8;
        }
        break;
    case 9:
        toolDescription = toolDescription9;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh9;
            shakesTH =shakeTh9;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium9;
            shakesTH =shakeThmedium9;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard9;
            shakesTH =shakeThhard9;
        } else {
            bumpsTH = bumpsThmedium9;
            shakesTH =shakeThmedium9;
        }
        break;
    case 10:
        toolDescription = toolDescription10;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh10;
            shakesTH =shakeTh10;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium10;
            shakesTH =shakeThmedium10;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard10;
            shakesTH =shakeThhard10;
        } else {
            bumpsTH = bumpsThmedium10;
            shakesTH =shakeThmedium10;
        }
        break;
    case 11:
        toolDescription = toolDescription11;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh11;
            shakesTH =shakeTh11;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium11;
            shakesTH =shakeThmedium11;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard11;
            shakesTH =shakeThhard11;
        } else {
            bumpsTH = bumpsThmedium11;
            shakesTH =shakeThmedium11;
        }
        break;
    case 12:
        toolDescription = toolDescription12;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh12;
            shakesTH =shakeTh12;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium12;
            shakesTH =shakeThmedium12;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard12;
            shakesTH =shakeThhard12;
        } else {
            bumpsTH = bumpsThmedium12;
            shakesTH =shakeThmedium12;
        }
        break;
    case 13:
        toolDescription = toolDescription13;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh13;
            shakesTH =shakeTh13;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium13;
            shakesTH =shakeThmedium13;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard13;
            shakesTH =shakeThhard13;
        } else {
            bumpsTH = bumpsThmedium13;
            shakesTH =shakeThmedium13;
        }
        break;
    case 14:
        toolDescription = toolDescription14;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh14;
            shakesTH =shakeTh14;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium14;
            shakesTH =shakeThmedium14;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard14;
            shakesTH =shakeThhard14;
        } else {
            bumpsTH = bumpsThmedium14;
            shakesTH =shakeThmedium14;
        }
        break;
    case 15:
        toolDescription = toolDescription15;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh15;
            shakesTH =shakeTh15;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium15;
            shakesTH =shakeThmedium15;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard15;
            shakesTH =shakeThhard15;
        } else {
            bumpsTH = bumpsThmedium15;
            shakesTH =shakeThmedium15;
        }
        break;
    case 16:
        toolDescription = toolDescription16;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh16;
            shakesTH =shakeTh16;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium16;
            shakesTH =shakeThmedium16;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard16;
            shakesTH =shakeThhard16;
        } else {
            bumpsTH = bumpsThmedium16;
            shakesTH =shakeThmedium16;
        }
        break;
    case 17:
        toolDescription = toolDescription17;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh17;
            shakesTH =shakeTh17;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium17;
            shakesTH =shakeThmedium17;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard17;
            shakesTH =shakeThhard17;
        } else {
            bumpsTH = bumpsThmedium17;
            shakesTH =shakeThmedium17;
        }
        break;
    case 18:
        toolDescription = toolDescription18;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh18;
            shakesTH =shakeTh18;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium18;
            shakesTH =shakeThmedium18;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard18;
            shakesTH =shakeThhard18;
        } else {
            bumpsTH = bumpsThmedium18;
            shakesTH =shakeThmedium18;
        }
        break;
    case 19:
        toolDescription = toolDescription19;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh19;
            shakesTH =shakeTh19;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium19;
            shakesTH =shakeThmedium19;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard19;
            shakesTH =shakeThhard19;
        } else {
            bumpsTH = bumpsThmedium19;
            shakesTH =shakeThmedium19;
        }
        break;
    case 20:
        toolDescription = toolDescription20;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh20;
            shakesTH =shakeTh20;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium20;
            shakesTH =shakeThmedium20;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard20;
            shakesTH =shakeThhard20;
        } else {
            bumpsTH = bumpsThmedium20;
            shakesTH =shakeThmedium20;
        }
        break;
    case 21:
        toolDescription = toolDescription21;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh21;
            shakesTH =shakeTh21;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium21;
            shakesTH =shakeThmedium21;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard21;
            shakesTH =shakeThhard21;
        } else {
            bumpsTH = bumpsThmedium21;
            shakesTH =shakeThmedium21;
        }
        break;
    case 22:
        toolDescription = toolDescription22;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh22;
            shakesTH =shakeTh22;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium22;
            shakesTH =shakeThmedium22;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard22;
            shakesTH =shakeThhard22;
        } else {
            bumpsTH = bumpsThmedium22;
            shakesTH =shakeThmedium22;
        }
        break;
    case 23:
        toolDescription = toolDescription23;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh23;
            shakesTH =shakeTh23;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium23;
            shakesTH =shakeThmedium23;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard23;
            shakesTH =shakeThhard23;
        } else {
            bumpsTH = bumpsThmedium23;
            shakesTH =shakeThmedium23;
        }
        break;
    case 24:
        toolDescription = toolDescription24;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh24;
            shakesTH =shakeTh24;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium24;
            shakesTH =shakeThmedium24;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard24;
            shakesTH =shakeThhard24;
        } else {
            bumpsTH = bumpsThmedium24;
            shakesTH =shakeThmedium24;
        }
        break;
    case 25:
        toolDescription = toolDescription25;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh25;
            shakesTH =shakeTh25;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium25;
            shakesTH =shakeThmedium25;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard25;
            shakesTH =shakeThhard25;
        } else {
            bumpsTH = bumpsThmedium25;
            shakesTH =shakeThmedium25;
        }
        break;
    case 26:
        toolDescription = toolDescription26;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh26;
            shakesTH =shakeTh26;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium26;
            shakesTH =shakeThmedium26;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard26;
            shakesTH =shakeThhard26;
        } else {
            bumpsTH = bumpsThmedium26;
            shakesTH =shakeThmedium26;
        }
        break;
    case 27:
        toolDescription = toolDescription27;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh27;
            shakesTH =shakeTh27;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium27;
            shakesTH =shakeThmedium27;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard27;
            shakesTH =shakeThhard27;
        } else {
            bumpsTH = bumpsThmedium27;
            shakesTH =shakeThmedium27;
        }
        break;
    case 28:
        toolDescription = toolDescription28;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh28;
            shakesTH =shakeTh28;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium28;
            shakesTH =shakeThmedium28;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard28;
            shakesTH =shakeThhard28;
        } else {
            bumpsTH = bumpsThmedium28;
            shakesTH =shakeThmedium28;
        }
        break;
    case 29:
        toolDescription = toolDescription29;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh29;
            shakesTH =shakeTh29;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium29;
            shakesTH =shakeThmedium29;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard29;
            shakesTH =shakeThhard29;
        } else {
            bumpsTH = bumpsThmedium29;
            shakesTH =shakeThmedium29;
        }
        break;
    case 30:
        toolDescription = toolDescription30;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh30;
            shakesTH =shakeTh30;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium30;
            shakesTH =shakeThmedium30;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard30;
            shakesTH =shakeThhard30;
        } else {
            bumpsTH = bumpsThmedium30;
            shakesTH =shakeThmedium30;
        }
        break;
    case 31:
        toolDescription = toolDescription31;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh31;
            shakesTH =shakeTh31;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium31;
            shakesTH =shakeThmedium31;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard31;
            shakesTH =shakeThhard31;
        } else {
            bumpsTH = bumpsThmedium31;
            shakesTH =shakeThmedium31;
        }
        break;
    case 32:
        toolDescription = toolDescription32;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh32;
            shakesTH =shakeTh32;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium32;
            shakesTH =shakeThmedium32;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard32;
            shakesTH =shakeThhard32;
        } else {
            bumpsTH = bumpsThmedium32;
            shakesTH =shakeThmedium32;
        }
        break;

    default:
        toolDescription = toolDescription1;
        if(materialType=="Soft"){
            bumpsTH = bumpsTh1;
            shakesTH =shakeTh1;
        } else if(materialType=="Medium"){
            bumpsTH = bumpsThmedium1;
            shakesTH =shakeThmedium1;
        } else if(materialType=="Hard"){
            bumpsTH = bumpsThhard1;
            shakesTH =shakeThhard1;
        } else {
            bumpsTH = bumpsThmedium1;
            shakesTH =shakeThmedium1;
        }
        break;
    }
    /*********************************************************/


    /********************************************************
     * aggiorna il file Settings.3dc
     ********************************************************/
    updateSettingsFile();
    /********************************************************/

    /*******************************************************************************
     * aggiorna i campi tool description, bumpsTH, shakesTH e shakesSamplingTime
     *******************************************************************************/
    ui->l_toolDescription->setText(toolDescription);
    ui->lE_bumpsTh->setText(QString::number((int)bumpsTH));
    ui->lE_shakesTh->setText(QString::number((int)shakesTH));
    ui->lE_shakesSamplingTime->setText(QString::number((int)shakesSamplingTime));
    /*******************************************************************************/

    /************************************
     * Resetta i contatori degli urti
     ************************************/
    resetBumpCounters();
    /************************************/

    /******************************************
     * Resetta i contatori delle vibrazioni
     ******************************************/
    resetShakesCounters();
    /******************************************/


    if(firstChange==false){
        /***************************************
         * Setta i parametri di configurazione
         ***************************************/
        setConfiguration();
        /***************************************/

        /***********************
         * PAUSA
         ***********************/
        //    unsigned long secs = 1;
        //    QThread::sleep(secs);
        /***********************/

        /****************************************
         * Richiede i valori di configurazione
         ****************************************/
        getConfiguration();
        /****************************************/


        /******************************************
         * crea il file di log
         ******************************************/
        createLogFile("TOOL_CHANGE");
        /******************************************/

    }


    firstChange=false;

}


void MainWindow::on_checkBox_RawData_stateChanged(int checkState)
{
    if(checkState == Qt::Unchecked){
        qDebug()<<"Raw Data Check Box Unchecked";

        /**************************************
         * mette a false rawDataEnableFlag
         * per disabilitare il getRawData_cmd
         **************************************/
        rawDataEnableFlag = false;
        /**************************************/

        /***********************************************
         * abilita i widget da abilitare
         ***********************************************/
        ui->radioButton_Manual->setEnabled(true);
        ui->radioButton_Automatic->setEnabled(true);
        ui->comboBox_toolSelection->setEnabled(true);
        ui->pB_toolOptions->setEnabled(true);
        ui->pB_hiddenBumpTh->setEnabled(true);
        ui->rB_soft->setEnabled(true);
        ui->rB_medium->setEnabled(true);
        ui->rB_hard->setEnabled(true);
        ui->lE_bumpsTh->setEnabled(true);
        ui->lE_shakesTh->setEnabled(true);
        ui->lE_shakesSamplingTime->setEnabled(true);
        ui->lE_acceptableShakes->setEnabled(true);
        ui->pB_resetBumps->setEnabled(true);
        ui->pB_resetShakes->setEnabled(true);
        ui->pB_setConfig->setEnabled(true);
        /***********************************************/

        /**************************************
         * Rende invisibili i valori degli assi
         **************************************/
        ui->label_14->setEnabled(false);
        ui->l_bumpX->setEnabled(false);
        ui->label_15->setEnabled(false);
        ui->l_bumpY->setEnabled(false);
        ui->label_16->setEnabled(false);
        ui->l_bumpZ->setEnabled(false);
        /**************************************/

        /********************************************
         * Rende invisibile il pusante Show Graphic
         ********************************************/
        ui->label_19->setEnabled(false);
        ui->lE_acqTime->setEnabled(false);
        ui->pB_startAcq->setEnabled(false);
        /********************************************/

        /**************************************
         * disabilita i valori degli assi
         **************************************/
        ui->label_2->setEnabled(false);
        ui->label_18->setEnabled(false);
        ui->l_suggBumpTh->setEnabled(false);

        ui->label_20->setEnabled(false);
        ui->label_21->setEnabled(false);
        ui->l_suggShakeTh->setEnabled(false);

        ui->pB_saveSuggested->setEnabled(false);
        /**************************************/

        /************************************************
         * Rende invisibili la progress bar,
         * il pulsante di arresto autoapprendimento e
         * il pulsante pB_saveSuggested
         ************************************************/
        ui->progressBar->setVisible(false);
        ui->pB_abortAcq->setVisible(false);
        ui->pB_saveSuggested->setVisible(false);
        /************************************************/

    }else if(checkState == Qt::Checked){
        qDebug()<<"Raw Data Check Box Checked";

        /**************************************
         * mette a true rawDataEnableFlag
         * per abilitare il getRawData_cmd
         **************************************/
        rawDataEnableFlag = true;
        /**************************************/

        /***********************************************
         * disabilita i widget da disabilitare
         ***********************************************/
        ui->radioButton_Manual->setEnabled(false);
        ui->radioButton_Automatic->setEnabled(false);
        ui->comboBox_toolSelection->setEnabled(false);
        ui->pB_toolOptions->setEnabled(false);
        ui->pB_hiddenBumpTh->setEnabled(false);
        ui->rB_soft->setEnabled(false);
        ui->rB_medium->setEnabled(false);
        ui->rB_hard->setEnabled(false);
        ui->lE_bumpsTh->setEnabled(false);
        ui->lE_shakesTh->setEnabled(false);
        ui->lE_shakesSamplingTime->setEnabled(false);
        ui->lE_acceptableShakes->setEnabled(false);
        ui->pB_resetBumps->setEnabled(false);
        ui->pB_resetShakes->setEnabled(false);
        ui->pB_setConfig->setEnabled(false);
        /***********************************************/

        /**************************************
         * Rende visibili i valori degli assi
         **************************************/
        ui->label_14->setEnabled(true);
        ui->l_bumpX->setEnabled(true);
        ui->label_15->setEnabled(true);
        ui->l_bumpY->setEnabled(true);
        ui->label_16->setEnabled(true);
        ui->l_bumpZ->setEnabled(true);
        /**************************************/

        /********************************************
         * abilita il pusante START ACQUISITION
         ********************************************/
        ui->label_19->setEnabled(true);
        ui->lE_acqTime->setEnabled(true);
        ui->pB_startAcq->setEnabled(true);
        /********************************************/

        /**************************************
         * disabilita i valori degli assi
         **************************************/
        ui->label_2->setEnabled(true);
        ui->label_18->setEnabled(true);
        ui->l_suggBumpTh->setEnabled(true);

        ui->label_20->setEnabled(true);
        ui->label_21->setEnabled(true);
        ui->l_suggShakeTh->setEnabled(true);

        //ui->pB_saveSuggested->setEnabled(true);
        /**************************************/

    }


}


void MainWindow::on_pB_startAcq_clicked()
{

    /***************************************************************
     * calcola il SAMPLES_NUM in base al tempo di acquisizione
     * impostato dall'utente. Tempo di aquisizione minmo 5s;
     * Tempo di acquisizione massimo 1h (3600s)
     ***************************************************************/
    double acqTime = lround(ui->lE_acqTime->text().toDouble()  );
    if(acqTime<=5){
        acqTime=5;
        ui->lE_acqTime->setText(QString::number((int)acqTime));
    }
    if(acqTime>=3600){
        acqTime=3600;
        ui->lE_acqTime->setText(QString::number((int)acqTime));
    }
    SAMPLES_NUM = lround(acqTime/shakesMonitorTimerPeriod*1000);
    /***************************************************************/

    /******************************************
     * mette a true il flag acqRunningFlag
     ******************************************/
    acqRunningFlag = true;
    /******************************************/

    /*********************************************
     * disabilita la checkBox_RawData per non
     * disabilirare l'acquisizione dei raw data
     * durante il calcolo
     *********************************************/
    ui->checkBox_RawData->setEnabled(false);
    /*********************************************/

    /****************************************
     * Disabilita pB_saveSuggested
     ****************************************/
    ui->pB_saveSuggested->setEnabled(false);
    /****************************************/

    /*************************************
     * Disabilita pB_toolOptions
     *************************************/
    //ui->pB_toolOptions->setEnabled(false);
    /*************************************/

    /*************************************
     * Disabilita pB_resetBumps
     *************************************/
    //ui->pB_resetBumps->setEnabled(false);
    /*************************************/

    /*************************************
     * Disabilita lE_bumpsTh
     *************************************/
    //ui->lE_bumpsTh->setEnabled(false);
    /*************************************/

    /*************************************
     * Disabilita pB_resetShakes
     *************************************/
    //ui->pB_resetShakes->setEnabled(false);
    /*************************************/

    /*************************************
     * Disabilita lE_shakesTh
     *************************************/
    //ui->lE_shakesTh->setEnabled(false);
    /*************************************/

    /*********************************************
     * Disabilita lE_shakesSamplingTime
     *********************************************/
    //ui->lE_shakesSamplingTime->setEnabled(false);
    /*********************************************/

    /*************************************
     * Disabilita pB_setConfig
     *************************************/
    //ui->pB_setConfig->setEnabled(false);
    /*************************************/

    /*********************************************
     * Disabilita radioButton_Automatic
     *********************************************/
    //ui->radioButton_Automatic->setEnabled(false);
    /*********************************************/

    /*********************************************
     * Disabilita radioButton_Manual
     *********************************************/
    //ui->radioButton_Manual->setEnabled(false);
    /*********************************************/

    /*********************************************
     * Disabilita rB_soft, rB_medium e rB_hard
     *********************************************/
    //ui->rB_soft->setEnabled(false);
    //ui->rB_medium->setEnabled(false);
    //ui->rB_hard->setEnabled(false);
    /*********************************************/

    /*************************************************
     * Disabilita comboBox_toolSelection se il
     * sistema è in modalità MANUALE
     *************************************************/
    //if( ui->radioButton_Manual->isChecked() ){
    //    ui->comboBox_toolSelection->setEnabled(false);
    //}
    /*************************************************/

    /*********************************************
     * disabilita il pulsante per
     * non far partire una seconda acquisizione
     *********************************************/
    ui->label_19->setEnabled(false);
    ui->lE_acqTime->setEnabled(false);
    ui->pB_startAcq->setEnabled(false);
    /*********************************************/

    /****************************************************************
     * mostra sull'interfaccia che si sta calcolando i valori
     ****************************************************************/
    ui->l_suggBumpTh->setText("Calculating");
    ui->l_suggShakeTh->setText("Calculating");
    /****************************************************************/

    /************************************************
     * Rende visibili la progress bar
     * ed il pulsante di arresto autoapprendimento
     ************************************************/
    ui->progressBar->setVisible(true);
    ui->pB_abortAcq->setVisible(true);
    /************************************************/

}


void MainWindow::on_pB_saveSuggested_clicked()
{
    /**************************************************************************************
     * Se non sono presenti dati validi non salva
     **************************************************************************************/
    if((ui->l_suggBumpTh->text()!="N/A") && (ui->l_suggShakeTh->text()!="N/A") ){

        /**************************************************
         * assegna le soglie al tool corrente
         **************************************************/
        switch (tool)
        {
        case 1:
            toolDescription = toolDescription1;
            if(materialType=="Soft"){
                bumpsTh1 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh1 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh1;
                shakesTH =shakeTh1;
            } else if(materialType=="Medium"){
                bumpsThmedium1 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium1 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium1;
                shakesTH =shakeThmedium1;
            } else if(materialType=="Hard"){
                bumpsThhard1 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard1 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard1;
                shakesTH =shakeThhard1;
            } else {
                bumpsTH = bumpsThmedium1;
                shakesTH =shakeThmedium1;
            }
            break;
        case 2:
            toolDescription = toolDescription2;
            if(materialType=="Soft"){
                bumpsTh2 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh2 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh2;
                shakesTH =shakeTh2;
            } else if(materialType=="Medium"){
                bumpsThmedium2 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium2 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium2;
                shakesTH =shakeThmedium2;
            } else if(materialType=="Hard"){
                bumpsThhard2 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard2 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard2;
                shakesTH =shakeThhard2;
            } else {
                bumpsTH = bumpsThmedium2;
                shakesTH =shakeThmedium2;
            }
            break;
        case 3:
            toolDescription = toolDescription3;
            if(materialType=="Soft"){
                bumpsTh3 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh3 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh3;
                shakesTH =shakeTh3;
            } else if(materialType=="Medium"){
                bumpsThmedium3 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium3 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium3;
                shakesTH =shakeThmedium3;
            } else if(materialType=="Hard"){
                bumpsThhard3 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard3 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard3;
                shakesTH =shakeThhard3;
            } else {
                bumpsTH = bumpsThmedium3;
                shakesTH =shakeThmedium3;
            }
            break;
        case 4:
            toolDescription = toolDescription4;
            if(materialType=="Soft"){
                bumpsTh4 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh4 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh4;
                shakesTH =shakeTh4;
            } else if(materialType=="Medium"){
                bumpsThmedium4 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium4 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium4;
                shakesTH =shakeThmedium4;
            } else if(materialType=="Hard"){
                bumpsThhard4 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard4 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard4;
                shakesTH =shakeThhard4;
            } else {
                bumpsTH = bumpsThmedium4;
                shakesTH =shakeThmedium4;
            }
            break;
        case 5:
            toolDescription = toolDescription5;
            if(materialType=="Soft"){
                bumpsTh5 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh5 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh5;
                shakesTH =shakeTh5;
            } else if(materialType=="Medium"){
                bumpsThmedium5 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium5 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium5;
                shakesTH =shakeThmedium5;
            } else if(materialType=="Hard"){
                bumpsThhard5 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard5 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard5;
                shakesTH =shakeThhard5;
            } else {
                bumpsTH = bumpsThmedium5;
                shakesTH =shakeThmedium5;
            }
            break;
        case 6:
            toolDescription = toolDescription6;
            if(materialType=="Soft"){
                bumpsTh6 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh6 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh6;
                shakesTH =shakeTh6;
            } else if(materialType=="Medium"){
                bumpsThmedium6 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium6 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium6;
                shakesTH =shakeThmedium6;
            } else if(materialType=="Hard"){
                bumpsThhard6 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard6 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard6;
                shakesTH =shakeThhard6;
            } else {
                bumpsTH = bumpsThmedium6;
                shakesTH =shakeThmedium6;
            }
            break;
        case 7:
            toolDescription = toolDescription7;
            if(materialType=="Soft"){
                bumpsTh7 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh7 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh7;
                shakesTH =shakeTh7;
            } else if(materialType=="Medium"){
                bumpsThmedium7 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium7 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium7;
                shakesTH =shakeThmedium7;
            } else if(materialType=="Hard"){
                bumpsThhard7 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard7 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard7;
                shakesTH =shakeThhard7;
            } else {
                bumpsTH = bumpsThmedium7;
                shakesTH =shakeThmedium7;
            }
            break;
        case 8:
            toolDescription = toolDescription8;
            if(materialType=="Soft"){
                bumpsTh8 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh8 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh8;
                shakesTH =shakeTh8;
            } else if(materialType=="Medium"){
                bumpsThmedium8 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium8 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium8;
                shakesTH =shakeThmedium8;
            } else if(materialType=="Hard"){
                bumpsThhard8 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard8 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard8;
                shakesTH =shakeThhard8;
            } else {
                bumpsTH = bumpsThmedium8;
                shakesTH =shakeThmedium8;
            }
            break;
        case 9:
            toolDescription = toolDescription9;
            if(materialType=="Soft"){
                bumpsTh9 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh9 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh9;
                shakesTH =shakeTh9;
            } else if(materialType=="Medium"){
                bumpsThmedium9 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium9 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium9;
                shakesTH =shakeThmedium9;
            } else if(materialType=="Hard"){
                bumpsThhard9 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard9 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard9;
                shakesTH =shakeThhard9;
            } else {
                bumpsTH = bumpsThmedium9;
                shakesTH =shakeThmedium9;
            }
            break;
        case 10:
            toolDescription = toolDescription10;
            if(materialType=="Soft"){
                bumpsTh10 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh10 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh10;
                shakesTH =shakeTh10;
            } else if(materialType=="Medium"){
                bumpsThmedium10 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium10 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium10;
                shakesTH =shakeThmedium10;
            } else if(materialType=="Hard"){
                bumpsThhard10 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard10 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard10;
                shakesTH =shakeThhard10;
            } else {
                bumpsTH = bumpsThmedium10;
                shakesTH =shakeThmedium10;
            }
            break;
        case 11:
            toolDescription = toolDescription11;
            if(materialType=="Soft"){
                bumpsTh11 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh11 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh11;
                shakesTH =shakeTh11;
            } else if(materialType=="Medium"){
                bumpsThmedium11 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium11 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium11;
                shakesTH =shakeThmedium11;
            } else if(materialType=="Hard"){
                bumpsThhard11 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard11 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard11;
                shakesTH =shakeThhard11;
            } else {
                bumpsTH = bumpsThmedium11;
                shakesTH =shakeThmedium11;
            }
            break;
        case 12:
            toolDescription = toolDescription12;
            if(materialType=="Soft"){
                bumpsTh12 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh12 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh12;
                shakesTH =shakeTh12;
            } else if(materialType=="Medium"){
                bumpsThmedium12 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium12 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium12;
                shakesTH =shakeThmedium12;
            } else if(materialType=="Hard"){
                bumpsThhard12 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard12 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard12;
                shakesTH =shakeThhard12;
            } else {
                bumpsTH = bumpsThmedium12;
                shakesTH =shakeThmedium12;
            }
            break;
        case 13:
            toolDescription = toolDescription13;
            if(materialType=="Soft"){
                bumpsTh13 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh13 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh13;
                shakesTH =shakeTh13;
            } else if(materialType=="Medium"){
                bumpsThmedium13 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium13 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium13;
                shakesTH =shakeThmedium13;
            } else if(materialType=="Hard"){
                bumpsThhard13 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard13 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard13;
                shakesTH =shakeThhard13;
            } else {
                bumpsTH = bumpsThmedium13;
                shakesTH =shakeThmedium13;
            }
            break;
        case 14:
            toolDescription = toolDescription14;
            if(materialType=="Soft"){
                bumpsTh14 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh14 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh14;
                shakesTH =shakeTh14;
            } else if(materialType=="Medium"){
                bumpsThmedium14 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium14 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium14;
                shakesTH =shakeThmedium14;
            } else if(materialType=="Hard"){
                bumpsThhard14 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard14 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard14;
                shakesTH =shakeThhard14;
            } else {
                bumpsTH = bumpsThmedium14;
                shakesTH =shakeThmedium14;
            }
            break;
        case 15:
            toolDescription = toolDescription15;
            if(materialType=="Soft"){
                bumpsTh15 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh15 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh15;
                shakesTH =shakeTh15;
            } else if(materialType=="Medium"){
                bumpsThmedium15 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium15 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium15;
                shakesTH =shakeThmedium15;
            } else if(materialType=="Hard"){
                bumpsThhard15 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard15 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard15;
                shakesTH =shakeThhard15;
            } else {
                bumpsTH = bumpsThmedium15;
                shakesTH =shakeThmedium15;
            }
            break;
        case 16:
            toolDescription = toolDescription16;
            if(materialType=="Soft"){
                bumpsTh16 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh16 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh16;
                shakesTH =shakeTh16;
            } else if(materialType=="Medium"){
                bumpsThmedium16 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium16 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium16;
                shakesTH =shakeThmedium16;
            } else if(materialType=="Hard"){
                bumpsThhard16 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard16 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard16;
                shakesTH =shakeThhard16;
            } else {
                bumpsTH = bumpsThmedium16;
                shakesTH =shakeThmedium16;
            }
            break;
        case 17:
            toolDescription = toolDescription17;
            if(materialType=="Soft"){
                bumpsTh17 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh17 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh17;
                shakesTH =shakeTh17;
            } else if(materialType=="Medium"){
                bumpsThmedium17 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium17 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium17;
                shakesTH =shakeThmedium17;
            } else if(materialType=="Hard"){
                bumpsThhard17 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard17 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard17;
                shakesTH =shakeThhard17;
            } else {
                bumpsTH = bumpsThmedium17;
                shakesTH =shakeThmedium17;
            }
            break;
        case 18:
            toolDescription = toolDescription18;
            if(materialType=="Soft"){
                bumpsTh18 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh18 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh18;
                shakesTH =shakeTh18;
            } else if(materialType=="Medium"){
                bumpsThmedium18 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium18 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium18;
                shakesTH =shakeThmedium18;
            } else if(materialType=="Hard"){
                bumpsThhard18 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard18 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard18;
                shakesTH =shakeThhard18;
            } else {
                bumpsTH = bumpsThmedium18;
                shakesTH =shakeThmedium18;
            }
            break;
        case 19:
            toolDescription = toolDescription19;
            if(materialType=="Soft"){
                bumpsTh19 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh19 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh19;
                shakesTH =shakeTh19;
            } else if(materialType=="Medium"){
                bumpsThmedium19 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium19 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium19;
                shakesTH =shakeThmedium19;
            } else if(materialType=="Hard"){
                bumpsThhard19 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard19 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard19;
                shakesTH =shakeThhard19;
            } else {
                bumpsTH = bumpsThmedium19;
                shakesTH =shakeThmedium19;
            }
            break;
        case 20:
            toolDescription = toolDescription20;
            if(materialType=="Soft"){
                bumpsTh20 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh20 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh20;
                shakesTH =shakeTh20;
            } else if(materialType=="Medium"){
                bumpsThmedium20 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium20 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium20;
                shakesTH =shakeThmedium20;
            } else if(materialType=="Hard"){
                bumpsThhard20 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard20 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard20;
                shakesTH =shakeThhard20;
            } else {
                bumpsTH = bumpsThmedium20;
                shakesTH =shakeThmedium20;
            }
            break;
        case 21:
            toolDescription = toolDescription21;
            if(materialType=="Soft"){
                bumpsTh21 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh21 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh21;
                shakesTH =shakeTh21;
            } else if(materialType=="Medium"){
                bumpsThmedium21 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium21 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium21;
                shakesTH =shakeThmedium21;
            } else if(materialType=="Hard"){
                bumpsThhard21 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard21 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard21;
                shakesTH =shakeThhard21;
            } else {
                bumpsTH = bumpsThmedium21;
                shakesTH =shakeThmedium21;
            }
            break;
        case 22:
            toolDescription = toolDescription22;
            if(materialType=="Soft"){
                bumpsTh22 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh22 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh22;
                shakesTH =shakeTh22;
            } else if(materialType=="Medium"){
                bumpsThmedium22 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium22 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium22;
                shakesTH =shakeThmedium22;
            } else if(materialType=="Hard"){
                bumpsThhard22 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard22 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard22;
                shakesTH =shakeThhard22;
            } else {
                bumpsTH = bumpsThmedium22;
                shakesTH =shakeThmedium22;
            }
            break;
        case 23:
            toolDescription = toolDescription23;
            if(materialType=="Soft"){
                bumpsTh23 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh23 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh23;
                shakesTH =shakeTh23;
            } else if(materialType=="Medium"){
                bumpsThmedium23 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium23 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium23;
                shakesTH =shakeThmedium23;
            } else if(materialType=="Hard"){
                bumpsThhard23 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard23 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard23;
                shakesTH =shakeThhard23;
            } else {
                bumpsTH = bumpsThmedium23;
                shakesTH =shakeThmedium23;
            }
            break;
        case 24:
            toolDescription = toolDescription24;
            if(materialType=="Soft"){
                bumpsTh24 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh24 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh24;
                shakesTH =shakeTh24;
            } else if(materialType=="Medium"){
                bumpsThmedium24 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium24 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium24;
                shakesTH =shakeThmedium24;
            } else if(materialType=="Hard"){
                bumpsThhard24 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard24 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard24;
                shakesTH =shakeThhard24;
            } else {
                bumpsTH = bumpsThmedium24;
                shakesTH =shakeThmedium24;
            }
            break;
        case 25:
            toolDescription = toolDescription25;
            if(materialType=="Soft"){
                bumpsTh25 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh25 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh25;
                shakesTH =shakeTh25;
            } else if(materialType=="Medium"){
                bumpsThmedium25 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium25 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium25;
                shakesTH =shakeThmedium25;
            } else if(materialType=="Hard"){
                bumpsThhard25 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard25 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard25;
                shakesTH =shakeThhard25;
            } else {
                bumpsTH = bumpsThmedium25;
                shakesTH =shakeThmedium25;
            }
            break;
        case 26:
            toolDescription = toolDescription26;
            if(materialType=="Soft"){
                bumpsTh26 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh26 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh26;
                shakesTH =shakeTh26;
            } else if(materialType=="Medium"){
                bumpsThmedium26 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium26 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium26;
                shakesTH =shakeThmedium26;
            } else if(materialType=="Hard"){
                bumpsThhard26 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard26 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard26;
                shakesTH =shakeThhard26;
            } else {
                bumpsTH = bumpsThmedium26;
                shakesTH =shakeThmedium26;
            }
            break;
        case 27:
            toolDescription = toolDescription27;
            if(materialType=="Soft"){
                bumpsTh27 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh27 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh27;
                shakesTH =shakeTh27;
            } else if(materialType=="Medium"){
                bumpsThmedium27 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium27 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium27;
                shakesTH =shakeThmedium27;
            } else if(materialType=="Hard"){
                bumpsThhard27 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard27 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard27;
                shakesTH =shakeThhard27;
            } else {
                bumpsTH = bumpsThmedium27;
                shakesTH =shakeThmedium27;
            }
            break;
        case 28:
            toolDescription = toolDescription28;
            if(materialType=="Soft"){
                bumpsTh28 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh28 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh28;
                shakesTH =shakeTh28;
            } else if(materialType=="Medium"){
                bumpsThmedium28 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium28 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium28;
                shakesTH =shakeThmedium28;
            } else if(materialType=="Hard"){
                bumpsThhard28 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard28 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard28;
                shakesTH =shakeThhard28;
            } else {
                bumpsTH = bumpsThmedium28;
                shakesTH =shakeThmedium28;
            }
            break;
        case 29:
            toolDescription = toolDescription29;
            if(materialType=="Soft"){
                bumpsTh29 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh29 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh29;
                shakesTH =shakeTh29;
            } else if(materialType=="Medium"){
                bumpsThmedium29 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium29 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium29;
                shakesTH =shakeThmedium29;
            } else if(materialType=="Hard"){
                bumpsThhard29 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard29 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard29;
                shakesTH =shakeThhard29;
            } else {
                bumpsTH = bumpsThmedium29;
                shakesTH =shakeThmedium29;
            }
            break;
        case 30:
            toolDescription = toolDescription30;
            if(materialType=="Soft"){
                bumpsTh30 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh30 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh30;
                shakesTH =shakeTh30;
            } else if(materialType=="Medium"){
                bumpsThmedium30 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium30 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium30;
                shakesTH =shakeThmedium30;
            } else if(materialType=="Hard"){
                bumpsThhard30 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard30 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard30;
                shakesTH =shakeThhard30;
            } else {
                bumpsTH = bumpsThmedium30;
                shakesTH =shakeThmedium30;
            }
            break;
        case 31:
            toolDescription = toolDescription31;
            if(materialType=="Soft"){
                bumpsTh31 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh31 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh31;
                shakesTH =shakeTh31;
            } else if(materialType=="Medium"){
                bumpsThmedium31 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium31 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium31;
                shakesTH =shakeThmedium31;
            } else if(materialType=="Hard"){
                bumpsThhard31 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard31 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard31;
                shakesTH =shakeThhard31;
            } else {
                bumpsTH = bumpsThmedium31;
                shakesTH =shakeThmedium31;
            }
            break;
        case 32:
            toolDescription = toolDescription32;
            if(materialType=="Soft"){
                bumpsTh32 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeTh32 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsTh32;
                shakesTH =shakeTh32;
            } else if(materialType=="Medium"){
                bumpsThmedium32 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThmedium32 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThmedium32;
                shakesTH =shakeThmedium32;
            } else if(materialType=="Hard"){
                bumpsThhard32 = lround(ui->l_suggBumpTh->text().toDouble());
                shakeThhard32 =lround(ui->l_suggShakeTh->text().toDouble());
                bumpsTH = bumpsThhard32;
                shakesTH =shakeThhard32;
            } else {
                bumpsTH = bumpsThmedium32;
                shakesTH =shakeThmedium32;
            }
            break;

        default:
            toolDescription = toolDescription1;
            bumpsThmedium1 = lround(ui->l_suggBumpTh->text().toDouble());
            shakeThmedium1 =lround(ui->l_suggShakeTh->text().toDouble());
            bumpsTH = bumpsThmedium1;
            shakesTH = shakeThmedium1;
            break;
        }
        /**************************************************/

        /**************************************
         * Aggiorna il file _ToolOptions.3dc
         **************************************/
        saveToolOptions();
        /**************************************/

        /****************************************************************
         * aggiorna i campi lE_bumpsTh e lE_shakesTh sull'interfaccia
         ****************************************************************/
        ui->lE_bumpsTh->setText( ui->l_suggBumpTh->text() );
        ui->lE_shakesTh->setText( ui->l_suggShakeTh->text() );
        /****************************************************************/

        /*********************
         * setta il sensore
         *********************/
        setConfigProcess();
        /*********************/

        /*****************************************
         * disabilita pB_saveSuggested
         *****************************************/
        ui->pB_saveSuggested->setEnabled(false);
        /*****************************************/

        /**********************************
         * crea il file di log
         **********************************/
        createLogFile("TEMPORARY_SET");
        /**********************************/
    }

}

/************************************************************************************************
 * funzione che serve per aggiornatre il file _ToolOptions.3dc
 ************************************************************************************************/
void MainWindow::saveToolOptions(){

    /*******************************************************************************
     * Aggiorna il file _ToolOptions.3dc
     *******************************************************************************/
    QFile outFile("_ToolOptions.3dc");
    outFile.remove();
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);


    QString txt;

    txt=toolDescription1;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh1);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh1);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium1);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium1);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard1);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard1);
    ts<<txt<<Qt::endl;

    txt=toolDescription2;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh2);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh2);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium2);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium2);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard2);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard2);
    ts<<txt<<Qt::endl;

    txt=toolDescription3;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh3);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh3);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium3);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium3);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard3);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard3);
    ts<<txt<<Qt::endl;

    txt=toolDescription4;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh4);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh4);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium4);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium4);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard4);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard4);
    ts<<txt<<Qt::endl;

    txt=toolDescription5;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh5);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh5);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium5);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium5);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard5);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard5);
    ts<<txt<<Qt::endl;

    txt=toolDescription6;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh6);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh6);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium6);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium6);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard6);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard6);
    ts<<txt<<Qt::endl;

    txt=toolDescription7;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh7);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh7);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium7);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium7);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard7);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard7);
    ts<<txt<<Qt::endl;

    txt=toolDescription8;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh8);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh8);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium8);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium8);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard8);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard8);
    ts<<txt<<Qt::endl;

    txt=toolDescription9;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh9);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh9);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium9);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium9);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard9);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard9);
    ts<<txt<<Qt::endl;

    txt=toolDescription10;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh10);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh10);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium10);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium10);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard10);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard10);
    ts<<txt<<Qt::endl;

    txt=toolDescription11;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh11);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh11);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium11);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium11);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard11);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard11);
    ts<<txt<<Qt::endl;

    txt=toolDescription12;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh12);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh12);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium12);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium12);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard12);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard12);
    ts<<txt<<Qt::endl;

    txt=toolDescription13;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh13);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh13);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium13);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium13);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard13);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard13);
    ts<<txt<<Qt::endl;

    txt=toolDescription14;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh14);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh14);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium14);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium14);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard14);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard14);
    ts<<txt<<Qt::endl;

    txt=toolDescription15;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh15);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh15);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium15);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium15);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard15);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard15);
    ts<<txt<<Qt::endl;

    txt=toolDescription16;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh16);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh16);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium16);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium16);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard16);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard16);
    ts<<txt<<Qt::endl;

    txt=toolDescription17;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh17);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh17);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium17);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium17);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard17);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard17);
    ts<<txt<<Qt::endl;

    txt=toolDescription18;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh18);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh18);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium18);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium18);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard18);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard18);
    ts<<txt<<Qt::endl;

    txt=toolDescription19;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh19);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh19);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium19);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium19);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard19);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard19);
    ts<<txt<<Qt::endl;

    txt=toolDescription20;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh20);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh20);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium20);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium20);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard20);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard20);
    ts<<txt<<Qt::endl;

    txt=toolDescription21;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh21);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh21);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium21);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium21);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard21);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard21);
    ts<<txt<<Qt::endl;

    txt=toolDescription22;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh22);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh22);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium22);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium22);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard22);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard22);
    ts<<txt<<Qt::endl;

    txt=toolDescription23;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh23);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh23);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium23);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium23);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard23);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard23);
    ts<<txt<<Qt::endl;

    txt=toolDescription24;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh24);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh24);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium24);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium24);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard24);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard24);
    ts<<txt<<Qt::endl;

    txt=toolDescription25;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh25);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh25);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium25);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium25);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard25);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard25);
    ts<<txt<<Qt::endl;

    txt=toolDescription26;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh26);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh26);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium26);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium26);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard26);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard26);
    ts<<txt<<Qt::endl;

    txt=toolDescription27;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh27);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh27);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium27);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium27);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard27);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard27);
    ts<<txt<<Qt::endl;

    txt=toolDescription28;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh28);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh28);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium28);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium28);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard28);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard28);
    ts<<txt<<Qt::endl;

    txt=toolDescription29;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh29);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh29);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium29);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium29);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard29);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard29);
    ts<<txt<<Qt::endl;

    txt=toolDescription30;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh30);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh30);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium30);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium30);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard30);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard30);
    ts<<txt<<Qt::endl;

    txt=toolDescription31;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh31);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh31);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium31);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium31);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard31);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard31);
    ts<<txt<<Qt::endl;

    txt=toolDescription32;
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsTh32);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeTh32);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThmedium32);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThmedium32);
    ts<<txt<<Qt::endl;
    txt=QString::number(bumpsThhard32);
    ts<<txt<<Qt::endl;
    txt=QString::number(shakeThhard32);
    ts<<txt<<Qt::endl;

    ts<<Qt::flush;
    /********************************************************************************/

}
/************************************************************************************************/



void MainWindow::on_tabWidget_currentChanged(int index)
{

    //    if(index==1){
    //        /*****************************************
    //         * mostra i widget relativi ai raw data
    //         *****************************************/
    //        //ui->checkBox_RawData->setEnabled(true);
    //        ui->label_2->setEnabled(true);
    //        ui->label_18->setEnabled(true);
    //        ui->l_suggBumpTh->setEnabled(true);
    //        ui->label_20->setEnabled(true);
    //        ui->label_21->setEnabled(true);
    //        ui->l_suggShakeTh->setEnabled(true);
    //        ui->pB_saveSuggested->setEnabled(true);
    //        /*****************************************/
    //    } else {
    //        /*****************************************
    //         * nasconde i widget relativi ai raw data
    //         *****************************************/
    //        //ui->checkBox_RawData->setEnabled(false);
    //        ui->label_2->setEnabled(false);
    //        ui->label_18->setEnabled(false);
    //        ui->l_suggBumpTh->setEnabled(false);
    //        ui->label_20->setEnabled(false);
    //        ui->label_21->setEnabled(false);
    //        ui->l_suggShakeTh->setEnabled(false);
    //        ui->pB_saveSuggested->setEnabled(false);
    //        /*****************************************/
    //    }

}


void MainWindow::on_radioButton_Manual_clicked()
{
    workingModality = "MANUAL";
    /********************************************************
     * aggiorna il file Settings.3dc
     ********************************************************/
    updateSettingsFile();
    /********************************************************/

    /******************************************
     * crea il file di log
     ******************************************/
    createLogFile("WORKING_MODALITY_CHANGE");
    /******************************************/
}

void MainWindow::on_radioButton_Automatic_clicked()
{
    workingModality = "AUTOMATIC";
    /********************************************************
     * aggiorna il file Settings.3dc
     ********************************************************/
    updateSettingsFile();
    /********************************************************/

    /******************************************
     * crea il file di log
     ******************************************/
    createLogFile("WORKING_MODALITY_CHANGE");
    /******************************************/
}

void MainWindow::on_pB_abortAcq_clicked()
{
    /******************************************
     * arresta la fase di autoapprendimento
     ******************************************/
    abortAcquisition();
    /******************************************/
}

void MainWindow::abortAcquisition(void){

    /****************************************
     * imposta a false acqRunningFlag
     ****************************************/
    acqRunningFlag = false;
    /****************************************/

//    /**********************************************
//     * calcola le medie
//     **********************************************/
//    double AvgXsamples = SumXsamples/SAMPLES_NUM;
//    double AvgYsamples = SumYsamples/SAMPLES_NUM;
//    double AvgZsamples = SumZsamples/SAMPLES_NUM;
//    /**********************************************/
//
//    /**********************************************
//     * ottiene il valore massimo delle medie
//     **********************************************/
//    double AvgMax = AvgXsamples;
//    if(AvgYsamples>AvgMax) AvgMax = AvgYsamples;
//    if(AvgZsamples>AvgMax) AvgMax = AvgZsamples;
//    /**********************************************/
//
//    /****************************************************************************
//     * calcola le soglie suggerite secondo il seguente
//     * principio:
//     * 1. la soglia delle vibrazioni è del shakeThPercent % più alta di AvgMax
//     * 2. la soglia degli urti è 3 volte la soglia delle vibrazioni
//     *****************************************************************************/
//    //double shakeThPercent = 250;
//    double bumpThPercent = 3*shakeThPercent;
//    double bumpThOffset = shakeThOffset;
//    double automaticBumpTh = lround(AvgMax+( (AvgMax*bumpThPercent/100) + bumpThOffset ) );
//    automaticShakeTh = lround(AvgMax+( (AvgMax*shakeThPercent/100) + shakeThOffset ) );
//    //double automaticBumpTh = 3*automaticShakeTh;
//    /*****************************************************************************/
//
    /****************************************************************
     * mostra sull'interfaccia i valori calcolati
     ****************************************************************/
    ui->l_suggBumpTh->setText("N/A"); //ui->l_suggBumpTh->setText(QString::number(automaticBumpTh));
    ui->l_suggShakeTh->setText("N/A"); //ui->l_suggShakeTh->setText(QString::number(automaticShakeTh));
    /****************************************************************/

    /************************************
     * azzera sampleIndex, SumXsamples,
     * SumYsamples e SumZsamples
     ************************************/
    sampleIndex = 0;
    SumXsamples = 0;
    SumYsamples = 0;
    SumZsamples = 0;
    /************************************/

    /************************************
     * abilita il pulsante pB_startAcq
     ************************************/
    ui->label_19->setEnabled(true);
    ui->lE_acqTime->setEnabled(true);
    ui->pB_startAcq->setEnabled(true);
    /************************************/

    /*************************************
     * Riabilita checkBox_RawData
     *************************************/
    ui->checkBox_RawData->setEnabled(true);
    /*************************************/

    /*************************************
     * Riabilita pB_saveSuggested
     *************************************/
    // //ui->pB_saveSuggested->setEnabled(true);
    /*************************************/

    /*************************************
     * Riabilita pB_toolOptions
     *************************************/
    //ui->pB_toolOptions->setEnabled(true);
    /*************************************/

    /*************************************
     * Riabilita pB_resetBumps
     *************************************/
    //ui->pB_resetBumps->setEnabled(true);
    /*************************************/

    /*************************************
     * Riabilita lE_bumpsTh
     *************************************/
    //ui->lE_bumpsTh->setEnabled(true);
    /*************************************/

    /*************************************
     * Riabilita pB_resetShakes
     *************************************/
    //ui->pB_resetShakes->setEnabled(true);
    /*************************************/

    /*************************************
     * Riabilita lE_shakesTh
     *************************************/
    //ui->lE_shakesTh->setEnabled(true);
    /*************************************/

    /*********************************************
     * Riabilita lE_shakesSamplingTime
     *********************************************/
    //ui->lE_shakesSamplingTime->setEnabled(true);
    /*********************************************/

    /*************************************
     * Riabilita pB_setConfig
     *************************************/
    //ui->pB_setConfig->setEnabled(true);
    /*************************************/

    /*********************************************
     * Riabilita radioButton_Automatic
     *********************************************/
    //ui->radioButton_Automatic->setEnabled(true);
    /*********************************************/

    /*********************************************
     * Riabilita radioButton_Manual
     *********************************************/
    //ui->radioButton_Manual->setEnabled(true);
    /*********************************************/

    /*********************************************
     * Riabilita rB_soft, rB_medium e rB_hard
     *********************************************/
    //ui->rB_soft->setEnabled(true);
    //ui->rB_medium->setEnabled(true);
    //ui->rB_hard->setEnabled(true);
    /*********************************************/

    /*************************************************
     * Riabilita comboBox_toolSelection se il
     * sistema è in modalità MANUALE
     *************************************************/
    //if( ui->radioButton_Manual->isChecked() ){
    //    ui->comboBox_toolSelection->setEnabled(true);
    //}
    /*************************************************/

    /**********************************************
     * Rende invisibile il pulsante pB_abortAcq
     **********************************************/
    ui->pB_abortAcq->setVisible(false);
    /**********************************************/

}

void MainWindow::on_rB_soft_clicked()
{
    materialType = "Soft";
    /********************************************************
     * aggiorna il file Settings.3dc
     ********************************************************/
    updateSettingsFile();
    /********************************************************/
qDebug()<< "BUMP TH" << bumpsTH;
qDebug()<< "BUMP TH" << shakesTH;
    /*******************************************************
     * rilegge il file dei settings
     ******************************************************/
    readSettingsFile();
    /******************************************************/
qDebug()<< "BUMP TH" << bumpsTH;
qDebug()<< "BUMP TH" << shakesTH;
    /*******************************************************************************
     * aggiorna i campi tool description, bumpsTH, shakesTH e shakesSamplingTime
     *******************************************************************************/
    ui->l_toolDescription->setText(toolDescription);
    ui->lE_bumpsTh->setText(QString::number((int)bumpsTH));
    ui->lE_shakesTh->setText(QString::number((int)shakesTH));
    ui->lE_shakesSamplingTime->setText(QString::number((int)shakesSamplingTime));
    /*******************************************************************************/

    /**********************************
     * crea il file di log
     **********************************/
    createLogFile("MATERIAL_CHANGE");
    /**********************************/
}

void MainWindow::on_rB_medium_clicked()
{
    materialType = "Medium";
    /********************************************************
     * aggiorna il file Settings.3dc
     ********************************************************/
    updateSettingsFile();
    /********************************************************/
qDebug()<< "BUMP TH" << bumpsTH;
qDebug()<< "BUMP TH" << shakesTH;
    /*******************************************************
     * rilegge il file dei settings
     ******************************************************/
    readSettingsFile();
    /******************************************************/
qDebug()<< "BUMP TH" << bumpsTH;
qDebug()<< "BUMP TH" << shakesTH;
    /*******************************************************************************
     * aggiorna i campi tool description, bumpsTH, shakesTH e shakesSamplingTime
     *******************************************************************************/
    ui->l_toolDescription->setText(toolDescription);
    ui->lE_bumpsTh->setText(QString::number((int)bumpsTH));
    ui->lE_shakesTh->setText(QString::number((int)shakesTH));
    ui->lE_shakesSamplingTime->setText(QString::number((int)shakesSamplingTime));
    /*******************************************************************************/

    /**********************************
     * crea il file di log
     **********************************/
    createLogFile("MATERIAL_CHANGE");
    /**********************************/
}

void MainWindow::on_rB_hard_clicked()
{
    materialType = "Hard";
    /********************************************************
     * aggiorna il file Settings.3dc
     ********************************************************/
    updateSettingsFile();
    /********************************************************/
qDebug()<< "BUMP TH" << bumpsTH;
qDebug()<< "BUMP TH" << shakesTH;
    /*******************************************************
     * rilegge il file dei settings
     ******************************************************/
    readSettingsFile();
    /******************************************************/
qDebug()<< "BUMP TH" << bumpsTH;
qDebug()<< "BUMP TH" << shakesTH;
    /*******************************************************************************
     * aggiorna i campi tool description, bumpsTH, shakesTH e shakesSamplingTime
     *******************************************************************************/
    ui->l_toolDescription->setText(toolDescription);
    ui->lE_bumpsTh->setText(QString::number((int)bumpsTH));
    ui->lE_shakesTh->setText(QString::number((int)shakesTH));
    ui->lE_shakesSamplingTime->setText(QString::number((int)shakesSamplingTime));
    /*******************************************************************************/

    /**********************************
     * crea il file di log
     **********************************/
    createLogFile("MATERIAL_CHANGE");
    /**********************************/
}

void MainWindow::on_pB_hiddenBumpTh_clicked()
{
    /********************************************
     * apre la hiddenbumpdialog
     ********************************************/
    HiddenBumpDialog hiddenBumpDialog;
    hiddenBumpDialog.setModal(true);
    hiddenBumpDialog.exec();
    /********************************************/

    /*******************************************
     * legge il file Settings.3dc per
     * l'eventuale aggiornamento della
     * soglia degli urti generale
     *******************************************/
    readSettingsFile();
    /*******************************************/

    /*******************************************
     * setta il sensore con gli eventuali nuovi
     * parameri di configurazione
     *******************************************/
    setConfiguration();
    /*******************************************/

    /****************************************
     * Richiede i valori di configurazione
     ****************************************/
    getConfiguration();
    /****************************************/



}

