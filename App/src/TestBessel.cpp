#include "TestBessel.h"
#include "MathFunctions.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TBenchmark.h"
#include "TMath.h"
#include <iostream>




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
        buff[i].b1 = TMath::BesselJ1(x);
        buff[i].b2 = MathFunctions::Bessel_J1(x);

        std::cout << i << " " << x << " " << buff[i].b1 << std::endl;
    }


    TCanvas *c1 = new TCanvas("c1","c1",1024, 768);
    TH1D *h2 = new TH1D("h2","h2", nx, xmin - dx/2., xmax+dx/2.);
    for(int i=0; i<nx; ++i) {
        h2->Fill(buff[i].x, rel_diff(buff[i].b1, buff[i].b2));
    }

    c1->Divide(2,2);
    c1->cd(1);
    h2->Draw();


}



void TestBessel::run_benchmark()
{

}


