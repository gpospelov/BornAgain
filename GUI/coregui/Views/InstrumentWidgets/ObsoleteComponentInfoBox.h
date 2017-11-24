// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/ObsoleteComponentInfoBox.h
//! @brief     Defines class ObsoleteComponentInfoBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETECOMPONENTINFOBOX_H
#define OBSOLETECOMPONENTINFOBOX_H

#include "GroupInfoBox.h"
#include "WinDllMacros.h"
#include <QWidget>

class ObsoleteComponentBoxEditor;
class SessionItem;

//! The ComponentEditorBox is a widget to display ComponentEditor inside
//! custom group box equipped with help sign functionality
//! (used to summon DistributionEditor)

class BA_CORE_API_ ObsoleteComponentInfoBox : public QWidget
{
    Q_OBJECT
public:
    ObsoleteComponentInfoBox(const QString& title, QWidget* parent = 0);

    void addPropertyItems(SessionItem* item);

    void clearEditor();

signals:
    void onDialogRequest(SessionItem* item, const QString& names);

private slots:
    void dialogRequest();

private:
    GroupInfoBox* m_groupBox;
    ObsoleteComponentBoxEditor* m_editor;
    SessionItem* m_item;
    QString m_title;
};

#endif // OBSOLETECOMPONENTINFOBOX_H
