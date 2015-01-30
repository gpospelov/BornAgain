// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestBessel.cpp
//! @brief     Implements class TestBessel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestBessel.h"
#include "MathFunctions.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TBenchmark.h"
#include "TMath.h"
#include <iostream>
#include <boost/math/special_functions.hpp>




void TestBessel::execute()
{
    std::cout << "TestBessel::execute() -> Hello World" << std::endl;

    double xmin(0.0), xmax(20.0);
    int nx(201);
    double dx = (xmax-xmin)/(nx-1);

    std::cout << "dx: " << dx << std::endl;

    std::vector<Data> buff;
    buff.resize(nx);

    for(int i=0; i<nx; ++i) {
        double x = xmin + dx*i;
        buff[i].x = x;
        buff[i].b_root = TMath::BesselJ1(x);
        buff[i].b_boost = boost::math::cyl_bessel_j(1,x);
        buff[i].b_gsl = MathFunctions::Bessel_J1(x);
    }


//    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
//    TH1D *h2 = new TH1D("h2","h2", nx, xmin - dx/2., xmax+dx/2.);
//    for(int i=0; i<nx; ++i) {
//        h2->Fill(buff[i].x, rel_diff(buff[i].b_boost, buff[i].b_gsl));
//    }

//    c1->Divide(2,2);
//    c1->cd(1);
//    h2->Draw();

    run_benchmark();

}



void TestBessel::run_benchmark()
{
    double xmin(0.0), xmax(20.0);
    int nx(201);
    double dx = (xmax-xmin)/(nx-1);

    TBenchmark mb;

    int ntotal(1e5);

    // warming up
    double value(0);
    for(int ix=0; ix<nx; ++ix) {
        double x = xmin + dx*ix;
        for(int i=0; i<ntotal; ++i) {
            value = TMath::BesselJ1(x);
            value = boost::math::cyl_bessel_j(1,x);
            value = MathFunctions::Bessel_J1(x);
        }
    }

    mb.Start("gsl");
    for(int ix=0; ix<nx; ++ix) {
        double x = xmin + dx*ix;
        for(int i=0; i<ntotal; ++i) {
            value = MathFunctions::Bessel_J1(x);
        }
    }
    mb.Stop("gsl");

    mb.Start("root");
    for(int ix=0; ix<nx; ++ix) {
        double x = xmin + dx*ix;
        for(int i=0; i<ntotal; ++i) {
            value = TMath::BesselJ1(x);
        }
    }
    mb.Stop("root");

    mb.Start("boost");
    for(int ix=0; ix<nx; ++ix) {
        double x = xmin + dx*ix;
        for(int i=0; i<ntotal; ++i) {
            value = boost::math::cyl_bessel_j(1,x);
        }
    }
    mb.Stop("boost");


    value = value*2;

    std::cout << "root " << mb.GetCpuTime("root") << " " << mb.GetRealTime("root") << std::endl;
    std::cout << "boost " << mb.GetCpuTime("boost") << " " << mb.GetRealTime("boost") << std::endl;
    std::cout << "gsl " << mb.GetCpuTime("gsl") << " " << mb.GetRealTime("gsl") << std::endl;

}


