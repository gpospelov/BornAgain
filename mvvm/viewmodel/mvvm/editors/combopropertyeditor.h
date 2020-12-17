//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/combopropertyeditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_COMBOPROPERTYEDITOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_COMBOPROPERTYEDITOR_H

#include "mvvm/editors/customeditor.h"

class QComboBox;

namespace ModelView {

//! Custom editor for QVariant based on ComboProperty.

class MVVM_VIEWMODEL_EXPORT ComboPropertyEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit ComboPropertyEditor(QWidget* parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    bool is_persistent() const override;

protected slots:
    virtual void onIndexChanged(int index);

private:
    std::vector<std::string> internLabels();
    int internIndex();
    void setConnected(bool isConnected);
    void update_components() override;
    QComboBox* m_box;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_COMBOPROPERTYEDITOR_H
