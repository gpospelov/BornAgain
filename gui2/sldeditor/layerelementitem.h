// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_LAYERELEMENTITEM_H
#define DAREFL_SLDEDITOR_LAYERELEMENTITEM_H

#include "darefl_export.h"
#include "mvvm/model/compounditem.h"
#include "mvvm/model/sessionmodel.h"

namespace DaRefl {

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

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_LAYERELEMENTITEM_H
