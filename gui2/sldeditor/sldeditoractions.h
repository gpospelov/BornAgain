// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

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
