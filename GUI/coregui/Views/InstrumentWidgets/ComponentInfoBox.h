// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/ComponentInfoBox.h
//! @brief     Declares class ComponentInfoBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTINFOBOX_H
#define COMPONENTINFOBOX_H

#include "WinDllMacros.h"
#include "GroupInfoBox.h"
#include <QWidget>

class ComponentBoxEditor;
class SessionItem;

//! The ComponentEditorBox is a widget to display ComponentEditor inside
//! custom group box equipped with help sign functionality
//! (used to summon DistributionEditor)
class BA_CORE_API_ ComponentInfoBox : public QWidget
{
    Q_OBJECT
public:

    ComponentInfoBox(const QString &title, QWidget *parent = 0);

    void addPropertyItems(SessionItem *item);

    void clearEditor();

signals:
    void onDialogRequest(SessionItem *item, QString names);

private slots:
    void dialogRequest();

private:
    GroupInfoBox *m_groupBox;
    ComponentBoxEditor *m_editor;
    SessionItem *m_item;
    QString m_title;
};

#endif // COMPONENTINFOBOX_H
