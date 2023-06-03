#include "periodic_tdialog.h"
#include "ui_periodic_tdialog.h"
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include "mainwindow.h"
#include "view.h"
#include <QGraphicsScene>
#include <QDebug>
Periodic_TDialog::Periodic_TDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Periodic_TDialog)
{
    ui->setupUi(this);
}

Periodic_TDialog::~Periodic_TDialog()
{
    delete ui;
}

void Periodic_TDialog::on_Hydrogen_clicked()
{
    //scene = new Scene();

    ele = "H";
    accept();
//    scene->addText("Hello Abhijeet");
//    qDebug() <<"on button hydrogen clicked";
//    ele = "H";
//    accept();
}

QString Periodic_TDialog::getEle() const
{
    return ele;
}

void Periodic_TDialog::setEle(const QString &newEle)
{
    ele = newEle;
}


void Periodic_TDialog::on_Lithium_clicked()
{
    scene = new Scene();
    //scene->addText("Hello Abhijeet");
    //qDebug() <<"on button hydrogen clicked";
    ele = "Li";
    accept();
}


void Periodic_TDialog::on_Sodium_clicked()
{
    scene = new Scene();
    ele = "Na";
    accept();
}


void Periodic_TDialog::on_K_clicked()
{
    scene = new Scene();
    ele = "K";
    accept();
}


void Periodic_TDialog::on_Rb_clicked()
{
    scene = new Scene();
    ele = "Rb";
    accept();
}


void Periodic_TDialog::on_Cs_clicked()
{
    scene = new Scene();
    ele = "Cs";
    accept();
}


void Periodic_TDialog::on_Fr_clicked()
{
    scene = new Scene();
    ele = "Fr";
    accept();
}


void Periodic_TDialog::on_Be_clicked()
{
    scene = new Scene();
    ele = "Be";
    accept();
}


void Periodic_TDialog::on_Mg_clicked()
{
    scene = new Scene();
    ele = "Mg";
    accept();
}


void Periodic_TDialog::on_Ca_clicked()
{
    scene = new Scene();
    ele = "Ca";
    accept();
}


void Periodic_TDialog::on_Sr_clicked()
{
    scene = new Scene();
    ele = "Sr";
    accept();
}


void Periodic_TDialog::on_Ba_clicked()
{
    scene = new Scene();
    ele = "Ba";
    accept();
}


void Periodic_TDialog::on_Ra_clicked()
{
    scene = new Scene();
    ele = "Ra";
    accept();
}


void Periodic_TDialog::on_Sc_clicked()
{
    scene = new Scene();
    ele = "Sc";
    accept();
}


void Periodic_TDialog::on_Y_clicked()
{
    scene = new Scene();
    ele = "Y";
    accept();
}


void Periodic_TDialog::on_Ti_clicked()
{
    scene = new Scene();
    ele = "Ti";
    accept();
}


void Periodic_TDialog::on_Zr_clicked()
{
    scene = new Scene();
    ele = "Zr";
    accept();
}


void Periodic_TDialog::on_Hf_clicked()
{
    scene = new Scene();
    ele = "Hf";
    accept();
}


void Periodic_TDialog::on_Rf_clicked()
{
    scene = new Scene();
    ele = "Rf";
    accept();
}


void Periodic_TDialog::on_La_clicked()
{
    scene = new Scene();
    ele = "La";
    accept();
}


void Periodic_TDialog::on_Ac_clicked()
{
    scene = new Scene();
    ele = "Ac";
    accept();
}


void Periodic_TDialog::on_V_clicked()
{
    scene = new Scene();
    ele = "V";
    accept();
}


void Periodic_TDialog::on_Nb_clicked()
{
    scene = new Scene();
    ele = "Nb";
    accept();
}


void Periodic_TDialog::on_Ta_clicked()
{
    scene = new Scene();
    ele = "Ta";
    accept();
}


void Periodic_TDialog::on_Db_clicked()
{
    scene = new Scene();
    ele = "Db";
    accept();
}


