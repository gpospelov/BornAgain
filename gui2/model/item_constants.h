//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/model/item_constants.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_ITEM_CONSTANTS_H
#define BORNAGAIN_GUI2_MODEL_ITEM_CONSTANTS_H

#include <string>

namespace gui2::Constants {

const std::string CanvasContainerItemType = "CanvasContainer";
const std::string CanvasItemType = "Canvas";
const std::string ExperimentalDataContainerItemType = "ExperimentalDataContainer";
const std::string ExperimentalScanItemType = "ExperimentalScan";
const std::string JobItemType = "Job";
const std::string LayerItemType = "Layer";
const std::string MaterialContainerItemType = "MaterialContainer";
const std::string MultiLayerItemType = "MultiLayer";
const std::string QSpecScanItemType = "QSpecScan";
const std::string RoughnessItemType = "Roughness";
const std::string SLDCanvasItemType = "SLDCanvas";
const std::string SLDMaterialItemType = "SLDMaterial";
const std::string SpecularBeamItemType = "SpecularBeam";
const std::string SpecularInstrumentItemType = "SpecularInstrument";
const std::string SpecularScanGroupItemType = "SpecularScanGroup";

} // namespace gui2::Constants

#endif // BORNAGAIN_GUI2_MODEL_ITEM_CONSTANTS_H
