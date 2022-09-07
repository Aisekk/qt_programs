#include "TreeView.h"

TreeView::TreeView(QWidget* pwgt) : QTreeView(pwgt)
{
    m_lotNum = 0;
    m_treeWidth = 210;
    m_offset = 30;

    m_pactSetInterval = new QAction("&Динамический интервал", nullptr);
    m_pactSetInterval->setEnabled(false);
    m_pactMaskByValues = new QAction("&Маскировать по значениям", nullptr);
    m_pactMaskByCoord = new QAction("&Маскировать по координатам", nullptr);
    m_pactMaskAllDies = new QAction("&Маскировать все кристаллы", nullptr);
    m_pactUnmaskAllDies = new QAction("&Демаскировать все кристаллы", nullptr);

    m_pmnu = new QMenu(this);
    m_pmnu->addAction(m_pactSetInterval);
    m_pmnu->addAction(m_pactMaskByValues);
    m_pmnu->addAction(m_pactMaskByCoord);
    m_pmnu->addAction(m_pactMaskAllDies);
    m_pmnu->addAction(m_pactUnmaskAllDies);
    connect(m_pmnu, SIGNAL(triggered(QAction*)), SLOT(slotEmitSignals(QAction*)));
}
TreeView::~TreeView(){}
//--------------------------------------------------------------------------------------
size_t TreeView::getLotNum() const{ return m_lotNum; }
void TreeView::setLotNum(size_t lotNum)
{
    m_lotNum = lotNum;
}
void TreeView::setIntervalEnabled(bool enabled)
{
    m_pactSetInterval->setEnabled(enabled);
}

void TreeView::toHide()
{
    if(width() == 0) setFixedWidth(m_treeWidth);
    else setFixedWidth(0);
}
void TreeView::toLeft()
{
    setFixedWidth(m_treeWidth - m_offset);
    m_treeWidth = m_treeWidth - m_offset;
}
void TreeView::toRight()
{
    setFixedWidth(m_treeWidth + m_offset);
    m_treeWidth = m_treeWidth + m_offset;
}
//--------------------------------------------------------------------------------------
void TreeView::slotEmitSignals(QAction* pact)
{
    if(pact == m_pactSetInterval)
        emit interval();
    else if(pact == m_pactMaskByValues)
        emit maskTrigger(MaskButtonType::value);
    else if(pact == m_pactMaskByCoord)
        emit maskTrigger(MaskButtonType::coord);
    else if(pact == m_pactMaskAllDies)
        emit maskState(Mask::red);
    else if(pact == m_pactUnmaskAllDies)
        emit maskState(Mask::no);
}

void TreeView::contextMenuEvent(QContextMenuEvent*)
{
    emit contextMnuEvent();
    m_pmnu->exec(QCursor::pos());
}
//----------------------------------------------------------------------------------------


