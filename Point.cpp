/**
 * @file Point.cpp
 * @author Itai Tagar <itagar>
 * @version 1.7
 * @date 04 Sep 2016
 *
 * @brief A File for the Point Class implementation.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A File for the Point Class implementation.
 * Define the Point Class methods and fields.
 * A Point class is a single Point with X and Y coordinates in the plane.
 */


/*-----=  Includes  =-----*/


#include <cmath>
#include "Point.h"


/*-----=  Definitions  =-----*/


/**
 * @def DEFAULT_COORDINATE_VALUE 0
 * @brief A Macro that sets the default value for a Point's coordinate.
 */
#define DEFAULT_COORDINATE_VALUE 0

/**
 * @def PI 3.14
 * @brief A Macro that sets the value of the number Pi.
 */
#define PI 3.141592

/**
 * @def ANGLE_FACTOR 180
 * @brief A Macro that sets the value for the factor calculating the Polar Angle.
 */
#define ANGLE_FACTOR 180


/*-----=  Point Constructors & Destructors  =-----*/


/**
 * @brief A Default Constructor for the Point, which create a new Point in the plane with
 *        the default coordinates.
 */
Point::Point()
{
    _x = DEFAULT_COORDINATE_VALUE;
    _y = DEFAULT_COORDINATE_VALUE;
}

/**
 * @brief A Constructor for the Point, which receive 2 coordinates and create a new Point in the
 *        plane with the given coordinates.
 * @param x The X coordinate in the plane.
 * @param y The Y coordinate in the plane.
 */
Point::Point(int const x, int const y)
{
    _x = x;
    _y = y;
}

/**
 * @brief A Destructor for the Point.
 */
Point::~Point()
{

}


/*-----=  Getters/Setters  =-----*/


/**
 * @brief Sets the Point's coordinates to the given new values.
 * @param x The new X coordinate to set.
 * @param y The new Y coordinate to set.
 */
void Point::set(int const x, int const y)
{
    _x = x;
    _y = y;
}


/*-----=  Point Misc. Methods  =-----*/


/**
 * @brief Represent the Point as a string for output use.
 * @return A string representation of the Point.
 */
std::string Point::toString() const
{
    return std::to_string(getX()) + COORDINATES_SEPARATOR + std::to_string(getY());
}

/**
 * @brief Calculates the Polar Angle of this Point with respect to another given Point.
 * @param other The Point to calculate the Angle with.
 * @return The Polar Angle of the Points.
 */
double Point::polarAngle(const Point& other) const
{
    double deltaX = this -> getX() - other.getX();
    double deltaY = this -> getY() - other.getY();
    return atan2(deltaY, deltaX) * ANGLE_FACTOR / PI;
}

/**
 * @brief Calculates the distance of this Point with respect to another given Point.
 * @param other The Point to calculate the distance with.
 * @return The distance of the Points.
 */
double Point::distance(const Point &other) const
{
    double deltaX = this -> getX() - other.getX();
    double deltaY = this -> getY() - other.getY();
    return sqrt(deltaX*deltaX + deltaY*deltaY);
}


/*-----=  Point Operators Overload  =-----*/


/**
 * @brief An operator overload for the comparison operator '==' which compares
 *        this Point with another given Point.
 * @param other A reference for the Point to compare to.
 * @return true if both the X coordinates and the Y coordinates are equal.
 */
bool Point::operator==(const Point& other) const
{
    return (this -> getX() == other.getX()) && (this -> getY() == other.getY());
}
