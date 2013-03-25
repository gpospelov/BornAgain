// ************************************************************************** //
//                                                                           
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestFittingBenchmark.cpp 
//! @brief     Implements class TestFittingBenchmark.
//
//! Homepage:  apps.jcns.fz-juelich.de/BornAgain
//! License:   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "TestFittingBenchmark.h"
//#include "BenchmarkFunctions.h"

#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include <iostream>

void TestFittingBenchmark::execute()
{
//    gStyle->SetPalette(1);

//    BenchmarkFunctions::DeJong *fo = new BenchmarkFunctions::DeJong();
//    double xx[2] = {1.0, 1.0};
//    double pp[2] = {1.0, 1.0};
//    std::cout << (*fo)(xx, pp) << std::endl;

//    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
//    c1->cd();

//    TF2 * f = new TF2("f", fo, fo->m_xmin, fo->m_xmax, fo->m_ymin, fo->m_ymax, fo->m_npar, fo->m_name.c_str() );
//    f->SetParameters(10.0, 0.5);

//    f->Draw("colz");
}
