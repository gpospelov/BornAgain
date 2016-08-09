// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FTDecayFunctionItems.h
//! @brief     Defines FTDecayFunction1DItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FTDECAYFUNCTIONITEMS_H
#define FTDECAYFUNCTIONITEMS_H


#include "SessionItem.h"
#include "FTDecayFunctions.h"


class BA_CORE_API_ FTDecayFunction1DItem : public SessionItem
{

public:
    static const QString P_DECAY_LENGTH;
    explicit FTDecayFunction1DItem(const QString name)
        : SessionItem(name){}
    virtual IFTDecayFunction1D *createFTDecayFunction() const { return 0;}
    virtual ~FTDecayFunction1DItem(){}
};

class BA_CORE_API_ FTDecayFunction1DCauchyItem : public FTDecayFunction1DItem
{

public:
    explicit FTDecayFunction1DCauchyItem();
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DGaussItem : public FTDecayFunction1DItem
{

public:
    explicit FTDecayFunction1DGaussItem();
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DTriangleItem : public FTDecayFunction1DItem
{

public:
    explicit FTDecayFunction1DTriangleItem();
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction1DVoigtItem : public FTDecayFunction1DItem
{

public:
    static const QString P_ETA;
    explicit FTDecayFunction1DVoigtItem();
    virtual IFTDecayFunction1D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction2DItem : public SessionItem
{

public:
    static const QString P_DECAY_LENGTH_X;
    static const QString P_DECAY_LENGTH_Y;
    static const QString P_GAMMA;
    explicit FTDecayFunction2DItem(const QString name)
        : SessionItem(name) {
         addProperty(P_GAMMA, 0.0);
    }
    virtual IFTDecayFunction2D *createFTDecayFunction() const { return 0;}
    virtual ~FTDecayFunction2DItem(){}
};

class BA_CORE_API_ FTDecayFunction2DCauchyItem : public FTDecayFunction2DItem
{

public:
    explicit FTDecayFunction2DCauchyItem();
    virtual IFTDecayFunction2D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction2DGaussItem : public FTDecayFunction2DItem
{

public:
    explicit FTDecayFunction2DGaussItem();
    virtual IFTDecayFunction2D *createFTDecayFunction() const;
};

class BA_CORE_API_ FTDecayFunction2DVoigtItem : public FTDecayFunction2DItem
{

public:
    static const QString P_ETA;
    explicit FTDecayFunction2DVoigtItem();
    virtual IFTDecayFunction2D *createFTDecayFunction() const;
};



#endif // FTDECAYFUNCTIONITEMS_H

