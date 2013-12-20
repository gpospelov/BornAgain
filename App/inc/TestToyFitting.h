// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestToySimulation.h
//! @brief     Defines classes ToySimulation, TestToySimulation.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTTOYFITTING_H
#define TESTTOYFITTING_H


#include "IApplicationTest.h"
#include "MathFunctions.h"
#include "TRandom.h"


class TH2D;
class TF2;


//! TestToyFitting class produces couple of plots used in User Manual's section
//! "Gentle introduction to the data fitting"

class TestToyFitting : public IApplicationTest
{
public:
    TestToyFitting();
    virtual ~TestToyFitting() { }

    virtual void execute();

    class IFunctionObject
    {
    public:
        virtual ~IFunctionObject(){}
        virtual double operator()(const double *xx, const double *pars ) = 0;
    };

    class SincXSincY : public IFunctionObject
    {
    public:
        double operator()(const double *xx, const double *pars )
        {
            const double x = xx[0];
            const double y = xx[1];
            const double p0=pars[0];
            const double p1=pars[1];
            const double p2=pars[2];
            const double p3=pars[3];
            double value = p0 + p1 * MathFunctions::Sinc(x-p2) * MathFunctions::Sinc(y-p3);
            return value;
        }
    };

    class SincXSincYNoisy : public IFunctionObject
    {
    public:
        double operator()(const double *xx, const double *pars )
        {
            const double x = xx[0];
            const double y = xx[1];
            const double p0=pars[0];
            const double p1=pars[1];
            const double p2=pars[2];
            const double p3=pars[3];
            double value = p0 + p1 * MathFunctions::Sinc(x-p2) * MathFunctions::Sinc(y-p3);
            value += mr.Gaus(0.0, 0.01);
            return value;
        }
        TRandom mr;
    };

    void fill_histogram(TH2D *hist, TF2 *func);

    void beautify_histogram(TH2D *hist);
    void beautify_palette(TH2D *hist);
    void fill_chi23(TH2D *hist, TF2 *func_exp, TF2 *func_sim);
    void fill_chi12(TH2D *hist, TF2 *func_exp, TF2 *func_sim);
    double get_chi2(TH2D *hist_exp, TH2D *hist_sim);

private:
    double m_xmin;
    double m_xmax;
    double m_ymin;
    double m_ymax;
    int m_nbinx;
    int m_nbiny;
};


#endif

