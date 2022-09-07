#include "MapImage.h"

// ----------------------------------------------------------------------
MapImage::MapImage(QWidget *pwgt/*=0*/) : QWidget(pwgt)
{
    m_widthInPixel = 1024+512;
    m_heghtInPixel = 1024+128;
    m_imageSize = QSize(m_widthInPixel*2, m_heghtInPixel*2);
    m_dieScale = 0.94;
    m_Xmap = m_imageSize.width()*0.28;
    m_Ymap = m_imageSize.height()*0.04;
    m_Xsplitter = m_Xmap*0.98;
    m_LeftMargin = m_imageSize.width()*0.01;//левое поле
    m_TopMargin = m_imageSize.height()*0.05;//верхнее поле
    m_FontWidth = m_imageSize.width()*0.1;
    //---------------------------------------------------------------------------------
    m_MaxOfDiesAlongRadius_NoCenterDie = -1;
    m_X_MaxOfDieFromCenter = m_MaxOfDiesAlongRadius_NoCenterDie;
    m_Y_MaxOfDieFromCenter = m_MaxOfDiesAlongRadius_NoCenterDie;
    m_MaxOf_XY_Drawn = 0;
    //---------------------------------------------------------------------------------
    //изменение размера кристалла
    m_scaleFactorDieSize = 1.8;
    //---------------------------------------------------------------------------------
    //для маскирования
    m_diesNumMasked = 0;
    m_unmaskedDiesNum = 0;
    //---------------------------------------------------------------------------------
    //Текст статистики
    m_txtStat = "СТАТИСТИКА ";
    m_txtWaferSlot_INIT = "Слот: ";         m_txtWaferSlot = m_txtWaferSlot_INIT;
    m_txtTestName_INIT = "Тест: ";          m_txtTestName = m_txtTestName_INIT;
    m_txtParamName_INIT = "Параметр: ";     m_txtParamName =  m_txtParamName_INIT;
    m_txtUnit_INIT = "Ед. измерения: ";     m_txtUnit = m_txtUnit_INIT;

    m_txtDiesNumOnWaferPainted_INIT = "на карте: ";
    m_txtDiesCountOnWaferPainted = m_txtDiesNumOnWaferPainted_INIT;

    m_txtDiesNumMeasured_INIT = "измеренных: ";
    m_txtDiesNumMeasured = m_txtDiesNumMeasured_INIT;

    m_txtUnmaskedDiesNum_INIT = "немаскированных: ";
    m_txtUnmaskedDiesNum = m_txtUnmaskedDiesNum_INIT;

    m_txtMaskedDiesNum_INIT = "маскированных: ";
    m_txtMaskedDiesNum = m_txtMaskedDiesNum_INIT;

    m_txtFitDiesNum_INIT = "годных: ";
    m_txtFitDiesNum = m_txtFitDiesNum_INIT;

    m_txtUnFitDiesNum_INIT = "брак: ";
    m_txtUnfitDiesNum = m_txtUnFitDiesNum_INIT;

    m_txtCalculationAtNorms = "Расчет на интервале ";
    m_txtCalculationByNumOfDies_INIT = "(по " + QString::number(m_unmaskedDiesNum,10)
            + " кристаллам):";
    m_txtCalculationByNumOfDies = m_txtCalculationByNumOfDies_INIT;

    m_txtAvg_INIT = "среднее: ";       m_txtAvg = m_txtAvg_INIT;
    m_txtStd_INIT = "сигма, %: ";       m_txtStd = m_txtStd_INIT;
    m_txtMin_INIT = "минимум: ";        m_txtMin = m_txtMin_INIT;
    m_txtMax_INIT = "максимум: ";       m_txtMax = m_txtMax_INIT;

    m_txtNormalInterval_INIT = "Интервал: ";
    m_txtNormalInterval = "";
    m_txtNormalDeviation_INIT = "Вне интервала: ";
    m_txtNormalDeviation1 = ""; m_txtNormalDeviation2 = "";

    m_txtCalculationAtFitDies = "по годным кристаллам: ";
    //------------------------------------------------------------------------------------------
    //цвета кристаллов
    colorGreen = QColor(0,255,0,128);
    colorRed = QColor(255,0,0,128);
    colorBlue = QColor(0,0,255,64);
    colorBlack = QColor(0,0,0,192+16);
    colorGray = QColor(0,0,0,32+16);
}
// ----------------------------------------------------------------------
MapImage::~MapImage(){}
// ----------------------------------------------------------------------
//рисование текста статистики
void MapImage::drawStatisticsText(QPainter& painter, int diesCountPainted)
{
    painter.begin(&m_imageMap);

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    double FontMargin = 2.0;
    double base = 1.1, mltpl = 0.2, st = 0.5;
    //QFont fontMap("New Courier", 38);
    QFont fontMap("Times New Roman", 38);
    QFont fontMapItalic("Times New Roman", 38,-1,true);
    painter.setFont(fontMap);

    painter.drawText(m_LeftMargin, m_TopMargin, m_txtStat);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*mltpl), m_txtWaferSlot);

    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtTestName);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtParamName);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtUnit);

    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st*2)), "Кристаллов");
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)),
                     m_txtDiesCountOnWaferPainted);
    m_FromTopPosChipCountOnWaferPainted = m_TopMargin*(FontMargin + base*mltpl);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtDiesNumMeasured);

    painter.setFont(fontMapItalic);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtUnmaskedDiesNum);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtMaskedDiesNum);
    painter.setFont(fontMap);

    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtFitDiesNum);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtUnfitDiesNum);


    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st*2)), m_txtCalculationAtNorms);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtCalculationByNumOfDies);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtAvg);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtStd);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtMin);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)), m_txtMax);

    //green
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st*2)),
                     m_txtNormalInterval_INIT);
    painter.drawText(m_LeftMargin, m_TopMargin*(FontMargin + base*(mltpl+=st)),
                     m_txtNormalInterval);
    //-----------------------------------------------------------------------------
    //отображение количества нарисованных кристаллов
    if(diesCountPainted >= 1)
    {
        m_txtDiesCountOnWaferPainted = QString(m_txtDiesNumOnWaferPainted_INIT +
                                               QString::number(diesCountPainted,10));
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.setFont(QFont("Times New Roman", 38));
        painter.drawText(m_LeftMargin,
                         m_FromTopPosChipCountOnWaferPainted, m_txtDiesCountOnWaferPainted);
        m_txtDiesCountOnWaferPainted = "";
    }
    // -----------------------------------------------------------------------------
    painter.end();
}
//----------------------------------------------------------------------
//устновка данных тестового элемента
void MapImage::setWaferSlot(int waferSlot)
{
    m_txtWaferSlot = "Cлот: " + QString::number(waferSlot, 10);
}
void MapImage::setTestName(const QString& testName)
{
    m_txtTestName = "Тест: " + testName;
}
void MapImage::setParamName(const QString& paramName)
{
    m_txtParamName = m_txtParamName_INIT + paramName;
}
void MapImage::setUnitName(const QString& unitName)
{
    m_txtUnit = m_txtUnit_INIT + " " + unitName;
}
//----------------------------------------------------------------------
//установка статистических данных
void MapImage::setDiesNumMeasured(int numMeasured)
{
    m_txtDiesNumMeasured = m_txtDiesNumMeasured_INIT + QString::number(numMeasured, 10);
}
void MapImage::setDiesNumUnmasked(int numUnmasked)
{
    m_txtUnmaskedDiesNum = m_txtUnmaskedDiesNum_INIT + QString::number(numUnmasked, 10);
}
void MapImage::setDiesNumMasked(int numMasked)
{
    m_txtMaskedDiesNum = m_txtMaskedDiesNum_INIT + QString::number(numMasked, 10);
}
void MapImage::setDiesFit(int diesFitNum, double diesFitPercent)
{
    m_txtFitDiesNum = m_txtFitDiesNum_INIT +  QString::number(diesFitNum, 10)
            + " (" + QString::number(diesFitPercent,'f',2) + "%)";

    m_txtCalculationByNumOfDies = "(по "+QString::number(diesFitNum,10)+" кристаллам):";
}
void MapImage::setDiesUnfit(int diesUnfitNum, double diesUnfitPercent)
{
    m_txtUnfitDiesNum = m_txtUnFitDiesNum_INIT +  QString::number(diesUnfitNum, 10)
            + " (" + QString::number(diesUnfitPercent,'f',2) + "%)";
}

