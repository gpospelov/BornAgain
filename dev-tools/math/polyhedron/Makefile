CC=             g++ -ggdb -O0 -std=c++11 -Wall -I/G/ba/Core/FormFactors/ -I/G/ba/Core/Geometry -I/G/ba/Core/Tools -I/G/ba/Core/Samples -I/usr/include/eigen3

# LIBS=           -lm -lgslcblas -lgsl -lyaml-cpp

BIND=   ./

all:    $(BIND)polyh_test

# source from BornAgain overwrites -lBornAgainCore, cf http://stackoverflow.com/questions/36667429
SRC = polyh_test.cpp /G/ba/Core/FormFactors/FormFactorPolyhedron.cpp

DIAG = -D POLYHEDRAL_DIAGNOSTIC=ON

$(BIND)polyh_test: $(SRC)
	$(CC) $(DIAG) -L/usr/local/lib/BornAgain-1.5 -lBornAgainCore -o $(BIND)polyh_test $(SRC)
