// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboToolBar.h
//! @brief     Defines class ItemComboToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMCOMBOTOOLBAR_H
#define ITEMCOMBOTOOLBAR_H

#include "StyledToolBar.h"
#include <QList>

class QAction;
class QComboBox;

//! The ItemComboToolBar class is a styled toolbar on top of ItemComboWidget. Contains
//! ComboBox to switch ItemComboWidget, and dynamic list of actions, which are updated
//! according to current state of ItemComboWidget.

class BA_CORE_API_ ItemComboToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit ItemComboToolBar(QWidget* parent = 0);

    void setPresentation(const QString& name);

    void setPresentationList(const QStringList& presentationList,
                             const QStringList& activeList = QStringList());

    QString currentPresentation() const;

    void setActionList(const QList<QAction*>& actionList);

signals:
    void comboChanged(const QString& presentation);

private:
    void setComboConnected(bool value);
    void makeItemsEnabled(const QStringList& activePresentations);

    QComboBox* m_comboBox;
    QAction* m_comboBoxAction;
};

#endif // ITEMCOMBOTOOLBAR_H

