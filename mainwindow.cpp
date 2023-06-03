#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QGraphicsView>
#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QUndoStack>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QKeyEvent>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QMimeData>
#include <QClipboard>
#include <QFontDialog>
#include "textedit.h"
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include "view.h"
#include <QColorDialog>
#include <QPrintPreviewDialog>
#include <QGraphicsProxyWidget>
#include "periodic_tdialog.h"
#include "scene.h"
#include <QColor>
#include "formula_dialog.h"
#include "number.h"
#include "symbol_dialog.h"
#include "colorpicker.h"
#include <Python.h>
#include <QInputDialog>
#include <QGraphicsItem>
#include <QSpinBox>
#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>
#include <QHoverEvent>
#include "myrectitem.h"
#include <QProcess>
#include "pyrun.h"
#include "benzene.h"
#include "pentagon.h"
#include "hexagon.h"
#include <QDirIterator>
#include "lineitem.h"
//#include "searchdialog.h"
#include "editablelineitem.h"
#include "editablepixmapitem.h"
#include "typerectitem.h"
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      isHoveringOverSide(false),
      currentSideIndex(-1),
      rect(nullptr)
{
    ui->setupUi(this);
    scene = new Scene(this);
    penToolEnabled = false;


    //scene->setSceneRect(-250,-300,1200,680);
    ui->graphicsView->setScene(scene);

    //pen Style
    ui->penstylecomboBox->addItem(QIcon(":/images/pen_style_solid.png") ,"Solid");
    ui->penstylecomboBox->addItem(QIcon(":/images/pen_style_dashed.png"),"Dashed");
    ui->penstylecomboBox->addItem(QIcon(":/images/pen_style_dotted.png"),"Dotted");
    ui->penstylecomboBox->addItem(QIcon(":/images/pen_style_dot_dashed.png"),"Dot Dashed");

    //Brush Style
    ui->brushstylecomboBox->addItem("Solid");
    ui->brushstylecomboBox->addItem("Dense");
    ui->brushstylecomboBox->addItem("Horizontal Lines");
    ui->brushstylecomboBox->addItem("Vertical Lines");
    ui->brushstylecomboBox->addItem("Cross Pattern");


    //pen width
    ui->penwidthcomboBox->addItem("1");
    ui->penwidthcomboBox->addItem("2");
    ui->penwidthcomboBox->addItem("3");
    ui->penwidthcomboBox->addItem("4");
    ui->penwidthcomboBox->addItem("5");
    ui->penwidthcomboBox->addItem("6");

    connect(ui->actionLine, &QAction::triggered, this, [this]() {
        if (scene) {
            // Create a LineItem object
            LineItem* line = new LineItem();

            // Set the line's start and end points
            //line->setLine(0, 50, 100, 50);

            // Set the pen color and thickness of the line
            QPen pen(Qt::black);
            pen.setWidth(2);
            line->setPen(pen);

            // Enable the movable and selectable flags of the line
            line->setFlag(QGraphicsItem::ItemIsMovable);
            line->setFlag(QGraphicsItem::ItemIsSelectable);

            // Add the line to the scene
            scene->addItem(line);
        }
    });


//    view = new View(this);
//    view->setScene(scene);

    //ui->showGridCheckbox->setChecked(view->getDrawGridLines());


}

MainWindow::~MainWindow()
{
    delete ui;

    //ui->graphicsView = new QGraphicsView(ui->centralwidget);

    Scene *scene = new Scene(this);
    //Scene *scene = new Scene(this);
    //ui->graphicsView->setScene(scene);
}

