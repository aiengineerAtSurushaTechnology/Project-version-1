#include "scene.h"
#include<QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPen>
#include <QGraphicsItem>
#include <QPointF>
#include <QGraphicsItemGroup>
#include "textedit.h"
#include "commands.h"
#include <QByteArray>
#include <QClipboard>
#include <QDataStream>
#include <QKeyEvent>
#include <QMimeData>
#include <QApplication>

const QString MimeType = "application/com.blikoontech.painterapp";
Scene::Scene(QObject *parent)
    : QGraphicsScene(parent),lastEraseCircle(nullptr),
      m_tool(Cursor),
      penColor(Qt::black),
      penWidth(2),
      penStyle(Qt::SolidLine),
      fillColor(Qt::gray),
      brushStyle(Qt::SolidPattern)
{
    lineGroup=nullptr;
    horGuideLine =  addLine(50,25,750,25,QPen(Qt::blue));
    verGuideLine = addLine(400,-400,400,400,QPen(Qt::blue));
    //setSceneRect(-800,-600,1600,1200);

    undoStack = new QUndoStack(this);
}


void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() <<"Mouse Pressed" << event->button();
    if(event->button() == Qt::LeftButton)
    {
        if(m_tool == Tool::Pen||m_tool == Tool::Eraser)
        {
            startpoint = event->scenePos();
            drawing = true;

        }
        //
        else if(m_tool == Tool::Cursor){
            m_selectedItems.clear();
            selectedItemInitialPositions.clear();
            QGraphicsScene::mousePressEvent(event);


        }else{
            QGraphicsScene::mousePressEvent(event);
        }
        //
    }
    else
    {
        QGraphicsScene::mousePressEvent(event);
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() <<"Mouse Move" << event->button();
    if((event->buttons() & Qt::LeftButton) && drawing)
    {

        if(m_tool == Tool::Pen)
        {
            //qDebug()<<event->scenePos();
            drawLineTo(event->scenePos());
        }
        else if(m_tool == Tool::Eraser)
        {
            drawEraseAt(event->scenePos());
        }
        /*
        else{
            drawShapeTo(event->scenePos());
        }
        */

    }
    else if((event->buttons() & Qt::LeftButton)&&(m_tool == Tool::Cursor))
    {

        if(m_selectedItems.isEmpty() && selectedItemInitialPositions.isEmpty()
                &&!selectedItems().isEmpty()){
            m_selectedItems = selectedItems();

            foreach (QGraphicsItem * item, m_selectedItems){
                selectedItemInitialPositions.append(item->scenePos());
            }
        }
        QGraphicsScene::mouseMoveEvent(event);
    }
    else
    {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() <<"Mouse RELEASED Pressed" <<event->button();
    if((event->button() == Qt::LeftButton) && drawing)
    {
        QPen mPen;
        mPen.setColor(penColor);
        mPen.setWidth(penWidth);
        mPen.setStyle(penStyle);

        QBrush mBrush;
        mBrush.setColor(fillColor);
        mBrush.setStyle(brushStyle);

        //qDebug() <<"Mouse RELESA inside";
        if(m_tool == Tool::Pen)
        {
            lineGroup=nullptr;
            drawing=false;
        }
        else if(m_tool == Tool::Eraser)
        {
            removeItem(lastEraseCircle);
            delete lastEraseCircle;
            lastEraseCircle = nullptr;
            drawing = false;
        }
    }
    //
    else if((event->button() == Qt::LeftButton) && (m_tool == Tool::Cursor))
    {

        for(int i = 0 ; i < m_selectedItems.count() ; i++){

            QGraphicsItem * currentItem = m_selectedItems[i];

            if(!(selectedItemInitialPositions[i] == currentItem->scenePos())){

                MoveCommand * moveCommand = new MoveCommand(currentItem, this,
                                                            selectedItemInitialPositions[i],
                                                            currentItem->scenePos());

                undoStack->push(moveCommand);
            }
        }
        QGraphicsScene::mouseReleaseEvent(event);

    }
    //
    else
    {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete){
        if(selectedItems().count()  > 0){
            QGraphicsItem * itemToRemove = selectedItems()[0];
            RemoveCommand * removeCommand = new RemoveCommand(itemToRemove, this);
            undoStack->push(removeCommand);
            //removeItem(itemToRemove);
            //delete itemToRemove;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::readItemsFromDataStream(QDataStream &in, bool copyPaste)
{
    clearSelection();


    qint32 itemType;

    while (!in.atEnd())
    {
        in >> itemType;
        //qDebug() <<"ItemType: "<<itemType;
        switch (itemType)
        {


        case StrokeType :
        {
            qDebug() <<"Inside Stroke Iype";
            StrokeItem *strokeItem = new StrokeItem();
            in >> *strokeItem;
            strokeItem->setFlag(QGraphicsItem::ItemIsMovable);
            strokeItem->setFlag(QGraphicsItem::ItemIsSelectable);
            addItem(strokeItem);
            if(copyPaste){
                strokeItem->moveBy(10,10);
                strokeItem->setSelected(true);
            }
            break;
        }
        case BenzeneType:
        {
            qDebug() <<"Inside Benzene Iype";
            isStructure = "Benzene";
            break;
            //Benzene* benzene = new Benzene(BenzenePos);
            //benzene->setFlag(QGraphicsItem::ItemIsMovable);
            //addItem(benzene);
        }
        case PentagonType:
        {
            qDebug() <<"Inside Pentagon Iype";
            isStructure = "Pentagon";
            break;
            //Benzene* benzene = new Benzene(BenzenePos);
            //benzene->setFlag(QGraphicsItem::ItemIsMovable);
            //addItem(benzene);
        }
        case HexagonType:
        {
            qDebug() <<"Inside Hexagon Iype";
            isStructure = "Hexagon";
            break;
            //Benzene* benzene = new Benzene(BenzenePos);
            //benzene->setFlag(QGraphicsItem::ItemIsMovable);
            //addItem(benzene);
        }
        }
    }
}

void Scene::writeItemsToDataStream(QDataStream &out, const QList<QGraphicsItem *> &items)
{
    foreach (QGraphicsItem * item, items) {

        qint32 type = static_cast<qint32>(item->type());
        qDebug() <<"Item Type: "<<item->type();
        out << type;

        switch (type) {

        case StrokeType :{
            qDebug() <<"StrokeItem Type: ";
            out << *static_cast<StrokeItem *>(item);
            break;
        }
        case BenzeneType: {
            qDebug() <<"BenzeneItem Type: ";
            BenzenePos = item->scenePos();
            break;
        }
        }
    }
}

void Scene::drawLineTo(const QPointF &endPoint)
{
    if(!lineGroup)
    {
        //qDebug()<<"Inside If";
        lineGroup = new StrokeItem();
        lineGroup->setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable );
        //
        AddCommand * addCommand = new AddCommand(lineGroup, this);
        undoStack->push(addCommand);
        //addItem(lineGroup);
        stoppoint = startpoint;
        qDebug() <<"If end";
    }
    //qDebug()<<lineGroup<<" value after if";
    QGraphicsLineItem *linedraw = new QGraphicsLineItem(QLineF(stoppoint,endPoint));
    QPen mPen;
    mPen.setWidth(penWidth);
    mPen.setColor(penColor);
    linedraw->setPen(mPen);
    lineGroup->addToGroup(linedraw);

    stoppoint = endPoint;
    /*
    if (lineGroup)
    {
        // Remove the existing line group
        removeItem(lineGroup);
        delete lineGroup;
        lineGroup = nullptr;
    }

    lineGroup = new StrokeItem();
    lineGroup->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    QPen mPen;
    mPen.setWidth(penWidth);
    mPen.setColor(penColor);

    QGraphicsLineItem *lineDraw = new QGraphicsLineItem(QLineF(stoppoint, endPoint));
    lineDraw->setPen(mPen);

    lineGroup->addToGroup(lineDraw);
    addItem(lineGroup);

    stoppoint = endPoint;
    */
}

void Scene::drawEraseAt(const QPointF &endPoint)
{
    if(!lastEraseCircle)
    {
        lastEraseCircle = addEllipse(0,0,50,50);
    }
    lastEraseCircle->setPos(endPoint - QPointF(lastEraseCircle->boundingRect().width()/2,
                                               lastEraseCircle->boundingRect().height()/2));
    eraseStrokesUnder(lastEraseCircle);
}

void Scene::eraseStrokesUnder(QGraphicsEllipseItem *item)
{
    QList<QGraphicsItem *> itemsToRemove = item->collidingItems();
    QList<QGraphicsItemGroup *> groupItems;

    foreach (QGraphicsItem *myItem, itemsToRemove) {
        QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup *> (myItem);
        if(group){
            groupItems.append(group);
        }

        QGraphicsLineItem *line = dynamic_cast<QGraphicsLineItem *> (myItem);
        if(line)
        {
            RemoveCommand * removeCommand = new RemoveCommand(line, this);
            undoStack->push(removeCommand);
            //removeItem(line);
            //delete line;
        }
    }

    foreach (QGraphicsItemGroup *group, groupItems) {
        if(group->childItems().count()==0)
        {
            RemoveCommand * removeCommand = new RemoveCommand(group, this);
            undoStack->push(removeCommand);
            //removeItem(group);
            //delete group;
        }
    }
}

Scene::Tool Scene::tool() const
{
    return m_tool;
}

void Scene::setTool(Tool newTool)
{
    m_tool = newTool;
}

void Scene::undo()
{
    undoStack->undo();
}

void Scene::redo()
{
    undoStack->redo();
}

QColor Scene::getFillColor() const
{
    return fillColor;
}

void Scene::setFillColor(const QColor &value)
{
    fillColor = value;
}

Qt::PenStyle Scene::getPenStyle() const
{
    return penStyle;
}

void Scene::setPenStyle(const Qt::PenStyle &value)
{
    penStyle = value;
}

Qt::BrushStyle Scene::getBrushStyle() const
{
    return brushStyle;
}

void Scene::setBrushStyle(const Qt::BrushStyle &value)
{
    brushStyle = value;
}

int Scene::getPenWidth() const
{
    return penWidth;
}

void Scene::setPenWidth(int value)
{
    penWidth = value;
}

QColor Scene::getPenColor() const
{
    return penColor;
}

void Scene::setPenColor(const QColor &value)
{
    penColor = value;
}


void Scene::copy()
{
    QByteArray mByteArray;
    QDataStream out(&mByteArray, QIODevice::WriteOnly);
    writeItemsToDataStream(out,selectedItems());
    QMimeData * mimeData = new QMimeData;
    mimeData->setData(MimeType,mByteArray);
    QClipboard * clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);
}

void Scene::cut()
{
    qDebug()<<"Inside Cut";
    QByteArray mByteArray;
    QDataStream out(&mByteArray, QIODevice::WriteOnly);

    QList<QGraphicsItem* > itemList = selectedItems();

    writeItemsToDataStream(out,itemList);
    QMimeData * mimeData = new QMimeData;
    mimeData->setData(MimeType,mByteArray);
    QClipboard * clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);

    //Remove items
    foreach (QGraphicsItem * item, itemList) {
        qDebug() <<"Removing Item";
        removeItem(item);
    }
    qDeleteAll(itemList);

}

void Scene::paste()
{
    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();

    if(!mimeData)
        return;

    if(mimeData->hasFormat(MimeType)){
        QByteArray mByteArray = mimeData->data(MimeType);
        QDataStream in(&mByteArray, QIODevice::ReadOnly);

        readItemsFromDataStream(in);

    }
    qDebug()<<"Paste";
}

