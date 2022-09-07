#ifndef PROGRESS_H
#define PROGRESS_H

#include <QDialog>
#include <QProgressBar>
#include <QCloseEvent>
//=================================================================================================
class Progress : public QDialog
{
    Q_OBJECT
public:
    Progress(QWidget* pwgt = nullptr, size_t count = 0);
    virtual ~Progress();
    void setStep(size_t step);
    bool isStopped() const;
    void setStopButtonVisible();
public slots:
    void slotStep(size_t step);
protected:
    void closeEvent(QCloseEvent* pe) override;
    QProgressBar *m_pprb{};
    QPushButton *m_pStopButton{};
    size_t m_count{};
signals:
    void stopped(bool);
    void closed();
};
//=================================================================================================
#endif // PROGRESS_H