//**********************************//

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // QGraphicsView::mousePressEvent(event);


    if (event->button() == Qt::LeftButton && scene->tool() == Scene::Rectangle ) {
        //        MyRectItem *rectItem = new MyRectItem();
        //        rectItem->setRect(-50, -50, 100, 100);
        //        rectItem->setFlag(QGraphicsItem::ItemIsMovable);
        //        rectItem->setPos(ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos())));
        //        ui->graphicsView->scene()->addItem(rectItem);
        //        rect = scene->addRect(QRectF(-50, -50, 100, 100), QPen(Qt::black));
        //        rect->setPos(ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos())));
        //        rect->setFlag(QGraphicsItem::ItemIsMovable);
        createRectangle();
        //        QPointF pos = ui->graphicsView->mapFromGlobal(QCursor::pos());
        //        rect = new QGraphicsRectItem(pos.x(), pos.y(), 100, 50);
        //        scene->addItem(rect);
        //    connect(rectItem, &MyRectItem::hoverEnter, this, &MainWindow::addSides);
    }
    if (event->button() == Qt::LeftButton && rect) {
        qDebug()<<" inside rectangle clicked";
        QPointF mousePos = ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos()));
        if (rect->contains(rect->mapFromScene(mousePos))) {
            if (currentSideIndex != -1) {
                removeSide(currentSideIndex);
                switch (currentSideIndex) {
                case Left:
                    rect->setRect(rect->rect().translated(rect->rect().width() / 2, 0).intersected(QRectF(0, 0, 999, 999)));
                    qDebug() << " remove left side";
                    break;
                case Right:
                    rect->setRect(rect->rect().translated(-rect->rect().width() / 2, 0).intersected(QRectF(0, 0, 999, 999)));
                    qDebug() << " remove right side";
                    break;
                case Top:
                    rect->setRect(rect->rect().translated(0, rect->rect().height() / 2).intersected(QRectF(0, 0, 999, 999)));
                    qDebug() << " remove top side";
                    break;
                case Bottom:
                    rect->setRect(rect->rect().translated(0, -rect->rect().height() / 2).intersected(QRectF(0, 0, 999, 999)));
                    qDebug() << " remove bottom side";
                    break;
                }
                isHoveringOverSide = false;
                currentSideIndex = -1;
            } else {
                qDebug() << " Outside Rectangle clicked";
            }
        }

    }
    if (event->button() == Qt::LeftButton && scene->tool() == Scene::Benzene ) {
        //        QGraphicsScene *scene = ui->graphicsView->scene();
        //           Benzene *benzene = new Benzene(scene);
        //           scene->addItem(benzene);

        /*Benzene *benzene = new Benzene(50, scene); // pass the QGraphicsScene pointer to the constructor
             benzene->setPos(ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos())));
            benzene->setFlag(QGraphicsItem::ItemIsMovable);
             scene->addItem(benzene);*/

        // add the Benzene object to the QGraphicsScene
        QPointF pos = ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos()));
        Benzene* benzene = new Benzene(pos);
        ui->graphicsView->scene()->addItem(benzene);
        //            ui->graphicsView->setScene(scene);
        //            ui->graphicsView->show();
    }
    if (event->button() == Qt::LeftButton && scene->tool() == Scene::Pentagon ) {

        QPointF pos = ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos()));
        Pentagon* pentagon = new Pentagon(pos);
        scene->addItem(pentagon);


    }
    if (event->button() == Qt::LeftButton && scene->tool() == Scene::Hexagon ) {
        QPointF pos = ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos()));
        Hexagon* hexagon = new Hexagon(pos);
        ui->graphicsView->scene()->addItem(hexagon);
    }
    if (event->button() == Qt::LeftButton && scene->tool() == Scene::AddSide ) {
        if (!rect) {
            qWarning() << "Please create a rectangle first";
            return;
        }

        // Get the position of the mouse cursor in scene coordinates
        QPointF mousePos = ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos()));

        // Get the side that the mouse is closest to
        Side side = getSideAtPos(mousePos);
        if (side == -1) {
            qWarning() << "Mouse is not hovering over a side";
            return;
        }

        // Get the two points that define the side
        QPointF p1(rect->rect().left() + (side * rect->rect().width() / 2), rect->rect().top() + (side * rect->rect().height() / 2));
        QPointF p2(rect->rect().left() + ((side + 1) * rect->rect().width() / 2), rect->rect().top() + ((side + 1) * rect->rect().height() / 2));

        // Add the line item to the scene and set its data to the side index
        QPen pen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        QGraphicsLineItem* line = scene->addLine(QLineF(rect->mapToScene(p1), rect->mapToScene(p2)), pen);
        line->setZValue(-1);
        line->setData(0, side);
    }
    QPointF mousePos = ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos()));
    QList<QGraphicsItem*> itemList = scene->items(mousePos);
    for(QGraphicsItem* item : itemList)
    {
        if(item->type() == QGraphicsRectItem::Type)
        {
            QGraphicsRectItem* rect = qgraphicsitem_cast<QGraphicsRectItem*>(item);
            QRectF rectGeometry = rect->rect();
            QPointF topLeft = rect->mapToScene(rectGeometry.topLeft());
            QPointF bottomRight = rect->mapToScene(rectGeometry.bottomRight());
            qreal tolerance = 5;
            if(qAbs(topLeft.x() - mousePos.x()) <= tolerance) // left side
            {
                QPointF start = rect->mapToScene(rectGeometry.topLeft() + QPointF(0, rectGeometry.height() / 2));
                QPointF end = rect->mapToScene(rectGeometry.bottomLeft() + QPointF(0, -rectGeometry.height() / 2));
                addSide(start, end);
                qDebug() << "left side";
            }
            else if(qAbs(bottomRight.x() - mousePos.x()) <= tolerance) // right side
            {
                QPointF start = rect->mapToScene(rectGeometry.topRight() + QPointF(0, rectGeometry.height() / 2));
                QPointF end = rect->mapToScene(rectGeometry.bottomRight() + QPointF(0, -rectGeometry.height() / 2));
                addSide(start, end);
                qDebug() << "right side";
            }
            else if(qAbs(topLeft.y() - mousePos.y()) <= tolerance) // top side
            {
                QPointF start = rect->mapToScene(rectGeometry.topLeft() + QPointF(rectGeometry.width() / 2, 0));
                QPointF end = rect->mapToScene(rectGeometry.topRight() + QPointF(-rectGeometry.width() / 2, 0));
                addSide(start, end);
                qDebug() << "top side";
            }
            else if(qAbs(bottomRight.y() - mousePos.y()) <= tolerance) // bottom side
            {
                QPointF start = rect->mapToScene(rectGeometry.bottomLeft() + QPointF(rectGeometry.width() / 2, 0));
                QPointF end = rect->mapToScene(rectGeometry.bottomRight() + QPointF(-rectGeometry.width() / 2, 0));
                addSide(start, end);
                qDebug() <<"bottom side";
            }
        }
    }
}

void MainWindow::createRectangle()
{
    QPointF mousePos = ui->graphicsView->mapToScene(ui->graphicsView->mapFromGlobal(QCursor::pos()));
    QPointF startPoint(mousePos);
    const qreal width = 100;
    const qreal height = 80;
    QPen pen(Qt::black, 1);

    // Create the four lines
    QGraphicsLineItem* leftLine = new QGraphicsLineItem(startPoint.x(), startPoint.y(), startPoint.x(), startPoint.y() + height);
    QGraphicsLineItem* rightLine = new QGraphicsLineItem(startPoint.x() + width, startPoint.y(), startPoint.x() + width, startPoint.y() + height);
    QGraphicsLineItem* topLine = new QGraphicsLineItem(startPoint.x(), startPoint.y(), startPoint.x() + width, startPoint.y());
    QGraphicsLineItem* bottomLine = new QGraphicsLineItem(startPoint.x(), startPoint.y() + height, startPoint.x() + width, startPoint.y() + height);

    // Set the pen and add the lines to the scene
    leftLine->setPen(pen);
    rightLine->setPen(pen);
    topLine->setPen(pen);
    bottomLine->setPen(pen);
    scene->addItem(leftLine);
    scene->addItem(rightLine);
    scene->addItem(topLine);
    scene->addItem(bottomLine);
}

void MainWindow::addSide(const QPointF& p1, const QPointF& p2)
{
    QPen pen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QGraphicsLineItem* line = scene->addLine(QLineF(p1, p2), pen);
    line->setZValue(-1);
}

void MainWindow::removeSide(int index)
{
    if ((index < 0) || (index > 3)){
        return;
    }
    QList<QGraphicsItem*> items = scene->items();
    foreach (QGraphicsItem* item, items) {
        QGraphicsLineItem* line = qgraphicsitem_cast<QGraphicsLineItem*>(item);
        if (line && line->data(0) == index) {
            scene->removeItem(line);
            delete line;
        }
    }
}

