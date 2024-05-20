#ifndef TOOLOPTIONS_H
#define TOOLOPTIONS_H

#include <QDialog>
#include <QFile>
#include <QDateTime>




namespace Ui {
class ToolOptions;
}

class ToolOptions : public QDialog
{
    Q_OBJECT


    /*******************
     * tool selezionato
     *******************/
    int toolNum=0;
    /*******************/

    /*********************************
     * tipo di materiale; può essere
     * Moft, Medium o Hard
     *********************************/
    QString MaterialType;
    /*********************************/

    /*********************************
     * modalità di lavoro
     *********************************/
    QString WorkingModality;
    /*********************************/

    /****************************************
     * variabili salvate in _ToolOptions.3dc
     ****************************************/
    QString Description1;
    double BumpsTh1=0;
    double ShakeTh1=0;
    double BumpsThmedium1=0;
    double ShakeThmedium1=0;
    double BumpsThhard1=0;
    double ShakeThhard1=0;

    QString Description2;
    double BumpsTh2=0;
    double ShakeTh2=0;
    double BumpsThmedium2=0;
    double ShakeThmedium2=0;
    double BumpsThhard2=0;
    double ShakeThhard2=0;

    QString Description3;
    double BumpsTh3=0;
    double ShakeTh3=0;
    double BumpsThmedium3=0;
    double ShakeThmedium3=0;
    double BumpsThhard3=0;
    double ShakeThhard3=0;

    QString Description4;
    double BumpsTh4=0;
    double ShakeTh4=0;
    double BumpsThmedium4=0;
    double ShakeThmedium4=0;
    double BumpsThhard4=0;
    double ShakeThhard4=0;

    QString Description5;
    double BumpsTh5=0;
    double ShakeTh5=0;
    double BumpsThmedium5=0;
    double ShakeThmedium5=0;
    double BumpsThhard5=0;
    double ShakeThhard5=0;

    QString Description6;
    double BumpsTh6=0;
    double ShakeTh6=0;
    double BumpsThmedium6=0;
    double ShakeThmedium6=0;
    double BumpsThhard6=0;
    double ShakeThhard6=0;

    QString Description7;
    double BumpsTh7=0;
    double ShakeTh7=0;
    double BumpsThmedium7=0;
    double ShakeThmedium7=0;
    double BumpsThhard7=0;
    double ShakeThhard7=0;

    QString Description8;
    double BumpsTh8=0;
    double ShakeTh8=0;
    double BumpsThmedium8=0;
    double ShakeThmedium8=0;
    double BumpsThhard8=0;
    double ShakeThhard8=0;

    QString Description9;
    double BumpsTh9=0;
    double ShakeTh9=0;
    double BumpsThmedium9=0;
    double ShakeThmedium9=0;
    double BumpsThhard9=0;
    double ShakeThhard9=0;

    QString Description10;
    double BumpsTh10=0;
    double ShakeTh10=0;
    double BumpsThmedium10=0;
    double shakeThmedium10=0;
    double bumpsThhard10=0;
    double shakeThhard10=0;

    QString Description11;
    double BumpsTh11=0;
    double ShakeTh11=0;
    double BumpsThmedium11=0;
    double shakeThmedium11=0;
    double bumpsThhard11=0;
    double shakeThhard11=0;

    QString Description12;
    double BumpsTh12=0;
    double ShakeTh12=0;
    double BumpsThmedium12=0;
    double shakeThmedium12=0;
    double bumpsThhard12=0;
    double shakeThhard12=0;

    QString Description13;
    double BumpsTh13=0;
    double ShakeTh13=0;
    double BumpsThmedium13=0;
    double shakeThmedium13=0;
    double bumpsThhard13=0;
    double shakeThhard13=0;

    QString Description14;
    double BumpsTh14=0;
    double ShakeTh14=0;
    double BumpsThmedium14=0;
    double shakeThmedium14=0;
    double bumpsThhard14=0;
    double shakeThhard14=0;

    QString Description15;
    double BumpsTh15=0;
    double ShakeTh15=0;
    double BumpsThmedium15=0;
    double shakeThmedium15=0;
    double bumpsThhard15=0;
    double shakeThhard15=0;

    QString Description16;
    double BumpsTh16=0;
    double ShakeTh16=0;
    double BumpsThmedium16=0;
    double shakeThmedium16=0;
    double bumpsThhard16=0;
    double shakeThhard16=0;

