#include "SampleEditor.h"
#include "SampleEditorScene.h"
#include "SampleEditorView.h"

SampleEditor::SampleEditor(QWidget *parent)
    : ISampleEditor(parent)
    , m_editorScene(0)
    , m_editorView(0)
    , m_editorStack(0)
{
    m_editorScene = new SampleEditorScene(parent);
    m_editorView = new SampleEditorView(parent, m_editorScene);
    m_editorStack = new QStackedWidget(parent);
    m_editorStack->addWidget(m_editorView);
}
