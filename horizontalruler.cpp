#include "horizontalruler.h"
#include <QPainter>
#include <QPaintEvent>

HorizontalRuler::HorizontalRuler(QWidget *parent)
    : QWidget(parent), offset(0)
{
}

void HorizontalRuler::setOffset(int offset)
{
    this->offset = offset;
    update();
}

void HorizontalRuler::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 8));

    int tickHeight = 5;
    int tickInterval = 10;
    int numberInterval = 50;

    int start = event->rect().left();
    int end = event->rect().right();
    int top = event->rect().top();
    int bottom = event->rect().bottom();

    for (int x = start; x <= end; x += tickInterval)
    {
        if (x % numberInterval == 0)
        {
            QString number = QString::number(x);
            int numberWidth = painter.fontMetrics().horizontalAdvance(number); // Updated line

            // Adjust the position of the numbers to avoid overlapping
            int numberX = x - numberWidth / 2;
            int numberY = top + tickHeight + painter.fontMetrics().height();
            painter.drawText(numberX, numberY, number);

            painter.drawLine(x, top, x, top + tickHeight);
        }
        else
        {
            painter.drawLine(x, top, x, top + tickHeight / 2);
        }
        painter.drawLine(x, bottom - tickHeight, x, bottom);
    }
}

