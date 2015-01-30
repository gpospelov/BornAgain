// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/IsGISAXSData.cpp
//! @brief     Implements class IsGISAXSData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXSData.h"
#include "BornAgainNamespace.h"
#include <iostream>
#include <fstream>

//! Read isgisaxs *.dat file which holds experimental data scans for fit.

void IsGISAXSData::read_datfile(const std::string& filename, DataSet_t& dataset)
{
    dataset.clear();

    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    std::vector<IsgiData > isgiScan;

    std::string sline;
    int n_dataset_line(0);
    while( std::getline(fin, sline))
    {
        //std::cout << sline << std::endl;
        std::string::size_type pos=sline.find("################################################");
        if( pos!= std::string::npos ) {
            n_dataset_line = 0; // it's a beginning of new data set ("cross-section" in isgisaxs terminology)
            if( !isgiScan.empty() ) {
                OutputData<double > *data = convert_isgi_scan(isgiScan);
                dataset.push_back(data);
                isgiScan.clear();
            }
        }
        if(n_dataset_line > 9) {
            // not a header, parsing records
            std::istringstream iss(sline.c_str());
            IsgiData isgiData;
            char ctmp;
            if ( !(iss >> ctmp >> isgiData.phif >> isgiData.alphaf >> isgiData.intensity) ) throw FormatErrorException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error!");
            iss >> isgiData.err; // column with errors can be absent in file, so no check for success here
            ctmp == 'T' ? isgiData.use_it = true : isgiData.use_it = false;
            isgiData.phif = std::asin(isgiData.phif); // because isgisax in fact stores in *.dat file sin(phif), and sin(alphaf) instead of phif, alphaf
            isgiData.alphaf = std::asin(isgiData.alphaf);  // because isgisax in fact stores in *.dat file sin(phif), and sin(alphaf) instead of phif, alphaf
            isgiScan.push_back(isgiData);
        }

        n_dataset_line++;
    }
    if ( fin.bad() ) {
        throw FileIsBadException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error! File is bad after readline(), probably it is a directory.");
    }
    fin.close();
}

//! Read special isgisaxs *.out file with isgisaxs adjusted data and fit results

//! if read_fit_results == false, then it loads isgisaxs data to fit
//! if read_fit_results == true, then it loads isgisaxs fit results
//!
void IsGISAXSData::read_outfile(const std::string& filename, DataSet_t& dataset, EItemToRead item)
{
    dataset.clear();

    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    std::vector<IsgiData > isgiScan;

    std::string sline;
    while( std::getline(fin, sline))
    {
        std::string::size_type pos=sline.find("# Cut # =");
        if( pos!= std::string::npos ) {
            //std::cout << "beginning of one dataset " << isgiScan.size() << std::endl;
            if( !isgiScan.empty() ) {
                OutputData<double > *data = convert_isgi_scan(isgiScan);
                dataset.push_back(data);
                isgiScan.clear();
            }
        } else if (sline[0] != '#' && sline.size() >2){
            // not a header, parsing records
            std::istringstream iss(sline.c_str());
            IsgiData isgiData;

            vdouble1d_t buff;
            std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(), back_inserter(buff));
            if( buff.size() != FITTED+1) {
                throw LogicErrorException("TestIsGISAXS12::read_isgisaxs_outfile -> Error! Line doesn't have enough double numbers. Not an *.out file? Line '"+sline+"'");
            }

            isgiData.phif = std::asin(buff[SIN_TWO_THETA]);
            isgiData.alphaf = std::asin(buff[SIN_ALPHA_F]);
            isgiData.intensity = buff[item];

            isgiScan.push_back(isgiData);
        }
    }
    if ( fin.bad() ) {
        throw FileIsBadException("TestIsGISAXS12::read_isgisaxs_datfile() -> Error! File is bad after readline(), probably it is a directory.");
    }
    fin.close();

    if( !isgiScan.empty() ) {
        OutputData<double > *data = convert_isgi_scan(isgiScan);
        dataset.push_back(data);
        isgiScan.clear();
    }
}

//! Convert isgisaxs 1d scan to output data 2d object.

OutputData<double> *IsGISAXSData::convert_isgi_scan(std::vector<IsgiData >& /* isgi_data */)
{
    throw Exceptions::NotImplementedException("IsGISAXSData::convert_isgi_scan");
//    if(isgi_data.size() <2 ) throw LogicErrorException("TestIsGISAXS12::convert_isgi_scan() -> Error! Too short vector.");

//    // check if it is scan with fixed phi_f or with fixed alpha_f
//    bool fixed_phif(true);
//    bool fixed_alphaf(true);
//    // if values of phif accross data points are chainging, then phif is not fixed
//    for(size_t i_point=0; i_point<isgi_data.size()-1; ++i_point) {
//        if( isgi_data[i_point].phif != isgi_data[i_point+1].phif ) {
//            fixed_phif = false;
//            break;
//        }
//    }
//    // if values of alphaf accross data points are chainging, then alphaf is not fixed
//    for(size_t i_point=0; i_point<isgi_data.size()-1; ++i_point) {
//        if( isgi_data[i_point].alphaf != isgi_data[i_point+1].alphaf ) {
//            fixed_alphaf = false;
//            break;
//        }
//    }
//    if(fixed_phif == fixed_alphaf)
//        throw LogicErrorException(
//            "TestIsGISAXS12::convert_isgi_scan() -> "
//            "Error! Scan can't have both angle phif,alphaf fixed");

//    AxisDouble phi_axis(BornAgain::PHI_AXIS_NAME);
//    AxisDouble alpha_axis(BornAgain::ALPHA_AXIS_NAME);
//    if( fixed_phif) {
//        //m_isgi_fixed_phif = isgi_data.back().phif;
//        phi_axis.push_back(isgi_data.back().phif);
//        std::cout << "fixed phi " << isgi_data.back().phif << std::endl;
//        for(size_t i_point=0; i_point<isgi_data.size(); ++i_point) {
//            alpha_axis.push_back(isgi_data[i_point].alphaf);
//        }
//    } else {
//        //m_isgi_fixed_alphaf = isgi_data.back().alphaf;
//        alpha_axis.push_back(isgi_data.back().alphaf);
//        for(size_t i_point=0; i_point<isgi_data.size(); ++i_point) {
//            phi_axis.push_back(isgi_data[i_point].phif);
//        }
//    }
//    OutputData<double> *data = new OutputData<double >;
//    data->addAxis(phi_axis);
//    data->addAxis(alpha_axis);
//    data->setAllTo(0.0);
//    OutputData<double>::iterator it = data->begin();
//    int i_point(0);
//    while( it!= data->end()) {
//        (*it) = isgi_data[i_point].intensity;
//        ++i_point;
//        ++it;
//    }
//    return data;
}


