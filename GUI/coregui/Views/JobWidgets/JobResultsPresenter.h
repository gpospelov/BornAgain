// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobResultsPresenter.h
//! @brief     Declares class JobResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBRESULTSPRESENTER_H
#define JOBRESULTSPRESENTER_H

#include "ItemComboWidget.h"

//! The JobResultsPresenter class is a widget which is able to present results of job (JobItem)
//! using stack of different widgets and combo box in the right top corner of JobView, to switch
//! between widgets.

//! For example, for JobItem with fitting abilities, it is possible to switch between
//! ColorMap plot and FitDataWidget.

class BA_CORE_API_ JobResultsPresenter : public ItemComboWidget
{
    Q_OBJECT
public:

        explicit JobResultsPresenter(QWidget *parent = 0);

};

#endif
