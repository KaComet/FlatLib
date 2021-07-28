#ifndef TILESETVIEWER_FLATMATH_H
#define TILESETVIEWER_FLATMATH_H

#include <optional>
#include <stdexcept>
#include <type_traits>
#include "FlatTypes.h"

/*
Name: Flat - Flat Math
Date: 8/9/2020 (MM/DD/YYYY)
Version: 1.01
*/

namespace flat {
    template<class T>
    requires std::is_integral_v<T> && std::is_arithmetic_v<T>
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

    bool bothCoordinatesAreWithinRadius(const IntegerCoordinate &a, const IntegerCoordinate &b, double radius);

    IntegerCoordinate makeUnit(const IntegerCoordinate &cord);

    bool cordIsUnidirectional(const IntegerCoordinate &cord);

    char getFirstNonWhitespace(const std::string &str);

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

            if ((currentIndex - currentLowerBoundInc) == 1)
                currentIndex++;
            else if (((currentUpperBoundInc - currentIndex) == 1) && (currentIndex != 0))
                currentIndex--;

            auto q = c[currentIndex] <=> d;
            // Another missed opportunity from C++20. Am I the only one that likes switch statements?
            if (q == std::strong_ordering::greater) {
                currentUpperBoundInc = currentIndex - 1;
                currentIndex = ((currentIndex - currentLowerBoundInc) / 2) + currentLowerBoundInc;
                if (currentIndex > currentUpperBoundInc)
                    currentIndex = currentUpperBoundInc;
            } else {
                if (q == std::strong_ordering::less) {
                    currentLowerBoundInc = currentIndex + 1;
                    currentIndex = ((currentUpperBoundInc - currentIndex) / 2) + currentIndex;
                    if (currentIndex < currentLowerBoundInc)
                        currentIndex = currentLowerBoundInc;
                } else {
                    return currentIndex;
                }
            }
        }

        return BINSEARCH_NOT_FOUND;
    }
}

#endif //TILESETVIEWER_FLATMATH_H
