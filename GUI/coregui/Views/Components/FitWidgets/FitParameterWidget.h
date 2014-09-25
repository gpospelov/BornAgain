#ifndef FITPARAMETERWIDGET_H
#define FITPARAMETERWIDGET_H

#include <QWidget>
#include <QTreeView>
#include <QAction>
#include <QTableWidget>

#include "FitModel.h"



class BA_CORE_API_ FitParameterWidget : public QWidget
{
    Q_OBJECT

public:
    FitParameterWidget(FitModel *fitModel, QWidget *parent = 0);

private:
    FitModel *m_fitModel;


    void createParameterModel();
};

#endif