void Periodic_TDialog::on_Ce_clicked()
{
    scene = new Scene();
    ele = "Ce";
    accept();
}


void Periodic_TDialog::on_Th_clicked()
{
    scene = new Scene();
    ele = "Th";
    accept();
}


void Periodic_TDialog::on_Cr_clicked()
{
    scene = new Scene();
    ele = "Cr";
    accept();
}


void Periodic_TDialog::on_Mo_clicked()
{
    scene = new Scene();
    ele = "Mo";
    accept();
}


void Periodic_TDialog::on_W_clicked()
{
    scene = new Scene();
    ele = "W";
    accept();
}


void Periodic_TDialog::on_Sg_clicked()
{
    scene = new Scene();
    ele = "Sg";
    accept();
}


void Periodic_TDialog::on_Pr_clicked()
{
    scene = new Scene();
    ele = "Pr";
    accept();
}


void Periodic_TDialog::on_Pa_clicked()
{
    scene = new Scene();
    ele = "Pa";
    accept();
}


void Periodic_TDialog::on_Mn_clicked()
{
    scene = new Scene();
    ele = "Mn";
    accept();
}


void Periodic_TDialog::on_Tc_clicked()
{
    scene = new Scene();
    ele = "Tc";
    accept();
}


void Periodic_TDialog::on_Re_clicked()
{
    scene = new Scene();
    ele = "Re";
    accept();
}


void Periodic_TDialog::on_Bh_clicked()
{
    scene = new Scene();
    ele = "Bh";
    accept();
}


void Periodic_TDialog::on_Nd_clicked()
{
    scene = new Scene();
    ele = "Nd";
    accept();
}


void Periodic_TDialog::on_U_clicked()
{
    scene = new Scene();
    ele = "U";
    accept();
}


void Periodic_TDialog::on_Fe_clicked()
{
    scene = new Scene();
    ele = "Fe";
    accept();
}


void Periodic_TDialog::on_Ru_clicked()
{
    scene = new Scene();
    ele = "Ru";
    accept();
}


void Periodic_TDialog::on_Os_clicked()
{
    scene = new Scene();
    ele = "Os";
    accept();
}


void Periodic_TDialog::on_Hs_clicked()
{
    scene = new Scene();
    ele = "Hs";
    accept();
}


void Periodic_TDialog::on_Pm_clicked()
{
    scene = new Scene();
    ele = "Pm";
    accept();
}


void Periodic_TDialog::on_Np_clicked()
{
    scene = new Scene();
    ele = "Np";
    accept();
}


void Periodic_TDialog::on_Co_clicked()
{
    scene = new Scene();
    ele = "Co";
    accept();
}


void Periodic_TDialog::on_Rh_clicked()
{
    scene = new Scene();
    ele = "Rh";
    accept();
}


void Periodic_TDialog::on_Ir_clicked()
{
    scene = new Scene();
    ele = "Ir";
    accept();
}


void Periodic_TDialog::on_Mt_clicked()
{
    scene = new Scene();
    ele = "Mt";
    accept();
}


void Periodic_TDialog::on_Sm_clicked()
{
    scene = new Scene();
    ele = "Sm";
    accept();
}


void Periodic_TDialog::on_Pu_clicked()
{
    scene = new Scene();
    ele = "Pu";
    accept();
}


void Periodic_TDialog::on_Ni_clicked()
{
    scene = new Scene();
    ele = "Ni";
    accept();
}


void Periodic_TDialog::on_Pd_clicked()
{
    scene = new Scene();
    ele = "Pd";
    accept();
}


void Periodic_TDialog::on_Pt_clicked()
{
    scene = new Scene();
    ele = "Pt";
    accept();
}


void Periodic_TDialog::on_Ds_clicked()
{
    scene = new Scene();
    ele = "Ds";
    accept();
}


void Periodic_TDialog::on_Eu_clicked()
{
    scene = new Scene();
    ele = "Eu";
    accept();
}


