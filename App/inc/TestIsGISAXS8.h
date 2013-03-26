// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS8.h 
//! @brief     Defines class TestIsGISAXS8.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTISGISAXS8_H_
#define TESTISGISAXS8_H_

#include "IFunctionalTest.h"

//! IsGISAXS ex#8: Cylinder with interference 2DDL_lattice.

class TestIsGISAXS8 : public IFunctionalTest
{
 public:
    TestIsGISAXS8();
    virtual ~TestIsGISAXS8(){}

    virtual void execute();
    virtual void finalise();
 private:
    // structure to hold info over several compare cases
    struct CompareStruct
    {
        CompareStruct(std::string _isginame, std::string _thisname, std::string _descr) : isginame(_isginame), thisname(_thisname), descr(_descr){}
        std::string isginame;
        std::string thisname;
        std::string descr;
    };

    std::string m_data_path;
};

#endif /* TESTISGISAXS8_H_ */
