#ifndef TESTELEMSTATISTICS_H
#define TESTELEMSTATISTICS_H
#include <QDebug>

class TestElemStatistics
{
public:
    TestElemStatistics();
    ~TestElemStatistics();
    //----------------------------------------------------------------------------
    int getDiesNum() const;
    int getDiesNumUnmasked() const;
    int getDiesNumMasked() const;
    int getDiesNumFit() const;
    int getDiesNumUnfit() const;
    double getDiesFitPercent() const;
    double getDiesUnfitPercent() const;

    double getAvg() const;
    double getStd() const;
    double getMin() const;
    double getMax() const;
    //----------------------------------------------------------------------------
    void setDiesNum(const int num);
    void setDiesNumUnmasked(int num);
    void setDiesNumMasked(int num);
    void setDiesNumFit(int num);
    void setDiesNumUnfit(int num);
    void setDiesFitPercent(double diesFitPercent);
    void setDiesUnfitPercent(double diesUnfitPercent);

    void setAvg(double avg);
    void setStd(double std);
    void setMin(double min);
    void setMax(double max);
    //----------------------------------------------------------------------------
private:
    int m_diesNum;
    int m_diesNumUnmasked;
    int m_diesNumMasked;
    int m_diesNumFit;
    int m_diesNumUnfit;
    double m_diesFitPercent;
    double m_diesUnfitPercent;

    double m_avg;
    double m_std;
    double m_min;
    double m_max;
};

#endif // TESTELEMSTATISTICS_H
