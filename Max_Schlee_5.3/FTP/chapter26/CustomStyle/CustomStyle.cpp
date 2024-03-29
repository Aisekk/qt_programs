// ======================================================================
//  CustomStyle.cpp
// ======================================================================
//                   This file is a part of the book 
//             "Qt 5.3 Professional programming with C++"
// ======================================================================
//  Copyright (c) 2014 by Max Schlee
//
//  Email : Max.Schlee@neonway.com
//  Blog  : http://www.maxschlee.com
//
//  Social Networks
//  ---------------
//  FaceBook : http://www.facebook.com/mschlee
//  Twitter  : http://twitter.com/Max_Schlee
//  2Look.me : http://2look.me/NW100003
//  Xing     : http://www.xing.com/profile/Max_Schlee
//  vk.com   : https://vk.com/max.schlee
// ======================================================================

#include <QtGui>
#include "CustomStyle.h"

// ----------------------------------------------------------------------
void CustomStyle::polish(QWidget* pwgt)
{
     if (qobject_cast<QPushButton*>(pwgt)) {
         pwgt->setAttribute(Qt::WA_Hover, true);
     }
}

// ----------------------------------------------------------------------
void CustomStyle::unpolish(QWidget* pwgt)
{
     if (qobject_cast<QPushButton*>(pwgt)) {
         pwgt->setAttribute(Qt::WA_Hover, false);
     }
}

// ----------------------------------------------------------------------
void CustomStyle::drawPrimitive(      PrimitiveElement elem, 
                                const QStyleOption*    popt,
                                      QPainter*        ppainter, 
                                const QWidget*         pwgt
                               ) const
{
    switch (elem) {
    case PE_PanelButtonCommand:
    {
        const QStyleOptionButton* pOptionButton = 
            qstyleoption_cast<const QStyleOptionButton*>(popt);
        if (pOptionButton) {
            bool bDown = (pOptionButton->state & State_Sunken) 
                       || (pOptionButton->state & State_On);

            QPixmap pix = bDown ? QPixmap(":/images/btnprs.bmp") 
                                : QPixmap(":/images/btn.bmp");
            
            ppainter->drawPixmap(pOptionButton->rect, pix);

            bool bHover = (pOptionButton->state & State_Enabled)
                          && (pOptionButton->state & State_MouseOver);
            if (bHover) {
                ppainter->fillRect(pOptionButton->rect, 
                                   QColor(25, 97, 45, 83)
                                  );
            }
        }
        break;
    }

    default:
        QCommonStyle::drawPrimitive(elem, popt, ppainter, pwgt);
        break;
    }
    return;
}
