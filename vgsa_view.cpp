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
            Controller->setBaudRate(QSerialPort::Baud38400); //38400 Boud
            Controller->setDataBits(QSerialPort::Data8);    //8 Bits Übertragen
            Controller->setParity(QSerialPort::NoParity); //Kein Paritätsbit
            Controller->setStopBits(QSerialPort::OneStop);  //1 Stopbit
            Controller->setFlowControl(QSerialPort::NoFlowControl);     //??
        //Conect the read method to readyRead Signal:
           QObject::connect(Controller,SIGNAL(readyRead()),this, SLOT(readSerial()));
        //Change btn state
            ui->btn_state->setText("Erfolgreich Verbunden..."); //tell user
             ui->btn_state->setStyleSheet("color:white; background-color:green");
            ui->btn_verbinden->setEnabled(false); //btn disable, prevent it from being assigned twice
            ui->btn_trennen->setEnabled(true);
            //ui->lst_out->addItem( "SYSTEM: CONECTION SUCCESSfUL");
    }
    else
    {
        //Fehler ausgeben:
              QMessageBox::warning(this, "Vebindung Fehlgeschlagen!","ESP32 konnte nicht gefunden werden!");
              ui->btn_state->setText("Verbindung zum USM fehlgeschlagen...");
              ui->btn_state->setStyleSheet("color:white; background-color:red");
             // ui->lst_out->addItem( "SYSTEM: CONECTION FAILED!");
    }
}

void VGSA_View::on_btn_trennen_clicked()
{
    //Close Connection of UART:
       if(Controller->isOpen())
       {
           Controller->close();
           ui->btn_state->setText("Verbindung zum USM vom User getrennt...");
           ui->btn_state->setStyleSheet("background-color:yellow;color:black");
           ui->btn_trennen->setEnabled(false);
           ui->btn_verbinden->setEnabled(true);
       }
}

void VGSA_View::readSerial()
{
    SerialInputBuffer.append(Controller->readAll());
    qDebug()<<"Unprocessed Data: "<<SerialInputBuffer.toHex();
    ProcessSerialData("Data");
}

void VGSA_View::ProcessSerialData(QString data)
{
    //Wenn Header da:
    if(SerialInputBuffer.size()>=3)
    {
        //Save Header:
       for(int i=0;i<4;i++)
       {
           Header[i]=SerialInputBuffer[i];
       }
       //Data complete?
       if(SerialInputBuffer.size()<=Header[2]+3)
       {
           return;
       }
       //Data Complette:
       else
       {
           if(Header[3]==GET_RESSULT)
           {
               qDebug()<<"Messwerte: "<<SerialInputBuffer.toHex();
               for (int i=0;i<48 ;i++ )
               {
                  Messwerte[i]=SerialInputBuffer[i+3]; //Save Messwerte
                  qDebug()<<"Messwert "<<i<<" ="<<Messwerte[i];
               }
           }
           //Trend kommt:
           else
           {
             Trend=SerialInputBuffer[4];
             qDebug()<<"Trend: "<<Trend;
           }

           SerialInputBuffer.clear(); //Clear Array
       }
    }
}

void VGSA_View::on_btn_Start_clicked()
{
    if(Controller->isOpen()&&Controller->isWritable())
    {
        //01 00 03 31 00 00 00
        QByteArray SendData(7,0);
        SendData[0]=0x01;
        SendData[1]=0x00;
        SendData[2]=0x03;
        SendData[3]=START_VGSA;
        SendData[4]=0x00;
        SendData[5]=0x00;
        SendData[6]=0x00;
        Controller->write(SendData);
    }
}

void VGSA_View::on_btn_Stop_clicked()
{
    if(Controller->isOpen()&&Controller->isWritable())
    {
        //01 00 03 31 00 00 00
        QByteArray SendData(7,0);
        SendData[0]=0x01;
        SendData[1]=0x00;
        SendData[2]=0x03;
        SendData[3]=STOP_VGSA;
        SendData[4]=0x00;
        SendData[5]=0x00;
        SendData[6]=0x00;
        Controller->write(SendData);
    }
}
