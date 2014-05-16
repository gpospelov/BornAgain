#include "LatticeTypeItems.h"
#include "Units.h"

BasicLatticeTypeItem::BasicLatticeTypeItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("BasicLatticeType"), parent)
{
    setItemName("BasicLatticeType");
    setProperty("Lattice_length_1", 20.0);
    setProperty("Lattice_length_2", 20.0);
    setProperty("Lattice_angle", 90.0);
}


SquareLatticeTypeItem::SquareLatticeTypeItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("SquareLatticeType"), parent)
{
    setItemName("SquareLatticeType");
    setProperty("Lattice_length", 20.0);
}


HexagonalLatticeTypeItem::HexagonalLatticeTypeItem(ParameterizedItem *parent)
    : ParameterizedItem(QString("HexagonalLatticeType"), parent)
{
    setItemName("HexagonalLatticeType");
    setProperty("Lattice_length", 20.0);
}

