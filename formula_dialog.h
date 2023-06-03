#ifndef FORMULA_DIALOG_H
#define FORMULA_DIALOG_H

#include <QDialog>
#include "view.h"

namespace Ui {
class formula_dialog;
}

class formula_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit formula_dialog(QWidget *parent = nullptr);
    ~formula_dialog();

    QString getFrml() const;
    void setFrml(const QString &newFrml);

private slots:
    void on_alpha_clicked();
    void on_beta_clicked();

    void on_insert_clicked();

private:
    Ui::formula_dialog *ui;
    QString frml;
    QGraphicsScene *vie;
};

#endif // FORMULA_DIALOG_H
