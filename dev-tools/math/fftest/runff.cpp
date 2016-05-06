// Form factor computation: test program
// JWu 2016

// Reference:
//   Joachim Wuttke
//   "Form factor (Fourier shape transform) of polygon and polyhedron."

// To use these tests, FormFactorPolyhedron.cpp must be compiled
// with flag -D POLYHEDRAL_DIAGNOSTIC=ON

#include <cassert>
#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>

#include "ParticleShapes.h"

using std::cout;
using std::cerr;
using std::vector;

static complex_t I(0.,1.);
static double eps(2e-16);

Diagnosis diagnosis;

int nshape = 11;

extern int n_limit;
extern double q_limit_series;
extern double qpa_limit_series;

//! Returns a pointer to a particle, according to given code

IFormFactorBorn* make_particle( int ishape )
{
    if       ( ishape==1 ) {
        return new FormFactorDodecahedron(3.);
    } else if( ishape==2 ) {
        return new FormFactorIcosahedron(15.);
    } else if( ishape==3 ) { // true tetrahedron
        double alpha = 72 * Units::degree;
        return new FormFactorTetrahedron(1., tan(alpha)/2/sqrt(3), alpha);
    } else if( ishape==4 ) { // tetrahedral frustum
        double alpha = 72 * Units::degree;
        return new FormFactorTetrahedron(1., 0.5*tan(alpha)/2/sqrt(3), alpha);
    } else if( ishape==5 ) {
        double alpha = 72 * Units::degree;
        return new FormFactorCone6(10., 10., alpha);
    } else if( ishape==6 ) {
        return new FormFactorPyramid(1.5, .24, 1.);
    } else if( ishape==7 ) {
        return new FormFactorAnisoPyramid(1.5, 1.5, .24, 1.);
    } else if( ishape==8 ) {
        return new FormFactorPrism3(1.2, 1.);
    } else if( ishape==9 ) {
        return new FormFactorPrism6(1., 1.);
    } else if( ishape==10) {
        return new FormFactorTruncatedCube(4., 1.);
    } else if( ishape==11 ) {
        double alpha = 72 * Units::degree;
        return new FormFactorCuboctahedron(1., 1., .8, alpha);
    } else
        throw "Shape not implemented";
}

//! Bisect between two q's to find possible discontinuities

void bisect(
    const IFormFactorBorn* polyh, const int ishape, const double q0mag,
    const cvector_t qi, const complex_t ri, const Diagnosis di,
    const cvector_t qf, const complex_t rf, const Diagnosis df,
    double& maxrelstep )
{
    assert( di!=df );
    if( (qi-qf).mag()<4*eps*q0mag ) {
        // narrowed down to minimal step, now check for continuity
        double aval = (std::abs(ri) + std::abs(rf))/2;
        double relstep = std::abs(ri-rf)/aval;
        maxrelstep = std::max( maxrelstep, relstep );
        if( relstep>1e-9 ){
            cerr<<"ishape="<<ishape<<": step "<<std::setprecision(8)<<relstep<<" @ "<<std::setprecision(16)<<aval<<" for "<<di<<"->"<<df<<" at q between "<< std::setprecision(16)<<qi<<" and "<<qf<<"\n";
        }
        return;
    }
    cvector_t q2 = (qi + qf)/2.;
    complex_t r2 = polyh->evaluate_for_q(q2);
    Diagnosis d2 = diagnosis;
    if( d2!=di )
        bisect( polyh, ishape, q0mag, qi, ri, di, q2, r2, d2, maxrelstep );
    if( d2!=df )
        bisect( polyh, ishape, q0mag, q2, r2, d2, qf, rf, df, maxrelstep );
}

//! Computes form factor, and prints result according to outfilter.

void run(const IFormFactorBorn* polyh, const int ishape, const cvector_t q, const int outfilter )
{
    complex_t ret = polyh->evaluate_for_q(q);

    if( outfilter==9 )
        return;
    cout <<
        ishape << " " <<
        std::setprecision(16) <<
        q[0].real() << " " << q[0].imag() << " " <<
        q[1].real() << " " << q[1].imag() << " " <<
        q[2].real() << " " << q[2].imag() << " " <<
        std::setprecision(17) <<
        q.mag() << " ";
    if     ( outfilter==0 )
        cout << ret;
    else if( outfilter==1 )
        cout << ret.real();
    else if( outfilter==2 )
        cout << ret.imag();
    else if( outfilter==7 || outfilter==8 )
        cout << ret.real() << " " << ret.imag() << " " << std::abs(ret);
    else
        throw "invalid outfilter";
#ifdef POLYHEDRAL_DIAGNOSTIC
    cout << " " << diagnosis.nExpandedFaces << " " << diagnosis.maxOrder << "\n";
#endif
}

