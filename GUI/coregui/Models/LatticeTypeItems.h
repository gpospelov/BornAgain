#ifndef LATTICETYPEITEMS_H
#define LATTICETYPEITEMS_H

#include "ParameterizedItem.h"


class BasicLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit BasicLatticeTypeItem(ParameterizedItem *parent=0);
    ~BasicLatticeTypeItem(){}
};


class SquareLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit SquareLatticeTypeItem(ParameterizedItem *parent=0);
    ~SquareLatticeTypeItem(){}
};


class HexagonalLatticeTypeItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit HexagonalLatticeTypeItem(ParameterizedItem *parent=0);
    ~HexagonalLatticeTypeItem(){}
};



#endif
