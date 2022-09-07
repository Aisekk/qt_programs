#ifndef TESTELEMSTATISTICS_H
#define TESTELEMSTATISTICS_H

class TestElemStatistics
{
public:
    TestElemStatistics();
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
    void setDiesNumUnmasked(const int num);
    void setDiesNumMasked(const int num);
    void setDiesNumFit(const int num);
    void setDiesNumUnfit(const int num);
    void setDiesFitPercent(const double diesFitPercent);
    void setDiesUnfitPercent(const double diesUnfitPercent);

    void setAvg(const double avg);
    void setStd(const double std);
    void setMin(const double min);
    void setMax(const double max);
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
