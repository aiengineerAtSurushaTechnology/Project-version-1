#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QMainWindow>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QTextEdit>
#include <QWidget>
#include <QPlainTextEdit>
#include <QScrollArea>
#include "horizontalruler.h"
#include "verticalruler.h"
#include <QResizeEvent>

namespace Ui {
class TextEdit;
}

class TextEdit : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEdit(QWidget *parent = nullptr);
    ~TextEdit();

private slots:
    void on_actionNew_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionSave_triggered();

    void on_actionSave_2_triggered();

    void on_actionPrint_triggered();

    void on_actionClose_triggered();

    void on_actionFlush_Left_triggered();

    void on_actionCentre_triggered();

    void on_actionFlush_Right_triggered();

    void on_actionJustified_triggered();

    void on_actionAutomatic_Justified_triggered();

    void on_actionPlain_triggered();

    void on_actionBold_triggered();

    void on_actionItalic_triggered();

    void on_actionUnderline_triggered();

    void on_actionFormula_triggered();

    void on_actionSubscript_selected_character_triggered();

    void on_actionAdds_a_degree_sign_triggered();

    void on_actionClean_triggered();

    void on_actionSelect_All_triggered();

    void on_actionPrint_Preview_triggered();

    void renderPreview(QPrinter *printer);

    void on_actionBackground_Color_triggered();

    void on_actionText_Color_triggered();

    void on_actionPower_off_Selected_Text_triggered();

    void on_actionOpen_triggered();

    void on_actionPage_Setup_2_triggered();

    void on_actionRuler_triggered();

    void on_actionToolbar_triggered();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::TextEdit *ui;
    //QTextEdit *formulaEditor;

    HorizontalRuler *horizontalRuler;
    VerticalRuler *verticalRuler;

    void adjustRulerSizes();
};

#endif // TEXTEDIT_H
