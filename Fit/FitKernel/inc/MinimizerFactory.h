// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/MinimizerFactory.h
//! @brief     Defines class MinimizerFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERFACTORY_H
#define MINIMIZERFACTORY_H

#include "IMinimizer.h"
#include <string>
#include <vector>
#include <map>


//! @class MinimizerFactory
//! @ingroup fitting
//! @brief Factory to create minimizers

class BA_CORE_API_ MinimizerFactory
{
 public:
    static IMinimizer *createMinimizer(const std::string& minimizer, const std::string& algorithm = std::string(), const std::string& options=std::string() );
    static void printCatalogue();

    //! Create minimizer using existing one. Only minimizer type and minimizer settings are propagated.
    static IMinimizer *createMinimizer(const IMinimizer *minimizer);

 private:

    //! @class map of minimizer names holding list of defined algorithms for every minimizer
    class Catalogue {
    public:
        typedef std::map<std::string, std::vector<std::string > > catalogue_t;
        typedef catalogue_t::const_iterator const_iterator;
        Catalogue();
        const_iterator begin() const { return m_data.begin(); }
        const_iterator end() const { return m_data.end(); }
        bool isValid(const std::string& minimizer, const std::string& algorithm) const;
        friend std::ostream& operator<<(std::ostream& ostr, const Catalogue& m) { m.print(ostr); return ostr; }
    private:
        void print(std::ostream& ostr) const;
        catalogue_t m_data;
    };

    static Catalogue m_catalogue;
};

#endif // MINIMIZERFACTORY_H
