/**
 * @file PointSet.h
 * @author Itai Tagar <itagar>
 * @version 2.0
 * @date 04 Sep 2016
 *
 * @brief A Header File for the PointSet Class.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A Header File for the PointSet Class.
 * Declaring the PointSet Class, it's methods and fields.
 * A PointSet class is a Set which holds Points and allows several operations associated with a Set.
 */


#ifndef EX1_POINTSET_H
#define EX1_POINTSET_H


/*-----=  Includes  =-----*/


#include "Point.h"


/*-----=  Type Definitions  =-----*/


/**
 * @brief PointP is a pointer to a Point.
 */
typedef Point *PointP;


/*-----=  Class Declaration  =-----*/


/**
 * @brief A Class representing a PointSet which contains several Points in it (without repetitions).
 *        The PointSet holds several method which perform operations of a Set.
 */
class PointSet
{
public:

    /**
     * @brief A Default Constructor for the PointSet, which create a new PointSet ready to
     *        store Points.
     */
    PointSet();

    /**
     * @brief A Copy Constructor for the PointSet, which create a new PointSet ready to store Points
     *        from a given PointSet data.
     * @param other The PointSet to copy.
     */
    PointSet(const PointSet& other);

    /**
     * @brief A Destructor for the PointSet.
     */
    ~PointSet();

    /**
     * @brief Returns the size of the PointSet, i.e. the current number of elements.
     * @return The size of the PointSet.
     */
    int size() const { return _size; };

    /**
     * @brief Adds a given Point to the PointSet.
     *        The new Point will be inserted to the end of the PointSet.
     *        If the Point is already in the Set, this method will do nothing.
     * @param point The new Point to insert.
     * @return true if the insertion succeed, false otherwise.
     */
    bool add(const Point& point);

    /**
     * @brief Removes a given Point from the PointSet if exists, and updates the PointSet
     *        accordingly. If the Point does not exist in the Set, this method will do nothing.
     * @param point The Point to remove.
     * @return true if the removal succeed, false otherwise.
     */
    bool remove(const Point& point);

    /**
     * @brief Represent the PointSet as a string for output use.
     * @return A string representation of the PointSet.
     */
    std::string toString() const;

    /**
     * @brief Sort the PointSet according to the X coordinates.
     */
    void sortSet();

    /**
     * @brief Sort the PointSet according to the Polar Angles.
     */
    void sortByPolar();

    /**
     * @brief An operator overload for the operator '[]' which gets the element in the
     *        given index in the PointSet.
     * @param index The required index in the PointSet.
     * @return The element in the given index.
     */
    const Point& operator[](int const index) const;

    /**
     * @brief An operator overload for the comparison operator '==' which compares
     *        this PointSet with another given PointSet.
     * @param other A reference for the PointSet to compare to.
     * @return true if both Sets contains the same elements, false otherwise.
     */
    bool operator==(const PointSet& other) const;

    /**
     * @brief An operator overload for the comparison operator '!=' which compares
     *        this PointSet with another given PointSet.
     * @param other A reference for the PointSet to compare to.
     * @return true if the Sets does not contain the same elements, false otherwise.
     */
    bool operator!=(const PointSet& other) const;

    /**
     * @brief An operator overload for the subtract operator '-' which subtracts all the Points
     *        that appears in the given PointSet from this PointSet.
     * @param other A reference for the PointSet to subtract with.
     * @return PointSet which include only the Points that appears in this PointSet
     *         and not in the other PointSet.
     */
    PointSet operator-(const PointSet& other) const;

    /**
     * @brief An operator overload for the intersect operator '&' which intersect the Points
     *        from this PointSet and the given PointSet.
     * @param other A reference for the PointSet to intersect with.
     * @return PointSet which include only the Points that appears both in this PointSet
     *         and in the other PointSet.
     */
    PointSet operator&(const PointSet& other) const;

    /**
     * @brief An operator overload for the assignment operator '=' which assign the given PointSet
     *        to this PointSet.
     * @param other A reference for the PointSet to assign it's data.
     * @return The assigned PointSet with the required data.
     */
    PointSet& operator=(const PointSet& other);

private:
    // PointSet Private Fields.
    int _size;  // The size of the PointSet, i.e. the current number of elements in the Set.
    int _capacity;  // The capacity of the PointSet, i.e. the current maximum size to hold.
    PointP *_pointSet;  // The container for the Points data.

    /**
     * @brief Resize the PointSet capacity.
     *        The Resize operation allocates memory for the new capacity, and copies all the data
     *        from the current Set to the new larger Set.
     */
    void _resizePointSet();

    /**
     * @brief Finds the given Point in the PointSet if exists and return it's index in the Set.
     *        If the given Point does not exist, returns INVALID_INDEX.
     * @param point The Point to find.
     * @return The index of the Point in the Set if exists, otherwise return INVALID_INDEX.
     */
    int _findPoint(const Point& point) const;

    /**
     * @brief Initialize the PointSet container with NULL Pointers in the given range.
     * @param startIndex The index to start initialize the PointP cells. (inclusive).
     * @param endIndex The index to end initialize the PointP cells. (exclusive).
     */
    void _initializeSet(int const startIndex, int const endIndex);

    /**
     * @brief Trims a gap in the PointSet which can occur during the removal operation.
     *        This method sets each PointP cell in the Set to point to the following cell, starting
     *        from the given index.
     * @param gapIndex The index to start the trimming process from.
     */
    void _trimGap(int const gapIndex);

    /**
     * @brief Swap data between the 2 given PointSets.
     * @param pointSet1 The first PointSet to swap.
     * @param pointSet2 The second PointSet to swap.
     */
    void _swapData(PointSet& pointSet1, PointSet& pointSet2);

};


#endif //EX1_POINTSET_H
