// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorLorentz.h
//! @brief     Defines class FormFactorLorentz.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FORMFACTORLORENTZ_H_
#define FORMFACTORLORENTZ_H_

#include "IFormFactorBorn.h"
#include "IStochasticParameter.h"

//! ?

class FormFactorLorentz : public IFormFactorBorn
{
public:
    FormFactorLorentz(double volume);
    FormFactorLorentz(double height, double width);
    ~FormFactorLorentz();
    virtual FormFactorLorentz *clone() const;

    virtual int getNumberOfStochasticParameters() const { return 2; }

    virtual complex_t evaluate_for_q(const cvector_t &q) const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    double m_height;
    double m_width;
};

#endif /* FORMFACTORLORENTZ_H_ */
