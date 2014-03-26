#include "Python.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION 
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY 
#include "numpy/arrayobject.h"
// the order of 3 guys above is important

#include "ParticleBuilder.pypp.h" 
#include "FormFactorFullSpheroid.pypp.h" 
#include "DistributionGate.pypp.h" 
#include "SimpleSelectionRule.pypp.h" 
#include "RealParameterWrapper.pypp.h" 
#include "vdouble1d_t.pypp.h" 
#include "SimulationParameters.pypp.h" 
#include "Transform3D.pypp.h" 
#include "ThreadInfo.pypp.h" 
#include "InterferenceFunction2DLattice.pypp.h" 
#include "LayerInterface.pypp.h" 
#include "ILayout.pypp.h" 
#include "FormFactorCone6.pypp.h" 
#include "FormFactorTetrahedron.pypp.h" 
#include "FormFactorWeighted.pypp.h" 
#include "DistributionGaussian.pypp.h" 
#include "IDetectorResolution.pypp.h" 
#include "FormFactorCylinder.pypp.h" 
#include "Crystal.pypp.h" 
#include "FTDistribution1DCauchy.pypp.h" 
#include "IFormFactorBorn.pypp.h" 
#include "FormFactorEllipsoidalCylinder.pypp.h" 
#include "InterferenceFunctionNone.pypp.h" 
#include "vector_kvector_t.pypp.h" 
#include "FormFactorTruncatedSpheroid.pypp.h" 
#include "Particle.pypp.h" 
#include "FTDistribution2DCauchy.pypp.h" 
#include "FormFactorCrystal.pypp.h" 
#include "MaterialManager.pypp.h" 
#include "vector_longinteger_t.pypp.h" 
#include "FormFactorAnisoPyramid.pypp.h" 
#include "MultiLayer.pypp.h" 
#include "IFormFactor.pypp.h" 
#include "kvector_t.pypp.h" 
#include "FormFactorSphereUniformRadius.pypp.h" 
#include "OffSpecSimulation.pypp.h" 
#include "FormFactorRipple1.pypp.h" 
#include "InterferenceFunction1DParaCrystal.pypp.h" 
#include "Simulation.pypp.h" 
#include "IObservable.pypp.h" 
#include "FormFactorLorentz.pypp.h" 
#include "ISelectionRule.pypp.h" 
#include "FormFactorRipple2.pypp.h" 
#include "StochasticDoubleGate.pypp.h" 
#include "LayerRoughness.pypp.h" 
#include "Bin1DCVector.pypp.h" 
#include "FormFactorSphereGaussianRadius.pypp.h" 
#include "ParameterPool.pypp.h" 
#include "FormFactorPrism3.pypp.h" 
#include "StochasticDoubleGaussian.pypp.h" 
#include "IMaterial.pypp.h" 
#include "ResolutionFunction2DSimple.pypp.h" 
#include "AxisDouble.pypp.h" 
#include "FormFactorPrism6.pypp.h" 
#include "IClusteredParticles.pypp.h" 
#include "DistributionCosine.pypp.h" 
#include "FormFactorHemiEllipsoid.pypp.h" 
#include "IAxis.pypp.h" 
#include "vector_integer_t.pypp.h" 
#include "Layer.pypp.h" 
#include "FormFactorPyramid.pypp.h" 
#include "StochasticSampledParameter.pypp.h" 
#include "IFTDistribution1D.pypp.h" 
#include "DistributionLorentz.pypp.h" 
#include "IDistribution1D.pypp.h" 
#include "PositionParticleInfo.pypp.h" 
#include "FormFactorCuboctahedron.pypp.h" 
#include "cvector_t.pypp.h" 
#include "OutputDataIOFactory.pypp.h" 
#include "PythonInterface_free_functions.pypp.h" 
#include "FormFactorSphereLogNormalRadius.pypp.h" 
#include "FormFactorInfLongRipple1.pypp.h" 
#include "IResolutionFunction2D.pypp.h" 
#include "vector_IFormFactorPtr_t.pypp.h" 
#include "FormFactorFullSphere.pypp.h" 
#include "ParticleLayout.pypp.h" 
#include "StochasticParameter_t.pypp.h" 
#include "FormFactorBox.pypp.h" 
#include "IParameterized.pypp.h" 
#include "Lattice2DIFParameters.pypp.h" 
#include "IFormFactorDecorator.pypp.h" 
#include "InterferenceFunction1DLattice.pypp.h" 
#include "ISample.pypp.h" 
#include "ISampleBuilder.pypp.h" 
#include "PythonInterface_global_variables.pypp.h" 
#include "Beam.pypp.h" 
#include "HomogeneousMaterial.pypp.h" 
#include "ICloneable.pypp.h" 
#include "ParticleCoreShell.pypp.h" 
#include "FormFactorDecoratorDebyeWaller.pypp.h" 
#include "MesoCrystal.pypp.h" 
#include "Lattice1DIFParameters.pypp.h" 
#include "IObserver.pypp.h" 
#include "IntensityData.pypp.h" 
#include "Lattice.pypp.h" 
#include "IInterferenceFunction.pypp.h" 
#include "ParticleInfo.pypp.h" 
#include "Instrument.pypp.h" 
#include "FormFactorInfLongBox.pypp.h" 
#include "IntensityDataHelper.pypp.h" 
#include "FormFactorCone.pypp.h" 
#include "FormFactorTruncatedSphere.pypp.h" 
#include "FormFactorGauss.pypp.h" 
#include "InterferenceFunction2DParaCrystal.pypp.h" 
#include "Detector.pypp.h" 
#include "FormFactorInfLongRipple2.pypp.h" 
#include "LatticeBasis.pypp.h" 
#include "ICompositeSample.pypp.h" 
#include "Bin1D.pypp.h" 
#include "AxisBin.pypp.h" 
#include "DistributionLogNormal.pypp.h" 
#include "IFTDistribution2D.pypp.h" 
#include "__call_policies.pypp.hpp" 
#include "__convenience.pypp.hpp" 