void MainWindow::updateHoveredSide(const QPointF& pos)
{
    Side hoveredSide = getSideAtPos(pos);
    if (hoveredSide != currentSideIndex) {
        if (isHoveringOverSide) {
            removeSide(currentSideIndex);
        }

        if (hoveredSide != -1) {
            QPen pen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
            QGraphicsLineItem* line = scene->addLine(QLineF(rect->mapToScene(rect->rect().topLeft() + QPointF(hoveredSide * rect->rect().width() / 2,
                                                                                                              hoveredSide * rect->rect().height() / 2)),
                                                            rect->mapToScene(rect->rect().topLeft() + QPointF((hoveredSide + 1) * rect->rect().width() / 2,
                                                                                                              (hoveredSide + 1) * rect->rect().height() / 2))), pen);
            //            addSide(rect->mapToScene(rect->rect().topLeft() + QPointF(hoveredSide * rect->rect().width() / 2,
            //                                                                      hoveredSide * rect->rect().height() / 2)),
            //                    rect->mapToScene(rect->rect().topLeft() + QPointF((hoveredSide + 1) * rect->rect().width() / 2,
            //                                                                      (hoveredSide + 1) * rect->rect().height() / 2)));
            isHoveringOverSide = true;
            currentSideIndex = hoveredSide;
        } else {
            isHoveringOverSide = false;
            currentSideIndex = -1;
        }
    }
}

MainWindow::Side MainWindow::getSideAtPos(const QPointF& pos)
{
    QPointF rectPos = rect->mapFromScene(pos);
    qreal w = rect->rect().width();
    qreal h = rect->rect().height();
    qreal x = rectPos.x();
    qreal y = rectPos.y();
    qreal tolerance = 5;
    if (qAbs(x) <= tolerance && y >= -tolerance && y <= h + tolerance) { // left side
        return Left;
    } else if (qAbs(x - w) <= tolerance && y >= -tolerance && y <= h + tolerance) { // right side
        return Right;
    } else if (qAbs(y) <= tolerance && x >= -tolerance && x <= w + tolerance) { // top side
        return Top;
    } else if (qAbs(y - h) <= tolerance && x >= -tolerance && x <= w + tolerance) { // bottom side
        return Bottom;
    } else {
        return None;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    //QGraphicsView::mouseMoveEvent(event);
    if (rect) {
        QPointF mousePos = ui->graphicsView->mapToScene(event->pos());
        if (rect->contains(rect->mapFromScene(mousePos))) {
            updateHoveredSide(mousePos);
        } else {
            if (isHoveringOverSide) {
                removeSide(currentSideIndex);
                isHoveringOverSide = false;
                currentSideIndex = -1;
            }
        }
    }
    if((event->buttons() & Qt::LeftButton) && Scene::Eraser)
    {
        QList<QGraphicsItem*> items = scene->items();
        foreach (QGraphicsItem* item, items) {
            QGraphicsLineItem* line = qgraphicsitem_cast<QGraphicsLineItem*>(item);
            if (line && line->parentItem() == rect) {
                scene->removeItem(line);
                delete line;
            }
        }
        qDebug() << "TO remove Sides";
    }
}

void MainWindow::addSides()
{
    // Get the rectangle item that was hovered over
    QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem*>(sender());

    // Create four line items for the sides of the rectangle
    QLineF topLine(rectItem->rect().topLeft(), rectItem->rect().topRight());
    QLineF rightLine(rectItem->rect().topRight(), rectItem->rect().bottomRight());
    QLineF bottomLine(rectItem->rect().bottomLeft(), rectItem->rect().bottomRight());
    QLineF leftLine(rectItem->rect().topLeft(), rectItem->rect().bottomLeft());

    // Add the line items to the graphics scene
    QGraphicsScene *scene = ui->graphicsView->scene();
    scene->addLine(topLine, QPen(Qt::black));
    scene->addLine(rightLine, QPen(Qt::black));
    scene->addLine(bottomLine, QPen(Qt::black));
    scene->addLine(leftLine, QPen(Qt::black));
}

void MainWindow::removeSides()
{
    // Get the rectangle item that was hovered over
    QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem*>(sender());

    // Remove the line items from the graphics scene
    QGraphicsScene *scene = ui->graphicsView->scene();
    QList<QGraphicsItem*> items = scene->items();
    foreach (QGraphicsItem *item, items) {
        if (item->type() == QGraphicsLineItem::Type && item->parentItem() == rectItem) {
            scene->removeItem(item);
            delete item;
        }
    }
}

//******************************//

void MainWindow::on_actionAdd_Image_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    if(fileName.isNull())
        return;

    QPixmap image(fileName);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(image);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addItem(item);
    ui->graphicsView->setScene(scene);

    currentPixmapItem = item;
    currentPixmapItem->setFlag(QGraphicsItem::ItemIsMovable);
    currentPixmapItem->setFlag(QGraphicsItem::ItemIsSelectable);
}

void MainWindow::on_actionOpen_New_Document_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QString(), tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open file: ") + file.errorString());
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    // Create a QGraphicsTextItem to display the file content
    QGraphicsTextItem* textItem = new QGraphicsTextItem(fileContent);
    textItem->setTextInteractionFlags(Qt::TextEditorInteraction | Qt::TextBrowserInteraction);  // make the text selectable and editable
    textItem->setPos(0, 0);  // set the position of the text item in the scene

    // Create a new QGraphicsScene and add the text item to it
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addItem(textItem);

    // Set the scene of the QGraphicsView to the new scene
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_actionUndo_triggered()
{
    ui->lineEdit->undo();
    //ui->graphicsView->undo();
    scene->undo();
    //scene->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->lineEdit->redo();
    scene->redo();
    //scene->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->lineEdit->copy();
    scene->copy();

}

void MainWindow::on_actionCut_triggered()
{
    ui->lineEdit->cut();
    scene->cut();

}

void MainWindow::on_actionPaste_triggered()
{
    ui->lineEdit->paste();
    scene->paste();

}

