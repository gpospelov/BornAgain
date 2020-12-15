// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_SLDEDITOR_SLDEDITORACTIONS_H
#define DAREFL_SLDEDITOR_SLDEDITORACTIONS_H

#include <QObject>
#include <darefl/darefl_export.h>
#include <memory>

namespace DaRefl
{

class SLDElementModel;

//! Handles user actions applied to SLDEditor.
//! Belongs to SLDEditor.

class DAREFLCORE_EXPORT SLDEditorActions : public QObject
{
    Q_OBJECT

public:
    SLDEditorActions(QObject* parent = nullptr);
    ~SLDEditorActions();

    void setModel(SLDElementModel* model);

private:
    struct SLDEditorActionsImpl;
    std::unique_ptr<SLDEditorActionsImpl> p_impl;
};

} // namespace DaRefl

#endif // DAREFL_SLDEDITOR_SLDEDITORACTIONS_H
