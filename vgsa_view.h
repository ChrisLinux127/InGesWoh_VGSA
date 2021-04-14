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
