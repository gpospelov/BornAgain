TARGET   = RootMinimizers

TEMPLATE = lib
QT      -= core gui
macx|unix {
  CONFIG  += plugin # to remove versions from file name
}

include(../../shared.pri)

SOURCES += \
    src/Math/Factory.cxx \
    src/Math/GenAlgoOptions.cxx \
    src/Math/MinimizerOptions.cxx \
    src/Math/MinimizerVariableTransformation.cxx \
    src/Math/MinimTransformFunction.cxx \
    \
    src/Minuit2/AnalyticalGradientCalculator.cxx \
    src/Minuit2/BasicMinimumError.cxx \
    src/Minuit2/CombinedMinimumBuilder.cxx \
    src/Minuit2/DavidonErrorUpdator.cxx \
    src/Minuit2/FumiliBuilder.cxx \
    src/Minuit2/FumiliErrorUpdator.cxx \
    src/Minuit2/FumiliGradientCalculator.cxx \
    src/Minuit2/FumiliMinimizer.cxx \
    src/Minuit2/FumiliStandardChi2FCN.cxx \
    src/Minuit2/FumiliStandardMaximumLikelihoodFCN.cxx \
    src/Minuit2/HessianGradientCalculator.cxx \
    src/Minuit2/InitialGradientCalculator.cxx \
    src/Minuit2/LaEigenValues.cxx \
    src/Minuit2/LaInnerProduct.cxx \
    src/Minuit2/LaInverse.cxx \
    src/Minuit2/LaOuterProduct.cxx \
    src/Minuit2/LaSumOfElements.cxx \
    src/Minuit2/LaVtMVSimilarity.cxx \
    src/Minuit2/Minuit2Minimizer.cxx \
    src/Minuit2/MnApplication.cxx \
    src/Minuit2/mnbins.cxx \
    src/Minuit2/MnContours.cxx \
    src/Minuit2/MnCovarianceSqueeze.cxx \
    src/Minuit2/mndasum.cxx \
    src/Minuit2/mndaxpy.cxx \
    src/Minuit2/mnddot.cxx \
    src/Minuit2/mndscal.cxx \
    src/Minuit2/mndspmv.cxx \
    src/Minuit2/mndspr.cxx \
    src/Minuit2/MnEigen.cxx \
    src/Minuit2/MnFcn.cxx \
    src/Minuit2/MnFumiliMinimize.cxx \
    src/Minuit2/MnFunctionCross.cxx \
    src/Minuit2/MnGlobalCorrelationCoeff.cxx \
    src/Minuit2/MnHesse.cxx \
    src/Minuit2/MnLineSearch.cxx \
    src/Minuit2/mnlsame.cxx \
    src/Minuit2/MnMachinePrecision.cxx \
    src/Minuit2/MnMinos.cxx \
    src/Minuit2/MnParabolaFactory.cxx \
    src/Minuit2/MnParameterScan.cxx \
    src/Minuit2/MnPlot.cxx \
    src/Minuit2/MnPosDef.cxx \
    src/Minuit2/MnPrint.cxx \
    src/Minuit2/MnScan.cxx \
    src/Minuit2/MnSeedGenerator.cxx \
    src/Minuit2/MnStrategy.cxx \
    src/Minuit2/mnteigen.cxx \
    src/Minuit2/MnTiny.cxx \
    src/Minuit2/mntplot.cxx \
    src/Minuit2/MnUserFcn.cxx \
    src/Minuit2/MnUserParameters.cxx \
    src/Minuit2/MnUserParameterState.cxx \
    src/Minuit2/MnUserTransformation.cxx \
    src/Minuit2/mnvert.cxx \
    src/Minuit2/mnxerbla.cxx \
    src/Minuit2/ModularFunctionMinimizer.cxx \
    src/Minuit2/MPIProcess.cxx \
    src/Minuit2/NegativeG2LineSearch.cxx \
    src/Minuit2/Numerical2PGradientCalculator.cxx \
    src/Minuit2/ParametricFunction.cxx \
    src/Minuit2/ScanBuilder.cxx \
    src/Minuit2/SimplexBuilder.cxx \
    src/Minuit2/SimplexParameters.cxx \
    src/Minuit2/SimplexSeedGenerator.cxx \
    src/Minuit2/SinParameterTransformation.cxx \
    src/Minuit2/SqrtLowParameterTransformation.cxx \
    src/Minuit2/SqrtUpParameterTransformation.cxx \
    src/Minuit2/VariableMetricBuilder.cxx \
    src/Minuit2/VariableMetricEDMEstimator.cxx \
    \ # from MathMore
    src/Math/Derivator.cxx \
    src/Math/GSLDerivator.cxx \
    src/Math/GSLMinimizer1D.cxx \
    src/Math/GSLMinimizer.cxx \
    src/Math/GSLRndmEngines.cxx \
    src/Math/GSLSimAnnealing.cxx \
    src/Math/MultiNumGradFunction.cxx \
    src/Math/GSLNLSMinimizer.cxx \
    src/Math/GSLSimAnMinimizer.cxx \


