#ifdef ALGORITHM_DIAGNOSTIC

#include "Base/Math/Constants.h"
#include "Sample/HardParticle/HardParticles.h"
#include "Sample/HardParticle/PolyhedralComponents.h" // for diagnostic
#include "Tests/GTestWrapper/google_test.h"
#include <cassert>
#include <complex>
#include <iomanip>
#include <iostream>
#include <vector>

const auto qlist = testing::Combine(
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({0, 1, 1}),
                    cvector_t({2, 3, 0}), cvector_t({5, 0, 2}), cvector_t({0, 5, 3}),
                    cvector_t({1, sqrt(2), 0}), cvector_t({sqrt(3), 0, 1}), cvector_t({1, 1, 1})),
    testing::Values(cvector_t({1, 0, 0}), cvector_t({0, 1, 0}), cvector_t({0, 0, 1}),
                    cvector_t({1, 1, 0}), cvector_t({1, 0, 1}), cvector_t({0, 1, 1}),
                    cvector_t({2, 3, 0}), cvector_t({5, 0, 2}), cvector_t({0, 5, 3}),
                    cvector_t({1, sqrt(2), 0}), cvector_t({sqrt(3), 0, 1}), cvector_t({1, 1, 1})),
    testing::Values(1e-19, 1e-17, 1e-15, 1e-12, 1e-9, 1e-6, 1e-3, .03, 1., 3., 10., 30., 100.),
    testing::Values(-1., 1.), testing::Values(0, -4e-16, +8e-16, -5e-11, 3e-7, -2e-3, .01, .1));

complex_t deriv(const IBornFF& ff, const cvector_t& qf, const complex_t Ff,
                const PolyhedralDiagnosis& /*df*/, const cvector_t& qdir, const double qstep)
{
    assert(Ff == ff.evaluate_for_q(qf));
    complex_t Fi = ff.evaluate_for_q(qf + qstep * qdir);
    PolyhedralDiagnosis di = polyhedralDiagnosis;
    // assert(di==df);
    return (Ff - Fi) / qstep;
}

//! Bisect between two q's to find possible discontinuities

