// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/IsGISAXSData.h
//! @brief     Defines class IsGISAXSData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXSDATA_H
#define ISGISAXSDATA_H


#include "OutputData.h"
#include "SafePointerVector.h"
#include <vector>

//! Collection of tools for reading isgisaxs files *.dat, *.out

class IsGISAXSData
{
public:
    typedef SafePointerVector<OutputData<double> >  DataSet_t;
    enum EItemToRead { SIN_TWO_THETA, SIN_ALPHA_F, QX, QY, QZ,
                      SIM_RESULT, DATA_TO_FIT, ERROR_BAR, I_OBS_I_CALC, FITTED };

    IsGISAXSData(){}
    ~IsGISAXSData(){}

    //! Represent single line stored in isgisaxs *.dat file with data to fit.
    class IsgiData {
    public:
        IsgiData() : use_it(true), phif(0), alphaf(0), intensity(0), err(0) {}
        bool use_it; double phif; double alphaf; double intensity; double err;
    };

    //! Read isgisaxs *.dat file which holds experimental data scans for fit.
    static void read_datfile(const std::string& filename, DataSet_t& dataset);

    //! Read special isgisaxs *.out file with isgisaxs fit results.
    static void read_outfile(const std::string& filename, DataSet_t& dataset,
                             EItemToRead item = DATA_TO_FIT);

private:
    //! Convert isgisaxs 1d scan to output data 2d object.
    static OutputData<double> *convert_isgi_scan(
        std::vector<IsgiData >& isgi_data);

};

#endif // ISGISAXSData_H


