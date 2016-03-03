#ifndef PYTHONFITEXPOSER_H
#define PYTHONFITEXPOSER_H

#include "Types.h"


//! this is special namespace to help Py++ generate correct names
namespace pyplusplus {
    namespace aliases {
    typedef std::vector<double > vdouble1d_t;
    typedef std::vector<vdouble1d_t > vdouble2d_t;
    typedef std::vector<complex_t > vcomplex1d_t;
    typedef std::vector<std::string > vector_string_t;
    }
}


//! functions to help Py++ with template instantiation
namespace pyplusplus {
    inline size_t pyplusplus_boost_vdouble1d() { return sizeof(pyplusplus::aliases::vdouble1d_t); }
    inline size_t pyplusplus_boost_vcomplex1d() { return sizeof(pyplusplus::aliases::vcomplex1d_t); }
    inline size_t pyplusplus_boost_vector_string() { return sizeof(pyplusplus::aliases::vector_string_t); }
}

#endif // PYTHONFITEXPOSER_H
