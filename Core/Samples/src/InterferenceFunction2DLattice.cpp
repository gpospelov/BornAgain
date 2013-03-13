#include "InterferenceFunction2DLattice.h"
#include <cassert>

InterferenceFunction2DLattice::InterferenceFunction2DLattice(
        const Lattice2DIFParameters& lattice_params)
: m_lattice_params(lattice_params)
, mp_pdf(0)
, m_prefactor(1.0)
, m_na(0)
, m_nb(0)
{
    setName("InterferenceFunction2DLattice");
    init_parameters();
    initialize_rec_vectors();
}

InterferenceFunction2DLattice::~InterferenceFunction2DLattice()
{
    delete mp_pdf;
}

void InterferenceFunction2DLattice::setProbabilityDistribution(
        const IFTDistribution2D& pdf)
{
    if (mp_pdf != &pdf) delete mp_pdf;
    mp_pdf = pdf.clone();
    initialize_calc_factors();
}

double InterferenceFunction2DLattice::evaluate(const cvector_t& q) const
{
    double result = 0.0;
    double qxr = q.x().real();
    double qyr = q.y().real();
    double qx_frac, qy_frac;
    calculateReciprocalVectorFraction(qxr, qyr, qx_frac, qy_frac);

    for (int i=-m_na-1; i<m_na+2; ++i)
    {
        for (int j=-m_nb-1; j<m_nb+2; ++j)
        {
            double qx = qx_frac + i*m_asx + j*m_bsx;
            double qy = qy_frac + i*m_asy + j*m_bsy;
            result += interferenceAtOneRecLatticePoint(qx, qy);
        }
    }
    return m_prefactor*result;
}

double InterferenceFunction2DLattice::interferenceAtOneRecLatticePoint(
        double qx, double qy) const
{
    double qp1, qp2;
    double gamma = m_lattice_params.m_xi + mp_pdf->getGamma();
    double delta = mp_pdf->getDelta();
    transformToPrincipalAxes(qx, qy, gamma, delta, qp1, qp2);
    return mp_pdf->evaluate(qp1, qp2);
}

void InterferenceFunction2DLattice::transformToPrincipalAxes(double qx,
        double qy, double gamma, double delta, double& q_pa_1, double& q_pa_2) const
{
    q_pa_1 = qx*std::cos(gamma) + qy*std::sin(gamma);
    q_pa_2 = qx*std::cos(gamma+delta) + qy*std::sin(gamma+delta);
}

void InterferenceFunction2DLattice::calculateReciprocalVectorFraction(double qx,
        double qy, double& qx_frac, double& qy_frac) const
{
    double a = m_lattice_params.m_length_1;
    double b = m_lattice_params.m_length_2;
    double xi = m_lattice_params.m_xi;
    double xialpha = xi + m_lattice_params.m_angle;
    int qa_int = (int)( a*(qx*std::cos(xi)+qy*std::sin(xi))/(2.0*M_PI) );
    int qb_int = (int)( b*(qx*std::cos(xialpha)+qy*std::sin(xialpha))/(2.0*M_PI) );
    qx_frac = qx - qa_int*m_asx - qb_int*m_bsx;
    qy_frac = qy - qa_int*m_asy - qb_int*m_bsy;
}

void InterferenceFunction2DLattice::init_parameters()
{
    getParameterPool()->clear();
}

void InterferenceFunction2DLattice::initialize_rec_vectors()
{
    if(m_lattice_params.m_length_1==0 || m_lattice_params.m_length_2 == 0) {
//        throw DivisionByZeroException("InterferenceFunction2DLattice::initialize_rec_vectors() -> Error! Zero parameters m_lattice_params.m_length1 or m_lattice_params.m_length_2");
    }
    double sinalpha = std::sin(m_lattice_params.m_angle);
    double ainv = 2.0*M_PI/m_lattice_params.m_length_1/sinalpha;
    double binv = 2.0*M_PI/m_lattice_params.m_length_2/sinalpha;
    double xi = m_lattice_params.m_xi;
    double xialpha = xi + m_lattice_params.m_angle;
    m_asx = ainv*std::sin(xialpha);
    m_asy = -ainv*std::cos(xialpha);
    m_bsx = -binv*std::sin(xi);
    m_bsy = binv*std::cos(xi);
}

void InterferenceFunction2DLattice::initialize_calc_factors()
{
    // constant prefactor
    //TODO: for non cauchy distributions: check if this still applies
    m_prefactor = 2.0*M_PI*m_lattice_params.m_corr_length_1*m_lattice_params.m_corr_length_2;
    double denominator = m_lattice_params.m_length_1*m_lattice_params.m_length_2*std::sin(m_lattice_params.m_angle);
    assert(denominator);
    m_prefactor /= denominator;

    // number of reciprocal lattice points to use
    double qa_max, qb_max;
    mp_pdf->transformToStarBasis(nmax/m_lattice_params.m_corr_length_1,
            nmax/m_lattice_params.m_corr_length_2, m_lattice_params.m_angle,
            m_lattice_params.m_length_1, m_lattice_params.m_length_2, qa_max, qb_max);
    m_na = (int)(std::abs(qa_max)+0.5);
    m_nb = (int)(std::abs(qb_max)+0.5);
}
