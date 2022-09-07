#include <QPushButton>
#include <QHBoxLayout>
#include "Progress.h"
#include <QTimer>

//=================================================================================================
Progress::Progress(QWidget* pwgt, size_t count) :
    QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    m_count(count)
{
    setModal(true);
    setWindowTitle("Запись на диск ...");
    setBaseSize(QWidget::sizeHint());

    m_pprb = new QProgressBar;
    m_pprb->setRange(0, m_count);
    m_pprb->setMinimumWidth(250);

    m_pStopButton = new QPushButton;
    m_pStopButton->setText("Стоп");
    m_pStopButton->setVisible(false);
    connect(m_pStopButton, QPushButton::clicked, this, close);

    QHBoxLayout* phbxLayout = new QHBoxLayout;
    phbxLayout->addStretch(1);
    phbxLayout->addWidget(m_pStopButton);

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(m_pprb);
    pvbxLayout->addLayout(phbxLayout);
    setLayout(pvbxLayout);
}
Progress::~Progress(){}
//-------------------------------------------------------------------------------------------------
void Progress::setStep(size_t step){ m_pprb->setValue(step); }
void Progress::slotStep(size_t step){ m_pprb->setValue(step); }

bool Progress::isStopped() const{ if(m_pStopButton->isDown()) return true; return false; }
void Progress::setStopButtonVisible(){ m_pStopButton->setVisible(true); }
void Progress::closeEvent(QCloseEvent *pe)
{
    emit closed();
    emit stopped(true);
    pe->accept();
}
//-------------------------------------------------------------------------------------------------
