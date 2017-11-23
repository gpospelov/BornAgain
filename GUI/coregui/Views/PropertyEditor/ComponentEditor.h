// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentEditor.h
//! @brief     Defines ComponentEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTEDITOR_H
#define COMPONENTEDITOR_H

#include "WinDllMacros.h"
#include <QWidget>

class ComponentView;
class SessionItem;
class QBoxLayout;

//! Component editor for SessionItem. Can have various appearance depending
//! on EditorFlags

class BA_CORE_API_ ComponentEditor : public QWidget
{
    Q_OBJECT
public:
    enum EditorFlags {
        Tree      = 0x1000,
        Widget    = 0x2000,

        PlainLayout  = 0x0010,
        GroupLayout  = 0x0020,
        InfoLayout   = 0x0040,

        T_Header     = 0x0100,
        T_Root       = 0x0200,

        FullTree     = Tree | PlainLayout | T_Header | T_Root,
        HeaderTree   = Tree | PlainLayout | T_Header,
        MiniTree     = Tree | PlainLayout,
        PlainWidget  = Widget | PlainLayout,
        GroupWidget  = Widget | GroupLayout,
        InfoWidget   = Widget | InfoLayout,
    };
    Q_DECLARE_FLAGS(EditorType, EditorFlags)

    ComponentEditor(EditorType editorType = HeaderTree);

    void setItem(SessionItem* item);
    void clearEditor();

private:
    ComponentView* createComponentView();

    EditorType m_type;
    ComponentView* m_componentView;
};

#endif  // COMPONENTEDITOR_H
