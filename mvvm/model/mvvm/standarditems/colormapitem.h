//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/colormapitem.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_COLORMAPITEM_H
#define BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_COLORMAPITEM_H

#include "mvvm/model/compounditem.h"

namespace ModelView {

class Data2DItem;

//! Two-dimensional color map representation of Data2DItem.
//! Contains plot properties (i.e. color, gradient etc) and link to Data2DItem, which will provide
//! actual data to plot. ColorMapItem is intended for plotting only via ColorMapViewportItem.

class MVVM_MODEL_EXPORT ColorMapItem : public CompoundItem {
public:
    static inline const std::string P_LINK = "P_LINK";
    static inline const std::string P_TITLE = "P_TITLE";
    static inline const std::string P_GRADIENT = "P_GRADIENT";
    static inline const std::string P_INTERPOLATION = "P_INTERPOLATION";

    ColorMapItem();

    void setDataItem(const Data2DItem* item);

    Data2DItem* dataItem() const;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_COLORMAPITEM_H
