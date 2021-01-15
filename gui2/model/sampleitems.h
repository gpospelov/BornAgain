//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/model/sampleitems.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_MODEL_SAMPLEITEMS_H
#define BORNAGAIN_GUI2_MODEL_SAMPLEITEMS_H

//! @file gui2/model/sampleitems.h
//! Collection of layer and multi-layer items to populate SampleModel.

#include "darefl_export.h"
#include "mvvm/model/compounditem.h"

namespace gui2 {

//! Item to represent the roughness of the layer.

class DAREFLCORE_EXPORT RoughnessItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_SIGMA = "P_SIGMA";
    static inline const std::string P_HURST = "P_HURST";
    static inline const std::string P_LATERAL_CORR_LENGTH = "P_LATERAL_CORR_LENGTH";

    RoughnessItem();
};

//! Layer with name, thickness and reference to material.

class DAREFLCORE_EXPORT LayerItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_NAME = "P_NAME";
    static inline const std::string P_MATERIAL = "P_MATERIAL";
    static inline const std::string P_THICKNESS = "P_THICKNESS";
    static inline const std::string P_ROUGHNESS = "P_ROUGHNESS";

    LayerItem();
};

//! Multi layer capable of holding layers and other multi-layers.

class DAREFLCORE_EXPORT MultiLayerItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_NAME = "P_NAME";
    static inline const std::string T_LAYERS = "T_LAYERS";
    static inline const std::string P_NREPETITIONS = "P_NREPETITIONS";

    MultiLayerItem();

    void activate() override;

private:
    void update_layer_appearance();
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_MODEL_SAMPLEITEMS_H
