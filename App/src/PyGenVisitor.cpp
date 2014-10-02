#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include "Exceptions.h"
#include "FormFactors.h"
#include "InterferenceFunctions.h"
#include "IMaterial.h"
#include "ICompositeSample.h"
#include "Layer.h"
#include "LabelSample.h"
#include "LayerInterface.h"
#include "ParticleBuilder.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "ParticleCoreShell.h"
#include "ParticleInfo.h"
#include "PositionParticleInfo.h"
#include "ParticleLayout.h"
#include "PyGenVisitor.h"
#include "TestPyGenerator.h"
#include "Transform3D.h"

PyGenVisitor::PyGenVisitor()
    : m_label(new LabelSample())
{

}

std::string PyGenVisitor::genPyScript(const Simulation *simulation, std::string fileName = "")
{
    std::ostringstream result;
    result << "import numpy \nimport matplotlib \nimport pylab \nfrom libBornAgainCore import *\n\n";
    result << "#NOTE: All the ANGLES are displayed in RADIANS\n\n";
    result << "def getSample():\n\t# Defining Materials\n";
    std::map<const IMaterial *,std::string>::iterator it1 = m_label->getMaterialMap()->begin();
    while (it1 != m_label->getMaterialMap()->end())
    {
        if (visitedMaterials.find(it1->second) == visitedMaterials.end())
        {
            visitedMaterials.insert(it1->second);
            const IMaterial *material = it1->first;
            complex_t ri = material->getRefractiveIndex();
            double delta = 1-real(ri);
            double beta = imag(ri);
            result << "\t" << m_label->getLabel(material) << " = HomogeneousMaterial(\"" << material->getName();
            result << "\"," << printDouble(delta) << "," << printDouble(beta) << ")\n";
        }
        it1++;
    }

    result << "\n\t# Defining Layers\n";
    std::map<const Layer *,std::string>::iterator it2 = m_label->getLayerMap()->begin();
    while (it2 != m_label->getLayerMap()->end())
    {
        const Layer *layer = it2->first;
        result << "\t" << it2->second << " = Layer(" << m_label->getLabel(layer->getMaterial());
        if (layer->getThickness() != 0)
        {
            result << "," << layer->getThickness();
        }
        result << ")\n";
        it2++;
    }

    if (m_label->getParticleMap()->size() != 0)
    {
        result << "\n\t# Defining Form Factors and Particles\n";
    }

    int formFactorNotFound =0;
    std::map<const IFormFactor *,std::string>::iterator it3 = m_label->getFormFactorMap()->begin();
    while (it3 != m_label->getFormFactorMap()->end())
    {
        result << "\t" << it3->second;
        const IFormFactor *iFormFactor = it3->first;

        if (const FormFactorAnisoPyramid *anisoPyramid = dynamic_cast<const FormFactorAnisoPyramid *>(iFormFactor))
        {
            result << " = FormFactorAnisoPyramid(" << anisoPyramid->getLength() << "*nanometer,"
            << anisoPyramid->getWidth() << "*nanometer," << anisoPyramid->getHeight() << "*nanometer,"
            << anisoPyramid->getAlpha() << ")\n";
        }

        else if (const FormFactorBox *box = dynamic_cast<const FormFactorBox *>(iFormFactor))
        {
            result << " = FormFactorBox(" << box->getLength() << "*nanometer,"
            << box->getWidth()<< "*nanometer," << box->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorCone *cone = dynamic_cast<const FormFactorCone *>(iFormFactor))
        {
            result << " = FormFactorCone(" << cone->getRadius() << "*nanometer," << cone->getHeight()
            << "*nanometer," << cone->getAlpha() << ")\n";
        }

        else if (const FormFactorCone6 *cone6 = dynamic_cast<const FormFactorCone6 *>(iFormFactor))
        {
            result << " = FormFactorCone6(" << cone6->getRadius() << "*nanometer," << cone6->getHeight()
            << "*nanometer," << cone6->getAlpha() << ")\n";
        }

        else if (const FormFactorCuboctahedron *cuboctahedron = dynamic_cast<const FormFactorCuboctahedron *>(iFormFactor))
        {
            result << " = FormFactorCuboctahedron(" << cuboctahedron->getLength() << "*nanometer,"
            << cuboctahedron->getHeight() << "*nanometer," << cuboctahedron->getHeightRatio() << "*nanometer"
            << cuboctahedron->getAlpha() << ")\n";
        }

        else if (const FormFactorCylinder *cylinder = dynamic_cast<const FormFactorCylinder *>(iFormFactor))
        {
            result << " = FormFactorCylinder(" << cylinder->getHeight() << "*nanometer,"
            << cylinder->getRadius() << "*nanometer)\n";
        }

        else if (const FormFactorEllipsoidalCylinder *ellipsoidalCylinder = dynamic_cast<const FormFactorEllipsoidalCylinder *>(iFormFactor))
        {
            result << " = FormFactorEllipsoidalCylinder(" << ellipsoidalCylinder->getRadiusA()
            << "*nanometer," << ellipsoidalCylinder->getRadiusB() << "*nanometer,"
            << ellipsoidalCylinder->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorFullSphere *fullSphere = dynamic_cast<const FormFactorFullSphere *>(iFormFactor))
        {
            result << " = FormFactorFullSphere(" << fullSphere->getRadius() << "*nanometer)\n";
        }

        else if (const FormFactorFullSpheroid *fullSpheroid = dynamic_cast<const FormFactorFullSpheroid *>(iFormFactor))
        {
            result << " = FormFactorFullSpheroid(" << fullSpheroid->getRadius() << "*nanometer,"
            << fullSpheroid->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorGauss *gauss = dynamic_cast<const FormFactorGauss *>(iFormFactor))
        {
            if(gauss->getRadius() == gauss->getHeight())
            {
                result << " = FormFactorGauss(" << gauss->getVolume() << "*(nanometer)**3)\n";
            }
            else
            {
                result << " = FormFactorGauss(" << gauss->getRadius() << "*nanometer,"
                << gauss->getHeight() << "*nanometer)\n";
            }
        }

        else if (const FormFactorHemiEllipsoid *hemiEllipsoid = dynamic_cast<const FormFactorHemiEllipsoid *>(iFormFactor))
        {
            result << " = FormFactorHemiEllipsoid(" << hemiEllipsoid->getRadiusA() << "*nanometer,"
            << hemiEllipsoid->getRadiusB() << "*nanometer," << hemiEllipsoid->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorInfLongBox *infLongBox = dynamic_cast<const FormFactorInfLongBox *>(iFormFactor))
        {
            result << " = FormFactorInfLongBox(" << infLongBox->getWidth() << "*nanometer,"
            << infLongBox->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorInfLongRipple1 *infLongRipple1 = dynamic_cast<const FormFactorInfLongRipple1 *>(iFormFactor))
        {
            result << " = FormFactorInfLongRipple1(" << infLongRipple1->getWidth() << "*nanometer,"
            << infLongRipple1->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorInfLongRipple2 *infLongRipple2 = dynamic_cast<const FormFactorInfLongRipple2 *>(iFormFactor))
        {
            result << " = FormFactorInfLongRipple2(" << infLongRipple2->getWidth() << "*nanometer,"
            << infLongRipple1->getHeight() << "*nanometer," << infLongRipple2->getAsymetry() << "*nanometer)\n";
        }

        else if (const FormFactorLorentz *lorentz = dynamic_cast<const FormFactorLorentz *>(iFormFactor))
        {
            if(lorentz->getRadius() == lorentz->getHeight())
            {
                result << " = FormFactorLorentz(" << lorentz->getVolume() << "*(nanometer)**3)\n";
            }
            else
            {
                result << " = FormFactorLorentz(" << lorentz->getRadius() << "*nanometer,"
                << lorentz->getHeight() << "*nanometer)\n";
            }
        }

        else if (const FormFactorPrism3 *prism3 = dynamic_cast<const FormFactorPrism3 *>(iFormFactor))
        {
            result << " = FormFactorPrism3(" << prism3->getLength() << "*nanometer,"
            << prism3->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorPrism6 *prism6 = dynamic_cast<const FormFactorPrism6 *>(iFormFactor))
        {
            result << " = FormFactorPrism6(" << prism6->getRadius() << "*nanometer,"
            << prism6->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorPyramid *pyramid = dynamic_cast<const FormFactorPyramid *>(iFormFactor))
        {
            result << " = FormFactorPyramid(" << pyramid->getLength() << "*nanometer," <<
            pyramid->getHeight() << "*nanometer," << pyramid->getAlpha() << ")\n";
        }

        else if (const FormFactorRipple1 *ripple1 = dynamic_cast<const FormFactorRipple1 *>(iFormFactor))
        {
            result << " = FormFactorRipple1(" << ripple1->getLength() << "*nanometer," <<
            ripple1->getWidth() << "*nanometer," << ripple1->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorRipple2 *ripple2 = dynamic_cast<const FormFactorRipple2 *>(iFormFactor))
        {
            result << " = FormFactorRipple2(" << ripple2->getLength() << "*nanometer," <<
            ripple2->getWidth() << "*nanometer," << ripple2->getHeight() << "nanometer," <<
            ripple2->getAsymmetry() << "*nanometer)\n";
        }

        else if (const FormFactorTetrahedron *tetrahedron = dynamic_cast<const FormFactorTetrahedron *>(iFormFactor))
        {
            result << " = FormFactorTetrahedron(" << tetrahedron->getLength() << "*nanometer," <<
            tetrahedron->getHeight() << "*nanometer," << tetrahedron->getAlpha() << ")\n";
        }

        else if (const FormFactorTruncatedSphere *truncatedSphere = dynamic_cast<const FormFactorTruncatedSphere *>(iFormFactor))
        {
            result << " = FormFactorTruncatedSphere(" << truncatedSphere->getRadius() << "*nanometer,"
            << truncatedSphere->getHeight() << "*nanometer)\n";
        }

        else if (const FormFactorTruncatedSpheroid *truncatedSpheroid = dynamic_cast<const FormFactorTruncatedSpheroid *>(iFormFactor))
        {
            result << " = FormFactorTruncatedSpheroid(" << truncatedSpheroid->getRadius() << "*nanometer,"
            << truncatedSpheroid->getHeight() << "*nanometer," << truncatedSpheroid->getHeightFlattening()
            << "*nanometer)\n";
        }

        else
        {
            // I should give proper Exception here
            std::cout << "\n" << formFactorNotFound << ": " << iFormFactor->getName()
            << "Not Casted To Any FormFactor\n";
            formFactorNotFound++;
        }
        it3++;
    }

    std::map<const Particle *,std::string>::iterator it4 = m_label->getParticleMap()->begin();
    while (it4 != m_label->getParticleMap()->end())
    {
        const Particle *particle = it4->first;
        if(particle->getPTransform3D())
        {
            double alpha, beta, gamma;
            particle->getPTransform3D()->calculateEulerAngles(&alpha, &beta, &gamma);
            switch (particle->getPTransform3D()->getRotationType()) {
            case 1:
                result << "\tGeometry::Transform3D " << it4->second << "_rotation = Geometry::Transform3D::createRotateX("
                << beta << ")\n";
                break;
            case 2:
                result << "\tGeometry::Transform3D " << it4->second << "_rotation = Geometry::Transform3D::createRotateY("
                << gamma << ")\n";
                break;
            case 3:
                result << "\tGeometry::Transform3D " << it4->second << "_rotation = Geometry::Transform3D::createRotateZ("
                << alpha << ")\n";
                break;
            default:
                break;
            }
        }
        result << "\t" << it4->second << " = Particle(" << m_label->getLabel(particle->getMaterial())
        << "," << m_label->getLabel(particle->getSimpleFormFactor());
        if (particle->getPTransform3D())
        {
            result << "," << it4->second << "_rotation";
        }
        result << ")\n";
        it4++;
    }

    if (m_label->getInterferenceFunctionMap()->size() != 0)
    {
        result << "\n\t# Defining Interference functions\n";
    }

    int interfernceFunctionNotFound =0;
    std::map<const IInterferenceFunction *,std::string>::iterator it = m_label->getInterferenceFunctionMap()->begin();
    while (it != m_label->getInterferenceFunctionMap()->end())
    {
        result << "\t" << it->second;
        const IInterferenceFunction *iInterferenceFunction = it->first;

        if (const InterferenceFunctionNone *none = dynamic_cast<const InterferenceFunctionNone *>(iInterferenceFunction))
        {
            result << " = InterferenceFunctionNone()\n";
        }

        else if (const InterferenceFunction1DLattice *oneDLattice = dynamic_cast<const InterferenceFunction1DLattice *>(iInterferenceFunction))
        {
            const Lattice1DIFParameters latticeParameters = oneDLattice->getLatticeParameters();
            result << " = InterferenceFunction1DLattice(" << printDouble(latticeParameters.m_length) << "," << printDouble(latticeParameters.m_xi) << ")\n";

            const IFTDistribution1D *pdf =  oneDLattice->getProbabilityDistribution();

            if (const FTDistribution1DVoigt *fTD1DVoigt = dynamic_cast<const FTDistribution1DVoigt *>(pdf))
            {
                result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DVoigt->getOmega())
                << "," << printDouble(fTD1DVoigt->getEta()) << ")\n";
            }

            if (pdf->getOmega() != 0.0)
            {
                if (const FTDistribution1DCauchy *fTD1DCauchy = dynamic_cast<const FTDistribution1DCauchy *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DCauchy->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DCosine *fTD1DCosine = dynamic_cast<const FTDistribution1DCosine *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DCosine->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DGate *fTD1DGate = dynamic_cast<const FTDistribution1DGate *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DGate->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DGauss *fTD1DGauss = dynamic_cast<const FTDistribution1DGauss *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DGauss->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DTriangle *fTD1DTriangle = dynamic_cast<const FTDistribution1DTriangle *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DTriangle->getOmega()) << ")\n";
                }

                result << "\t" << it->second << ".setProbabilityDistribution(" << it->second << "_pdf)\n\n";
            }
        }

        else if (const InterferenceFunction1DParaCrystal *oneDParaCrystal = dynamic_cast<const InterferenceFunction1DParaCrystal *>(iInterferenceFunction))
        {
            result << " = InterferenceFunction1DParaCrystal(" << oneDParaCrystal->getPeakDistance()
            << "*nanometer," << oneDParaCrystal->getDampingLength() << "*nanometer)\n";
            if (oneDParaCrystal->getKappa() != 0.0)
            {
                result << "\t" << it->second << ".setKappa(" << printDouble(oneDParaCrystal->getKappa()) << ")\n";
            }

            if (oneDParaCrystal->getDomainSize() != 0.0)
            {
                result << "\t" << it->second << ".setDomainSize(" << printDouble(oneDParaCrystal->getDomainSize()) << ")\n";
            }

            const IFTDistribution1D *pdf =  oneDParaCrystal->getPropabilityDistribution();

            if (const FTDistribution1DVoigt *fTD1DVoigt = dynamic_cast<const FTDistribution1DVoigt *>(pdf))
            {
                result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DVoigt->getOmega())
                << "," << printDouble(fTD1DVoigt->getEta()) << ")\n";
            }

            if (pdf->getOmega() != 0.0)
            {
                if (const FTDistribution1DCauchy *fTD1DCauchy = dynamic_cast<const FTDistribution1DCauchy *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DCauchy->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DCosine *fTD1DCosine = dynamic_cast<const FTDistribution1DCosine *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DCosine->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DGate *fTD1DGate = dynamic_cast<const FTDistribution1DGate *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DGate->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DGauss *fTD1DGauss = dynamic_cast<const FTDistribution1DGauss *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DGauss->getOmega()) << ")\n";
                }

                else if (const FTDistribution1DTriangle *fTD1DTriangle = dynamic_cast<const FTDistribution1DTriangle *>(pdf))
                {
                    result << "\t" << it->second << "_pdf  = FTDistribution1DCauchy(" << printDouble(fTD1DTriangle->getOmega()) << ")\n";
                }

                result << "\t" << it->second << ".setProbabilityDistribution(" << it->second << "_pdf)\n\n";
            }
        }

        else if (const InterferenceFunction2DLattice *twoDLattice = dynamic_cast<const InterferenceFunction2DLattice *>(iInterferenceFunction))
        {
            const Lattice2DIFParameters latticeParameters = twoDLattice->getLatticeParameters();
            result << " = InterferenceFunction2DLattice(" << printDouble(latticeParameters.m_length_1) << "*nanometer,"
            << printDouble(latticeParameters.m_length_2) << "*nanometer," << printDouble(latticeParameters.m_angle) << ","
            << printDouble(latticeParameters.m_xi) << ")\n";

            const IFTDistribution2D *pdf =  twoDLattice->getProbabilityDistribution();

            if (const FTDistribution2DCauchy *fTD2DCauchy = dynamic_cast<const FTDistribution2DCauchy *>(pdf))
            {
                result << "\t" << it->second << "_pdf  = FTDistribution2DCauchy(" << printDouble(fTD2DCauchy->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DCauchy->getCoherenceLengthY()) << "*nanometer" << ")\n";
                if (fTD2DCauchy->getGamma() != 0.0)
                {
                    result << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DCauchy->getGamma()) << ")\n";
                }
            }

            if (const FTDistribution2DCone *fTD2DCone = dynamic_cast<const FTDistribution2DCone *>(pdf))
            {
                result << "\t" << it->second << "_pdf  = FTDistribution2DCone(" << printDouble(fTD2DCone->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DCone->getCoherenceLengthY()) << "*nanometer" << ")\n";
                if (fTD2DCone->getGamma() != 0.0)
                {
                    result << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DCone->getGamma()) << ")\n";
                }
            }

            if (const FTDistribution2DGate *fTD2DGate = dynamic_cast<const FTDistribution2DGate *>(pdf))
            {
                result << "\t" << it->second << "_pdf  = FTDistribution2DGate(" << printDouble(fTD2DGate->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DGate->getCoherenceLengthY()) << "*nanometer" << ")\n";
                if (fTD2DGate->getGamma() != 0.0)
                {
                    result << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DGate->getGamma()) << ")\n";
                }
            }

            if (const FTDistribution2DGauss *fTD2DGauss = dynamic_cast<const FTDistribution2DGauss *>(pdf))
            {
                result << "\t" << it->second << "_pdf  = FTDistribution2DGauss(" << printDouble(fTD2DGauss->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DGauss->getCoherenceLengthY()) << "*nanometer" << ")\n";
                if (fTD2DGauss->getGamma() != 0.0)
                {
                    result << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DGauss->getGamma()) << ")\n";
                }
            }

            if (const FTDistribution2DVoigt *fTD2DVoigt = dynamic_cast<const FTDistribution2DVoigt *>(pdf))
            {
                result << "\t" << it->second << "_pdf  = FTDistribution2DVoigt(" << printDouble(fTD2DVoigt->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DVoigt->getCoherenceLengthY()) << "*nanometer" << "," << printDouble(fTD2DVoigt->getEta()) << ")\n";
                if (fTD2DVoigt->getGamma() != 0.0)
                {
                    result << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DVoigt->getGamma()) << ")\n";
                }
            }

        }

        else if (const InterferenceFunction2DParaCrystal *twoDParaCrystal = dynamic_cast<const InterferenceFunction2DParaCrystal *>(iInterferenceFunction))
        {
            result << " = InterferenceFunction2DParaCrystal(" <<twoDParaCrystal->getLatticeLengths()[0]
            << "*nanometer," << twoDParaCrystal->getLatticeLengths()[1] << "*nanometer," <<
            twoDParaCrystal->getAlphaLattice() << "*nanometer," << twoDParaCrystal->getLatticeOrientation()
            << "*nanometer," << twoDParaCrystal->getDampingLength() << "*nanometer)\n";

  /*          const IFTDistribution2D *pdf =  twoDParaCrystal->getProbabilityDistributions();

            if (const FTDistribution2DCauchy *fTD2DCauchy = dynamic_cast<const FTDistribution2DCauchy *>(pdf))
            {
                myfile << "\t" << it->second << "_pdf  = FTDistribution2DCauchy(" << printDouble(fTD2DCauchy->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DCauchy->getCoherenceLengthY()) << "*nanometer" << ")\n";
                if (fTD2DCauchy->getGamma() != 0.0)
                {
                    myfile << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DCauchy->getGamma()) << ")\n";
                }
            }

            if (const FTDistribution2DCone *fTD2DCone = dynamic_cast<const FTDistribution2DCone *>(pdf))
            {
                myfile << "\t" << it->second << "_pdf  = FTDistribution2DCone(" << printDouble(fTD2DCone->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DCone->getCoherenceLengthY()) << "*nanometer" << ")\n";
                if (fTD2DCone->getGamma() != 0.0)
                {
                    myfile << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DCone->getGamma()) << ")\n";
                }
            }

            if (const FTDistribution2DGate *fTD2DGate = dynamic_cast<const FTDistribution2DGate *>(pdf))
            {
                myfile << "\t" << it->second << "_pdf  = FTDistribution2DGate(" << printDouble(fTD2DGate->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DGate->getCoherenceLengthY()) << "*nanometer" << ")\n";
                if (fTD2DGate->getGamma() != 0.0)
                {
                    myfile << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DGate->getGamma()) << ")\n";
                }
            }

            if (const FTDistribution2DGauss *fTD2DGauss = dynamic_cast<const FTDistribution2DGauss *>(pdf))
            {
                myfile << "\t" << it->second << "_pdf  = FTDistribution2DGauss(" << printDouble(fTD2DGauss->getCoherenceLengthX())
                << "*nanometer," << printDouble(fTD2DGauss->getCoherenceLengthY()) << "*nanometer" << ")\n";
                if (fTD2DGauss->getGamma() != 0.0)
                {
                    myfile << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DGauss->getGamma()) << ")\n";
                }
            }

            if (const FTDistribution2DVoigt *fTD2DVoigt = dynamic_cast<const FTDistribution2DVoigt *>(pdf))
            {
                myfile << "\t" << it->second << "_pdf  = FTDistribution2DVoigt(" << printDouble(fTD2DVoigt->getCoherenceLengthX()) << "*nanometer,"
                << printDouble(fTD2DVoigt->getCoherenceLengthY()) << "*nanometer" << "," << printDouble(fTD2DVoigt->getEta()) << ")\n";
                if (fTD2DVoigt->getGamma() != 0.0)
                {
                    myfile << "\t" << it->second << "_pdf" << ".setGamma(" << printDouble(fTD2DVoigt->getGamma()) << ")\n";
                }  */
        }

        else
        {
            // I should Give Proper Exception Here
            std::cout << "\n" << interfernceFunctionNotFound << ": " << iInterferenceFunction->getName()
            << "Not Casted To Any Interference Function\n";
            formFactorNotFound++;
        }

        it++;
    }

    if (m_label->getParticleCoreShellMap()->size() != 0)
    {
        result << "\n\t# Defining Particle Core Shells\n";
    }
    std::map<const ParticleCoreShell *,std::string>::iterator it5 = m_label->getParticleCoreShellMap()->begin();
    while (it5 != m_label->getParticleCoreShellMap()->end())
    {
        kvector_t position = it5->first->getRelativeCorePosition();
        result << "\t" << it5->second << "_relPosition = kvector_t(" << position.x()
        << "*nanometer," << position.y() << "*nanometer," << position.z() << "*nanometer)";
        result << "\n\t" << it5->second << " = ParticleCoreShell(" << m_label->getLabel(it5->first->getShellParticle())
        << "," << m_label->getLabel(it5->first->getCoreParticle()) << ", " << it5->second << "_relPosition)\n";
        it5++;
    }

    if (m_label->getParticleLayoutMap()->size() > 0)
    {
        result << "\n\t# Defining Particle layouts and adding Particles\n";
    }

    std::map<const ILayout *,std::string>::iterator it6 = m_label->getParticleLayoutMap()->begin();
    while (it6 != m_label->getParticleLayoutMap()->end())
    {
        const ILayout *iLayout = it6->first;
        if (const ParticleLayout *particleLayout = dynamic_cast<const ParticleLayout *>(iLayout))
        {
            result << "\t" << it6->second << " = ParticleLayout()\n\n";
            size_t numberOfParticles = particleLayout->getNumberOfParticles();
            size_t particleIndex = 0;
            while (particleIndex != numberOfParticles)
            {
                const ParticleInfo *particleInfo = particleLayout->getParticleInfo(particleIndex);
                if (const PositionParticleInfo *positionParticleInfo = dynamic_cast<const PositionParticleInfo *>(particleInfo))
                {
                    result << "\t# Defining " << m_label->getLabel(particleInfo->getParticle());
                    result << "\n\t" << m_label->getLabel(particleInfo->getParticle()) << "_position = kvector_t(" << positionParticleInfo->getPosition().x() << "*nanometer,"
                    << positionParticleInfo->getPosition().y() << "*nanometer," << positionParticleInfo->getPosition().z() << "*nanometer)\n";
                    result << "\t" << it6->second << ".addParticle(" << m_label->getLabel(particleInfo->getParticle()) << ","
                    << m_label->getLabel(particleInfo->getParticle()) << "_position," << printDouble(particleInfo->getAbundance()) << ")\n";
                }
                else
                {
                    result << "\t# Defining " << m_label->getLabel(particleInfo->getParticle());
                    result << "\n\t" << it6->second << ".addParticle(" << m_label->getLabel(particleInfo->getParticle()) << ","
                    << printDouble(particleInfo->getDepth()) << "," << printDouble(particleInfo->getAbundance()) << ")\n";
                }
                particleIndex++;
            }
            size_t numberOfInterferenceFunctions = particleLayout->getNumberOfInterferenceFunctions();
            size_t InterferenceFunctionsIndex = 0;
            while (InterferenceFunctionsIndex != numberOfInterferenceFunctions)
            {
                result << "\t" << it6->second << ".addInterferenceFunction("
                << m_label->getLabel(particleLayout->getInterferenceFunction(InterferenceFunctionsIndex)) << ")\n";
                InterferenceFunctionsIndex++;
            }
        }
        it6++;
    }

    it2 = m_label->getLayerMap()->begin();
    while (it2 != m_label->getLayerMap()->end())
    {
        const Layer *layer = it2->first;
        if (layer->hasDWBASimulation())
        {
            result << "\n\t" << it2->second << ".setLayout(" << m_label->getLabel(layer->getLayout())<< ")\n";
        }
        it2++;
    }

    if (m_label->getLayerRoughnessMap()->size() != 0)
    {
        result << "\n\t# Defining Roughness Parameters\n";
    }
    std::map<const LayerRoughness *,std::string>::iterator it7 = m_label->getLayerRoughnessMap()->begin();
    while (it7 != m_label->getLayerRoughnessMap()->end())
    {
        result << "\t" << it7->second << " = LayerRoughness(" << it7->first->getSigma()
        << "*nanometer," << it7->first->getHurstParameter() << "*nanometer,"
        << it7->first->getLatteralCorrLength() << "*nanometer)\n";
        it7++;
    }

    result << "\n\t# Defining Multilayers\n";
    std::map<const MultiLayer *,std::string>::iterator it8 = m_label->getMultiLayerMap()->begin();
    while (it8 != m_label->getMultiLayerMap()->end())
    {
        result << "\t" << it8->second << " = MultiLayer()\n";
        size_t numberOfLayers = it8->first->getNumberOfLayers();
        result << "\t" << it8->second << ".addLayer(" <<
        m_label->getLabel(it8->first->getLayer(0)) << ")\n";
        size_t layerIndex = 1;
        while (layerIndex != numberOfLayers)
        {
            const LayerInterface *layerInterface = it8->first->getLayerInterface(layerIndex-1);
            if (m_label->getLayerRoughnessMap()->find(layerInterface->getRoughness())
                == m_label->getLayerRoughnessMap()->end())
            {
                result << "\t" << it8->second << ".addLayer(" <<
                m_label->getLabel(it8->first->getLayer(layerIndex)) << ")\n";
            }
            else
            {
                result << "\t" << it8->second << ".addLayerWithTopRoughness(" <<
                m_label->getLabel(it8->first->getLayer(layerIndex)) << "," <<
                m_label->getLabel(layerInterface->getRoughness()) << ")\n";
            }
            layerIndex++;
        }
        result <<"\treturn " << it8->second <<  std::endl << std::endl;
        it8++;
    }

    result << "def getSimulation():\n";
    result << "\t# Creating and returning GISAXS simulation\n";
    result << "\t# Defining Beam and Detector Parameters\n";
    result << "\tsimulation = Simulation()\n";
    result << "\tsimulation.setDetectorParameters(" ;
    size_t numberOfDetectorDimensions = simulation->getInstrument().getDetectorDimension();
    size_t index = 0;
    while (index != numberOfDetectorDimensions)
    {
        if (index != 0) {result << ",";}
        result << simulation->getInstrument().getDetectorAxis(index).getSize() << "," <<
        simulation->getInstrument().getDetectorAxis(index).getMin() << "," <<
        simulation->getInstrument().getDetectorAxis(index).getMax();
        index++;
    }
    result << ") \n";
    result << "\tsimulation.setBeamParameters(" ;
    result << simulation->getInstrument().getBeam().getWavelength() << "*nanometer,"
    << simulation->getInstrument().getBeam().getAlpha() << "," <<
    simulation->getInstrument().getBeam().getPhi() << ")\n";
    result << "\treturn simulation\n\n";
    result << "def runSimulation(filename = ''):\n";
    result << "\t# Run Simulation and plot results\n";
    result << "\tsample = getSample()\n";
    result << "\tsimulation = getSimulation()\n";
    result << "\tsimulation.setSample(sample)\n";
    result << "\tif filename == '':\n";
    result << "\t\tsimulation.runSimulation()\n";
    result << "\t\tresult = simulation.getIntensityData().getArray() + 1 # +1 for log scale\n";
    result << "\t\tim = pylab.imshow(numpy.rot90(result, 1), norm=matplotlib.colors.LogNorm(), extent=[";
    index = 0;
    while (index != numberOfDetectorDimensions)
    {
        if (index != 0) {result << ",";}
        result << simulation->getInstrument().getDetectorAxis(index).getMin() << "," <<
        simulation->getInstrument().getDetectorAxis(index).getMax();
        index++;
    }
    result << "]) \n\t\tpylab.colorbar(im) \n\t\tpylab.show() \n\telse:\n";
    result << "\t\tIntensityDataIOFactory.writeIntensityData(simulation.getIntensityData(), filename + '.int')\n\n";
    result << "if __name__ == '__main__': \n\trunSimulation('";
    if (fileName != "")
        result << fileName;
    result << "')";
    return result.str();
}

