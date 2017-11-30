// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BackgroundItems.h
//! @brief     Defines BackgroundItem classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef BACKGROUNDITEMS_H
#define BACKGROUNDITEMS_H

#include "SessionItem.h"

class IBackground;

class BA_CORE_API_ BackgroundItem : public SessionItem
{
public:
    explicit BackgroundItem(const QString& model_type)
        : SessionItem(model_type) {}

    virtual std::unique_ptr<IBackground> createBackground() const=0;
};

class BA_CORE_API_ BackgroundNoneItem : public BackgroundItem
{
public:
    BackgroundNoneItem();
    std::unique_ptr<IBackground> createBackground() const;
};

class BA_CORE_API_ ConstantBackgroundItem : public BackgroundItem
{
public:
    static const QString P_VALUE;

    ConstantBackgroundItem();
    std::unique_ptr<IBackground> createBackground() const;
};

#endif // BACKGROUNDITEMS_H

