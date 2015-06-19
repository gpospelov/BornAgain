#ifndef TESTFORMFACTORSREGISTRY_H
#define TESTFORMFACTORSREGISTRY_H

#include <map>
#include <string>

class IFormFactor;

class TestFormFactorsRegistry {
public:
    typedef std::map<std::string, IFormFactor *>::iterator iterator;
    TestFormFactorsRegistry();

    iterator begin() { return m_data.begin();}
    iterator end() { return m_data.end();}

protected:
    void add(const std::string &key, IFormFactor *formfactor);

private:
    std::map<std::string, IFormFactor *> m_data;
};

#endif
