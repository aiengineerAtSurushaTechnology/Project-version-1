//#include "MyGraphicsView.h"
#include "mygraphicsview.h"
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QGraphicsPolygonItem>
#include <QBrush>
#include <cmath>
#include <limits>
#include <QHoverEvent>
#include <QGraphicsView>

MyGraphicsView::MyGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::RubberBandDrag);
}

void MyGraphicsView::createNewPolygon(const QPointF& position)
{
    m_polygon.clear();
    m_polygon.append(position);
    m_currentPolygon = new QGraphicsPolygonItem(QPolygonF(m_polygon));
    m_currentPolygon->setPen(QPen(Qt::black, 2));
    m_currentPolygon->setBrush(QBrush(Qt::gray));
    scene()->addItem(m_currentPolygon);
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
        QPointF pos = mapToScene(event->pos());
        if (m_drawing) {
            m_polygon.append(pos);
            m_currentPolygon->setPolygon(m_polygon);
        } else {
            createNewPolygon(pos);
            m_drawing = true;
        }
    }
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
    if (m_drawing) {
        QPointF pos = mapToScene(event->pos());
        m_polygon.back() = pos;
        m_currentPolygon->setPolygon(m_polygon);
    }
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton && m_drawing) {
        m_drawing = false;
    }
}

void MyGraphicsView::hoverMoveEvent(QHoverEvent* event)
{
    QGraphicsView::hoverMoveEvent(event);
    if (m_currentPolygon && m_currentPolygon->isUnderMouse()) {
        QPointF pos = mapToScene(event->pos());
        int index = findClosestVertex(pos);
        if (index >= 0 && index < m_polygon.size()) {
            switch (index) {
            case 0:
            case 2:
                m_currentPolygon->setCursor(Qt::SizeFDiagCursor);
                break;
            case 1:
            case 3:
                m_currentPolygon->setCursor(Qt::SizeBDiagCursor);
                break;
            default:
                m_currentPolygon->setCursor(Qt::ArrowCursor);
                break;
            }
        } else {
            m_currentPolygon->setCursor(Qt::ArrowCursor);
        }
    }
}

void MyGraphicsView::hoverEnterEvent(QHoverEvent* event)
{
    QGraphicsView::hoverEnterEvent(event);
    setCursor(Qt::CrossCursor);
    QGraphicsView::hoverEnterEvent(event);
    if (m_currentPolygon && m_currentPolygon->isUnderMouse()) {
        m_currentPolygon->setBrush(QBrush(Qt::cyan));
    }
}

void MyGraphicsView::hoverLeaveEvent(QHoverEvent* event)
{
    QGraphicsView::hoverLeaveEvent(event);
    if (m_currentPolygon) {
        m_currentPolygon->setBrush(QBrush(Qt::gray));
        m_currentPolygon->setCursor(Qt::ArrowCursor);
    }
}

void MyGraphicsView::hoverPressEvent(QHoverEvent* event)
{
    QGraphicsView::hoverPressEvent(event);
    if (m_currentPolygon && m_currentPolygon->isUnderMouse()) {
        QPointF pos = mapToScene(event->pos());
        int index = findClosestVertex(pos);
        if (index >= 0 && index < m_polygon.size()) {
            m_polygon.insert(index + 1, pos);
            m_currentPolygon->setPolygon(m_polygon);
        }
    }
}

int MyGraphicsView::findClosestVertex(const QPointF& point) const
{
    int index = -1;
    qreal minDistance = std::numeric_limits<qreal>::max();
    for (int i = 0; i < m_polygon.size(); ++i) {
        qreal distance = QLineF(point, m_polygon[i]).length();
        if (distance < minDistance) {
            index = i;
            minDistance = distance;
        }
    }
    return index;
}