double test_continuity( int ishape, const vector<vector<cvector_t>>& scans )
{
    IFormFactorBorn* polyh( make_particle( ishape ) );
    double maxrelstep = 0;
    for( size_t j=0; j<scans.size(); ++j ) {
        if( !(j%100) )
            fprintf( stderr, "%2i: %8li/%li\r", ishape, j, scans.size() );
        const vector<cvector_t>& q_scan = scans[j];
        for( size_t i=1; i<q_scan.size(); ++i ) {
            complex_t last_ret = polyh->evaluate_for_q(q_scan[i-1]);
            Diagnosis last_diag = diagnosis;
            complex_t ret = polyh->evaluate_for_q(q_scan[i]);
            Diagnosis diag = diagnosis;
            if( diag!=last_diag )
                bisect( polyh, ishape, q_scan[i].mag(), q_scan[i], ret, diag, q_scan[i-1],
                        last_ret, last_diag, maxrelstep );
        }
    }
    fprintf( stderr, "\n" );
    cout << "shape " << ishape << " => max rel step = " << maxrelstep << "\n";
    return maxrelstep;
}

void loop_one_shape( int outfilter, int ishape, const vector<vector<cvector_t>>& scans )
{
    IFormFactorBorn* polyh( make_particle( ishape ) );
    for( const vector<cvector_t>& q_scan: scans ) {
        for( const cvector_t q: q_scan )
            run( polyh, ishape, q, outfilter );
    }
}

vector<vector<cvector_t>> scans_for_blabla()
{
    static int n_qdir = 10;
    int nsteps = 2001;
    if( !(nsteps&1) )
        throw "nsteps must be odd";
    vector<double> steps(nsteps);
    steps[0] = 0;
    steps[nsteps-1] = 1;
    int n2 = (nsteps-1)/2;
    steps[n2] = .5;
    for( int i=1; i<n2; ++i ){
        steps[i] = pow(.5, (i-1)/((double)(n2-1))) * pow(1e-10, (n2-i)/((double)(n2-1)));
        steps[nsteps-1-i] = 1-steps[i];
    }
    double steps_short[3] = { 0., 1e-12, 1e-6 };
    cvector_t qdirs[n_qdir+1] = {
        { 1., 0., 0. },
        { 0., 1.+.01*I, 0. },
        { .001*I, 1., 1. },
        { 1.+.01*I, 1.-.01*I, 0. },
        { 0., 0., 1. },
        { 1., 1., 1. },
        { 1., 0., 1. },
        { 1., 2., 0. },
        { 0., 2., 3. },
        { 1., 2.71813+0.1*I, 3.14158-0.2*I, },
        { -2.+.02*I, .03-.0004*I, .0005 } };

    vector<vector<cvector_t>> scans;
    // For different directions ...
    for( int idx_qdir=0; idx_qdir<n_qdir; ++idx_qdir ){
        for( int irot=0; irot<3; ++irot ){
            double rot = steps_short[irot];
            cvector_t uq = ((1-rot)*qdirs[idx_qdir] + rot*qdirs[idx_qdir+1]).unit();
            // ... sweep |q|
            vector<cvector_t> scan;
            scan.push_back( cvector_t() ); // q=0 to start with
            for( int idx_qmag=0; idx_qmag<(nsteps-1); ++idx_qmag ) {
                double qmag = pow(10.,-10+13.*idx_qmag/(nsteps-2));
                scan.push_back( qmag * uq );
            }
            scans.push_back( scan );
        }
    }
    // For different |q| ...
    for( int idx_qmag=0; idx_qmag<7; ++idx_qmag ) {
        double qmag = pow(10.,-9+12.*idx_qmag/(7-1));
        // ... sweep direction
        for( int idx_qdir=0; idx_qdir<n_qdir; ++idx_qdir ){
            vector<cvector_t> scan;
            for( int irot=0; irot<nsteps; ++irot ){
                double rot = steps[irot];
                cvector_t uq = ((1-rot)*qdirs[idx_qdir] + rot*qdirs[idx_qdir+1]).unit();
                scan.push_back( qmag * uq );
            }
            scans.push_back( scan );
        }
    }
    return scans;
}

