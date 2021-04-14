//-------------------------------------------------------------------------------------
//++++++++  Data header +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//********  File:   vgsa_view.h *******************************************************
//********  Function:   Header file of View Class   ***********************************
//********              Contains all prototypes and members of class    ***************
//********  Author: Christian Grünewald ***********************************************
//********  Projekt: InGesWoh_VGSA of InGesWoh Projekt ********************************
//********  Date:   2021-04-14    *****************************************************
//********  Git:    https://github.com/ChrisLinux127/InGesWoh_VGSA  *******************
//********  Date of last Changes:   2021-04-14  ***************************************
//********  Last Changes:   Init  *****************************************************
//********  Current Version: 0.1  *****************************************************
//-------------------------------------------------------------------------------------

#ifndef VGSA_VIEW_H
#define VGSA_VIEW_H

#include <QMainWindow>
#include<QSerialPort>   //für Serielle Kommunikation
#include<QSerialPortInfo>   //Für Infos von Seriellen Kommunikation
#include<QDebug>    //Für Ausgaben in Debuger
#include<QtWidgets> //Für Warnungen (QMessageBox

//Definition of VGSA Commands for CMD Register:
#define BROADCAST 0x00
#define GET_GASSET_CONFIG 0x30
#define START_VGSA 0x31
#define STOP_VGSA 0x32

#define SET_DEVICE_CONFIG 0x02
#define GET_DEVICE_CONFIG 0x04
#define GET_RESULT 0x09
#define GET_TREND 0x0D

#define RESET_ZERO_LEVEL 0x0B
#define SET_GASPRINT 0x10
#define CLR_GASPRINT 0x20

#define ACK_ZERO_LEVEL 0x4B
#define ACK_SET_GASPRINT 0x41
#define ACK_CLR_GASPRINT 0x42

QT_BEGIN_NAMESPACE
namespace Ui { class VGSA_View; }
QT_END_NAMESPACE

class VGSA_View : public QMainWindow
{
    Q_OBJECT

public:
    VGSA_View(QWidget *parent = nullptr);
    ~VGSA_View();

private slots:
    void on_btn_verbinden_clicked();

    void on_btn_trennen_clicked();

    void readSerial();

private:

    Ui::VGSA_View *ui;  //conncetion to Formular.ui to design the gui
    QSerialPort *Controller;    //Serial Connection to Controller (VGSA)
    static const quint16 s_Controller_Vendor_ID=1027;   //Vendor ID of VGSA
    static const quint16 s_Controller_Product_ID=24577; //Product ID of VGSA
    QString Controller_Portname;
    bool Is_Controller_available;
};
#endif // VGSA_VIEW_H
