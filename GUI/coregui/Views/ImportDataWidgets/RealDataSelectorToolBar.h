// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorToolBar.h
//! @brief     Defines class RealDataSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATASELECTORTOOLBAR_H
#define REALDATASELECTORTOOLBAR_H

#include "StyledToolBar.h"

class RealDataSelectorActions;
class QToolButton;

//! The RealDataSelectorToolBar class represents a narrow toolbar on top of
//! RealDataSelectorWidget (ImportDataView)

class BA_CORE_API_ RealDataSelectorToolBar : public StyledToolBar
{
    Q_OBJECT
public:
    RealDataSelectorToolBar(RealDataSelectorActions* actions, QWidget* parent = 0);

private:
    QToolButton* m_importDataButton;
    QToolButton* m_removeDataButton;
};

#endif // REALDATASELECTORTOOLBAR_H
