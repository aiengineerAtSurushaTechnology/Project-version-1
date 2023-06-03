#ifndef HORIZONTALRULER_H
#define HORIZONTALRULER_H

#include <QWidget>

class HorizontalRuler : public QWidget
{
    Q_OBJECT

public:
    explicit HorizontalRuler(QWidget *parent = nullptr);
    void setOffset(int offset);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int offset;
};

#endif // HORIZONTALRULER_H
