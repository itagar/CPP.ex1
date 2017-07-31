CXX= g++
CXXFLAGS= -c -Wextra -Wall -Wvla -pthread -std=c++11 -DNDEBUG
CODEFILES= ex1.tar Point.h Point.cpp PointSet.h PointSet.cpp ConvexHull.cpp PointSetBinaryOperations.cpp Makefile README


# Default
default: PointSetBinaryOperations ConvexHull
	./PointSetBinaryOperations


# Executables
PointSetBinaryOperations: PointSetBinaryOperations.o PointSet.o Point.o
	$(CXX) PointSetBinaryOperations.o PointSet.o Point.o -o PointSetBinaryOperations

ConvexHull: ConvexHull.o PointSet.o Point.o
	$(CXX) ConvexHull.o PointSet.o Point.o -o ConvexHull


# Object Files
Point.o: Point.cpp Point.h
	$(CXX) $(CXXFLAGS) Point.cpp -o Point.o

PointSet.o: PointSet.cpp PointSet.h Point.h
	$(CXX) $(CXXFLAGS) PointSet.cpp -o PointSet.o

ConvexHull.o: ConvexHull.cpp PointSet.h
	$(CXX) $(CXXFLAGS) ConvexHull.cpp -o ConvexHull.o

PointSetBinaryOperations.o: PointSetBinaryOperations.cpp PointSet.h
	$(CXX) $(CXXFLAGS) PointSetBinaryOperations.cpp -o PointSetBinaryOperations.o


# tar
tar:
	tar -cvf $(CODEFILES)


# Other Targets
clean:
	-rm -vf *.o PointSetBinaryOperations ConvexHull
