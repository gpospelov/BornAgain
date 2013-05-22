#ifndef SAMPLEEDITOR_H
#define SAMPLEEDITOR_H

#include <QObject>
#include <QStackedWidget>

class DesignerScene;
class DesignerView;
class SamplePropertyEditor;

//- -------------------------------------------------------------------
//! @class ISampleEditor
//! @brief Interface for SampleEditor
//- -------------------------------------------------------------------
class SampleDesignerInterface : public QObject
{
    Q_OBJECT

public:
    SampleDesignerInterface(QObject *parent = 0) : QObject(parent){}
    virtual ~SampleDesignerInterface() { }

    virtual DesignerScene *getScene() const = 0;
    virtual DesignerView *getView() const = 0;

};


//- -------------------------------------------------------------------
//! @class SampleEditor
//! @brief Main class for editing sample
//- -------------------------------------------------------------------
class SampleDesigner: public SampleDesignerInterface
{
    Q_OBJECT
public:
    SampleDesigner(QWidget *parent = 0);
    virtual ~SampleDesigner(){}

    DesignerScene *getScene() const { return m_designerScene; }
    DesignerView *getView() const { return m_designerView; }

    QWidget *getCentralWidget() { return m_editorStack; }

    //void setPropertyEditor(const SamplePropertyEditor *property_editor) { m_property_editor = property_editor; }
private:
    DesignerScene *m_designerScene; //! scene which holds all objects
    DesignerView *m_designerView;   //! graphical representation of scene with object
    QStackedWidget *m_editorStack;    //! stack for varaiety of SampleEditorView
    //const SamplePropertyEditor *m_property_editor; //! widget to control ISampleView properties
};



#endif // SAMPLEEDITOR_H
