// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/PythonFormatting.cpp
//! @brief     Implements functions from PythonFormatting namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PythonFormatting.h"
#include "Distributions.h"
#include "Ellipse.h"
#include "GISASSimulation.h"
#include "IInterferenceFunction.h"
#include "IShape2D.h"
#include "InfinitePlane.h"
#include "IParameterized.h"
#include "Line.h"
#include "Macros.h"
#include "MultiLayer.h"
#include "ParameterPool.h"
#include "Polygon.h"
#include "ExportToPython.h"
#include "RealParameter.h"
#include "Rectangle.h"
#include "Units.h"
#include "Utils.h"
#include <iomanip>
GCC_DIAG_OFF(missing-field-initializers)
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)

std::string PythonFormatting::genPyScript(GISASSimulation* simulation, const std::string& output_filename)
{
    simulation->prepareSimulation();
    std::unique_ptr<ISample> sample;
    if(simulation->getSample())
        sample.reset(simulation->getSample()->clone());
    else
        sample.reset(simulation->getSampleBuilder()->buildSample());
    MultiLayer* multilayer = dynamic_cast<MultiLayer*>(sample.get());
    ExportToPython visitor(*multilayer);
    std::ostringstream result;
    result << visitor.writePyScript(simulation, output_filename);
    return result.str();
}

std::string PythonFormatting::getRepresentation(const IDistribution1D* distribution)
{
     std::ostringstream result;
     result << std::setprecision(12);

     if     (const DistributionGate* d =
             dynamic_cast<const DistributionGate*>(distribution)) {
        result << "DistributionGate("
               << PythonFormatting::printDouble(d->getMin()) << ", "
               << PythonFormatting::printDouble(d->getMax()) << ")";
     }
     else if(const DistributionLorentz* d =
             dynamic_cast<const DistributionLorentz*>(distribution)) {
         result << "DistributionLorentz("
                << PythonFormatting::printDouble(d->getMean()) << ", "
                << PythonFormatting::printDouble(d->getHWHM()) << ")";
     }
     else if(const DistributionGaussian* d =
             dynamic_cast<const DistributionGaussian*>(distribution)) {
         result << "DistributionGaussian("
                << PythonFormatting::printDouble(d->getMean()) << ", "
                << PythonFormatting::printDouble(d->getStdDev()) << ")";
     }
     else if(const DistributionLogNormal* d =
             dynamic_cast<const DistributionLogNormal*>(distribution)) {
         result << "DistributionLogNormal("
                << PythonFormatting::printDouble(d->getMedian()) << ", "
                << PythonFormatting::printDouble(d->getScalePar()) << ")";
     }
     else if(const DistributionCosine* d =
             dynamic_cast<const DistributionCosine*>(distribution)) {
         result << "DistributionCosine("
                << PythonFormatting::printDouble(d->getMean()) << ", "
                << PythonFormatting::printDouble(d->getSigma()) << ")";
     }
     else {
         throw Exceptions::RuntimeErrorException(
            "PythonFormatting::getRepresentation(const IDistribution1D* distribution) "
            "-> Error. Unknown distribution type");
     }
     return result.str();
}

