// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleViewComponents.h
//! @brief     Defines class SampleViewComponents
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEVIEWCOMPONENTS_H
#define SAMPLEVIEWCOMPONENTS_H

#include <QWidget>
#include "ItemTreeView.h"
#include "widgetbox.h"

//#include "SamplePropertyEditor.h"
#include "SampleWidgetBox.h"
#include "SampleModel.h"

#include <QSortFilterProxyModel>


//class BA_CORE_API_ SampleInfoStreamInterface : public QWidget
//{
//public:
//    explicit SampleInfoStreamInterface(QWidget *parent = 0) : QWidget(parent)
//    {
//        setMinimumSize(128, 128);
//        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    }
//};



class BA_CORE_API_ SampleViewComponents
{
public:
    static SampleWidgetBox *createWidgetBox(
            SampleDesignerInterface *core, QWidget *parent);
//    static SamplePropertyEditor *createPropertyEditor(
//            QItemSelectionModel *selection_model, QWidget *parent);
    static ItemTreeView *createTreeView(
            SampleModel *sample_model, QWidget *parent);
//    static SampleInfoStreamInterface *createInfoStream(QWidget *parent);
};

#endif // SAMPLEVIEWCOMPONENTS_H
