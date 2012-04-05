#include "IAlgorithm.h"
#include "Exceptions.h"


void IAlgorithm::Run()
{
    throw NotImplementedException("This algorithm can't tun.");
}
