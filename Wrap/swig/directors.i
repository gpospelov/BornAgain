 // manually declare which classes can be derived in Python and passed back to C++
 // this can be used to reduce the bloat in the swig-generated code

%feature("director") IParameterized;     // needed by ISampleBuilder
%feature("director") ISampleBuilder;     // used in mesocrystal1.py
%feature("director") INode;              // needed by ISample
%feature("director") ISample;            // needed by IFormFactor
%feature("director") IFormFactor;        // needed by IFormFactorBorn
%feature("director") IFormFactorBorn;    // used in CustomFormFactor.py
%feature("director") FitObjective;       // used in custom_objective_function.py
%feature("director") PyCallback;         // used in extendFit.i
%feature("director") PyBuilderCallback;  // used in extendCore.i
%feature("director") PyObserverCallback; // used in extendCore.i

// Propagate python exceptions
// taken from
// https://stackoverflow.com/questions/4811492/swig-reporting-python-exceptions-from-c-code
%feature("director:except") {
    if( $error != NULL ) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch( &ptype, &pvalue, &ptraceback );
        PyErr_Restore( ptype, pvalue, ptraceback );
        PyErr_Print();
        Py_Exit(1);
    }
}
