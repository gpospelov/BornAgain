// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestIsGISAXS3.h 
//! @brief     Defines class TestIsGISAXS3.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef TESTISGISAXS3_H_
#define TESTISGISAXS3_H_

#include "IFunctionalTest.h"
#include "OutputData.h"
//#include "ISample.h"

#include <string>

//! IsGISAXS ex#3: Cylinder on top of substrate.

class TestIsGISAXS3 : public IFunctionalTest
{
  public:
    TestIsGISAXS3();
    virtual ~TestIsGISAXS3(){}
    virtual void execute();
    virtual void finalise();

  private:
    // structure to hold info over several compare cases
    struct CompareStruct
    {
        CompareStruct(std::string _isginame,
                      std::string _thisname,
                      std::string _descr)
        : isginame(_isginame), thisname(_thisname), descr(_descr){}
        std::string isginame;
        std::string thisname;
        std::string descr;
    };

    std::string m_data_path;
};
#endif /* TESTISGISAXS3_H_ */
