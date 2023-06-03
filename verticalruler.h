#ifndef VERTICALRULER_H
#define VERTICALRULER_H

#include <QWidget>

class VerticalRuler : public QWidget
{
    Q_OBJECT

public:
    explicit VerticalRuler(QWidget *parent = nullptr);
    void setOffset(int offset);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int offset;

};

#endif // VERTICALRULER_H
