#include "IAlgorithm.h"
#include "Exceptions.h"


void IAlgorithm::execute()
{
    throw NotImplementedException("This algorithm can't tun.");
}
