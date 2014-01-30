#include "FitView.h"
#include "rootcanvas.h"

#include "TCanvas.h"
#include "TH2D.h"
#include "QVBoxLayout"
#include "TRandom.h"

FitView::FitView(QWidget *parent)
    : QWidget(parent)
    , m_customPlot(0)
{

    m_customPlot = new QCustomPlot(this);
    m_customPlot->setObjectName(QString::fromUtf8("customPlot"));

//    RootCanvas *canvas = new RootCanvas(this);
//    canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    canvas->cd();
//    TH2D *h2 = new TH2D("hpxpy","py vs px",100,-2,2,100,-2,2);
//    for(size_t i=0; i<500000; ++i) {
//        double px, py;
//        gRandom->Rannor(px, py);
//        h2->Fill(px,py);
//    }
//    h2->Draw("CONT4 Z");
//    canvas->Update();

    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i];  // let's plot a quadratic function
    }
    // create graph and assign data to it:
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    m_customPlot->xAxis->setLabel("x");
    m_customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    m_customPlot->xAxis->setRange(-1, 1);
    m_customPlot->yAxis->setRange(0, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(canvas);
    mainLayout->addWidget(m_customPlot);
    setLayout(mainLayout);

}


