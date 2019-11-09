#ifndef MARTIX
#define MARTIX
#include <iostream>
#include <vector>
#include <sstream>
class Martix{
public:
    bool operator==(const Martix& b) const{
        return (martix==b.martix)&&(column==b.column)&&(row==b.row);
    }
    bool operator!=(const Martix& b) const{
        return !(martix==b.martix);
    }
    Martix()=default;
    Martix(unsigned c,unsigned r):row(r),column(c){
        for(unsigned i=0;i<r;i++){
            std::vector<int> temp;
            for(unsigned j=0;j<c;j++){
                temp.push_back(0);
            }
            martix.push_back(temp);
        }
    }
    Martix(const std::string& s):Martix(3,3){
        std::istringstream iss(s);
        unsigned n;unsigned num=0;
        while(iss>>n){
            martix[num/3][num%3]=n;
            num++;
        }
        row=3;
        column=3;
    }
    void show() const{
        for(const auto&i:martix){
            for(const auto&j:i){
                std::cout<<j<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
    std::vector<int>& operator[](int n) {
        return martix[n];
    }
    const std::vector<int>& operator[](int n) const {
        return martix[n];
    }
    unsigned getRow(){
        return row;
    }
    unsigned getColumn(){
        return column;
    }
private:
    std::vector<std::vector<int>> martix;
    unsigned column;
    unsigned row;
};
#endif
