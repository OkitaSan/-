#ifndef STATE_NONE
#define STATE_NONE
#include <iostream>
#include <string>
#include <functional>
#include <array>
#include <vector>
#include <memory>
#include "Martix.h"
void swapNum(int &x,int &y){
    x=x^y;
    y=x^y;
    x=x^y;
}
class StateNode{
public:
    friend void estimate(StateNode& start,const StateNode& des);
    using PtToParents= std::shared_ptr<StateNode>;
    unsigned getDepth() const {
        return deep;
    }
    StateNode(const StateNode& a){
        parent=a.parent;
        currState=a.currState;
        deep=a.deep;
        destination=a.destination;
        zeroX=a.zeroX;
        zeroY=a.zeroY;
        heristic=a.heristic;
    }
    StateNode& updateDepth(){
        deep=(parent->getDepth())+1;
        return *this;
    }
    unsigned getZeroX() const{
        return zeroX;
    }
    unsigned getZeroY() const{
        return zeroY;
    }
    void setZeroX(unsigned x){
        zeroX = x;
    }
    void setZeroY(unsigned y){
        zeroY = y;
    }
    friend void setHeristic(StateNode&a,const StateNode&b);
    StateNode()=default;
    StateNode(const std::string& s):currState(s){
        for(unsigned i=0;i<3;i++){
            for(unsigned j=0;j<3;j++){
                if(currState[i][j]==0){
                    zeroX=i;zeroY=j;break;
                }
                if(currState[zeroX][zeroY]==0) break;
            }
        }
    }
    std::vector<int>& operator[](int n) {
        return currState[n];
    }
    const std::vector<int>& operator[](int n) const {
        return currState[n];
    }
    bool operator==(const StateNode& b) const{
        return currState == b.currState;
    }
    unsigned getHeristical() const{
        return heristic;
    }
    void setParent(PtToParents ptr){
        parent=ptr;
    }
    const StateNode& getParent() const{
        return *parent;
    }
    StateNode& getParent() {
        return *parent;
    }
    bool operator!=(const StateNode& a) const{
        return !(a.currState==currState);
    }
    void show() const{
        currState.show();
    }
    bool searched=0;
private:
    PtToParents parent=nullptr;
    Martix currState=Martix(3,3);
    unsigned deep=0;
    unsigned destination=0;
    unsigned zeroX=0;
    unsigned zeroY=0;
    unsigned heristic;
};
auto isUpSafe=[](StateNode a)->bool{
    if(a.getZeroX()==0) return false;
    else return true;
};
auto isDownSafe=[](StateNode a)->bool{
    if(a.getZeroX()==2) return false;
    else return true;
};
auto isLeftSafe=[](StateNode a)->bool{
    if(a.getZeroY()==0) return false;
    else return true;
};
auto isRightSafe=[](StateNode a)->bool{
    if(a.getZeroY()==2) return false;
    else return true;
};
void estimate(StateNode& start,const StateNode& des);
void estimate(StateNode& start,const StateNode& des){
    start.destination=(start[0][0]!=des[0][0])+(start[0][1]!=des[0][1])+(start[0][2]!=des[0][2])+(start[1][0]!=des[1][0])+(start[1][1]!=des[1][1])+(start[1][2]!=des[1][2])+(start[2][0]!=des[2][0])+(start[2][1]!=des[2][1])+(start[2][2]!=des[2][2]);
}
void setHeristic(StateNode&a,const StateNode&b);
void setHeristic(StateNode&a,const StateNode&b){
    estimate(a,b);
    a.heristic=a.updateDepth().deep+a.destination;
}
std::array<std::function<bool(StateNode)>,4> Safe{isUpSafe,isDownSafe,isLeftSafe,isRightSafe};
auto goUp=[](StateNode a)mutable->StateNode{
    unsigned tempX=a.getZeroX()-1;
    swapNum(a[a.getZeroX()][a.getZeroY()],a[a.getZeroX()-1][a.getZeroY()]);
    a.setZeroX(tempX);
    return a;
};
auto goDown=[](StateNode a)mutable->StateNode{
    unsigned tempX=a.getZeroX()+1;
    swapNum(a[a.getZeroX()][a.getZeroY()],a[a.getZeroX()+1][a.getZeroY()]);
    a.setZeroX(tempX);
    return a;
};
auto goLeft=[](StateNode a)mutable->StateNode{
    unsigned tempY=a.getZeroY()-1;
    swapNum(a[a.getZeroX()][a.getZeroY()],a[a.getZeroX()][a.getZeroY()-1]);
    a.setZeroY(tempY);
    return a;
};
auto goRight=[](StateNode a)mutable->StateNode{
    unsigned tempY=a.getZeroY()+1;
    swapNum(a[a.getZeroX()][a.getZeroY()],a[a.getZeroX()][a.getZeroY()+1]);
    a.setZeroY(tempY);
    return a;
};
std::array<std::function<StateNode(StateNode)>,4> Go{goUp, goDown, goLeft, goRight};
void showPath(StateNode &a, StateNode &b){
    while(b.getParent()!=a){
        b.show();
        b=b.getParent();
    }
}
#endif
