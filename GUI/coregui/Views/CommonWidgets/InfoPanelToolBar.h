// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/InfoPanelToolBar.h
//! @brief     Defines class InfoPanelToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INFOPANELTOOLBAR_H
#define INFOPANELTOOLBAR_H

#include "StyledToolBar.h"

class QToolButton;

//! The InfoPanelToolBar class represents a toolbar for InfoPanel

class BA_CORE_API_ InfoPanelToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit InfoPanelToolBar(QWidget *parent = 0);

signals:
    void expandButtonClicked();
    void closeButtonClicked();

public slots:
    void setExpandStatus(bool status);

protected slots:
    void onExpandButtonClicked();

private:
    QToolButton *m_expandButton;
    QToolButton *m_closeButton;
    bool m_expanded;
};


#endif // INFOPANELTOOLBAR_H
