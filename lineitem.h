#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

class LineItem : public QGraphicsLineItem
{
public:
    LineItem(QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void joinLines(LineItem* otherLine);

private:
    bool movableStartPoint;
    bool movableEndPoint;
    QPointF initialPos;
    QLineF initialLine;
    qreal pointToLineDistance(const QPointF& point, const QLineF& line);
};

#endif // LINEITEM_H
