#include "SampleEditor.h"
#include "DesignerScene.h"
#include "DesignerView.h"

SampleEditor::SampleEditor(QWidget *parent)
    : ISampleEditor(parent)
    , m_designerScene(0)
    , m_designerView(0)
    , m_editorStack(0)
{
    m_designerScene = new DesignerScene(parent);
    m_designerView = new DesignerView(parent, m_designerScene);
    m_editorStack = new QStackedWidget(parent);
    m_editorStack->addWidget(m_designerView);
}
