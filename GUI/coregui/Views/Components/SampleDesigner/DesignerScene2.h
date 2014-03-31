#ifndef DESIGNERSCENE2_H
#define DESIGNERSCENE2_H


#include "DesignerScene.h"
#include <QModelIndex>
#include <QMap>

class SessionModel;
class ParameterizedItem;
class ParameterizedGraphicsItem;
class QItemSelectionModel;
class IView;
class QItemSelection;


class DesignerScene2 : public DesignerSceneInterface
{
    Q_OBJECT

public:
    explicit DesignerScene2(QObject *parent = 0);
    virtual ~DesignerScene2(){}

    void setSessionModel(SessionModel *model);
    void setSelectionModel(QItemSelectionModel *model);

    void update(const QModelIndex &parentIndex = QModelIndex());

public slots:
    void onSceneSelectionChanged();
    void onSessionSelectionChanged(const QItemSelection &, const QItemSelection &);

private:
    void addViewForItem(ParameterizedItem *item);

    SessionModel *m_sessionModel;
    QItemSelectionModel *m_selectionModel;
    bool m_block_selection;

    QMap<ParameterizedItem *, IView *> m_ItemToView;
};


#endif

