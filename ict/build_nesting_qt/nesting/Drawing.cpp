#include "Drawing.h"
#include "drawers/Drawer.h"

Drawing::Drawing(Drawer *drawer) : m_pDrawer(drawer) {}

void Drawing::draw(DrawerParams &drawerParams)
{
    m_pDrawer->draw(drawerParams);
}
