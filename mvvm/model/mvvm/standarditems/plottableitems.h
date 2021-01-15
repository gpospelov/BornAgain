//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/plottableitems.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_PLOTTABLEITEMS_H
#define BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_PLOTTABLEITEMS_H

//! @file mvvm/model/mvvm/standarditems/plottableitems.h
//! Collection of items to plot in QCustomPlot context.

#include "mvvm/model/compounditem.h"

namespace ModelView {

//! Represent text item on plot.

class MVVM_MODEL_EXPORT TextItem : public CompoundItem {
public:
    static inline const std::string P_TEXT = "P_TEXT";
    static inline const std::string P_FONT = "P_FONT";
    static inline const std::string P_SIZE = "P_SIZE";

    TextItem();
};

//! Represents basics settings of QPen.

class MVVM_MODEL_EXPORT PenItem : public CompoundItem {
public:
    static inline const std::string P_COLOR = "P_COLOR";
    static inline const std::string P_STYLE = "P_STYLE";
    static inline const std::string P_WIDTH = "P_WIDTH";

    PenItem();

    void setSelected(bool is_selected);

    std::string colorName() const;
    void setNamedColor(const std::string& named_color);
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_PLOTTABLEITEMS_H
