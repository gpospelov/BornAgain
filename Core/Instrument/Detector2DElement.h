// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/Detector2DElement.h
//! @brief     Defines class Detector2DElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTOR2DELEMENT_H
#define DETECTOR2DELEMENT_H

#include "EigenCore.h"
#include <memory>

class IPixel;

//! Data stucture containing input elements of detector cells.
//! @ingroup simulation

class Detector2DElement
{
public:
    Detector2DElement(std::unique_ptr<IPixel> P_pixel);

#ifndef SWIG
    //! Sets the polarization analyzer operator (in spin basis along z-axis)
    void setAnalyzerOperator(const Eigen::Matrix2cd& analyzer_operator) {
        m_analyzer_operator = analyzer_operator; }

    //! Gets the polarization analyzer operator (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const { return m_analyzer_operator; }
#endif
private:
    void initAnalyzerOperator();
#ifndef SWIG
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
#endif
    std::unique_ptr<IPixel> mP_pixel;
};

#endif // DETECTOR2DELEMENT_H
