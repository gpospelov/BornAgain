#include "ISample.h"

long ISample::m_id_last=0;


ISample::ISample() {
    m_id = m_id_last;
    m_id_last++;
}


ISample *ISample::clone()
{
    throw NotImplementedException("ISample::clone() -> Error! The clone method is not implemented");
}
