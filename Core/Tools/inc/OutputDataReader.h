// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/OutputDataReader.h
//! @brief     Defines class OutputDataReader.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef OUTPUTDATAREADER_H
#define OUTPUTDATAREADER_H

#include "WinDllMacros.h"
#include <string>
#include <vector>

template <class T> class OutputData;
class IOutputDataReadStrategy;


//! @class OutputDataReader
//! @ingroup tools
//! @brief Reads OutputData from file using different reading strategies.

class BA_CORE_API_ OutputDataReader
{
public:
    enum CompressionType {UNCOMPRESSED, GZIP, BZIP2};

    OutputDataReader() : m_read_strategy(0) {}
    OutputDataReader(const std::string& file_name);
    OutputDataReader(IOutputDataReadStrategy *read_strategy);
    virtual ~OutputDataReader();

    //! read output data from file (file name was set already from OutputDataIOFactory)
    OutputData<double > *getOutputData();

    //! Sets concrete reading strategy
    void setStrategy(IOutputDataReadStrategy *read_strategy);
    void setCompression(CompressionType compressionType);
    void setBinaryFlag(bool value);

private:
    std::vector<char> readBuffer(std::istream &input_stream);

    std::string m_file_name;
    IOutputDataReadStrategy *m_read_strategy;
    CompressionType m_compressionType;
    bool m_is_binary;
};

#endif // OUTPUTDATAREADER_H


