// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataCanvas.cpp
//! @brief     Implements class IntensityDataCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IntensityDataCanvas.h"
#include "AppSvc.h"
#include "ColorMap.h"
#include "ColorMapCanvas.h"
#include "IntensityDataItem.h"
#include "SavePlotAssistant.h"
#include "projectmanager.h"
#include "ComboProperty.h"
#include <QAction>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QSettings>

namespace {

QString group_name() { return QStringLiteral("IntensityDataCanvas/"); }
QString gradient_setting_name() { return group_name()+IntensityDataItem::P_GRADIENT; }
QString interpolation_setting_name() { return group_name()+IntensityDataItem::P_IS_INTERPOLATED;}

}

IntensityDataCanvas::IntensityDataCanvas(QWidget *parent)
    : SessionItemWidget(parent)
    , m_colorMap(new ColorMapCanvas)
    , m_resetViewAction(nullptr)
    , m_savePlotAction(nullptr)
    , m_fftAction(nullptr)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_colorMap);
    setLayout(layout);

    m_colorMap->setStatusLabelEnabled(true);

    initActions();

    connect(m_colorMap->customPlot(), &QCustomPlot::mousePress,
            this, &IntensityDataCanvas::onMousePress, Qt::UniqueConnection);
}

void IntensityDataCanvas::setItem(SessionItem* intensityItem)
{
    SessionItemWidget::setItem(intensityItem);
    m_colorMap->setItem(intensityDataItem());

    applyPersistentSettings();
}

QSize IntensityDataCanvas::sizeHint() const
{
    return QSize(500, 400);
}

QSize IntensityDataCanvas::minimumSizeHint() const
{
    return QSize(128, 128);
}

QList<QAction*> IntensityDataCanvas::actionList()
{
    return QList<QAction*>() << m_resetViewAction << m_savePlotAction << m_fftAction;
}

void IntensityDataCanvas::onResetViewAction()
{
    intensityDataItem()->resetView();
}

void IntensityDataCanvas::onSavePlotAction()
{
    QString dirname = AppSvc::projectManager()->userExportDir();
    SavePlotAssistant saveAssistant;
    saveAssistant.savePlot(dirname, m_colorMap->customPlot(), intensityDataItem());
}

void IntensityDataCanvas::onMousePress(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton)
        emit customContextMenuRequested(event->globalPos());
}

#include<QDebug>
void IntensityDataCanvas::onfftAction()
{
    //qDebug() << "IntensityDataCanvas::onFFTAction" << status;
    auto dataItem = intensityDataItem();
    auto data = dataItem->getOutputData();

    OutputData<double> fftData;
    fftData.copyFrom(*data);
    fftData.setAllTo(42.);
    dataItem->setOutputData(&fftData);
    //m_backup.reset(new OutputData<double>);
    //m_backup->copyFrom(*data);

    /*
    bool status=0;
    if(status == 0)
    {
        OutputData<double> fftData;
        fftData.copyFrom(*data);
        fftData.setAllTo(42.);
        dataItem->setOutputData(&fftData);
        m_backup.reset(new OutputData<double>);
        m_backup->copyFrom(*data);

        status = 1;

    }

    else
    {
        OutputData<double> backupData;
        backupData.copyFrom(*m_backup);
        dataItem->setOutputData(&backupData);
        status = 0;
    }
    */
//    // convert data to vector<vector<double>>

//    auto fftOutputData = IntensityDaqtaFunctions::fft(*data);
//    dataItem->setOutputData(fftOutputData);
}

void IntensityDataCanvas::subscribeToItem()
{
    intensityDataItem()->mapper()->setOnPropertyChange(
        [this](const QString& name)
    {
        onPropertyChanged(name);
    }, this);

}

IntensityDataItem* IntensityDataCanvas::intensityDataItem()
{
    IntensityDataItem* result = dynamic_cast<IntensityDataItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

void IntensityDataCanvas::initActions()
{
    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset view\n"
                                  "x,y,z axes range will be set to default");
    connect(m_resetViewAction, &QAction::triggered, this, &IntensityDataCanvas::onResetViewAction);

    m_savePlotAction = new QAction(this);
    m_savePlotAction->setText("Save");
    m_savePlotAction->setIcon(QIcon(":/images/toolbar16light_save.svg"));
    m_savePlotAction->setToolTip("Save plot");
    connect(m_savePlotAction, &QAction::triggered, this, &IntensityDataCanvas::onSavePlotAction);

    m_fftAction = new QAction(this);
    m_fftAction->setText("Fourier Transform");
    //m_fftAction->setIcon(QIcon(":/images/toolbar16light_save.svg"));
    m_fftAction->setToolTip("Get the Fourier Transform of this intensity map");
    connect(m_fftAction, &QAction::triggered, this, &IntensityDataCanvas::onfftAction);
}

//! Reads gradient/ interpolation settings from IntensityDataItem and writes to persistant
//! project settings.

void IntensityDataCanvas::onPropertyChanged(const QString& name)
{
    if (name == IntensityDataItem::P_GRADIENT) {
        QSettings settings;
        settings.setValue(gradient_setting_name(), intensityDataItem()->getGradient());
    } else if (name == IntensityDataItem::P_IS_INTERPOLATED) {
        QSettings settings;
        settings.setValue(interpolation_setting_name(), intensityDataItem()->isInterpolated());
    }
}

//! Apply persistent settings (gradient, interpolation) to IntensityDataItem.

void IntensityDataCanvas::applyPersistentSettings()
{
    QSettings settings;

    if (settings.contains(gradient_setting_name())) {
        ComboProperty combo = intensityDataItem()->getItemValue(IntensityDataItem::P_GRADIENT)
                                  .value<ComboProperty>();
        QString persistentGradient = settings.value(gradient_setting_name()).toString();
        if (combo.getValue() != persistentGradient) {
            combo.setValue(settings.value(gradient_setting_name()).toString());
            intensityDataItem()->setItemValue(IntensityDataItem::P_GRADIENT, combo.variant());
        }
    }

    if (settings.contains(interpolation_setting_name())) {
        bool value = settings.value(interpolation_setting_name()).toBool();
        intensityDataItem()->setItemValue(IntensityDataItem::P_IS_INTERPOLATED, value);
    }
}
