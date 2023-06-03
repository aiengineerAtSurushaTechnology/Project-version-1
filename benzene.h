#ifndef BENZENE_H
#define BENZENE_H

#include <QGraphicsItem>
#include "painterapptypes.h"
class Benzene : public QGraphicsItem
{
public:
    Benzene(QPointF position);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    enum ButtonType {
           ADD_BUTTON,
           REMOVE_BUTTON
       };
//    Q_ENUM(ButtonType);
    enum{Type = BenzeneType};
    int type() const;
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
     QList<QGraphicsLineItem*> m_doubleBonds; // declare double bonds here
};

#endif // BENZENE_H
