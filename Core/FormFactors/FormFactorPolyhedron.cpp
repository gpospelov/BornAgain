// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPolyhedron.cpp
//! @brief     Implements class FormFactorPolyhedron, and auxiliary classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

//! The mathematics implemented here is described in full detail in a paper
//! by Joachim Wuttke, entitled
//! "Form factor (Fourier shape transform) of polygon and polyhedron."

#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <complex>
#include <vector>

#include "Precomputed.h"
#include "BasicVector3D.h"
#include "MathFunctions.h"

typedef std::complex<double> complex_t;
typedef Geometry::BasicVector3D<complex_t> cvector_t;
typedef Geometry::BasicVector3D<double> kvector_t;
#include "IFormFactorBorn.h"
#include "FormFactorPolyhedron.h"

static complex_t I(0.,1.);
static double eps(2e-16);

#ifdef POLYHEDRAL_DIAGNOSTIC
extern Diagnosis diagnosis;
#endif

//***************************************************************************************************
//  PolyhedralEdge implementation
//***************************************************************************************************

PolyhedralEdge::PolyhedralEdge( const kvector_t _Vlow, const kvector_t _Vhig )
    : E((_Vhig-_Vlow)/2)
    , R((_Vhig+_Vlow)/2)
{
    if( E.mag2()==0 ) {
        std::ostringstream msg;
        msg<<"zero-length edge between "<<_Vlow<<" and "<<_Vhig;
        throw std::runtime_error(msg.str());
    }
};

//! Returns the contribution of this edge to the form factor.

complex_t PolyhedralEdge::contrib(int m, cvector_t prevec, cvector_t q) const
{
    complex_t prefac = prevec.dot(E); // conj(prevec)*E [BasicVector3D::dot is antilinear in 'this']
    complex_t u = E.dot(q);
    complex_t v = R.dot(q);
    static auto& precomputed = IPrecomputed::instance();
    if( u==0. ) { // only l=0 contributes
        return prefac * pow(v, m+1) / precomputed.factorial[m+1];
    } else if( v==0. ) { // only 2l=m+1 contributes
        if( m&1 ) // m is odd
            return prefac * pow(u, m+1) / precomputed.factorial[m+2];
        else
            return 0.;
    } else {
        complex_t ret = 0;
        for( int l=0; l<=(m+1)/2; ++l )
            ret += pow(u, 2*l) * pow(v, m+1-2*l) /
                precomputed.factorial[m+1-2*l] / precomputed.factorial[2*l+1];
        return prefac * ret;
    }
}

//***************************************************************************************************
//  PolyhedralFace implementation
//***************************************************************************************************

const double PolyhedralFace::qpa_limit_series = 1e-3;

//! Sets internal variables for given vertex chain.

PolyhedralFace::PolyhedralFace( const std::vector<kvector_t>& V, bool _sym_S2 )
    : sym_S2( _sym_S2 )
{
    size_t N = V.size();
    if( !N )
        return; // we would forbid these calls altogether, but swig requires constructor()
    // compute edges
    for ( size_t j=0; j<N; ++j ) {
        size_t jj = (j+1)%N;
        edges.push_back( PolyhedralEdge(V[j], V[jj]) );
    }
    // compute n_k, rperp
    normal = kvector_t();
    for( size_t j=0; j<N; ++j ){
        size_t jj = (j+1)%N;
        kvector_t ee = edges[j].E.cross( edges[jj].E );
        if( ee.mag2()==0 ) {
            std::ostringstream msg;
            size_t jjj = (j+2)%N;
            msg<<"parallel edges between V["<<j<<"]="<<V[j]<<
                " and V["<<jj<<"]="<<V[jj]<<
                " and  V["<<jjj<<"]="<<V[jjj];
            throw std::runtime_error(msg.str());
        }
        normal += ee.unit();
    }
    normal /= N;
    rperp = 0;
    for( size_t j=0; j<N; ++j )
        rperp += V[j].dot(normal);
    rperp /= N;
    // compute radius in 3d
    radius_3d = 0;
    for( const kvector_t v: V )
        radius_3d = std::max( radius_3d, v.mag() );
    // assert that the vertices lay in a plane
    for ( size_t j=1; j<N; ++j )
        if( std::abs(V[j].dot(normal) - rperp) > 1e-14*radius_3d )
            throw std::runtime_error("Face is not planar");
    // compute area
    area = 0;
    for ( size_t j=0; j<N; ++j ) {
        size_t jj = (j+1)%N;
        area += normal.dot( V[j].cross( V[jj] ) ) / 2;
    }
    // compute radius in 2d
    radius_2d = 0;
    for( const kvector_t v: V )
        radius_2d = std::max( radius_2d, (v-rperp*normal).mag() );

    // only now deal with inversion symmetry
    if( sym_S2 ) {
        if( N&1 )
            throw std::runtime_error("Odd #edges violates symmetry S2");
        N /= 2;
        for( size_t j=0; j<N; ++j ){
            if( ((V[j]-rperp*normal)+(V[j+N]-rperp*normal)).mag2()>1e-24*radius_2d*radius_2d )
                throw std::runtime_error("Given points violate symmetry S2");
        }
        // keep only half of the egdes
        edges.erase( edges.begin()+N, edges.end() );
    }
}

