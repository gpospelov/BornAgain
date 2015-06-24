#include "GUIFunctionalTestService.h"
#include "AdvancedGUIFunctionalTest.h"


GUIFunctionalTestService::GUIFunctionalTestService(const FunctionalTestInfo &info)
    : FunctionalTestComponentService(info)
{

}

IFunctionalTest *GUIFunctionalTestService::getFunctionalTest()
{
    AdvancedGUIFunctionalTest *result = new AdvancedGUIFunctionalTest(m_testInfo.m_test_name, m_testInfo.m_test_description, getSimulation(), getThreshold());
    return result;
}

