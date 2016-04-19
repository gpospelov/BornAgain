// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.h
//! @brief     Declares class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QWidget>

class MainWindow;
class QTabWidget;
class QAbstractItemModel;

class TestView : public QWidget
{
    Q_OBJECT
public:
    TestView(MainWindow *mainWindow = 0);

private:
    void test_MaskEditor();
    void test_AccordionWidget();
    void test_RunFitWidget();
    MainWindow *m_mainWindow;
    void addModelToTabs(QTabWidget *tabs, QAbstractItemModel *model);
    void test_sessionModel();
    void test_MaterialEditor();
};


#include "SessionModel.h"
#include <QObject>
#include <QIdentityProxyModel>
#include <QModelIndex>

class TestProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    TestProxyModel(QObject *parent = 0);
    void setSourceModel(QAbstractItemModel *source);
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex& child) const;
    int rowCount(const QModelIndex& parent) const;
private:
    SessionModel *m_source;
};

#endif
