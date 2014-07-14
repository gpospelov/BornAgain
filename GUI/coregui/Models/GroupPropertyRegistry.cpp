#include "GroupPropertyRegistry.h"
#include "GUIHelpers.h"

GroupPropertyRegistry *GroupPropertyRegistry::m_instance = 0;

GroupPropertyRegistry::GroupPropertyRegistry()
{
    if(m_instance)
        throw GUIHelpers::Error("GroupPropertyRegistry::GroupPropertyRegistry() -> Error. The instance has already been created.");
    m_instance = this;
}


GroupPropertyRegistry::~GroupPropertyRegistry()
{
    m_instance = 0;
}
