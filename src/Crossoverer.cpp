//
// Created by kuba on 10/7/22.
//

#include "Crossoverer.h"
#include <unordered_map>

void PMXCrossoverer::Cross(Specimen& lhs, Specimen& rhs) {
    if (this->distChance(mt) > this->crossoverProbability) { return; }
    // select start, end
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> distStart(0, lhs.nodeGenome.size()-2);
    int start = distStart(mt);
    std::uniform_int_distribution<> distEnd(start+1, lhs.nodeGenome.size()-1);
    int end = distEnd(mt);
    // create mapping dicts
    std::unordered_map<int, int> mappingLhsRhs;
    std::unordered_map<int, int> mappingRhsLhs;
    for (int i = start; i<=end; i++){
        bool lhsrhsHasKey = !(mappingLhsRhs.find(lhs.nodeGenome.at(i)) == mappingLhsRhs.end());
        bool rhslhsHasKey = !(mappingRhsLhs.find(rhs.nodeGenome.at(i)) == mappingRhsLhs.end());
        if (!lhsrhsHasKey)
            mappingLhsRhs.insert(std::pair<int,int> {rhs.nodeGenome.at(i),lhs.nodeGenome.at(i)});
        else{
            mappingLhsRhs.insert(std::pair<int,int> {rhs.nodeGenome.at(i),mappingLhsRhs.at(lhs.nodeGenome.at(i))});
            mappingLhsRhs.erase(lhs.nodeGenome.at(i));
        }
        if (!rhslhsHasKey)
            mappingRhsLhs.insert(std::pair<int,int> {lhs.nodeGenome.at(i),rhs.nodeGenome.at(i)});
        else{
            mappingRhsLhs.insert(std::pair<int,int> {lhs.nodeGenome.at(i),mappingRhsLhs.at(rhs.nodeGenome.at(i))});
            mappingRhsLhs.erase(rhs.nodeGenome.at(i));
        }
    }
    for (int i =0; i<lhs.nodeGenome.size(); i++){
        if(i>=start && i<=end){ //swap
            int temp = lhs.nodeGenome.at(i);
            lhs.nodeGenome.at(i)=rhs.nodeGenome.at(i);
            rhs.nodeGenome.at(i)=temp;
        }
        else{ // map
            if (!(mappingLhsRhs.find(lhs.nodeGenome.at(i)) == mappingLhsRhs.end()))
                lhs.nodeGenome.at(i)=mappingLhsRhs.at(lhs.nodeGenome.at(i));
            if (!(mappingRhsLhs.find(rhs.nodeGenome.at(i)) == mappingRhsLhs.end()))
                rhs.nodeGenome.at(i)=mappingRhsLhs.at(rhs.nodeGenome.at(i));
        }
    }
    // 1\2\3\4\5\6
    // 1\3\5\4\6\2
    // s=1
    // e=3
    // 1\3\5\4\2\6
    // 1\2\3\4\6\3
    // swap
    // lr {3:2} -> {5:2}
    // rl
}

Crossoverer& Crossoverer::GenerateCrossoverer(std::string crossovererName)
{
    if (crossovererName == "PMX") {
        PMXCrossoverer crossoverer;
        return crossoverer;
    }
}
