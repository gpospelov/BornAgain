//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/viewmodel/mvvm/editors/coloreditor.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_COLOREDITOR_H
#define BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_COLOREDITOR_H

#include "mvvm/editors/customeditor.h"

class QLabel;

namespace ModelView {

class LostFocusFilter;

//! Custom editor for QVariant based on QColor.

class MVVM_VIEWMODEL_EXPORT ColorEditor : public CustomEditor {
    Q_OBJECT

public:
    explicit ColorEditor(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QColor currentColor() const;

    void update_components() override;
    QLabel* m_textLabel{nullptr};
    QLabel* m_pixmapLabel{nullptr};
    LostFocusFilter* m_focusFilter;
};

} // namespace ModelView

#endif // BORNAGAIN_MVVM_VIEWMODEL_MVVM_EDITORS_COLOREDITOR_H
