#ifndef EDITABLEPIXMAPITEM_H
#define EDITABLEPIXMAPITEM_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
class EditablePixmapItem : public QGraphicsPixmapItem
{
public:
    EditablePixmapItem(const QPixmap& pixmap);


    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // EDITABLEPIXMAPITEM_H
