//-------------------------------------------------------------------------------------
//++++++++  Data header +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//********  File:   vgsa_view.cpp   ***************************************************
//********  Function:   Implementation of Gui   ***************************************
//********              VGSA view and Signals and Slot for Communication    ***********
//********  Author: Christian Grünewald ***********************************************
//********  Projekt: InGesWoh_VGSA of InGesWoh Projekt ********************************
//********  Date:   2021-04-14    *****************************************************
//********  Git:    https://github.com/ChrisLinux127/InGesWoh_VGSA  *******************
//********  Date of last Changes:   2021-04-14  ***************************************
//********  Last Changes:   Init  *****************************************************
//********  Current Version: 0.1  *****************************************************
//-------------------------------------------------------------------------------------

#include "vgsa_view.h"
#include "ui_vgsa_view.h"
//Standard constructor:
VGSA_View::VGSA_View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VGSA_View)
{
    ui->setupUi(this);  //create all elements of .ui (not viewable now)
    Controller=new QSerialPort; //Create new QSerliaport obj
    Controller_Portname="";
    Is_Controller_available=false;
}
//Destructor:
VGSA_View::~VGSA_View()
{
    //Close Connection of UART:
       if(Controller->isOpen())
       {
           Controller->close();
       }
    delete ui;
}


void VGSA_View::on_btn_verbinden_clicked()
{
    //conect with controller:
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier()&&serialPortInfo.hasProductIdentifier())
                {
                    if(serialPortInfo.vendorIdentifier()==s_Controller_Vendor_ID)
                    {
                        if(serialPortInfo.productIdentifier()==s_Controller_Product_ID)
                        {
                            //Erst wenn Kontroller gefunden wurde, dann zuweisen:
                            Controller_Portname=serialPortInfo.portName();
                            Is_Controller_available=true;
                        }
                    }
                }
    }
    if(Is_Controller_available)
    {
        //Setup of UART
            Controller->setPortName(Controller_Portname);   //Namen zuweisen
            Controller->open(QSerialPort::ReadWrite); //Bidirektionale Kommunikation
            Controller->setBaudRate(QSerialPort::Baud9600); //9600 Boud
            Controller->setDataBits(QSerialPort::Data8);    //8 Bits Übertragen
            Controller->setParity(QSerialPort::NoParity); //Kein Paritätsbit
            Controller->setStopBits(QSerialPort::OneStop);  //1 Stopbit
            Controller->setFlowControl(QSerialPort::NoFlowControl);     //??
        //Change btn state
            ui->btn_state->setText("Erfolgreich Verbunden..."); //tell user
            ui->btn_state->setStyleSheet("background-color:green");
            ui->btn_verbinden->setEnabled(false); //btn disable, prevent it from being assigned twice
            ui->btn_trennen->setEnabled(true);
            ui->lst_out->addItem("SYSTEM: CONECTION SUCCESSfUL");
    }
    else
    {
        //Fehler ausgeben:
              QMessageBox::warning(this, "Vebindung Fehlgeschlagen!","ESP32 konnte nicht gefunden werden!");
              ui->btn_state->setText("Verbindung zum USM fehlgeschlagen...");
              ui->btn_state->setStyleSheet("background-color:red");
    }
}

void VGSA_View::on_btn_trennen_clicked()
{
    //Close Connection of UART:
       if(Controller->isOpen())
       {
           Controller->close();
           ui->btn_state->setText("Verbindung zum USM vom User getrennt...");
           ui->btn_state->setStyleSheet("background-color:yellow");
           ui->btn_trennen->setEnabled(false);
           ui->btn_verbinden->setEnabled(true);
       }
}
