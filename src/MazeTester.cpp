#include "MazeTester.hpp"
#include <memory>
#include "Matrix.hpp"
#include "MazeState.hpp"
#include <iostream>

int mazeTester::MazeTester::check() const {
    bool mistake = false; 
    int count = 0;
    auto mazeAsMatrix = std::make_unique<matrix::Matrix>(3,2);
    for (int i = 0; i < mazeAsMatrix->getHight(); i++) {
        for (int j = 0; j < mazeAsMatrix->getWidth(); j ++) {
            mazeAsMatrix->setValue(i ,j, count++);
        }
    }
    auto startState = std::make_unique<state::MazeState>(0,0);
    auto endState = std::make_unique<state::MazeState>(2,1);
    auto maze  = std::make_unique<maze::Maze>(*mazeAsMatrix, *startState, *endState);
    if(maze->getWidth() != 2) {
        mistake = true;
        std::cout<<"mistake at getWidth. your width is "<<maze->getWidth()<< "but it is actually 2"<<std::endl;
    }
    if(maze->getHeight() != 3) {
        mistake = true;
        std::cout<<"mistake at getWidth. your width is "<<maze->getHeight()<< "but it is actually 3"<<std::endl;
    }
    if(!mistake) {
        std::cout<<"success"<<std::endl;
        return 0;
    }
    return 1;
}