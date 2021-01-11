#ifdef ALGORITHM_DIAGNOSTIC

#include "Base/Math/Constants.h"
#include "Sample/HardParticle/HardParticles.h"
#include "Sample/HardParticle/PolyhedralComponents.h" // for diagnostic
#include "Tests/GTestWrapper/google_test.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>

static double eps(2e-16);

const auto qlist = testing::Combine(
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({0, 1, 1}),
                    cvector_t({2, 3, 0}), cvector_t({5, 0, 2}), cvector_t({0, 5, 3}),
                    cvector_t({1, sqrt(2), 0}), cvector_t({sqrt(3), 0, 1}), cvector_t({1, 1, 1})),
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({0, 1, 1}),
                    cvector_t({2, 3, 0}), cvector_t({5, 0, 2}), cvector_t({0, 5, 3}),
                    cvector_t({1, sqrt(2), 0}), cvector_t({sqrt(3), 0, 1}), cvector_t({1, 1, 1})),
    testing::Values(1e-19, 1e-17, 1e-15, 1e-12, 1e-9, 1e-6, 1e-3, .03, 1., 3., 10., 30.),
    testing::Values(0, -4e-16, +8e-16, -5e-11, 3e-7, -2e-3, .01, .1)
    );


//! Print q in a form that can be easily pasted to the command line for further investigation

std::string nice_q( cvector_t q )
{
    std::ostringstream ret;
    double qmax = 0;
    ret << std::setprecision(16);
    for( int i=0; i<3; ++i )
        qmax = std::max( qmax, q[i].real() );
    for( int i=0; i<3; ++i )
        ret << q[i].real()/qmax << " " << q[i].imag()/qmax << " ";
    ret << qmax;
    return ret.str();
}

//! Bisect between two q's to find possible discontinuities

void bisect(
    const IBornFF& ff,
    const cvector_t& q0, const cvector_t& q1, const complex_t F0, const complex_t F1,
    const PolyhedralDiagnosis& d0, const PolyhedralDiagnosis& d1,
    const double qmindiff, const double Fmaxreldiff)
{
    assert( d0!=d1 );
    if( (q0-q1).mag()<qmindiff ) {
        // narrowed down to minimal step, now check for continuity
        double aval = (std::abs(F0) + std::abs(F1))/2;
        double step = std::abs(F0-F1);
        double relstep = step/aval;
        if( relstep>Fmaxreldiff){
            std::cout<<"relstep "<<std::setprecision(8)<<relstep<<"="<<step<<"/"<<std::setprecision(16)<<aval<<" for "<<d0.message()<<"->"<<d1.message()<<" at q between "<<nice_q(q0)<<" and "<<nice_q(q1)<<"\n";
            // maxrelstep = relstep;
        }
        return;
    }
    cvector_t q2 = (q0 + q1)/2.;
    complex_t F2 = ff.evaluate_for_q(q2);
    PolyhedralDiagnosis d2 = polyhedralDiagnosis;
    if( d2!=d0 )
        bisect(ff, q0, q2, F0, F2, d0, d2, qmindiff, Fmaxreldiff);
    if( d2!=d1 )
        bisect(ff, q2, q1, F2, F1, d2, d1, qmindiff, Fmaxreldiff);
}

void run_bisection(IBornFF& ff, const cvector_t& q0, const cvector_t& q1)
{
    const double qdiffmin = std::max(q0.mag(), q1.mag())/4e16;
    complex_t F0 = ff.evaluate_for_q(q0);
    PolyhedralDiagnosis d0 = polyhedralDiagnosis;
    complex_t F1 = ff.evaluate_for_q(q1);
    PolyhedralDiagnosis d1 = polyhedralDiagnosis;

    if (d0==d1)
        return;
    bisect(ff, q0, q1, F0, F1, d0, d1, qdiffmin, 1e-14);
}

void run_test(IBornFF& ff)
{
    ::testing::internal::ParamGenerator<std::tuple<cvector_t, cvector_t, double, double>>
        gen = qlist;
    for (auto it : gen) {
        const cvector_t q_dir0 = std::get<0>(it).unit();
        const cvector_t q_dir1 = std::get<1>(it).unit();
        const double qrealmag = std::get<2>(it);
        const double qimagrel = std::get<3>(it);
        const complex_t qmag(qrealmag, qrealmag*qimagrel);
        const cvector_t q0 = qmag * q_dir0;
        const cvector_t q1 = qmag * q_dir1;

        run_bisection(ff, q0, q1);
    }
}

class BisectFF : public testing::Test {};

TEST_F(BisectFF, Tetrahedron)
{
    FormFactorTetrahedron ff(8.23, .27, .51);
    run_test(ff);
}

#endif // ALGORITHM_DIAGNOSTIC
