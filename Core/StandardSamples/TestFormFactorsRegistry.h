#ifndef TESTFORMFACTORSREGISTRY_H
#define TESTFORMFACTORSREGISTRY_H

#include <map>
class IFormFactor;

class TestFormFactorsRegistry {
public:
    TestFormFactorsRegistry();

protected:
    void add(const std::string &key, IFormFactor *formfactor);

private:
    std::map<std::string, IFormFactor *> m_data;
};

#endif
