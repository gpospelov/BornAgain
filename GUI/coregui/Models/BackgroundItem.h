// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BackgroundItem.h
//! @brief     Defines class BackgroundItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include "SessionItem.h"

class IBackground;

class BA_CORE_API_ BackgroundItem : public SessionItem
{
public:
    static const QString P_VALUE;
    BackgroundItem();
    virtual ~BackgroundItem();

    double getBackgroundValue() const;
    void setBackgroundValue(double value);

    std::unique_ptr<IBackground> createBackground() const;
};

#endif // BACKGROUNDITEM_H

