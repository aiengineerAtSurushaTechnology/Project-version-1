#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include "lineitem.h"

LineItem::LineItem(QGraphicsItem *parent)
    : QGraphicsLineItem(parent), movableStartPoint(false), movableEndPoint(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void LineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Check if the click is near the endpoints of the line
        QPointF clickPos = event->pos();
        qreal startX = line().x1();
        qreal startY = line().y1();
        qreal endX = line().x2();
        qreal endY = line().y2();

        if (qAbs(clickPos.x() - startX) < 10 && qAbs(clickPos.y() - startY) < 10)
        {
            // Clicked near the start point, allow movement of start point only
            movableStartPoint = true;
            movableEndPoint = false;
        }
        else if (qAbs(clickPos.x() - endX) < 10 && qAbs(clickPos.y() - endY) < 10)
        {
            // Clicked near the end point, allow movement of end point only
            movableStartPoint = false;
            movableEndPoint = true;
        }
        else
        {
            // Clicked elsewhere, enable movement of the whole line
            movableStartPoint = false;
            movableEndPoint = false;
        }

        initialPos = clickPos;
        initialLine = line();
    }

    QGraphicsLineItem::mousePressEvent(event);
}

void LineItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (movableStartPoint || movableEndPoint)
    {
        QPointF offset = event->pos() - initialPos;

        if (movableStartPoint)
        {
            // Update the start point's position
            setLine(initialLine.x1() + offset.x(), initialLine.y1() + offset.y(),
                    initialLine.x2(), initialLine.y2());
        }
        else if (movableEndPoint)
        {
            // Update the end point's position
            setLine(initialLine.x1(), initialLine.y1(),
                    initialLine.x2() + offset.x(), initialLine.y2() + offset.y());
        }

        // Check for collision with other LineItems
        QList<QGraphicsItem*> collisions = collidingItems();
        foreach (QGraphicsItem* item, collisions)
        {
            if (item->type() == Type && item != this)
            {
                LineItem* otherLine = static_cast<LineItem*>(item);
                if (otherLine->isSelected()) {
                    joinLines(otherLine);
                }
            }
        }
    }
    else
    {
        QGraphicsLineItem::mouseMoveEvent(event);
    }
}

void LineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    movableStartPoint = false;
    movableEndPoint = false;
    QGraphicsLineItem::mouseReleaseEvent(event);
}

void LineItem::joinLines(LineItem* other)
{
    QLineF thisLine = line();
    QLineF otherLine = other->line();

    QPointF intersectionPoint;
    if (thisLine.intersects(otherLine, &intersectionPoint) == QLineF::BoundedIntersection)
    {
        // Calculate the combined line by extending it to include both lines
        qreal minX = qMin(qMin(thisLine.x1(), thisLine.x2()), qMin(otherLine.x1(), otherLine.x2()));
        qreal minY = qMin(qMin(thisLine.y1(), thisLine.y2()), qMin(otherLine.y1(), otherLine.y2()));
        qreal maxX = qMax(qMax(thisLine.x1(), thisLine.x2()), qMax(otherLine.x1(), otherLine.x2()));
        qreal maxY = qMax(qMax(thisLine.y1(), thisLine.y2()), qMax(otherLine.y1(), otherLine.y2()));

        // Create a new line using the combined endpoints
        //QLineF newLine(minX, minY, maxX, maxY);

        // Update this LineItem's line to the combined line
        //setLine(newLine);
        setLine(minX, minY, maxX, maxY);

        // Remove the other LineItem from the scene
        scene()->removeItem(other);
        delete other;
    }
}

qreal LineItem::pointToLineDistance(const QPointF& point, const QLineF& line)
{
    qreal dx = line.dx();
    qreal dy = line.dy();

    if (dx == 0 && dy == 0)
    {
        // The line is actually a point
        return QPointF(point - line.p1()).manhattanLength();
    }

    qreal u = ((point.x() - line.p1().x()) * dx + (point.y() - line.p1().y()) * dy) / (dx * dx + dy * dy);

    QPointF closestPoint;
    if (u < 0)
    {
        closestPoint = line.p1();
    }
    return QPointF(point - closestPoint).manhattanLength();
}
