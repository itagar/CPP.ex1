/**
 * @file PointSetBinaryOperations.cpp
 * @author Itai Tagar <itagar>
 * @version 1.0
 * @date 04 Sep 2016
 *
 * @brief A program for the demonstrating several operators of the PointSet.
 *
 * @section LICENSE
 * This program is free to use in every operation system.
 *
 * @section DESCRIPTION
 * A program for the demonstrating several operators of the PointSet.
 * Creating several PointSets and apply on them some of the PointSet operators that were overloaded.
 */


/*-----=  Includes  =-----*/


#include <iostream>
#include "PointSet.h"


/*-----=  Definitions  =-----*/


/**
 * @def POINTS_1 {{7, 12}, {1, 1}, {2, 0}, {-4, -4}, {1, 1}, {0, 0}, {7, 12}}
 * @brief A Macro that sets Points array number 1.
 */
#define POINTS_1 {{7, 12}, {1, 1}, {2, 0}, {-4, -4}, {1, 1}, {0, 0}, {7, 12}}

/**
 * @def POINTS_2 {{1, 1}, {0, 0}, {7, 12}, {-4, -4}, {2, 0}}
 * @brief A Macro that sets Points array number 2.
 */
#define POINTS_2 {{1, 1}, {0, 0}, {7, 12}, {-4, -4}, {2, 0}}

/**
 * @def POINTS_3 {{5, 7}, {7, 12}, {0, 0}, {4, 123}, {0, 3}, {1, 1}}
 * @brief A Macro that sets Points array number 3.
 */
#define POINTS_3 {{5, 7}, {7, 12}, {0, 0}, {4, 123}, {0, 3}, {1, 1}}

/**
 * @def END_OUTPUT "End of Demonstration"
 * @brief A Macro that sets the output message for the end of demonstration.
 */
#define END_OUTPUT "End of Demonstration!"

/**
 * @def INTERSECT_TITLE "Intersect"
 * @brief A Macro that sets the title message for the Intersection demo.
 */
#define INTERSECT_TITLE "Intersect"

/**
 * @def SUBTRACT_TITLE "Subtract"
 * @brief A Macro that sets the title message for the Subtraction demo.
 */
#define SUBTRACT_TITLE "Subtract"


/*-----=  Demonstrations  =-----*/


/**
 * @brief Initialize the given 3 PointSets, A, B and C with the Points from the Point's arrays.
 * @param pointSetA A PointsSet to initialize.
 * @param pointSetB A PointsSet to initialize.
 * @param pointSetC A PointsSet to initialize.
 */
static void initializePointSets(PointSet& pointSetA, PointSet& pointSetB, PointSet& pointSetC)
{
    // Adding Numbers to pointSetA.
    Point points1[] = POINTS_1;
    for (Point point : points1)
    {
        pointSetA.add(point);
    }

    // Adding Numbers to pointSetB.
    Point points2[] = POINTS_2;
    for (Point point : points2)
    {
        pointSetB.add(point);
    }

    // Adding Numbers to pointSetC.
    Point points3[] = POINTS_3;
    for (Point point : points3)
    {
        pointSetC.add(point);
    }
    std::cout << "A... \n" << pointSetA.toString() << std::endl;
    std::cout << "B... \n" << pointSetB.toString() << std::endl;
    std::cout << "C... \n" << pointSetC.toString() << std::endl;
}

/**
 * @brief Demonstrate copy and assignment operations with the given 3 PointSets, A, B and C.
 * @param pointSetA A PointsSet to use in the demonstration.
 * @param pointSetB A PointsSet to use in the demonstration.
 * @param pointSetC A PointsSet to use in the demonstration.
 */
static void copy(PointSet& pointSetA, PointSet& pointSetB, PointSet& pointSetC)
{
    PointSet pointSetD = pointSetB;
    PointSet pointSetE(pointSetB);
    pointSetA = pointSetA;  // Checking self-copy.
    pointSetD = pointSetC;
    std::cout << "D (Copy of C)... \n" << pointSetD.toString() << std::endl;
    std::cout << "E (Copy of B)... \n" << pointSetE.toString() << std::endl;
}

/**
 * @brief Demonstrate equality operations with the given 3 PointSets, A, B and C.
 * @param pointSetA A PointsSet to use in the demonstration.
 * @param pointSetB A PointsSet to use in the demonstration.
 * @param pointSetC A PointsSet to use in the demonstration.
 */
static void equality(PointSet& pointSetA, PointSet& pointSetB, PointSet& pointSetC)
{
    if (pointSetA == pointSetB)
    {
        std::cout << "A==B" << std::endl;
    }
    else
    {
        std::cout << "A!=B" << std::endl;
    }

    if (pointSetB != pointSetC)
    {
        std::cout << "B!=C" << std::endl;
    }
    else
    {
        std::cout << "B==C" << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief Demonstrate subtraction operations with the given 3 PointSets, A, B and C.
 * @param pointSetA A PointsSet to use in the demonstration.
 * @param pointSetB A PointsSet to use in the demonstration.
 * @param pointSetC A PointsSet to use in the demonstration.
 */
static void subtraction(PointSet& pointSetA, PointSet& pointSetB, PointSet& pointSetC)
{
    PointSet subtract = pointSetB-pointSetC;
    std::cout << SUBTRACT_TITLE << " B-C... \n" << subtract.toString() << std::endl;
    subtract = pointSetC-pointSetA;
    std::cout << SUBTRACT_TITLE << " C-A... \n" << subtract.toString() << std::endl;
}

/**
 * @brief Demonstrate intersection operations with the given 3 PointSets, A, B and C.
 * @param pointSetA A PointsSet to use in the demonstration.
 * @param pointSetB A PointsSet to use in the demonstration.
 * @param pointSetC A PointsSet to use in the demonstration.
 */
static void intersection(PointSet& pointSetA, PointSet& pointSetB, PointSet& pointSetC)
{
    PointSet intersect = pointSetA&pointSetC;
    std::cout << INTERSECT_TITLE << " A&C... \n" << intersect.toString() << std::endl;
    intersect = pointSetB&pointSetB;
    std::cout << INTERSECT_TITLE << " B&B... \n" << intersect.toString() << std::endl;
}


/*-----=  Main  =-----*/


/**
 * @brief The Main function that runs this Demo Program and demonstrate the different operations
 *        available on PointSet.
 * @return 0 when the program ran successfully, otherwise return a non-zero number.
 */
int main()
{
    // Initializations.
    PointSet pointSetA;
    PointSet pointSetB;
    PointSet pointSetC;
    initializePointSets(pointSetA, pointSetB, pointSetC);

    // Copy and Assign.
    copy(pointSetA, pointSetB, pointSetC);

    // Equality and Non-Equality.
    equality(pointSetA, pointSetB, pointSetC);

    // Subtraction.
    subtraction(pointSetA, pointSetB, pointSetC);

    // Intersection.
    intersection(pointSetA, pointSetB, pointSetC);

    std::cout << END_OUTPUT << std::endl;
    return 0;
}