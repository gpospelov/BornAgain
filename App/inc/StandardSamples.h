#ifndef STANDARDSAMPLES_H
#define STANDARDSAMPLES_H

#include "ISample.h"
#include "SampleFactory.h"


namespace StandardSamples{

ISample *AirOnSubstrate();
ISample *SubstrateOnSubstrate();
ISample *SimpleMultilayer();
ISample *MultilayerOffspecTestcase1a();
ISample *MultilayerOffspecTestcase1b();
ISample *MultilayerOffspecTestcase2a();
ISample *MultilayerOffspecTestcase2b();
ISample *IsGISAXS1_CylinderAndPrism();
ISample *IsGISAXS2_CylindersMixture();
ISample *IsGISAXS3_CylinderDWBA();
ISample *IsGISAXS3_CylinderBA();
ISample *IsGISAXS3_CylinderBASize();
ISample *IsGISAXS4_1DDL();
ISample *IsGISAXS4_2DDL();
ISample *IsGISAXS6_lattice();
ISample *IsGISAXS6_centered();
ISample *IsGISAXS6_rotated();
ISample *IsGISAXS7_morphology();
ISample *IsGISAXS8_2DDL_lattice();
ISample *IsGISAXS8_2DDL_lattice2();
ISample *IsGISAXS9_Pyramid();
ISample *IsGISAXS9_RotatedPyramid();
ISample *IsGISAXS10_CylindersParacrystal1D();
ISample *IsGISAXS11_CoreShellParticles();
ISample *IsGISAXS15_SSCA();
ISample *MesoCrystal1();
ISample *MesoCrystal2();

}



#endif // STANDARDSAMPLES_H
