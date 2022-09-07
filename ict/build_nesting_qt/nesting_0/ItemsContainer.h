#ifndef ITEMSCONTAINER_H
#define ITEMSCONTAINER_H
#include <QMultiMap>

/* инкапсулирует контейнер & с данными изделия и переопределяет итерацию по контейнеру,
 * меняя направление итерации на противоположное - для алгоритма раскроя изделия */
class ItemsContainer
{
    typedef QMap<double, QPair<double,double>>::iterator map_iterator;
public:
    ItemsContainer(QMultiMap<double, QPair<double,double>>& mmap_Square_and_ItemSizes);
    //--------------------------------------------------
    class iterator
    {
    public:
        iterator(map_iterator &it) :_it(it) {}
        bool operator == (const iterator& it)
        {
            return _it == it._it;
        }
        bool operator != (const iterator& it)
        {
            return _it != it._it;
        }
        iterator& operator ++ ()
        {
            -- _it;
            return *this;
        }
        iterator& operator -- ()
        {
            ++ _it;
            return *this;
        }
        double item_width() const
        {
            QPair<double,double> value = _it.value();
            // ширина изделия
            return std::min(value.first, value.second);
        }
        double item_height() const
        {
            QPair<double,double> value = _it.value();
            // высота изделия
            return std::max(value.first, value.second);
        }
        QPair<double,double> value() const
        {
            QPair<double,double> value = _it.value();
            // размеры изделий
            double w = std::min(value.first, value.second);
            double h = std::max(value.first, value.second);
            return QPair<double,double>(w,h);
        }
    private:
        map_iterator _it;
    };
    //--------------------------------------------------
    iterator begin() const;
    iterator end() const;
private:
    QMultiMap<double, QPair<double,double>> & m_mmap_Square_and_ItemSizes;
};

#endif // ITEMSCONTAINER_H
