//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/sldeditor/sldeditoractions.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_SLDEDITOR_SLDEDITORACTIONS_H
#define BORNAGAIN_GUI2_SLDEDITOR_SLDEDITORACTIONS_H

#include "darefl_export.h"
#include <QObject>
#include <memory>

namespace gui2 {

class SLDElementModel;

//! Handles user actions applied to SLDEditor.
//! Belongs to SLDEditor.

class DAREFLCORE_EXPORT SLDEditorActions : public QObject {
    Q_OBJECT

public:
    SLDEditorActions(QObject* parent = nullptr);
    ~SLDEditorActions();

    void setModel(SLDElementModel* model);

private:
    struct SLDEditorActionsImpl;
    std::unique_ptr<SLDEditorActionsImpl> p_impl;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_SLDEDITOR_SLDEDITORACTIONS_H
