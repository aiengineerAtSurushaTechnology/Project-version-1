#include "hoverellipseitem.h"

HoverEllipseItem::HoverEllipseItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent)
    : QGraphicsEllipseItem(x, y, width, height, parent)
{
}

void HoverEllipseItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsEllipseItem::hoverEnterEvent(event);
//    emit hoverEntered();
}

void HoverEllipseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsEllipseItem::hoverLeaveEvent(event);
//    emit hoverLeft();
}
