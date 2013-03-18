# -----------------------------------------------------------------------------
# qmake project file to compile libBornAgainCore
# -----------------------------------------------------------------------------

TARGET   = BornAgainCore
TEMPLATE = lib
CONFIG  += plugin # to remove versions from file name
QT      -= core gui
CONFIG  += BORNAGAIN_PYTHON
QMAKE_EXTENSION_SHLIB = so # making standard *.so extension

# -----------------------------------------------------------------------------
# source and headers
# -----------------------------------------------------------------------------
SOURCES += \
    Algorithms/src/Beam.cpp \
    Algorithms/src/ChiSquaredFrequency.cpp \
    Algorithms/src/ChiSquaredModule.cpp \
    Algorithms/src/ConvolutionDetectorResolution.cpp \
    Algorithms/src/DecouplingApproximationStrategy.cpp \
    Algorithms/src/Detector.cpp \
    Algorithms/src/DiffuseDWBASimulation.cpp \
    Algorithms/src/DWBADiffuseReflection.cpp \
    Algorithms/src/DWBASimulation.cpp \
    Algorithms/src/Simulation.cpp \
    Algorithms/src/FTDistributions.cpp \
    Algorithms/src/IChiSquaredModule.cpp \
    Algorithms/src/IFittingDataSelector.cpp \
    Algorithms/src/Instrument.cpp \
    Algorithms/src/IOutputDataNormalizer.cpp \
    Algorithms/src/IsGISAXSMorphologyFileStrategy.cpp \
    Algorithms/src/LayerDecoratorDWBASimulation.cpp \
    Algorithms/src/StrategyBuilder.cpp \
    Algorithms/src/LayerDWBASimulation.cpp \
    Algorithms/src/LocalMonodisperseApproximationStrategy.cpp \
    Algorithms/src/Mask.cpp \
    Algorithms/src/MaskCoordinateFunction.cpp \
    Algorithms/src/MultiLayerDWBASimulation.cpp \
    Algorithms/src/MultiLayerRoughnessDWBASimulation.cpp \
    Algorithms/src/OpticalFresnel.cpp \
    Algorithms/src/ResolutionFunction2DSimple.cpp \
    Algorithms/src/SizeSpacingCorrelationApproximationStrategy.cpp \
    \
    Fitting/src/FitObject.cpp \
    Fitting/src/FitParameter.cpp \
    Fitting/src/FitParameterLinked.cpp \
    Fitting/src/FitSuite.cpp \
    Fitting/src/FitSuiteFunctions.cpp \
    Fitting/src/FitSuiteObjects.cpp \
    Fitting/src/FitSuiteParameters.cpp \
    Fitting/src/FitSuiteStrategies.cpp \
    Fitting/src/IFitSuiteStrategy.cpp \
    Fitting/src/MinimizerScan.cpp \
    Fitting/src/MinimizerTest.cpp \
    \
    FormFactors/src/FormFactorBox.cpp \
    FormFactors/src/FormFactorCone.cpp \
    FormFactors/src/FormFactorCrystal.cpp \
    FormFactors/src/FormFactorCylinder.cpp \
    FormFactors/src/FormFactorDecoratorTransformation.cpp \
    FormFactors/src/FormFactorDWBA.cpp \
    FormFactors/src/FormFactorDWBAConstZ.cpp \
    FormFactors/src/FormFactorEllipsoid.cpp \
    FormFactors/src/FormFactorFullSphere.cpp \
    FormFactors/src/FormFactorFullSpheroid.cpp \
    FormFactors/src/FormFactorGauss.cpp \
    FormFactors/src/FormFactorHemiSpheroid.cpp \
    FormFactors/src/FormFactorLorentz.cpp \
    FormFactors/src/FormFactorParallelepiped.cpp \
    FormFactors/src/FormFactorPrism3.cpp \
    FormFactors/src/FormFactorPrism6.cpp \
    FormFactors/src/FormFactorPyramid.cpp \
    FormFactors/src/FormFactorSphere.cpp \
    FormFactors/src/FormFactorWeighted.cpp \
    FormFactors/src/IFormFactorBorn.cpp \
    \
    Geometry/src/BasicVector3D.cpp \
    Geometry/src/Normal3D.cpp \
    Geometry/src/Plane3D.cpp \
    Geometry/src/Point3D.cpp \
    Geometry/src/Transform3D.cpp \
    Geometry/src/Vector3D.cpp \
    \
    Samples/src/Crystal.cpp \
    Samples/src/DiffuseParticleInfo.cpp \
    Samples/src/HomogeneousMaterial.cpp \
    Samples/src/ICompositeIterator.cpp \
    Samples/src/ICompositeSample.cpp \
    Samples/src/IMaterial.cpp \
    Samples/src/InterferenceFunction1DParaCrystal.cpp \
    Samples/src/InterferenceFunction2DLattice.cpp \
    Samples/src/InterferenceFunction2DParaCrystal.cpp \
    Samples/src/ISample.cpp \
    Samples/src/Lattice.cpp \
    Samples/src/LatticeBasis.cpp \
    Samples/src/Layer.cpp \
    Samples/src/LayerDecorator.cpp \
    Samples/src/LayerInterface.cpp \
    Samples/src/LayerRoughness.cpp \
    Samples/src/MaterialManager.cpp \
    Samples/src/MesoCrystal.cpp \
    Samples/src/MultiLayer.cpp \
    Samples/src/Particle.cpp \
    Samples/src/ParticleBuilder.cpp \
    Samples/src/ParticleCoreShell.cpp \
    Samples/src/ParticleDecoration.cpp \
    Samples/src/ParticleInfo.cpp \
    Samples/src/PositionParticleInfo.cpp \
    \
    Tools/src/AxisBin.cpp \
    Tools/src/AxisDouble.cpp \
    Tools/src/Convolve.cpp \
    Tools/src/CoreOptionsDescription.cpp \
    Tools/src/DoubleToComplexInterpolatingFunction.cpp \
    Tools/src/Exceptions.cpp \
    Tools/src/IFactory.cpp \
    Tools/src/IObserver.cpp \
    Tools/src/IParameterized.cpp \
    Tools/src/ISingleton.cpp \
    Tools/src/MathFunctions.cpp \
    Tools/src/OutputData.cpp \
    Tools/src/OutputDataFunctions.cpp \
    Tools/src/OutputDataIOFactory.cpp \
    Tools/src/OutputDataReadStrategy.cpp \
    Tools/src/OutputDataReader.cpp \
    Tools/src/OutputDataWriteStrategy.cpp \
    Tools/src/OutputDataWriter.cpp \
    Tools/src/ParameterPool.cpp \
    Tools/src/ProgramOptions.cpp \
    Tools/src/RealParameterWrapper.cpp \
    Tools/src/StochasticGaussian.cpp \
    Tools/src/StochasticSampledParameter.cpp \
    Tools/src/Types.cpp \
    Tools/src/Utils.cpp

