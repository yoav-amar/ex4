#include "MazeStateTester.hpp"
#include "MazeState.hpp"
#include <memory>
#include <iostream>
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
    if(!mistake) {
        std::cout<<"success"<<std::endl;
        return 0;
    }
    return 1;
}