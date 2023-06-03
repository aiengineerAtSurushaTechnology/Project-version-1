#include "formula_dialog.h"
#include "ui_formula_dialog.h"

formula_dialog::formula_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formula_dialog)
{
    ui->setupUi(this);
}

formula_dialog::~formula_dialog()
{
    delete ui;
}

QString formula_dialog::getFrml() const
{
    return frml;
}

void formula_dialog::setFrml(const QString &newFrml)
{
    frml = newFrml;
}

void formula_dialog::on_alpha_clicked()
{
frml.push_back("α");
ui->textEdit ->setPlainText(frml);
}

void formula_dialog::on_beta_clicked()
{
    frml.push_back("β");
    ui->textEdit ->setPlainText(frml);
}


void formula_dialog::on_insert_clicked()
{
    vie = new QGraphicsScene();
    frml = ui->textEdit->toPlainText();
//    qDebug() << "HIII";
    accept();
}

