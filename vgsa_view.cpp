#include "vgsa_view.h"
#include "ui_vgsa_view.h"

VGSA_View::VGSA_View(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VGSA_View)
{
    ui->setupUi(this);
}

VGSA_View::~VGSA_View()
{
    delete ui;
}

