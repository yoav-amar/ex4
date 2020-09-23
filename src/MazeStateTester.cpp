#include "MazeStateTester.hpp"
#include "MazeState.hpp"
#include <memory>
#include <iostream>
#include "Matrix.hpp"

void printState(state::MazeState s) {
    std::cout<<s.getX()<<","<<s.getY()<<std::endl;
}

int stateTester::MazeStateTester::check() {
    bool mistake = false;
    auto state = std::make_unique<state::MazeState>(1,2);
    if(1 != state->getX()) {
        std::cout<<"mistake at get X, your x ="<<state->getX()<<" but it is actually 1"<<std::endl;
        mistake = true;
    }
    if(2 != state->getY()) {
        std::cout<<"mistake at get Y, your Y ="<<state->getX()<<" but it is actualy 2"<<std::endl;
        mistake = true;
    }
    auto matrix = std::make_unique<matrix::Matrix>(3,3);
    int count = 0;
    for(int i = 0; i < 3; i ++) {
        for(int j = 0; j < 3; j++) {
            matrix->setValue(i,j,count);
            ++count;
        }
    }
    auto neighbors = std::vector<state::MazeState>(state->getAllPossibleNeighbors(*matrix));
    for(int i = 0; i < neighbors.size(); i++) {
        printState(neighbors.at(i));
    }
    if(!mistake) {
        std::cout<<"success"<<std::endl;
        return 0;
    }
    return 1;
}