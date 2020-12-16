// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <darefl/model/instrumentitems.h>
#include <darefl/model/item_constants.h>
#include <darefl/model/modelutils.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/graphitem.h>

using namespace ModelView;

namespace DaRefl {

BasicSpecularScanItem::BasicSpecularScanItem(const std::string& model_type)
    : CompoundItem(model_type) {}

// ----------------------------------------------------------------------------

QSpecScanItem::QSpecScanItem() : BasicSpecularScanItem(Constants::QSpecScanItemType) {
    addProperty(P_NBINS, 500)->setDisplayName("Nbins");
    addProperty(P_QMIN, 0.0)->setDisplayName("Qmin");
    addProperty(P_QMAX, 1.0)->setDisplayName("Qmax");
}

std::vector<double> QSpecScanItem::qScanValues() const {
    int nbins = property<int>(P_NBINS);
    double qmin = property<double>(P_QMIN);
    double qmax = property<double>(P_QMAX);
    return FixedBinAxisItem::create(nbins, qmin, qmax)->binCenters();
}

// ----------------------------------------------------------------------------

ExperimentalScanItem::ExperimentalScanItem()
    : BasicSpecularScanItem(Constants::ExperimentalScanItemType) {
    addProperty(P_IMPORTED_DATA, ExternalProperty::undefined())->setDisplayName("Graph");
}

void ExperimentalScanItem::setGraphItem(GraphItem* graph) {
    setProperty(P_IMPORTED_DATA, Utils::CreateProperty(graph));
}

GraphItem* ExperimentalScanItem::graphItem() const {
    if (model()) {
        auto graph_id = property<ExternalProperty>(P_IMPORTED_DATA).identifier();
        return dynamic_cast<GraphItem*>(model()->findItem(graph_id));
    }
    return nullptr;
}

std::vector<double> ExperimentalScanItem::qScanValues() const {
    return graphItem() ? graphItem()->binCenters() : std::vector<double>();
}

// ----------------------------------------------------------------------------

SpecularScanGroupItem::SpecularScanGroupItem() : GroupItem(Constants::SpecularScanGroupItemType) {
    registerItem<QSpecScanItem>("Q-scan", /*make_selected*/ true);
    registerItem<ExperimentalScanItem>("Based on data");
    init_group();
}

// ----------------------------------------------------------------------------

SpecularBeamItem::SpecularBeamItem() : CompoundItem(Constants::SpecularBeamItemType) {
    addProperty(P_INTENSITY, 1.0)->setDisplayName("Intensity");
    addProperty<SpecularScanGroupItem>(P_SCAN_GROUP)->setDisplayName("Specular scan type");
}

std::vector<double> SpecularBeamItem::qScanValues() const {
    auto scan_group = item<SpecularScanGroupItem>(P_SCAN_GROUP);
    if (auto scanItem = dynamic_cast<const BasicSpecularScanItem*>(scan_group->currentItem());
        scanItem)
        return scanItem->qScanValues();
    return {};
}

double SpecularBeamItem::intensity() const {
    return property<double>(P_INTENSITY);
}

//! Returns corresponding experimental graph. If current setup is based on simple q-scan, will
//! return nullptr.

GraphItem* SpecularBeamItem::experimentalGraphItem() const {
    auto scan_group = item<SpecularScanGroupItem>(P_SCAN_GROUP);
    if (auto scanItem = dynamic_cast<const ExperimentalScanItem*>(scan_group->currentItem());
        scanItem)
        return scanItem->graphItem();
    return nullptr;
}

// ----------------------------------------------------------------------------

SpecularInstrumentItem::SpecularInstrumentItem()
    : CompoundItem(Constants::SpecularInstrumentItemType) {
    addProperty<SpecularBeamItem>(P_BEAM);
}

SpecularBeamItem* SpecularInstrumentItem::beamItem() const {
    return item<SpecularBeamItem>(P_BEAM);
}

} // namespace DaRefl
