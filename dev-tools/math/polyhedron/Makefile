CC=             g++ -ggdb -std=c++11 -Wall -O4 -I/G/ba/Core/FormFactors/ -I/G/ba/Core/Geometry -I/G/ba/Core/Tools -I/G/ba/Core/Samples -I/usr/include/eigen3

# LIBS=           -lm -lgslcblas -lgsl -lyaml-cpp

BIND=   ./

all:    $(BIND)polyh_test

SRC = polyh_test.cpp /G/ba/Core/FormFactors/FormFactorPolyhedron.cpp /G/ba/Core/Geometry/BasicVector3D.cpp /G/ba/Core/Tools/Exceptions.cpp /G/ba/Core/Tools/Precomputed.cpp

DIAG = -D POLYHEDRAL_DIAGNOSTIC=ON

$(BIND)polyh_test: $(SRC)
	$(CC) $(DIAG) -L/usr/local/lib/BornAgain-1.5 -lBornAgainCore -o $(BIND)polyh_test $(SRC)
