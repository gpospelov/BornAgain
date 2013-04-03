// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/inc/PythonPlusplusHelper.h
//! @brief     Defines class PythonPlusplusHelper, and namespace pypluslus::aliases.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYTHONPLUSPLUSHELPER_H
#define PYTHONPLUSPLUSHELPER_H

#include "Types.h"
#include "BasicVector3D.h"
#include "DiffuseParticleInfo.h"
#include "IFormFactor.h"
#include "MaterialManager.h"
#include "IStochasticParameter.h"
#include "OutputData.h"
#include "ITransform3D.h"
#include "boost/shared_ptr.hpp"

//! this is special namespace to help Py++ generate correct names
namespace pyplusplus {
    namespace aliases {
        using namespace Geometry;
        //typedef Geometry::BasicVector3D<double > kvector_t;
        typedef BasicVector3D<double > kvector_t;
        typedef std::vector<kvector_t > vector_kvector_t;
        typedef BasicVector3D<std::complex<double> > cvector_t;
        typedef std::vector<cvector_t > vector_cvector_t;
        typedef std::vector<DiffuseParticleInfo *> vector_DiffuseParticleInfoPtr_t;
        typedef std::vector<IFormFactor *> vector_IFormFactorPtr_t;
        typedef ISingleton<MaterialManager> MaterialManagerSingleton_t;
        typedef StochasticParameter<double> StochasticParameter_t;
        typedef OutputData<double > ndimdata_t;
        typedef std::vector<int > vector_integer_t;
        typedef std::vector<unsigned long int > vector_longinteger_t;
        static const kvector_t dummy1 = 2.0*kvector_t(0,0,0);
        static const kvector_t dummy2 = kvector_t(0,0,0)*2.0;
        static const kvector_t dummy3 = kvector_t(0,0,0)/2.0;
        //typedef boost::shared_ptr<Geometry::ITransform3D> PTransform3D;
    }
}

//typedef boost::shared_ptr<Geometry::ITransform3D> ITransform3D_sptr;
//ITransform3D_sptr create_shared();



//! helper class to provide Py++ with explicit template instantiations

class PythonPlusplusHelper
{
 public:
//    size_t pyplusplus_boost_kvector() { return sizeof(kvector_t); }
    size_t pyplusplus_boost_kvector() { return sizeof(pyplusplus::aliases::kvector_t); }
    size_t pyplusplus_boost_vectorof_kvector() { return sizeof(pyplusplus::aliases::vector_kvector_t); }
    size_t pyplusplus_boost_cvector() { return sizeof(pyplusplus::aliases::cvector_t); }
    size_t pyplusplus_boost_vectorof_cvector() { return sizeof(pyplusplus::aliases::vector_cvector_t); }
    size_t pyplusplus_boost_vectorof_DiffuseParticleInfoPtr() { return sizeof(pyplusplus::aliases::vector_DiffuseParticleInfoPtr_t); }
    size_t pyplusplus_boost_stochastic_parameter() { return sizeof(pyplusplus::aliases::StochasticParameter_t); }
    size_t pyplusplus_boost_outputdata() { return sizeof(pyplusplus::aliases::ndimdata_t); }
    //size_t pypluspus_boost_ptransform() { return sizeof(pyplusplus::aliases::PTransform3D); }
    //size_t pyplusplus_boost_kvector2() { return sizeof(pyplusplus::aliases::kvector_t); }
};

//! helper function to set value via subscript operator from python
template <class Self, class Key, class Value>
void pyplusplus_setitem(Self& self, Key const& key, Value const& value)
{
    self[key] = value;
}


namespace pyplusplus {

//  inline Geometry::BasicVector3D<double>
//  operator+(const Geometry::BasicVector3D<double> & v) { return v; }

////  inline Geometry::BasicVector3D<double>
////  operator+(const Geometry::BasicVector3D<double> & a,const BasicVector3D<double> & b) {
////    return BasicVector3D<double>(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
////  }

//  inline Geometry::BasicVector3D<double>
//  operator-(const Geometry::BasicVector3D<double> & v) {
//    return Geometry::BasicVector3D<double>(-v.x(), -v.y(), -v.z());
//  }

////    inline BasicVector3D<double>
////    operator-(const BasicVector3D<double> & a,const BasicVector3D<double> & b) {
////      return BasicVector3D<double>(a.x()-b.x(), a.y()-b.y(), a.z()-b.z());
////    }

//    inline Geometry::BasicVector3D<double>
//    operator*(const Geometry::BasicVector3D<double> & v, double a) {
//      return Geometry::BasicVector3D<double>(v.x()*a, v.y()*a, v.z()*a);
//    }

////    /**
////     * Scalar product of two vectors.
////     * @relates BasicVector3D
////     */
////    inline double
////    operator*(const BasicVector3D<double> & a,const BasicVector3D<double> & b) {
////      return a.dot(b);
////    }

//      inline Geometry::BasicVector3D<double>
//      operator*(double a, const Geometry::BasicVector3D<double> & v) {
//        return Geometry::BasicVector3D<double>(a*v.x(), a*v.y(), a*v.z());
//      }

//      inline Geometry::BasicVector3D<double>
//      operator/(const Geometry::BasicVector3D<double> & v, double a) {
//        return Geometry::BasicVector3D<double>(v.x()/a, v.y()/a, v.z()/a);
//      }

////      /**
////       * Comparison of two vectors for equality.
////       * @relates BasicVector3D
////       */
////      inline bool
////      operator==(const BasicVector3D<double> & a, const BasicVector3D<double> & b)
////      {
////        return (a.x()==b.x() && a.y()==b.y() && a.z()==b.z());
////      }

////      /**
////       * Comparison of two vectors for inequality.
////       * @relates BasicVector3D
////       */
////      inline bool
////      operator!=(const BasicVector3D<double> & a, const BasicVector3D<double> & b)
////      {
////        return (a.x()!=b.x() || a.y()!=b.y() || a.z()!=b.z());
////      }

////      inline BasicVector3D<double> CrossProduct(const BasicVector3D<double> &vectorLeft, const BasicVector3D<double> &vectorRight)
////        {
////            double x = vectorLeft.y()*vectorRight.z() - vectorLeft.z()*vectorRight.y();
////            double y = vectorLeft.z()*vectorRight.x() - vectorLeft.x()*vectorRight.z();
////            double z = vectorLeft.x()*vectorRight.y() - vectorLeft.y()*vectorRight.x();
////            return BasicVector3D<double> (x, y, z);
////        }

////        inline double DotProduct(const BasicVector3D<double> &left, const BasicVector3D<double> &right)
////        {
////            return left.x()*right.x() + left.y()*right.y() + left.z()*right.z();
////        }

//template Geometry::BasicVector3D<double> operator* <Geometry::BasicVector3D<double>, double> (const Geometry::BasicVector3D<double>& v, double a);

// to push gccxml to instantiate templates
//typedef foo<int>::foo foo_int;

}

#endif // PYTHONPLUSPLUSHELPER_H


