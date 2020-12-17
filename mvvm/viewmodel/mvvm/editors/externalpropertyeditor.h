//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/externalpropertyeditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_EXTERNALPROPERTYEDITOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_EXTERNALPROPERTYEDITOR_H

#include "mvvm/editors/customeditor.h"
#include <functional>

class QLabel;

namespace ModelView {

class LostFocusFilter;

//! Custom editor for QVariant based on ExternalProperty.
//! Contains icon, label and button to call external dialog via callback mechanism.

class MVVM_VIEWMODEL_EXPORT ExternalPropertyEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit ExternalPropertyEditor(QWidget* parent = nullptr);

    void setCallback(std::function<void(const QVariant&)> callback);

private slots:
    void buttonClicked();

private:
    void update_components() override;
    QLabel* m_textLabel;
    QLabel* m_pixmapLabel;
    LostFocusFilter* m_focusFilter;
    std::function<void(const QVariant&)> m_callback; //! actions to take on clicked button
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_EXTERNALPROPERTYEDITOR_H