#include "PythonListConverter.h"

BOOST_PYTHON_MODULE(libBornAgainCore){

    boost::python::docstring_options doc_options(true, true, false);

    register_vector_longinteger_t_class();
    register_vector_integer_t_class();
    register_vdouble1d_t_class();
    register_vector_IFormFactorPtr_t_class();
    register_vector_kvector_t_class();
    register_IAxis_class();
    register_AxisBin_class();
    register_AxisDouble_class();
    register_IParameterized_class();
    register_Beam_class();
    register_Bin1D_class();
    register_Bin1DCVector_class();
    register_ICloneable_class();
    register_ISample_class();
    register_ICompositeSample_class();
    register_IClusteredParticles_class();
    register_Crystal_class();
    register_Detector_class();
    register_IDistribution1D_class();
    register_DistributionCosine_class();
    register_DistributionGate_class();
    register_DistributionGaussian_class();
    register_DistributionLogNormal_class();
    register_DistributionLorentz_class();
    register_IFTDistribution1D_class();
    register_FTDistribution1DCauchy_class();
    register_IFTDistribution2D_class();
    register_FTDistribution2DCauchy_class();
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
    register_FormFactorInfLongBox_class();
    register_FormFactorInfLongRipple1_class();
    register_FormFactorInfLongRipple2_class();
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
    register_FormFactorTruncatedSphere_class();
    register_FormFactorTruncatedSpheroid_class();
    register_FormFactorWeighted_class();
    register_kvector_t_class();
    register_cvector_t_class();
    register_Transform3D_class();
    register_IMaterial_class();
    register_HomogeneousMaterial_class();
    register_IDetectorResolution_class();
    register_IInterferenceFunction_class();
    register_ILayout_class();
    register_IObservable_class();
    register_IObserver_class();
    register_IResolutionFunction2D_class();
    register_ISampleBuilder_class();
    register_ISelectionRule_class();
    register_Instrument_class();
    register_IntensityDataHelper_class();
    register_InterferenceFunction1DLattice_class();
    register_InterferenceFunction1DParaCrystal_class();
    register_InterferenceFunction2DLattice_class();
    register_InterferenceFunction2DParaCrystal_class();
    register_InterferenceFunctionNone_class();
    register_Lattice_class();
    register_Lattice1DIFParameters_class();
    register_Lattice2DIFParameters_class();
    register_Particle_class();
    register_LatticeBasis_class();
    register_Layer_class();
    register_LayerInterface_class();
    register_LayerRoughness_class();
    register_MaterialManager_class();
    register_MesoCrystal_class();
    register_MultiLayer_class();
    register_OffSpecSimulation_class();
    register_IntensityData_class();
    register_OutputDataIOFactory_class();
    register_ParameterPool_class();
    register_ParticleBuilder_class();
    register_ParticleCoreShell_class();
    register_ParticleInfo_class();
    register_ParticleLayout_class();
    register_PositionParticleInfo_class();
    register_RealParameterWrapper_class();
    register_ResolutionFunction2DSimple_class();
    register_SimpleSelectionRule_class();
    register_Simulation_class();
    register_SimulationParameters_class();
    register_StochasticParameter_t_class();
    register_StochasticDoubleGate_class();
    register_StochasticDoubleGaussian_class();
    register_StochasticSampledParameter_class();
    register_ThreadInfo_class();
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
