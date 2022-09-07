#ifndef MAPIMAGE
#define MAPIMAGE

#include <QWidget>
#include <QMap>
#include <QPainter>
#include <QFileDialog>
#include <QtMath>

#include "Lot/Die.h"
#include "Types.h"
extern QString g_strVersion, g_strYears;
// ======================================================================
class MapImage : public QWidget
{
    Q_OBJECT
public:
    MapImage(QWidget* pwgt = nullptr);
    virtual ~MapImage();
    //----------------------------------------------------------------------------------------------
    void drawStatisticsText(QPainter& painter, const int diesCountPainted);

    void setWaferSlot(const int waferSlot);
    void setTestName(const QString& testName);
    void setParamName(const QString& paramName);
    void setUnitName(const QString &unitName);

    void setDiesNumMeasured(const int numMeasured);
    void setDiesNumUnmasked(const int numUnmasked);
    void setDiesNumMasked(const int numMasked);
    void setDiesFit(const int diesFitNum, const double diesFitPercent);
    void setDiesUnfit(const int diesUnfitNum, const double diesUnfitPercent);

    void setAvg(const double avg);
    void setStd(const double std);
    void setMin(const double min);
    void setMax(const double max);

    void setNormsInterval(const double CriteriumDn, const double CriteriumUp);
    void setNormsDeviations(const double CriteriumDn, const double CriteriumUp);
    //----------------------------------------------------------------------------------------------
    //считывание/установка максимального количества кристаллов
    int getMaxOfDiesAlongRadius() const;
    int getNumOfVoidDiesLayers() const;

    void setMaxOfMesuredDiesAlongRadius(const int MaxOfXY);
    void setNumOfVoidDiesLayers(const int NumOfDiesLayers);
    void setMaxOfDiesAlongRadiusInFact(const int MaxOfDiesAlongRadius);
    //----------------------------------------------------------------------------------------------
    //установка годных/негодных кристаллов (заполнение кристаллов цветом)
    void setFitDies(const vecPair &vecPairXY_Fit);
    void setUnfitDiesUpper(const vecPair &vecPairXY_UnfitMore);
    void setUnfitDiesLower(const vecPair &vecPairXY_UnfitLess);
    //----------------------------------------------------------------------------------------------
    //маскирование кристаллов
    void setUnmaskedDies(const vecPair &vecPairXY, const QVector<double> &vecValues);
    void setMaskedDies(const vecPair &vecPairXY, const QVector<double> &vecValues, const QVector<Mask> &vecMaskType);


    void setCurrentDieMaskState();
    //----------------------------------------------------------------------------------------------
    //масштабирование
    int getScaleFactorDieSize() const;

    void setScaleFactorDieSize(const double scaleFactor);
    void scaleUpDieSize();
    void scaleDownDieSize();
    void setNormalScaleFactorDieSize();
    //----------------------------------------------------------------------------------------------
    //тип карты
    void setMapType(const MapType mt);
    //-----------------------------------------------------------------------------------------------
    //рисование только координат в кристаллах
    void drawOnlyDieCoordinates(QPainter &painter, QRectF& dieRect, const int x, const int y,
                                const int rectFontXY);
    //-----------------------------------------------------------------------------------------------
    //рисование кристаллов
    void drawDieArea(QPainter &painter, QRectF& dieRect,
                     const int x, const int y, const int rectFontXY);
    void drawStandardDie(QPainter &Painter, QRectF& Die, const int x, const int y,
                         const int rectFontXY);
    //-----------------------------------------------------------------------------------------------
public slots:
    //сохранить карту
    void slotSave();
    //маскирование
    void slotDrawDieMasked(const int X, const int Y, const Mask maskState);

protected:
    void paintEvent(QPaintEvent*) override;


private:
    //----------------------------------------------------------------------------------------------
    //изображение карты
    QImage m_imageMap;
    //размер карты
    QSize m_imageSize;
    //разрешение рисунка карты
    int m_widthInPixel;
    int m_heghtInPixel;
    //x-координата карты
    double m_Xmap;
    //y-координата карты
    double m_Ymap;
    //x-координата разделителя
    double m_Xsplitter;
    //поля
    double m_LeftMargin;
    double m_TopMargin;
    //шрифт
    double m_FontWidth;
    //размеры и координаты на пластине
    int m_MaxOfDiesAlongRadius_NoCenterDie;
    //----------------------------------------------------------------------------------------------
    //максимальное значение нарисованной координаты
    int m_MaxOf_XY_Drawn;
    int m_X_MaxOfDieFromCenter;
    int m_Y_MaxOfDieFromCenter;