void MainWindow::on_actionPrint_triggered()
{
    // Get a pointer to the scene
    QGraphicsScene* scene = ui->graphicsView->scene();

    // Create a new printer object
    QPrinter printer(QPrinter::HighResolution);

    // Create a new print dialog and set the printer
    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted) {
        // Create a QPainter object to render the scene
        QPainter painter(&printer);

        // Set the resolution of the printer
        printer.setResolution(300);

        // Set rendering hints
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

        // Get the page layout
        QPageLayout layout = printer.pageLayout();
        QRectF pageRect = layout.paintRectPixels(printer.resolution());

        // Set the scene rect to match the page rect
        scene->setSceneRect(pageRect);
        ui->graphicsView->fitInView(pageRect, Qt::KeepAspectRatio);

        // Render the scene onto the printer
        scene->render(&painter);
    }
}

void MainWindow::on_actionSave_triggered()
{
    // Get the file name from a file dialog
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    // Return if no file was selected
    if (fileName.isEmpty()) {
        return;
    }

    // Open the file and write the contents of the QGraphicsTextItem to it
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to save file"));
        return;
    }
    QTextStream out(&file);
    QGraphicsTextItem* textItem = qgraphicsitem_cast<QGraphicsTextItem*>(ui->graphicsView->scene()->focusItem());
    if (textItem) {
        out << textItem->toPlainText();
    }
    file.close();
}

void MainWindow::on_actionQuit_triggered()
{
    //MainWindow::close();
    qApp->quit();
}

void MainWindow::on_actionOpen_Style_Sheets_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Style Sheet", "", "CSS Files (*.css)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString styleSheet = file.readAll();
            ui->graphicsView->setStyleSheet(styleSheet);
            file.close();
        } else {
            QMessageBox::warning(this, "Error", QString("Failed to open file %1").arg(fileName));
        }
    }
}

void MainWindow::on_actionOpen_Template_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.png *.xpm *.jpg)"));
    if(fileName != "") {
        QImage image(fileName);
        if(!image.isNull()) {
            QGraphicsScene* scene = new QGraphicsScene();
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            scene->addItem(item);
            ui->graphicsView->setScene(scene);
            ui->graphicsView->fitInView(item, Qt::KeepAspectRatio);
        }
    }
}

void MainWindow::on_actionOpen_Samples_triggered()
{
    //    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Image Files (*.png *.jpg *.bmp);;PDF Files (*.pdf);;Text Files (*.txt)"));
    //    if (!fileName.isEmpty())
    //    {
    //        QGraphicsItem *item = nullptr;
    //        QString ext = QFileInfo(fileName).suffix();
    //        if (ext == "pdf") {
    //            // Convert PDF to image using Poppler library
    //            Poppler::Document *doc = Poppler::Document::load(fileName);
    //            if (doc && !doc->isLocked()) {
    //                Poppler::Page *page = doc->page(0);
    //                QImage image = page->renderToImage(72, 72);
    //                item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    //                delete page;
    //            }
    //            delete doc;
    //        } else if (ext == "txt") {
    //            // Read text file and create QGraphicsTextItem object
    //            QFile file(fileName);
    //            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    //                QTextStream in(&file);
    //                QString text = in.readAll();
    //                item = new QGraphicsTextItem(text);
    //            }
    //        } else {
    //            // Load image file
    //            item = new QGraphicsPixmapItem(QPixmap(fileName));
    //        }

    //        if (item) {
    //            QGraphicsScene *scene = new QGraphicsScene(this);
    //            scene->addItem(item);
    //            ui->graphicsView->setScene(scene);
    //        }
    //    }
}


void MainWindow::on_actionSave_Style_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Style"), "", tr("Style files (*.style)"));

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QTextStream out(&file);
    out << ui->graphicsView->styleSheet();
    file.close();
}

void MainWindow::on_actionRevert_triggered()
{

}

void MainWindow::on_actionRun_Script_triggered()
{

}

void MainWindow::on_actionPage_Setup_triggered()
{
    static bool isPrinterSize = false; // Flag to track the current state

    if (!isPrinterSize) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setPageSize(QPageSize(QPageSize::A4));

        QRectF sceneRect(0, 0, printer.width(), printer.height());
        scene->setSceneRect(sceneRect);
        isPrinterSize = true; // Update the flag
    } else {
        // Restore the default size here
        QRectF defaultRect(0, 0, 800, 600); // Replace with your default width and height
        scene->setSceneRect(defaultRect);
        isPrinterSize = false; // Update the flag
    }
}

void MainWindow::on_actionDocument_Settings_triggered()
{
    // Create the dialog and spin box
    QDialog dialog(this);
    QSpinBox spinBox(&dialog);
    spinBox.setRange(0, 100);
    spinBox.setValue(50);
    QLabel label("Margin size:", &dialog);

    // Create the apply button
    QPushButton applyButton("Apply", &dialog);
    applyButton.setDefault(true);

    // Layout the dialog
    QVBoxLayout layout(&dialog);
    layout.addWidget(&label);
    layout.addWidget(&spinBox);
    layout.addWidget(&applyButton);

    // Connect the "Apply" button clicked() signal to close the dialog and apply the margin
    connect(&applyButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // Show the dialog and wait for it to close
    dialog.setWindowTitle("Document Settings");
    if (dialog.exec() == QDialog::Rejected) {
        // Dialog was cancelled
        return;
    }

    // Get the selected margin size
    int newMargin = spinBox.value();

    // Get the current margin size
    int oldMargin = qRound(ui->graphicsView->sceneRect().left());

    // Calculate the change in margin size
    int marginChange = newMargin - oldMargin;

    // Get the QGraphicsScene and adjust the scene rectangle
    QGraphicsScene* scene = ui->graphicsView->scene();
    QRectF viewportRect = ui->graphicsView->viewport()->rect();
    QRectF newSceneRect = viewportRect.adjusted(newMargin, newMargin, -newMargin, -newMargin);
    QRectF oldSceneRect = scene->sceneRect();
    scene->setSceneRect(newSceneRect);

    // Calculate the change in scene rectangle
    qreal dx = newSceneRect.left() - oldSceneRect.left();
    qreal dy = newSceneRect.top() - oldSceneRect.top();

    // Adjust the positions of the items in the scene
    foreach (QGraphicsItem* item, scene->items()) {
        item->moveBy(dx, dy);
    }
}

void MainWindow::on_actionDocument_Annotations_triggered()
{

}

void MainWindow::on_actionApply_Document_Settings_triggered()
{

}

void MainWindow::on_actionPaste_Special_triggered()
{
    const QMimeData *mimeData = QApplication::clipboard()->mimeData();
    if (mimeData->hasText()) {
        QGraphicsTextItem *textItem = new QGraphicsTextItem;
        textItem->setPlainText(mimeData->text());
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction); // make item editable and selectable
        QGraphicsScene *scene = ui->graphicsView->scene();
        scene->addItem(textItem);
    }
}