void MapImage::setAvg(double avg)
{
    double fvalue = fabs(avg);
    if( (fvalue >= 1000.0 || fvalue < 0.01) && fvalue != 0.0)
        m_txtAvg = m_txtAvg_INIT + QString::number(avg,'e',2);
    else
        m_txtAvg = m_txtAvg_INIT + QString::number(avg,'f',2);
}
void MapImage::setStd(double std)
{
    double fvalue = fabs(std);
    if( (fvalue >= 1000.0 || fvalue < 0.01) && fvalue != 0.0)
        m_txtStd = m_txtStd_INIT + QString::number(std,'e',2);
    else
        m_txtStd = m_txtStd_INIT + QString::number(std,'f',2);
}
void MapImage::setMin(double min)
{
    double fvalue = fabs(min);
    if( (fvalue >= 1000.0 || fvalue < 0.01) && fvalue != 0.0)
        m_txtMin = m_txtMin_INIT + QString::number(min,'e',2);
    else
        m_txtMin = m_txtMin_INIT + QString::number(min,'f',2);
}
void MapImage::setMax(double max)
{
    double fvalue = fabs(max);
    if( (fvalue >= 1000.0 || fvalue < 0.01) && fvalue != 0.0)
        m_txtMax = m_txtMax_INIT + QString::number(max,'e',2);
    else
        m_txtMax = m_txtMax_INIT + QString::number(max,'f',2);
}
// ----------------------------------------------------------------------
//установка норм и отклонений
void MapImage::setNormsInterval(double CriterionDn, double CriterionUp)
{
    QString strCriterionDn;
    QString strCriterionUp;
    if( fabs(CriterionDn) > 1.0e+3 || fabs(CriterionDn) < 1.0e-2 )
    {
        if(CriterionDn == 0.0) strCriterionDn = QString::number(CriterionDn,'f',2);
        else strCriterionDn = QString::number(CriterionDn,'e',2);
    }
    else strCriterionDn = QString::number(CriterionDn,'f',2);
    //---------------------------------------------------------------------------   
    if( fabs(CriterionUp) > 1.0e+3 || fabs(CriterionUp) < 1.0e-2 )
    {
        if(CriterionUp == 0.0) strCriterionUp = QString::number(CriterionUp,'f',2);
        else strCriterionUp = QString::number(CriterionUp,'e',2);
    }
    else strCriterionUp = QString::number(CriterionUp,'f',2);
    //---------------------------------------------------------------------------
    if(CriterionDn < -1.0e+200) strCriterionDn = "-inf";
    if(CriterionUp > 1.0e+200) strCriterionUp = "+inf";
    m_txtNormalInterval = "[" + strCriterionDn + "; " + strCriterionUp + "]";
}
void MapImage::setNormsDeviations(double criterionDn, double criterionUp)
{
    QString strCriterionBottom;
    if( fabs(criterionDn) > 1.0e+3 || fabs(criterionDn) < 1.0e-2 )
    {
        if(criterionDn == 0.0)
            strCriterionBottom = QString::number(criterionDn,'f',2);
        else
            strCriterionBottom = QString::number(criterionDn,'e',2);
    }
    else
        strCriterionBottom = QString::number(criterionDn,'f',2);

    m_txtNormalDeviation1 = "< " + strCriterionBottom;
    //----------------------------------------------------------------------------
    QString strCriterionTop;
    if( fabs(criterionUp) > 1.0e+3 || fabs(criterionUp) < 1.0e-2 )
    {
        if(criterionUp == 0.0)
            strCriterionTop = QString::number(criterionUp,'f',2);
        else
            strCriterionTop = QString::number(criterionUp,'e',2);
    }
    else
        strCriterionTop = QString::number(criterionUp,'f',2);

    m_txtNormalDeviation2 = "> " + strCriterionTop;
}
//-----------------------------------------------------------------------
//считывание, установка максимального количества кристаллов
int MapImage::getMaxOfDiesAlongRadius() const
{
    return m_MaxOfDiesAlongRadiusInFact;
}
int MapImage::getNumOfVoidDiesLayers() const
{
    return m_NumOfVoidDieLayers;
}

