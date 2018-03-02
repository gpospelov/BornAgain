// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleViewComponents.h
//! @brief     Defines class SampleViewComponents
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLEVIEWCOMPONENTS_H
#define SAMPLEVIEWCOMPONENTS_H

#include "ItemTreeView.h"
#include "SampleModel.h"
#include "SampleWidgetBox.h"



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