void MainWindow::on_actionClear_triggered()
{
    //ui->textEdit->setText("");
    if (ui->graphicsView->hasFocus())
    {
        ui->graphicsView->scene()->clear();
    }
    else if (ui->lineEdit->hasFocus())
    {
        ui->lineEdit->clear();
    }
    else if (ui->chemical_edit->hasFocus())
    {
        ui->chemical_edit->clear();
    }
    // Reset the pen tool state
    penToolEnabled = true;

}

void MainWindow::on_actionSelect_All_triggered()
{
    if(ui->lineEdit->hasFocus())
    {
        ui->lineEdit->selectAll();
    }
    else if (ui->chemical_edit->hasFocus())
    {
        ui->chemical_edit->selectAll();
    }
    else if(ui->graphicsView->hasFocus())
    {
        QGraphicsScene* scene = ui->graphicsView->scene();
        QList<QGraphicsItem*> items = scene->items();
        foreach (QGraphicsItem* item, items) {
            item->setSelected(true);
        }
        ui->graphicsView->viewport()->update();
    }
}

void MainWindow::on_actionRepeat_General_Show_triggered()
{

}

void MainWindow::on_actionToolbar_triggered()
{
    ui->toolBar->setHidden(!ui->toolBar->isHidden());
}

void MainWindow::on_actionInsert_Files_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select Files"), QDir::homePath(), tr("All Files (*)"));

    if (!fileNames.isEmpty()) {
        // Add the selected files to the QGraphicsTextItem in the Scene
        QString text;
        for (const QString& fileName : fileNames) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                text += in.readAll();
                file.close();
            }
        }
        QGraphicsTextItem* textItem = scene->addText(text);
        textItem->setPos(0, 0); // Set the position of the text item in the scene
    }
}

void MainWindow::on_actionInsert_Object_triggered()
{
    // Open a dialog to allow the user to select the type of object to insert
    QStringList items;
    items << tr("Text") << tr("Image") << tr("Link");
    QString selectedItem = QInputDialog::getItem(this, tr("Insert Object"), tr("Select the type of object to insert:"), items);

    if (selectedItem == tr("Text")) {
        // Open a file dialog to allow the user to select a text file
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Text File"), "", tr("Text Files (*.txt)"));

        // Check if a file was selected
        if (!fileName.isEmpty()) {
            // Open the file for reading
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                // Read the contents of the file
                QString text = QString::fromUtf8(file.readAll());

                // Create a QGraphicsTextItem with the file contents
                QGraphicsTextItem* textItem = new QGraphicsTextItem(text);

                // Add the text item to the scene at position (0,0)
                ui->graphicsView->scene()->addItem(textItem);
                textItem->setPos(0, 0);

                // Center the view on the new text item
                ui->graphicsView->centerOn(textItem);
            }
        }
    } else if (selectedItem == tr("Image")) {
        // Open a file dialog to allow the user to select an image file
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("Image Files (*.png *.jpg *.bmp)"));

        // Check if a file was selected
        if (!fileName.isEmpty()) {
            // Create a QPixmap with the selected image
            QPixmap pixmap(fileName);

            // Create a QGraphicsPixmapItem with the pixmap
            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);

            // Set flags for the pixmap item to be selectable and movable
            pixmapItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

            // Add the pixmap item to the scene at position (0,0)
            ui->graphicsView->scene()->addItem(pixmapItem);
            pixmapItem->setPos(0, 0);

            // Center the view on the new pixmap item
            ui->graphicsView->centerOn(pixmapItem);
        }
    }

    else if (selectedItem == tr("Link")) {
        // Open a dialog to allow the user to enter a URL
        QString url = QInputDialog::getText(this, tr("Insert Link"), tr("Enter the URL:"));

        // Create a QGraphicsTextItem with the link and make it clickable and movable
        QGraphicsTextItem* textItem = new QGraphicsTextItem(url);
        textItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setCursor(Qt::PointingHandCursor);

        // Add the text item to the scene at position (0,0)
        ui->graphicsView->scene()->addItem(textItem);
        textItem->setPos(0, 0);

        // Center the view on the new text item
        ui->graphicsView->centerOn(textItem);
    }
    /*
    else if (selectedItem == tr("Link")) {
        // Open a dialog to allow the user to enter a URL
        QString url = QInputDialog::getText(this, tr("Insert Link"), tr("Enter the URL:"));

        // Create a QGraphicsTextItem with the link and make it clickable and movable
        QGraphicsTextItem* textItem = new QGraphicsTextItem(url);
        textItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setCursor(Qt::PointingHandCursor);

        // Connect the linkActivated() signal of the text item to the on_linkItemClicked() slot
        connect(textItem, SIGNAL(linkActivated(QGraphicsTextItem*)), this, SLOT(on_linkItemClicked(QGraphicsTextItem*)));

        // Add the text item to the scene at position (0,0)
        ui->graphicsView->scene()->addItem(textItem);
        textItem->setPos(0, 0);

        // Center the view on the new text item
        ui->graphicsView->centerOn(textItem);
    }*/
}
/*
void MainWindow::openUrl(const QString& url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_linkItemClicked(QGraphicsTextItem* item) {
    QDesktopServices::openUrl(QUrl(item->toPlainText()));
}
*/
void MainWindow::on_actionObjects_triggered()
{

}

void MainWindow::on_actionCursor_triggered()
{
    statusBar()->showMessage("Current tool is cursor");
    //view->setCursor(Qt::ArrowCursor);
    //setActiveTool(Scene::Cursor);
    //statusBar()->showMessage("Current tool is Cursor");
    scene->setTool(Scene::Cursor);;
}

void MainWindow::on_actionPen_triggered()
{    if (scene->items().isEmpty()) {
        statusBar()->showMessage("The screen is empty. Please clear the screen to enable the Pen tool.");
        return;
    }

    statusBar()->showMessage("Current tool is Pen");
    scene->setTool(Scene::Pen);
}

