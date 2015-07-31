// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/BornAgainNamespace.h
//! @brief     Defines BornAgain namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef BORNAGAINNAMESPACE_H
#define BORNAGAINNAMESPACE_H

#include<string>

namespace BornAgain
{
    static const std::string PHI_AXIS_NAME = "phi_f";
    static const std::string ALPHA_AXIS_NAME = "alpha_f";

    const std::string FTDistribution2DCauchyType = "FTDistribution2DCauchy";
    const std::string FTDistribution2DGaussType = "FTDistribution2DGauss";
    const std::string FTDistribution2DGateType = "FTDistribution2DGate";
    const std::string FTDistribution2DConeType = "FTDistribution2DCone";
    const std::string FTDistribution2DVoigtType = "FTDistribution2DVoigt";

    const std::string AnisoPyramidType = "AnisoPyramid";
    const std::string BoxType = "Box";
    const std::string ConeType = "Cone";
    const std::string Cone6Type = "Cone6";
    const std::string CuboctahedronType = "Cuboctahedron";
    const std::string CylinderType = "Cylinder";
    const std::string EllipsoidalCylinderType = "EllipsoidalCylinder";
    const std::string FullSphereType = "FullSphere";
    const std::string FullSpheroidType = "FullSpheroid";
    const std::string HemiEllipsoidType = "HemiEllipsoid";
    const std::string Prism3Type = "Prism3";
    const std::string Prism6Type = "Prism6";
    const std::string PyramidType = "Pyramid";
    const std::string Ripple1Type = "Ripple1";
    const std::string Ripple2Type = "Ripple2";
    const std::string TetrahedronType = "Tetrahedron";
    const std::string TruncatedCubeType = "TruncatedCube";
    const std::string TruncatedSphereType = "TruncatedSphere";
    const std::string TruncatedSpheroidType = "TruncatedSpheroid";
}

#endif // BORNAGAINNAMESPACE_H


