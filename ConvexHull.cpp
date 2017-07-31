/**
 * @file ConvexHull.cpp
 * @author Itai Tagar <itagar>
 * @version 2.4
 * @date 04 Sep 2016
 *
 * @brief A program for calculating the Convex Hull of a PointSet.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A program for calculating the Convex Hull of a PointSet.
 * Input:       X and Y coordinates from the user via the standard input stream.
 * Process:     From the input, the program creates a PointSet which contains all the Points that
 *              are in the given X,Y coordinates.
 *              It then performs the Graham Scan Algorithm on this PointSet and calculate the
 *              Convex Hull.
 *              The Algorithm runs as follow:
 *                  First, it finds the Point with the minimal Y value
 *                  (if there are 2 we take the one with the minimal X value as a tie breaker).
 *                  Then we sort all the other Points in the PointSet by their Polar Angle
 *                  according to the minimal Point we just found.
 *                  when our Set is sorted, we can start run in a Counter-Clockwise direction
 *                  and for each 3 Points we check if their orientation performs a Counter-Clockwise
 *                  turn or not.
 *                  If the turn is Counter-Clockwise, we continue, otherwise we remove these Points
 *                  that make the bad turn and keep up to the next set of Points.
 *                  We keep doing so until reaching the starting Point again and then we got our
 *                  Convex Hull.
 *                  The Algorithm running time complexity is O(n*log(n)) because we use sorting
 *                  algorithms that run in O(n*log(n)). The running time of the orientation check
 *                  and the first initialization of the PointSet within the user input is O(n).
 *                  So we get O(n*log(n)).
 *                  Reference:
 *                      "Cormen, Leiserson, Rivest & Stein - Introduction to Algorithms", Page 1031.
 * Output:      Prints to the standard output the Points that make the Convex Hull, sorted by their
 *              X coordinate.
 */

/*-----=  Includes  =-----*/


#include <iostream>
#include "PointSet.h"


/*-----=  Definitions  =-----*/


/**
 * @def RESULT_START_OUTPUT "result\n"
 * @brief A Macro that sets the output beginning for the entire result output.
 */
#define RESULT_START_OUTPUT "result\n"

/**
 * @def START_INDEX 0
 * @brief A Macro that sets the value for the start index in the input.
 */
#define START_INDEX 0

/**
 * @def INITIAL_RESULT_SIZE 2
 * @brief A Macro that sets the initial size of the result Set in the Convex Hull algorithm.
 */
#define INITIAL_RESULT_SIZE 2


/*-----=  Input Handling  =-----*/


/**
 * @brief Initialize a new Point from a given user input.
 * @param currentInput A string representing the user input, containing the X,Y coordinates.
 * @return A Point with the requested data given from the user input.
 */
static Point initializePoint(std::string const currentInput)
{
    // Parse the current input to the X,Y coordinates.
    size_t delimiterIndex = currentInput.find(COORDINATES_SEPARATOR);
    int x = stoi(currentInput.substr(START_INDEX, delimiterIndex));
    int y = stoi(currentInput.substr(delimiterIndex + 1, std::string::npos));

    // Create a new Point.
    Point point(x, y);
    return point;
}

/**
 * @brief Handle the process of receiving input from the user and creating proper Points from the
 *        given data to the PointSet.
 * @param pointSet The PointSet to add data to.
 */
static void receiveInput(PointSet& pointSet)
{
    std::string currentInput;
    while (std::getline(std::cin, currentInput))
    {
        // Create a new Point from the input.
        Point point = initializePoint(currentInput);
        pointSet.add(point);
    }
}


/*-----=  Convex Hull Process  =-----*/


/**
 * @brief Determine if a given 3 Points create a Counter-Clockwise turn.
 *        If the result of the calculation is negative - we get Clockwise turn.
 *        If the result of the calculation is positive - we get Counter-Clockwise turn.
 *        If the result of the calculation is zero - we get Collinear.
 * @param pointA The first point to include in the calculation.
 * @param pointB The second point to include in the calculation.
 * @param pointC The third point to include in the calculation.
 * @return true if the Points make a Counter-Clockwise turn.
 */
static bool counterClockwise(const Point& pointA, const Point& pointB, const Point& pointC)
{
    long result = (pointB.getX() - pointA.getX()) * (pointC.getY() - pointA.getY())
                   - (pointB.getY() - pointA.getY()) * (pointC.getX() - pointA.getX());
    return (result > 0);
}

/**
 * @brief Calculate the Convex Hull of a given PointSet.
 *        The Algorithm is specified in the header of this file.
 * @pointSet The PointSet that contain the Point to calculate their Convex Hull.
 * @return A PointSet which contains the result of the Convex Hull Points.
 */
static PointSet getConvexHull(PointSet& pointSet)
{
    PointSet resultSet;
    pointSet.sortByPolar();

    int i = 0;  // The index of the given PointSet.
    int j = 0;  // The index for the result PointSet.

    // Initialize the Result set with the first Points.
    for ( ; (j < pointSet.size()) && (j < INITIAL_RESULT_SIZE); j++)
    {
        resultSet.add(pointSet[j]);
    }

    // Iterate on the Points in the given PointSet.
    for (i = INITIAL_RESULT_SIZE ; i < pointSet.size(); i++)
    {
        // Every time we encounter a bad turn we remove the Point from the Set.
        while ((j >= INITIAL_RESULT_SIZE) &&
               (!counterClockwise(resultSet[j-2], resultSet[j-1], pointSet[i])))
        {
            resultSet.remove(resultSet[j-1]);
            j--;
        }

        resultSet.add(pointSet[i]);
        j++;
    }
    return resultSet;
}


/*-----=  Output Handling  =-----*/


/**
 * @brief Process the result PointSet after the Convex Hull operation, and output it to the
 *        standard output.
 * @param resultSet The result PointSet after the Convex Hull operation.
 */
static void processResult(PointSet& resultSet)
{
    resultSet.sortSet();
    std::cout << RESULT_START_OUTPUT;
    std::cout << resultSet.toString();
}


/*-----=  Main  =-----*/


/**
 * @brief The Main function that runs this program.
 *        The function receive input from the user, and then create a PointSet with the given data.
 *        It then finds the Convex Hull of that PointSet and output the result.
 * @return 0 when the program ran successfully, otherwise return a non-zero number.
 */
int main()
{
    // Create the PointSet from the user input.
    PointSet pointSet;
    receiveInput(pointSet);

    // Analyze data and get the Convex Hull.
    PointSet resultSet = getConvexHull(pointSet);

    // Printing the result to the standard output.
    processResult(resultSet);

    return 0;
}