//-------------------------------------------------------------------------------------
//++++++++  Data header +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//********  File:   vgsa_view.h   *****************************************************
//********  Author: Christian Grünewald ***********************************************
//********  Projekt: InGesWoh_VGSA of InGesWoh Projekt ********************************
//********  Date:   2021-04-14    *****************************************************
//********  Git:
//********  Date of last Changes:   2021-04-14  ***************************************
//********  Last Changes:   Init  *****************************************************
//********  Current Version: 0.1  *****************************************************
//-------------------------------------------------------------------------------------

#ifndef VGSA_VIEW_H
#define VGSA_VIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class VGSA_View; }
QT_END_NAMESPACE

class VGSA_View : public QMainWindow
{
    Q_OBJECT

public:
    VGSA_View(QWidget *parent = nullptr);
    ~VGSA_View();

private:
    Ui::VGSA_View *ui;
};
#endif // VGSA_VIEW_H
