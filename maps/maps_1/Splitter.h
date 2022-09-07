#ifndef SPLITTER_H
#define SPLITTER_H

#include <QSplitter>

class Splitter : public QSplitter
{
    Q_OBJECT
public:
    Splitter(QWidget *pwgt);
    size_t getLotNum() const;
    void setLotNum(const size_t lotNum);
private:
    size_t m_lotNum{};
};

#endif // SPLITTER_H