    //максимальное количество непустых кристаллов
    int m_MaxOfDiesAlongRadiusInFact;
    //количество пустых кристаллов на кромке пластины
    int m_NumOfVoidDieLayers;
    //количество кристаллов на диаметре пластины
    int m_NumOfDiesAlongDiam;
    //внутренний диаметр пласины
    double m_diam;
    //внутренний радиус пластины
    double m_radius;
    //внешний радиус пластины
    double m_externalDiam;
    //размер кристалла
    double m_dieSize;
    //расстояние между кристаллами
    double m_dieSpacing;
    //коэффициент масштабирования кристалла
    double m_dieScale;
    //----------------------------------------------------------------------------------------------
    //отображение статистики на рисунке
    QString m_txtStat;
    QString m_txtWaferSlot_INIT,                    m_txtWaferSlot;
    QString m_txtTestName_INIT,                     m_txtTestName;
    QString m_txtParamName_INIT,                    m_txtParamName;
    QString m_txtUnit_INIT,                         m_txtUnit;

    QString m_txtDiesNumMeasured_INIT,              m_txtDiesNumMeasured;
    QString m_txtDiesNumOnWaferPainted_INIT,        m_txtDiesCountOnWaferPainted;
    QString m_txtFitDiesNum_INIT,                   m_txtFitDiesNum;
    QString m_txtUnFitDiesNum_INIT,                 m_txtUnfitDiesNum;
    QString m_txtUnmaskedDiesNum_INIT,              m_txtUnmaskedDiesNum;
    QString m_txtMaskedDiesNum_INIT,                m_txtMaskedDiesNum;

    QString m_txtCalculationAtNorms;
    QString m_txtCalculationAtFitDies;
    QString m_txtCalculationByNumOfDies_INIT,       m_txtCalculationByNumOfDies;

    QString m_txtAvg_INIT,                          m_txtAvg;
    QString m_txtStd_INIT,                          m_txtStd;
    QString m_txtMin_INIT,                          m_txtMin;
    QString m_txtMax_INIT,                          m_txtMax;
    double m_FromTopPosChipCountOnWaferPainted;

    QString m_txtNormalInterval_INIT,               m_txtNormalInterval;
    QString m_txtNormalDeviation_INIT,              m_txtNormalDeviation1, m_txtNormalDeviation2;
    //-------------------------------------------------------------------------------------------------
    //данные о годных, негодных кристаллах
    vecPair m_vecPairXY_Fit;
    vecPair m_vecPairXY_UnfitLower;
    vecPair m_vecPairXY_UnFitUpper;
    //-------------------------------------------------------------------------------------------------
    //данные о маскированных, немаскированных кристаллах
    int m_diesNumMasked;
    int m_unmaskedDiesNum;
    vecPair m_vecPairXY_Unmasked;
    vecPair m_vecPairXY_Masked;
    QVector<Mask> m_vecMaskType;
    //величины тестов в кристаллах
    QVector<double> m_vecValues_Unmasked;
    QVector<double> m_vecValues_Masked;
    QHash<QString,Mask> m_hash_XY_State_Masked;
    //-------------------------------------------------------------------------------------------------
    //цвета кристаллов
    QColor colorGreen, colorRed, colorBlue, colorBlack, colorGray;
    //-------------------------------------------------------------------------------------------------
    //изменение размера кристалла
    double m_scaleFactorDieSize;
    //-------------------------------------------------------------------------------------------------
    //типы карты
    MapType m_map_type;
    //-------------------------------------------------------------------------------------------------
};

#endif // MAPIMAGE

