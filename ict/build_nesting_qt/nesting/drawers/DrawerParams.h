#ifndef DRAWERPARAMS_H
#define DRAWERPARAMS_H
#include "ItemsContainer.h"
class QPainter;

// параметры алгоритма рисования (раскроя листа металла)
struct DrawerParams
{
    DrawerParams(double scale, double notScaledSheetWidth, double notScaledSheetHeight,
                 QPainter& painter, ItemsContainer& itemsContaner, int& execItemCount);

    double m_scale;
    double m_notScaledSheetWidth;
    double m_notScaledSheetHeight;
    QPainter& m_painter;
    ItemsContainer& m_itemsContaner;
    int& m_nExecItemCount;
};

#endif // DRAWERPARAMS_H
