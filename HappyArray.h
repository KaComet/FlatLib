#ifndef FLAT_HAPPYARRAY_H
#define FLAT_HAPPYARRAY_H

#include <stdexcept>
#include <type_traits>

/*
Name: Flat - Happy Array
Date: 6/22/2021 (MM/DD/YYYY)
Version: 1.03
*/

namespace flat {
    template<class T> requires std::is_default_constructible_v<T>
    class HappyArray {
    public:
        HappyArray();

        HappyArray(std::initializer_list<T> list);

        explicit HappyArray(unsigned long int size);

        ~HappyArray();

        HappyArray(const HappyArray &);

        [[nodiscard]] std::size_t size() const noexcept;

        void fill(const T &fillValue) noexcept;

        T &operator[](size_t index) const;

        HappyArray<T> &operator=(const HappyArray<T> &other);

    private:
        T *_arrayPtr;
        std::size_t _nElements;
    };

    template<class T> requires std::is_default_constructible_v<T>
    HappyArray<T>::HappyArray() {
        _nElements = 0;
        _arrayPtr = nullptr;
    }

    template<class T> requires std::is_default_constructible_v<T>
    HappyArray<T>::HappyArray(std::initializer_list<T> list) : HappyArray(list.size()) {
        auto it = list.begin();
        std::size_t i = 0;
        for (const T& t : list)
            _arrayPtr[i++] = t;
    }

    template<class T> requires std::is_default_constructible_v<T>
    HappyArray<T>::HappyArray(const unsigned long int size) {
        _nElements = size;
        if (_nElements != 0)
            _arrayPtr = new T[_nElements];
        else
            _arrayPtr = nullptr;
    }

    template<class T> requires std::is_default_constructible_v<T>
    HappyArray<T>::HappyArray(const HappyArray &other) {
        _nElements = other._nElements;
        _arrayPtr = new T[_nElements];
        for (unsigned int i = 0; i < _nElements; i++)
            _arrayPtr[i] = other._arrayPtr[i];
    }

    template<class T> requires std::is_default_constructible_v<T>
    HappyArray<T>::~HappyArray() {
        delete[] _arrayPtr;
    }

    template<class T> requires std::is_default_constructible_v<T>
    std::size_t HappyArray<T>::size() const noexcept {
        return _nElements;
    }

    template<class T> requires std::is_default_constructible_v<T>
    void HappyArray<T>::fill(const T &fillValue) noexcept {
        for (size_t i = 0; i < _nElements; i++)
            _arrayPtr[i] = fillValue;
    }

    template<class T> requires std::is_default_constructible_v<T>
    T &HappyArray<T>::operator[](const size_t index) const {
        if ((index >= _nElements) || !_arrayPtr)
            throw std::out_of_range("");

        return _arrayPtr[index];
    }

    template<class T> requires std::is_default_constructible_v<T>
    HappyArray<T> &HappyArray<T>::operator=(const HappyArray<T> &other) {
        if (this != &other) {
            delete[] _arrayPtr;
            _nElements = other._nElements;
            _arrayPtr = new T[_nElements];
            for (unsigned int i = 0; i < _nElements; i++)
                _arrayPtr[i] = other._arrayPtr[i];
        }

        return *this;
    }
}

#endif //FLAT_HAPPYARRAY_H
