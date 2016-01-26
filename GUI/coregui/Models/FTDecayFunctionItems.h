// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FTDecayFunctionItems.h
//! @brief     Defines FTDecayFunction1DItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FTDECAYFUNCTIONITEMS_H
#define FTDECAYFUNCTIONITEMS_H


#include "ParameterizedItem.h"
#include "FTDecayFunctions.h"


class BA_CORE_API_ FTDecayFunction1DItem : public ParameterizedItem
{
    Q_OBJECT
public:
    static const QString P_DECAY_LENGTH;
    explicit FTDecayFunction1DItem(const QString name, ParameterizedItem *parent)
        : ParameterizedItem(name, parent){}
    virtual IFTDecayFunction1D *createFTDecayFunction() const { return 0;}
    virtual ~FTDecayFunction1DItem(){}
};

class BA_CORE_API_ FTDecayFunction1DCauchyItem : public FTDecayFunction1DItem
{
    Q_OBJECT
public:
    explicit FTDecayFunction1DCauchyItem(ParameterizedItem *parent=0);
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DGaussItem : public FTDecayFunction1DItem
{
    Q_OBJECT
public:
    explicit FTDecayFunction1DGaussItem(ParameterizedItem *parent=0);
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DGateItem : public FTDecayFunction1DItem
{
    Q_OBJECT
public:
    explicit FTDecayFunction1DGateItem(ParameterizedItem *parent=0);
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DTriangleItem : public FTDecayFunction1DItem
{
    Q_OBJECT
public:
    explicit FTDecayFunction1DTriangleItem(ParameterizedItem *parent=0);
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DCosineItem : public FTDecayFunction1DItem
{
    Q_OBJECT
public:
    explicit FTDecayFunction1DCosineItem(ParameterizedItem *parent=0);
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DVoigtItem : public FTDecayFunction1DItem
{
    Q_OBJECT
public:
    static const QString P_ETA;
    explicit FTDecayFunction1DVoigtItem(ParameterizedItem *parent=0);
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

#endif // FTDECAYFUNCTIONITEMS_H

