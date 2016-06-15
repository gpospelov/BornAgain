// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItem.h
//! @brief     Declares MinimizerItem class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MINUITMINIMIZERITEM_H
#define MINUITMINIMIZERITEM_H

#include "SessionItem.h"

//! The MinimizerItem class is the main item to hold various minimizer settings.

class BA_CORE_API_ MinimizerItem : public SessionItem
{
public:
    static const QString P_MINIMIZER_LIBRARY;
    explicit MinimizerItem();
};

#endif

