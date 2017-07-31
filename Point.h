/**
 * @file Point.h
 * @author Itai Tagar <itagar>
 * @version 1.2
 * @date 04 Sep 2016
 *
 * @brief A Header File for the Point Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Header File for the Point Class.
 * Declaring the Point Class, it's methods and fields.
 * A Point class is a single Point with X and Y coordinates in the plane.
 */


#ifndef EX1_POINT_H
#define EX1_POINT_H


/*-----=  Includes  =-----*/


#include <string>


/*-----=  Definitions  =-----*/


/**
 * @def COORDINATES_SEPARATOR ","
 * @brief A Macro that sets the output for the separator between the Point's coordinates.
 */
#define COORDINATES_SEPARATOR ","


/*-----=  Class Declaration  =-----*/


/**
 * @brief A Class representing a single Point with X and Y coordinates.
 *        The Point holds it's coordinates in the plane, and several methods that operates these
 *        coordinates.
 */
class Point
{
public:

    /**
     * @brief A Default Constructor for the Point, which create a new Point in the plane with
     *        the default coordinates.
     */
    Point();

    /**
     * @brief A Constructor for the Point, which receive 2 coordinates and create a new Point in the
     *        plane with the given coordinates.
     * @param x The X coordinate in the plane.
     * @param y The Y coordinate in the plane.
     */
    Point(int const x, int const y);

    /**
     * @brief A Destructor for the Point.
     */
    ~Point();

    /**
     * @brief Returns the X coordinate value.
     * @return The X coordinate value.
     */
    int getX() const { return _x; };

    /**
     * @brief Returns the Y coordinate value.
     * @return The Y coordinate value.
     */
    int getY() const { return _y; };

    /**
     * @brief Sets the Point's coordinates to the given new values.
     * @param x The new X coordinate to set.
     * @param y The new Y coordinate to set.
     */
    void set(int const x, int const y);

    /**
     * @brief Represent the Point as a string for output use.
     * @return A string representation of the Point.
     */
    std::string toString() const;

    /**
     * @brief Calculates the Polar Angle of this Point with respect to another given Point.
     * @param other The Point to calculate the Angle with.
     * @return The Polar Angle of the Points.
     */
    double polarAngle(const Point& other) const;

    /**
     * @brief Calculates the distance of this Point with respect to another given Point.
     * @param other The Point to calculate the distance with.
     * @return The distance of the Points.
     */
    double distance(const Point& other) const;

    /**
     * @brief An operator overload for the comparison operator '==' which compares
     *        this Point with another given Point.
     * @param other A reference for the Point to compare to.
     * @return true if both the X coordinates and the Y coordinates are equal.
     */
    bool operator==(const Point& other) const;

private:
    // Point Private Fields.
    int _x;  // The X coordinate value for the Point.
    int _y;  // The Y coordinate value for the Point.
};


#endif //EX1_POINT_H
