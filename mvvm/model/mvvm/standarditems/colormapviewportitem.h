//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/model/mvvm/standarditems/colormapviewportitem.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H
#define BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H

#include "mvvm/standarditems/viewportitem.h"

namespace ModelView {

class Data2DItem;

//! Container with viewport and collection of ColorMapItem's to plot.

class MVVM_MODEL_EXPORT ColorMapViewportItem : public ViewportItem {
public:
    static inline const std::string P_ZAXIS = "P_ZAXIS";

    ColorMapViewportItem();

    ViewportAxisItem* zAxis() const;

    using ViewportItem::setViewportToContent;
    void setViewportToContent() override;

protected:
    virtual std::pair<double, double> data_xaxis_range() const override;
    virtual std::pair<double, double> data_yaxis_range() const override;

private:
    Data2DItem* data_item() const;
    void update_data_range();
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_MODEL_MVVM_STANDARDITEMS_COLORMAPVIEWPORTITEM_H
