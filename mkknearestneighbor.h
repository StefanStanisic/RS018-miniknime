#ifndef MKKNEARESTNEIGHBOR_H
#define MKKNEARESTNEIGHBOR_H

#include "mknode.h"

class MKKNearestNeighbor : public MKNode
{
public:
    MKKNearestNeighbor();

    bool process_data() override;
    bool classify(unsigned int k, unsigned long labelIndex, std::vector<double> p);
};

#endif // MKKNEARESTNEIGHBOR_H
