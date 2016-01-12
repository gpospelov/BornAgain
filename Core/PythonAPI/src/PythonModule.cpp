#include "Python.h"
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)

// Numpy (the order of the following three lines is important):
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
#include "numpy/arrayobject.h"
#include "ILayout.pypp.h"
#include "RotationZ.pypp.h"
#include "FTDistribution1DCauchy.pypp.h"
#include "ISampleBuilder.pypp.h"
#include "Beam.pypp.h"
#include "FormFactorWeighted.pypp.h"
#include "HomogeneousMagneticMaterial.pypp.h"
#include "DistributionLorentz.pypp.h"
#include "RotationX.pypp.h"
#include "Crystal.pypp.h"
#include "InterferenceFunctionNone.pypp.h"
#include "FTDistribution2DGate.pypp.h"
#include "FormFactorPrism6.pypp.h"
#include "vdouble2d_t.pypp.h"
#include "FormFactorTruncatedCube.pypp.h"
#include "VerticalLine.pypp.h"
#include "IFTDistribution2D.pypp.h"
#include "FormFactorLorentz.pypp.h"
#include "FixedBinAxis.pypp.h"
#include "ISample.pypp.h"
#include "ConstKBinAxis.pypp.h"
#include "LayerInterface.pypp.h"
#include "IDetectorResolution.pypp.h"
#include "Lattice2DIFParameters.pypp.h"
#include "HorizontalLine.pypp.h"
#include "IntensityData.pypp.h"
#include "LayerRoughness.pypp.h"
#include "vector_integer_t.pypp.h"
#include "FormFactorTruncatedSphere.pypp.h"
#include "FormFactorCylinder.pypp.h"
#include "FormFactorFullSphere.pypp.h"
#include "IAxis.pypp.h"
#include "Simulation.pypp.h"
#include "IDetector2D.pypp.h"
#include "InterferenceFunction2DParaCrystal.pypp.h"
#include "DistributionLogNormal.pypp.h"
#include "FTDistribution1DCosine.pypp.h"
#include "OffSpecSimulation.pypp.h"
#include "RotationEuler.pypp.h"
#include "FTDistribution1DTriangle.pypp.h"
#include "FormFactorSphereUniformRadius.pypp.h"
#include "IntensityDataFunctions.pypp.h"
#include "Instrument.pypp.h"
#include "FormFactorTrivial.pypp.h"
#include "FormFactorSphereLogNormalRadius.pypp.h"
#include "RotationY.pypp.h"
#include "vector_realparameter_t.pypp.h"
#include "IInterferenceFunction.pypp.h"
#include "FTDistribution2DCauchy.pypp.h"
#include "IFormFactor.pypp.h"
#include "IObserver.pypp.h"
#include "ParticleComposition.pypp.h"
#include "Particle.pypp.h"
#include "MultiLayer.pypp.h"
#include "ParameterPool.pypp.h"
#include "FormFactorTetrahedron.pypp.h"
#include "FormFactorFullSpheroid.pypp.h"
#include "IParameterized.pypp.h"
#include "FormFactorAnisoPyramid.pypp.h"
#include "IObservable.pypp.h"
#include "ParticleCoreShell.pypp.h"
#include "Histogram2D.pypp.h"
#include "IShape2D.pypp.h"
#include "FormFactorCone.pypp.h"
#include "vector_string_t.pypp.h"
#include "Polygon.pypp.h"
#include "RectangularDetector.pypp.h"
#include "IDistribution1D.pypp.h"
#include "MesoCrystal.pypp.h"
#include "FTDistribution2DVoigt.pypp.h"
#include "InterferenceFunctionRadialParaCrystal.pypp.h"
#include "IMaterial.pypp.h"
#include "IsGISAXSDetector.pypp.h"
#include "SimulationParameters.pypp.h"
#include "IResolutionFunction2D.pypp.h"
#include "FormFactorTruncatedSpheroid.pypp.h"
#include "FormFactorCone6.pypp.h"
#include "FormFactorSphereGaussianRadius.pypp.h"
#include "VariableBinAxis.pypp.h"
#include "vector_longinteger_t.pypp.h"
#include "ResolutionFunction2DGaussian.pypp.h"
#include "cvector_t.pypp.h"
#include "FormFactorDecoratorDebyeWaller.pypp.h"
#include "IClusteredParticles.pypp.h"
#include "FTDistribution1DVoigt.pypp.h"
#include "vector_complex_t.pypp.h"
#include "FTDistribution2DCone.pypp.h"
#include "ParticleDistribution.pypp.h"
#include "vector_kvector_t.pypp.h"
#include "FormFactorRipple1.pypp.h"
#include "Bin1D.pypp.h"
#include "FormFactorRipple2.pypp.h"
#include "InterferenceFunction2DLattice.pypp.h"
#include "ThreadInfo.pypp.h"
#include "DistributionCosine.pypp.h"
#include "FTDistribution1DGauss.pypp.h"
#include "FTDistribution1DGate.pypp.h"
#include "FormFactorCuboctahedron.pypp.h"
#include "Layer.pypp.h"
#include "RealParameterWrapper.pypp.h"
#include "Histogram1D.pypp.h"
#include "SpecularSimulation.pypp.h"
#include "FormFactorCrystal.pypp.h"
#include "FormFactorPrism3.pypp.h"
#include "PythonInterface_global_variables.pypp.h"
#include "FTDistribution2DGauss.pypp.h"
#include "Line.pypp.h"
#include "FormFactorGauss.pypp.h"
#include "vector_less__const_ISample_ptr___greater_.pypp.h"
#include "FormFactorHemiEllipsoid.pypp.h"
#include "PythonInterface_free_functions.pypp.h"
#include "IParticle.pypp.h"
#include "vdouble1d_t.pypp.h"
#include "AttLimits.pypp.h"
#include "DistributionGaussian.pypp.h"
#include "FormFactorBox.pypp.h"
#include "FormFactorPyramid.pypp.h"
#include "Lattice.pypp.h"
#include "IFTDistribution1D.pypp.h"
#include "IFormFactorBorn.pypp.h"
#include "FormFactorEllipsoidalCylinder.pypp.h"
#include "ParticleLayout.pypp.h"
#include "WavevectorInfo.pypp.h"
#include "IFormFactorDecorator.pypp.h"
#include "HomogeneousMaterial.pypp.h"
#include "DistributionGate.pypp.h"
#include "kvector_t.pypp.h"
#include "IAbstractParticle.pypp.h"
#include "ISelectionRule.pypp.h"
#include "IntensityDataIOFactory.pypp.h"
#include "IHistogram.pypp.h"
#include "ParameterDistribution.pypp.h"
#include "SimpleSelectionRule.pypp.h"
#include "InterferenceFunction1DLattice.pypp.h"
#include "Ellipse.pypp.h"
#include "Rectangle.pypp.h"
#include "Bin1DCVector.pypp.h"
#include "CustomBinAxis.pypp.h"
#include "ICloneable.pypp.h"
#include "IRotation.pypp.h"
#include "Lattice1DIFParameters.pypp.h"
#include "ICompositeSample.pypp.h"
#include "GISASSimulation.pypp.h"
#include "SphericalDetector.pypp.h"
#include "__call_policies.pypp.hpp"
#include "__call_policies.pypp.hpp"

