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

#ifndef MINIMIZERITEM_H
#define MINIMIZERITEM_H

#include "SessionItem.h"
#include <memory>

class IMinimizer;

//! The MinimizerItem class is the base item to hold minimizer settings.

class BA_CORE_API_ MinimizerItem : public SessionItem
{
public:
    static const QString P_ALGORITHMS;
    static const QString P_MAX_ITERATION_COUNT;
    static const QString P_ERROR_DEFINITION;
    static const QString P_MAX_TOLERANCE;
    static const QString P_PRECISION;
    explicit MinimizerItem(const QString &model_type);
    virtual std::unique_ptr<IMinimizer> createMinimizer() const = 0;
    int maxIterationCount() const;
};


//! The MinimizerContainerItem class holds group of 3 minimizers.

class BA_CORE_API_ MinimizerContainerItem : public MinimizerItem
{
public:
    static const QString P_MINIMIZERS;
    explicit MinimizerContainerItem();

    virtual std::unique_ptr<IMinimizer> createMinimizer() const;
};

//! The MinuitMinimizerItem class represents settings for ROOT Minuit2 minimizer.

class BA_CORE_API_ MinuitMinimizerItem : public MinimizerItem
{
public:
    explicit MinuitMinimizerItem();
    virtual std::unique_ptr<IMinimizer> createMinimizer() const;
};

//! The GSLMinimizerItem class represents settings for GSL minimizers family.

class BA_CORE_API_ GSLMinimizerItem : public MinimizerItem
{
public:
    explicit GSLMinimizerItem();
    virtual std::unique_ptr<IMinimizer> createMinimizer() const;
};

//! The GeneticMinimizerItem class represents settings for TMVA/Genetic minimizer.

class BA_CORE_API_ GeneticMinimizerItem : public MinimizerItem
{
public:
    explicit GeneticMinimizerItem();
    virtual std::unique_ptr<IMinimizer> createMinimizer() const;
};

#endif // MINIMIZERITEM_H

