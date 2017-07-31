/**
 * @file PointSet.cpp
 * @author Itai Tagar <itagar>
 * @version 2.5
 * @date 04 Sep 2016
 *
 * @brief A File for the PointSet Class implementation.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A File for the PointSet Class implementation.
 * Define the PointSet Class methods and fields.
 * A PointSet class is a Set which holds Points and allows several operations associated with a Set.
 */


/*-----=  Includes  =-----*/


#include <algorithm>
#include <cassert>
#include "PointSet.h"


/*-----=  Definitions  =-----*/


/**
 * @def EMPTY_SET_SIZE 0
 * @brief A Macro that sets the size for an empty PointSet.
 */
#define EMPTY_SET_SIZE 0

/**
 * @def MINIMUM_INDEX 0
 * @brief A Macro that sets the index for the minimum value in the Set after sort operation.
 */
#define MINIMUM_INDEX 0

/**
 * @def INITIAL_CAPACITY 10
 * @brief A Macro that sets the initial capacity for the PointSet.
 */
#define INITIAL_CAPACITY 1

/**
 * @def RESIZE_FACTOR 2
 * @brief A Macro that sets the number for the capacity resize factor.
 */
#define RESIZE_FACTOR 2

/**
 * @def INVALID_INDEX -1
 * @brief A Macro that sets an invalid index in the PointSet.
 */
#define INVALID_INDEX -1

/**
 * @def EMPTY_SET_OUTPUT ""
 * @brief A Macro that sets the output for the PointSet in case the Set is empty.
 */
#define EMPTY_SET_OUTPUT ""

/**
 * @def END_OF_POINT_OUTPUT "\n"
 * @brief A Macro that sets the output for the end of a single Point output representation.
 */
#define END_OF_POINT_OUTPUT "\n"


/*-----=  Global Variables  =-----*/


/**
 * @brief A pointer for the Point which will be the Axis Point during the Polar Angle Sort.
 */
static PointP gAxisPoint;


/*-----=  PointSet Constructors & Destructors  =-----*/


/**
 * @brief A Default Constructor for the PointSet, which create a new PointSet ready to store Points.
 */
PointSet::PointSet()
{
    _size = EMPTY_SET_SIZE;
    _capacity = INITIAL_CAPACITY;
    _pointSet = new PointP[_capacity];
}

/**
 * @brief A Copy Constructor for the PointSet, which create a new PointSet ready to store Points
 *        from a given PointSet data.
 * @param other The PointSet to copy.
 */
PointSet::PointSet(const PointSet& other)
{
    _size = EMPTY_SET_SIZE;  // Note that '_size' will be updated by the 'add()' method.
    this -> _capacity = other._capacity;
    this -> _pointSet = new PointP[_capacity];

    // Deep-Copy each element in the given PointSet.
    for (int i = 0; i < other.size(); i++)
    {
        this -> add(*(other._pointSet[i]));
    }
    _initializeSet(_size, _capacity);
}

/**
 * @brief A Destructor for the PointSet.
 */
PointSet::~PointSet()
{
    for (int i = 0; i < _size; i++)
    {
        delete _pointSet[i];
    }
    delete[] _pointSet;
}


/*-----=  PointSet Misc. Methods  =-----*/


/**
 * @brief Initialize the PointSet container with NULL Pointers in the given range.
 * @param startIndex The index to start initialize the PointP cells. (inclusive).
 * @param endIndex The index to end initialize the PointP cells. (exclusive).
 */
void PointSet::_initializeSet(int const startIndex, int const endIndex)
{
    assert(startIndex >= EMPTY_SET_SIZE && endIndex <= _capacity);
    for (int i = startIndex; i < endIndex; i++)
    {
        _pointSet[i] = nullptr;
    }
}

/**
 * @brief Finds the given Point in the PointSet if exists and return it's index in the Set.
 *        If the given Point does not exist, returns INVALID_INDEX.
 * @param point The Point to find.
 * @return The index of the Point in the Set if exists, otherwise return INVALID_INDEX.
 */
int PointSet::_findPoint(const Point& point) const
{
    for (int i = 0; i < _size; i++)
    {
        if (*(_pointSet[i]) == point)
        {
            return i;
        }
    }
    return INVALID_INDEX;
}

/**
 * @brief Represent the PointSet as a string for output use.
 * @return A string representation of the PointSet.
 */
std::string PointSet::toString() const
{
    std::string result = EMPTY_SET_OUTPUT;
    for (int i = 0; i < _size; i++)
    {
        result += (_pointSet[i]) -> toString() + END_OF_POINT_OUTPUT;
    }
    return result;
}

/**
 * @brief Swap data between the 2 given PointSets.
 * @param pointSet1 The first PointSet to swap.
 * @param pointSet2 The second PointSet to swap.
 */
