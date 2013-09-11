// ************************************************************************** //
//                                                                         
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestFormFactors.h
//! @brief     Defines class TestFormFactors.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTFORMFACTORS_H
#define TESTFORMFACTORS_H

#include "IFunctionalTest.h"
#include "OutputData.h"
#include "ISample.h"

//! Comparison with FormFactors ex-1: mean forfactor cylinder and prism

class TestFormFactors : public IFunctionalTest
{
public:
    TestFormFactors(){}
    virtual ~TestFormFactors(){}

    virtual void execute();
    virtual void finalise();
private:
    std::string m_data_path;
};

#endif // TESTFORMFACTORS_H


