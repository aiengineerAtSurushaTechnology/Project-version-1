
#ifndef TYPERECTITEM_H
#define TYPERECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class TypeRectItem : public QGraphicsRectItem
{
public:
    TypeRectItem(QGraphicsItem* parent = nullptr);

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void adjustTextItemPosition();
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

private:
    QGraphicsTextItem* m_textItem;
    bool m_isResizing;
    qreal m_resizeHandleSize;
    QPointF m_resizeStartPos;
};

#endif // TYPERECTITEM_H
