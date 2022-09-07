#include "drawers/Drawer.h"
#include <limits>

Drawer::Drawer() : eps(std::numeric_limits<double>::epsilon()){}

Drawer::~Drawer(){}

void Drawer::draw(DrawerParams &drawerParams)
{
    //
}
