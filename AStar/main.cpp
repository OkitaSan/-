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
    std::shared_ptr<StateNode> parentNode=std::make_shared<StateNode>(start);
    std::vector<StateNode> Open{start},Closed;
    while(!Open.empty()){
        std::cout<<Open.size()<<std::endl;
        current=Open[Open.size()-1];
        if(current!=start){
        std::cout<<"The following is the parent node"<<std::endl;
        (current.getParent()).show();
        }
        std::cout<<"The following is the node"<<std::endl;
        current.show();
        if(current==desti)
            return;
        Open.pop_back();
        current.searched=1;
        Closed.push_back(current);
        for(unsigned i=0;i<4;i++){
            StateNode neighbour;
            if(Safe[i](current)){
                neighbour=Go[i](current);
                neighbour.searched=0;
                parentNode=std::make_shared<StateNode>(current);
                neighbour.setParent(parentNode);
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
int main(){
    std::string beginState="2 8 3 1 0 4 7 6 5";
    std::string endState="1 2 3 8 0 4 7 6 5";
    StateNode strt(beginState);
    StateNode edt(endState);
    AStar(strt,edt);
    return 0;
}
