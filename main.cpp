//-------------------------------------------------------------------------------------
//++++++++  Data header +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//********  File:   main.cpp   ********************************************************
//********  Function:   mainfunction (startpoint)   ***********************************
//********  Author: Christian Grünewald ***********************************************
//********  Projekt: InGesWoh_VGSA of InGesWoh Projekt ********************************
//********  Date:   2021-04-14    *****************************************************
//********  Git:    https://github.com/ChrisLinux127/InGesWoh_VGSA  *******************
//********  Date of last Changes:   2021-04-14  ***************************************
//********  Last Changes:   Init  *****************************************************
//********  Current Version: 0.1  *****************************************************
//-------------------------------------------------------------------------------------

#include "vgsa_view.h"  //includes all the Gui

#include <QApplication> //for manager

//Here is the start point of the application:
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //Application Manager of QT
    VGSA_View w;    //call standard Constructor of Window class
    w.show();   //set MainWindow viewable
    return a.exec();
}
