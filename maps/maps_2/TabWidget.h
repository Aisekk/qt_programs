#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QSplitter>

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget();
protected:
    //void tabRemoved(int tabIndex) override;
};

#endif // TABWIDGET_H
