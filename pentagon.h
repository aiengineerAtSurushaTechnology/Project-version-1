#ifndef PENTAGON_H
#define PENTAGON_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include "painterapptypes.h"
class Pentagon : public QGraphicsItem
{
public:
    enum{Type = PentagonType};
    int type() const;
    Pentagon(const QPointF& position, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QPointF m_position;
    QList<QGraphicsLineItem*> m_lines;
    QPointF m_hoverPos;
    int m_hoverSide;
    bool m_adding;
};

#endif // PENTAGON_H