void MainWindow::on_actionEraser_triggered()
{
    if (scene->items().isEmpty()) {
        statusBar()->showMessage("The screen is empty. Please clear the screen to enable the Eraser tool.");
        return;
    }

    statusBar()->showMessage("Current tool is Eraser");
    scene->setTool(Scene::Eraser);
}

void MainWindow::on_actionShow_triggered()
{

}

void MainWindow::on_actionDatabase_triggered()
{

}

void MainWindow::on_actionSize_triggered()
{

}

void MainWindow::on_actionPeriodic_Table_triggered()
{
    Periodic_TDialog periodic_Table;
    periodic_Table.setModal(true);
    auto ret=periodic_Table.exec();
    if(ret==1)
    {
        QGraphicsTextItem *boundText = new QGraphicsTextItem();
        //QString hydro = "H";
        QFont f;
        f.setPointSize(30);
        boundText->setPlainText(periodic_Table.getEle());
        boundText->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
        boundText->setFont(f);
        scene->addItem(boundText);
    }
}

void MainWindow::on_actionProperties_triggered()
{

}

void MainWindow::on_actionCheck_Structure_triggered()
{

}

void MainWindow::on_actionLabel_triggered()
{

}

void MainWindow::on_actionStructure_triggered()
{

}

void MainWindow::on_actionMap_triggered()
{

}

