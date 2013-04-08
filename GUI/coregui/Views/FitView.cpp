#include "FitView.h"
#include "rootcanvas.h"

#include "TCanvas.h"
#include "TH2D.h"
#include "QVBoxLayout"
#include "TRandom.h"

FitView::FitView(QWidget *parent)
    : QWidget(parent)
{

    RootCanvas *canvas = new RootCanvas(this);
    canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    canvas->cd();
    TH2D *h2 = new TH2D("hpxpy","py vs px",100,-2,2,100,-2,2);
    for(size_t i=0; i<500000; ++i) {
        double px, py;
        gRandom->Rannor(px, py);
        h2->Fill(px,py);
    }
    h2->Draw("CONT4 Z");
    canvas->Update();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(canvas);
    setLayout(mainLayout);

}


