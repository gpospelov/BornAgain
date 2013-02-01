#include "OutputDataWriteStrategy.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

/* ************************************************************************* */
// read data from ASCII file (2D assumed) and fill newly created OutputData with it
/* ************************************************************************* */
void OutputDataWriteStreamIMA::writeOutputData(const OutputData<double> &data, std::ostream &output_stream)
{
    size_t row_length = data.getAxis(1)->getSize();
    OutputData<double>::const_iterator it = data.begin();
    while(it != data.end()) {
        double z_value = *it++;
        output_stream << std::scientific << std::setprecision(m_precision) << z_value << "    ";
        if(it.getIndex()%row_length==0) output_stream << std::endl;
    }
}