vector<vector<cvector_t>> scans_for_cont_test()
{
    static int n_dir = 7;
    cvector_t dir[n_dir] = {
        { 1., 0., 0. },
        { 0., 1., 0. },
        { 0., 0., 1. },

        { 0., 1., 1. },
        { 1., 0., 1. },
        { 1., 1., 0. },

        { 1., 1., 1. }
    };

    static int n_difdir = 7;
    cvector_t difdir[n_difdir] = {
        { 1., 0., 0. },
        { 0., 1., 0. },
        { 0., 0., 1. },

        { 0., 1., 1. },
        { 1., 0., 1. },
        { 1., 1., 0. },

        { 1., 1., 1. }
    };

    static int n_absdir = 7; // absorption component
    cvector_t absdir[n_absdir] = {
        { 1e-15*I, 0., 0. },
        { 0., 1e-10*I, 0. },
        { 0., 0., 1e-5*I },
        { .1*I, 0., 0. },
        { 0., .1*I, 0. },
        { 0., 0., .1*I },
        { .1*I, .1*I, .1*I }
    };

    static const int n_mag = 20;
    static double mag[n_mag] = { 0, 1e-12, 1e-10, 1e-8, 1e-7, 1e-6, 1e-5, 1e-4, 1e-3,
                          .01, .06, .2, .5, 1, 2, 5, 10, 20, 50, 100 };
    static const int n_difmag = 16;
    static double difmag[n_difmag] = { 3e-16, 1e-15, 3e-15, 1e-14, 1e-13, 1e-12, 1e-11, 1e-9, 1e-7,
                             1e-5, 1e-3, .01, .03, .1, .2, .3 };

    vector<vector<cvector_t>> scans;
    for( int i=0; i<n_dir; ++i ) {
        for( int j=0; j<n_difdir; ++j ) {
            for( int k=0; k<n_difmag; ++k ) {
                for( int l=0; l<n_absdir; ++l ) {
                    cvector_t uq = ( dir[i].unit() + difmag[k]*difdir[j] + absdir[l] ).unit();
                    vector<cvector_t> scan;
                    for( int m=0; m<n_mag; ++m )
                        scan.push_back( mag[m] * uq );
                    scans.push_back( scan );
                }
            }
        }
    }
    return scans;
}

void help_and_exit()
{
    cerr << "fftest limits inmode outfilter shape qxr qxi qyr qyi qzr qzi [q]\n";
    cerr << "  limits:    \"def\" | qlim qpalim nlim\n";
    cerr << "  inmode:    get q from 0:stdin | 1:cmdline\n";
    cerr << "  outfilter: return 0:all | 1:real | 2:imag\n";
    cerr << "fftest limits loop shape [outfilter]\n";
    cerr << "  limits:    \"def\" | qlim qpalim nlim\n";
    cerr << "  loop:      2[cont_test] |\n";
    cerr << "  shape:     0[all] | 1..[specific]\n";
    exit(0);
}

#define NEXTARG if( (++arg)-argv >= argc ) help_and_exit()
#define MULTIARG(n) if( (arg+=n)-argv >= argc ) help_and_exit()

int main (int argc, const char *argv[])
{
    try {
        const char** arg = argv;
        NEXTARG;
        if ( !strncmp( *arg, "def", 3 ) ) {
            // do nothing
        } else {
            double q_limit = atof( *arg );
            NEXTARG;
            double qpa_limit = atof( *arg );
            NEXTARG;
            int n_limit = atoi( *arg );
            FormFactorPolyhedron::setLimits( q_limit, n_limit );
            PolyhedralFace::setLimits( qpa_limit, n_limit );
        }
        NEXTARG;
        int inmode = atoi( *arg );
        if( inmode==0 || inmode==1 ) {
            NEXTARG;
            int outfilter = atoi( *arg );
            NEXTARG;
            int ishape = atoi( *arg );
            IFormFactorBorn* P( make_particle( ishape ) );
            MULTIARG(6);
            cvector_t uq(
                complex_t( atof(*(arg-5)), atof(*(arg-4)) ),
                complex_t( atof(*(arg-3)), atof(*(arg-2)) ),
                complex_t( atof(*(arg-1)), atof(*(arg-0)) ) );
            double qmag;
            if( inmode==1 ) {
                NEXTARG;
                qmag = atof(argv[10]);
                run( P, ishape, qmag*uq, outfilter );
            } else if( inmode==0 ) {
                // for use through Frida
                int nop;
                std::cin >> nop;
                while( std::cin >> qmag )
                    run( P, ishape, qmag*uq, outfilter );
            }
            exit(0);
        }
        // it's some loop
        NEXTARG;
        int ishapepar = atoi( *arg );

        if( inmode==2 ) { // continuity test
            vector<vector<cvector_t>> scans = scans_for_cont_test();
            double totmaxrelstep = 0;
            if( ishapepar==0 ) {
                for( int ishape=1; ishape<=nshape; ++ishape )
                    totmaxrelstep = std::max( totmaxrelstep, test_continuity( ishape, scans ) );
                cout << "grand total max rel step = " << totmaxrelstep << "\n";
            } else {
                test_continuity( ishapepar, scans );
            }
            exit (0);
        }
        // it's a straight loop over q
        vector<vector<cvector_t>> scans = scans_for_blabla();
        NEXTARG;
        int outfilter = atoi( *arg );
        if( ishapepar==0 ) {
            for( int ishape=1; ishape<=nshape; ++ishape )
                loop_one_shape( outfilter, ishape, scans );
        } else
            loop_one_shape( outfilter, ishapepar, scans );
        exit(0);

    } catch( const char* ex ) {
        cerr << "F(q) failed: " << ex << "\n";
        exit(0);
    }
}
