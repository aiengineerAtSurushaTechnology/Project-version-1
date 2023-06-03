#ifndef SYMBOL_DIALOG_H
#define SYMBOL_DIALOG_H

#include <QDialog>
#include "scene.h"
#include "view.h"
#include <QString>

namespace Ui {
class Symbol_Dialog;
}

class Symbol_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Symbol_Dialog(QWidget *parent = nullptr);
    ~Symbol_Dialog();

    QString getSymbol() const;
    void setSymbol(const QString &newSymbol);

private slots:
    void on_plusButton_clicked();

    void on_minusButton_clicked();

    void on_multiplyButton_clicked();

    void on_divideButton_clicked();

    void on_modulusButton_clicked();

    void on_equalButton_clicked();

private:
    Ui::Symbol_Dialog *ui;
    Scene *scene;
    QString symbol;

};

#endif // SYMBOL_DIALOG_H
