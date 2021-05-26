#ifndef FLAT_HAPPYPOINTER_H
#define FLAT_HAPPYPOINTER_H

#include <stdexcept>

/*
Name: Flat - Happy Pointer
Date: 5/25/2021 (MM/DD/YYYY)
Version: 1.00
*/

namespace flat {
    template<class T>
    class HappyPointer {
    public:
        HappyPointer();

        ~HappyPointer();

        HappyPointer(const HappyPointer &);

        T &operator->() const;

        HappyPointer<T> &operator=(const HappyPointer<T> &other);

        [[nodiscard]] T *IAcceptTheRiskOfUsingThisRawPointer() const;

    private:
        T *_Ptr;
    };

    template<class T>
    HappyPointer<T>::HappyPointer() {
        _Ptr = new T;
    }

    template<class T>
    HappyPointer<T>::HappyPointer(const HappyPointer &other) {
        _Ptr = new T;
        *_Ptr = *other._Ptr;
    }

    template<class T>
    HappyPointer<T>::~HappyPointer() {
        delete _Ptr;
    }

    template<class T>
    T &HappyPointer<T>::operator->() const {
        return &_Ptr;
    }

    template<class T>
    HappyPointer<T> &HappyPointer<T>::operator=(const HappyPointer<T> &other) {
        if (this != &other) {
            delete _Ptr;
            *_Ptr = *other._Ptr;
        }

        return *this;
    }

    template<class T>
    [[nodiscard]] T *HappyPointer<T>::IAcceptTheRiskOfUsingThisRawPointer() const {
        return _arrayPtr;
    }
}

#endif //FLAT_HAPPYPOINTER_H
