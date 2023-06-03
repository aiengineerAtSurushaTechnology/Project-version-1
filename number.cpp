#include "number.h"
#include "ui_number.h"

Number::Number(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Number)
{
    ui->setupUi(this);
}

Number::~Number()
{
    delete ui;
}

void Number::on_zero_clicked()
{
    num="0";
    accept();
}

void Number::on_one_clicked()
{
    num="1";
    accept();
}


void Number::on_two_clicked()
{
    num="2";
    accept();
}


void Number::on_three_clicked()
{
    num="3";
    accept();
}


void Number::on_Four_clicked()
{
    num="4";
    accept();
}


void Number::on_Five_clicked()
{
    num="5";
    accept();
}


void Number::on_Six_clicked()
{
    num="6";
    accept();
}


void Number::on_Seven_clicked()
{
    num="7";
    accept();
}


void Number::on_eight_clicked()
{
    num="8";
    accept();
}


void Number::on_Nine_clicked()
{
    num="9";
    accept();
}

QString Number::getNum() const
{
    return num;
}

void Number::setNum(const QString &newNum)
{
    num = newNum;
}
