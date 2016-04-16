CC=             g++ -ggdb -std=c++11 -Wall -O4 -I/G/ba/Core/FormFactors/ -I/G/ba/Core/Geometry -I/G/ba/Core/Tools

# LIBS=           -lm -lgslcblas -lgsl -lyaml-cpp

BIND=   ./

all:    $(BIND)fftest

SRC = fftest.cpp /G/ba/Core/FormFactors/FormFactorPolyhedron.cpp /G/ba/Core/Geometry/BasicVector3D.cpp /G/ba/Core/Tools/Exceptions.cpp /G/ba/Core/Tools/Precomputed.cpp

DIAG = -D POLYHEDRAL_DIAGNOSTIC=ON

$(BIND)fftest: $(SRC)
	$(CC) $(DIAG) -o $(BIND)fftest $(SRC)
