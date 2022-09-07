#include "DrawerParams.h"

DrawerParams::DrawerParams(double scale, double notScaledSheetWidth, double notScaledSheetHeight,
                           QPainter &painter, ItemsContainer &itemsContaner, int &execItemCount)
    : m_scale(scale),
      m_notScaledSheetWidth(notScaledSheetWidth),
      m_notScaledSheetHeight(notScaledSheetHeight),
      m_painter(painter),
      m_itemsContaner(itemsContaner),
      m_nExecItemCount(execItemCount)
{

}
