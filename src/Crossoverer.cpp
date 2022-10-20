//
// Created by kuba on 10/7/22.
//

#include "Crossoverer.h"
#include <unordered_map>
#include <iostream>
#include "RandomGenerators.h"

void PMXCrossoverer::Cross(Specimen& lhs, Specimen& rhs) {
    //std::random_device rd;
    //std::mt19937_64 mt(rd());
    if ((*rand->distChance)(*rand->mt) > this->crossoverProbability) {
        return; 
    }
    // select start, end
    int start = (*rand->distStart)(*rand->mt);
    int end = (*rand->distsEndNode.at(start + 1))(*rand->mt);
    // clear mapping dicts
//    std::vector<int> ll{7,5,0,6,1,9,3,2,8,4};
//    std::vector<int> rl{0,5,8,9,2,3,4,6,7,1};
//    for (int i = 0; i<10;i++){
//        lhs.nodeGenome.at(i)=ll.at(i);
//        rhs.nodeGenome.at(i)=rl.at(i);
//    }
//    start = 4;
//    end = 6;
    this->mappingLhsRhs.clear();
    this->mappingRhsLhs.clear();
    for (int i = start; i<=end; i++){
        int l = lhs.nodeGenome.at(i); //o
        int r = rhs.nodeGenome.at(i); //n
        if (l!=r){
            // lr == u
            // rl == ur
            bool lhsrhsHasKey = !(mappingLhsRhs.find(l) == mappingLhsRhs.end());
            bool rhslhsHasKey = !(mappingRhsLhs.find(r) == mappingRhsLhs.end());
            if (!rhslhsHasKey && !lhsrhsHasKey){
                mappingLhsRhs.insert_or_assign(r,l);
                mappingRhsLhs.insert_or_assign(l,r);
            }
            else if(rhslhsHasKey && lhsrhsHasKey){
//                mappingLhsRhs.erase(mappingRhsLhs.at(r));
//                mappingRhsLhs.erase(mappingLhsRhs.at(l));

                mappingLhsRhs.insert_or_assign(mappingRhsLhs.at(r),mappingLhsRhs.at(l));
                mappingRhsLhs.insert_or_assign(mappingLhsRhs.at(l),mappingRhsLhs.at(r));
                mappingLhsRhs.erase(l);
                mappingRhsLhs.erase(r);
            }
            else if(rhslhsHasKey){
//                mappingRhsLhs.erase(l);
                mappingRhsLhs.insert_or_assign(l,mappingRhsLhs.at(r));
//                mappingLhsRhs.erase(mappingRhsLhs.at(r));
                mappingLhsRhs.insert_or_assign(mappingRhsLhs.at(r),l);
                mappingRhsLhs.erase(r);
            }
            else {
//                mappingLhsRhs.erase(r);
                mappingLhsRhs.insert_or_assign(r,mappingLhsRhs.at(l));
//                mappingRhsLhs.erase(mappingLhsRhs.at(r));
                mappingRhsLhs.insert_or_assign(mappingLhsRhs.at(r),r);
                mappingLhsRhs.erase(l);
            }
        }
//        if (!lhsrhsHasKey)
//            mappingLhsRhs.insert(std::pair<int,int> {rhs.nodeGenome.at(i),lhs.nodeGenome.at(i)});
//        else{
//            mappingLhsRhs.insert(std::pair<int,int> {rhs.nodeGenome.at(i),mappingLhsRhs.at(lhs.nodeGenome.at(i))});
//            mappingLhsRhs.erase(lhs.nodeGenome.at(i));
//        }
//        if (!rhslhsHasKey)
//            mappingRhsLhs.insert(std::pair<int,int> {lhs.nodeGenome.at(i),rhs.nodeGenome.at(i)});
//        else{
//            mappingRhsLhs.insert(std::pair<int,int> {lhs.nodeGenome.at(i),mappingRhsLhs.at(rhs.nodeGenome.at(i))});
//            mappingRhsLhs.erase(rhs.nodeGenome.at(i));
//        }
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

Crossoverer* Crossoverer::GenerateCrossoverer(std::string crossovererName, double crossoverProbability, RandomGenerators& rand)
{
    if (crossovererName == "PMX") {
        return new PMXCrossoverer(crossoverProbability, rand);
    }
}


