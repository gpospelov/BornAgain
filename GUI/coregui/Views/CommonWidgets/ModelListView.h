// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ModelListView.h
//! @brief     Defines class ModelListView.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MODELLISTVIEW_H
#define MODELLISTVIEW_H

#include "WinDllMacros.h"
#include <QWidget>

class QListView;
class SessionModel;
class SessionDecorationModel;

//! Equivalent of QListView for SessionModel allowing to add visual decorations to the list.

class BA_CORE_API_ ModelListView : public QWidget
{
    Q_OBJECT
public:
    ModelListView(QWidget* parent, SessionModel* model);

private:
    QListView* m_listView;
    SessionDecorationModel* m_decorationProxy;
};


#endif  // MODELLISTVIEW_H
