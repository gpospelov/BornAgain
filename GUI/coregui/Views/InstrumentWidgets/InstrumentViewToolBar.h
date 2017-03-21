// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentViewToolBar.h
//! @brief     Defines class InstrumentViewToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTVIEWTOOLBAR_H
#define INSTRUMENTVIEWTOOLBAR_H

#include "StyledToolBar.h"
#include <QList>

class QAction;
class QToolButton;
class InstrumentViewActions;

//! Styled tool bar on top of InstrumentView with add/remove/clone instrument buttons.

class BA_CORE_API_ InstrumentViewToolBar : public StyledToolBar
{
    Q_OBJECT

public:
    explicit InstrumentViewToolBar(InstrumentViewActions* actions, QWidget* parent = 0);

private:
    QToolButton* m_addInstrumentButton;
    QToolButton* m_removeInstrumentButton;
};

#endif // INSTRUMENTVIEWTOOLBAR_H

