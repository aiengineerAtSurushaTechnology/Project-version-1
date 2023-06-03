#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsEllipseItem>
#include <QUndoStack>
#include "textedit.h"
#include "strokeitem.h"
#include "benzene.h"
#include "hexagon.h"
#include <QString>


class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    QString isStructure="Null";
    enum Tool {
        Select,
        Pen,
        Eraser,
        Benzene,
        Cursor,
        //
        Rectangle,
        AddSide,
        Pentagon,
        Hexagon,

        //
    };
    Q_ENUM(Tool)
    explicit Scene(QObject *parent = nullptr);

    void setTool(Tool newTool);
    //
    Tool getTool() const;
    //
    Tool tool() const;

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

    int getPenWidth() const;
    void setPenWidth(int value);

    Qt::PenStyle getPenStyle() const;
    void setPenStyle(const Qt::PenStyle &value);

    QColor getFillColor() const;
    void setFillColor(const QColor &value);

    Qt::BrushStyle getBrushStyle() const;
    void setBrushStyle(const Qt::BrushStyle &value);


    void copy();
    void cut();
    void paste();


    void undo();
    void redo();

signals:


    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event) override;

private:
    //Benzene *benz;

    QPointF BenzenePos;
    QPointF startpoint;
    QPointF stoppoint;
    QGraphicsItemGroup *lineGroup;
    Tool m_tool=Tool::Select;
    bool drawing;
    //
    QList<QGraphicsItem *> m_selectedItems;
    QList<QPointF> selectedItemInitialPositions;
    QUndoStack * undoStack;

    QColor penColor;
    int penWidth;
    Qt::PenStyle penStyle;
    QColor fillColor;
    Qt::BrushStyle brushStyle;

    void readItemsFromDataStream(QDataStream &in , bool copyPaste = true);
    void writeItemsToDataStream(QDataStream &out, const QList<QGraphicsItem *> &items);
    //const QList<QGraphicsItem*> &items);

    //
    QGraphicsEllipseItem *lastEraseCircle;
    void drawLineTo(const QPointF &endPoint);
    void drawEraseAt(const QPointF &endPoint);
    void eraseStrokesUnder(QGraphicsEllipseItem *item);

    QGraphicsLineItem * horGuideLine;
    QGraphicsLineItem * verGuideLine;


    QGraphicsPixmapItem* currentImage;


};

#endif // SCENE_H
