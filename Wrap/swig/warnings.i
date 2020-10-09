// unproblematic warnings, keep them permanently disabled:
#pragma SWIG nowarn=314 // print conflicts with Python, renamed to _print
#pragma SWIG nowarn=315 // nothing known about std::size_t
#pragma SWIG nowarn=362 // operator= ignored
#pragma SWIG nowarn=389 // operator[] ignored, consider %extend
#pragma SWIG nowarn=503 // operator= ignored, consider renaming to valid identifier

// questionable warnings, TODO: reinvestigate
#pragma SWIG nowarn=473 // questionable return pointer
#pragma SWIG nowarn=509 // overloaded method shadowed, effectively ignored
#pragma SWIG nowarn=520 // base class not similarly marked as a smart pointer