void MainWindow::on_actionFlush_Left_triggered()
{
    //ui->textEdit->setAlignment(Qt::AlignLeft);
    ui->graphicsView->setAlignment(Qt::AlignLeft);
    ui->lineEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_actionCentre_triggered()
{
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->lineEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_actionFlush_Right_triggered()
{
    ui->graphicsView->setAlignment(Qt::AlignRight);
    ui->lineEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_actionJustified_triggered()
{
    ui->graphicsView->setAlignment(Qt::AlignJustify);
    ui->lineEdit->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_actionAutomatic_Justification_triggered()
{
    //    QTextEdit *textEdit = new QTextEdit();
    //    textEdit->setAlignment(Qt::AlignJustify);
    QGraphicsView *graphicsView = new QGraphicsView();
    graphicsView->setAlignment(Qt::AlignJustify);

    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_actionPlain_triggered()
{
    //QString plainText = ui->textEdit->toPlainText();
    // Create a new text item
    QGraphicsTextItem *textItem = new QGraphicsTextItem();

    // Set its plain text
    textItem->setPlainText("Hello, world!");

    // Add the item to the scene
    ui->graphicsView->scene()->addItem(textItem);
}

void MainWindow::on_actionBold_triggered()
{

    QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(ui->graphicsView->scene()->focusItem());

    // If there is no text item, return
    if (!textItem) {
        return;
    }

    // Get the current font
    QFont font = textItem->font();

    // Toggle bold
    font.setBold(!font.bold());

    // Create a QTextCharFormat and set the font
    QTextCharFormat charFormat;
    charFormat.setFont(font);

    // Get the text cursor and merge the char format
    QTextCursor cursor = textItem->textCursor();
    cursor.mergeCharFormat(charFormat);

    // Set the new text cursor
    textItem->setTextCursor(cursor);

}

void MainWindow::on_actionItalic_triggered()
{
    QFont font = ui->lineEdit->font();

    // Toggle the italic state
    if (font.italic()) {
        font.setItalic(false);
    } else {
        font.setItalic(true);
    }

    // Set the new font on the QLineEdit object
    ui->lineEdit->setFont(font);

}

void MainWindow::on_actionUnderline_triggered()
{
    // Get a reference to the currently selected QLineEdit widget
    QLineEdit* selectedLineEdit = qobject_cast<QLineEdit*>(focusWidget());

    if (selectedLineEdit)
    {
        // Get the current font and underline status of the selected QLineEdit
        QFont font = selectedLineEdit->font();
        bool isUnderlined = font.underline();

        // Toggle the underline format on or off depending on the current status
        font.setUnderline(!isUnderlined);
        selectedLineEdit->setFont(font);
    }

    /*
    QGraphicsTextItem *textItem = qgraphicsitem_cast<QGraphicsTextItem*>(ui->graphicsView->scene()->focusItem());

    if (!textItem) {
        return;
    }

    QFont font = textItem->font();

    if (font.underline()) {
        font.setUnderline(false);
    } else {
        font.setUnderline(true);
    }

    textItem->setFont(font);
    */
}

void MainWindow::on_actionFormula_triggered()
{
    formula_dialog formula;
    formula.setModal(true);
    auto ret = formula.exec();
    if (ret == QDialog::Accepted)
    {
        QString newFormula = formula.getFrml();
        if (!newFormula.isEmpty())
        {
            QGraphicsTextItem* boundText = new QGraphicsTextItem(newFormula);
            QFont f;
            f.setPointSize(30);
            boundText->setFont(f);
            boundText->setFlag(QGraphicsItem::ItemIsMovable);
            boundText->setFlag(QGraphicsItem::ItemIsSelectable);
            ui->graphicsView->scene()->addItem(boundText);
        }
    }
}

void MainWindow::on_actionSubscript_selected_character_triggered()
{

}

void MainWindow::on_actionAdds_a_degree_sign_triggered()
{
    //ui->textEdit->insertPlainText(QString::fromUtf8("°C"));
    if (ui->lineEdit->hasFocus())
    {
        ui->lineEdit->insert("°C");
    }
    else if (ui->chemical_edit->hasFocus())
    {
        ui->chemical_edit->insert("°C");
    }
}

void MainWindow::on_actionRepeat_triggered()
{

}

void MainWindow::on_actionSearch_the_Content_triggered()
{
    qDebug() << "Button Clicked Search";
//    SearchDialog searchDialog(this);
//    searchDialog.exec();
}

void MainWindow::on_pushButton_10_clicked()
{
    TextEdit * textEdit = new TextEdit();
    textEdit->show();
    //scene->centerOn(QPointF(0,0));
}

void MainWindow::on_centerButton_clicked()
{
//    QRectF sceneRect = ui->graphicsView->sceneRect();
//    QRectF viewRect = ui->graphicsView->viewport()->rect();
//    ui->graphicsView->setSceneRect(sceneRect);
//    ui->graphicsView->centerOn(sceneRect.center());
    ui->graphicsView->centerOn(QPoint());
}

void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid()) {
        QMessageBox::information(this, "Selected Color", "You selected: " + color.name());
        ui->graphicsView->setStyleSheet("background-color: " + color.name() + ";");
    }
}

void MainWindow::on_actionPen_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this);

    if(color.isValid()){
        scene->setPenColor(color);
        QString colorQss = QString("background-color: %1").arg(color.name());

        //        ui->graphicsView->setStyleSheet(colorQss);
    }
    /*
    QColor color = QColorDialog::getColor(Qt::black,this);

    if(color.isValid()){
        scene->setPenColor(color);
        QString colorQss = QString("background-color: %1").arg(color.name());

        ui->lineEdit->setStyleSheet(colorQss);
    }
    */

}

void MainWindow::on_actionPentagon_triggered()
{
    scene->setTool(Scene::Pentagon);
    if (scene->tool() == Scene::Pentagon) {
        ui->statusbar->showMessage("Click to create Pentagon");

    } else {
        ui->statusbar->clearMessage();
    }
}

void MainWindow::on_actionBenzene_triggered()
{
    /*Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                           "print('Today is',ctime(time()))\n");
    Py_Finalize();
    PyRun *pyRun = new PyRun();
    qDebug("\nRun from file...");
    //Abosulte path is needed
    QString fName = "F:/Internship/Quick Search/new_qgraphics_view_demo/new_qgraphics_view_demo/Trail.py";
    pyRun->runFile(fName);
    qDebug()<<"Bezene Clicked";
    QProcess p;
    p.start("Python", QStringList("Trail.py"));

    p.waitForFinished();
    QByteArray p_stdout = p.readAllStandardOutput();
    QByteArray p_stderr = p.readAllStandardError();

    qDebug()<< p_stdout;*/

    scene->setTool(Scene::Benzene);
    if (scene->tool() == Scene::Benzene) {
        ui->statusbar->showMessage("Click to create Benzene");

    } else {
        ui->statusbar->clearMessage();
    }
}

void MainWindow::on_actionNumbers_triggered()
{
    Number Numeric_Table;
    Numeric_Table.setModal(true);
    auto ret=Numeric_Table.exec();
    if(ret==1)
    {
        QGraphicsTextItem *boundText = new QGraphicsTextItem();
        //QString hydro = "H";
        QFont f;
        f.setPointSize(15);
        boundText->setPlainText(Numeric_Table.getNum());
        boundText->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
        boundText->setFont(f);
        scene->addItem(boundText);
    }
}


void MainWindow::on_actionSymbols_triggered()
{
    Symbol_Dialog symbols;
    symbols.setModal(true);
    auto ret = symbols.exec();
    if(ret==1)
    {
        QGraphicsTextItem *boundText = new QGraphicsTextItem();
        //QString hydro = "H";
        QFont f;
        f.setPointSize(30);
        boundText->setPlainText(symbols.getSymbol());
        boundText->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
        boundText->setFont(f);
        scene->addItem(boundText);
    }
}

void MainWindow::on_penstylecomboBox_activated(int index)
{
    switch (index) {

    case 0 :{
        //Solid
        scene->setPenStyle(Qt::SolidLine);

    }
        break;

    case 1 :{
        //Dashed
        scene->setPenStyle(Qt::DashLine);

    }
        break;

    case 2 :{
        //Dotted
        scene->setPenStyle(Qt::DotLine);

    }
        break;

    case 3 :{
        //Dot Dashed
        scene->setPenStyle(Qt::DashDotLine);

    }
        break;

    }
}


void MainWindow::on_brushstylecomboBox_activated(int index)
{
    switch (index) {
    case 0 :
    {
        scene->setBrushStyle(Qt::SolidPattern);
    }
        break;
    case 1 :
    {
        scene->setBrushStyle(Qt::Dense5Pattern);
    }
        break;
    case 2 :
    {
        scene->setBrushStyle(Qt::HorPattern);
    }
        break;
    case 3 :
    {
        scene->setBrushStyle(Qt::VerPattern);
    }
        break;
    case 4 :
    {
        scene->setBrushStyle(Qt::CrossPattern);
    }
        break;

    }

}

void MainWindow::on_penwidthcomboBox_activated(int index)
{
    switch (index) {

    case 0 :{
        //Pen width 1
        scene->setPenWidth(1);

    }
        break;

    case 1 :{
        //Pen Width 2
        scene->setPenWidth(2);
        break;
    }

    case 2 :{
        //Pen Widht 3
        scene->setPenWidth(3);

    }
        break;

    case 3 :{
        //Pen Width 4
        scene->setPenWidth(4);

    }
        break;
    case 4 : {
        //Pen Width 5
        scene->setPenWidth(5);
    }
        break;

    case 5: {
        // Pen Width 6
        scene->setPenWidth(6);
    }
        break;
    }
}

//-------------------------------------------------
void MainWindow::on_Quick_Search_Btn_clicked()
{
    QString input = ui->lineEdit->text();

    // Open a dialog to select the root directory
    QString rootPath = QFileDialog::getExistingDirectory(this, "Select Root Directory", QDir::rootPath());
    if (rootPath.isEmpty())
    {
        // User canceled the dialog
        return;
    }

    // Search for files matching the input in the entire system
    QStringList filePaths = searchFiles(rootPath, input);

    if (filePaths.isEmpty())
    {
        QMessageBox::information(this, "Message", "No matching files found.");
    }
    else
    {
        for (const QString& filePath : filePaths)
        {
            // Load and display the file
            displayFile(filePath);
        }
    }
}

QStringList MainWindow::searchFiles(const QString& drivePath, const QString& input)
{
    QStringList filePaths;

    // Recursive search for all files in the selected drive
    QDirIterator it(drivePath, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString filePath = it.next();
        QString fileName = QFileInfo(filePath).fileName();

        // Search for files matching the input
        if (fileName.contains(input))
        {
            filePaths.append(filePath);
        }
    }

    return filePaths;
}

void MainWindow::displayFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.exists())
    {
        QMessageBox::information(this, "Error", "File does not exist: " + filePath);
        return;
    }

    QFileInfo fileInfo(filePath);
    QString fileExtension = fileInfo.suffix();

    if (fileExtension.isEmpty())
    {
        // Unable to determine file type
        QMessageBox::information(this, "Error", "Unable to determine file type.");
        return;
    }

    if (fileExtension.toLower() == "txt")
    {
        // Display text file content
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString fileContent = file.readAll();
            file.close();

            // Create a QGraphicsTextItem to display the text
            QGraphicsTextItem* textItem = new QGraphicsTextItem(fileContent);
            // Set the position and properties of the text item as needed
            scene->addItem(textItem);
        }
        else
        {
            QMessageBox::information(this, "Error", "Failed to open file: " + file.errorString());
        }
    }
    else if (fileExtension.toLower() == "png" || fileExtension.toLower() == "jpg" || fileExtension.toLower() == "jpeg")
    {
        // Display image file
        QPixmap pixmap(filePath);

        // Create a QGraphicsPixmapItem to display the image
        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap.scaled(110, 110));

        // Create a QGraphicsRectItem as a bounding box for the image
        QGraphicsRectItem* boundRectItem = new QGraphicsRectItem();
        boundRectItem->setRect(pixmapItem->boundingRect().adjusted(-10, -10, 10, 10));
        boundRectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        pixmapItem->setParentItem(boundRectItem);

        // Add the bounding box with the image to the scene
        scene->addItem(boundRectItem);
    }
    else
    {
        // Unsupported file type
        QMessageBox::information(this, "Error", "Unsupported file type: " + fileExtension);
    }
}