std::string PyGenVisitor::printDouble(double input)
{
    std::ostringstream inter;
    if((input-floor(input)) == 0.0)
    {
        inter << input << ".0";
    }
    else
    {
        inter << input;
    }
    return inter.str();
}

void PyGenVisitor::visit(const FormFactorAnisoPyramid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorBox *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorCone *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorCone6 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorCuboctahedron *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorCylinder *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorEllipsoidalCylinder *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorFullSphere *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorFullSpheroid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorGauss *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorHemiEllipsoid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorInfLongBox *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorInfLongRipple1 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorInfLongRipple2 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorLorentz *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorPrism3 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorPrism6 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorPyramid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorRipple1 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorRipple2 *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorTetrahedron *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorTruncatedSphere *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const FormFactorTruncatedSpheroid *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunctionNone *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunction1DLattice *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunction1DParaCrystal *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunction2DLattice *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
{
     m_label->setLabel(sample);
}

void PyGenVisitor::visit(const Layer *sample)
{
    m_label->insertMaterial(sample->getMaterial());
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const LayerRoughness *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const MultiLayer *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const Particle *sample)
{
    m_label->insertMaterial(sample->getMaterial());
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const ParticleCoreShell *sample)
{
    m_label->setLabel(sample);
}

void PyGenVisitor::visit(const ParticleLayout *sample)
{
    m_label->setLabel(sample);
//     myfile << sample->getName() << std::endl;
}
