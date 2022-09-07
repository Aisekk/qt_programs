#ifndef POPUPWIDGET_H
#define POPUPWIDGET_H

#include <QToolBar>

class PopUpWidget : public QToolBar
{
public:
    PopUpWidget(const QString& title, QWidget* pwgt = nullptr);
protected:
    virtual void enterEvent(QEvent*) override;
    virtual void leaveEvent(QEvent*) override;
};

#endif // POPUPWIDGET_H
