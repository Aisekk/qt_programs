// ======================================================================
//  SystemTray.h
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

#pragma once

#include <QLabel>

class QSystemTrayIcon;
class QMenu;

// ======================================================================
class SystemTray : public QLabel {
Q_OBJECT
private:
    QSystemTrayIcon* m_ptrayIcon;
    QMenu*           m_ptrayIconMenu;
    bool             m_bIconSwitcher;

protected:
    virtual void closeEvent(QCloseEvent*);

public:
    SystemTray(QWidget* pwgt = 0);

public slots:
    void slotShowHide   ();
    void slotShowMessage();
    void slotChangeIcon ();
};

