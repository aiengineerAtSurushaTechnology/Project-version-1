
#include "view.h"
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include "mainwindow.h"
#include <QDebug>
#include <QPainter>

View::View(QWidget *parent) : QGraphicsView(parent),drawingSelection(false),
    lastRect(nullptr),drawGridLines(true)
{

}
/*
void View::mousePressEvent(QMouseEvent *event)
{

    QGraphicsScene * currentScene = scene();
    MainWindow * mMainwindow = dynamic_cast<MainWindow *>(currentScene);
    //Scene * mScene = dynamic_cast<Scene * >(currentScene);

    if(mMainwindow && (mMainwindow->getTool() == MainWindow::Cursor)){
        QGraphicsItem * sceneItem = scene()->itemAt(mapToScene(event->pos()),transform());
        if(!sceneItem){
            selectTopLeft = event->pos();
            drawingSelection = true;
        }

    }
    QGraphicsView::mousePressEvent(event);
}*/
/*
void View::mousePressEvent(QMouseEvent *event)
{

    QGraphicsScene * currentScene = scene();
    MainWindow * mMainwindow = dynamic_cast<MainWindow *>(currentScene);
    //Scene * mScene = dynamic_cast<Scene * >(currentScene);

    if(mMainwindow && (mMainwindow->getTool() == MainWindow::Tool::Select)){
        QGraphicsItem * sceneItem = scene()->itemAt(mapToScene(event->pos()),transform());
        if(!sceneItem){
            selectTopLeft = event->pos();
            drawingSelection = true;
        }

    }
    QGraphicsView::mousePressEvent(event);
}


void View::mouseMoveEvent(QMouseEvent *event)
{

    QGraphicsScene * currentScene = scene();
    MainWindow * mMainwindow = dynamic_cast<MainWindow * >(currentScene);

    if(mMainwindow && (mMainwindow->getTool() == MainWindow::Tool::Select)){
        if(drawingSelection){

            //Selection region
            QRect selectRegion = QRect(selectTopLeft,event->pos());

            QPainterPath path;
            path.addRect(selectRegion);

            scene()->setSelectionArea(mapToScene(path));

            //Draw visual feedback for the user
            QGraphicsItem * itemToRemove = lastRect;



            lastRect = scene()->addRect(QRectF(mapToScene(selectTopLeft),
                                               mapToScene(event->pos())).normalized());
            lastRect->setBrush(QBrush(QColor(255, 0, 0, 50)));

            if(itemToRemove){
                scene()->removeItem(itemToRemove);
                delete  itemToRemove;
            }

        }

    }

    QGraphicsView::mouseMoveEvent(event);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsScene * currentScene = scene();
    MainWindow * mMainwindow = dynamic_cast<MainWindow * >(currentScene);

    if(mMainwindow && (mMainwindow->getTool() == MainWindow::Tool::Select)){
        if(drawingSelection){
            QGraphicsItem * itemToRemove = lastRect;
            if(itemToRemove){
                scene()->removeItem(itemToRemove);
                delete itemToRemove;
                lastRect = nullptr;
            }

        }
        drawingSelection = false;
    }

    QGraphicsView::mouseReleaseEvent(event);
}
*/



void View::drawForeground(QPainter *painter, const QRectF &rect)
{

    if(drawGridLines){
        painter->save();
        //-800,-600,1600,1200
        painter->setPen(QColor(100, 44, 18, 30));
        //Vertical lines
        for( int i = 0 ; i < 32 ; i++){
            painter->drawLine( -800 + (50 *i) , -600, -800 + (50 *i) ,600 );
        }
        //Horizantal lines
        for( int i =0 ; i < 24 ; i++){
            painter->drawLine(-800, -600 + (i * 50), 800, -600 + (i * 50));
        }
        painter->restore();
    }else{
        QGraphicsView::drawForeground(painter,rect);
    }

}

bool View::getDrawGridLines() const
{
    return drawGridLines;
}

void View::setDrawGridLines(bool value)
{
    if(drawGridLines != value){
        drawGridLines = value;
        scene()->update();
    }
}


