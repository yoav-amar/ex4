#include <filesystem>
#include <string.h>
#include <iostream>
#include <filesystem>
#include "file_reading.hpp"
#include "Problem.hpp"
#include "CacheException.hpp"
// #include "crc.h"
// #include "ParseBmp.hpp"


problem::Problem::Problem (const std::vector<std::string>& inputFiles, const std::string& typeOfProblem) : 
            m_inputFiles(inputFiles), m_typeOfProblem(typeOfProblem){}

// problem::Matrix::Matrix (const std::vector<std::string>& inputFiles, const std::string& typeOfProblem) :
//                                 Problem(inputFiles, typeOfProblem){}

problem::Problem::~Problem() = default;


bool isNumber(char ch){
    if((ch <= 'p' && ch >= '0') || ch == 'b'){
        return true;
    }
    return false;
}

bool isValid(char ch){
    if(isNumber(ch) || ch == ' ' || ch == ',' || ch == '\n' || ch == '\r' || ch == '\t'){
        return true;
    }
    return false;
}



problem::Search::Search(std::string const matrixInformation, const std::string typeOfAlgoritem,
       const std::string startPoint, const std::string endPoint, uint32_t height, uint32_t width): 
         Problem({""},"") ,m_typeOfAlgoritem(typeOfAlgoritem)
{
    uint32_t i = 0;
    uint32_t realWidth = 1;
    uint32_t realHeight = 1;
    std::size_t place = 0;
    while (matrixInformation[i] != '\n')
    {
        if(matrixInformation[i] == ','){
            ++realWidth;
        }
        ++i;
    }

    for(uint32_t j  = 0; j < matrixInformation.size(); ++j){
        if(!isValid(matrixInformation[j])){
            throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
        }
        if(matrixInformation[j] == '\n'){
            ++realHeight;
        }
    }
    if( realHeight!= height || realWidth != width){
        throw cacheExcption::CacheExcpetion(error::error_Wrong_dimensions);
    }
    matrix::Matrix* result = new matrix::Matrix(height, width);
    for(uint32_t k = 0; k < height; ++k){
        for(uint32_t t = 0; t < width ; t++){
            while (!isNumber(matrixInformation[place]))
            {
                ++place;
            }
            double tmp;
            if(matrixInformation[place] == 'b'){
                tmp = -1;
            }else{
                tmp = std::stod(matrixInformation.substr(place));
            }
            while (isNumber(matrixInformation[place]) || matrixInformation[place] == '.')
            {
                ++place;
            }
            
            result->setValue(k, t, tmp);
            
        }
    }
    std::string startPoint_x_asString;
    std::string startPoint_y_asString;
    std::string endPoint_x_asString;
    std::string endPoint_y_asString;
    
    uint32_t count = 0;
    while(startPoint[count] != ',' ) {
        startPoint_x_asString += startPoint[count];
        ++count;
    }
    ++count;
    while(startPoint[count] != '\0') {
        startPoint_y_asString += startPoint[count];
        ++count;
    }
    count = 0;
    while(endPoint[count] != ',' ) {
        endPoint_x_asString += endPoint[count];
        ++count;
    }
    ++count;
    while(endPoint[count] != '\0') {
        endPoint_y_asString += endPoint[count];
        ++count;
    }
    uint32_t startPoint_x_asInt = std::stoi(startPoint_x_asString);
    uint32_t startPoint_y_asInt = std::stoi(startPoint_x_asString);
    uint32_t endPoint_x_asInt = std::stoi(endPoint_x_asString);
    uint32_t endPoint_y_asInt = std::stoi(endPoint_x_asString);

    auto startState = std::make_unique<state::MazeState>(startPoint_x_asInt, startPoint_y_asInt, result->getValue(startPoint_x_asInt, startPoint_y_asInt));
    auto endState = std::make_unique<state::MazeState>(endPoint_x_asInt, endPoint_y_asInt, result->getValue(endPoint_x_asInt, endPoint_y_asInt));

    m_maze = new maze::Maze(*result, *startState, *endState);
}


std::string problem::Search::solveProblem() const {
    std::unique_ptr<searchAlgoritem::SearchAlgoritm> searcher;
    if (m_typeOfAlgoritem.compare("DFS") == 0) {
         searcher = std::make_unique<searchAlgoritem::DFS_Algoritem>(*m_maze);
    }
    else if(m_typeOfAlgoritem.compare("A*") == 0){
        searcher = std::make_unique<searchAlgoritem::A_STAR_Algoritem>(*m_maze);
    }
    else if(m_typeOfAlgoritem.compare("BestFS") == 0){
        searcher = std::make_unique<searchAlgoritem::BestFS_Algoritem>(*m_maze);
    }
    else {
         searcher = std::make_unique<searchAlgoritem::BFS_Algoritem>(*m_maze);
    }
    auto soloution = std::make_unique<soloution::Soloution>(searcher->solve());
    std::string result = std::to_string(soloution->getCost()) + "," + m_typeOfAlgoritem + soloution->getPathToSoloution();
    return result;
}

maze::Maze problem::Search::getMaze() const {
    auto startState =std::make_unique<state::MazeState> (m_maze->getstartState().getX(), m_maze->getstartState().getY(), m_maze->getstartState().getValue());
    auto endState =std::make_unique<state::MazeState> (m_maze->getEndState().getX(), m_maze->getEndState().getY(), m_maze->getEndState().getValue());
    auto matrix = std::make_unique<matrix::Matrix>(m_maze->getMazeAsMatrix().getHight(), m_maze->getMazeAsMatrix().getWidth());
    for(int i = 0; i < matrix->getHight(); i++) {
        for(int j =0; j < matrix->getWidth(); j++) {
            matrix->setValue(i,j,m_maze->getMazeAsMatrix().getValue(i,j));
        }
    }
    auto maze_copy = std::make_unique<maze::Maze>(*matrix, *startState, *endState);
    return *maze_copy;
}