//-------------------------------------------------

void MainWindow::on_actionLine_triggered()
{
    if (scene) {
        // Create a LineItem object
        LineItem* line = new LineItem();

        // Set the line's start and end points
        line->setLine(0, 50, 100, 50);

        // Set the pen color and thickness of the line
        QPen pen(Qt::black);
        pen.setWidth(2);
        line->setPen(pen);

        // Enable the movable and selectable flags of the line
        line->setFlag(QGraphicsItem::ItemIsMovable);
        line->setFlag(QGraphicsItem::ItemIsSelectable);

        // Add the line to the scene
        scene->addItem(line);

        // Optionally, you can ensure that the new line is always added on top of other items
        line->setZValue(1);

        // Ensure that previously added lines remain selectable
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            if (item->type() == LineItem::Type) {
                item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            }
        }
    }
}

//*******************************//
void MainWindow::on_actionRectangle_triggered()
{
    scene->setTool(Scene::Rectangle);
    if (scene->tool() == Scene::Rectangle) {
        ui->statusbar->showMessage("Click to create rectangle");

    } else {
        ui->statusbar->clearMessage();
    }
}

void MainWindow::on_actionaddSide_triggered()
{
    scene->setTool(Scene::AddSide);

}

void MainWindow::on_actionHexagon_triggered()
{
    scene->setTool(Scene::Hexagon);
    if (scene->tool() == Scene::Hexagon) {
        ui->statusbar->showMessage("Click to create Hexagon");

    } else {
        ui->statusbar->clearMessage();
    }
}

//************************************//

void MainWindow::on_actionOctagon_triggered()
{

}

void MainWindow::on_chemical_search_Button_clicked()
{
    Py_Initialize();

    // Import the required modules
    PyObject *pChemModule = PyImport_ImportModule("rdkit.Chem");
    PyObject *pDrawModule = PyImport_ImportModule("rdkit.Chem.Draw");

    // Define the SMILES string
    QString temp = ui->chemical_edit->text();
    const char *res=temp.toUtf8().data();
    qDebug() << temp<<";"<<res;
    //const char *smiles_string = "CC(C)C1=CC=C(C=C1)NC(=O)C2=CC=C(C=C2)Cl";

    // Create the molecule from the SMILES string
    PyObject *pMol = PyObject_CallMethod(pChemModule, "MolFromSmiles", "s", res);

    // Draw the molecule and save it to a file
    QString fname = temp+".png";
    qDebug()<<fname;
    PyObject_CallMethod(pDrawModule, "MolToFile", "Os", pMol,  qPrintable(fname));
    //QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem();
    QPixmap pixmap( fname);
    EditablePixmapItem* pixmapItem = new EditablePixmapItem(pixmap);

    // Enable pen editing on the pixmapItem
    pixmapItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pixmapItem->setAcceptHoverEvents(true);
    //pixmapItem->setPixmap(pixmap);
    //pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //pixmapItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    scene->addItem(pixmapItem);
    // Draw the molecule and display it in a QGraphicsView


    //QPixmap pixmap = QPixmap::fromImage(QImage((unsigned char *)PyBytes_AsString(PyTuple_GetItem(pImage, 0)), PyObject_GetBuffer(PyTuple_GetItem(pImage, 0), NULL, PyBUF_SIMPLE)->len, QImage::Format_RGB888));
    //QPixmap pixmap = QPixmap::fromImage(QImage((unsigned char *)PyBytes_AsString(PyTuple_GetItem(pImage, 0)), PyObject_GetBuffer(PyTuple_GetItem(pImage, 0), NULL)->len, QImage::Format_RGB888));
    //QGraphicsScene scene;
    //QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    //QGraphicsView view(&scene);
    //scene->addItem(item);
    //view.show();

    // Cleanup
    Py_DECREF(pChemModule);
    Py_DECREF(pDrawModule);
    Py_DECREF(pMol);
    //Py_DECREF(pImage);
    Py_Finalize();


}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void MainWindow::on_actionShow_Rulers_triggered()
{

}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void MainWindow::on_actionShow_Main_Toolbar_triggered()
{
    ui->toolBar->setHidden(!ui->toolBar->isHidden());
}


void MainWindow::on_zoomInButton_clicked()
{
    double scaleFactor = 1.1;
    ui->graphicsView->scale(scaleFactor, scaleFactor);
}


void MainWindow::on_zoomOutButton_clicked()
{
    double scaleFactor = 1.1;
    ui->graphicsView->scale(1/scaleFactor, 1/scaleFactor);
}


void MainWindow::on_ResetButton_clicked()
{
    ui->graphicsView->resetTransform();
}


void MainWindow::on_actionShow_Style_Toolbar_triggered()
{
    ui->toolBar_3->setHidden(!ui->toolBar_3->isHidden());
}

void MainWindow::on_actionType_triggered()
{
    TypeRectItem* rectItem = new TypeRectItem();
    rectItem->setRect(0, 0, 100, 100);
    QGraphicsScene* scene = ui->graphicsView->scene();
    scene->addItem(rectItem);
}

