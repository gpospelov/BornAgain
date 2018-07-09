#ifndef FITCOMPARISONVIEWCONTROLLER_H
#define FITCOMPARISONVIEWCONTROLLER_H

#include "WinDllMacros.h"
#include <QObject>

class DataItem;
class DataItem1DView;
class JobItem;
class PropertyRepeater;
class SessionModel;

class BA_CORE_API_ DiffItemController : public QObject
{
public:
    DiffItemController(const QString& data_type, QObject* parent);
    ~DiffItemController() override;
    SessionModel* model() {return m_private_model;}
    void setJobItem(JobItem* job_item);
    JobItem* jobItem() {return m_current_item;}
    void updateDiffData();
    DataItem* diffItem() {return m_diff_item;}
    void subscribe();
    void unsubscribe();
private:
    JobItem* m_current_item;
    SessionModel* m_private_model;
    DataItem* m_diff_item;
};

class BA_CORE_API_ FitComparison1DViewController : public QObject
{
public:
    explicit FitComparison1DViewController(QObject* parent);

    DataItem1DView* diffItemView();

    void setItem(JobItem* job_item);
    void updateDiffData();
    void resetDiffView();

    void clear();

private:
    DiffItemController* m_diff_item_controller;
    DataItem1DView* m_diff_view_item;
    PropertyRepeater* m_appearanceRepeater;
    PropertyRepeater* m_xAxisRepeater;
};

#endif // FITCOMPARISONVIEWCONTROLLER_H
