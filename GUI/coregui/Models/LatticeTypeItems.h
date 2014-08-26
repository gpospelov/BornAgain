#ifndef LATTICETYPEITEMS_H
#define LATTICETYPEITEMS_H

#include "ParameterizedItem.h"

class BA_CORE_API_ BasicLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH1;
    static const QString P_LATTICE_LENGTH2;
    static const QString P_LATTICE_ANGLE;
    explicit BasicLatticeTypeItem(ParameterizedItem *parent=0);
    ~BasicLatticeTypeItem(){}
};

class BA_CORE_API_ SquareLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH;
    explicit SquareLatticeTypeItem(ParameterizedItem *parent=0);
    ~SquareLatticeTypeItem(){}
};

class BA_CORE_API_ HexagonalLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_LATTICE_LENGTH;
    explicit HexagonalLatticeTypeItem(ParameterizedItem *parent=0);
    ~HexagonalLatticeTypeItem(){}
};

#endif
