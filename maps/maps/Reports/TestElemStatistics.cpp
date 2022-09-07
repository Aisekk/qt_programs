#include "TestElemStatistics.h"

TestElemStatistics::TestElemStatistics(){ qDebug() << "Object created"; }
TestElemStatistics::~TestElemStatistics(){ qDebug() << "Object destroyed"; }
//---------------------------------------------------------------------------------------------
int TestElemStatistics::getDiesNum() const{                         return m_diesNum;}
int TestElemStatistics::getDiesNumUnmasked() const{                 return m_diesNumUnmasked;}
int TestElemStatistics::getDiesNumMasked() const{                   return m_diesNumMasked;}
int TestElemStatistics::getDiesNumFit() const{                      return m_diesNumFit;}
int TestElemStatistics::getDiesNumUnfit() const{                    return m_diesNumUnfit;}
double TestElemStatistics::getDiesFitPercent() const{               return m_diesFitPercent;}
double TestElemStatistics::getDiesUnfitPercent() const{             return m_diesUnfitPercent;}

double TestElemStatistics::getAvg() const{                          return m_avg;}
double TestElemStatistics::getStd() const{                          return m_std;}
double TestElemStatistics::getMin() const{                          return m_min;}
double TestElemStatistics::getMax() const{                          return m_max;}
//---------------------------------------------------------------------------------------------
void TestElemStatistics::setDiesNum(int num)
{ m_diesNum = num; }
void TestElemStatistics::setDiesNumUnmasked(int num)
{ m_diesNumUnmasked = num; }
void TestElemStatistics::setDiesNumMasked(int num)
{ m_diesNumMasked = num; }
void TestElemStatistics::setDiesNumFit(int num)
{ m_diesNumFit = num; }
void TestElemStatistics::setDiesNumUnfit(int num)
{ m_diesNumUnfit = num; }
void TestElemStatistics::setDiesFitPercent(double diesFitPercent)
{ m_diesFitPercent = diesFitPercent; }
void TestElemStatistics::setDiesUnfitPercent(double diesUnfitPercent)
{ m_diesUnfitPercent = diesUnfitPercent; }

void TestElemStatistics::setAvg(double avg)
{ m_avg = avg; }
void TestElemStatistics::setStd(double std)
{ m_std = std; }
void TestElemStatistics::setMin(double min)
{ m_min = min; }
void TestElemStatistics::setMax(double max)
{ m_max = max; }
//---------------------------------------------------------------------------------------------