//! Returns area of this polygon
double PolyhedralFace::getArea() const { return area; }

//! Returns volume of pyramid spanned by the origin and this polygon
double PolyhedralFace::getPyramidalVolume() const { return rperp*area/3; }

//! Sets qperp and qpa according to argument q and to this polygon's normal.

void PolyhedralFace::decompose_q( const cvector_t q, complex_t& qperp, cvector_t qpa ) const
{
    qperp = normal.dot(q);
    qpa = q - qperp*normal;
    // improve numeric accuracy:
    qpa -= normal.dot(qpa)*normal;
    if( qpa.mag()<eps*std::abs(qperp) )
        qpa = cvector_t(0.,0.,0.);
}

//! Returns core contribution to f_n

complex_t PolyhedralFace::ff_n_core( int m, const cvector_t q ) const
{
    cvector_t prevec = 2.*normal.cross( q ); // complex conjugation will take place in .dot
    complex_t ret = 0;
    for( const PolyhedralEdge& e: edges )
        ret += e.contrib(m, prevec, q);
    return ret;
}

//! Returns contribution qn*f_n [of order q^(n+1)] from this face to the polyhedral form factor.

complex_t PolyhedralFace::ff_n( int n, const cvector_t q ) const
{
    complex_t qn = q.dot(normal); // conj(q)*normal (BasicVector3D::dot is antilinear in 'this' argument)
    if ( std::abs(qn)<eps*q.mag() )
        return 0.;
    complex_t qperp;
    cvector_t qpa;
    decompose_q( q, qperp, qpa );
    double qpa_mag2 = qpa.mag2();
    static auto& precomputed = IPrecomputed::instance();
    if ( qpa_mag2==0. ) {
        return qn * pow(qperp*rperp, n) * area / precomputed.factorial[n];
    } else if ( sym_S2 ) {
        return qn * ( ff_n_core( n, q ) + ff_n_core( n, qperp*normal-qpa ) ) / qpa_mag2;
    } else {
        return qn * ff_n_core( n, q ) / qpa_mag2;
    }
}

//! Returns the contribution of this face to the polyhedral form factor.

