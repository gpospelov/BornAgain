//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/booleditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_BOOLEDITOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_BOOLEDITOR_H

#include "mvvm/editors/customeditor.h"

class QCheckBox;

namespace ModelView {

//! Custom editor for QVariant based on bool values.

class MVVM_VIEWMODEL_EXPORT BoolEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit BoolEditor(QWidget* parent = nullptr);

    bool is_persistent() const override;

private slots:
    void onCheckBoxChange(bool value);

private:
    void update_components() override;
    QCheckBox* m_checkBox;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_BOOLEDITOR_H
