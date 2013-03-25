// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/IsGISAXSData.h 
//! @brief     Defines class IsGISAXSData.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
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
    enum ItemToRead { kSin_twotheta, kSin_alphaf, kQx, kQy, kQz,
                      kSimResult, kData2fit, kErrorbar, kIobs_Icalc, kFitted };

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
    static void read_outfile(const std::string& filename, DataSet_t& dataset, ItemToRead item = kData2fit);

private:
    //! Convert isgisaxs 1d scan to output data 2d object.
    static OutputData<double> *convert_isgi_scan(
        std::vector<IsgiData >& isgi_data);

};

#endif // ISGISAXSData_H
