#ifndef PERIODIC_TDIALOG_H
#define PERIODIC_TDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "view.h"
#include <QString>
namespace Ui {
class Periodic_TDialog;
}

class Periodic_TDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Periodic_TDialog(QWidget *parent = nullptr);
    ~Periodic_TDialog();

    QString getEle() const;
    void setEle(const QString &newEle);

private slots:

    void on_Hydrogen_clicked();

    void on_Lithium_clicked();

    void on_Sodium_clicked();

    void on_K_clicked();

    void on_Rb_clicked();

    void on_Cs_clicked();

    void on_Fr_clicked();

    void on_Be_clicked();

    void on_Mg_clicked();

    void on_Ca_clicked();

    void on_Sr_clicked();

    void on_Ba_clicked();

    void on_Ra_clicked();

    void on_Sc_clicked();

    void on_Y_clicked();

    void on_Ti_clicked();

    void on_Zr_clicked();

    void on_Hf_clicked();

    void on_Rf_clicked();

    void on_La_clicked();

    void on_Ac_clicked();

    void on_V_clicked();

    void on_Nb_clicked();

    void on_Ta_clicked();

    void on_Db_clicked();

    void on_Ce_clicked();

    void on_Th_clicked();

    void on_Cr_clicked();

    void on_Mo_clicked();

    void on_W_clicked();

    void on_Sg_clicked();

    void on_Pr_clicked();

    void on_Pa_clicked();

    void on_Mn_clicked();

    void on_Tc_clicked();

    void on_Re_clicked();

    void on_Bh_clicked();

    void on_Nd_clicked();

    void on_U_clicked();

    void on_Fe_clicked();

    void on_Ru_clicked();

    void on_Os_clicked();

    void on_Hs_clicked();

    void on_Pm_clicked();

    void on_Np_clicked();

    void on_Co_clicked();

    void on_Rh_clicked();

    void on_Ir_clicked();

    void on_Mt_clicked();

    void on_Sm_clicked();

    void on_Pu_clicked();

    void on_Ni_clicked();

    void on_Pd_clicked();

    void on_Pt_clicked();

    void on_Ds_clicked();

    void on_Eu_clicked();

    void on_Am_clicked();

    void on_Cu_clicked();

    void on_Ag_clicked();

    void on_Au_clicked();

    void on_Rg_clicked();

    void on_Gd_clicked();

    void on_Cm_clicked();

    void on_Zn_clicked();

    void on_Cd_clicked();

    void on_Hg_clicked();

    void on_Cn_clicked();

    void on_Tb_clicked();

    void on_Bk_clicked();

    void on_Boron_clicked();

    void on_Al_clicked();

    void on_Ga_clicked();

    void on_In_clicked();

    void on_Tl_clicked();

    void on_Uut_clicked();

    void on_Dy_clicked();

    void on_Cf_clicked();

    void on_Carbon_clicked();

    void on_Si_clicked();

    void on_Ge_clicked();

    void on_Sn_clicked();

    void on_Pb_clicked();

    void on_Fl_clicked();

    void on_Ho_clicked();

    void on_Es_clicked();

    void on_Nitrogen_clicked();

    void on_P_clicked();

    void on_As_clicked();

    void on_Sb_clicked();

    void on_Bi_clicked();

    void on_Uup_clicked();

    void on_Er_clicked();

    void on_Fm_clicked();

    void on_Oxygen_clicked();

    void on_S_clicked();

    void on_Se_clicked();

    void on_Te_clicked();

    void on_Po_clicked();

    void on_Lv_clicked();

    void on_Tm_clicked();

    void on_Md_clicked();

    void on_Flourine_clicked();

    void on_Cl_clicked();

    void on_Br_clicked();

    void on_I_clicked();

    void on_At_clicked();

    void on_Uus_clicked();

    void on_Yb_clicked();

    void on_No_clicked();

    void on_Helium_clicked();

    void on_Neon_clicked();

    void on_Ar_clicked();

    void on_Kr_clicked();

    void on_Xe_clicked();

    void on_Rn_clicked();

    void on_Uuo_clicked();

    void on_Lu_clicked();

    void on_Lr_clicked();


private:
    Ui::Periodic_TDialog *ui;
    Scene *scene;
    QString ele;
};

#endif // PERIODIC_TDIALOG_H
