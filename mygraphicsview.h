#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPolygonF>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    MyGraphicsView(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void hoverMoveEvent(QHoverEvent* event);
    void hoverEnterEvent(QHoverEvent* event);
    void hoverLeaveEvent(QHoverEvent* event);
    void hoverPressEvent(QHoverEvent* event);

private:
    void createNewPolygon(const QPointF& position);
    int findClosestVertex(const QPointF& point) const;

    QPolygonF m_polygon;
    QGraphicsPolygonItem* m_currentPolygon = nullptr;
    bool m_drawing = false;
};

#endif // MYGRAPHICSVIEW_H
