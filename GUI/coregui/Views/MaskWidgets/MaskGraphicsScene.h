// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskGraphicsScene.h
//! @brief     Defines class MaskGraphicsScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKGRAPHICSSCENE_H
#define MASKGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QModelIndex>
#include <QMap>

class SessionModel;
class ParameterizedItem;
class IMaskView;

//! Graphics scene for MaskEditorCanvas

class MaskGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MaskGraphicsScene(QObject *parent = 0);

    void setModel(SessionModel *model);

private:
    void resetScene();
    void updateScene();
    void updateViews(const QModelIndex &parentIndex = QModelIndex());
    IMaskView* addViewForItem(ParameterizedItem *item);

    SessionModel *m_model;
    QMap<ParameterizedItem *, IMaskView *> m_ItemToView;
};


#endif
