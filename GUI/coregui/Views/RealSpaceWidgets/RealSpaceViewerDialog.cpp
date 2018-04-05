
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
    const QSize minimum_dialog_size(400, 250);
    const QSize default_dialog_size(500, 400);
}

RealSpaceViewerDialog::RealSpaceViewerDialog(SampleModel *sampleModel,
                                             QItemSelectionModel* selectionModel, QWidget *parent)
    : QDialog(parent)
    , m_sampleModel(sampleModel)
    , m_selectionModel(selectionModel)
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
    RealSpaceWidget* widget = new RealSpaceWidget(m_sampleModel, m_selectionModel);
    widget->setModel(m_sampleModel, m_selectionModel);
    layout->addWidget(widget);
    #endif

    setLayout(layout);
    setAttribute(Qt::WA_DeleteOnClose, true);
    StyleUtils::setResizable(this);
}
