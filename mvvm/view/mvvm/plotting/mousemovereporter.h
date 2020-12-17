//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/view/mvvm/plotting/mousemovereporter.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_MOUSEMOVEREPORTER_H
#define BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_MOUSEMOVEREPORTER_H

#include "mvvm/view_export.h"
#include <functional>
#include <memory>

class QCustomPlot;

namespace ModelView {

struct MousePosInfo;

//! Tracks mouse moves in QCustomPlot canvas.
//! Notifies client about mouse moves and corresponding pointer coordinates expressed in axes units
//! at current zoom level.

class MVVM_VIEW_EXPORT MouseMoveReporter {
public:
    using callback_t = std::function<void(const MousePosInfo& pos_info)>;
    MouseMoveReporter(QCustomPlot* custom_plot, callback_t callback);
    ~MouseMoveReporter();

private:
    struct MouseMoveReporterImpl;
    std::unique_ptr<MouseMoveReporterImpl> p_impl;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEW_MVVM_PLOTTING_MOUSEMOVEREPORTER_H
