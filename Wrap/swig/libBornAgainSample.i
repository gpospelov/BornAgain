// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainSample.i
//! @brief     SWIG interface file for libBornAgainSample
//!
//!            Configuration is done in Sample/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainSample"

%include "commons.i"

%include "../../auto/Wrap/doxygenSample.i"

%include "ignoreBase.i"
%include "ignoreSample.i"

// force swig to use move ctor instead of copy ctor
%typemap(out) SlicedParticle %{
    $result = SWIG_NewPointerObj(new $1_ltype(std::move($1)), $&1_descriptor, SWIG_POINTER_OWN);
  %}

%shared_ptr(ISampleBuilder)

%feature("director") ISampleBuilder;     // used in mesocrystal1.py
%feature("director") ISample;            // needed by IFormFactor
%feature("director") IFormFactor;        // needed by IFormFactorBorn
%feature("director") IFormFactorBorn;    // used in CustomFormFactor.py

%{
#include "Sample/Aggregate/IInterferenceFunction.h"
#include "Sample/Aggregate/InterferenceFunction1DLattice.h"
#include "Sample/Aggregate/InterferenceFunction2DLattice.h"
#include "Sample/Aggregate/InterferenceFunction2DParaCrystal.h"
#include "Sample/Aggregate/InterferenceFunction2DSuperLattice.h"
#include "Sample/Aggregate/InterferenceFunction3DLattice.h"
#include "Sample/Aggregate/InterferenceFunctionFinite2DLattice.h"
#include "Sample/Aggregate/InterferenceFunctionFinite3DLattice.h"
#include "Sample/Aggregate/InterferenceFunctionHardDisk.h"
#include "Sample/Aggregate/InterferenceFunctionNone.h"
#include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Sample/Aggregate/InterferenceFunctionTwin.h"
#include "Sample/Aggregate/ParticleLayout.h"
#include "Sample/Correlations/FTDecay1D.h"
#include "Sample/Correlations/FTDecay2D.h"
#include "Sample/Correlations/FTDistributions1D.h"
#include "Sample/Correlations/FTDistributions2D.h"
#include "Sample/Correlations/ILayout.h"
#include "Sample/Correlations/IPeakShape.h"
#include "Sample/HardParticle/FormFactorAnisoPyramid.h"
#include "Sample/HardParticle/FormFactorBar.h"
#include "Sample/HardParticle/FormFactorBox.h"
#include "Sample/HardParticle/FormFactorCantellatedCube.h"
#include "Sample/HardParticle/FormFactorCone.h"
#include "Sample/HardParticle/FormFactorCone6.h"
#include "Sample/HardParticle/FormFactorCosineRipple.h"
#include "Sample/HardParticle/FormFactorCuboctahedron.h"
#include "Sample/HardParticle/FormFactorCylinder.h"
#include "Sample/HardParticle/FormFactorDodecahedron.h"
#include "Sample/HardParticle/FormFactorDot.h"
#include "Sample/HardParticle/FormFactorEllipsoidalCylinder.h"
#include "Sample/HardParticle/FormFactorFullSphere.h"
#include "Sample/HardParticle/FormFactorFullSpheroid.h"
#include "Sample/HardParticle/FormFactorHemiEllipsoid.h"
#include "Sample/HardParticle/FormFactorHollowSphere.h"
#include "Sample/HardParticle/FormFactorIcosahedron.h"
#include "Sample/HardParticle/FormFactorLongBoxGauss.h"
#include "Sample/HardParticle/FormFactorLongBoxLorentz.h"
#include "Sample/HardParticle/FormFactorPrism3.h"
#include "Sample/HardParticle/FormFactorPrism6.h"
#include "Sample/HardParticle/FormFactorPyramid.h"
#include "Sample/HardParticle/FormFactorSawtoothRipple.h"
#include "Sample/HardParticle/FormFactorTetrahedron.h"
#include "Sample/HardParticle/FormFactorTruncatedCube.h"
#include "Sample/HardParticle/FormFactorTruncatedSphere.h"
#include "Sample/HardParticle/FormFactorTruncatedSpheroid.h"
#include "Sample/HardParticle/IFormFactorPolyhedron.h"
#include "Sample/HardParticle/IFormFactorPrism.h"
#include "Sample/Lattice/ILatticeOrientation.h"
#include "Sample/Lattice/ISelectionRule.h"
#include "Sample/Lattice/Lattice.h"
#include "Sample/Lattice/Lattice2D.h"
#include "Sample/Lattice/LatticeUtils.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Material/WavevectorInfo.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/LayerInterface.h"
#include "Sample/Multilayer/LayerRoughness.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/Particle/Crystal.h"
#include "Sample/Particle/FormFactorCrystal.h"
#include "Sample/Particle/FormFactorWeighted.h"
#include "Sample/Particle/IAbstractParticle.h"
#include "Sample/Particle/IClusteredParticles.h"
#include "Sample/Particle/IParticle.h"
#include "Sample/Particle/MesoCrystal.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleComposition.h"
#include "Sample/Particle/ParticleCoreShell.h"
#include "Sample/Particle/ParticleDistribution.h"
#include "Sample/Particle/SlicedParticle.h"
#include "Sample/RT/SimulationOptions.h"
#include "Sample/SampleBuilderEngine/ISampleBuilder.h"
#include "Sample/Scattering/IFormFactorDecorator.h"
#include "Sample/Scattering/ISample.h"
#include "Sample/Scattering/Rotations.h"
#include "Sample/SoftParticle/FormFactorGauss.h"
#include "Sample/SoftParticle/FormFactorSphereGaussianRadius.h"
#include "Sample/SoftParticle/FormFactorSphereLogNormalRadius.h"
#include "Sample/StandardSamples/SampleBuilderFactory.h"
%}

