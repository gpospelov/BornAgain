#include "SampleEditor.h"
#include "DesignerScene.h"
#include "DesignerView.h"

SampleEditor::SampleEditor(QWidget *parent)
    : ISampleEditor(parent)
    , m_editorScene(0)
    , m_editorView(0)
    , m_editorStack(0)
{
    m_editorScene = new DesignerScene(parent);
    m_editorView = new DesignerView(parent, m_editorScene);
    m_editorStack = new QStackedWidget(parent);
    m_editorStack->addWidget(m_editorView);
}
