// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/TiffHandler.h
//! @brief     Defines class TiffHandler.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TIFFHANDLER_H
#define TIFFHANDLER_H

#include "WinDllMacros.h"
#include "OutputData.h"
#include <string>
#include <tiffio.h>
#include <tiffio.hxx>
#include <boost/scoped_ptr.hpp>

//! @class TiffHandler
//! @ingroup input_output
//! @brief Reads/write tiff files, should be used through TiffReadStrategy

class BA_CORE_API_ TiffHandler
{
public:
    TiffHandler();
    ~TiffHandler();

    void read(const std::string &file_name);
    void read(std::istream& input_stream);

    const OutputData<double> *getOutputData() const;

private:
    void open(const std::string &file_name);
    void read_header();
    void read_data();
    void close();
    void create_output_data();
    std::vector<int> get_int_vector();

    TIFF *m_tiff;
    size_t m_width;
    size_t m_height;
    boost::scoped_ptr<OutputData<double> > m_data;
};


#endif

