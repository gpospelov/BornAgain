#include "fitmanager.h"
#include "rootcanvas.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStatusBar>
#include <iostream>
#include <QSizePolicy>

#include "TH2D.h"
#include "TQtWidget.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TApplication.h"

FitManager::FitManager(QWidget *parent)
    : QWidget(parent)
{

//    m_qcanvas = new TQtWidget(this,"qt-canvas");
//    m_qcanvas->setMinimumSize(256, 256);
//    m_qcanvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    m_qcanvas->EnableSignalEvents(kMousePressEvent);
//    m_qcanvas->EnableSignalEvents(kMouseMoveEvent);

//    m_qcanvas->GetCanvas()->cd();
//    TH2D *h2 = new TH2D("hpxpy","py vs px",40,-4,4,40,-4,4);
//    for(size_t i=0; i<100000; ++i) {
//        double px, py;
//        gRandom->Rannor(px, py);
//        h2->Fill(px,py);
//    }
//    h2->Draw("cont");

//    m_qcanvas->GetCanvas()->Modified();
//    m_qcanvas->GetCanvas()->Update();

////    QLabel *label = new QLabel(tr("&Hist Info"));
//    m_lineEdit = new QLineEdit;
//    m_lineEdit->setReadOnly(true);
//    m_lineEdit->insert("XXX");
////    QStatusBar *statusBar = new QStatusBar;
////    statusBar->showMessage("Hello world");
////    label->setBuddy(lineEdit);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(m_qcanvas);
//    mainLayout->addSpacing(12);
//    mainLayout->addWidget(m_lineEdit);
//    mainLayout->addStretch(100);
//    setLayout(mainLayout);

//    connect(m_qcanvas, SIGNAL(RootEventProcessed(TObject *,unsigned int, TCanvas *)), this,SLOT(CanvasEvent(TObject *, unsigned int, TCanvas *)));
//    connect(m_qcanvas, SIGNAL(CanvasPainted()), this, SLOT(print_something()));

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


void FitManager::CanvasEvent(TObject *obj,unsigned int event,TCanvas *)
{
    (void)obj;
    (void)event;
//    m_lineEdit->insert("AAA");
//    std::cout << "XXX " << std::endl;
}

void FitManager::print_something()
{
//    std::cout << "ZZZ " << std::endl;
}


