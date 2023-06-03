#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QTextStream>
#include <QUndoStack>
#include <QUndoCommand>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include "view.h"
#include <QTextCursor>
#include "scene.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Tool {Select, Pen, Eraser, Benz, Rectangle, AddSide, path};
    Q_ENUM(Tool)


    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Tool getTool() const { return m_tool; }

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private slots:
    void on_actionAdd_Image_triggered();

    void on_actionOpen_New_Document_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionPrint_triggered();

    void on_actionSave_triggered();

    void on_actionQuit_triggered();

    void on_actionOpen_Style_Sheets_triggered();

    void on_actionOpen_Template_triggered();

    void on_actionOpen_Samples_triggered();

    void on_actionSave_Style_triggered();

    void on_actionRevert_triggered();

    void on_actionRun_Script_triggered();

    void on_actionPage_Setup_triggered();

    void on_actionDocument_Settings_triggered();

    void on_actionDocument_Annotations_triggered();

    void on_actionApply_Document_Settings_triggered();

    void on_actionPaste_Special_triggered();

    void on_actionClear_triggered();

    void on_actionSelect_All_triggered();

    void on_actionRepeat_General_Show_triggered();

    void on_actionToolbar_triggered();

    void on_actionInsert_Files_triggered();

    void on_actionInsert_Object_triggered();

    void on_actionObjects_triggered();

    void on_actionPen_triggered();

    void on_actionEraser_triggered();

    void on_actionShow_triggered();

    void on_actionDatabase_triggered();

    void on_actionSize_triggered();

    void on_actionPeriodic_Table_triggered();

    void on_actionProperties_triggered();

    void on_actionCheck_Structure_triggered();

    void on_actionLabel_triggered();

    void on_actionStructure_triggered();

    void on_actionMap_triggered();

    void on_actionFlush_Left_triggered();

    void on_actionCentre_triggered();

    void on_actionFlush_Right_triggered();

    void on_actionJustified_triggered();

    void on_actionAutomatic_Justification_triggered();

    void on_actionPlain_triggered();

    void on_actionBold_triggered();

    void on_actionItalic_triggered();

    void on_actionUnderline_triggered();

    void on_actionFormula_triggered();

    void on_actionSubscript_selected_character_triggered();

    void on_actionAdds_a_degree_sign_triggered();

    void on_actionSearch_the_Content_triggered();

    void on_pushButton_10_clicked();

    void on_actionBenzene_triggered();

    void on_actionBackground_Color_triggered();

    void on_actionCursor_triggered();

    void on_actionPen_Color_triggered();

    void on_actionRepeat_triggered();

    void on_actionPentagon_triggered();

    void on_actionNumbers_triggered();

    void on_actionSymbols_triggered();

    void on_penstylecomboBox_activated(int index);

    void on_brushstylecomboBox_activated(int index);

    void on_penwidthcomboBox_activated(int index);

    void on_Quick_Search_Btn_clicked();

    void on_actionLine_triggered();

    void on_centerButton_clicked();

    //void openUrl(const QString& url);

    //void on_linkItemClicked(QGraphicsTextItem* item);

    //********************************//

    void on_actionRectangle_triggered();

    void createRectangle();
    void addSides();
    void removeSides();

    void on_actionaddSide_triggered();

    void on_actionHexagon_triggered();

    //***********************************//

    void on_actionOctagon_triggered();

    void on_chemical_search_Button_clicked();

    void on_actionShow_Rulers_triggered();

    void on_actionShow_Main_Toolbar_triggered();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

    void on_ResetButton_clicked();

    void on_actionShow_Style_Toolbar_triggered();

    void on_actionType_triggered();

private:

    Ui::MainWindow *ui;
    QGraphicsPixmapItem *currentPixmapItem;
    Tool m_tool = Tool::Select;
    View *view;
    Scene * scene;
    QTextCursor m_previousCursor;
    //QUndoStack *undoStack = nullptr;
    QToolBar *toolbar; // Declare QToolBar pointer variable

    //********************************//
    QGraphicsRectItem *rect;

    bool isHoveringOverSide;
    int currentSideIndex;
    enum Side {
        Top,
        Right,
        Bottom,
        Left,
        None
    };

    void addSide(const QPointF& p1, const QPointF& p2);
    void removeSide(int index);
    void updateHoveredSide(const QPointF& pos);
    Side getSideAtPos(const QPointF& pos);

    bool penToolEnabled;

    QStringList searchFiles(const QString& drivePath, const QString& input);
    void displayFile(const QString& filePath);

};

#endif // MAINWINDOW_H
