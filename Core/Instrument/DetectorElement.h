// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectorElement.h
//! @brief     Defines class DetectorElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DETECTORELEMENT_H
#define DETECTORELEMENT_H

#include "EigenCore.h"
#include <memory>

class IPixel;

//! Data stucture containing input elements of detector cells.
//! @ingroup simulation

class DetectorElement
{
public:
    DetectorElement(IPixel* p_pixel, Eigen::Matrix2cd analyzer_operator);

    void setSpecular(bool specular=true);
    bool isSpecular() const;

    //! Gets the polarization analyzer operator (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const { return m_analyzer_operator; }

    //! Gets the pixel information
    std::unique_ptr<IPixel> pixel() const;

private:
    bool m_specular;
    std::unique_ptr<IPixel> mP_pixel;
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
};

#endif // DETECTORELEMENT_H
