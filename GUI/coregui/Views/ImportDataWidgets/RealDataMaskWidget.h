// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataMaskWidget.h
//! @brief     Defines class RealDataMaskWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATAMASKWIDGET_H
#define REALDATAMASKWIDGET_H

#include "SessionItemWidget.h"

class SessionItem;
class MaskEditor;
class IntensityDataItem;
class QAction;
class MaskContainerItem;

//! The RealDataMaskWidget class provides mask editing for RealDataItem on ImportDataView.

class BA_CORE_API_ RealDataMaskWidget : public NewSessionItemWidget
{
    Q_OBJECT

public:
    RealDataMaskWidget(QWidget* parent = 0);

    void setItem(SessionItem* realDataItem);

    QList<QAction*> actionList();

private:
    IntensityDataItem* intensityDataItem();
    MaskContainerItem* createMaskContainer(IntensityDataItem* intensityData);

    MaskEditor* m_maskEditor;
};

#endif // REALDATAMASKWIDGET_H

