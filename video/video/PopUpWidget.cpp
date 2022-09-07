#include "PopUpWidget.h"

PopUpWidget::PopUpWidget(const QString &title, QWidget *pwgt) : QToolBar(title, pwgt)
{
    setMaximumHeight(5);
}
void PopUpWidget::enterEvent(QEvent*)
{
    setMaximumHeight(100);
}
void PopUpWidget::leaveEvent(QEvent*)
{
    setMaximumHeight(5);
}
