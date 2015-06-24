#ifndef GUIFUNCTIONALTESTSERVICE_H
#define GUIFUNCTIONALTESTSERVICE_H

#include "FunctionalTestComponentService.h"
#include "FunctionalTestRegistry.h"


class GUIFunctionalTestService : public FunctionalTestComponentService
{
public:
    GUIFunctionalTestService(const FunctionalTestInfo &info);

    IFunctionalTest *getFunctionalTest();
};

#endif

