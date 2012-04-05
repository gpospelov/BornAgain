#ifndef ISIMULATION_H
#define ISIMULATION_H

class OutputData;

class ISimulation
{
public:
    virtual ~ISimulation() {}
    void run();
    void setOutputData(OutputData* p_data) { mp_output_data = p_data; }

protected:
    OutputData* mp_output_data;
};

#endif // ISIMULATION_H
