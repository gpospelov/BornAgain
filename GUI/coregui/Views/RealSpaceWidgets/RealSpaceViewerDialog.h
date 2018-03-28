#ifndef REALSPACEVIEWERDIALOG_H
#define REALSPACEVIEWERDIALOG_H

#include "WinDllMacros.h"
#include <QDialog>
#include <memory>
#include <SampleModel.h>
#include <QTreeView>

#include <QCloseEvent>

class MaterialModel;
class MaterialEditor;
class ExternalProperty;
class QBoxLayout;

//! Dialog to hold RealSpaceViewer.

class BA_CORE_API_ RealSpaceViewerDialog : public QDialog
{
    Q_OBJECT

public:
    RealSpaceViewerDialog(SampleModel* sampleModel, QTreeView* treeView, QWidget *parent = nullptr);

    void closeEvent(QCloseEvent* event);

signals:
    void dialogClosed();

private:
    SampleModel *m_sampleModel;
    QTreeView *m_treeView;
};


#endif // REALSPACEVIEWERDIALOG_H
