//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/scientificdoubleeditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_SCIENTIFICDOUBLEEDITOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_SCIENTIFICDOUBLEEDITOR_H

#include "mvvm/editors/customeditor.h"

class QLineEdit;
class QDoubleValidator;

namespace ModelView {

//! Custom editor for QVariant based on double with scientific notation support.

class MVVM_VIEWMODEL_EXPORT ScientificDoubleEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit ScientificDoubleEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QLineEdit* m_lineEdit;
    QDoubleValidator* m_validator{nullptr};
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_SCIENTIFICDOUBLEEDITOR_H