    QString Description17;
    double BumpsTh17=0;
    double ShakeTh17=0;
    double BumpsThmedium17=0;
    double shakeThmedium17=0;
    double bumpsThhard17=0;
    double shakeThhard17=0;

    QString Description18;
    double BumpsTh18=0;
    double ShakeTh18=0;
    double BumpsThmedium18=0;
    double shakeThmedium18=0;
    double bumpsThhard18=0;
    double shakeThhard18=0;

    QString Description19;
    double BumpsTh19=0;
    double ShakeTh19=0;
    double BumpsThmedium19=0;
    double shakeThmedium19=0;
    double bumpsThhard19=0;
    double shakeThhard19=0;

    QString Description20;
    double BumpsTh20=0;
    double ShakeTh20=0;
    double BumpsThmedium20=0;
    double ShakeThmedium20=0;
    double BumpsThhard20=0;
    double ShakeThhard20=0;

    QString Description21;
    double BumpsTh21=0;
    double ShakeTh21=0;
    double BumpsThmedium21=0;
    double ShakeThmedium21=0;
    double BumpsThhard21=0;
    double ShakeThhard21=0;

    QString Description22;
    double BumpsTh22=0;
    double ShakeTh22=0;
    double BumpsThmedium22=0;
    double ShakeThmedium22=0;
    double BumpsThhard22=0;
    double ShakeThhard22=0;

    QString Description23;
    double BumpsTh23=0;
    double ShakeTh23=0;
    double BumpsThmedium23=0;
    double ShakeThmedium23=0;
    double BumpsThhard23=0;
    double ShakeThhard23=0;

    QString Description24;
    double BumpsTh24=0;
    double ShakeTh24=0;
    double BumpsThmedium24=0;
    double ShakeThmedium24=0;
    double BumpsThhard24=0;
    double ShakeThhard24=0;

    QString Description25;
    double BumpsTh25=0;
    double ShakeTh25=0;
    double BumpsThmedium25=0;
    double ShakeThmedium25=0;
    double BumpsThhard25=0;
    double ShakeThhard25=0;

    QString Description26;
    double BumpsTh26=0;
    double ShakeTh26=0;
    double BumpsThmedium26=0;
    double ShakeThmedium26=0;
    double BumpsThhard26=0;
    double ShakeThhard26=0;

    QString Description27;
    double BumpsTh27=0;
    double ShakeTh27=0;
    double BumpsThmedium27=0;
    double ShakeThmedium27=0;
    double BumpsThhard27=0;
    double ShakeThhard27=0;

    QString Description28;
    double BumpsTh28=0;
    double ShakeTh28=0;
    double BumpsThmedium28=0;
    double ShakeThmedium28=0;
    double BumpsThhard28=0;
    double ShakeThhard28=0;

    QString Description29;
    double BumpsTh29=0;
    double ShakeTh29=0;
    double BumpsThmedium29=0;
    double ShakeThmedium29=0;
    double BumpsThhard29=0;
    double ShakeThhard29=0;

    QString Description30;
    double BumpsTh30=0;
    double ShakeTh30=0;
    double BumpsThmedium30=0;
    double ShakeThmedium30=0;
    double BumpsThhard30=0;
    double ShakeThhard30=0;

    QString Description31;
    double BumpsTh31=0;
    double ShakeTh31=0;
    double BumpsThmedium31=0;
    double ShakeThmedium31=0;
    double BumpsThhard31=0;
    double ShakeThhard31=0;

    QString Description32;
    double BumpsTh32=0;
    double ShakeTh32=0;
    double BumpsThmedium32=0;
    double ShakeThmedium32=0;
    double BumpsThhard32=0;
    double ShakeThhard32=0;
    /****************************************/

    /*************************************************************
     * Valori di default
     *************************************************************/
    QString defaultDescription = "Description Not Available";
    double defaultBumpsTh=100;
    double defaultShakeTh=20;
    /*************************************************************/


public:
    explicit ToolOptions(QWidget *parent = nullptr);
    ~ToolOptions();

private slots:
    void on_pB_DefaultOpt_clicked();

    void on_pB_SaveOpt_clicked();

    void fillEditFields();

    void saveToolOptions();

    void on_cB_toolSelected_currentIndexChanged(int index);

    void on_lE_toolBumpTh_editingFinished();

    void on_lE_toolShakeTh_editingFinished();

    void on_tE_toolDescription_textChanged();

    void createLogFile_2(QString eventType);

private:
    Ui::ToolOptions *ui;
};

#endif // TOOLOPTIONS_H
