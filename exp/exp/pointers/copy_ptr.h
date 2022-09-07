#ifndef COPY_PTR_H
#define COPY_PTR_H

template <class T> inline T *new_clone(const T &rcT)
{
    return new T(rcT);
}
template <class T> inline void delete_clone(const T *pcT)
{
    delete pcT;
}

#define DECLARE_CLONEABLE_BASE(thisClass) \
    protected: \
    thisClass(const thisClass &) {} \
    thisClass &operator = (const thisClass &) {} \
    virtual thisClass *do_clone() const = 0; \
    public: \
    thisClass() {} \
    virtual ~thisClass() {} \
    thisClass *clone() const { return do_clone(); }

#define DECLARE_CLONEABLE(thisClass) \
    protected: \
    virtual thisClass *do_clone() const \
{ \
    return new thisClass(*this); \
    }

class Base
{
    DECLARE_CLONEABLE_BASE(Base)
    //
    // protected:
    // Base(const Base &) { }
    // Base &operator = (const Base &) { }
    // virtual Base *do_clone() const = 0;
    // public:
    // Base() { }
    // virtual ~Base() { }
    // Base *clone() const { return do_clone(); }
    // ...
    Base *new_clone(const Base &rcBase)
    {
        return rcBase.clone();
    }
};

class Derived1 : public Base
{
    DECLARE_CLONEABLE(Derived1)
    //
    // protected:
    // virtual Derived1 *do_clone() const
    // {
    // return new Derived1(*this);
    // }
    // ...
};

// указатель с глубоким копированием
template <class T> class copy_ptr
{
private:
    T *m_pT;
public:
    // ...
    copy_ptr(const copy_ptr &rPtr)
        : m_pT(new_clone(*rPtr.m_pT))
    { }
    copy_ptr &operator = (const copy_ptr &rPtr)
    { /* ... */ }
};

#endif // COPY_PTR_H
