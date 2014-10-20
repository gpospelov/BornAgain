#ifndef PYSCRIPTTOOLS_H
#define PYSCRIPTTOOLS_H
#include "Simulation.h"
#include "PyGenVisitor.h"


namespace PyGenTools {
    BA_CORE_API_ void genPyScript(Simulation *simulation, std::string pyScriptName);
    BA_CORE_API_ std::string printDouble(double input);
    BA_CORE_API_ bool isSquare(double length1, double length2, double angle);
    BA_CORE_API_ bool isHexagonal(double length1, double length2, double angle);
    BA_CORE_API_ bool testPyScript(Simulation *simulation);
}

#endif // PYSCRIPTTOOLS_H