#include "PythonListConverter.h"

BOOST_PYTHON_MODULE(libBornAgainCore){
    boost::python::docstring_options doc_options(true, true, false);

    register_vector_longinteger_t_class();
    register_vdouble2d_t_class();
    register_vector_string_t_class();
    register_vector_complex_t_class();
    register_vector_integer_t_class();
    register_vdouble1d_t_class();
    register_vector_less__const_ISample_ptr___greater__class();
    register_vector_realparameter_t_class();
    register_vector_kvector_t_class();
    register_AttLimits_class();
    register_IParameterized_class();
    register_Beam_class();
    register_Bin1D_class();
    register_Bin1DCVector_class();
    register_IAxis_class();
    register_VariableBinAxis_class();
    register_ConstKBinAxis_class();
    register_ICloneable_class();
    register_ISample_class();
    register_ICompositeSample_class();
    register_IClusteredParticles_class();
    register_Crystal_class();
    register_CustomBinAxis_class();
    register_IDistribution1D_class();
    register_DistributionCosine_class();
    register_DistributionGate_class();
    register_DistributionGaussian_class();
    register_DistributionLogNormal_class();
    register_DistributionLorentz_class();
    register_IFTDistribution1D_class();
    register_FTDistribution1DCauchy_class();
    register_FTDistribution1DCosine_class();
    register_FTDistribution1DGate_class();
    register_FTDistribution1DGauss_class();
    register_FTDistribution1DTriangle_class();
    register_FTDistribution1DVoigt_class();
    register_IFTDistribution2D_class();
    register_FTDistribution2DCauchy_class();
    register_FTDistribution2DCone_class();
    register_FTDistribution2DGate_class();
    register_FTDistribution2DGauss_class();
    register_FTDistribution2DVoigt_class();
    register_FixedBinAxis_class();
    register_IFormFactor_class();
    register_IFormFactorBorn_class();
    register_FormFactorAnisoPyramid_class();
    register_FormFactorBox_class();
    register_FormFactorCone_class();
    register_FormFactorCone6_class();
    register_FormFactorCrystal_class();
    register_FormFactorCuboctahedron_class();
    register_FormFactorCylinder_class();
    register_IFormFactorDecorator_class();
    register_FormFactorDecoratorDebyeWaller_class();
    register_FormFactorEllipsoidalCylinder_class();
    register_FormFactorFullSphere_class();
    register_FormFactorFullSpheroid_class();
    register_FormFactorGauss_class();
    register_FormFactorHemiEllipsoid_class();
    register_FormFactorLorentz_class();
    register_FormFactorPrism3_class();
    register_FormFactorPrism6_class();
    register_FormFactorPyramid_class();
    register_FormFactorRipple1_class();
    register_FormFactorRipple2_class();
    register_FormFactorSphereGaussianRadius_class();
    register_FormFactorSphereLogNormalRadius_class();
    register_FormFactorSphereUniformRadius_class();
    register_FormFactorTetrahedron_class();
    register_FormFactorTrivial_class();
    register_FormFactorTruncatedCube_class();
    register_FormFactorTruncatedSphere_class();
    register_FormFactorTruncatedSpheroid_class();
    register_FormFactorWeighted_class();
    register_Simulation_class();
    register_GISASSimulation_class();
    register_kvector_t_class();
    register_cvector_t_class();
    register_IShape2D_class();
    register_Ellipse_class();
    register_HorizontalLine_class();
    register_Line_class();
    register_Polygon_class();
    register_Rectangle_class();
    register_VerticalLine_class();
    register_IHistogram_class();
    register_Histogram1D_class();
    register_Histogram2D_class();
    register_IMaterial_class();
    register_HomogeneousMaterial_class();
    register_HomogeneousMagneticMaterial_class();
    register_IAbstractParticle_class();
    register_IDetector2D_class();
    register_IDetectorResolution_class();
    register_IInterferenceFunction_class();
    register_ILayout_class();
    register_IObservable_class();
    register_IObserver_class();
    register_IParticle_class();
    register_IResolutionFunction2D_class();
    register_IRotation_class();
    register_ISampleBuilder_class();
    register_ISelectionRule_class();
    register_Instrument_class();
    register_IntensityDataFunctions_class();
    register_IntensityDataIOFactory_class();
    register_InterferenceFunction1DLattice_class();
    register_InterferenceFunction2DLattice_class();
    register_InterferenceFunction2DParaCrystal_class();
    register_InterferenceFunctionNone_class();
    register_InterferenceFunctionRadialParaCrystal_class();
    register_SphericalDetector_class();
    register_IsGISAXSDetector_class();
    register_Lattice_class();
    register_Lattice1DIFParameters_class();
    register_Lattice2DIFParameters_class();
    register_Layer_class();
    register_LayerInterface_class();
    register_LayerRoughness_class();
    register_MesoCrystal_class();
    register_MultiLayer_class();
    register_OffSpecSimulation_class();
    register_IntensityData_class();
    register_ParameterDistribution_class();
    register_ParameterPool_class();
    register_Particle_class();
    register_ParticleComposition_class();
    register_ParticleCoreShell_class();
    register_ParticleDistribution_class();
    register_ParticleLayout_class();
    register_RealParameterWrapper_class();
    register_RectangularDetector_class();
    register_ResolutionFunction2DGaussian_class();
    register_RotationEuler_class();
    register_RotationX_class();
    register_RotationY_class();
    register_RotationZ_class();
    register_SimpleSelectionRule_class();
    register_SimulationParameters_class();
    register_SpecularSimulation_class();
    register_ThreadInfo_class();
    register_WavevectorInfo_class();
    register_global_variables();
    register_free_functions();

    register_python2cpp_converters();

    import_array();
    /* IMPORTANT
    this is initialisation function from C-API of python-numpy package. It has to be called once in the
    initialisation section of the module (i.e. here), when module is going to use any of python numpy C-API.
    Additional rule: when initialisation of the module, and functions that use python-numpy C-API are located in
    different files (different compilation units) - and this is exactly our case - additional defines has
    to be inserted before #include "numpy/arrayobject.h". See explanations
    http://docs.scipy.org/doc/numpy/reference/c-api.array.html#import_array
    */
}