%include "fromBase.i"

%include "fromParam.i"

%newobject InterferenceFunction2DLattice::createSquare(double lattice_length, double xi);
%newobject InterferenceFunction2DLattice::createHexagonal(double lattice_length, double xi);
%newobject InterferenceFunction2DParaCrystal::createSquare(
        double lattice_length, double damping_length, double domain_size_1, double domain_size_2);
%newobject InterferenceFunction2DParaCrystal::createHexagonal(
        double lattice_length, double damping_length, double domain_size_1, double domain_size_2);
%newobject InterferenceFunction2DSuperLattice::createSquare(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunction2DSuperLattice::createHexagonal(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunctionFinite2DLattice::createSquare(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunctionFinite2DLattice::createHexagonal(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);

%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;

%template(vector_IFormFactorPtr_t) std::vector<IFormFactor*>;

%include "Fit/TestEngine/IFactory.h"
%template(SampleBuilderFactoryTemp) IFactory<std::string, ISampleBuilder>;

%include "Sample/Material/Material.h"
%include "Sample/Material/MaterialFactoryFuncs.h"
%include "Sample/Material/WavevectorInfo.h"

%include "Sample/RT/SimulationOptions.h"

%include "Sample/Scattering/ISample.h"
%include "Sample/Scattering/IFormFactor.h"
%include "Sample/Scattering/IFormFactorBorn.h"
%include "Sample/Scattering/IFormFactorDecorator.h"

%include "Sample/Scattering/Rotations.h"

%include "Sample/Particle/FormFactorCrystal.h"
%include "Sample/Particle/FormFactorWeighted.h"
%include "Sample/Particle/IAbstractParticle.h"
%include "Sample/Particle/IClusteredParticles.h"
%include "Sample/Particle/Crystal.h"
%include "Sample/Particle/IParticle.h"
%include "Sample/Particle/MesoCrystal.h"
%include "Sample/Particle/Particle.h"
%include "Sample/Particle/ParticleComposition.h"
%include "Sample/Particle/ParticleCoreShell.h"
%include "Sample/Particle/ParticleDistribution.h"

%include "Sample/Correlations/FTDecay1D.h"
%include "Sample/Correlations/FTDecay2D.h"
%include "Sample/Correlations/FTDistributions1D.h"
%include "Sample/Correlations/FTDistributions2D.h"
%include "Sample/Correlations/FTDecay1D.h"
%include "Sample/Correlations/FTDecay2D.h"
%include "Sample/Correlations/ILayout.h"
%include "Sample/Correlations/IPeakShape.h"

%include "Sample/Aggregate/IInterferenceFunction.h"
%include "Sample/Aggregate/InterferenceFunction1DLattice.h"
%include "Sample/Aggregate/InterferenceFunction2DLattice.h"
%include "Sample/Aggregate/InterferenceFunction2DParaCrystal.h"
%include "Sample/Aggregate/InterferenceFunction2DSuperLattice.h"
%include "Sample/Aggregate/InterferenceFunction3DLattice.h"
%include "Sample/Aggregate/InterferenceFunctionFinite2DLattice.h"
%include "Sample/Aggregate/InterferenceFunctionFinite3DLattice.h"
%include "Sample/Aggregate/InterferenceFunctionHardDisk.h"
%include "Sample/Aggregate/InterferenceFunctionNone.h"
%include "Sample/Aggregate/InterferenceFunctionRadialParaCrystal.h"
%include "Sample/Aggregate/InterferenceFunctionTwin.h"
%include "Sample/Aggregate/ParticleLayout.h"

%include "Sample/Multilayer/Layer.h"
%include "Sample/Multilayer/LayerRoughness.h"
%include "Sample/Multilayer/MultiLayer.h"

// SWIG workaround for using axes units the same way as they are used in cpp files
%rename(RoughnessModel) RoughnessModelWrap;
%include "Sample/Multilayer/RoughnessModels.h"

%include "Sample/HardParticle/IFormFactorPolyhedron.h"
%include "Sample/HardParticle/IFormFactorPrism.h"
%include "Sample/HardParticle/IProfileRipple.h"

%include "Sample/HardParticle/FormFactorAnisoPyramid.h"
%include "Sample/HardParticle/FormFactorBox.h"
%include "Sample/HardParticle/FormFactorCantellatedCube.h"
%include "Sample/HardParticle/FormFactorCone.h"
%include "Sample/HardParticle/FormFactorCone6.h"
%include "Sample/HardParticle/FormFactorCosineRipple.h"
%include "Sample/HardParticle/FormFactorCuboctahedron.h"
%include "Sample/HardParticle/FormFactorCylinder.h"
%include "Sample/HardParticle/FormFactorDodecahedron.h"
%include "Sample/HardParticle/FormFactorDot.h"
%include "Sample/HardParticle/FormFactorEllipsoidalCylinder.h"
%include "Sample/HardParticle/FormFactorFullSphere.h"
%include "Sample/HardParticle/FormFactorFullSpheroid.h"
%include "Sample/HardParticle/FormFactorHemiEllipsoid.h"
%include "Sample/HardParticle/FormFactorHollowSphere.h"
%include "Sample/HardParticle/FormFactorIcosahedron.h"
%include "Sample/HardParticle/FormFactorLongBoxGauss.h"
%include "Sample/HardParticle/FormFactorLongBoxLorentz.h"
%include "Sample/HardParticle/FormFactorPrism3.h"
%include "Sample/HardParticle/FormFactorPrism6.h"
%include "Sample/HardParticle/FormFactorPyramid.h"
%include "Sample/HardParticle/FormFactorSawtoothRipple.h"
%include "Sample/HardParticle/FormFactorTetrahedron.h"
%include "Sample/HardParticle/FormFactorTruncatedCube.h"
%include "Sample/HardParticle/FormFactorTruncatedSphere.h"
%include "Sample/HardParticle/FormFactorTruncatedSpheroid.h"

%include "Sample/SoftParticle/FormFactorGauss.h"
%include "Sample/SoftParticle/FormFactorSphereGaussianRadius.h"
%include "Sample/SoftParticle/FormFactorSphereLogNormalRadius.h"

%include "Sample/Lattice/ILatticeOrientation.h"
%include "Sample/Lattice/ISelectionRule.h"
%include "Sample/Lattice/Lattice.h"
%include "Sample/Lattice/Lattice2D.h"
%include "Sample/Lattice/LatticeUtils.h"

%include "Sample/SampleBuilderEngine/ISampleBuilder.h"
%include "Sample/StandardSamples/SampleBuilderFactory.h"

%extend BasicVector3D<double> {
    BasicVector3D<double> __add__(const BasicVector3D<double>& rhs) const {
        return *($self) + rhs; }
    BasicVector3D<double> __mul__(double c) const {
        return c * *($self); }
    BasicVector3D<double> __rmul__(double c) const {
        return *($self) * c; }
    BasicVector3D<double> __neg__() const {
        return - *($self); }
};

%extend ISampleBuilder {
    virtual RealParameter* registerParameter(const std::string& name, int64_t parpointer) {
        return &(($self)->IParameterized::registerParameter(name, (double*)parpointer)); }

    virtual void setParameterValue(const std::string& name, double value) {
        ($self)->IParameterized::setParameterValue(name, value); }

    virtual std::string parametersToString() const {
        return ($self)->IParameterized::parametersToString();
        }

    virtual ParameterPool* createParameterTree() const {
        return ($self)->IParameterized::createParameterTree();
        }

    virtual ParameterPool* parameterPool() const {
        return ($self)->IParameterized::parameterPool();
    }

    virtual void onChange() {
        return ($self)->IParameterized::onChange();
    }

};