void MapImage::setMaxOfMesuredDiesAlongRadius(int MaxOfXY)
{
    m_MaxOfDiesAlongRadiusInFact = MaxOfXY;
}
void MapImage::setNumOfVoidDiesLayers(int NumOfVoidDieLayers)
{
    m_NumOfVoidDieLayers = NumOfVoidDieLayers;
}
void MapImage::setMaxOfDiesAlongRadiusInFact(int MaxOfDiesAlongRadius)
{
    if(MaxOfDiesAlongRadius < 6)
        m_MaxOfDiesAlongRadius_NoCenterDie = 5;
    else if(MaxOfDiesAlongRadius >= 6)
        m_MaxOfDiesAlongRadius_NoCenterDie = MaxOfDiesAlongRadius;

    m_X_MaxOfDieFromCenter = m_MaxOfDiesAlongRadius_NoCenterDie;
    m_Y_MaxOfDieFromCenter = m_MaxOfDiesAlongRadius_NoCenterDie;
}
//======================================================================================
//установка годных, негодных кристаллов
void MapImage::setFitDies(vecPair& vecPairXY_Fit)
{
    m_vecPairXY_Fit = std::move(vecPairXY_Fit);
}
void MapImage::setUnfitDiesUpper(vecPair& vecPairXY_UnfitMore)
{
   m_vecPairXY_UnFitUpper = std::move(vecPairXY_UnfitMore);
}
void MapImage::setUnfitDiesLower(vecPair& vecPairXY_UnfitLess)
{
    m_vecPairXY_UnfitLower = std::move(vecPairXY_UnfitLess);
}
//======================================================================================
//маскирование
//запись немаскированных величин на пластину
void MapImage::setUnmaskedDies(vecPair& vecPairXY, QVector<double>& vecValues)
{
    m_vecPairXY_Unmasked = std::move(vecPairXY);
    m_vecValues_Unmasked = std::move(vecValues);
}
//запись маскированных величин на пластину
void MapImage::setMaskedDies(vecPair& vecPairXY, QVector<double>& vecValues,
                             QVector<Mask>& vecMaskType)
{
    m_vecPairXY_Masked = std::move(vecPairXY);
    m_vecValues_Masked = std::move(vecValues);
    m_vecMaskType = std::move(vecMaskType);
}
//слот для приема координат int,int и состояния кристалла bool
void MapImage::slotDrawDieMasked(int X, int Y, Mask maskState)
{
    QString XY = QString::number(X,10) + "_" + QString::number(Y,10);

    if(maskState == Mask::no)
    {
        if(!m_hash_XY_State_Masked.contains(XY))
        {
            m_hash_XY_State_Masked.insert(XY, maskState);
            ++m_diesNumMasked;
        }
    }
    else if(maskState >= Mask::red)
        if(!m_hash_XY_State_Masked.isEmpty())
            if(m_hash_XY_State_Masked.contains(XY))
            {
                m_hash_XY_State_Masked.remove(XY);
                if(m_diesNumMasked > 0)
                    --m_diesNumMasked;
            }

    m_txtMaskedDiesNum = m_txtMaskedDiesNum_INIT + QString::number(m_diesNumMasked, 10);
    update();
}

