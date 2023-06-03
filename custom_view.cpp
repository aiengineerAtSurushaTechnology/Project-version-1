#include "custom_view.h"

Custom_View::Custom_View(QWidget *parent) : QGraphicsView(parent)
{

}

void Custom_View::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(AnchorUnderMouse);
    double scaleFactor = 1.5;
    QPoint delta = event->angleDelta();

    if (!delta.isNull())
    {
        int x = delta.x();
        int y = delta.y();
        if (x > 0 || y > 0)
        {
            scale(scaleFactor, scaleFactor);
        }
        else if (x < 0 || y < 0)
        {
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }

    event->accept();
}

void Custom_View::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setTransform(QTransform());
    }

    event->accept();
}
