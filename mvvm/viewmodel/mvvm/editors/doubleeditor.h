//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/doubleeditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_DOUBLEEDITOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_DOUBLEEDITOR_H

#include "mvvm/editors/customeditor.h"

class QDoubleSpinBox;

namespace ModelView {

//! Custom editor for QVariant based on double with possibility to set limits.

class MVVM_VIEWMODEL_EXPORT DoubleEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit DoubleEditor(QWidget* parent = nullptr);

    void setRange(double minimum, double maximum);

    void setDecimals(int decimals);

    void setSingleStep(double value);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QDoubleSpinBox* m_doubleEditor;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_DOUBLEEDITOR_H
