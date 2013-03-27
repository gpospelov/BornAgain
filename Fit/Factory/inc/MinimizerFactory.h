#ifndef MINIMIZERFACTORY_H
#define MINIMIZERFACTORY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MinimizerFactory.h
//! @brief  Definition of SampleFactory class
//! @author Scientific Computing Group at FRM II
//! @date   23.01.2013

#include "IMinimizer.h"
#include <string>
#include <vector>
#include <map>


//- -------------------------------------------------------------------
//! @class MinimizerFactory
//! @brief Factory to create minimizers
//- -------------------------------------------------------------------
class MinimizerFactory
{
 public:
    static IMinimizer *createMinimizer(const std::string& minimizer, const std::string& algorithm = std::string(), const std::string& options=std::string() );
    static void print_catalogue();

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
