#ifndef HOVERELLIPSEITEM_H
#define HOVERELLIPSEITEM_H

#include <QGraphicsEllipseItem>

class HoverEllipseItem : public QGraphicsEllipseItem {
//    Q_OBJECT
public:
    explicit HoverEllipseItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem* parent = nullptr);

signals:
    void hoverEntered();
    void hoverLeft();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
};

#endif // HOVERELLIPSEITEM_H
