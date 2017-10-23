// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobResultsPresenter.h
//! @brief     Defines class JobResultsPresenter
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

//! Presents results of job (JobItem) using stack of different widgets and combo box in the
//! right top corner of JobView, to switch between widgets.

class BA_CORE_API_ JobResultsPresenter : public ItemComboWidget
{
    Q_OBJECT

public:
    explicit JobResultsPresenter(QWidget* parent = 0);

    void setPresentation(const QString& presentationType) override;

protected:
    QString itemPresentation() const override;
    QStringList activePresentationList(SessionItem* item) override;
    virtual QStringList presentationList(SessionItem* item) override;
};

#endif // JOBRESULTSPRESENTER_H
