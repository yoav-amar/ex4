#include "StatesPairTester.hpp"
#include <memory>
#include "MazeState.hpp"
#include <iostream>
int statesPairTester::StatasPairTester::check() {
    auto curState = std::make_unique<state::MazeState>(1,2);
    auto prevState = std::make_unique<state::MazeState>(1,2);
    auto statesPair = std::make_unique<statesPair::StatesPair>(*curState, *prevState);
    if(statesPair->getPrev().equlas(statesPair->getCur())) {
        std::cout<<"success"<<std::endl;
        return 0;
    }
    return 1;
}