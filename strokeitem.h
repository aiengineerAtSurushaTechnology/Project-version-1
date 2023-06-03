#ifndef STROKEITEM_H
#define STROKEITEM_H

#include <QDataStream>
#include <QGraphicsItemGroup>
#include "painterapptypes.h"


class StrokeItem : public QGraphicsItemGroup
{
public:
    explicit StrokeItem();
    enum{Type = StrokeType};

    int type() const;
};
//Read
QDataStream &operator<<(QDataStream &out,const StrokeItem & mStroke);
//Write
QDataStream &operator>>(QDataStream &in, StrokeItem & mStroke);
#endif // STROKEITEM_H