void Periodic_TDialog::on_Am_clicked()
{
    scene = new Scene();
    ele = "Am";
    accept();
}


void Periodic_TDialog::on_Cu_clicked()
{
    scene = new Scene();
    ele = "Cu";
    accept();
}


void Periodic_TDialog::on_Ag_clicked()
{
    scene = new Scene();
    ele = "Ag";
    accept();
}


void Periodic_TDialog::on_Au_clicked()
{
    scene = new Scene();
    ele = "Au";
    accept();
}


void Periodic_TDialog::on_Rg_clicked()
{
    scene = new Scene();
    ele = "Rg";
    accept();
}


void Periodic_TDialog::on_Gd_clicked()
{
    scene = new Scene();
    ele = "Gd";
    accept();
}


void Periodic_TDialog::on_Cm_clicked()
{
    scene = new Scene();
    ele = "Cm";
    accept();
}


void Periodic_TDialog::on_Zn_clicked()
{
    scene = new Scene();
    ele = "Zn";
    accept();
}


void Periodic_TDialog::on_Cd_clicked()
{
    scene = new Scene();
    ele = "Cd";
    accept();
}


void Periodic_TDialog::on_Hg_clicked()
{
    scene = new Scene();
    ele = "Hg";
    accept();
}


void Periodic_TDialog::on_Cn_clicked()
{
    scene = new Scene();
    ele = "Cn";
    accept();
}


void Periodic_TDialog::on_Tb_clicked()
{
    scene = new Scene();
    ele = "Tb";
    accept();
}


void Periodic_TDialog::on_Bk_clicked()
{
    scene = new Scene();
    ele = "Bk";
    accept();
}


void Periodic_TDialog::on_Boron_clicked()
{
    scene = new Scene();
    ele = "B";
    accept();
}


void Periodic_TDialog::on_Al_clicked()
{
    scene = new Scene();
    ele = "Al";
    accept();
}


void Periodic_TDialog::on_Ga_clicked()
{
    scene = new Scene();
    ele = "Ga";
    accept();
}


void Periodic_TDialog::on_In_clicked()
{
    scene = new Scene();
    ele = "In";
    accept();
}


void Periodic_TDialog::on_Tl_clicked()
{
    scene = new Scene();
    ele = "Tl";
    accept();
}


void Periodic_TDialog::on_Uut_clicked()
{
    scene = new Scene();
    ele = "Uut";
    accept();
}


void Periodic_TDialog::on_Dy_clicked()
{
    scene = new Scene();
    ele = "Dy";
    accept();
}


void Periodic_TDialog::on_Cf_clicked()
{
    scene = new Scene();
    ele = "Cf";
    accept();
}


void Periodic_TDialog::on_Carbon_clicked()
{
    scene = new Scene();
    ele = "C";
    accept();
}


void Periodic_TDialog::on_Si_clicked()
{
    scene = new Scene();
    ele = "Si";
    accept();
}


void Periodic_TDialog::on_Ge_clicked()
{
    scene = new Scene();
    ele = "Ge";
    accept();
}


void Periodic_TDialog::on_Sn_clicked()
{
    scene = new Scene();
    ele = "Sn";
    accept();
}


void Periodic_TDialog::on_Pb_clicked()
{
    scene = new Scene();
    ele = "Pb";
    accept();
}


void Periodic_TDialog::on_Fl_clicked()
{
    scene = new Scene();
    ele = "Fl";
    accept();
}


void Periodic_TDialog::on_Ho_clicked()
{
    scene = new Scene();
    ele = "Ho";
    accept();
}


void Periodic_TDialog::on_Es_clicked()
{
    scene = new Scene();
    ele = "Es";
    accept();
}


void Periodic_TDialog::on_Nitrogen_clicked()
{
    scene = new Scene();
    ele = "N";
    accept();
}


void Periodic_TDialog::on_P_clicked()
{
    scene = new Scene();
    ele = "P";
    accept();
}


