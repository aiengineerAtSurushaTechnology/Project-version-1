#include "symbol_dialog.h"
#include "ui_symbol_dialog.h"
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include "mainwindow.h"
#include "view.h"
#include <QGraphicsScene>
#include <QDebug>

Symbol_Dialog::Symbol_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Symbol_Dialog)
{
    ui->setupUi(this);
}

Symbol_Dialog::~Symbol_Dialog()
{
    delete ui;
}

void Symbol_Dialog::on_plusButton_clicked()
{
    symbol="+";
    accept();
}


void Symbol_Dialog::on_minusButton_clicked()
{
    symbol = "-";
    accept();
}


void Symbol_Dialog::on_multiplyButton_clicked()
{
   symbol = "*";
   accept();
}


void Symbol_Dialog::on_divideButton_clicked()
{
    symbol = "/";
    accept();
}


void Symbol_Dialog::on_modulusButton_clicked()
{
    symbol = "%";
    accept();
}


void Symbol_Dialog::on_equalButton_clicked()
{
    symbol = "=";
    accept();
}


QString Symbol_Dialog::getSymbol() const
{
    return symbol;
}

void Symbol_Dialog::setSymbol(const QString &newSymbol)
{
    symbol = newSymbol;
}

