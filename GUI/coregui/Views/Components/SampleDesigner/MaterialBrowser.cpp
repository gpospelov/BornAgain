#include "MaterialBrowser.h"

MaterialBrowser *MaterialBrowser::m_instance = 0;

MaterialBrowser::MaterialBrowser(QWidget *parent)
{
    Q_ASSERT(!m_instance);
    m_instance = this;
}


MaterialBrowser::~MaterialBrowser()
{
    m_instance = 0;
}


MaterialBrowser *MaterialBrowser::instance()
{
    return m_instance;
}

