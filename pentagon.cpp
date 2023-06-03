#include "pentagon.h"
#include <QtMath>
#include <QPainter>
#include <QGraphicsScene>

int Pentagon::type() const
{
    return Type;
}

Pentagon::Pentagon(const QPointF& position, QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , m_position(position)
    , m_hoverPos()
    , m_hoverSide(-1)
    , m_adding(false)
{
    for (int i = 0; i < 5; ++i) {
        qreal x1 = m_position.x() + 50 * cos(i * 2 * M_PI / 5);
        qreal y1 = m_position.y() + 50 * sin(i * 2 * M_PI / 5);
        qreal x2 = m_position.x() + 50 * cos((i + 1) * 2 * M_PI / 5);
        qreal y2 = m_position.y() + 50 * sin((i + 1) * 2 * M_PI / 5);
        QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2, this);
        line->setFlag(QGraphicsItem::ItemIsMovable, true);
        m_lines.append(line);
    }
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF Pentagon::boundingRect() const
{
    qreal penWidth = 1;
    qreal extra = (penWidth + 10) / 2.0;

    return QRectF(m_position.x() - 60 - extra, m_position.y() - 60 - extra,
                  120 + penWidth + 10 + extra, 120 + penWidth + 10 + extra);
}

void Pentagon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(Qt::white);

//    QPolygonF polygon;
//    for (int i = 0; i < 5; ++i) {
//        polygon << QPointF(m_lines[i]->line().x1(), m_lines[i]->line().y1());
//    }
//    polygon << QPointF(m_lines[0]->line().x1(), m_lines[0]->line().y1());

//    painter->drawPolygon(polygon);
}

void Pentagon::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
//    QPointF pos = mapToScene(event->pos());
//    m_hoverPos = QPointF();
//    m_adding = false;
//    for (int i = 0; i < m_lines.size(); ++i) {
//        QLineF line = m_lines[i]->line();
//        if (QLineF(line.p1(), pos).length() + QLineF(pos, line.p2()).length() - qFabs(line.length()) < 0.1) {
//            m_hoverPos = pos;
//            m_hoverSide = i;
//            update();
//            return;
//        }
//    }
//    m_hoverSide = -1;
//    update();
}

void Pentagon::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
//    if (event->button() == Qt::LeftButton) {
//        if (m_hoverSide >= 0 && m_hoverSide < m_lines.size()) {
//            m_adding = true;
//        }
//    } else if (event->button() == Qt::RightButton) {
//        if (m_hoverSide >= 0 && m_hoverSide < m_lines.size() && m_lines.size() > 5) {
//            m_adding = false;
//        }
//    }
}

void Pentagon::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
//if (event->button() == Qt::LeftButton && m_adding) {
//QPointF pos = mapToScene(event->pos());
//qreal x1 = pos.x() + 50 * cos(m_hoverSide * 2 * M_PI / 5);
//qreal y1 = pos.y() + 50 * sin(m_hoverSide * 2 * M_PI / 5);
//qreal x2 = pos.x() + 50 * cos((m_hoverSide + 1) * 2 * M_PI / 5);
//qreal y2 = pos.y() + 50 * sin((m_hoverSide + 1) * 2 * M_PI / 5);
//QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2, this);
//line->setFlag(QGraphicsItem::ItemIsMovable, true);
//m_lines.insert(m_hoverSide + 1, line);
//update();
//} else if (event->button() == Qt::RightButton && !m_adding) {
//    QGraphicsLineItem* line = m_lines.takeAt(m_hoverSide);
//    delete line;
//    update();
//}
//m_adding = false;
}
