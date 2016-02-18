// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ResolutionFunctionItems.cpp
//! @brief     Implements family of ResolutionFunctionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ResolutionFunctionItems.h"
#include "ComboProperty.h"
#include "Units.h"
#include <QDebug>

ResolutionFunctionItem::ResolutionFunctionItem(const QString name)
    : ParameterizedItem(name)
{
}

/* ------------------------------------------------ */

ResolutionFunctionNoneItem::ResolutionFunctionNoneItem()
    : ResolutionFunctionItem(Constants::ResolutionFunctionNoneType)
{
}

IResolutionFunction2D *ResolutionFunctionNoneItem::createResolutionFunction(double scale) const
{
    Q_UNUSED(scale);
    return 0;
}

/* ------------------------------------------------ */

const QString ResolutionFunction2DGaussianItem::P_SIGMA_X = "Sigma X";
const QString ResolutionFunction2DGaussianItem::P_SIGMA_Y = "Sigma Y";

ResolutionFunction2DGaussianItem::ResolutionFunction2DGaussianItem()
    : ResolutionFunctionItem(Constants::ResolutionFunction2DGaussianType)
{
    registerProperty(P_SIGMA_X, 0.02);//.lowerLimited(0.0).setDecimals(3);
    registerProperty(P_SIGMA_Y, 0.02);//.lowerLimited(0.0).setDecimals(3);
}

IResolutionFunction2D *ResolutionFunction2DGaussianItem::createResolutionFunction(double scale) const
{
    double sigma_x = getRegisteredProperty(P_SIGMA_X).toDouble();
    double sigma_y = getRegisteredProperty(P_SIGMA_Y).toDouble();
    return new ResolutionFunction2DGaussian(sigma_x*scale, sigma_y*scale);
}
