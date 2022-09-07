#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QMenu>
#include <QTreeView>
#include <QEvent>
#include <QStandardItemModel>

#include <Types.h>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget* pwgt = nullptr);
    virtual ~TreeView();

    size_t getLotNum() const;
    void setLotNum(size_t lotNum);
    void setIntervalEnabled(bool enabled);

    void toHide();
    void toLeft();
    void toRight();

signals:
    void interval();
    void maskTrigger(MaskButtonType);
    void maskState(Mask);
    void contextMnuEvent();

public slots:
    void slotEmitSignals(QAction* pact);

protected:
    void contextMenuEvent(QContextMenuEvent*) override;

private:
    size_t m_treeWidth;
    size_t m_offset;
    size_t m_lotNum;
    QMenu *m_pmnu;

    QAction *m_pactSetInterval;
    QAction *m_pactMaskByValues;
    QAction *m_pactMaskByCoord;
    QAction *m_pactMaskAllDies;
    QAction *m_pactUnmaskAllDies;
};
//======================================================================================
#endif // TREEVIEW_H
