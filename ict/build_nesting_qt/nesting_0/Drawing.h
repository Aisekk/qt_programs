#ifndef DRAWING_H
#define DRAWING_H

class Drawer;
class DrawerParams;

// context class of pattern strategy
class Drawing
{
public:
    Drawing(Drawer* drawer);
    void draw(DrawerParams& drawerParams);
private:
    Drawer *m_pDrawer;
};

#endif // DRAWING_H