std::string PythonFormatting::getRepresentation(
    const std::string& indent, const Geometry::IShape2D* ishape, bool mask_value)
{     std::ostringstream result;
      result << std::setprecision(12);

    if(const Geometry::Ellipse* shape = dynamic_cast<const Geometry::Ellipse*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.Ellipse("
               << PythonFormatting::printDegrees(shape->getCenterX()) << ", "
               << PythonFormatting::printDegrees(shape->getCenterY()) << ", "
               << PythonFormatting::printDegrees(shape->getRadiusX()) << ", "
               << PythonFormatting::printDegrees(shape->getRadiusY());
        if(shape->getTheta() != 0.0) result << ", " << PythonFormatting::printDegrees(shape->getTheta());
        result << "), " << PythonFormatting::printBool(mask_value) << ")\n";
    }

    else if(const Geometry::Rectangle* shape = dynamic_cast<const Geometry::Rectangle*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.Rectangle("
               << PythonFormatting::printDegrees(shape->getXlow()) << ", "
               << PythonFormatting::printDegrees(shape->getYlow()) << ", "
               << PythonFormatting::printDegrees(shape->getXup()) << ", "
               << PythonFormatting::printDegrees(shape->getYup()) << "), "
               << PythonFormatting::printBool(mask_value) << ")\n";
    }

    else if(const Geometry::Polygon* shape = dynamic_cast<const Geometry::Polygon*>(ishape)) {
        std::vector<double> xpos, ypos;
        shape->getPoints(xpos, ypos);
        result << indent << "points = [";
        for(size_t i=0; i<xpos.size(); ++i) {
            result << "[" << PythonFormatting::printDegrees(xpos[i]) << ", " <<
                PythonFormatting::printDegrees(ypos[i]) << "]";
            if(i!= xpos.size()-1) result << ", ";
        }
        result << "]\n";
        result << indent << "simulation.addMask(" <<
            "ba.Polygon(points), " << PythonFormatting::printBool(mask_value) << ")\n";
    }

    else if(const Geometry::VerticalLine* shape =
            dynamic_cast<const Geometry::VerticalLine*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.VerticalLine("
               << PythonFormatting::printDegrees(shape->getXpos()) << "), "
               << PythonFormatting::printBool(mask_value) << ")\n";
    }

    else if(const Geometry::HorizontalLine* shape =
            dynamic_cast<const Geometry::HorizontalLine*>(ishape)) {
        result << indent << "simulation.addMask(";
        result << "ba.HorizontalLine("
               << PythonFormatting::printDegrees(shape->getYpos()) << "), "
               << PythonFormatting::printBool(mask_value) << ")\n";
    }

    else if(dynamic_cast<const Geometry::InfinitePlane*>(ishape)) {
        result << indent << "simulation.maskAll()\n";
    }
    return result.str();
}

std::string PythonFormatting::printBool(double value)
{
    return value ? "True" : "False";
}

std::string PythonFormatting::printDouble(double input)
{
    std::ostringstream inter;
    inter << std::setprecision(12);
    if (std::abs(input) < std::numeric_limits<double>::epsilon()) {
        inter << "0.0";
        return inter.str();
    }
    inter << input;
    if(inter.str().find('e') == std::string::npos && inter.str().find('.') == std::string::npos)
        inter << ".0";
    return inter.str();
}

std::string PythonFormatting::printNm(double input)
{
    std::ostringstream inter;
    inter << std::setprecision(12);
    inter << PythonFormatting::printDouble(input) << "*nm";
    return inter.str();
}

// 1.000000e+07 -> 1.0e+07
std::string PythonFormatting::printScientificDouble(double input)
{
    std::ostringstream inter;
    inter << std::scientific;
    inter << input;

    std::string::size_type pos = inter.str().find('e');
    if(pos == std::string::npos) return inter.str();

    std::string part1 = inter.str().substr(0, pos);
    std::string part2 = inter.str().substr(pos, std::string::npos);

    part1.erase(part1.find_last_not_of('0') + 1, std::string::npos);
    if(part1.back() == '.') part1 += "0";

    return part1+part2;
}

std::string PythonFormatting::printDegrees(double input)
{
    std::ostringstream inter;
    inter << std::setprecision(11);
    double in_degrees = input*180.0/M_PI;
    inter << in_degrees;
    if(inter.str().find('e') == std::string::npos && inter.str().find('.') == std::string::npos)
        inter << ".0";
    inter << "*deg";
    return inter.str();
}

bool PythonFormatting::isSquare(double length1, double length2, double angle)
{
    return length1==length2 && Numeric::areAlmostEqual(angle, Units::PI/2.0);
}

bool PythonFormatting::isHexagonal(double length1, double length2, double angle)
{
    return length1==length2 && Numeric::areAlmostEqual(angle, 2*Units::PI/3.0);
}

std::string PythonFormatting::printKvector(const kvector_t value)
{
    std::ostringstream result;
    result << "kvector_t(" << PythonFormatting::printDouble(value.x()) << ", "
           << PythonFormatting::printDouble(value.y()) << ", "
           << PythonFormatting::printDouble(value.z()) << ")";
    return result.str();
}

//! returns true if it is (0, -1, 0) vector
bool PythonFormatting::isDefaultDirection(const kvector_t direction)
{
    if( Numeric::areAlmostEqual(direction.x(),  0.0) &&
        Numeric::areAlmostEqual(direction.y(), -1.0) &&
        Numeric::areAlmostEqual(direction.z(),  0.0) )
        return true;
    return false;
}

//! Returns parameter value, followed by its unit multiplicator (like "* nm").

std::string PythonFormatting::valueTimesUnit(const RealParameter* par)
{
    if (par->unit()=="rad")
        return PythonFormatting::printDegrees(par->getValue());
    return PythonFormatting::printDouble(par->getValue()) + ( par->unit()=="" ? "" : ("*"+par->unit()) );
}

//! Returns comma-separated list of parameter values, including unit multiplicator (like "* nm").

std::string PythonFormatting::argumentList(const IParameterized* ip)
{
    std::vector<std::string> args;
    for(const auto* par: ip->getParameterPool()->getParameters())
        args.push_back( valueTimesUnit(par) );
    return Utils::String::join( args, ", " );
}