//======================================================================================
//масштабирование
int MapImage::getScaleFactorDieSize() const
{
    return m_scaleFactorDieSize;
}

void MapImage::setScaleFactorDieSize(double scaleFactor)
{
    m_scaleFactorDieSize = scaleFactor;
}
void MapImage::setNormalScaleFactorDieSize()
{
    m_scaleFactorDieSize = 1.8;
}
void MapImage::scaleUpDieSize()
{
    m_scaleFactorDieSize -= 0.2;
}
void MapImage::scaleDownDieSize()
{
    m_scaleFactorDieSize += 0.2;
}
//----------------------------------------------------------------------
//установка типа карты
void MapImage::setMapType(MapType mt)
{
    m_map_type = mt;
}
//==========================================================================================
//перерисовка карты
void MapImage::paintEvent(QPaintEvent*)
{
    m_imageMap = QImage(m_imageSize, QImage::Format_ARGB32_Premultiplied);
    m_imageMap.fill(Qt::white);

    QPainter painter(this);

    //непрозрачный режим
    painter.begin(&m_imageMap);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.end();
    //----------------------------------------------------------------------------------------------
    //шрифт
    painter.begin(&m_imageMap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.initFrom(this);
    painter.end();
    //==============================================================================================
    //рисование карты
    painter.begin(&m_imageMap);
    //----------------------------------------------------------------------------------------------
    //расчет размера кристалла и максимального количества кристаллов вдоль X или Y
    if(m_X_MaxOfDieFromCenter > m_Y_MaxOfDieFromCenter
            || m_X_MaxOfDieFromCenter == m_Y_MaxOfDieFromCenter)
    {
        m_NumOfDiesAlongDiam = m_X_MaxOfDieFromCenter*2 + 1;
        m_dieSize = ((m_imageSize.height() - m_Xmap*0.10)/m_NumOfDiesAlongDiam)*m_dieScale;
        //расстояние между кристаллами
        m_dieSpacing = m_dieSize * 0.06;
    }
    if(m_Y_MaxOfDieFromCenter > m_X_MaxOfDieFromCenter
            || m_Y_MaxOfDieFromCenter == m_X_MaxOfDieFromCenter)
    {
        m_NumOfDiesAlongDiam = m_Y_MaxOfDieFromCenter*2 + 1;
        m_dieSize = ((m_imageSize.height() - m_Xmap*0.10)/m_NumOfDiesAlongDiam)*m_dieScale;
        //расстояние между кристаллами
        m_dieSpacing = m_dieSize * 0.06;
    }
    //----------------------------------------------------------------------------------------------
    //расчет диаметра
    double addition = m_imageSize.height()*0.01;//добавка к суммарному размеру чипов
    m_diam = m_NumOfDiesAlongDiam*m_dieSize + addition;
    m_radius = m_diam/2;
    double edge = m_diam*0.05;
    m_externalDiam = m_diam + edge;
    //----------------------------------------------------------------------------------------------
    //рисование внешней окружности
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
    QRectF ExternalRect(m_Xmap - edge/2, m_Ymap - edge/2, m_externalDiam, m_externalDiam);
    painter.drawChord(ExternalRect,-72*16,324*16);
    //рисование внутренней окружности
    painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    QRectF rect(m_Xmap, m_Ymap, m_diam, m_diam);
    painter.drawEllipse(rect);
    //рисование линий
    double Xpos = m_Xmap, Ypos = m_Ymap, dL = edge/2 + edge/4;
    QLineF lineH(Xpos - dL, Ypos + m_diam/2, Xpos + dL + m_diam, Ypos + m_diam/2);
    QLineF lineV(Xpos + m_diam/2, Ypos - dL, Xpos + m_diam/2, Ypos + m_diam + edge/4);
    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
    painter.drawLine(lineH);
    painter.drawLine(lineV);
    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
    //----------------------------------------------------------------------------------------------
    //рисование кристаллов
    //переопределение размера кристалла с учетом расстояния между чипами
    m_dieSize = m_dieSize - m_scaleFactorDieSize * m_dieSpacing;
    //инициализация X центральным кристаллом
    double X0 = (m_Xmap + m_diam/2) - m_dieSize/2;
    double Y0 = (m_Ymap + m_diam/2) - m_dieSize/2;
    double tempXR = X0;
    double tempXL = X0;
    double tempYD = Y0;
    double tempYU = Y0;
    //-----------------------------------------------------------------------
    //переопределение радиуса
    double add = (m_dieSize/2 + addition)*1.05;
    double radius = m_radius - add;
    //количество нарисованных кристаллов + кол-во перерисованных кристаллов
    int diesCountPainted = 0;
    //координаты кристаллов
    int x = 0, y = 0;
    //масштабирование шрифта внутри кристалла по размеру кристалла
    int rectFontXY = m_dieSize/3.5;
    // -----------------------------------------------------------------------------
    //рисование данных на кристаллах
    switch(m_map_type)
    {
    case MapType::standard:
    {
        diesCountPainted = 0;
        for(int j = 0; j < m_Y_MaxOfDieFromCenter + 1; ++j)
        {
            for(int i = 0; i < m_X_MaxOfDieFromCenter + 1; ++i)
            {
                //кристалл в квадрате 1 (слева вверху)
                QRectF dieLU(tempXL, tempYU, m_dieSize, m_dieSize);
                //кристалл в квадрате 2 (справа вверху)
                QRectF dieRU(tempXR, tempYU, m_dieSize, m_dieSize);
                //кристалл в квадрате 3 (слева внизу)
                QRectF dieLD(tempXL, tempYD, m_dieSize, m_dieSize);
                //кристалл в квадрате 4 (справа внизу)
                QRectF dieRD(tempXR, tempYD, m_dieSize, m_dieSize);

                double r_LeftUp  = qSqrt(qPow(tempXL - X0, 2.0) + qPow(tempYU - Y0, 2.0));
                double r_RightUp = qSqrt(qPow(tempXR - X0, 2.0) + qPow(tempYU - Y0, 2.0));
                double r_LeftDn = qSqrt(qPow(tempXL - X0, 2.0) + qPow(tempYD - Y0, 2.0));
                double r_RightDn = qSqrt(qPow(tempXR - X0, 2.0) + qPow(tempYD - Y0, 2.0));
                double r_Left = r_LeftUp;
                double r_Right = r_RightUp;
                double r_Up = r_LeftUp;
                double r_Dn = r_LeftDn;

                //рисование кристаллов вдоль горизонтального и вертикального диаметров
                //-------------------------------------------------------------------------
                //кристаллы вдоль левого радиуса и центральный чип
                if(r_Left < radius && j==0)
                {
                    painter.eraseRect(dieLU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLU);
                    x = -i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //кристаллы вдоль правого радиуса
                if(r_Right < radius && i!=0 && j==0)
                {
                    painter.eraseRect(dieRU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieRU);
                    x = i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieRU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //кристаллы вдоль верхнего радиуса
                if(r_Up < radius && i==0 && j!=0)
                {
                    painter.eraseRect(dieLU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLU);
                    x = i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //кристаллы вдоль нижнего радиуса
                if(r_Dn < radius && i==0 && j!=0)
                {
                    painter.eraseRect(dieLD);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLD);
                    x = i; y = -j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLD,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //-------------------------------------------------------------------------
                //рисование чипов в квадратах
                // квадрат 1
                if(r_LeftUp < radius && i!=0 && j!=0)
                {
                    painter.eraseRect(dieLU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLU);
                    x = -i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                // квадрат 2
                if(r_RightUp < radius && i!=0 && j!=0)
                {
                    painter.eraseRect(dieRU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieRU);
                    x = i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieRU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                // квадрат 3
                if(r_LeftDn < radius && i!=0 && j!=0)
                {
                    painter.eraseRect(dieLD);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLD);
                    x = -i; y = -j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLD,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                // квадрат 4
                if(r_RightDn < radius && i!=0 && j!=0)
                {
                    painter.eraseRect(dieRD);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieRD);
                    x = i; y = -j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieRD,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //-------------------------------------------------------------------------
                tempXR += (m_dieSize + m_dieSpacing);
                tempXL -= (m_dieSize + m_dieSpacing);
            }
            tempXR = X0;
            tempXL = X0;
            tempYD += (m_dieSize + m_dieSpacing);
            tempYU -= (m_dieSize + m_dieSpacing);
        }
        break;
    }
    case MapType::coordinates:
    {
        if(m_MaxOfDiesAlongRadius_NoCenterDie == -1)
        {
            m_MaxOfDiesAlongRadius_NoCenterDie = 9;
            m_X_MaxOfDieFromCenter = m_MaxOfDiesAlongRadius_NoCenterDie;
            m_Y_MaxOfDieFromCenter = m_MaxOfDiesAlongRadius_NoCenterDie;
        }
        diesCountPainted = 0;
        for(int j = 0; j < m_Y_MaxOfDieFromCenter + 10; ++j)
        {
            for(int i = 0; i < m_X_MaxOfDieFromCenter + 10; ++i)
            {
                //кристалл в квадрате 1 (слева вверху)
                QRectF dieLU(tempXL, tempYU, m_dieSize, m_dieSize);
                //кристалл в квадрате 2 (справа вверху)
                QRectF dieRU(tempXR, tempYU, m_dieSize, m_dieSize);
                //кристалл в квадрате 3 (слева внизу)
                QRectF dieLD(tempXL, tempYD, m_dieSize, m_dieSize);
                //кристалл в квадрате 4 (справа внизу)
                QRectF dieRD(tempXR, tempYD, m_dieSize, m_dieSize);

                double r_LeftUp  = qSqrt(qPow(tempXL - X0, 2.0) + qPow(tempYU - Y0, 2.0));
                double r_RightUp = qSqrt(qPow(tempXR - X0, 2.0) + qPow(tempYU - Y0, 2.0));
                double r_LeftDn = qSqrt(qPow(tempXL - X0, 2.0) + qPow(tempYD - Y0, 2.0));
                double r_RightDn = qSqrt(qPow(tempXR - X0, 2.0) + qPow(tempYD - Y0, 2.0));
                double r_Left = r_LeftUp;
                double r_Right = r_RightUp;
                double r_Up = r_LeftUp;
                double r_Dn = r_LeftDn;

                //рисование кристаллов вдоль горизонтального и вертикального диаметров
                //--------------------------------------------------------------------------
                //кристаллы вдоль левого радиуса и центральный чип
                if(r_Left < radius && j==0)
                {
                    painter.eraseRect(dieLU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLU);
                    x = -i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //кристаллы вдоль правого радиуса
                if(r_Right < radius && i!=0 && j==0)
                {
                    painter.eraseRect(dieRU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieRU);
                    x = i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieRU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //кристаллы вдоль верхнего радиуса
                if(r_Up < radius && i==0 && j!=0)
                {
                    painter.eraseRect(dieLU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLU);
                    x = i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //кристаллы вдоль нижнего радиуса
                if(r_Dn < radius && i==0 && j!=0)
                {
                    painter.eraseRect(dieLD);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLD);
                    x = i; y = -j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLD,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //--------------------------------------------------------------------------
                //рисование кристаллов в квадратах
                // квадрат 1
                if(r_LeftUp < radius && i!=0 && j!=0)
                {
                    painter.eraseRect(dieLU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLU);
                    x = -i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                // квадрат 2
                if(r_RightUp < radius && i!=0 && j!=0)
                {
                    painter.eraseRect(dieRU);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieRU);
                    x = i; y = j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieRU,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                // квадрат 3
                if(r_LeftDn < radius && i!=0 && j!=0)
                {
                    painter.eraseRect(dieLD);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieLD);
                    x = -i; y = -j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieLD,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                // квадрат 4
                if(r_RightDn < radius && i!=0 && j!=0)
                {
                    painter.eraseRect(dieRD);
                    painter.setPen(QPen(Qt::gray, 2, Qt::SolidLine));
                    painter.drawRect(dieRD);
                    x = i; y = -j;
                    m_MaxOf_XY_Drawn = (i > j)? i : j;
                    drawDieArea(painter,dieRD,x,y,rectFontXY);
                    ++diesCountPainted;
                }
                //--------------------------------------------------------------------------
                tempXR += (m_dieSize + m_dieSpacing);
                tempXL -= (m_dieSize + m_dieSpacing);
            }
            tempXR = X0;
            tempXL = X0;
            tempYD += (m_dieSize + m_dieSpacing);
            tempYU -= (m_dieSize + m_dieSpacing);
        }
        break;
    }
    }

    painter.end();
    //==============================================================================================
    //статистика на карте
    drawStatisticsText(painter, diesCountPainted);
    // -----------------------------------------------------------------------------
    update();
    //------------------------------------------------------------------------------
    //завершение рисования карты
    //отображение карты на виджете
    painter.begin(this);
    //рисуем изображение от 0,0 и растягиваем по всему виджету
    painter.drawImage(0, 0, m_imageMap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painter.end();
}
//==========================================================================================
//функции, используемые в paintEvent()
void MapImage::drawOnlyDieCoordinates(QPainter &painter, QRectF& dieRect,
                                      int x, int y, int rectFontXY)
{
    QString strPos, strX, strY;
    strX = QString::number(x,10);
    strY = QString::number(y,10);

    //координаты в кристаллах
    painter.setPen(QPen(colorBlack, 1, Qt::SolidLine));
    painter.setFont(QFont("Times New Roman", rectFontXY));
    strPos = strX + ", " + strY;
    painter.drawText(dieRect, strPos, QTextOption(Qt::AlignCenter));
}
void MapImage::drawDieArea(QPainter& painter, QRectF& dieRect,
                           int x, int y, int rectFontXY)
{
    //маскирование (закраска цветом маски) кристаллов
    vecPair::const_iterator citM = m_vecPairXY_Masked.constBegin();
    QVector<Mask>::const_iterator citMT = m_vecMaskType.constBegin();
    while(citM != m_vecPairXY_Masked.constEnd() && citMT != m_vecMaskType.constEnd())
    {
        if(citM->first == x && citM->second == y)
        {
            Mask maskState = *citMT;
            QColor maskColor = colorRed;
            switch(maskState)
            {
            case Mask::red:
            { maskColor = colorRed; break; }
            case Mask::blue:
            { maskColor = colorBlue; break; }
            case Mask::gray:
            { maskColor = colorGray; break; }
            default: break;
            }
            painter.fillRect(dieRect, QBrush(maskColor, Qt::SolidPattern));
        }
        ++citM;
        ++citMT;
    }

    //закраска годных кристаллов
    vecPair::const_iterator citF = m_vecPairXY_Fit.constBegin();
    while(citF != m_vecPairXY_Fit.constEnd())
    {
        if(citF->first == x && citF->second == y)
            painter.fillRect(dieRect, QBrush(colorGreen, Qt::SolidPattern));
        ++citF;
    }

    //закраска негодных кристаллов Less
    vecPair::const_iterator citUL = m_vecPairXY_UnfitLower.constBegin();
    while(citUL != m_vecPairXY_UnfitLower.constEnd())
    {
        if(citUL->first == x && citUL->second == y)
            painter.fillRect(dieRect, QBrush(colorRed, Qt::SolidPattern));
        ++citUL;
    }

    //закраска негодных кристаллов More
    vecPair::const_iterator citUM = m_vecPairXY_UnFitUpper.constBegin();
    while(citUM != m_vecPairXY_UnFitUpper.constEnd())
    {
        if(citUM->first == x && citUM->second == y)
            painter.fillRect(dieRect, QBrush(colorRed, Qt::SolidPattern));
        ++citUM;
    }


    //рисование внутри кристаллов:
    switch(m_map_type)
    {
    case MapType::standard:
        drawStandardDie(painter,dieRect,x,y,rectFontXY);
        break;
    case MapType::coordinates:
        drawOnlyDieCoordinates(painter,dieRect,x,y,rectFontXY);
        break;
    }
}
void MapImage::drawStandardDie(QPainter &Painter, QRectF& Die,
                               int x, int y, int rectFontXY)
{
    //координаты в чипах
    int rectFontValuesBig = rectFontXY*1.00;
    int rectFontValuesMid = rectFontXY*0.79;
    int rectFontValuesSmall = rectFontXY*0.70;
    //Длина числа для выбора подходящего шрифта
    int valueLen1 = 5;// <= valueLen1
    int valueLen2 = 7;// > valueLen1 && <= valueLen2; > valueLen2

    QString strPos, strX, strY;
    strX = QString::number(x,10);
    strY = QString::number(y,10);

    Painter.setPen(QPen(colorBlack, 1, Qt::SolidLine));
    Painter.setFont(QFont("Times New Roman", rectFontXY));

    strPos = strX + ", " + strY;
    Painter.drawText(Die, strPos, QTextOption(Qt::AlignHCenter | Qt::AlignTop));

    //величины в чипах
    vecPair::const_iterator citXY = m_vecPairXY_Unmasked.constBegin();
    QVector<double>::const_iterator citV = m_vecValues_Unmasked.constBegin();
    while(citXY != m_vecPairXY_Unmasked.constEnd() &&
          citV != m_vecValues_Unmasked.constEnd())
    {
        QString strValue = "";
        if(citXY->first == x && citXY->second == y)
        {
            if((fabs(*citV) >= 1.0*1e3 || fabs(*citV) <= 1.0*1e-3) && *citV != 0.0)
                strValue = QString::number(*citV,'e',1);
            else
                strValue = QString::number(*citV,'f',2);
        }
        Painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        if(strValue.length() <= valueLen1)
        {
            Painter.setFont(QFont("Times New Roman", rectFontValuesBig));
            Painter.drawText(Die, strValue, QTextOption(Qt::AlignBottom | Qt::AlignHCenter));
        }
        else if(strValue.length() > valueLen1 && strValue.length() <= valueLen2)
        {
            Painter.setFont(QFont("Times New Roman", rectFontValuesMid));
            Painter.drawText(Die, strValue, QTextOption(Qt::AlignBottom | Qt::AlignHCenter));
        }
        else if(strValue.length() > valueLen2)
        {
            Painter.setFont(QFont("Times New Roman", rectFontValuesSmall));
            Painter.drawText(Die, strValue, QTextOption(Qt::AlignBottom | Qt::AlignHCenter));
        }
        ++citXY; ++citV;
    }
}
//==========================================================================================
//СЛОТЫ
//сохранение рисунка карты
void MapImage::slotSave()
{
    QString strFilter{};
    QString fileName = QFileDialog::
            getSaveFileName(this, "","","Изображение(*.png);;Изображение(*.jpg)",
                            &strFilter);
    if(!fileName.isEmpty())
        if(&m_imageMap != nullptr)
        {
            if(strFilter.contains("jpg"))
                m_imageMap.save(fileName,"JPG",100);
            else if(strFilter.contains("png"))
                m_imageMap.save(fileName,"PNG");
            else if(strFilter.contains("bmp"))
                m_imageMap.save(fileName,"BMP");
        }
}




