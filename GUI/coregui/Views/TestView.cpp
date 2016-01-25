// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "TestView.h"
#include "MaskEditor.h"
#include "RunFitWidget.h"
#include "FitView.h"
#include "mainwindow.h"
#include "FitParameterWidget.h"
#include "JobModel.h"
#include <QMimeData>
#include <QVBoxLayout>
#include <AccordionWidget.h>
#include <QLineEdit>
#include <QCheckBox>
#include <QTabWidget>



// FIXME_DAVID Rename Ivona's FitView into ObsoleteFitView. And use nice name FitView for own purpose.
//  -- suggestion: for consistency use prefix Obsolete for all classes you are goind to throw soon
//  -- you may want to add to all Ivona's classes prefix Obsolete. Don't forget about 'ifndef' header guards

// FIXME_DAVID Move your activity from TestView to FitView.
// - FitView should contain QTabWidget with 3 tabs:
// - 1) ImportDataWidget (empty for the moment) 2) FitSettingsWidget 3) RunFitWidget

// FIXME_DAVID FitSettingsWidget should contain
// - FitParametersWidget (for the moment), and later sample/instrument selector + MinimizerSettingsWidgert


TestView::TestView(MainWindow *window, QWidget *parent)
    : QWidget(parent)
    , m_mainWindow(window)
{
//    test_MaskEditor();
//    test_AccordionWidget();
    test_RunFitWidget();

}

void TestView::test_MaskEditor()
{
    MaskEditor *maskEditor = new MaskEditor();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(maskEditor);
    setLayout(layout);

    maskEditor->init_test_model();
}

void TestView::test_AccordionWidget()
{
    AccordionWidget *myAccordion = new AccordionWidget();
    myAccordion->setMultiActive(true);
    // add the Accordion to your layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(myAccordion);
    setLayout(layout);

    // add a content pane with a header
    int firstPaneIndex = myAccordion->addContentPane("My first content pane");
    // make sure our content pane was added
    if (firstPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame *contentFrame = myAccordion->getContentPane(firstPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        contentFrame->layout()->addWidget(new QLabel("Hello Cute World!!!"));
    }

    // add a content pane with a header
    int secondPaneIndex = myAccordion->addContentPane("Basic settings");
    // make sure our content pane was added
    if (secondPaneIndex != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        QFrame *contentFrame = myAccordion->getContentPane(secondPaneIndex)->getContentFrame();
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QLineEdit *led = new QLineEdit();
        QLineEdit *led2 = new QLineEdit();
        contentFrame->layout()->addWidget(new QLabel("Name:"));
        contentFrame->layout()->addWidget(led);
        contentFrame->layout()->addWidget(new QLabel("Living place:"));
        contentFrame->layout()->addWidget(led2);
    }

    // add a content pane with a header
    int third = myAccordion->addContentPane("Advanced");
    // make sure our content pane was added
    if (third != -1) {
        // get a QFrame* from the Content Pane. This is where we place our content
        myAccordion->getContentPane(third)->setMaximumHeight(500);
        QFrame *contentFrame = myAccordion->getContentPane(third)->getContentFrame();
        contentFrame->setMaximumHeight(500);
        // give the QFrame a QLayout
        contentFrame->setLayout(new QVBoxLayout());
        // add a simpel QLabel to the frame
        QCheckBox *cb = new QCheckBox();
        cb->setText("Option 1");
        QCheckBox *cb2 = new QCheckBox();
        cb2->setText("Option 2");
        QCheckBox *cb3 = new QCheckBox();
        cb3->setText("Option 3");
        QCheckBox *cb4 = new QCheckBox();
        cb4->setText("Option 4");
        QCheckBox *cb5 = new QCheckBox();
        cb5->setText("Option 5");
        QCheckBox *cb6 = new QCheckBox();
        cb6->setText("Option 6");
        QCheckBox *cb7 = new QCheckBox();
        cb7->setText("Option 7");
        contentFrame->layout()->addWidget(cb);
        contentFrame->layout()->addWidget(cb2);
        contentFrame->layout()->addWidget(cb3);
        contentFrame->layout()->addWidget(cb4);
        contentFrame->layout()->addWidget(cb5);
        contentFrame->layout()->addWidget(cb6);
        contentFrame->layout()->addWidget(cb7);

    }
}

void TestView::test_RunFitWidget()
{
    // FIXME_DAVID Use consistent variable names: not 'maskEditor', but runFitWidget

    RunFitWidget *maskEditor = new RunFitWidget();
    //FitView *fw = new FitView(m_mainWindow->getSampleModel(), m_mainWindow->getInstrumentModel());

    FitParameterWidget *fitting = new FitParameterWidget(m_mainWindow);
    QVBoxLayout *layout = new QVBoxLayout;
    QTabWidget *tabs = new QTabWidget;
    tabs->addTab(maskEditor, "Run Fit");
    //tabs->addTab(fw, "FitView by Ivonna");
    tabs->addTab(fitting, "Test TreeView");
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(tabs);
    setLayout(layout);

}
