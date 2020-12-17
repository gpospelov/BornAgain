//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/scientificspinboxeditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_SCIENTIFICSPINBOXEDITOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_SCIENTIFICSPINBOXEDITOR_H

#include "mvvm/editors/customeditor.h"

namespace ModelView {

class ScientificSpinBox;

//! Custom editor for QVariant based on double with scientific notation support.

class MVVM_VIEWMODEL_EXPORT ScientificSpinBoxEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit ScientificSpinBoxEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);
    void setDecimals(int decimals);
    void setSingleStep(double step);

    bool is_persistent() const override;

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    ScientificSpinBox* m_doubleEditor;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_SCIENTIFICSPINBOXEDITOR_H
