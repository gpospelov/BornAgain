#include "FitComparisonViewController.h"
#include "AxesItems.h"
#include "DataItem.h"
#include "DataItem1DView.h"
#include "IntensityDataFunctions.h"
#include "JobItem.h"
#include "PropertyRepeater.h"
#include "RealDataItem.h"
#include "SessionModel.h"

namespace
{
const double relative_diff_min_1d = 1e-05;
const double relative_diff_max_1d = 4.0;
}

FitComparison1DViewController::FitComparison1DViewController(QObject* parent)
    : QObject(parent),
      m_diff_item_controller(new DiffItemController(Constants::SpecularDataType, this)),
      m_diff_view_item(dynamic_cast<DataItem1DView*>(
          m_diff_item_controller->model()->insertNewItem(Constants::DataItem1DViewType))),
      m_appearanceRepeater(new PropertyRepeater(this)), m_xAxisRepeater(new PropertyRepeater(this))
{
    m_diff_view_item->addItem(m_diff_item_controller->diffItem());
}

DataItem1DView* FitComparison1DViewController::diffItemView()
{
    return m_diff_view_item;
}

void FitComparison1DViewController::setItem(JobItem* job_item)
{
    assert(job_item);

    clear();
    m_diff_item_controller->setJobItem(job_item);
    diffItemView()->setJobItem(job_item);

    auto job_data_view = job_item->dataItemView();

    m_appearanceRepeater->addItem(job_data_view);
    m_appearanceRepeater->addItem(diffItemView());

    m_xAxisRepeater->addItem(job_data_view->xAxisItem());
    m_xAxisRepeater->addItem(diffItemView()->xAxisItem());

    diffItemView()->setXaxisTitle(job_data_view->getXaxisTitle());
    diffItemView()->setYaxisTitle("Relative difference");
    diffItemView()->setLowerY(relative_diff_min_1d);
    diffItemView()->setUpperY(relative_diff_max_1d);
}

void FitComparison1DViewController::updateDiffData()
{
    m_diff_item_controller->updateDiffData();
}

void FitComparison1DViewController::resetDiffView()
{
    diffItemView()->resetView();
    diffItemView()->setLowerY(relative_diff_min_1d);
    diffItemView()->setUpperY(relative_diff_max_1d);
}

void FitComparison1DViewController::clear()
{
    m_diff_item_controller->unsubscribe();
    m_appearanceRepeater->clear();
    m_xAxisRepeater->clear();
}

DiffItemController::DiffItemController(const QString& data_type, QObject* parent)
    : QObject(parent), m_current_item(nullptr),
      m_private_model(new SessionModel("TempIntensityDataModel", this)),
      m_diff_item(dynamic_cast<DataItem*>(m_private_model->insertNewItem(data_type)))
{
    assert(m_diff_item);
}

DiffItemController::~DiffItemController()
{
    unsubscribe();
}

void DiffItemController::setJobItem(JobItem* job_item)
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

void DiffItemController::subscribe()
{
    if (!m_current_item) {
        assert(false);
        return;
    }

    // on simulation data change
    m_current_item->dataItem()->mapper()->setOnValueChange([this]() { updateDiffData(); }, this);
}

void DiffItemController::unsubscribe()
{
    if (!m_current_item)
        return;
    m_current_item->dataItem()->mapper()->unsubscribe(this);
    m_diff_item->mapper()->unsubscribe(this);
    m_current_item = nullptr;
}
