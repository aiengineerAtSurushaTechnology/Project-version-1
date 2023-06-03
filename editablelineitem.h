#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QPen>

class EditableLineItem : public QGraphicsLineItem
{
public:
    EditableLineItem(QPointF p1, QPointF p2, QGraphicsItem* parent = nullptr)
        : QGraphicsLineItem(QLineF(p1, p2), parent)
    {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setFlag(QGraphicsItem::ItemIsSelectable, true);
    }

    virtual QRectF boundingRect() const override
    {
        return shape().controlPointRect();
    }

    virtual QPainterPath shape() const override
    {
        QPainterPath path;
        path.moveTo(line().p1());
        path.cubicTo(QPointF(line().p1().x() + 20, line().p1().y()),
                     QPointF(line().p2().x() - 20, line().p2().y()),
                     line().p2());
        return path;
    }

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override
    {
        Q_UNUSED(option)
        Q_UNUSED(widget)
        QPen pen = QPen(Qt::black, 2);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawPath(shape());
    }

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value) override
    {
        if (change == QGraphicsItem::ItemSelectedHasChanged && value.toBool()) {
            // Redraw the line when it's selected
            update();
        }
        return QGraphicsItem::itemChange(change, value);
    }
};
