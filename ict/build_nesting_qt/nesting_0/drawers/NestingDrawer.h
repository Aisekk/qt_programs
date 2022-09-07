#ifndef NESTINGDRAWER_H
#define NESTINGDRAWER_H
#include "drawers/Drawer.h"

class QPainter;

class NestingDrawer : public Drawer
{
public:
    NestingDrawer();
    virtual void draw(DrawerParams &params) override;
protected:
    void drawItem(QPainter &painter, double x, double y, double width, double height);
};

#endif // NESTINGDRAWER_H