HEADERS += \
    Algorithms/inc/Beam.h \
    Algorithms/inc/ChiSquaredFrequency.h \
    Algorithms/inc/ChiSquaredModule.h \
    Algorithms/inc/ConvolutionDetectorResolution.h \
    Algorithms/inc/DecouplingApproximationStrategy.h \
    Algorithms/inc/Detector.h \
    Algorithms/inc/DetectorParameters.h \
    Algorithms/inc/DiffuseDWBASimulation.h \
    Algorithms/inc/DWBADiffuseReflection.h \
    Algorithms/inc/DWBASimulation.h \
    Algorithms/inc/Simulation.h \
    Algorithms/inc/FTDistributions.h \
    Algorithms/inc/IChiSquaredModule.h \
    Algorithms/inc/IDetectorResolution.h \
    Algorithms/inc/IFittingDataSelector.h \
    Algorithms/inc/IIntensityFunction.h \
    Algorithms/inc/IInterferenceFunctionStrategy.h \
    Algorithms/inc/Instrument.h \
    Algorithms/inc/InterferenceFunctionStrategies.h \
    Algorithms/inc/IOutputDataNormalizer.h \
    Algorithms/inc/IResolutionFunction2D.h \
    Algorithms/inc/ISampleBuilder.h \
    Algorithms/inc/IsGISAXSMorphologyFileStrategy.h \
    Algorithms/inc/ISimulation.h \
    Algorithms/inc/ISquaredFunction.h \
    Algorithms/inc/LayerDecoratorDWBASimulation.h \
    Algorithms/inc/LayerDWBASimulation.h \
    Algorithms/inc/LocalMonodisperseApproximationStrategy.h \
    Algorithms/inc/Mask.h \
    Algorithms/inc/MaskCoordinateFunction.h \
    Algorithms/inc/MultiLayerDWBASimulation.h \
    Algorithms/inc/MultiLayerRoughnessDWBASimulation.h \
    Algorithms/inc/OpticalFresnel.h \
    Algorithms/inc/ResolutionFunction2DSimple.h \
    Algorithms/inc/SimulationParameters.h \
    Algorithms/inc/SizeSpacingCorrelationApproximationStrategy.h \
    Algorithms/inc/StrategyBuilder.h \
    Algorithms/inc/ThreadInfo.h \
    \
    Fitting/inc/AttLimits.h \
    Fitting/inc/FitObject.h \
    Fitting/inc/FitParameter.h \
    Fitting/inc/FitParameterLinked.h \
    Fitting/inc/FitSuite.h \
    Fitting/inc/FitSuiteFunctions.h \
    Fitting/inc/FitSuiteObjects.h \
    Fitting/inc/FitSuiteParameters.h \
    Fitting/inc/FitSuiteStrategies.h \
    Fitting/inc/IFitSuiteStrategy.h \
    Fitting/inc/IMinimizer.h \
    Fitting/inc/MinimizerScan.h \
    Fitting/inc/MinimizerTest.h \
    \
    FormFactors/inc/FormFactorBox.h \
    FormFactors/inc/FormFactorCone.h \
    FormFactors/inc/FormFactorCrystal.h \
    FormFactors/inc/FormFactorCylinder.h \
    FormFactors/inc/FormFactorDecoratorDebyeWaller.h \
    FormFactors/inc/FormFactorDecoratorFactor.h \
    FormFactors/inc/FormFactorDecoratorMultiPositionFactor.h \
    FormFactors/inc/FormFactorDecoratorPositionFactor.h \
    FormFactors/inc/FormFactorDecoratorRefractiveIndex.h \
    FormFactors/inc/FormFactorDecoratorTransformation.h \
    FormFactors/inc/FormFactorDWBA.h \
    FormFactors/inc/FormFactorDWBAConstZ.h \
    FormFactors/inc/FormFactorEllipsoid.h \
    FormFactors/inc/FormFactorFullSphere.h \
    FormFactors/inc/FormFactorFullSpheroid.h \
    FormFactors/inc/FormFactorGauss.h \
    FormFactors/inc/FormFactorHemiSpheroid.h \
    FormFactors/inc/FormFactorLorentz.h \
    FormFactors/inc/FormFactorParallelepiped.h \
    FormFactors/inc/FormFactorPrism3.h \
    FormFactors/inc/FormFactorPrism6.h \
    FormFactors/inc/FormFactorPyramid.h \
    FormFactors/inc/FormFactorSphere.h \
    FormFactors/inc/FormFactorSphereGaussianRadius.h \
    FormFactors/inc/FormFactorWeighted.h \
    FormFactors/inc/FormFactors.h \
    FormFactors/inc/IFormFactor.h \
    FormFactors/inc/IFormFactorBorn.h \
    FormFactors/inc/IFormFactorBornSeparable.h \
    FormFactors/inc/IFormFactorDecorator.h \
    \
    Geometry/inc/BasicVector3D.h \
    Geometry/inc/Normal3D.h \
    Geometry/inc/Plane3D.h \
    Geometry/inc/Point3D.h \
    Geometry/inc/Transform3D.h \
    Geometry/inc/Transform3D.icc \
    Geometry/inc/Vector3D.h \
    \
    Samples/inc/Crystal.h \
    Samples/inc/DiffuseParticleInfo.h \
    Samples/inc/HomogeneousMaterial.h \
    Samples/inc/IClusteredParticles.h \
    Samples/inc/ICompositeIterator.h \
    Samples/inc/ICompositeSample.h \
    Samples/inc/IDecoration.h \
    Samples/inc/IDispersalState.h \
    Samples/inc/IInterferenceFunction.h \
    Samples/inc/IMaterial.h \
    Samples/inc/InterferenceFunctions.h \
    Samples/inc/InterferenceFunction1DParaCrystal.h \
    Samples/inc/InterferenceFunction2DLattice.h \
    Samples/inc/InterferenceFunction2DParaCrystal.h \
    Samples/inc/InterferenceFunctionNone.h \
    Samples/inc/IRoughness.h \
    Samples/inc/ISample.h \
    Samples/inc/ISelectionRule.h \
    Samples/inc/Lattice.h \
    Samples/inc/Lattice2DIFParameters.h \
    Samples/inc/LatticeBasis.h \
    Samples/inc/Layer.h \
    Samples/inc/LayerDecorator.h \
    Samples/inc/LayerInterface.h \
    Samples/inc/LayerRoughness.h \
    Samples/inc/MaterialManager.h \
    Samples/inc/MesoCrystal.h \
    Samples/inc/MultiLayer.h \
    Samples/inc/Particle.h \
    Samples/inc/ParticleBuilder.h \
    Samples/inc/ParticleCoreShell.h \
    Samples/inc/ParticleDecoration.h \
    Samples/inc/ParticleInfo.h \
    Samples/inc/PositionParticleInfo.h \
    \
    Tools/inc/AxisBin.h \
    Tools/inc/AxisDouble.h \
    Tools/inc/Bin.h \
    Tools/inc/Convolve.h \
    Tools/inc/Coordinate3D.h \
    Tools/inc/CoreOptionsDescription.h \
    Tools/inc/DoubleToComplexInterpolatingFunction.h \
    Tools/inc/DoubleToComplexMap.h \
    Tools/inc/Exceptions.h \
    Tools/inc/FastVector.h \
    Tools/inc/IAxis.h \
    Tools/inc/IChangeable.h \
    Tools/inc/ICloneable.h \
    Tools/inc/IDoubleToComplexFunction.h \
    Tools/inc/IFactory.h \
    Tools/inc/INamed.h \
    Tools/inc/IObserver.h \
    Tools/inc/IParameterized.h \
    Tools/inc/ISingleton.h \
    Tools/inc/IStochasticParameter.h \
    Tools/inc/LLData.h \
    Tools/inc/Macros.h \
    Tools/inc/MathFunctions.h \
    Tools/inc/MemberFunctionIntegrator.h \
    Tools/inc/Numeric.h \
    Tools/inc/OutputData.h \
    Tools/inc/OutputDataFunctions.h \
    Tools/inc/OutputDataIOFactory.h \
    Tools/inc/OutputDataIterator.h \
    Tools/inc/OutputDataReadStrategy.h \
    Tools/inc/OutputDataReader.h \
    Tools/inc/OutputDataWriteStrategy.h \
    Tools/inc/OutputDataWriter.h \
    Tools/inc/ParameterPool.h \
    Tools/inc/ProgramOptions.h \
    Tools/inc/RealParameterWrapper.h \
    Tools/inc/SafePointerVector.h \
    Tools/inc/StochasticDiracDelta.h \
    Tools/inc/StochasticDoubleGate.h \
    Tools/inc/StochasticGaussian.h \
    Tools/inc/StochasticSampledParameter.h \
    Tools/inc/TRange.h \
    Tools/inc/Types.h \
    Tools/inc/Units.h \
    Tools/inc/Utils.h \
    Tools/inc/MemberComplexFunctionIntegrator.h \
    Fitting/inc/AttFitting.h \
    Samples/inc/Samples.h

contains(CONFIG, BORNAGAIN_PYTHON) {
   include($$PWD/python_module.pri)
}


# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
QMAKE_POST_LINK = (make install)

# -----------------------------------------------------------------------------
# general project settings
# -----------------------------------------------------------------------------
include($$PWD/../shared.pri)

