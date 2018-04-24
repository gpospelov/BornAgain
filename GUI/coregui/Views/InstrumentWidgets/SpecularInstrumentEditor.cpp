#include "SpecularInstrumentEditor.h"
#include "SpecularBeamEditor.h"
#include "EnvironmentEditor.h"
#include "PolarizationAnalysisEditor.h"
#include "InstrumentItems.h"
#include "detailswidget.h"
#include "ColumnResizer.h"
#include <QVBoxLayout>

SpecularInstrumentEditor::SpecularInstrumentEditor(QWidget* parent)
    : SessionItemWidget(parent)
    , m_columnResizer(new ColumnResizer(this))
    , m_beamEditor(new SpecularBeamEditor(m_columnResizer))
    , m_environmentEditor(new EnvironmentEditor(m_columnResizer))
    , m_polarizationAnalysisEditor(nullptr)
{
    auto mainLayout = new QVBoxLayout;

    addEditor(mainLayout, m_beamEditor, "Beam parameters");
//    addEditor(mainLayout, m_polarizationAnalysisEditor, "Polarization analysis", /*expanded*/false);
    addEditor(mainLayout, m_environmentEditor, "Environment", /*expanded*/false);

    mainLayout->addStretch();

    setLayout(mainLayout);
}

void SpecularInstrumentEditor::subscribeToItem()
{
    m_beamEditor->setItem(instrumentItem());
    m_environmentEditor->setItem(instrumentItem());
//    m_polarizationAnalysisEditor->setItem(instrumentItem());
}

void SpecularInstrumentEditor::addEditor(QVBoxLayout* layout, QWidget* widget, const QString& name,
                                         bool expanded)
{
    auto detailsWidget = new Utils::DetailsWidget;
    detailsWidget->setSummaryText(name);
    detailsWidget->setSummaryFontBold(true);
    detailsWidget->setWidget(widget);
    if (expanded)
        detailsWidget->setState(Utils::DetailsWidget::Expanded);
    layout->addWidget(detailsWidget);
}

SpecularInstrumentItem* SpecularInstrumentEditor::instrumentItem()
{
    auto result = dynamic_cast<SpecularInstrumentItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}

