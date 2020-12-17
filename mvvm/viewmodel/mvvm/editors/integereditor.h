//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/integereditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_INTEGEREDITOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_INTEGEREDITOR_H

#include "mvvm/editors/customeditor.h"

class QSpinBox;

namespace ModelView {

//! Custom editor for QVariant based on integer with possibility to set limits.

class MVVM_VIEWMODEL_EXPORT IntegerEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit IntegerEditor(QWidget* parent = nullptr);

    void setRange(int minimum, int maximum);

private slots:
    void onEditingFinished();

private:
    void update_components() override;
    QSpinBox* m_intEditor;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_INTEGEREDITOR_H
