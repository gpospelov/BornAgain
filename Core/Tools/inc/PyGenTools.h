#ifndef PYSCRIPTTOOLS_H
#define PYSCRIPTTOOLS_H
#include "Simulation.h"
#include "PyGenVisitor.h"


namespace PyGenTools {
    void genPyScript(Simulation *simulation, std::string pyScriptName);
    std::string printDouble(double input);
    bool isSquare(double length1, double length2, double angle);
    bool isHexagonal(double length1, double length2, double angle);
    bool testPyScript(Simulation *simulation);

}

#endif // PYSCRIPTTOOLS_H
