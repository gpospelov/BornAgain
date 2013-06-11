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
//        m_browserView->show();
        //m_browserView->hide();
        //m_browserView->exec();
        //m_browserView->setWindowModality(Qt::ApplicationModal);
        m_browserView->exec();
//        if(m_browserView->exec() == QDialog::Accepted) return;

        std::cout << "MaterialBrowser::BroswerViewCall() -> exec done" << std::endl;
    }
}


// create new MaterialBrowserView or raise old one if exists
//void MaterialBrowser::BrowserViewCall(bool isModal)
//{
//    m_browserModel->resetSelection();
//    if( !m_browserView ) {
//        // create new MaterialBrowserView
//        m_browserView = new MaterialBrowserView(m_browserModel, m_parent);
////        connect( m_browserView, SIGNAL(WindowClosed()), this, SLOT(BrowserViewOnCloseEvent()) );
//        connect(m_browserView, SIGNAL(destroyed()), this, SLOT(BrowserViewOnCloseEvent()));
//        if(isModal) {
//            m_browserView->show();
//        } else {
////            if(m_browserView->exec() == QDialog::Accepted) return;
//            //if(m_browserView->exec() == QDialog::Accepted) return;
//            m_browserView->exec();
//        }
//    } else {
//        // raise existing MaterialBrowserView
//        std::cout << "MaterialBrowser::BrowserViewCall() -> isModal " << isModal << std::endl;
//        if(isModal) {
//            std::cout << "MaterialBrowser::BrowserViewCall() -> show, raise "  << std::endl;
//            m_browserView->show();
//            m_browserView->raise();
//        } else {
//            std::cout << "MaterialBrowser::BrowserViewCall() -> show, hide, exec "  << std::endl;
//            m_browserView->exec();
////            m_browserView->show();
////            m_browserView->hide(); // necessary to swtich modal mode
////            if(m_browserView->exec() == QDialog::Accepted) return;
//            std::cout << "MaterialBrowser::BrowserViewCall() -> show, hide, exec 1.1"  << std::endl;
//            //m_browserView->setModal(false);
//            std::cout << "MaterialBrowser::BrowserViewCall() -> show, hide, exec 1.2"  << std::endl;
//            //m_browserView->show();
//            std::cout << "MaterialBrowser::BrowserViewCall() -> show, hide, exec 1.3"  << std::endl;
//            //m_browserView->setModal(true);
//            std::cout << "MaterialBrowser::BrowserViewCall() -> show, hide, exec 1.4"  << std::endl;
//        }
//    }
//}


// delete MaterialBrowserView if it was closed by the user
void MaterialBrowser::BrowserViewOnDeleteEvent()
{
    std::cout << "MaterialBrowser::BrowserViewOnCloseEvent() -> XXX" << std::endl;
    m_browserView = 0;
}


MaterialProperty MaterialBrowser::this_getSelectedMaterialProperty()
{
    std::cout << "MaterialBrowser::this_getSelectedMaterialProperty() -> 1.1" << std::endl;
    BrowserViewCall(Qt::WindowModal);
    std::cout << "MaterialBrowser::this_getSelectedMaterialProperty() -> 1.3" << std::endl;
    //Q_ASSERT(m_browserModel->hasSelection());
    return m_browserModel->getSelectedMaterialProperty();
}



