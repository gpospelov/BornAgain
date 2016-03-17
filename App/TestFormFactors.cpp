// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFormFactors.cpp
//! @brief     Implements class TestFormFactors.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestFormFactors.h"
#include "IsGISAXSTools.h"
#include "IntensityDataIOFactory.h"
#include "Units.h"
#include "Utils.h"
#include "Simulation.h"
#include "MultiLayer.h"
#include "ParticleLayout.h"
#include "Materials.h"
#include "FormFactors.h"
#include "InterferenceFunctionNone.h"
#include "FileSystem.h"
#include "IsGISAXSDetector.h"

TestFormFactors::TestFormFactors()
: IApplicationTest("TestFormFactors")
, mp_form_factor(0)
{
    setOutputPath(Utils::FileSystem::GetPathToData(
            "../Tests/ReferenceData/IsGISAXS/FormFactors/" ));
}

void TestFormFactors::execute()
{  // no rotation of particles angle =54.73deg
   // For Cone6 and prism6 radius = 2./sqrt(3.)R_{IsGiSaXs}
   // Length unit : nanometers
   //Cylinder
   FormFactorCylinder ff_cyl(5.0, 5.0);
   IFormFactor* p_ff_cyl =& ff_cyl;
   run_isgisaxs_simulation(p_ff_cyl->clone());

   //Box
   FormFactorBox ff_box(10.0, 20.0, 5.0);
   IFormFactor* p_ff_box =& ff_box;
   run_isgisaxs_simulation(p_ff_box->clone());

   //Cone
   FormFactorCone ff_cone(5.0, 5.0, Units::deg2rad(54.73 ));
   IFormFactor* p_ff_cone =& ff_cone;
   run_isgisaxs_simulation(p_ff_cone->clone());

   //Cone6
   FormFactorCone6 ff_cone6(2./sqrt(3.)*5.0, 5.0, Units::deg2rad(54.73));
   IFormFactor* p_ff_cone6 =& ff_cone6;
   run_isgisaxs_simulation(p_ff_cone6->clone());

   //FullSphere
   FormFactorFullSphere ff_fsph(5.0);
   IFormFactor* p_ff_fsph =& ff_fsph;
   run_isgisaxs_simulation(p_ff_fsph->clone());

   //Parallelepiped
   //FormFactorParallelepiped ff_par(10.0, 5.0);
   //IFormFactor* p_ff_par =& ff_par;
   //run_isgisaxs_simulation(p_ff_par->clone());

   //Prism3
   FormFactorPrism3 ff_pr3(10.0, 5.0);
   IFormFactor* p_ff_pr3 =& ff_pr3;
   run_isgisaxs_simulation(p_ff_pr3->clone());

   //Prism6
   FormFactorPrism6 ff_pr6(2./sqrt(3.)*5.0, 5.0);
   IFormFactor* p_ff_pr6 =& ff_pr6;
   run_isgisaxs_simulation(p_ff_pr6->clone());

   //Pyramid
   FormFactorPyramid ff_pyr(10.0, 5.0, Units::deg2rad(54.73 ));
   IFormFactor* p_ff_pyr =& ff_pyr;
   run_isgisaxs_simulation(p_ff_pyr->clone());

   //TruncatedSphere
   FormFactorTruncatedSphere ff_sph(5.0, 5.0);
   IFormFactor* p_ff_sph =& ff_sph;
   run_isgisaxs_simulation(p_ff_sph->clone());

   // Tetrahedron
   FormFactorTetrahedron ff_tetr(10.0, 4.0, Units::deg2rad(54.73 ));
   IFormFactor* p_ff_tetr =& ff_tetr;
   run_isgisaxs_simulation(p_ff_tetr->clone());

   // Cuboctahedron
   FormFactorCuboctahedron ff_cuboc(10.0, 5.0, 1.0, Units::deg2rad(54.73 ));
   IFormFactor* p_ff_cuboc =& ff_cuboc;
   run_isgisaxs_simulation(p_ff_cuboc->clone());

   // Anisotropic Pyramid
   FormFactorAnisoPyramid ff_anipyr(10.0, 20.0, 5.0, Units::deg2rad(54.73 ));
   IFormFactor* p_ff_anipyr =& ff_anipyr;
   run_isgisaxs_simulation(p_ff_anipyr->clone());

   // Ellipsoidal cylinder
   FormFactorEllipsoidalCylinder ff_ellipscyl(5.0, 10.0, 5.0);
   IFormFactor* p_ff_ellipscyl =& ff_ellipscyl;
   run_isgisaxs_simulation(p_ff_ellipscyl->clone());

   // Full Spheroid
    FormFactorFullSpheroid ff_fspheroid(5.0, 5.0);
    IFormFactor* p_ff_fspheroid =& ff_fspheroid;
    run_isgisaxs_simulation(p_ff_fspheroid->clone());

   // Truncated Spheroid
   FormFactorTruncatedSpheroid  ff_spheroid(5.0, 5.0, 1.0);
   IFormFactor* p_ff_spheroid =& ff_spheroid;
   run_isgisaxs_simulation(p_ff_spheroid->clone());

   // Anisotropic HemiEllipsoid
   FormFactorHemiEllipsoid  ff_hellipsoid(5.0, 10.0, 5.0);
   IFormFactor* p_ff_hellipsoid=& ff_hellipsoid;
   run_isgisaxs_simulation(p_ff_hellipsoid->clone());
}


