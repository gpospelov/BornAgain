#include "SampleToolBar.h"
#include "MaterialEditor.h"
#include "MaterialProperty.h"
#include <QIcon>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QStyle>
#include <QComboBox>
#include <QButtonGroup>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QMenu>


#include "styledbar.h"

//! main tool bar on top of SampleView window
SampleToolBar::SampleToolBar(QWidget *parent)
    : QToolBar(parent)
{
    setMovable(false);

    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    setIconSize(QSize(size, size));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

//    m_materialBrowserAction = new QAction(QIcon(":/SampleDesigner/images/document-attribute-m.png"), tr("Material Editor (M)"), this);
//    m_materialBrowserAction->setShortcut(Qt::Key_M);
//    connect(m_materialBrowserAction, SIGNAL(triggered()), this, SLOT(materialBrowserCall()));
//    addAction(m_materialBrowserAction);



    // Select & Pan
    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_pointer.png"));
    QToolButton *panButton = new QToolButton;
    panButton->setCheckable(true);
    panButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_hand.png"));

    QButtonGroup *pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, 0);
    pointerTypeGroup->addButton(panButton, 1);
//    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
//            this, SLOT(pointerGroupClicked(int)));
    addWidget(pointerButton);
    addWidget(panButton);


    // unddo redo
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));

    QToolButton *unddoButton = new QToolButton;
    unddoButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_unddo.png"));
    addWidget(unddoButton);
    QToolButton *redoButton = new QToolButton;
    redoButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_redo.png"));
    addWidget(redoButton);

    // Erase item
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
    addWidget(new QLabel(" "));
//    addSeparator();
//    addWidget(new QLabel(" "));
    QToolButton *recycleButton = new QToolButton;
    recycleButton->setText("Remove item");
    recycleButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_recycle.png"));
    recycleButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addWidget(recycleButton);


    // center
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
    QToolButton *centerButton = new QToolButton;
    centerButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_center.png"));
    addWidget(centerButton);

    QToolButton *alignButton = new QToolButton;
    alignButton->setIcon(QIcon(":/SampleDesigner/images/toolbar_align.png"));
    addWidget(alignButton);


    // Zoom
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));



    QLabel *label = new QLabel("Zoom ");
    //label->setStyleSheet("QLabel { color : rgb(222, 222, 222); }");
    addWidget(label);

    QComboBox *m_scaleCombo = new QComboBox;
    //m_scaleCombo->setEditable(true);
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    m_scaleCombo->addItems(scales);
    m_scaleCombo->setCurrentIndex(1);
//    QDoubleValidator *validator = new QDoubleValidator(1.0, 500., 1, this);
//    m_scaleCombo->setValidator(validator);
//    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
//            this, SLOT(fontSizeChanged(QString)));
    addWidget(m_scaleCombo);





    // MaterialEditor
    addWidget(new QLabel(" "));
    addSeparator();
    addWidget(new QLabel(" "));
    QToolButton *materialEditor = new QToolButton;
    materialEditor->setText("Material Editor");
    materialEditor->setIcon(QIcon(":/SampleDesigner/images/toolbar_materialeditor.png"));
    materialEditor->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addWidget(materialEditor);


    //
//    QMenu *zoomMenu = new QMenu();
//    QAction *action1 = new QAction("50",this);
//    QAction *action2 = new QAction("100",this);
//    zoomMenu->addAction(action1);
//    zoomMenu->addAction(action2);

//    QToolButton *xxx = new QToolButton;
//    xxx->setPopupMode(QToolButton::MenuButtonPopup);
//    xxx->setMenu(zoomMenu);
//    xxx->setText("Material Editor");
//    xxx->setIcon(QIcon(":/SampleDesigner/images/toolbar_materialeditor.png"));
//    xxx->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
//    addWidget(xxx);


    //    m_addDefaultGisasAction = new QAction(tr("Default GISAS instrument"), this);
    //    m_addDefaultGisasAction->setStatusTip(tr("Add default GISAS instrument"));


//    QPushButton *runSimulationButton = new QPushButton(tr("Run Simulation"));
//    runSimulationButton->setIcon(QIcon(":/images/main_simulation.png"));
//    addWidget(runSimulationButton);



//    m_zoomOutAction = new QAction(QIcon(":/SampleDesigner/images/magnifier-zoom-out.png"), tr("Zoom out, Ctrl-"), this);
//    m_zoomOutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
//    connect(m_zoomOutAction, SIGNAL(triggered()), this, SIGNAL(zoomOut()));
//    addAction(m_zoomOutAction);

//    m_zoomInAction = new QAction(QIcon(":/SampleDesigner/images/magnifier-zoom-in.png"), tr("Zoom in, Ctrl+"), this);
//    m_zoomInAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
//    connect(m_zoomInAction, SIGNAL(triggered()), this, SIGNAL(zoomIn()));
//    addAction(m_zoomInAction);

//    m_zoomFitAction = new QAction(QIcon(":/SampleDesigner/images/magnifier-zoom-fit.png"), tr("Zoom fit"), this);
//    connect(m_zoomFitAction, SIGNAL(triggered()), this, SIGNAL(zoomFit()));
//    addAction(m_zoomFitAction);

////    addWidget(new Manhattan::StyledSeparator());

//    m_clearAllAction = new QAction(QIcon(":/SampleDesigner/images/eraser.png"), tr("Clear all"), this);
//    connect(m_clearAllAction, SIGNAL(triggered()), this, SIGNAL(clearAll()));
//    addAction(m_clearAllAction);

////    insertSeparator(m_clearAllAction);
////    Manhattan::StyledSeparator *sep = new Manhattan::StyledSeparator(this);
////    addWidget(new Manhattan::StyledSeparator());

//    m_sceneToISampleAction = new QAction(QIcon(":/SampleDesigner/images/next.png"), tr("Smart align"), this);
//    connect(m_sceneToISampleAction, SIGNAL(triggered()), this, SIGNAL(smartAlign()));
//    addAction(m_sceneToISampleAction);

//    addSeparator();

//    QComboBox *m_scaleCombo = new QComboBox;
//    QStringList scales;
//    scales << tr("50%") << tr("100%") << tr("150%");
//    m_scaleCombo->addItems(scales);
//    m_scaleCombo->setCurrentIndex(1);
//    addWidget(m_scaleCombo);
//    connect(m_scaleCombo, SIGNAL(currentIndexChanged(QString)),
//            this, SIGNAL(sceneScaleChanged(QString)));




//    insertSeparator(m_clearAllAction);

}


void SampleToolBar::materialBrowserCall()
{
    //MaterialBrowser::BrowserViewCall();
    MaterialProperty mp = MaterialEditor::selectMaterialProperty();
    qDebug() << "SampleToolBar::materialBrowserCall()" << mp.getName() << mp.getColor();

}
