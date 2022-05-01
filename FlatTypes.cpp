#include "FlatTypes.h"
#include "FlatMath.h"


/*
 * Coordinate functions
 */
flat::IntegerCoordinate::IntegerCoordinate(int_fast64_t x, int_fast64_t y) : x(x), y(y) {

}

bool flat::IntegerCoordinate::operator==(const IntegerCoordinate &b) const noexcept {
    return (y == b.y) && (x == b.x);
}

flat::IntegerCoordinate flat::IntegerCoordinate::operator-(const IntegerCoordinate &b) const noexcept {
    return IntegerCoordinate(x - b.x, y - b.y);
}

flat::IntegerCoordinate flat::IntegerCoordinate::operator+(const IntegerCoordinate &b) const noexcept {
    return IntegerCoordinate(x + b.x, y + b.y);
}

flat::IntegerCoordinate &flat::IntegerCoordinate::operator-=(const IntegerCoordinate &b) noexcept {
    x -= b.x;
    y -= b.y;
    return *this;
}

std::string flat::IntegerCoordinate::toString(flat::IntegerCoordinate position) {
    return (std::string) ('(' + std::to_string(position.x) + ',' +
                          std::to_string(position.y) + ')');
}


/*
 * Rectangle functions
 */
flat::Rectangle::Rectangle(int_fast32_t width, int_fast32_t height) : width(width), height(height) {
    if (height < 0)
        height = 0;

    if (width < 0)
        width = 0;
}

bool flat::Rectangle::operator==(const Rectangle &b) const noexcept {
    return (width == b.width) && (height == b.height);
}

[[nodiscard]] bool flat::Rectangle::contains(const IntegerCoordinate &cord) const noexcept {
    return (cord.x < width) && (cord.y < height);
}

std::string flat::Rectangle::toString(Rectangle rect) {
    return (std::string) ('[' + std::to_string(rect.width) + ',' +
                          std::to_string(rect.height) + ']');
}


/*
 * CoordinateAndRectangle functions
 */
flat::CoordinateAndRectangle::CoordinateAndRectangle(int_fast32_t x, int_fast32_t y, int_fast32_t width,
                                                     int_fast32_t height) : x(x), y(y), width(width), height(height) {
    if (height < 0)
        height = 0;

    if (width < 0)
        width = 0;
}

flat::CoordinateAndRectangle::CoordinateAndRectangle(const flat::IntegerCoordinate &cord, flat::Rectangle rect) : x(
        cord.x),
                                                                                                                  y(cord.y),
                                                                                                                  width(rect.width),
                                                                                                                  height(rect.height) {

}

bool flat::CoordinateAndRectangle::operator==(const CoordinateAndRectangle &b) const noexcept {
    return (x == b.x) && (y == b.y) && (width == b.width) && (height == b.height);
}

std::string flat::CoordinateAndRectangle::toString(flat::CoordinateAndRectangle rect) {
    return (std::string) ("{[" + std::to_string(rect.width) + ',' +
                          std::to_string(rect.height) + "](" +
                          std::to_string(rect.x) + ',' +
                          std::to_string(rect.y)) + ")}";
}

bool flat::CoordinateAndRectangle::overlaps(const flat::CoordinateAndRectangle &a,
                                            const flat::CoordinateAndRectangle &b) noexcept {
    if (a.x > (b.x + b.width) || (a.x + a.width) > b.x)
        return false;
    if (a.y < (b.y + b.height) || (a.y + a.height) < b.y)
        return false;
    return true;
}

bool flat::CoordinateAndRectangle::containtsPoint(const flat::CoordinateAndRectangle &a,
                                                  const flat::IntegerCoordinate &p) noexcept {
    return (a.x <= p.x) && (a.y <= p.y) && ((a.x + a.width) >= p.x) && ((a.y + a.height) >= p.y);
}

flat::CoordinateAndRectangle flat::CoordinateAndRectangle::overlap(const flat::CoordinateAndRectangle &a,
                                                                   const flat::CoordinateAndRectangle &b) noexcept {
    if (!overlaps(a, b))
        flat::CoordinateAndRectangle(0, 0, 0, 0);
    CoordinateAndRectangle result;
    result.x = a.x > b.x ? a.x : b.x;
    result.y = a.y > b.y ? a.y : b.y;
    result.width = a.x + a.width < b.x + b.width ? a.x + a.width : b.x + b.width;
    result.height = a.y + a.height < b.y + b.height ? a.y + a.height : b.y + b.height;
    result.height -= result.x;
    result.width -= result.y;

    return result;
}
