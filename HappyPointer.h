#ifndef FLAT_HAPPYPOINTER_H
#define FLAT_HAPPYPOINTER_H

#include <stdexcept>

/*
Name: Flat - Happy Pointer
Date: 5/25/2021 (MM/DD/YYYY)
Version: 1.01
*/

namespace flat {
    template<class T>
    class HappyPointer {
    public:
        HappyPointer();

        HappyPointer(T);

        ~HappyPointer();

        HappyPointer(const HappyPointer &);

        T &operator->() const;

        HappyPointer<T> &operator=(const HappyPointer<T> &other);

        [[nodiscard]] T *IAcceptTheRiskOfUsingThisRawPointer() const noexcept;

        [[nodiscard]] bool isNull() const noexcept;

    private:
        T *_Ptr;
    };

    template<class T>
    HappyPointer<T>::HappyPointer() {
        _Ptr = nullptr;
    }

    template<class T>
    HappyPointer<T>::HappyPointer(T t) {
        _Ptr = new T;
        *_Ptr = t;
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
            if (_Ptr == nullptr) {
                _Ptr = new T(*other._Ptr);
            } else {
                *_Ptr = *other._Ptr;
            }
        }

        return *this;
    }

    template<class T>
    [[nodiscard]] T *HappyPointer<T>::IAcceptTheRiskOfUsingThisRawPointer() const {
        return _arrayPtr;
    }

    template<class T>
    [[nodiscard]] bool HappyPointer<T>::isNull() const noexcept {
        return _Ptr == nullptr;
    }
}

#endif //FLAT_HAPPYPOINTER_H
