 // manually declare which classes can be derived in Python and passed back to C++
 // this can be used to reduce the bloat in the swig-generated code
 
%feature("director") ISampleBuilder;
%feature("director") INamed;
%feature("director") INamedShared;
%feature("director") IParameterized;
%feature("director") IParameterizedShared;
%feature("director") IParameterizedTemplate<ICloneable>;
%feature("director") IParameterizedTemplate<IShareable>;
%feature("director") ISample;
%feature("director") IFormFactor;
%feature("director") IFormFactorBorn;
%feature("director") IFitObserver;
%feature("director") IObservable;

 
