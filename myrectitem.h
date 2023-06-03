#ifndef MYRECTITEM_H
#define MYRECTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneHoverEvent>

class MyRectItem : public QGraphicsRectItem
{
//    Q_OBJECT

public:
//   explicit MyRectItem(QGraphicsItem* parent = nullptr)
//        : QGraphicsRectItem(parent)
//    {}

    MyRectItem(QGraphicsItem* parent = nullptr);
        virtual ~MyRectItem();
signals:
    void hoverEnter();
    void hoverLeave();
protected:
   virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
 //   {
 //       emit hoverEnter();
 //       QGraphicsRectItem::hoverEnterEvent(event);
 //   }

  virtual  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
   // {
   //     emit hoverLeave();
   //     QGraphicsRectItem::hoverLeaveEvent(event);
   // }


};


#endif // MYRECTITEM_H
