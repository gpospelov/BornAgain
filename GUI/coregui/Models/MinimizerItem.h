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
    static const QString P_ALGORITHMS;
    explicit MinimizerItem();
};

//! The MinuitMinimizerItem class represents settings for ROOT Minuit2 minimizer.

class BA_CORE_API_ MinuitMinimizerItem : public SessionItem
{
public:
    explicit MinuitMinimizerItem();
};

//! The GSLMinimizerItem class represents settings for GSL minimizers family.

class BA_CORE_API_ GSLMinimizerItem : public SessionItem
{
public:
    explicit GSLMinimizerItem();
};

//! The GeneticMinimizerItem class represents settings for TMVA/Genetic minimizer.

class BA_CORE_API_ GeneticMinimizerItem : public SessionItem
{
public:
    explicit GeneticMinimizerItem();
};

#endif

