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
#include "TiffHandler.h"
#include "Exceptions.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <sstream>
#include <tiffio.h>
#include <tiffio.hxx>

namespace {
size_t supported_bitPerSample = 32;
size_t supported_samplesPerPixel = 1;
size_t size_of_int = 4;
}

TiffHandler::TiffHandler()
    : m_tiff(0)
    , m_width(0)
    , m_height(0)
{

}

TiffHandler::~TiffHandler()
{
    close();
}

void TiffHandler::read(const std::string &file_name)
{
    open(file_name);

    read_header();
    read_data();

    close();
}

void TiffHandler::read(std::istream &input_stream)
{
//    close();
    std::cout << "opening stream" << std::endl;
    m_tiff = TIFFStreamOpen("MemTIFF", &input_stream);
    read_header();
    read_data();
    close();
}

const OutputData<double> *TiffHandler::getOutputData() const
{
    return m_data.get();
}

void TiffHandler::open(const std::string &file_name)
{
//    close();

    m_tiff = TIFFOpen(file_name.c_str(), "r");
    if(!m_tiff) {
        throw FileNotIsOpenException("TiffHandler::open() -> Error. Can't open file '"
                                     + file_name + "' for reading.");
    }

}

void TiffHandler::read_header()
{
    assert(m_tiff);
    uint32 width(0);
    uint32 height(0);
    uint16 photometric(0);
    if (!TIFFGetField(m_tiff, TIFFTAG_IMAGEWIDTH, &width)
        || !TIFFGetField(m_tiff, TIFFTAG_IMAGELENGTH, &height)
        || !TIFFGetField(m_tiff, TIFFTAG_PHOTOMETRIC, &photometric)) {
        throw FormatErrorException("TiffHandler::read_header() -> Error. "
                                   "Can't read width/height/photometric info.");
    }

    m_width = (size_t) width;
    m_height = (size_t) height;

    uint16 orientationTag(0);
    TIFFGetField(m_tiff, TIFFTAG_ORIENTATION, &orientationTag);

    // BitsPerSample defaults to 1 according to the TIFF spec.
    uint16 bitPerSample(0);
    if (!TIFFGetField(m_tiff, TIFFTAG_BITSPERSAMPLE, &bitPerSample))
        bitPerSample = 1;
    uint16 samplesPerPixel(0); // they may be e.g. grayscale with 2 samples per pixel
    if (!TIFFGetField(m_tiff, TIFFTAG_SAMPLESPERPIXEL, &samplesPerPixel))
        samplesPerPixel = 1;

    std::cout << "width:" << m_width
              << " m_height:" << m_height
              << " orientationTag:" << orientationTag
              << " m_photometric:" << photometric
              << " bitPerSample:" << bitPerSample
              << " samplePerPixel:" << samplesPerPixel
              << std::endl;

    if(bitPerSample!= supported_bitPerSample ||
            samplesPerPixel != supported_samplesPerPixel) {
        std::ostringstream message;
        message << "TiffHandler::read_header() -> Error. "
                << "Can't read tiff image with following parameters:" << std::endl
                << "    TIFFTAG_PHOTOMETRIC: " << photometric << std::endl
                << "    TIFFTAG_BITSPERSAMPLE: " << bitPerSample << std::endl
                << "    TIFFTAG_SAMPLESPERPIXEL: " << samplesPerPixel << std::endl;
        throw FormatErrorException(message.str());
    }

}

void TiffHandler::read_data()
{
    assert(m_tiff);

    tmsize_t buf_size = TIFFScanlineSize(m_tiff);
    tmsize_t expected_size = size_of_int*m_width;
    if(buf_size != expected_size) {
        throw FormatErrorException("TiffHandler::read_data() -> Error. Wrong scanline size.");
    }
    tdata_t buf = _TIFFmalloc(buf_size);
    if(!buf) {
        throw FormatErrorException("TiffHandler::read_data() -> Error. Can't allocate buffer.");
    }

    create_output_data();

    std::vector<int> line_buf;
    line_buf.resize(m_width, 0);
    std::vector<int> axes_indices(2);
    for (uint32 row = 0; row < (uint32) m_height; row++) {
        if(TIFFReadScanline(m_tiff, buf, row) < 0) {
            throw FormatErrorException("TiffHandler::read_data() -> Error. Error in scanline.");
        }
        memcpy(&line_buf[0], buf, buf_size);
        for(size_t col=0; col<line_buf.size(); ++col) {
//            std::cout << "row:" << row << " col:" << col << " " << line_buf[col] << std::endl;
            axes_indices[0] = col;
            axes_indices[1] = m_height - 1 - row;
            size_t global_index = m_data->toGlobalIndex(axes_indices);
            (*m_data)[global_index] = (double)line_buf[col];
        }
    }
    _TIFFfree(buf);
}

void TiffHandler::close()
{
    if(m_tiff) {
        TIFFClose(m_tiff);
        m_tiff = 0;
        m_width = 0;
        m_height = 0;
    }
}

void TiffHandler::create_output_data()
{
    assert(m_tiff);
    m_data.reset(new OutputData<double>);
    m_data->addAxis("x", m_width, 0.0, double(m_width));
    m_data->addAxis("y", m_height, 0.0, double(m_height));
}



