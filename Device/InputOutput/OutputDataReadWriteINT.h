//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/InputOutput/OutputDataReadWriteINT.h
//! @brief     Declares OutputDataReadWriteINT
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITEINT_H
#define BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITEINT_H

#include <istream>

template <class T> class OutputData;

//! Class for reading and writing BornAgain native IntensityData from ASCII file.
//! @ingroup input_output_internal

class OutputDataReadWriteINT {
public:
    OutputData<double>* readOutputData(std::istream& input_stream);
    void writeOutputData(const OutputData<double>& data, std::ostream& output_stream);

private:
    void writeOutputDataDoubles(const OutputData<double>& data, std::ostream& output_stream,
                                size_t n_columns);
    double ignoreDenormalized(double value) const;

    const int m_precision = 12;
};

#endif // BORNAGAIN_DEVICE_INPUTOUTPUT_OUTPUTDATAREADWRITEINT_H
