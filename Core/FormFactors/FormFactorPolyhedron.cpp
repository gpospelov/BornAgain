// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorPolyhedron.cpp
//! @brief     Implements class FormFactorPolyhedron, FormFactorPrism, and auxiliary classes.
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
#include "BornAgainNamespace.h"

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

double PolyhedralFace::qpa_limit_series = 1e-30;
int PolyhedralFace::n_limit_series = 20;

double FormFactorPolyhedron::q_limit_series = 1e-5;
int FormFactorPolyhedron::n_limit_series = 20;

//***************************************************************************************************
//  PolyhedralEdge implementation
//***************************************************************************************************

PolyhedralEdge::PolyhedralEdge( const kvector_t _Vlow, const kvector_t _Vhig )
    : m_E((_Vhig-_Vlow)/2)
    , m_R((_Vhig+_Vlow)/2)
{
    if( m_E.mag2()==0 ) {
        std::ostringstream msg;
        msg<<"zero-length edge between "<<_Vlow<<" and "<<_Vhig;
        throw std::runtime_error(msg.str());
    }
};

//! Returns the contribution of this edge to the form factor.

complex_t PolyhedralEdge::contrib(int m, cvector_t prevec, cvector_t q) const
{
    complex_t prefac = prevec.dot(E()); // conj(prevec)*E [BasicVector3D::dot is antilinear in *this]
    complex_t u = qE(q);
    complex_t v = qR(q);
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

//! Static method, returns diameter of circle that contains all vertices.

double PolyhedralFace::diameter( const std::vector<kvector_t>& V )
{
    double diameterFace = 0;
    for ( size_t j=0; j<V.size(); ++j )
        for ( size_t jj=j+1; jj<V.size(); ++jj )
            diameterFace = std::max( diameterFace, (V[j]-V[jj]).mag() );
    return diameterFace;
}

#ifdef POLYHEDRAL_DIAGNOSTIC
void PolyhedralFace::setLimits( double _qpa, int _n ) { qpa_limit_series=_qpa; n_limit_series=_n; }
#endif

//! Sets internal variables for given vertex chain.

//! @param V oriented vertex list
//! @param _sym_S2 true if face has a perpedicular two-fold symmetry axis

PolyhedralFace::PolyhedralFace( const std::vector<kvector_t>& V, bool _sym_S2 )
    : sym_S2( _sym_S2 )
{
    size_t NV = V.size();
    if( !NV )
        throw NotImplementedException( "Face with no edges" );
    if( NV<3 )
        throw NotImplementedException( "Face with less than three edges" );

    // compute radius in 2d and 3d
    m_radius_2d = diameter( V )/2;
    m_radius_3d = 0;
    for( const kvector_t v: V )
        m_radius_3d = std::max( m_radius_3d, v.mag() );

    // Initialize list of 'edges'.
    // Do not create an edge if two vertices are too close to each other.
    // TODO This is implemented in a somewhat sloppy way: we just skip an edge if it would
    //      be too short. This leaves tiny open edges. In a clean implementation, we
    //      rather should merge adjacent vertices before generating edges.
    for ( size_t j=0; j<NV; ++j ) {
        size_t jj = (j+1)%NV;
        if( (V[j]-V[jj]).mag() < 1e-14*m_radius_2d )
            continue; // distance too short -> skip this edge
        edges.push_back( PolyhedralEdge(V[j], V[jj]) );
    }
    size_t NE = edges.size();
    if( NE<3 )
        throw RuntimeErrorException( "Face has less than three non-vanishing edges" );

    // compute n_k, rperp
    m_normal = kvector_t();
    for( size_t j=0; j<NE; ++j ){
        size_t jj = (j+1)%NE;
        kvector_t ee = edges[j].E().cross( edges[jj].E() );
        if( ee.mag2()==0 ) {
            throw RuntimeErrorException( "Two adjacent edges are parallel" );
        }
        m_normal += ee.unit();
    }
    m_normal /= NE;
    m_rperp = 0;
    for( size_t j=0; j<NV; ++j )
        m_rperp += V[j].dot(m_normal);
    m_rperp /= NV;
    // assert that the vertices lay in a plane
    for ( size_t j=1; j<NV; ++j )
        if( std::abs(V[j].dot(m_normal) - m_rperp) > 1e-14*m_radius_3d )
            throw std::runtime_error("Face is not planar");
    // compute m_area
    m_area = 0;
    for ( size_t j=0; j<NV; ++j ) {
        size_t jj = (j+1)%NV;
        m_area += m_normal.dot( V[j].cross( V[jj] ) ) / 2;
    }
    // only now deal with inversion symmetry
    if( sym_S2 ) {
        if( NE&1 )
            throw std::runtime_error("Odd #edges violates symmetry S2");
        NE /= 2;
        for( size_t j=0; j<NE; ++j ){
            if( ((edges[j].R()-m_rperp*m_normal)+
                 (edges[j+NE].R()-m_rperp*m_normal)).mag() > 1e-12*m_radius_2d )
                throw std::runtime_error("Edge centers violate symmetry S2");
            if( (edges[j].E()+edges[j+NE].E()).mag() > 1e-12*m_radius_2d )
                throw std::runtime_error("Edge vectors violate symmetry S2");
        }
        // keep only half of the egdes
        edges.erase( edges.begin()+NE, edges.end() );
    }
}

//! Sets qperp and qpa according to argument q and to this polygon's normal.

void PolyhedralFace::decompose_q( const cvector_t q, complex_t& qperp, cvector_t& qpa ) const
{
    qperp = m_normal.dot(q);
    qpa = q - qperp*m_normal;
    // improve numeric accuracy:
    qpa -= m_normal.dot(qpa)*m_normal;
    if( qpa.mag()<eps*std::abs(qperp) )
        qpa = cvector_t(0.,0.,0.);
}

//! Returns core contribution to f_n

complex_t PolyhedralFace::ff_n_core( int m, const cvector_t q ) const
{
    cvector_t prevec = 2.*m_normal.cross( q ); // complex conjugation will take place in .dot
    complex_t ret = 0;
    for( const PolyhedralEdge& e: edges )
        ret += e.contrib(m, prevec, q);
    return ret;
}

//! Returns contribution qn*f_n [of order q^(n+1)] from this face to the polyhedral form factor.

complex_t PolyhedralFace::ff_n( int n, const cvector_t q ) const
{
    complex_t qn = q.dot(m_normal); // conj(q)*normal (BasicVector3D::dot is antilinear in 'this' argument)
    if ( std::abs(qn)<eps*q.mag() )
        return 0.;
    complex_t qperp;
    cvector_t qpa;
    decompose_q( q, qperp, qpa );
    double qpa_mag2 = qpa.mag2();
    static auto& precomputed = IPrecomputed::instance();
    if ( qpa_mag2==0. ) {
        return qn * pow(qperp*m_rperp, n) * m_area / precomputed.factorial[n];
    } else if ( sym_S2 ) {
        return qn * ( ff_n_core( n, q ) + ff_n_core( n, qperp*m_normal-qpa ) ) / qpa_mag2;
    } else {
        return qn * ff_n_core( n, q ) / qpa_mag2;
    }
}

//! Returns the contribution ff(q) of this face to the polyhedral form factor.

complex_t PolyhedralFace::ff( const cvector_t q, const bool sym_Ci ) const
{
    complex_t qperp;
    cvector_t qpa;
    decompose_q( q, qperp, qpa );
    double qpa_red = m_radius_2d * qpa.mag();
    complex_t qr_perp = qperp*m_rperp;
    if ( qpa_red==0 ) {
        return (sym_Ci ? 2.*I*sin(qr_perp) : exp(I*qr_perp)) * m_area;
    } else if ( qpa_red < qpa_limit_series && !sym_S2 ) {
        // summation of power series
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis.nExpandedFaces += 1;
#endif
        complex_t fac_even;
        complex_t fac_odd;
        if( sym_Ci ) {
            fac_even = 2. * I * sin(qr_perp);
            fac_odd = 2. * cos(qr_perp);
        } else {
            fac_even = exp( I*qr_perp );
            fac_odd = fac_even;
        }
        complex_t sum = fac_even * m_area;
        complex_t n_fac = I;
        for( int n=1; n<n_limit_series; ++n ) {
#ifdef POLYHEDRAL_DIAGNOSTIC
            diagnosis.maxOrder = std::max( diagnosis.maxOrder, n );
#endif
            complex_t term = n_fac * ( n&1 ? fac_odd : fac_even ) * ff_n_core(n, qpa) / qpa.mag2();
            sum += term;
            // std::cout<<std::setprecision(16)<<"  sum="<<sum<<" term="<<term<<"\n";
            if( !(n&1) && std::abs(term)<=eps*std::abs(sum) )
                return sum;
            n_fac *= I;
        }
#ifdef POLYHEDRAL_DIAGNOSTIC
        return sum;
#else
        throw std::runtime_error("Bug in formfactor computation: series f(q_pa) not converged");
#endif
    } else {
        // direct evaluation of analytic formula
        cvector_t prevec = m_normal.cross( qpa ); // complex conjugation will take place in .dot
        complex_t prefac = 2.;
        if( sym_S2 )
            prefac *= sym_Ci ? -4.*sin(qr_perp) : 2.*I*exp(I*qr_perp);
        complex_t sum = 0;
        complex_t vfacsum = 0;
        for( size_t i=0; i<edges.size(); ++i ) {
            const PolyhedralEdge& e = edges[i];
            complex_t qE = e.qE(q);
            complex_t qR = e.qR(q);
            complex_t Rfac = sym_S2 ? sin(e.qR(qpa)) : ( sym_Ci ? 2.*cos(qR) : exp(I*qR) );
            complex_t vfac;
            if( sym_S2 || i<edges.size()-1 ) {
                vfac = prevec.dot(e.E());
                vfacsum += vfac;
            } else {
                vfac = - vfacsum; // to improve numeric accuracy: qcE_J = - sum_{j=0}^{J-1} qcE_j
            }
            sum += vfac * MathFunctions::sinc(qE) * Rfac;
        }
        return prefac * sum / ( I*qpa.mag2() );
    }
}

//! Returns the two-dimensional form factor of this face, for use in a prism.

complex_t PolyhedralFace::ff_2D( const cvector_t qpa ) const
{
    if ( std::abs(qpa.dot(m_normal))>eps*qpa.mag() )
        throw std::runtime_error("ff_2D called with perpendicular q component");
    double qpa_red = m_radius_2d * qpa.mag();
    if ( qpa_red==0 ) {
        return m_area;
    } else if ( qpa_red < qpa_limit_series && !sym_S2 ) {
        // summation of power series
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis.nExpandedFaces += 1;
#endif
        complex_t sum = m_area;
        complex_t n_fac = I;
        for( int n=1; n<n_limit_series; ++n ) {
#ifdef POLYHEDRAL_DIAGNOSTIC
            diagnosis.maxOrder = std::max( diagnosis.maxOrder, n );
#endif
            complex_t term = n_fac * ff_n_core(n, qpa) / qpa.mag2();
            sum += term;
            if( !(n&1) && std::abs(term)<=eps*std::abs(sum) )
                return sum;
            n_fac *= I;
        }
#ifdef POLYHEDRAL_DIAGNOSTIC
        return sum;
#else
        throw std::runtime_error("Bug in formfactor computation: series f(q_pa) not converged");
#endif
    } else {
        // direct evaluation of analytic formula
        cvector_t prevec = m_normal.cross( qpa );  // complex conjugation will take place in .dot
        complex_t sum = 0;
        for( const PolyhedralEdge& e: edges ) {
            complex_t qE = e.qE(qpa);
            complex_t qR = e.qR(qpa);
            complex_t Rfac = sym_S2 ? sin(e.qR(qpa)) : exp(I*qR);
            sum += prevec.dot(e.E()) * MathFunctions::sinc(qE) * Rfac;
        }
        return sum * (sym_S2 ? 4. : 2./I ) / qpa.mag2();
    }
}

//! Throws if deviation from inversion symmetry is detected. Does not check vertices.

void PolyhedralFace::assert_Ci( const PolyhedralFace& other ) const
{
    if( std::abs(m_rperp-other.m_rperp)>1e-15*(m_rperp+other.m_rperp) )
        throw std::runtime_error("Faces with different distance from origin violate symmetry Ci");
    if( std::abs(m_area-other.m_area)>1e-15*(m_area+other.m_area) )
        throw std::runtime_error("Faces with different areas violate symmetry Ci");
    if( (m_normal+other.m_normal).mag()>1e-14 )
        throw std::runtime_error("Faces do not have opposite orientation, violating symmetry Ci");
}

//***************************************************************************************************
//  FormFactorPolyhedron implementation
//***************************************************************************************************

#ifdef POLYHEDRAL_DIAGNOSTIC
void FormFactorPolyhedron::setLimits( double _q, int _n ) { q_limit_series=_q; n_limit_series=_n; }
#endif

//! Called by child classes to set faces and other internal variables.

void FormFactorPolyhedron::setPolyhedron(
    const Topology& topology, double z_origin, bool sym_Ci, const std::vector<kvector_t>& vertices )
{
    m_z_origin = z_origin;
    m_sym_Ci = sym_Ci;

    double diameter = 0;
    for ( size_t j=0; j<vertices.size(); ++j )
        for ( size_t jj=j+1; jj<vertices.size(); ++jj )
            diameter = std::max( diameter, (vertices[j]-vertices[jj]).mag() );

    m_faces.clear();
    for( const TopologyFace& tf: topology ) {
        std::vector<kvector_t> corners; // of one face
        for( int i: tf.vertexIndices )
            corners.push_back( vertices[i] );
        if( PolyhedralFace::diameter( corners )<= 1e-14*diameter )
            continue; // skip ridiculously small face
        m_faces.push_back( PolyhedralFace( corners, tf.symmetry_S2 ) );
    }
    if( m_faces.size() < 4 )
        throw RuntimeErrorException( "less than four non-vanishing faces" );

    m_radius = 0;
    m_volume = 0;
    for( const PolyhedralFace& Gk: m_faces ) {
        m_radius = std::max( m_radius, Gk.radius3d() );
        m_volume += Gk.pyramidalVolume();
    }

    if( m_sym_Ci ) {
        if( m_faces.size()&1 )
            throw std::runtime_error("Odd #faces violates symmetry Ci");
        size_t N = m_faces.size()/2;
        // for this tests, m_faces must be in a specific order
        for( size_t k=0; k<N; ++k )
            m_faces[k].assert_Ci( m_faces[2*N-1-k] );
        // keep only half of the faces
        m_faces.erase( m_faces.begin()+N, m_faces.end() );
    }
}

//! Returns the form factor F(q) of this polyhedron, respecting the offset z_origin.

complex_t FormFactorPolyhedron::evaluate_for_q( const cvector_t q ) const
{
    return exp(-I*m_z_origin*q.z()) * evaluate_centered(q);
}

//! Returns the form factor F(q) of this polyhedron, with origin at z=0.

complex_t FormFactorPolyhedron::evaluate_centered( const cvector_t q ) const
{
    double q_red = m_radius * q.mag();
#ifdef POLYHEDRAL_DIAGNOSTIC
    diagnosis = { 0, 0 };
#endif
    if( q_red==0 ) {
        return m_volume;
    } else if ( q_red < q_limit_series ) {
        // summation of power series
        complex_t sum = m_volume;
        complex_t n_fac = ( m_sym_Ci ? -2 : -1 ) / q.mag2();
        for( int n=2; n<n_limit_series; ++n ) {
            if( m_sym_Ci && n&1 )
                continue;
#ifdef POLYHEDRAL_DIAGNOSTIC
            diagnosis.maxOrder = std::max( diagnosis.maxOrder, n );
#endif
            complex_t term = 0;
            for( const PolyhedralFace& Gk: m_faces )
                term += Gk.ff_n( n+1, q );
            term *= n_fac;
            sum += term;
            // std::cout<<std::setprecision(16)<<"  sum="<<sum<<" term="<<term<<"\n";
            if( !(n&1) && std::abs(term)<eps*std::abs(sum) )
                return sum;
            n_fac *= ( m_sym_Ci ? -1 : I );
        }
#ifdef POLYHEDRAL_DIAGNOSTIC
        return sum;
#else
        throw std::runtime_error("Bug in formfactor computation: series F(q) not converged");
#endif
    } else {
        // direct evaluation of analytic formula (coefficients may involve series)
        complex_t sum = 0;
        for( const PolyhedralFace& Gk: m_faces ) {
            complex_t qn = Gk.normalProjectionConj( q ); // conj(q)*normal
            if ( std::abs(qn)<eps*q.mag() )
                continue;
            sum += qn * Gk.ff(q, m_sym_Ci );
        }
        return sum / (I * q.mag2());
    }
}

//! Assertions for Platonic solid.

void FormFactorPolyhedron::assert_platonic() const
{
    // just one test; one could do much more ...
    double pyramidal_volume = 0;
    for( const auto& Gk: m_faces )
        pyramidal_volume += Gk.pyramidalVolume();
    pyramidal_volume /= m_faces.size();
    for( const auto& Gk: m_faces )
        if (std::abs(Gk.pyramidalVolume()-pyramidal_volume) > 160*eps*pyramidal_volume) {
            std::cout<<std::setprecision(16)<<"BUG: pyr_volume(this face)="<<
                Gk.pyramidalVolume()<<" vs pyr_volume(avge)="<<pyramidal_volume<<"\n";
            throw std::runtime_error("Deviant pyramidal volume");
        }
}


//***************************************************************************************************
//  FormFactorPolygonalPrism implementation
//***************************************************************************************************

FormFactorPolygonalPrism::FormFactorPolygonalPrism(double height)
    : m_height(height)
{
    registerParameter(BornAgain::Height, &m_height, AttLimits::n_positive());
}

//! Returns the volume of this prism.
double FormFactorPolygonalPrism::getVolume() const { return m_height * m_base->area(); }

//! Returns the form factor F(q) of this polyhedron, respecting the offset height/2.

complex_t FormFactorPolygonalPrism::evaluate_for_q( const cvector_t q ) const
{
#ifdef POLYHEDRAL_DIAGNOSTIC
    diagnosis = { 0, 0 };
#endif
    const cvector_t qxy( q.x(), q.y(), 0. );
    return m_height * exp(I*(m_height/2)*q.z()) * MathFunctions::sinc(m_height/2*q.z()) *
        m_base->ff_2D( qxy );
}


//***************************************************************************************************
//  FormFactorPolygonalSurface implementation
//***************************************************************************************************

complex_t FormFactorPolygonalSurface::evaluate_for_q( const cvector_t q ) const
{
#ifdef POLYHEDRAL_DIAGNOSTIC
    diagnosis = { 0, 0 };
#endif
    return m_base->ff( q, false );
}
