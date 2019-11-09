/*
#include <iostream>
#include <string>
#include <functional>
#include <array>
#include <vector>
#include <memory>
#include "Martix.h"
#include <algorithm>
#include "StateNode.h"
void AStar(StateNode &start,StateNode &desti){
    StateNode current;
    std::vector<StateNode> Open{start},Closed;
    while(!Open.empty()){
        current=Open[Open.size()-1];
        if(current==desti) 
            showPath(start,desti);
        Open.pop_back();
        current.searched=1;
        Closed.push_back(current);
        for(unsigned i=0;i<4;i++){
            StateNode neighbour;
            if(Safe[i](current)){
                neighbour=Go[i](current);
                neighbour.searched=0;
                neighbour.setParent(&current);
                neighbour.updateDepth();
                setHeristic(neighbour,desti);
                for(const auto&i:Closed){
                    if(i==neighbour){ 
                        neighbour.searched=1;
                        break;
                    }
                }
                if(neighbour.searched==1) continue;
                for(auto&i:Open){
                    if(i==neighbour){
                        neighbour.getHeristical()<i.getHeristical()?(i=neighbour):(i=i);
                    }
                }
                Open.push_back(neighbour);
            }
        }
        std::sort(Open.begin(),Open.end(),[](StateNode &a,StateNode &b){
            return a.getHeristical()>b.getHeristical();
        }
        );
    }
}
*/

