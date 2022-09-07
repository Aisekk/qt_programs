#ifndef MASKWINDOW_H
#define MASKWINDOW_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

#include <vector>
#include <memory>
using namespace std;

#include "LotGroup/Die.h"
#include "Types.h"

class MaskWindow : public QDialog
{
    Q_OBJECT
public:
    MaskWindow(QWidget *pwgt = nullptr);
    virtual ~MaskWindow();

    ValueFontSize valuesFormat(double val, QString &strValue);

    void setDieButtons(QVector<shared_ptr<Die>> vec_spDies, MaskButtonType maskBtnType);
    void setDieButtonToMaskedState(const int X, const int Y);
    void setDieButtonToUnmaskedState(const int X, const int Y);
public slots:
    void slotApply();
    void slotApplyToEnable(bool);
signals:
    void sigGlobalMaskState(const int, const int, const Mask);
//-------------------------------------------------------------------------------------------------
protected:
    virtual void sendSigMaskState();
protected:
    int m_diesNumMaxAlongRadiusNoCenter;
    int m_diesNumOnRadius;
    QVBoxLayout *m_pvbxMainLayout;
    QGridLayout *m_pgrdLayout;
    QHBoxLayout *m_phbxLayout;

    QLabel *m_pLabel;
    QPushButton* m_pcmdApply;

    //toggle buttons
    int m_size;
    QVector<QPushButton*> m_vec_pToggleBtns;
    QHash<QString,Mask> m_hashDies_XY_State;

protected slots:
    void slotMaskInsert(bool maskState);
};
#endif // MASKWINDOW_H
