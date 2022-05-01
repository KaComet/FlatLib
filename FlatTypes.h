#ifndef TILESETVIEWER_FLATTYPES_H
#define TILESETVIEWER_FLATTYPES_H

#include <cstdint>
#include <string>

namespace flat {
    struct IntegerCoordinate {
        explicit IntegerCoordinate(int_fast32_t x = 0, int_fast32_t y = 0);

        bool operator==(const IntegerCoordinate &b) const noexcept;

        IntegerCoordinate operator-(const IntegerCoordinate &b) const noexcept;

        IntegerCoordinate operator+(const IntegerCoordinate &b) const noexcept;

        IntegerCoordinate &operator-=(const IntegerCoordinate &b) noexcept;

        static std::string toString(IntegerCoordinate position);

        typedef int_fast32_t DATA_TYPE;

        int_fast32_t x, y;
    };

    struct Rectangle {
        explicit Rectangle(int_fast32_t width = 0, int_fast32_t height = 0);

        // Returns true if both of the Rectangles are identical.
        bool operator==(const Rectangle &b) const noexcept;

        Rectangle &operator=(const Rectangle &other) = default;

        [[nodiscard]] bool contains(const IntegerCoordinate &cord) const noexcept;

        static std::string toString(Rectangle rect);

        uint_fast32_t width, height;
    };

    struct CoordinateAndRectangle {
        explicit CoordinateAndRectangle(int_fast32_t x = 0, int_fast32_t y = 0, int_fast32_t width = 0,
                                        int_fast32_t height = 0);

        explicit CoordinateAndRectangle(const IntegerCoordinate &cord, Rectangle rect);

        // If the two CoordinateAndRectangle are identical, returns true.
        bool operator==(const CoordinateAndRectangle &b) const noexcept;

        static std::string toString(CoordinateAndRectangle rect);

        // Returns true if the provided CoordinateAndRectangles overlap.
        static bool overlaps(const CoordinateAndRectangle &a, const CoordinateAndRectangle &b) noexcept;

        // Returns true if the CoordinateAndRectangle contains the point.
        static bool containtsPoint(const CoordinateAndRectangle &a, const IntegerCoordinate &p) noexcept;

        // Returns the area where two CoordinateAndRectangles overlap. Returns CoordinateAndRectangle(0,0,0,0)
        //   if they don't overlap.
        static CoordinateAndRectangle overlap(const CoordinateAndRectangle &a,
                                              const CoordinateAndRectangle &b) noexcept;

        int_fast32_t x, y;
        int_fast32_t width, height;
    };

    // A shorthand for CoordinateAndRectangle.
    typedef CoordinateAndRectangle CaR;
}

#endif //TILESETVIEWER_FLATTYPES_H