void Periodic_TDialog::on_As_clicked()
{
    scene = new Scene();
    ele = "As";
    accept();
}


void Periodic_TDialog::on_Sb_clicked()
{
    scene = new Scene();
    ele = "Sb";
    accept();
}


void Periodic_TDialog::on_Bi_clicked()
{
    scene = new Scene();
    ele = "Bi";
    accept();
}


void Periodic_TDialog::on_Uup_clicked()
{
    scene = new Scene();
    ele = "Uup";
    accept();
}


void Periodic_TDialog::on_Er_clicked()
{
    scene = new Scene();
    ele = "Er";
    accept();
}


void Periodic_TDialog::on_Fm_clicked()
{
    scene = new Scene();
    ele = "Fm";
    accept();
}


void Periodic_TDialog::on_Oxygen_clicked()
{
    scene = new Scene();
    ele = "O";
    accept();
}


void Periodic_TDialog::on_S_clicked()
{
    scene = new Scene();
    ele = "S";
    accept();
}


void Periodic_TDialog::on_Se_clicked()
{
    scene = new Scene();
    ele = "Se";
    accept();
}


void Periodic_TDialog::on_Te_clicked()
{
    scene = new Scene();
    ele = "Te";
    accept();
}


void Periodic_TDialog::on_Po_clicked()
{
    scene = new Scene();
    ele = "Po";
    accept();
}


void Periodic_TDialog::on_Lv_clicked()
{
    scene = new Scene();
    ele = "Lv";
    accept();
}


void Periodic_TDialog::on_Tm_clicked()
{
    scene = new Scene();
    ele = "Tm";
    accept();
}


void Periodic_TDialog::on_Md_clicked()
{
    scene = new Scene();
    ele = "Md";
    accept();
}


void Periodic_TDialog::on_Flourine_clicked()
{
    scene = new Scene();
    ele = "F";
    accept();
}


void Periodic_TDialog::on_Cl_clicked()
{
    scene = new Scene();
    ele = "Cl";
    accept();
}


void Periodic_TDialog::on_Br_clicked()
{
    scene = new Scene();
    ele = "Br";
    accept();
}


void Periodic_TDialog::on_I_clicked()
{
    scene = new Scene();
    ele = "I";
    accept();
}


void Periodic_TDialog::on_At_clicked()
{
    scene = new Scene();
    ele = "At";
    accept();
}


void Periodic_TDialog::on_Uus_clicked()
{
    scene = new Scene();
    ele = "Uus";
    accept();
}


void Periodic_TDialog::on_Yb_clicked()
{
    scene = new Scene();
    ele = "Yb";
    accept();
}


void Periodic_TDialog::on_No_clicked()
{
    scene = new Scene();
    ele = "No";
    accept();
}


void Periodic_TDialog::on_Helium_clicked()
{
    scene = new Scene();
    ele = "He";
    accept();
}


void Periodic_TDialog::on_Neon_clicked()
{
    scene = new Scene();
    ele = "Ne";
    accept();
}


void Periodic_TDialog::on_Ar_clicked()
{
    scene = new Scene();
    ele = "Ar";
    accept();
}


void Periodic_TDialog::on_Kr_clicked()
{
    scene = new Scene();
    ele = "Kr";
    accept();
}


void Periodic_TDialog::on_Xe_clicked()
{
    scene = new Scene();
    ele = "Xe";
    accept();
}


void Periodic_TDialog::on_Rn_clicked()
{
    scene = new Scene();
    ele = "Rn";
    accept();
}


void Periodic_TDialog::on_Uuo_clicked()
{
    scene = new Scene();
    ele = "Uuo";
    accept();
}


void Periodic_TDialog::on_Lu_clicked()
{
    scene = new Scene();
    ele = "Lu";
    accept();
}


void Periodic_TDialog::on_Lr_clicked()
{
    scene = new Scene();
    ele = "Lr";
    accept();
}


