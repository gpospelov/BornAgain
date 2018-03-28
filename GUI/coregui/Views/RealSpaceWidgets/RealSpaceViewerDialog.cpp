
#include "RealSpaceViewerDialog.h"
#include "RealSpaceWidget.h"

#include "StyleUtils.h"
#include <QAction>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

#include <QApplication>

namespace
{
const QSize minimum_dialog_size(600, 400);
const QSize default_dialog_size(950, 600);
}

RealSpaceViewerDialog::RealSpaceViewerDialog(SampleModel *sampleModel, QTreeView *treeView,
                                             QWidget *parent)
    : QDialog(parent)
    , m_sampleModel(sampleModel)
    , m_treeView(treeView)
{
    setWindowTitle("Real Space Viewer");
    setMinimumSize(minimum_dialog_size);
    resize(default_dialog_size);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    //layout->setContentsMargins(0, 0, 0, 0);

    #ifdef BORNAGAIN_OPENGL
    RealSpaceWidget* widget = new RealSpaceWidget(m_sampleModel, m_treeView);
    widget->setModel(m_sampleModel, m_treeView);
    layout->addWidget(widget);
    #endif

    setLayout(layout);
    StyleUtils::setResizable(this);
}

void RealSpaceViewerDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit dialogClosed();
}