void PointSet::_swapData(PointSet& pointSet1, PointSet& pointSet2)
{
    PointP *tempSet = pointSet1._pointSet;
    pointSet1._pointSet = pointSet2._pointSet;
    pointSet2._pointSet = tempSet;

    int tempSize = pointSet1._size;
    pointSet1._size = pointSet2._size;
    pointSet2._size = tempSize;

    int tempCapacity = pointSet1._capacity;
    pointSet1._capacity = pointSet2._capacity;
    pointSet2._capacity = tempCapacity;
}


/*-----=  PointSet Addition  =-----*/


/**
 * @brief Adds a given Point to the PointSet.
 *        The new Point will be inserted to the end of the PointSet.
 *        If the Point is already in the Set, this method will do nothing.
 * @param point The new Point to insert.
 * @return true if the insertion succeed, false otherwise.
 */
bool PointSet::add(const Point& point)
{
    // Check if the new Point to add is already exists in the PointSet.
    if (_findPoint(point) != INVALID_INDEX)
    {
        return false;
    }

    // Validate the capacity of the PointSet for inserting a new Point.
    if (_size == (_capacity - 1))
    {
        _resizePointSet();
    }

    // Allocate place for the new Point.
    _pointSet[_size] = new Point;

    // Update the PointSet.
    *(_pointSet[_size]) = point;
    _size++;

    return true;
}

/**
 * @brief Resize the PointSet capacity.
 *        The Resize operation allocates memory for the new capacity, and copies all the data
 *        from the current Set to the new larger Set.
 */
void PointSet::_resizePointSet()
{
    // Allocate the new PointSet.
    PointP *newPointSet = nullptr;
    newPointSet = new PointP[_capacity * RESIZE_FACTOR];

    PointP *oldPointSet = _pointSet;

    // Copy the data from the current Set to the new Set.
    for (int i = 0; i < _size; i++)
    {
        newPointSet[i] = oldPointSet[i];
    }

    delete[] oldPointSet;

    // Update the PointSet data.
    _pointSet = newPointSet;
    _capacity *= RESIZE_FACTOR;
    _initializeSet(_size, _capacity);  // Initialize all the new cells.
}


/*-----=  PointSet Deletion  =-----*/


/**
 * @brief Trims a gap in the PointSet which can occur during the removal operation.
 *        This method sets each PointP cell in the Set to point to the following cell, starting
 *        from the given index.
 * @param gapIndex The index to start the trimming process from.
 */
void PointSet::_trimGap(int const gapIndex)
{
    assert(gapIndex >= EMPTY_SET_SIZE && gapIndex < _size);
    for (int i = gapIndex; i < (_size - 1); i++)
    {
        _pointSet[i] = _pointSet[i + 1];
    }
    _pointSet[_size - 1] = nullptr;
}

/**
 * @brief Removes a given Point from the PointSet if exists, and updates the PointSet accordingly.
 *        If the Point does not exist in the Set, this method will do nothing.
 * @param point The Point to remove.
 * @return true if the removal succeed, false otherwise.
 */
bool PointSet::remove(const Point& point)
{
    // Find the desired Point in the PointSet.
    int pointIndex = _findPoint(point);
    if (pointIndex != INVALID_INDEX)
    {
        PointP toDelete = _pointSet[pointIndex];

        // Trim the gap in the PointSet where the Point to remove appears.
        _trimGap(pointIndex);

        // Update the PointSet.
        delete toDelete;
        _size--;

        return true;
    }
    return false;
}


/*-----=  PointSet Sorting  =-----*/


/**
 * @brief A comparator function used for sorting Points in the PointSet.
 *        This comparator compares 2 Points by their Y coordinate value.
 *        If the 2 Points comparison turn to be equal, we will compare by their X coordinate value.
 * @param point1 A pointer to the first Point to compare.
 * @param point2 A pointer to the second Point to compare.
 * @return true if the first Point is smaller then the second Point.
 */
static bool yComparator(const PointP point1, const PointP point2)
{
    return ((point1 -> getY()) < (point2 -> getY())) ||
            ((point1 -> getY()) == (point2 -> getY()) && (point1 -> getX()) < (point2 -> getX()));
}

/**
 * @brief A comparator function used for sorting Points in the PointSet.
 *        This comparator compares 2 Points by their X coordinate value.
 *        If the 2 Points comparison turn to be equal, we will compare by their Y coordinate value.
 * @param point1 A pointer to the first Point to compare.
 * @param point2 A pointer to the second Point to compare.
 * @return true if the first Point is smaller then the second Point.
 */
static bool xComparator(const PointP point1, const PointP point2)
{
    return ((point1 -> getX()) < (point2 -> getX())) ||
            ((point1 -> getX()) == (point2 -> getX()) && (point1 -> getY()) < (point2 -> getY()));
}

