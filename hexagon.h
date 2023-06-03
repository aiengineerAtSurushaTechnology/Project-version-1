#ifndef HEXAGON_H
#define HEXAGON_H

#include <QGraphicsItem>
#include "painterapptypes.h"
class Hexagon : public QGraphicsItem
{
public:
    enum{Type = HexagonType};
    int type() const;
    Hexagon(QPointF position);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    enum ButtonType {
           ADD_BUTTON,
           REMOVE_BUTTON
       };
//    Q_ENUM(ButtonType);
    void addRemoveButtons(QGraphicsScene* scene);
public:
//    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    QPointF m_position;
    QList<QGraphicsLineItem*> m_lines;
    QList<QGraphicsEllipseItem*> m_buttonItems;
    qreal m_buttonRadius = 6;
};

#endif // HEXAGON_H
