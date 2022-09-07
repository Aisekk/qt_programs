#include "MaskWindow.h"

MaskWindow::MaskWindow(QWidget *pwgt) :
    QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint)
{
    setModal(true);
    setWindowTitle("Маскирование");
    //setMinimumSize(100,100);
    setFixedSize(QWidget::sizeHint());
    m_size = 44;

    QFont LabelFont("New Courier", 10);
    setFont(LabelFont);
    m_pLabel = new QLabel("Выберите тестовый элемент");
    m_pLabel->setAlignment(Qt::AlignTop);

    m_pgrdLayout = new QGridLayout;
    m_phbxLayout = new QHBoxLayout;
    m_pvbxMainLayout = new QVBoxLayout;

    //рисование карты Toggle Bottons
    m_diesNumOnRadius = 9;
    //n - присвоение для улучшения читабельности цикла:
    int n = m_diesNumOnRadius;
    QString strRow, strCol, strSum, strMinus("-");
    int row = 0, col = 0;
    for(int i = -n; i <= n; ++i)
    {
        row = 0;
        strRow = QString::number(i, 10);
        for(int j = n; j >= -n; --j)
        {
            strCol = QString::number(j, 10);
            if(strCol.contains(strMinus))   strSum = strRow + "," + strCol;
            else                            strSum = strRow + ", " + strCol;
            if(abs(i) + abs(j) < (n-3)+(n-2)+1) //< 14
            {
                //toggle buttons
                QPushButton *pcmdToggle = new QPushButton;
                pcmdToggle->setFlat(true);
                pcmdToggle->setCheckable(true);
                pcmdToggle->setText(strSum);
                pcmdToggle->setObjectName(strRow + "_" + strCol);
                pcmdToggle->setChecked(true);

                pcmdToggle->setMinimumWidth(m_size);
                pcmdToggle->setMinimumHeight(m_size);

                connect(pcmdToggle, QPushButton::toggled, this, slotApplyToEnable);
                connect(pcmdToggle, QPushButton::toggled, this, slotMaskInsert);

                m_pgrdLayout->addWidget(pcmdToggle,row,col);
                pcmdToggle->setVisible(false);
                //запись адресов кнопок
                m_vec_pToggleBtns.push_back(pcmdToggle);
            }
            ++row;
        }
        ++col;
    }
//------------------------------------------------------------------------------------------------
    QPushButton *pcmdOk = new QPushButton("&Ok");
    QPushButton *pcmdCancel = new QPushButton("&Отмена");
    m_pcmdApply = new QPushButton("&Применить");
    m_pcmdApply->setEnabled(false);

    connect(pcmdOk, &QPushButton::clicked, this, accept);
    connect(pcmdOk, &QPushButton::clicked, this, slotApply);
    connect(m_pcmdApply, &QPushButton::clicked, this, slotApply);
    connect(pcmdCancel, &QPushButton::clicked, this, reject);


    m_pvbxMainLayout->setMargin(10);
    m_pvbxMainLayout->setSpacing(4);
    m_pvbxMainLayout->addWidget(m_pLabel);
    m_pvbxMainLayout->addLayout(m_pgrdLayout);
    //Ok, Apply, Cancel
    m_phbxLayout->addStretch(1);
    m_phbxLayout->addWidget(pcmdOk);
    m_phbxLayout->addWidget(m_pcmdApply);
    m_phbxLayout->addWidget(pcmdCancel);
    m_pvbxMainLayout->addLayout(m_phbxLayout);

    setLayout(m_pvbxMainLayout);
}
//------------------------------------------------------------------------------------------------
MaskWindow::~MaskWindow(){}
//------------------------------------------------------------------------------------------------
void MaskWindow::sendSigMaskState()
{
    int x = 0;
    int y = 0;
    QStringList XY{};
    QString strX{}, strY{};
    QString strXY{};
    Mask state{};
    auto cit = m_hashDies_XY_State.constBegin();
    for(;cit != m_hashDies_XY_State.constEnd(); ++cit)
    {
        XY = (cit.key()).split("_");
        strX = XY[0];  strY = XY[1];
        x = strX.toInt();  y = strY.toInt();
        // !!! количество отправленных сигналов = количество элементов в перебираемом массиве
        strXY = cit.key();
        state = cit.value();

        emit sigGlobalMaskState(x, y, state);
    }
}
//------------------------------------------------------------------------------------------------
//слоты
void MaskWindow::slotApply()
{
    sendSigMaskState();

    // !!! - очистка массива для исключения повторной передачи сигналов (в цикле),
    //возникающей в результате ранее измененных состояний кристаллов и записанных в массив
    //(нужно для корректного счета маскированных кристаллов)
    if(!m_hashDies_XY_State.isEmpty()) m_hashDies_XY_State.clear();

    m_pcmdApply->setEnabled(false);
}
void MaskWindow::slotApplyToEnable(bool)
{
    m_pcmdApply->setEnabled(true);
}
void MaskWindow::slotMaskInsert(bool maskState)
{
    Mask state{};
    if(maskState)   state = Mask::red;
    else            state = Mask::no;

    QString XY{};
    QPushButton* pcmdToggle = qobject_cast<QPushButton*>(sender());
    if(pcmdToggle != nullptr)
    {
        XY = pcmdToggle->objectName();
        m_hashDies_XY_State.insert(XY, state);
    }
}
//------------------------------------------------------------------------------------------------
ValueFontSize MaskWindow::valuesFormat(double val, QString& strValue)
{
    double MIN_0 = 10.0, MAX_0 = 100.0;
    double MIN_1 = 0.01, MAX_1 = 1000.0;
    double MIN_2 = 1.0e-10, MAX_2 = 1.0e+10;
    double MIN_3 = 1.0e-100, MAX_3 = 1.0e+100;
    double fval = fabs(val);

    if( (fval >= MIN_0 && fval < MAX_0) || fval == 0.0 )
    {
        strValue = QString::number(val,'f',1);
        return ValueFontSize::size_1;
    }
    else if( fval >= MIN_1 && fval < MIN_0 )
    {
        strValue = QString::number(val,'f',2);
        return ValueFontSize::size_1;
    }
    else if( fval >= MAX_0 && fval < MAX_1 )
    {
        strValue = QString::number(val,'f',1);
        return ValueFontSize::size_2;
    }
    else if( (fval > MAX_1 && fval < MAX_2) || (fval < MIN_1 && fval > MIN_2) )
    {
        strValue = QString::number(val,'e',1);
        return ValueFontSize::size_3;
    }
    else if( (fval < MIN_2 && fval > MIN_3 ) || ( fval >= MAX_2 && fval < MAX_3) )
    {
        strValue = QString::number(val,'e',1);
        return ValueFontSize::size_4;
    }
    else
        strValue = QString::number(val,'e',1);

    return ValueFontSize::size_5;
}
//------------------------------------------------------------------------------------------------
void MaskWindow::setDieButtons(QVector<shared_ptr<Die> > &vec_spDies, MaskButtonType maskBtnType)
{
    m_pLabel->setVisible(false);
    //toggle buttons
    for(QPushButton* pcmdToggle : m_vec_pToggleBtns)
        pcmdToggle->setVisible(false);

    QString strX{}, strY{}, strXY{};
    vector<pair<int,int>> vecXY;
    //n - переопределение для улучшения читабельности цикла:
    int n = m_diesNumOnRadius;
    for(int i = -n; i <= n; ++i)
        for(int j = n; j >= -n; --j)
            if(abs(i) + abs(j) < (n-3)+(n-2)+1 ) //< 14
                vecXY.push_back(make_pair(i,j));

    for(pair<int,int>& pairXY : vecXY)
    {
        int i = pairXY.first; int j = pairXY.second;
        for(QPushButton* pcmdToggle : m_vec_pToggleBtns)
            for(shared_ptr<Die> spDie : vec_spDies)
                if(spDie->getX() == i && spDie->getY() == j )
                {
                    strX = QString::number(i,10);
                    strY = QString::number(j,10);
                    strXY = strX + "_" + strY;
                    //toggle buttons
                    QString strToggleBtn = pcmdToggle->objectName();
                    //маскировать по координатам (по умолчанию):
                    if(strXY == strToggleBtn)
                    {
                        pcmdToggle->setVisible(true);
                        double val = spDie->getValue();

                        QString strValue{};
                        ValueFontSize vf = valuesFormat(val, strValue);

                        //маскировать по координатам
                        if(maskBtnType == MaskButtonType::coord)
                            pcmdToggle->setToolTip(strValue);
                        //маскировать по значениям:
                        else if(maskBtnType == MaskButtonType::value)
                        {
                            pcmdToggle->setToolTip("(" + strX + "; " + strY + ")");
                            pcmdToggle->setText(strValue);

                            QFont font("Times New Roman");
                            if(vf == ValueFontSize::size_1)        font.setPointSize(12);
                            else if(vf == ValueFontSize::size_2)   font.setPointSize(11);
                            else if(vf == ValueFontSize::size_3)   font.setPointSize(9);
                            else if(vf == ValueFontSize::size_4)   font.setPointSize(7);
                            else if(vf == ValueFontSize::size_5)   font.setPointSize(6);

                            pcmdToggle->setFont(font);
                        }
                    }
                }
    }
}

void MaskWindow::setDieButtonToMaskedState(int X, int Y)
{
    QString dieXY = QString::number(X) + "_" + QString::number(Y);
    QString toggleButton{};

    for(QPushButton* pcmdToggle : m_vec_pToggleBtns)
    {
            toggleButton = pcmdToggle->objectName();
            if(dieXY == toggleButton)
                pcmdToggle->setChecked(false);
    }
}
void MaskWindow::setDieButtonToUnmaskedState(int X, int Y)
{
    QString dieXY = QString::number(X) + "_" + QString::number(Y);
    QString toggleButton{};

    for(QPushButton* pcmdToggle : m_vec_pToggleBtns)
    {
            toggleButton = pcmdToggle->objectName();
            if(dieXY == toggleButton)
                pcmdToggle->setChecked(true);
    }
}
//------------------------------------------------------------------------------------------------
