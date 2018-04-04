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
    RealSpaceViewerDialog(SampleModel* sampleModel = nullptr,
                          QItemSelectionModel* selectionModel = nullptr,
                          QWidget *parent = nullptr);

private:
    SampleModel *m_sampleModel;
    QItemSelectionModel *m_selectionModel;
};


#endif // REALSPACEVIEWERDIALOG_H