complex_t PolyhedralFace::ff( const cvector_t q, const bool sym_Ci ) const
{
    complex_t qn = q.dot(normal); // conj(q)*normal (BasicVector3D::dot is antilinear in 'this' argument)
    if ( std::abs(qn)<eps*q.mag() )
        return 0;
    complex_t qperp;
    cvector_t qpa;
    decompose_q( q, qperp, qpa );
    double qpa_red = radius_2d * qpa.mag();
    complex_t qr_perp = qperp*rperp;
    if ( qpa_red==0 ) {
        return qn * (sym_Ci ? 2.*I*sin(qr_perp) : exp(I*qr_perp)) * area;
    } else if ( qpa_red < qpa_limit_series && !sym_S2 ) {
        // summation of power series
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis.nExpandedFaces += 1;
#endif
        complex_t fac_even;
        complex_t fac_odd;
        if( sym_Ci ) {
            fac_even = qn * 2. * I * sin(qr_perp);
            fac_odd = qn * 2. * cos(qr_perp);
        } else {
            fac_even = qn * exp( I*qr_perp );
            fac_odd = fac_even;
        }
        complex_t sum = fac_even * area;
        complex_t n_fac = I;
        for( int n=1; n<20; ++n ) {
#ifdef POLYHEDRAL_DIAGNOSTIC
            diagnosis.maxOrder = std::max( diagnosis.maxOrder, n );
#endif
            complex_t term = n_fac * ( n&1 ? fac_odd : fac_even ) * ff_n_core(n, qpa) / qpa.mag2();
            sum += term;
            if( !(n&1) && std::abs(term)<=eps*std::abs(sum) )
                return sum;
            n_fac *= I;
        }
        throw std::runtime_error("Bug in formfactor computation: series f(q_pa) not converged");
    } else {
        // direct evaluation of analytic formula
        cvector_t prevec = 2.*normal.cross( qpa ); // complex conjugation will take place in .dot
        complex_t prefac = qn;
        if( sym_S2 )
            prefac *= sym_Ci ? -4.*sin(qr_perp) : 2.*I*exp(I*qr_perp);
        complex_t sum = 0;
        for( const PolyhedralEdge& e: edges ) {
            complex_t qE = e.E.dot(q);
            complex_t qR = e.R.dot(q);
            complex_t sinc_qE = MathFunctions::sinc(qE);
            complex_t Rfac = sym_S2 ? sin(e.R.dot(qpa)) : ( sym_Ci ? 2.*cos(qR) : exp(I*qR) );
            sum += prevec.dot(e.E) * (sinc_qE*Rfac);
        }
        return prefac * sum / ( I*qpa.mag2() );
    }
}

//! Returns the two-dimensional form factor of this face, for use in a prism.

complex_t PolyhedralFace::ff_2D( const cvector_t qpa ) const
{
    if ( std::abs(qpa.dot(normal))>eps*qpa.mag() )
        throw std::runtime_error("ff_2D called with perpendicular q component");
    double qpa_red = radius_2d * qpa.mag();
    if ( qpa_red==0 ) {
        return area;
    } else if ( qpa_red < qpa_limit_series ) {
        // summation of power series
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis.nExpandedFaces += 1;
#endif
        complex_t sum = area;
        complex_t n_fac = I;
        for( int n=1; n<20; ++n ) {
#ifdef POLYHEDRAL_DIAGNOSTIC
            diagnosis.maxOrder = std::max( diagnosis.maxOrder, n );
#endif
            complex_t term = n_fac * ff_n_core(n, qpa) / qpa.mag2();
            sum += term;
            if( !(n&1) && std::abs(term)<=eps*std::abs(sum) )
                return sum;
            n_fac *= I;
        }
        throw std::runtime_error("Bug in formfactor computation: series f(q_pa) not converged");
    } else {
        // direct evaluation of analytic formula
        cvector_t prevec = 2.*normal.cross( qpa ); // complex conjugation will take place in .dot
        complex_t sum = 0;
        for( const PolyhedralEdge& e: edges ) {
            complex_t qE = e.E.dot(qpa);
            complex_t qR = e.R.dot(qpa);
            complex_t sinc_qE = MathFunctions::sinc(qE);
            complex_t Rfac = sym_S2 ? 2.*sin(e.R.dot(qpa)) : exp(I*qR);
            sum += prevec.dot(e.E) * (sinc_qE*Rfac);
        }
        return sum / ( I*qpa.mag2() );
    }
}

//! Throws if deviation from inversion symmetry is detected. Does not check vertices.

void PolyhedralFace::assert_Ci( const PolyhedralFace& other ) const
{
    if( std::abs(rperp-other.rperp)>1e-15*(rperp+other.rperp) )
        throw std::runtime_error("Faces with different distance from origin violate symmetry Ci");
    if( std::abs(area-other.area)>1e-15*(area+other.area) )
        throw std::runtime_error("Faces with different areas violate symmetry Ci");
    if( (normal+other.normal).mag()>1e-14 )
        throw std::runtime_error("Faces do not have opposite orientation, violating symmetry Ci");
}

//***************************************************************************************************
//  FormFactorPolyhedron implementation
//***************************************************************************************************

const double FormFactorPolyhedron::q_limit_series = 1e-6;