HEADERS += \
    inc/Fit/BinData.h \
    inc/Fit/BinPoint.h \
    inc/Fit/Chi2FCN.h \
    inc/Fit/DataOptions.h \
    inc/Fit/DataRange.h \
    inc/Fit/DataVectorfwd.h \
    inc/Fit/DataVector.h \
    inc/Fit/FcnAdapter.h \
    inc/Fit/FitConfig.h \
    inc/Fit/FitResult.h \
    inc/Fit/Fitter.h \
    inc/Fit/FitUtil.h \
    inc/Fit/FitUtilParallel.h \
    inc/Fit/LogLikelihoodFCN.h \
    inc/Fit/ParameterSettings.h \
    inc/Fit/PoissonLikelihoodFCN.h \
    inc/Fit/SparseData.h \
    inc/Fit/UnBinData.h \
    \
    inc/Math/Error.h \
    inc/Math/Factory.h \
    inc/Math/FitMethodFunction.h \
    inc/Math/Functor.h \
    inc/Math/GenAlgoOptions.h \
    inc/Math/IFunctionfwd.h \
    inc/Math/IFunction.h \
    inc/Math/IMinimizer1D.h \
    inc/Math/IOptions.h \
    inc/Math/IParamFunctionfwd.h \
    inc/Math/IParamFunction.h \
    inc/Math/Minimizer.h \
    inc/Math/MinimizerOptions.h \
    inc/Math/MinimizerVariable.h \
    inc/Math/MinimizerVariableTransformation.h \
    inc/Math/MinimTransformFunction.h \
    inc/Math/OneDimFunctionAdapter.h \
    inc/Math/Util.h \
    inc/Math/WrappedFunction.h \
    inc/Math/WrappedParamFunction.h \
    \
    inc/Minuit2/ABObj.h \
    inc/Minuit2/ABProd.h  \
    inc/Minuit2/ABSum.h \
    inc/Minuit2/ABTypes.h \
    inc/Minuit2/AnalyticalGradientCalculator.h \
    inc/Minuit2/BasicFunctionGradient.h \
    inc/Minuit2/BasicFunctionMinimum.h \
    inc/Minuit2/BasicMinimumError.h \
    inc/Minuit2/BasicMinimumParameters.h \
    inc/Minuit2/BasicMinimumSeed.h \
    inc/Minuit2/BasicMinimumState.h \
    inc/Minuit2/CombinedMinimizer.h \
    inc/Minuit2/CombinedMinimumBuilder.h \
    inc/Minuit2/ContoursError.h \
    inc/Minuit2/DavidonErrorUpdator.h \
    inc/Minuit2/FCNAdapter.h \
    inc/Minuit2/FCNBase.h \
    inc/Minuit2/FCNGradAdapter.h \
    inc/Minuit2/FCNGradientBase.h \
    inc/Minuit2/FumiliBuilder.h \
    inc/Minuit2/FumiliChi2FCN.h \
    inc/Minuit2/FumiliErrorUpdator.h \
    inc/Minuit2/FumiliFCNAdapter.h \
    inc/Minuit2/FumiliFCNBase.h \
    inc/Minuit2/FumiliGradientCalculator.h \
    inc/Minuit2/FumiliMaximumLikelihoodFCN.h \
    inc/Minuit2/FumiliMinimizer.h \
    inc/Minuit2/FumiliStandardChi2FCN.h \
    inc/Minuit2/FumiliStandardMaximumLikelihoodFCN.h \
    inc/Minuit2/FunctionGradient.h \
    inc/Minuit2/FunctionMinimizer.h \
    inc/Minuit2/FunctionMinimum.h \
    inc/Minuit2/GenericFunction.h \
    inc/Minuit2/GradientCalculator.h \
    inc/Minuit2/HessianGradientCalculator.h \
    inc/Minuit2/InitialGradientCalculator.h \
    inc/Minuit2/LaInverse.h \
    inc/Minuit2/LaOuterProduct.h \
    inc/Minuit2/LaProd.h \
    inc/Minuit2/LaSum.h \
    inc/Minuit2/LASymMatrix.h \
    inc/Minuit2/LAVector.h \
    inc/Minuit2/MatrixInverse.h \
    inc/Minuit2/MinimumBuilder.h \
    inc/Minuit2/MinimumError.h \
    inc/Minuit2/MinimumErrorUpdator.h \
    inc/Minuit2/MinimumParameters.h \
    inc/Minuit2/MinimumSeedGenerator.h \
    inc/Minuit2/MinimumSeed.h \
    inc/Minuit2/MinimumState.h \
    inc/Minuit2/MinosError.h \
    inc/Minuit2/Minuit2Minimizer.h \
    inc/Minuit2/MinuitParameter.h \
    inc/Minuit2/MnApplication.h \
    inc/Minuit2/MnConfig.h \
    inc/Minuit2/MnContours.h \
    inc/Minuit2/MnCovarianceSqueeze.h \
    inc/Minuit2/MnCross.h \
    inc/Minuit2/MnEigen.h \
    inc/Minuit2/MnFcn.h \
    inc/Minuit2/MnFumiliMinimize.h \
    inc/Minuit2/MnFunctionCross.h \
    inc/Minuit2/MnGlobalCorrelationCoeff.h \
    inc/Minuit2/MnHesse.h \
    inc/Minuit2/MnLineSearch.h \
    inc/Minuit2/MnMachinePrecision.h \
    inc/Minuit2/MnMatrix.h \
    inc/Minuit2/MnMigrad.h \
    inc/Minuit2/MnMinimize.h \
    inc/Minuit2/MnMinos.h \
    inc/Minuit2/MnParabolaFactory.h \
    inc/Minuit2/MnParabola.h \
    inc/Minuit2/MnParabolaPoint.h \
    inc/Minuit2/MnParameterScan.h \
    inc/Minuit2/MnPlot.h \
    inc/Minuit2/MnPosDef.h \
    inc/Minuit2/MnPrint.h \
    inc/Minuit2/MnRefCountedPointer.h \
    inc/Minuit2/MnReferenceCounter.h \
    inc/Minuit2/MnScan.h \
    inc/Minuit2/MnSeedGenerator.h \
    inc/Minuit2/MnSimplex.h \
    inc/Minuit2/MnStrategy.h \
    inc/Minuit2/MnTiny.h \
    inc/Minuit2/MnUserCovariance.h \
    inc/Minuit2/MnUserFcn.h \
    inc/Minuit2/MnUserParameters.h \
    inc/Minuit2/MnUserParameterState.h \
    inc/Minuit2/MnUserTransformation.h \
    inc/Minuit2/MnVectorTransform.h \
    inc/Minuit2/ModularFunctionMinimizer.h \
    inc/Minuit2/MPIProcess.h \
    inc/Minuit2/NegativeG2LineSearch.h \
    inc/Minuit2/Numerical2PGradientCalculator.h \
    inc/Minuit2/ParametricFunction.h \
    inc/Minuit2/ScanBuilder.h \
    inc/Minuit2/ScanMinimizer.h \
    inc/Minuit2/SimplexBuilder.h \
    inc/Minuit2/SimplexMinimizer.h \
    inc/Minuit2/SimplexParameters.h \
    inc/Minuit2/SimplexSeedGenerator.h \
    inc/Minuit2/SinParameterTransformation.h \
    inc/Minuit2/SqrtLowParameterTransformation.h \
    inc/Minuit2/SqrtUpParameterTransformation.h \
    inc/Minuit2/StackAllocator.h \
    inc/Minuit2/VariableMetricBuilder.h \
    inc/Minuit2/VariableMetricEDMEstimator.h \
    inc/Minuit2/VariableMetricMinimizer.h \
    inc/Minuit2/VectorOuterProduct.h \
    \ # from MathMore
    inc/Math/Derivator.h \
    inc/Math/GSLFunctionAdapter.h \
    inc/Math/GSLFunctionWrapper.h \
    inc/Math/GSLMinimizer1D.h \
    inc/Math/GSLMinimizer.h \
    inc/Math/GSLRndmEngines.h \
    inc/Math/GSLSimAnnealing.h \
    inc/Math/MultiNumGradFunction.h \
    inc/Math/GSLNLSMinimizer.h \
    inc/Math/GSLSimAnMinimizer.h \
    \
    src/Math/GSL1DMinimizerWrapper.h \
    src/Math/GSLDerivator.h \
    src/Math/GSLFunctionWrapper.h \
    src/Math/GSLMultiFitFunctionAdapter.h \
    src/Math/GSLMultiFitFunctionWrapper.h \
    src/Math/GSLMultiFit.h \
    src/Math/GSLMultiMinFunctionAdapter.h \
    src/Math/GSLMultiMinFunctionWrapper.h \
    src/Math/GSLMultiMinimizer.h \
    src/Math/GSLRngWrapper.h \


#INCLUDEPATH += inc $${RootMathMore_INCLUDEPATH}
#DEPENDPATH += inc $${RootMathMore_INCLUDEPATH}
INCLUDEPATH += inc
DEPENDPATH += inc

QMAKE_CXXFLAGS += -DMATH_NO_PLUGIN_MANAGER -DHAS_MINUIT2 -DR__HAS_MATHMORE

#win32 {
#    DEFINES += BA_CORE_BUILD_DLL
#}

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
isEmpty(MAKEFILE): MAKEFILE="Makefile"
QMAKE_POST_LINK = $$MAKE_COMMAND -f $${MAKEFILE} install
