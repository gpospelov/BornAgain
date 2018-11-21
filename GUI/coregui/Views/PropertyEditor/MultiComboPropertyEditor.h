// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/MultiComboPropertyEditor.h
//! @brief     Defines MultiComboPropertyEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTICOMBOPROPERTYEDITOR_H
#define MULTICOMBOPROPERTYEDITOR_H

#include "CustomEditors.h"

//! Provides custom editor for ComboProperty with multi-select option.

class BA_CORE_API_ MultiComboPropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    explicit MultiComboPropertyEditor(QWidget *parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected slots:
    virtual void onIndexChanged(int index);

protected:
    void initEditor();
    virtual QStringList internLabels();
    virtual int internIndex();
    void setConnected(bool isConnected);

    QComboBox* m_box;
    class WheelEventEater* m_wheel_event_filter;
};

#endif
