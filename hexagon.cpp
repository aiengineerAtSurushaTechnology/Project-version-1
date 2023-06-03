#include "hexagon.h"
#include "mainwindow.h"
#include <QtCore/QObject>
#include <QGraphicsSceneHoverEvent>
#include"hoverellipseitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QUndoCommand>

int Hexagon::type() const
{
    return Type;
}

Hexagon::Hexagon(QPointF position)
    : m_position(position)
{
    // Create the six lines of the benzene ring
    for (int i = 0; i < 6; ++i) {
        qreal x1 = m_position.x() + 50 * cos(i * M_PI / 3);
        qreal y1 = m_position.y() + 50 * sin(i * M_PI / 3);
        qreal x2 = m_position.x() + 50 * cos((i + 1) * M_PI / 3);
        qreal y2 = m_position.y() + 50 * sin((i + 1) * M_PI / 3);
        QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2, this);
        line->setFlag(QGraphicsItem::ItemIsMovable, true);

        m_lines.append(line);
    }
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF Hexagon::boundingRect() const
{
    qreal penWidth = 1;
    qreal extra = (penWidth + 10) / 2.0;

    return QRectF(m_position.x() - 60 - extra, m_position.y() - 60 - extra,
                  120 + penWidth + 10 + extra, 120 + penWidth + 10 + extra);
//    return QRectF(m_position.x() - 50, m_position.y() - 50, 100, 100);
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::white);

    // Draw the benzene ring
//    painter->drawEllipse(m_position, 50, 50);

    // Draw the double bonds
//    for (int i = 0; i < 6; i += 2) {
//        QPointF p1 = m_lines.at(i)->line().p1();
//        QPointF p2 = m_lines.at(i + 1)->line().p2();
//        painter->drawLine(p1, p2);
//    }
}

void Hexagon::addRemoveButtons(QGraphicsScene* scene)
{
    for (auto line : m_lines) {
        QPointF p1 = line->line().p1();
        QPointF p2 = line->line().p2();
        QPointF center = (p1 + p2) / 2;

        // Add "+" button
        QGraphicsEllipseItem* plusButton = new QGraphicsEllipseItem(-m_buttonRadius, -m_buttonRadius,
                                                                     2 * m_buttonRadius, 2 * m_buttonRadius, line);
//        plusButton->setData(ButtonType, ADD_BUTTON);
        plusButton->setPos(center);
        plusButton->setBrush(Qt::green);
        m_buttonItems.append(plusButton);
        scene->addItem(plusButton);
//        connect(plusButton, &HoverEllipseItem::hoverEntered, this, &Benzene::hoverEnterEvent);
//        connect(plusButton, &HoverEllipseItem::hoverLeft, this, &Benzene::hoverLeaveEvent);
        // Add "-" button
        QGraphicsEllipseItem* minusButton = new QGraphicsEllipseItem(-m_buttonRadius, -m_buttonRadius,
                                                                      2 * m_buttonRadius, 2 * m_buttonRadius, line);
//       minusButton->setData(ButtonType, REMOVE_BUTTON);
        minusButton->setPos(center);
        minusButton->setBrush(Qt::red);
       m_buttonItems.append(minusButton);
       scene->addItem(minusButton);

        // Make buttons invisible
        plusButton->setVisible(false);
        minusButton->setVisible(false);
    }
}
void Hexagon::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    // Change color of the ellipse when the mouse enters
//    QGraphicsEllipseItem::hoverEnterEvent(event);
    QPen pen(Qt::red);
//    setPen(pen);
}

void Hexagon::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    // Change color of the ellipse back to black when the mouse leaves
//    QGraphicsEllipseItem::hoverLeaveEvent(event);
    QPen pen(Qt::black);
//      setPen(pen);
}
