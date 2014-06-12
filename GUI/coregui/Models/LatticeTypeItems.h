#ifndef LATTICETYPEITEMS_H
#define LATTICETYPEITEMS_H

#include "ParameterizedItem.h"

class BasicLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH1, P_LATTICE_LENGTH2, P_LATTICE_ANGLE;
    explicit BasicLatticeTypeItem(ParameterizedItem *parent=0);
    ~BasicLatticeTypeItem(){}
};

class SquareLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH;
    explicit SquareLatticeTypeItem(ParameterizedItem *parent=0);
    ~SquareLatticeTypeItem(){}
};

class HexagonalLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH;
    explicit HexagonalLatticeTypeItem(ParameterizedItem *parent=0);
    ~HexagonalLatticeTypeItem(){}
};

#endif
