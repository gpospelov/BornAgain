// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/src/TiffReadStrategy.cpp
//! @brief     Implements class TiffReadStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "TiffReadStrategy.h"
#include "Exceptions.h"
#include "TiffHandler.h"
#include <fstream>
#include <cassert>
#include <iostream>



TiffReadStrategy::TiffReadStrategy()
    : m_d(new TiffHandler)
{

}

TiffReadStrategy::~TiffReadStrategy()
{
    delete m_d;
}

//void TiffReadStrategy::read(const std::string &file_name)
//{
//    std::cout << "TiffReadStrategy::read() -> Info" << std::endl;

//    m_d->read(file_name);
//}


void TiffReadStrategy::read(const std::string &file_name)
{
    std::cout << "TiffReadStrategy::read() -> Info" << std::endl;


    std::ifstream fin;

    std::ios_base::openmode openmode = std::ios::in | std::ios_base::binary;

    fin.open(file_name.c_str(), openmode );
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("TiffReadStrategy::read() -> Error. Can't open file '"
                                     + file_name + "' for reading.");
    }
    if ( !fin.good() ) {
        throw FileIsBadException("OutputDataReader::getOutputData() -> Error! File is not good, "
                                 "probably it is a directory.");
    }

    m_d->read(fin);

    fin.close();
}

void TiffReadStrategy::read(std::istream &input_stream)
{
    m_d->read(input_stream);
}

OutputData<double> *TiffReadStrategy::readOutputData(std::istream &input_stream)
{
    m_d->read(input_stream);
    return m_d->getOutputData()->clone();
}


//void TiffReadStrategy::read(std::istream &input_stream)
//{

////    TIFF* mem_TIFF = TIFFStreamOpen("MemTIFF", &input_stream);

////    TIFFClose(mem_TIFF);
//}