void bisect(int& ifail, const cvector_t& qdir, const IBornFF& ff, const cvector_t& q0,
            const cvector_t& q1, const complex_t F0, const complex_t F1,
            const PolyhedralDiagnosis& d0, const PolyhedralDiagnosis& d1, const double qmindiff,
            const double Fmaxreldiff)
{
    assert(d0 != d1);
    if ((q0 - q1).mag() < qmindiff) {
        // narrowed down to minimal step, now check for continuity
        double aval = (std::abs(F0) + std::abs(F1)) / 2;
        double step = std::abs(F0 - F1);
        double relstep = step / aval;
        if (relstep > Fmaxreldiff) {
            std::cout << d0.message() << " -> " << d1.message() << ":\n";
            std::cout << "relstep " << std::setprecision(8) << relstep << "=" << step << "/"
                      << std::setprecision(16) << aval << "\n";
            std::cout << "    q[-] = " << q0 << "\n";
            std::cout << "    q[+] = " << q1 << "\n";
            std::cout << "    F[-] = " << F0 << "\n";
            std::cout << "    F[+] = " << F1 << "\n";
            std::cout << "    F'[-1k] =" << -deriv(ff, q0, F0, d0, -qdir, 1000 * qmindiff) << "\n";
            std::cout << "    F'[-300] =" << -deriv(ff, q0, F0, d0, -qdir, 300 * qmindiff) << "\n";
            std::cout << "    F'[-100] =" << -deriv(ff, q0, F0, d0, -qdir, 100 * qmindiff) << "\n";
            std::cout << "    F'[-30] =" << -deriv(ff, q0, F0, d0, -qdir, 30 * qmindiff) << "\n";
            std::cout << "    F'[-10] =" << -deriv(ff, q0, F0, d0, -qdir, 10 * qmindiff) << "\n";
            std::cout << "    F'[-3]  =" << -deriv(ff, q0, F0, d0, -qdir, 3 * qmindiff) << "\n";
            std::cout << "    F'[-1]  =" << -deriv(ff, q0, F0, d0, -qdir, 1 * qmindiff) << "\n";
            std::cout << "    F'[here]=" << (F1 - F0) / (q0 - q1).mag() << "\n";
            std::cout << "    F'[+1]  =" << deriv(ff, q1, F1, d1, +qdir, 1 * qmindiff) << "\n";
            std::cout << "    F'[+3]  =" << deriv(ff, q1, F1, d1, +qdir, 3 * qmindiff) << "\n";
            std::cout << "    F'[+10] =" << deriv(ff, q1, F1, d1, +qdir, 10 * qmindiff) << "\n";
            std::cout << "    F'[+30] =" << deriv(ff, q1, F1, d1, +qdir, 30 * qmindiff) << "\n";
            std::cout << "    F'[+100] =" << deriv(ff, q1, F1, d1, +qdir, 100 * qmindiff) << "\n";
            std::cout << "    F'[+300] =" << deriv(ff, q1, F1, d1, +qdir, 300 * qmindiff) << "\n";
            std::cout << "    F'[+1k]  =" << deriv(ff, q1, F1, d1, +qdir, 1000 * qmindiff) << "\n";
            std::cout << std::endl;
            ++ifail;
            // maxrelstep = relstep;
            return;
        }
        // std::cout<<"ok for "<<d0.message()<<"->"<<d1.message()<<" at q between "<<q0<<" and
        // "<<q1<<std::endl;
        return;
    }
    cvector_t q2 = (q0 + q1) / 2.;
    complex_t F2 = ff.evaluate_for_q(q2);
    PolyhedralDiagnosis d2 = polyhedralDiagnosis;
    if (d2 != d0)
        bisect(ifail, qdir, ff, q0, q2, F0, F2, d0, d2, qmindiff, Fmaxreldiff);
    if (d2 != d1)
        bisect(ifail, qdir, ff, q2, q1, F2, F1, d2, d1, qmindiff, Fmaxreldiff);
}

void run_bisection(int& ifail, IBornFF& ff, const cvector_t& q0, const cvector_t& q1)
{
    const double qdiffmin = std::max(q0.mag(), q1.mag()) / 4e11;
    complex_t F0 = ff.evaluate_for_q(q0);
    PolyhedralDiagnosis d0 = polyhedralDiagnosis;
    complex_t F1 = ff.evaluate_for_q(q1);
    PolyhedralDiagnosis d1 = polyhedralDiagnosis;

    if (d0 == d1)
        return;
    bisect(ifail, q1 - q0, ff, q0, q1, F0, F1, d0, d1, qdiffmin, .6e-10);
}

void run_test(IBornFF& ff)
{
    ::testing::internal::ParamGenerator<std::tuple<cvector_t, cvector_t, double, double, double>>
        gen = qlist;
    int ifail = 0;
    for (auto it : gen) {
        const cvector_t q_dir0 = std::get<0>(it).unit();
        const cvector_t q_dir1 = std::get<1>(it).unit();
        const double qrealmag = std::get<2>(it);
        const double qrel1 = std::get<3>(it);
        const double qimagrel = std::get<4>(it);
        const complex_t qmag(qrealmag, qrealmag * qimagrel);
        const cvector_t q0 = q_dir0 * qmag;
        const cvector_t q1 = q_dir1 * (qmag * qrel1);
        run_bisection(ifail, ff, q0, q1);
    }
    EXPECT_EQ(ifail, 0);
}

class BisectFF : public testing::Test {
};

TEST_F(BisectFF, Bisect1)
{
    FormFactorCone6 ff(.23, 3.5, .999 * M_PI / 2);
    // FormFactorTetrahedron ff(8.23, .27, .51);
    run_test(ff);
}

#endif // ALGORITHM_DIAGNOSTIC
