
#include <QFont>
#include "typerectitem.h"
#include <QGraphicsSceneHoverEvent>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

TypeRectItem::TypeRectItem(QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);
    m_textItem = new QGraphicsTextItem(this);
    m_textItem->setDefaultTextColor(Qt::black);
    QFont font("Arial", 12);
    m_textItem->setFont(font);
    adjustTextItemPosition();
    m_isResizing = false;
    m_resizeHandleSize = 10;
}

void TypeRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    QRectF rect = this->rect();
    QPointF hoverPos = event->pos();
    if (hoverPos.x() >= rect.x() + rect.width() - m_resizeHandleSize &&
        hoverPos.y() >= rect.y() + rect.height() - m_resizeHandleSize)
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else
    {
        unsetCursor();
        m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
    }
}

void TypeRectItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        m_textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        m_textItem->setFocus();
        event->accept();
    }
    else if (event->button() == Qt::LeftButton)
    {
        QRectF rect = this->rect();
        QPointF pressPos = event->pos();
        if (pressPos.x() >= rect.x() + rect.width() - m_resizeHandleSize &&
            pressPos.y() >= rect.y() + rect.height() - m_resizeHandleSize)
        {
            m_isResizing = true;
            m_resizeStartPos = pressPos;
            event->accept();
            return;
        }

        QGraphicsRectItem::mousePressEvent(event);
    }
}

void TypeRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton && flags() & ItemIsMovable)
    {
        if (m_isResizing)
        {
            QPointF currentPos = event->pos();
            qreal dx = currentPos.x() - m_resizeStartPos.x();
            qreal dy = currentPos.y() - m_resizeStartPos.y();

            QRectF rect = this->rect();
            qreal newWidth = rect.width() + dx;
            qreal newHeight = rect.height() + dy;

            // Limit the minimum size of the rectangle
            qreal minWidth = 20;
            qreal minHeight = 20;
            if (newWidth < minWidth)
                newWidth = minWidth;
            if (newHeight < minHeight)
                newHeight = minHeight;

            prepareGeometryChange();
            setRect(rect.x(), rect.y(), newWidth, newHeight);
            adjustTextItemPosition();
            m_resizeStartPos = currentPos;
        }
        else
        {
            QGraphicsRectItem::mouseMoveEvent(event);
            adjustTextItemPosition();
        }
    }
}

void TypeRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isResizing)
    {
        m_isResizing = false;
    }
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void TypeRectItem::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Backspace)
    {
        QString text = m_textItem->toPlainText();
        if (!text.isEmpty())
        {
            text.chop(1);
            m_textItem->setPlainText(text);

            // Adjust font size based on the remaining lines
            int numLines = text.count('\n') + 1;
            qreal height = rect().height() - 10;
            qreal textHeight = m_textItem->boundingRect().height() / numLines;
            QFont font = m_textItem->font();
            int fontSize = font.pointSize();
            font.setPointSizeF(fontSize * (height / textHeight));
            m_textItem->setFont(font);
        }
    }
    else if (event->text().length() == 1)
    {
        QString text = m_textItem->toPlainText();
        text.append(event->text());
        m_textItem->setPlainText(text);

        // Adjust font size based on the updated lines
        int numLines = text.count('\n') + 1;
        qreal height = rect().height() - 10;
        qreal textHeight = m_textItem->boundingRect().height() / numLines;
        QFont font = m_textItem->font();
        int fontSize = font.pointSize();
        font.setPointSizeF(fontSize * (height / textHeight));
        m_textItem->setFont(font);
    }
}

void TypeRectItem::adjustTextItemPosition()
{
    QRectF rect = this->rect();
    qreal x = rect.x() + 5;
    qreal y = rect.y() + 5;
    qreal width = rect.width() - 10;
    qreal height = rect.height() - 10;

    m_textItem->setPos(x, y);
    m_textItem->setTextWidth(width);  // Set the maximum width of the text item
    m_textItem->setPlainText(m_textItem->toPlainText());  // Force reflow of the text

    // Adjust the height of the text item if needed
    qreal textHeight = m_textItem->boundingRect().height();
    if (textHeight > height)
    {
        QFont font = m_textItem->font();
        int fontSize = font.pointSize();
        font.setPointSizeF(fontSize * (height / textHeight));
        m_textItem->setFont(font);
        m_textItem->setPlainText(m_textItem->toPlainText());  // Force reflow of the text
    }
}

QPainterPath TypeRectItem::shape() const
{
    QPainterPath path;
    path.addRect(rect());
    return path;
}

void TypeRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsRectItem::paint(painter, option, widget);

    // Set the font size based on the rectangle's height
    QRectF clipRect = painter->clipBoundingRect();
    qreal height = rect().height() - 10;
    qreal textHeight = m_textItem->boundingRect().height();
    if (textHeight > height)
    {
        QFont font = m_textItem->font();
        int fontSize = font.pointSize();
        font.setPointSizeF(fontSize * (height / textHeight));
        m_textItem->setFont(font);
    }

    m_textItem->setTextWidth(rect().width() - 10);  // Set the maximum width of the text item

    // Paint the text item
    painter->translate(clipRect.topLeft());
    m_textItem->paint(painter, option, widget);
}
