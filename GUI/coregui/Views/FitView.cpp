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



//    // generate some data:
//    QVector<double> x(101), y(101); // initialize with entries 0..100
//    for (int i=0; i<101; ++i)
//    {
//      x[i] = i/50.0 - 1; // x goes from -1 to 1
//      y[i] = x[i]*x[i];  // let's plot a quadratic function
//    }
//    // create graph and assign data to it:
//    m_customPlot->addGraph();
//    m_customPlot->graph(0)->setData(x, y);
//    // give the axes some labels:
//    m_customPlot->xAxis->setLabel("x");
//    m_customPlot->yAxis->setLabel("y");
//    // set axes ranges, so we see all data:
//    m_customPlot->xAxis->setRange(-1, 1);
//    m_customPlot->yAxis->setRange(0, 1);


    m_customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    m_customPlot->axisRect()->setupFullAxesBox(true);
    m_customPlot->xAxis->setLabel("x");
    m_customPlot->yAxis->setLabel("y");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(m_customPlot->xAxis, m_customPlot->yAxis);
    m_customPlot->addPlottable(colorMap);
    int nx = 200;
    int ny = 200;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y, z;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
        double r = 3*qSqrt(x*x+y*y)+1e-2;
        z = 2*x*(qCos(r+2)/r-qSin(r+2)/r); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, z);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(m_customPlot);
    m_customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale
    colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(m_customPlot);
    m_customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    m_customPlot->rescaleAxes();





    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(canvas);
    mainLayout->addWidget(m_customPlot);
    setLayout(mainLayout);

}


