// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @copyright Forschungszentrum Jülich GmbH 2013
//             
//  Homepage:  apps.jcns.fz-juelich.de/BornAgain
//  License:   GNU General Public License v3 or higher (see COPYING)
//
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
//! @file      FormFactors/FormFactorPrism6.h 
//! @brief     Defines class FormFactorPrism6.
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM6_H
#define FORMFACTORPRISM6_H
#include "IFormFactorBorn.h"

//! Form factor of a ??

class FormFactorPrism6 : public IFormFactorBorn
{
public:
    FormFactorPrism6(double height, double half_side);
    ~FormFactorPrism6();
    virtual FormFactorPrism6 *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual double getHeight() const { return m_height; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:    
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_height;
    double m_half_side;
    double m_root3; // Cached value of square root of 3
};

#endif // FORMFACTORPRISM6_H
