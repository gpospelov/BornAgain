#include "welcomemode.h"
#include "WelcomeView.h"

WelcomeMode::WelcomeMode()
{
    m_welcomeManager = new WelcomeManager();
    setObjectName(QLatin1String("WelcomeMode"));
    setDisplayName(tr("Welcome"));
    setIcon(QIcon(QLatin1String(":/fancyactionbar/images/mode_Edit.png")));

}


WelcomeMode::~WelcomeMode()
{
    // Make sure the editor manager does not get deleted
    m_welcomeManager->setParent(0);
}
