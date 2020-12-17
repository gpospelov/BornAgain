//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/layerelementitem.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_SLDEDITOR_LAYERELEMENTITEM_H
#define BORNAGAIN_GUI2_SLDEDITOR_LAYERELEMENTITEM_H

#include "darefl_export.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/sessionmodel.h"

namespace gui2 {

//! The mvvm session item associated to a layer
class DAREFLCORE_EXPORT LayerElementItem : public ModelView::CompoundItem {
public:
    static inline const std::string P_X_POS = "P_X_POS";
    static inline const std::string P_WIDTH = "P_WIDTH";
    static inline const std::string P_HEIGHT = "P_HEIGHT";
    static inline const std::string P_ROUGHNESS = "P_ROUGHNESS";

    static inline const std::string P_SIDE_THICKNESS = "P_SIDE_THICKNESS";
    static inline const std::string P_SIDE_BRUSH_COLOR = "P_SIDE_BRUSH_COLOR";
    static inline const std::string P_SIDE_PEN_WIDTH = "P_SIDE_PEN_WIDTH";
    static inline const std::string P_SIDE_PEN_COLOR = "P_SIDE_PEN_COLOR";

    static inline const std::string P_TOP_THICKNESS = "P_TOP_THICKNESS";
    static inline const std::string P_TOP_BRUSH_COLOR = "P_TOP_BRUSH_COLOR";
    static inline const std::string P_TOP_PEN_WIDTH = "P_TOP_PEN_WIDTH";
    static inline const std::string P_TOP_PEN_COLOR = "P_TOP_PEN_COLOR";

    static inline const std::string P_HANDLE_RADIUS = "P_HANDLE_RADIUS";
    static inline const std::string P_HANDLE_BRUSH_COLOR = "P_HANDLE_BRUSH_COLOR";
    static inline const std::string P_HANDLE_PEN_WIDTH = "P_HANDLE_PEN_WIDTH";
    static inline const std::string P_HANDLE_PEN_COLOR = "P_HANDLE_PEN_COLOR";

    static inline const std::string P_ROUGHNESS_BRUSH_COLOR = "P_ROUGHNESS_BRUSH_COLOR";
    static inline const std::string P_ROUGHNESS_PEN_WIDTH = "P_ROUGHNESS_PEN_WIDTH";
    static inline const std::string P_ROUGHNESS_PEN_COLOR = "P_ROUGHNESS_PEN_COLOR";

    static inline const std::string P_R_HANDLE_RADIUS = "P_R_HANDLE_RADIUS";
    static inline const std::string P_R_HANDLE_BRUSH_COLOR = "P_R_HANDLE_BRUSH_COLOR";
    static inline const std::string P_R_HANDLE_PEN_WIDTH = "P_R_HANDLE_PEN_WIDTH";
    static inline const std::string P_R_HANDLE_PEN_COLOR = "P_R_HANDLE_PEN_COLOR";

    LayerElementItem();
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_SLDEDITOR_LAYERELEMENTITEM_H
