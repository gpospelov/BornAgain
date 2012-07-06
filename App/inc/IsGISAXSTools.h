#ifndef ISGISAXSTOOLS_H_
#define ISGISAXSTOOLS_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IsGISAXSTools.h
//! @brief  Definition of functions and classes for IsGISAXS validation
//! @author herck
//! @date   19.06.2012
#include "OutputData.h"

#include <string>

namespace IsGISAXSTools {

//! draw 2D histogram representing OutputData (in new canvas)
void drawLogOutputData(const OutputData<double> &output, const std::string &canvas_name,
        const std::string &canvas_title, const std::string &draw_options,
        const std::string &histogram_title = std::string());

//! draw 2D histogram representing OutputData (in current gPad)
void drawLogOutputDataInCurrentPad(const OutputData<double> &output, const std::string &draw_options, const std::string &histogram_title = std::string());

//! write output data (1D or 2D) in ASCII file
void writeOutputDataToFile(const OutputData<double> &output, const std::string &filename);

//! read data from ASCII file (2D assumed) and fill newly created OutputData with it
OutputData<double> *readOutputDataFromFile(const std::string &filename);


} /* namespace IsGISAXS Tools */

#endif /* ISGISAXSTOOLS_H_ */
