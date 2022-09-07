#ifndef GLOBALSETTINGSWIN_H
#define GLOBALSETTINGSWIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSettings>
#include <QValidator>
#include <QMessageBox>
#include <math.h>
//--------------------------------------------------------------------------------------
#include <memory>
//--------------------------------------------------------------------------------------
#include "Validator.h"
//--------------------------------------------------------------------------------------
using namespace std;

class GlobalSettingsWin : public QWidget
{
    Q_OBJECT
public:
    GlobalSettingsWin(QWidget *pwgt = nullptr);
    ~GlobalSettingsWin();

    void writeSettings(bool &error);
    void setSettings(shared_ptr<QSettings> spSettings);
public slots:
    void setDnLimit(const QString &Dn);
    void setUpLimit(const QString &Up);
signals:
    void recalc();
private:
    //------------------------------------------------------------------
    //объекты, включенные в объектную иерархию:
    //------------------------------------------------------------------
    QLabel *m_plbl_Dn_Limit;
    QLabel *m_plbl_Up_Limit;

    QLineEdit *m_ptxt_Dn_Limit;
    QLineEdit *m_ptxt_Up_Limit;

    QPushButton *m_pcmdApply;
    QPushButton *m_pcmdMachineLimits;

    QHBoxLayout *m_phbxLayout_Dn;
    QHBoxLayout *m_phbxLayout_Up;
    QHBoxLayout *m_phbxLayout_Buttons;
    QVBoxLayout *m_pvbxLayout;

    //валидаторы
    QDoubleValidator* m_pdblValidator_Dn_Limit;
    QDoubleValidator* m_pdblValidator_Up_Limit;
    //------------------------------------------------------------------
    //объекты, не включенные в объектную иерархию:
    //------------------------------------------------------------------
    //настройки
    shared_ptr<QSettings> m_spSettings;
    double m_TypeLimit;
    double m_NormalLimit;
    QString m_strNormalLimit_Dn;
    QString m_strNormallLimit_Up;
    //------------------------------------------------------------------
private slots:
    void slotCmdApplyEnabled();
    void slotApply();
    void slotMachineLimits();
    void slotHideWin();
    void slot_Apply_and_HideWin();
    //------------------------------------------------------------------
};

#endif // GLOBALSETTINGSWIN_H
