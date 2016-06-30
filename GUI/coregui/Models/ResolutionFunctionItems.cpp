// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ResolutionFunctionItems.cpp
//! @brief     Implements family of ResolutionFunctionItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ResolutionFunctionItems.h"
#include "ComboProperty.h"
#include "Units.h"
#include <QDebug>

ResolutionFunctionItem::ResolutionFunctionItem(const QString name)
    : SessionItem(name)
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
    addProperty(P_SIGMA_X, 0.02);
    getItem(P_SIGMA_X)->setLimits(AttLimits::lowerLimited(0.0));
    getItem(P_SIGMA_X)->setDecimals(3);
    addProperty(P_SIGMA_Y, 0.02);
    getItem(P_SIGMA_Y)->setLimits(AttLimits::lowerLimited(0.0));
    getItem(P_SIGMA_Y)->setDecimals(3);
}

IResolutionFunction2D *ResolutionFunction2DGaussianItem::createResolutionFunction(double scale) const
{
    double sigma_x = getItemValue(P_SIGMA_X).toDouble();
    double sigma_y = getItemValue(P_SIGMA_Y).toDouble();
    return new ResolutionFunction2DGaussian(sigma_x*scale, sigma_y*scale);
}
