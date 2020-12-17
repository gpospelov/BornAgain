//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/axistitlecontroller.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_AXISTITLECONTROLLER_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_AXISTITLECONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCPAxis;

namespace ModelView {

class TextItem;

//! Propagates title settings from TextItem to QCPAxis.

class MVVM_VIEW_EXPORT AxisTitleController : public ItemListener<TextItem> {
public:
    explicit AxisTitleController(QCPAxis* axis);
    ~AxisTitleController() override;

protected:
    void subscribe() override;

public:
    struct AxisTitleControllerImpl;
    std::unique_ptr<AxisTitleControllerImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_AXISTITLECONTROLLER_H