/**
 * @brief A comparator function used for sorting Points in the PointSet.
 *        This comparator compares 2 Points by their polar angle from the Axis Point value.
 *        If the 2 Points comparison turn to be equal, we will compare by their distance.
 * @param point1 A pointer to the first Point to compare.
 * @param point2 A pointer to the second Point to compare.
 * @return true if the first Point is smaller then the second Point.
 */
static bool polarComparator(const PointP point1, const PointP point2)
{
    if ((point1 -> polarAngle(*gAxisPoint)) == (point2 -> polarAngle(*gAxisPoint)))
    {
        // If the Polar Angle is equal, we compare by the distance from the Axis Point.
        return point1 -> distance(*gAxisPoint) < point2 -> distance(*gAxisPoint);
    }
    return (point1 -> polarAngle(*gAxisPoint)) < (point2 -> polarAngle(*gAxisPoint));
}

/**
 * @brief Sort the PointSet according to the X coordinates.
 */
void PointSet::sortSet()
{
    if (_size != EMPTY_SET_SIZE)
    {
        std::sort(_pointSet, _pointSet + _size, xComparator);
    }
}

/**
 * @brief Sort the PointSet according to the Polar Angles.
 */
void PointSet::sortByPolar()
{
    if (_size != EMPTY_SET_SIZE)
    {
        // First we get the minimum Y value.
        std::stable_sort(_pointSet, _pointSet + _size, yComparator);
        gAxisPoint = _pointSet[MINIMUM_INDEX];

        // The n we sort all the rest of the Points according to our minimum.
        std::stable_sort(_pointSet + 1, _pointSet + _size, polarComparator);
    }
}


/*-----=  PointSet Operators Overload  =-----*/


/**
 * @brief An operator overload for the operator '[]' which gets the element in the
 *        given index in the PointSet.
 * @param index The required index in the PointSet.
 * @return The element in the given index.
 */
const Point& PointSet::operator[](int const index) const
{
    assert(index >= EMPTY_SET_SIZE && index < _size);
    return *(this -> _pointSet[index]);
}

/**
 * @brief An operator overload for the comparison operator '==' which compares
 *        this PointSet with another given PointSet.
 * @param other A reference for the PointSet to compare to.
 * @return true if both Sets contains the same elements, false otherwise.
 */
bool PointSet::operator==(const PointSet& other) const
{
    if (this -> _size != other._size)
    {
        return false;
    }

    // If both Sets have the same number of Elements, we will iterate on the current Set and check
    // that for each Point, the other Set contains that Point too.
    PointP currentPoint = nullptr;
    for (int i = 0; i < _size; i++)
    {
        currentPoint = _pointSet[i];
        if (other._findPoint(*currentPoint) == INVALID_INDEX)
        {
            return false;
        }
    }

    return true;
}

/**
 * @brief An operator overload for the comparison operator '!=' which compares
 *        this PointSet with another given PointSet.
 * @param other A reference for the PointSet to compare to.
 * @return true if the Sets does not contain the same elements, false otherwise.
 */
bool PointSet::operator!=(const PointSet& other) const
{
    return !(*this == other);
}

/**
 * @brief An operator overload for the subtract operator '-' which subtracts all the Points
 *        that appears in the given PointSet from this PointSet.
 * @param other A reference for the PointSet to subtract with.
 * @return PointSet which include only the Points that appears in this PointSet
 *         and not in the other PointSet.
 */
PointSet PointSet::operator-(const PointSet& other) const
{
    PointSet resultSet;

    PointP currentPoint = nullptr;
    for (int i = 0; i < _size; i++)
    {
        currentPoint = _pointSet[i];
        if (other._findPoint(*currentPoint) == INVALID_INDEX)
        {
            resultSet.add(*currentPoint);
        }
    }

    return resultSet;
}

/**
 * @brief An operator overload for the intersect operator '&' which intersect the Points from this
 *        PointSet and the given PointSet.
 * @param other A reference for the PointSet to intersect with.
 * @return PointSet which include only the Points that appears both in this PointSet
 *         and in the other PointSet.
 */
PointSet PointSet::operator&(const PointSet& other) const
{
    PointSet resultSet;

    PointP currentPoint = nullptr;
    for (int i = 0; i < _size; i++)
    {
        currentPoint = _pointSet[i];
        if (other._findPoint(*currentPoint) != INVALID_INDEX)
        {
            resultSet.add(*currentPoint);
        }
    }

    return resultSet;
}

/**
 * @brief An operator overload for the assignment operator '=' which assign the given PointSet
 *        to this PointSet.
 * @param other A reference for the PointSet to assign it's data.
 * @return The assigned PointSet with the required data.
 */
PointSet& PointSet::operator=(const PointSet& other)
{
    if (*this != other)
    {
        PointSet newSet(other);
        _swapData(*this, newSet);
    }
    return *this;
}

