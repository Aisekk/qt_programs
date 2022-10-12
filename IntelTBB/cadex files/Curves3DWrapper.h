#pragma once
#include "Forwards.h"

class Curves3DWrapper
{
    using internal_iter = CurvesLibrary::Curves3D::const_iterator;
public:
    class ConstIterator
    {
        friend class Curves3DWrapper;
    private:
        internal_iter _it;
    public:
        ConstIterator(const internal_iter& it = internal_iter())
        {
            _it = it;
        }
        ConstIterator(size_t t)
        {

        }
    public:
        ConstIterator& operator++()
        {
            ++_it;
            return *this;
        }
        bool operator==(const ConstIterator& other) const
        {
            if (_it == other._it)
                return true;
            return false;
        }
        bool operator!=(const ConstIterator& other) const
        {
            return !operator==(other);
        }
        friend bool operator< (const ConstIterator& it1, const ConstIterator& it2)
        {
            return false;
        }
        ConstIterator operator-(ConstIterator& it1) const
        {
            return ConstIterator(_it);
        }
        friend ConstIterator operator-(const ConstIterator& it1, const ConstIterator& it2)
        {
            auto it = std::distance(it1._it, it2._it); // it1._it - it2._it;
            return ConstIterator(it);
        }
        operator std::size_t() const 
        { 
            std::size_t t = 10; 
            return t; 
        }
    };

    Curves3DWrapper(const CurvesLibrary::Curves3D& curves);
    double cbegin() const;
    double cend() const;
    ConstIterator begin() const;
    ConstIterator end() const;
private:
    double GetCurveParameterValue(const CurvesLibrary::Curves3D::const_iterator& it) const;
    const CurvesLibrary::Curves3D& _curves;
};


