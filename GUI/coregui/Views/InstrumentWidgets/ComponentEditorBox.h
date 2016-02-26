// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/ComponentEditorBox.h
//! @brief     Defines class ComponentEditorBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTEDITORBOX_H
#define COMPONENTEDITORBOX_H

#include "WinDllMacros.h"
#include "GroupInfoBox.h"
#include <QWidget>

class ComponentEditor;
class ParameterizedItem;

//! The ComponentEditorBox is a widget to display ComponentEditor inside
//! custom group box equipped with help sign functionality
//! (used to summon DistributionEditor)
class BA_CORE_API_ ComponentEditorBox : public QWidget
{
    Q_OBJECT
public:

    ComponentEditorBox(const QString &title, QWidget *parent = 0);
    ComponentEditor *getEditor();

    void setItem(ParameterizedItem *item);

    void clearEditor();

signals:
    void onDialogRequest(ParameterizedItem *item, QString names);

private slots:
    void dialogRequest();

private:
    GroupInfoBox *m_groupBox;
    ComponentEditor *m_editor;
    ParameterizedItem *m_item;
    QString m_title;
};

#endif
