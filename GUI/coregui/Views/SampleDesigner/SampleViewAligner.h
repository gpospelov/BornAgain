// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewAligner.h
//! @brief     Declares class SampleViewAligner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEVIEWALIGNER_H
#define SAMPLEVIEWALIGNER_H

#include <QMap>
#include <QModelIndex>
#include <QPointF>
#include "WinDllMacros.h"
class DesignerScene;
class IView;
class SessionItem;


//! Makes alignment of sample droped on graphics scene.
//! Implements additional algorithm for smart alignment.
class BA_CORE_API_ SampleViewAligner
{
public:
    SampleViewAligner(DesignerScene *scene);

    void alignSample(SessionItem *item, QPointF reference = QPointF(), bool force_alignment = false);
    void alignSample(const QModelIndex & parentIndex, QPointF reference = QPointF(), bool force_alignment = false);

    void smartAlign();
    void updateViews(const QModelIndex & parentIndex = QModelIndex());
    void updateForces();
    void calculateForces(IView *view);
    void advance();

private:
    IView *getViewForIndex(const QModelIndex &index);
    QList<IView *> getConnectedViews(IView *view);

    DesignerScene *m_scene;
    QList<IView *> m_views; //!< list of all views which are subject to smart align
    QMap<IView *, QPointF> m_viewToPos;
};


#endif // SAMPLEVIEWALIGNER_H

