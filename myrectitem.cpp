#include "myrectitem.h"

#include <QGraphicsSceneHoverEvent>
MyRectItem::MyRectItem(QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{
}

MyRectItem::~MyRectItem()
{
}
void MyRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
//   emit hoverEnter();
    QGraphicsRectItem::hoverEnterEvent(event);
}

void MyRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
   // emit hoverLeave();
    QGraphicsRectItem::hoverLeaveEvent(event);
}
