#include "fitmanager.h"
//#include <QtWidgets>
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
//    QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

//    QLabel *nameLabel = new QLabel(tr("Name:"));
//    QLineEdit *nameEdit = new QLineEdit;

//    QLabel *dateLabel = new QLabel(tr("Released after:"));
//    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

//    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
//    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

//    QSpinBox *hitsSpinBox = new QSpinBox;
//    hitsSpinBox->setPrefix(tr("Return up to "));
//    hitsSpinBox->setSuffix(tr(" results"));
//    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
//    hitsSpinBox->setMinimum(1);
//    hitsSpinBox->setMaximum(100);
//    hitsSpinBox->setSingleStep(10);

//    QPushButton *startQueryButton = new QPushButton(tr("Start query"));

//    QGridLayout *packagesLayout = new QGridLayout;
//    packagesLayout->addWidget(nameLabel, 0, 0);
//    packagesLayout->addWidget(nameEdit, 0, 1);
//    packagesLayout->addWidget(dateLabel, 1, 0);
//    packagesLayout->addWidget(dateEdit, 1, 1);
//    packagesLayout->addWidget(releasesCheckBox, 2, 0);
//    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
//    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
//    packagesGroup->setLayout(packagesLayout);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(packagesGroup);
//    mainLayout->addSpacing(12);
//    mainLayout->addWidget(startQueryButton);
//    mainLayout->addStretch(1);
//    setLayout(mainLayout);

    m_qcanvas = new TQtWidget(this,"qt-canvas");
    m_qcanvas->setMinimumSize(256, 256);
    m_qcanvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_qcanvas->EnableSignalEvents(kMousePressEvent);
    m_qcanvas->EnableSignalEvents(kMouseMoveEvent);

    m_qcanvas->GetCanvas()->cd();
    TH2D *h2 = new TH2D("hpxpy","py vs px",40,-4,4,40,-4,4);
    for(size_t i=0; i<100000; ++i) {
        double px, py;
        gRandom->Rannor(px, py);
        h2->Fill(px,py);
    }
    h2->Draw("cont");

    m_qcanvas->GetCanvas()->Modified();
    m_qcanvas->GetCanvas()->Update();

//    QLabel *label = new QLabel(tr("&Hist Info"));
    m_lineEdit = new QLineEdit;
    m_lineEdit->setReadOnly(true);
    m_lineEdit->insert("XXX");
//    QStatusBar *statusBar = new QStatusBar;
//    statusBar->showMessage("Hello world");
//    label->setBuddy(lineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_qcanvas);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(m_lineEdit);
    mainLayout->addStretch(100);
    setLayout(mainLayout);

    connect(m_qcanvas, SIGNAL(RootEventProcessed(TObject *,unsigned int, TCanvas *)), this,SLOT(CanvasEvent(TObject *, unsigned int, TCanvas *)));
    connect(m_qcanvas, SIGNAL(CanvasPainted()), this, SLOT(print_something()));

}


void FitManager::CanvasEvent(TObject *obj,unsigned int event,TCanvas *)
{
    (void)obj;
    (void)event;
    m_lineEdit->insert("AAA");
    std::cout << "XXX " << std::endl;
}

void FitManager::print_something()
{
    std::cout << "ZZZ " << std::endl;
}


//void qtrootexample1::CanvasEvent(TObject *obj,unsigned int event,TCanvas *)
//{
//TQtWidget *tipped = (TQtWidget *)sender();
//const char *objectInfo = obj->GetObjectInfo(tipped->GetEventX(),
//tipped->GetEventY());
//QString tipText ="You have ";
//if (tipped == tQtWidget1)
//tipText +="clicked";
//else
//tipText +="passed";
//tipText += " the object <";
//tipText += obj->GetName();
//tipText += "> of class ";
//tipText += obj->ClassName();
//tipText += " : ";
//tipText += objectInfo;
//QWhatsThis::display(tipText)
//}
