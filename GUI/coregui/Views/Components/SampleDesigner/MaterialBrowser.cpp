#include "MaterialBrowser.h"
#include "MaterialBrowserView.h"
#include "MaterialManager.h"
#include <iostream>

MaterialBrowser *MaterialBrowser::m_instance = 0;


MaterialBrowser::MaterialBrowser(QWidget *parent)
    : m_parent(parent)
    , m_browserView(0)
{
    Q_ASSERT(!m_instance);
    m_instance = this;

    // adding few default materials
    MaterialManager::getHomogeneousMaterial("Air", 1., 0.);
    MaterialManager::getHomogeneousMaterial("Substrate", 1-6e-6, 2e-8);
    MaterialManager::getHomogeneousMaterial("Default", 1., 0.);
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
void MaterialBrowser::BrowserViewCall()
{
    std::cout << "MaterialBrowser::BrowserViewCall()" << std::endl;
    if( !m_browserView ) {
        std::cout << " MaterialBrowser::BrowserViewCall() " << m_parent << std::endl;
        m_browserView = new MaterialBrowserView(m_parent);
        connect( m_browserView, SIGNAL(WindowClosed()), this, SLOT(BrowserViewOnCloseEvent()) );
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
