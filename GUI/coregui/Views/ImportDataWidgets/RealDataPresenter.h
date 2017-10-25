// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataPresenter.h
//! @brief     Defines class RealDataPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATAPRESENTER_H
#define REALDATAPRESENTER_H

#include "ItemComboWidget.h"

class RealDataMaskWidget;
class QAction;

//! Presents imported data (RealDataItem) using stack of different widgets and combo box in the
//! right top corner of ImportDataView, to switch between widgets.

class BA_CORE_API_ RealDataPresenter : public ItemComboWidget
{
    Q_OBJECT
public:
    explicit RealDataPresenter(QWidget* parent = nullptr);

    QList<QAction*> actionList();

protected:
    QStringList activePresentationList(SessionItem*);

};

#endif  // REALDATAPRESENTER_H
