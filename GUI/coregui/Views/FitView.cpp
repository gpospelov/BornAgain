#include "FitView.h"
#include "rootcanvas.h"

#include "TCanvas.h"
#include "TH2D.h"
#include "QVBoxLayout"
#include "TRandom.h"

FitManager::FitManager(QWidget *parent)
    : QWidget(parent)
{

    RootCanvas *canvas = new RootCanvas(this);
    canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    canvas->cd();
    TH2D *h2 = new TH2D("hpxpy","py vs px",40,-4,4,40,-4,4);
    for(size_t i=0; i<100000; ++i) {
        double px, py;
        gRandom->Rannor(px, py);
        h2->Fill(px,py);
    }
    h2->Draw("cont");
    canvas->Update();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(canvas);
    setLayout(mainLayout);

}


