#ifndef WELCOMEMODE_H
#define WELCOMEMODE_H

#include "imode.h"
class WelcomeView;

class WelcomeMode : public IMode
{
public:
    WelcomeMode();
    ~WelcomeMode();

private:
    WelcomeView *m_welcomeManager;
};

#endif // WELCOMEMODE_H
