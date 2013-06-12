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


MaterialProperty MaterialBrowser::getMaterialProperty()
{
    Q_ASSERT(instance());
    return instance()->this_getSelectedMaterialProperty();
}


MaterialProperty MaterialBrowser::getDefaultMaterialProperty()
{
    Q_ASSERT(instance());
    return instance()->this_getDefaultMaterialProperty();
}


void MaterialBrowser::BrowserViewCall(Qt::WindowModality modality)
{
    Q_ASSERT(instance());
    return instance()->this_BrowserViewCall(modality);
}



void MaterialBrowser::this_BrowserViewCall(Qt::WindowModality modality)
{
    m_browserModel->resetSelection();
    if( !m_browserView ) {
        std::cout << "MaterialBrowser::BroswerViewCall() -> new " << std::endl;
        m_browserView = new MaterialBrowserView(m_browserModel, m_parent);
        connect(m_browserView, SIGNAL(destroyed()), this, SLOT(BrowserViewOnDeleteEvent()));
    }
    if(modality == Qt::NonModal) {
        std::cout << "MaterialBrowser::BroswerViewCall() -> show " << std::endl;
        m_browserView->show();
        m_browserView->raise();
        std::cout << "MaterialBrowser::BroswerViewCall() -> show done " << std::endl;
    } else {
        std::cout << "MaterialBrowser::BroswerViewCall() -> exec " << std::endl;
        //        if(m_browserView->exec() == QDialog::Accepted) return;
        m_browserView->exec();
        std::cout << "MaterialBrowser::BroswerViewCall() -> exec done" << std::endl;
    }
}


// delete MaterialBrowserView if it was closed by the user
void MaterialBrowser::BrowserViewOnDeleteEvent()
{
    std::cout << "MaterialBrowser::BrowserViewOnCloseEvent() -> XXX" << std::endl;
    m_browserView = 0;
}


MaterialProperty MaterialBrowser::this_getSelectedMaterialProperty()
{
    BrowserViewCall(Qt::WindowModal);
    return m_browserModel->getSelectedMaterialProperty();
}


MaterialProperty MaterialBrowser::this_getDefaultMaterialProperty()
{
    return m_browserModel->getDefaultMaterialProperty();
}



