#include "MaterialBrowser.h"
#include "MaterialBrowserView.h"
#include "MaterialBrowserModel.h"
#include "MaterialManager.h"
#include <iostream>

MaterialBrowser *MaterialBrowser::m_instance = 0;


MaterialBrowser::MaterialBrowser(QWidget *parent)
    : m_parent(parent)
    , m_browserView(0)
    , m_browserModel(0)
{
    Q_ASSERT(!m_instance);
    m_instance = this;

    // adding few default materials
    MaterialManager::getHomogeneousMaterial("Air", 1., 0.);
    MaterialManager::getHomogeneousMaterial("Substrate", 1-6e-6, 2e-8);
    MaterialManager::getHomogeneousMaterial("Default", 1., 0.);

    m_browserModel = new MaterialBrowserModel(0);

}


MaterialBrowser::~MaterialBrowser()
{
    m_instance = 0;
}


MaterialBrowser *MaterialBrowser::instance()
{
    return m_instance;
}


// create new MaterialBrowserView or raise old one if exists
void MaterialBrowser::BrowserViewCall(bool isModal)
{
    std::cout << "MaterialBrowser::BrowserViewCall()" << std::endl;
    if( !m_browserView ) {
        std::cout << " MaterialBrowser::BrowserViewCall() " << m_parent << std::endl;
        m_browserModel->resetSelection();
        m_browserView = new MaterialBrowserView(m_browserModel, m_parent);
//        NonModal,
//        WindowModal,
//        ApplicationModal

        connect( m_browserView, SIGNAL(WindowClosed()), this, SLOT(BrowserViewOnCloseEvent()) );
        //m_browserView->setWindowModality(Qt::ApplicationModal);
        m_browserView->setModal(isModal);
        m_browserView->show();
    } else {
        m_browserView->raise();
    }
}


// delete MaterialBrowserView if it was closed by the user
void MaterialBrowser::BrowserViewOnCloseEvent()
{
    std::cout << "MaterialBrowser::BrowserViewOnCloseEvent()" << std::endl;
    delete m_browserView;
    m_browserView = 0;
}


MaterialProperty MaterialBrowser::this_getSelectedMaterialProperty()
{
    std::cout << "MaterialBrowser::this_getMaterialProperty()-> " << std::endl;
    BrowserViewCall(true);
    Q_ASSERT(m_browserModel->hasSelection());
    return m_browserModel->getSelectedMaterialProperty();
}
