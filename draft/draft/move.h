#ifndef MOVE_H
#define MOVE_H

#include <QUrl>
#include <QUrlQuery>
#include <QDebug>

namespace Move {

class UrlBuilder final : public QUrl, public QUrlQuery {
public:
    explicit UrlBuilder();
    UrlBuilder& operator=(UrlBuilder &&) {
        qDebug() << "UrlBuilder& operator=(const UrlBuilder &other)";
        return *this;
    }
};

class A {
public:
    void setUrl(UrlBuilder &&url) {
        this->url = std::move(url);
        //this->url = url;
    }
private:
    UrlBuilder url;
};



void func() {

}

}
#endif // MOVE_H
