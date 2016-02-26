// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/AwesomePropertyPresenter.h
//! @brief     Defines class AwesomePropertyPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef AWESOMEPROPERTYPRESENTER_H
#define AWESOMEPROPERTYPRESENTER_H

#include "WinDllMacros.h"
#include <QWidget>
#include "GroupInfoBox.h"
#include "ParameterizedItem.h"

class AwesomePropertyEditor;
class QGroupBox;

//! The AwesomePropertyPresenter is a widget to display AwesomePropertyEditor inside
//! custom group box equipped with help sign functionality (used to summon DistributionEditor)
class BA_CORE_API_ AwesomePropertyPresenter : public QWidget
{
    Q_OBJECT
public:

    AwesomePropertyPresenter(const QString &title, QWidget *parent = 0);
    AwesomePropertyEditor *getEditor() { return m_editor; }

    void setItem(ParameterizedItem *item);

    void clearEditor();

signals:
    void onDialogRequest(ParameterizedItem *item, QString names);

private slots:
    void dialogRequest();

private:
    GroupInfoBox *m_groupBox;
    AwesomePropertyEditor *m_editor;
    ParameterizedItem *m_item;
    QString m_title;
};

#endif
