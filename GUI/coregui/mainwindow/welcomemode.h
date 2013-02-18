#ifndef WELCOMEMODE_H
#define WELCOMEMODE_H

#include "imode.h"
class WelcomeManager;

class WelcomeMode : public IMode
{
public:
    WelcomeMode();
    ~WelcomeMode();

private:
    WelcomeManager *m_welcomeManager;
};

#endif // WELCOMEMODE_H
