// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ResolutionFunctionItems.h
//! @brief     Defines family of ResolutionFunctionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RESOLUTIONFUNCTIONITEMS_H
#define RESOLUTIONFUNCTIONITEMS_H

#include "SessionItem.h"
#include "ResolutionFunction2DGaussian.h"


class BA_CORE_API_ ResolutionFunctionItem : public SessionItem
{

public:
    explicit ResolutionFunctionItem(const QString name);
    virtual ~ResolutionFunctionItem() {}

    virtual IResolutionFunction2D *createResolutionFunction(double scale = 1.0) const=0;
};

class BA_CORE_API_ ResolutionFunctionNoneItem : public ResolutionFunctionItem
{

public:
    explicit ResolutionFunctionNoneItem();
    virtual IResolutionFunction2D *createResolutionFunction(double scale) const;
};

class BA_CORE_API_ ResolutionFunction2DGaussianItem : public ResolutionFunctionItem
{

public:
    static const QString P_SIGMA_X;
    static const QString P_SIGMA_Y;
    explicit ResolutionFunction2DGaussianItem();
    virtual IResolutionFunction2D *createResolutionFunction(double scale) const;
};



#endif // DISTRIBUTIONITEM_H