FormFactorPolyhedron::FormFactorPolyhedron(
    const std::vector<PolyhedralFace>& _faces, const double _z_origin, const bool _sym_Ci )
    : z_origin(_z_origin), sym_Ci(_sym_Ci), faces(_faces)
{
    radius = 0;
    volume = 0;
    for( const PolyhedralFace& Gk: faces ) {
        radius = std::max( radius, Gk.radius_3d );
        volume += Gk.getPyramidalVolume();
    }

    if( sym_Ci ) {
        if( faces.size()&1 )
            throw std::runtime_error("Odd #faces violates symmetry Ci");
        size_t N = faces.size()/2;
        // for this tests, faces must be in a specific order
        for( size_t k=0; k<N; ++k )
            faces[k].assert_Ci( faces[2*N-1-k] );
        // keep only half of the faces
        faces.erase( faces.begin()+N, faces.end() );
    }
}

//! Returns the form factor F(q) of this polyhedron, respecting the offset z_origin.

complex_t FormFactorPolyhedron::evaluate_for_q( const cvector_t q ) const
{
    return exp(-I*z_origin*q.z()) * evaluate_centered(q);
}

//! Returns the form factor F(q) of this polyhedron, with origin at z=0.

complex_t FormFactorPolyhedron::evaluate_centered( const cvector_t q ) const
{
    double q_red = radius * q.mag();
#ifdef POLYHEDRAL_DIAGNOSTIC
    diagnosis = { 0, 0 };
#endif
    if( q_red==0 ) {
        return volume;
    } else if ( q_red < q_limit_series ) {
        // summation of power series
        complex_t ret = volume;
        complex_t n_fac = ( sym_Ci ? -2 : I ) / q.mag2();
        for( int n=1; n<20; ++n ) {
            if( sym_Ci && n&1 )
                continue;
#ifdef POLYHEDRAL_DIAGNOSTIC
            diagnosis.maxOrder = std::max( diagnosis.maxOrder, n );
#endif
            complex_t term = 0;
            for( const PolyhedralFace& Gk: faces )
                term += Gk.ff_n( n+1, q );
            term *= n_fac;
            ret += term;
            if( !(n&1) && std::abs(term)<=eps*std::abs(ret) )
                return ret;
            n_fac *= ( sym_Ci ? -1 : I );
        }
        throw std::runtime_error("Bug in formfactor computation: series F(q) not converged");
    } else {
        // direct evaluation of analytic formula (coefficients may involve series)
        complex_t ret = 0;
        for( const PolyhedralFace& Gk: faces )
            ret += Gk.ff(q, sym_Ci );
        return ret / (I * q.mag2());
    }
}

//! Assertions for Platonic solid.

void FormFactorPolyhedron::assert_platonic() const
{
    // just one test; one could do much more ...
    double pyramidal_volume = 0;
    for( const auto& Gk: faces )
        pyramidal_volume += Gk.getPyramidalVolume();
    pyramidal_volume /= faces.size();
    for( const auto& Gk: faces )
        if (std::abs(Gk.getPyramidalVolume()-pyramidal_volume) > 160*eps*pyramidal_volume) {
            std::cout<<std::setprecision(16)<<"BUG: pyr_volume(this face)="<<
                Gk.getPyramidalVolume()<<" vs pyr_volume(avge)="<<pyramidal_volume<<"\n";
            throw std::runtime_error("Deviant pyramidal volume");
        }
}


//***************************************************************************************************
//  FormFactorPolygonalPrism implementation
//***************************************************************************************************

FormFactorPolygonalPrism::FormFactorPolygonalPrism(
    const PolyhedralFace& _base, const double _height )
    : m_base(_base), m_height(_height)
{
}

//! Returns the volume of this prism.
double FormFactorPolygonalPrism::getVolume() const { return m_height * m_base.getArea(); }
//! Returns the height of this prism.
double FormFactorPolygonalPrism::getHeight() const { return m_height; }

//! Returns the form factor F(q) of this polyhedron, respecting the offset z_origin.

complex_t FormFactorPolygonalPrism::evaluate_for_q( const cvector_t q ) const
{
#ifdef POLYHEDRAL_DIAGNOSTIC
    diagnosis = { 0, 0 };
#endif
    const cvector_t qxy( q.x(), q.y(), 0. );
    return m_height * exp(I*(m_height/2)*q.z()) * MathFunctions::sinc(m_height/2*q.z()) * m_base.ff_2D( qxy );
}
