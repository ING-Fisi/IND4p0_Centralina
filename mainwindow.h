#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include <QtSerialPort/QSerialPort>
//#include <QtSerialPort/QSerialPortInfo>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QQueue>
#include <QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "chart.h"
#include "chartview.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include "protocollo.h"
//#include "qcustomplot.h"

#include <QDateTime>
#include <QFile>
#include <gpiod.h>






//QT_CHARTS_USE_NAMESPACE

class ProgressBar;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPixmap* green_led;
    QPixmap* red_led;

    struct Settings {
        QString name;
        qint32 baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
        bool localEchoEnabled;
    };

    Settings settings;

    //****************************** GPIO ******************///

    const char *chipname = "gpiochip0";
    struct gpiod_chip *chip;
    struct gpiod_line *rele00;
    struct gpiod_line *rele01;
    struct gpiod_line *rele02;
    struct gpiod_line *rele03;



    struct gpiod_line *ingressi_dig[8]; // Pushbutton


    QTimer *acquisitionTimer;



    int i, val;




    //    void send_edge_limit();
    void setConfiguration();
    void saveConfiguration();
    void getConfiguration();


    QString name_serialport;
    void init_serial_port(QString name, uint32_t baud);
    void openSerialPort();
    void closeSerialPort();
    void writeData(const char *data, qint64 len);
    void readData();
    void handleError(QSerialPort::SerialPortError error);


    //QCustomPlot *customPlot;
    QVector<double> mSamples;
    QVector<double> mIndices;
    QVector<double> mFftIndices;


    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    QLineSeries *series3 = new QLineSeries();
    QLineSeries *series4 = new QLineSeries();
    int graph_index = 0;

    Chart *chart;
    ChartView *chartView;




private slots:
    void on_pushButton_toggled(bool checked);

    //    void on_verticalSlider_limit_valueChanged(int value);

    void on_pushButton_refresh_serial_clicked();

    void on_pB_setConfig_clicked();
    void setConfigProcess();

    void on_pB_saveConfig_clicked();

    void on_pB_resetBumps_clicked();
    void resetBumpCounters();

    void shakesMonitorFunction();

    void bumpFilterFunction();

    void acquisitionTask();

    void on_pB_resetShakes_clicked();
    void resetShakesCounters();

    void enableSettingsSection(bool enFlag);


    void on_pB_toolOptions_clicked();
    void saveToolOptions();

    void on_comboBox_toolSelection_currentIndexChanged(int index);

    void updateSettingsFile(void);
    void readSettingsFile(void);

    void createLogFile(QString eventType);

    void on_checkBox_RawData_stateChanged(int arg1);

    void on_pB_startAcq_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pB_saveSuggested_clicked();

    void on_radioButton_Manual_clicked();

    void on_radioButton_Automatic_clicked();

    void on_pB_abortAcq_clicked();
    void abortAcquisition(void);

    void on_rB_soft_clicked();

    void on_rB_medium_clicked();

    void on_rB_hard_clicked();

    void on_pB_hiddenBumpTh_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serial_port = nullptr;

};
#endif // MAINWINDOW_H