void TestFormFactors::run_isgisaxs_simulation(IFormFactor *p_form_factor)
{
//    HomogeneousMaterial air_material("Air", 0.0, 0.0);
//    HomogeneousMaterial particle_material("Particle", 6e-4, 2e-8);

//    //building sample
//    MultiLayer multi_layer;
//    Layer air_layer;
//    air_layer.setMaterial(air_material);

//    mp_form_factor=p_form_factor;
//    Particle particle(particle_material, *mp_form_factor);
//    ParticleLayout particle_layout(particle);
//    particle_layout.addInterferenceFunction(new InterferenceFunctionNone());
//    air_layer.addLayout(particle_layout);
//    multi_layer.addLayer(air_layer);

//    // building simulation
//    GISASSimulation simulation(mp_options);
//    IsGISAXSDetector detector;
//    detector.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
//                                     100, 0.0*Units::degree, 2.0*Units::degree);
//    simulation.setDetector(detector);

//    simulation.setSample(multi_layer);
//    simulation.runSimulation();
//    std::cout << mp_form_factor->getName().substr(10) <<std::endl;
//    IntensityDataIOFactory::writeOutputData(*simulation.getOutputData(),
//                       "this_"+mp_form_factor->getName().substr(10)+"_BA.ima");
    throw Exceptions::NotImplementedException("Cleanup the code!");

}

void TestFormFactors::finalise()
{
//   std::vector< CompareStruct > tocompare;
//   tocompare.push_back( CompareStruct(getOutputPath()+"isgi_cylinder_BA.ima",
//            "this_Cylinder_BA.ima",
//            "Cylinder BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_box_BA.ima",
//            "this_Box_BA.ima", "Box BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_cone_BA.ima",
//            "this_Cone_BA.ima", "Cone BA Formfactor"));

//    tocompare.push_back( CompareStruct( getOutputPath()+"isgi_cone6_BA.ima",
//            "this_Cone6_BA.ima", "Cone6 BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+
//                                       "isgi_full_sphere_BA.ima",
//            "this_FullSphere_BA.ima","Full Sphere BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+
//                                      "isgi_parallelepiped_BA.ima",
//            "this_Parallelepiped_BA.ima","Parallelepiped BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_prism3_BA.ima",
//            "this_Prism3_BA.ima", "Prism3 BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_prism6_BA.ima",
//            "this_Prism6_BA.ima", "Prism6 BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_pyramid_BA.ima",
//            "this_Pyramid_BA.ima","Pyramid BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_sphere_BA.ima",
//            "this_Sphere_BA.ima","Sphere BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+
//                                       "isgi_tetrahedron_BA.ima",
//            "this_Tetrahedron_BA.ima","Tetrahedron BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+
//                                        "isgi_cuboctahedron_BA.ima",
//         "this_Cuboctahedron_BA.ima","Cuboctahedron BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+
//                                          "isgi_aniso_pyramid_BA.ima",
//          "this_AnisoPyramid_BA.ima", "AnisoPyramid BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_ellipsoid_BA.ima",
//        "this_EllipsoidalCylinder_BA.ima","EllipsoidalCylinder BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_full_spheroid_BA.ima",
//         "this_FullSpheroid_BA.ima", "FullSpheroid BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+"isgi_spheroid_BA.ima",
//         "this_Spheroid_BA.ima", "Spheroid BA Formfactor"));

//    tocompare.push_back( CompareStruct(getOutputPath()+
//                                       "isgi_hemi_ellipsoid_BA.ima","this_HemiEllipsoid_BA.ima",
//          "HemiEllipsoid BA Formfactor"));


//    const double threshold(2e-10);

//    for(size_t i=0; i<tocompare.size(); ++i) {
//        OutputData<double> *isgi_data = IntensityDataIOFactory::readOutputData(
//                tocompare[i].isginame);
//        OutputData<double> *our_data = IntensityDataIOFactory::readOutputData(
//                tocompare[i].thisname);

//        IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data,
//                tocompare[i].descr, tocompare[i].descr);

//        *our_data -= *isgi_data;
//        *our_data /= *isgi_data;

//        double diff(0);
//        for(OutputData<double>::const_iterator it =
//            our_data->begin(); it!=our_data->end(); ++it) {
//            diff+= std::abs(*it);
//        }
//        diff /= our_data->getAllocatedSize();

//        bool status_ok(true);
//        if( diff > threshold || MathFunctions::isnan(diff) ) status_ok=false;
//        std::cout << m_name  << tocompare[i].descr<<" " << diff << " " <<
//            (status_ok ? "[OK]" : "[FAILED]") << std::endl;

//        delete isgi_data;
//        delete our_data;
//    }

    throw Exceptions::NotImplementedException("Cleanup the code!");

}





