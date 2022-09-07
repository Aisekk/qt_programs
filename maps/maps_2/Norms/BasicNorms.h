#ifndef BASICNORMS_H
#define BASICNORMS_H

#include <QString>
#include <QRegExp>
#include "Types.h"

class BasicNorms
{
public:
    BasicNorms();
    virtual ~BasicNorms();
    //метод установки пределов для теста
    void setTestInterval(const QString& testName, ValuePrefix valuePrefix,
                         double& criteriumDn, double& criteriumUp);

protected:
    void setPrefix(ValuePrefix valuePrefix, double &criteriumDn, double &criteriumUp);
    //функции-члены setTestInterval
    void Contacting(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void SIL09(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void SIL05(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void SIL035(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void SIL06(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void KLV_M1Si(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Z_M1Si(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Meanders(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void KLV_MeMe(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Z_MeMe(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void VDPs(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Capacity(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Diods(const QString& testName, double& criteriumDn, double& criteriumUp);

    virtual void Tr_Vt(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Tr_VtRevers(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Tr_Be(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Tr_Vbr(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Tr_Gleak(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Tr_DSleak(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Tr_DSw_leak(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Tr_DScurrent(const QString& testName, double& criteriumDn, double& criteriumUp);
    virtual void Tr_DSw_driver(const QString& testName, double& criteriumDn, double& criteriumUp);
//---------------------------------------------------------------------------------------
protected:
    double m_milli, m_micro, m_nano, m_pico;
    double m_kilo, m_mega, m_giga, m_tera;

    //названия тестов
    //структуры контактирования
    QRegExp pNpN;
    //Силицидированные резисторы
    QString tRZnTiSi;//на N-моноSi
    QString tRZpTiSi;//на P-моноSi
    QString tRZnSiTiSi;//на N-полиSi
    QString tRZpSiTiSi;//на P-полиSi
    QString tRZSiTiSi;//на нелегированном полиSi

    QString w09, w05, w035, w06;
//---------------------------------------------------------------------------------------
    //меандры
    QString Meander, One, Two, Three, Four;
    //сопротивление резистора в слое Met1 шириной 0,5 мкм (tRM1_3)
    QString dMeander1;
    //сопротивление резистора в слое Met3 шириной 0,6 мкм (tRM1_3)
    QString dMeander3;
    //сопротивление резистора в слое Met1 шириной 0,9 мкм (tRM1_3_09)
    QString dMeander1_09;
    //сопротивление резистора в слое Met3 шириной 0,9 мкм (tRM1_3_09)
    QString dMeander3_09;

    //сопротивление резистора в слое Met2 шириной 0,6 мкм (tRM2_4)
    QString dMeander2;
    //сопротивление резистора в слое Met4 шириной 0,6 мкм (tRM2_4)
    QString dMeander4;
    //сопротивление резистора в слое Met2 шириной 0,9 мкм (tRM2_4_09)
    QString dMeander2_09;
    //сопротивление резистора в слое Met4 шириной 0,9 мкм (tRM2_4_09)
    QString dMeander4_09;

    double divisorMeander;
//---------------------------------------------------------------------------------------
    //кельвины M1-Si
    QString KLV_nM1, KLVnM1;//на N-моноSi
    QString KLV_pM1, KLVpM1;//на P-моноSi
    QString KLV_nSiM1, KLVnSiM1;//на N-полиSi
    QString KLV_pSiM1, KLVpSiM1;//на P-полиSi
    QString KLV_SiM1, KLVSiM1;//на нелегированном полиSi

    //цепочки контактов M1-Si
    QString dZnM1, dZ_nM1;//на N-моноSi
    QString dZpM1, dZ_pM1;//на P-моноSi
    QString dZnSiM1, dZ_nSiM1;//на N-полиSi
    QString dZpSiM1, dZ_pSiM1;//на P-полиSi
    QString dZSiM1, dZ_SiM1;//на нелегированном полиSi

    //кельвины металл-металл
    QString KLV_M1_M2, KLV_M1M2;
    QString KLV_M2_M3, KLV_M2M3;
    QString KLV_M3_M4, KLV_M3M4;
    QString KLV_M1_M4, KLV_M1M4;

    //цепочки контактов металл-металл
    QString dZ_M1M2, dZM1M2, Z_M1M2, ZM1M2;
    QString dZ_M2M3, dZM2M3, Z_M2M3, ZM2M3;
    QString dZ_M3M4, dZM3M4, Z_M3M4, ZM3M4;
    QString dZ_M1M4, dZM1M4, Z_M1M4, ZM1M4;

    //структуры Ван-дер-Пау
    QString VDP;
    QString VDPnWell;
    QString VDPpWell;
    QString VDPn;
    QString VDPp;
    QString VDPnSi;
    QString VDPpSi;

    //емкости
    QString CpSinWell, CnSipWell;
    //диоды
    QString Diod, diod;

    //транзисторы
    QString An, Ap, Rn, Rp, Hn, Hp;
    QString Vt, Vbr;
    QString revers;
    QString Be;
    QString leak, w;
    QString Gleak, G;
    QString DSleak, DS;
    double LEN;//мкм
    QString DSw_leak;
    QString DScurrent, current;
    QString DSw_driver, driver;
};

#endif // BASICNORMS_H
