#include "verticalruler.h"
#include <QPainter>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QFontMetrics>

VerticalRuler::VerticalRuler(QWidget *parent)
    : QWidget(parent), offset(0)
{
}

void VerticalRuler::setOffset(int offset)
{
    this->offset = offset;
    update();
}

void VerticalRuler::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 8));

    int tickHeight = 5;
    int tickInterval = 10;
    int numberInterval = 50;

    int start = event->rect().top();
    int end = event->rect().bottom();
    int left = event->rect().left();
    int right = event->rect().right();

    for (int y = start; y <= end; y += tickInterval)
    {
        int adjustedY = y + offset;  // Apply the offset

        if (adjustedY % numberInterval == 0)
        {
            QString number = QString::number(adjustedY);
            int numberWidth = painter.fontMetrics().horizontalAdvance(number);
            int numberHeight = painter.fontMetrics().height();

            // Calculate the position to draw the number
            int numberX = left - tickHeight - numberWidth;
            int numberY = adjustedY + numberHeight / 2;  // Use adjustedY

            // Rotate the painter to draw the number vertically
            painter.save();
            painter.translate(numberX, numberY);
            painter.rotate(-90);
            painter.drawText(0, 0, number);
            painter.restore();
        }

        painter.drawLine(left, y, left + tickHeight, y);
        painter.drawLine(right - tickHeight, y, right, y);
    }
}

void VerticalRuler::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}
