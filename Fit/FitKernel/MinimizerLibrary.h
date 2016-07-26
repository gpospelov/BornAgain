// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/MinimizerLibrary.h
//! @brief     Declares namespace MinimizerLibrary.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERLIBRARY_H
#define MINIMIZERLIBRARY_H

#include <list>
#include <map>
#include <string>

//! The MinimizerLibrary namespace contains set of classes to form the catalogue of
//! available minimizers, their algorithms and short descriptions.

namespace MinimizerLibrary {

//! @class InfoItem
//! @ingroup fitting_internal
//! @brief Simple item to hold the name and the description.

class BA_CORE_API_ InfoItem {
public:
    InfoItem(){}
    InfoItem(const std::string& itemType, const std::string& itemDescription)
        : m_itemType(itemType)
        , m_itemDescription(itemDescription){}

    std::string getType() const { return m_itemType; }
    std::string getDescription() const { return m_itemDescription; }
private:
    std::string m_itemType;
    std::string m_itemDescription;
};

//! @class AlgorithmInfo
//! @ingroup fitting_internal
//! @brief Provides description of minimization algorithm.

class BA_CORE_API_ AlgorithmInfo : public InfoItem {
public:
    AlgorithmInfo(){}
    AlgorithmInfo(const std::string& algType, const std::string& algDescription);
};

//! @class MinimizerInfo
//! @ingroup fitting_internal
//! @brief Provides info about the minimizer, including list of defined minimization algorithms.

class BA_CORE_API_ MinimizerInfo : public InfoItem {
public:
    MinimizerInfo(){}
    MinimizerInfo(const std::string& minimizerType, const std::string& minimizerDescription);

    void addAlgorithm(const AlgorithmInfo& algorithm);
    void addAlgorithm(const std::string& algorithmName, const std::string& algorithmDescription);

    std::list<std::string> algorithmTypes() const;
    std::list<std::string> algorithmDescriptions() const;

private:
    std::list<AlgorithmInfo> m_algorithms;
};

//! @class MinimizerInfo
//! @ingroup fitting_internal
//! @brief Holds all information about available minimization engines.

class BA_CORE_API_ Catalogue {
public:
    Catalogue();

    void addMinimizer(const MinimizerInfo& minimizer);

    std::list<std::string> algorithmTypes(const std::string& minimizerType);
    std::list<std::string> algorithmDescriptions(const std::string& minimizerType);

private:
    MinimizerInfo minimizerInfo(const std::string& minimizerType);

    std::map<std::string, MinimizerInfo> m_minimizers;
};

} // MinimizerLibrary namespace

#endif // MINIMIZERLIBRARY_H
