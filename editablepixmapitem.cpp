#include "editablepixmapitem.h"
#include <QDebug>
EditablePixmapItem::EditablePixmapItem(const QPixmap& pixmap) : QGraphicsPixmapItem(pixmap)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
}

void EditablePixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        // Perform pen editing operations here
        // Example: Change the pixel color at the clicked position
        qDebug() <<" Mosuse pressed inside event ";
        QPointF pos = event->pos();
        QPixmap pixmap = this->pixmap();
        QPainter painter(&pixmap);
        painter.setPen(Qt::red);
        painter.drawPoint(pos.x(), pos.y());
        setPixmap(pixmap);
    }
    else
        QGraphicsPixmapItem::mousePressEvent(event);
}

void EditablePixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton)
    {
        // Perform pen editing operations here
        // Example: Draw a line with the pen color between previous and current position
        QPointF prevPos = event->lastPos();
        QPointF currPos = event->pos();
        QPixmap pixmap = this->pixmap();
        QPainter painter(&pixmap);
        painter.setPen(Qt::red);
        painter.drawLine(prevPos, currPos);
        setPixmap(pixmap);
    }
    else
        QGraphicsPixmapItem::mouseMoveEvent(event);
}

void EditablePixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}
