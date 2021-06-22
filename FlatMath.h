#ifndef TILESETVIEWER_FLATMATH_H
#define TILESETVIEWER_FLATMATH_H

#include <optional>
#include <stdexcept>
#include "FlatTypes.h"

/*
Name: Flat - Flat Math
Date: 8/9/2020 (MM/DD/YYYY)
Version: 1.01
*/

namespace flat {
    template<class T>
    T nonWrappingSubtraction(const T &a, const T &b) {
        if (b > a)
            return T(0);
        else
            return a - b;
    }

    template<class T>
    T atLeast(const T &a, const T &b) {
        if (a < b)
            return b;
        else
            return a;
    }

    template<class T>
    void ensureValue(std::optional<T> &input, std::optional<T> defaultValue) {
        if (input.has_value())
            return;
        else if (defaultValue.has_value()) {
            input = std::optional<T>(defaultValue);
            return;
        } else
            throw std::runtime_error("");
    }

    // Returns true if the coordinate is within the provided CoordinateAndRectangle.
    bool isInBound(const IntegerCoordinate &coordinate, const CoordinateAndRectangle &coordinateAndRectangle);

    IntegerCoordinate makeUnit(const IntegerCoordinate &cord);

    bool cordIsUnidirectional(const IntegerCoordinate &cord);

    const std::size_t BINSEARCH_NOT_FOUND = -1;

    template<class D, class C>
    std::size_t binarySearch(std::size_t startInc, std::size_t endInc, C &c, D &d) {
        if (startInc > endInc)
            return BINSEARCH_NOT_FOUND;

        std::size_t currentIndex = ((endInc - startInc) / 2) + startInc;
        std::size_t currentUpperBoundInc = endInc;
        std::size_t currentLowerBoundInc = startInc;
        std::size_t lastIndex = -1;

        while (currentIndex != lastIndex) {
            lastIndex = currentIndex;
            auto q = c[currentIndex] <=> d;
            // Another missed opportunity from C++20. Am I the only one that likes switch statements?
            if (q == std::strong_ordering::greater) {
                currentUpperBoundInc = currentIndex;
                currentIndex = ((currentIndex - currentLowerBoundInc) / 2) + currentLowerBoundInc;
            } else {
                if (q == std::strong_ordering::less) {
                    currentLowerBoundInc = currentIndex;
                    currentIndex = ((currentUpperBoundInc - currentIndex) / 2) + currentIndex;
                } else {
                    return currentIndex;
                }
            }

        }

        return BINSEARCH_NOT_FOUND;
    }
}

#endif //TILESETVIEWER_FLATMATH_H
