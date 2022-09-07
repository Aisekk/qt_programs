#ifndef HELPWIN_H
#define HELPWIN_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

class HelpWin : public QWidget
{
public:
    HelpWin(QWidget *pwgt = nullptr);
private:
    QString itemString(const QString& item);

    int m_itemNumber;
    QLabel* m_pLabel;
    QTextEdit* m_pHelpText;
    QVBoxLayout* m_pvbxLayout;
};

#endif // HELPWIN_H
