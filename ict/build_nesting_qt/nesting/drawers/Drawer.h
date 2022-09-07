#ifndef DRAWER_H
#define DRAWER_H
class DrawerParams;

// base class of pattern strategy
class Drawer
{
public:
    Drawer();
    virtual ~Drawer();
    virtual void draw(DrawerParams &drawerParams);
protected:
    double eps;
};

#endif // DRAWER_H
