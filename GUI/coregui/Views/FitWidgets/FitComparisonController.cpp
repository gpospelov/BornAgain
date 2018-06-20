// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonController.cpp
//! @brief     Implements class FitComparisonController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitComparisonController.h"
#include "AxesItems.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "PropertyRepeater.h"
#include "RealDataItem.h"
#include "SessionModel.h"
#include "SpecularDataItem.h"

namespace {
const double default_y_min = 0.0;
const double default_y_max = 2.0;

template<class DataType>
DataType* simulationData(JobItem* job_item)
{
    assert(dynamic_cast<DataType*>(job_item->dataItem()));
    return dynamic_cast<DataType*>(job_item->dataItem());
}

template<class DataType>
DataType* realData(JobItem* job_item)
{
    assert(dynamic_cast<DataType*>(job_item->realDataItem()->dataItem()));
    return dynamic_cast<DataType*>(job_item->realDataItem()->dataItem());
}
}

class DiffItemController : public QObject
{
public:
    DiffItemController(const QString& data_type, QObject* parent);
    ~DiffItemController() override;
    void setItem(JobItem* job_item);
    void updateDiffData();
    DataItem* diffItem();
    void subscribe();
    void unsubscribe();
private:
    JobItem* m_current_item;
    SessionModel* m_tempIntensityDataModel;
    DataItem* m_diff_item;
};

FitComparisonController2D::FitComparisonController2D(QObject* parent)
    : QObject(parent)
    , m_appearanceRepeater(new PropertyRepeater(this))
    , m_xAxisRepeater(new PropertyRepeater(this))
    , m_yAxisRepeater(new PropertyRepeater(this))
    , m_zAxisRepeater(new PropertyRepeater(this))
    , m_relativeDiffItem(nullptr)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this))
{
    createRelativeDifferenceItem();
}

IntensityDataItem* FitComparisonController2D::diffItem()
{
    return m_relativeDiffItem;
}

void FitComparisonController2D::setItems(IntensityDataItem* realDataItem,
                                       IntensityDataItem* simDataItem)
{
    double zmin = realDataItem->getLowerZ();
    double zmax = realDataItem->getUpperZ();
    simDataItem->setLowerAndUpperZ(zmin, zmax);

    m_appearanceRepeater->addItem(realDataItem);
    m_appearanceRepeater->addItem(simDataItem);
    m_appearanceRepeater->addItem(diffItem());

    m_xAxisRepeater->addItem(realDataItem->xAxisItem());
    m_xAxisRepeater->addItem(simDataItem->xAxisItem());
    m_xAxisRepeater->addItem(diffItem()->xAxisItem());

    m_yAxisRepeater->addItem(realDataItem->yAxisItem());
    m_yAxisRepeater->addItem(simDataItem->yAxisItem());
    m_yAxisRepeater->addItem(diffItem()->yAxisItem());

    m_zAxisRepeater->addItem(realDataItem->zAxisItem());
    m_zAxisRepeater->addItem(simDataItem->zAxisItem());
}

void FitComparisonController2D::clear()
{
    m_appearanceRepeater->clear();

    m_xAxisRepeater->clear();
    m_yAxisRepeater->clear();
    m_zAxisRepeater->clear();
}

void FitComparisonController2D::createRelativeDifferenceItem()
{
    m_tempIntensityDataModel->clear();

    m_relativeDiffItem = dynamic_cast<IntensityDataItem*>(
        m_tempIntensityDataModel->insertNewItem(Constants::IntensityDataType));
}

FitComparisonController1D::FitComparisonController1D(QObject* parent)
    : QObject(parent)
    , m_diff_item_controller(new DiffItemController(Constants::SpecularDataType, this))
    , m_appearanceRepeater(new PropertyRepeater(this))
    , m_xAxisRepeater(new PropertyRepeater(this))
{
}

SpecularDataItem* FitComparisonController1D::diffItem()
{
    assert(dynamic_cast<SpecularDataItem*>(m_diff_item_controller->diffItem()));
    return dynamic_cast<SpecularDataItem*>(m_diff_item_controller->diffItem());
}

void FitComparisonController1D::setItem(JobItem* job_item)
{
    assert(job_item);

    clear();
    m_diff_item_controller->setItem(job_item);

    auto sim_data_item = simulationData<SpecularDataItem>(job_item);
    auto real_data_item = realData<SpecularDataItem>(job_item);

    m_appearanceRepeater->addItem(real_data_item);
    m_appearanceRepeater->addItem(sim_data_item);
    m_appearanceRepeater->addItem(diffItem());

    m_xAxisRepeater->addItem(real_data_item->xAxisItem());
    m_xAxisRepeater->addItem(sim_data_item->xAxisItem());
    m_xAxisRepeater->addItem(diffItem()->xAxisItem());

    diffItem()->setXaxisTitle(sim_data_item->getXaxisTitle());
    diffItem()->setYaxisTitle("Relative difference");
    diffItem()->setLog(false);
    diffItem()->setLowerY(default_y_min);
    diffItem()->setUpperY(default_y_max);
}

void FitComparisonController1D::updateDiffData()
{
    m_diff_item_controller->updateDiffData();
}

void FitComparisonController1D::resetDiffItem()
{
    diffItem()->resetView();
    diffItem()->setLowerY(default_y_min);
    diffItem()->setUpperY(default_y_max);
}

void FitComparisonController1D::clear()
{
    m_diff_item_controller->unsubscribe();
    m_appearanceRepeater->clear();
    m_xAxisRepeater->clear();
}

DiffItemController::DiffItemController(const QString& data_type, QObject* parent)
    : QObject(parent)
    , m_current_item(nullptr)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this))
    , m_diff_item(dynamic_cast<DataItem*>(m_tempIntensityDataModel->insertNewItem(data_type)))
{
    assert(m_diff_item);
}

DiffItemController::~DiffItemController()
{
    unsubscribe();
}

void DiffItemController::setItem(JobItem* job_item)
{
    assert(job_item);
    if (m_current_item)
        unsubscribe();
    m_current_item = job_item;
    subscribe();
    updateDiffData();
}

void DiffItemController::updateDiffData()
{
    assert(m_current_item);

    auto sim_data = m_current_item->dataItem();
    auto real_data = m_current_item->realDataItem()->dataItem();
    assert(sim_data && real_data);

    if (!sim_data->getOutputData()) // job failed
        return;

    m_diff_item->setOutputData(IntensityDataFunctions::createRelativeDifferenceData(
                                   *sim_data->getOutputData(), *real_data->getOutputData())
                               .release());
}

DataItem* DiffItemController::diffItem()
{
    return m_diff_item;
}

void DiffItemController::subscribe()
{
    if (!m_current_item) {
        assert(false);
        return;
    }

    // on simulation data change
    m_current_item->dataItem()->mapper()->setOnValueChange([this]() { updateDiffData(); }, this);

    // on diff item units change
    m_diff_item->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == DataItem::P_AXES_UNITS)
                m_diff_item->updateAxesUnits(m_current_item->instrumentItem());
        },
        this);
}

void DiffItemController::unsubscribe()
{
    if (!m_current_item)
        return;
    m_current_item->dataItem()->mapper()->unsubscribe(this);
    m_diff_item->mapper()->unsubscribe(this);
    m_current_item = nullptr;
}
