#ifndef NUMBER_H
#define NUMBER_H

#include <QDialog>
#include "scene.h"
namespace Ui {
class Number;
}

class Number : public QDialog
{
    Q_OBJECT

public:
    explicit Number(QWidget *parent = nullptr);
    ~Number();

    QString getNum() const;
    void setNum(const QString &newNum);

private slots:
    void on_one_clicked();

    void on_two_clicked();

    void on_three_clicked();

    void on_Four_clicked();

    void on_Five_clicked();

    void on_Six_clicked();

    void on_Seven_clicked();

    void on_eight_clicked();

    void on_Nine_clicked();

    void on_zero_clicked();

private:
    Ui::Number *ui;
    Scene *scene;
    QString num;
};

#endif // NUMBER_H
