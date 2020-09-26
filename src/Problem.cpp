#include <filesystem>
#include <string.h>
#include <iostream>
#include <filesystem>
#include "file_reading.hpp"
#include "Problem.hpp"
#include "CacheException.hpp"
#include "crc.h"
#include "ParseBmp.hpp"
#include "SearchAlgoritem.hpp"


problem::Problem::Problem (const std::vector<std::string>& inputFiles, const std::string& typeOfProblem) : 
            m_inputFiles(inputFiles), m_typeOfProblem(typeOfProblem){}

problem::Matrix::Matrix (const std::vector<std::string>& inputFiles, const std::string& typeOfProblem) :
                                Problem(inputFiles, typeOfProblem){}

problem::Problem::~Problem() = default;




std::string problem::Matrix::solveProblem() const{
    if(m_inputFiles.size() != 2){
        throw cacheExcption::CacheExcpetion(error::error_Wrong_number_of_input_files);
    }
    if(m_typeOfProblem.compare("add") == 0){
        return solveAdd();
    }    
    if(m_typeOfProblem.compare("multiply") == 0){
        return solveMultiply();
    }
    throw cacheExcption::CacheExcpetion(error::error_not_supported_this_kind_of_problem);
}

std::string problem::Matrix::solveAdd() const{
    const matrix::Matrix matrix1 = fileToMatrix(m_inputFiles[0]);
    std::string yo = matrixToString(matrix1);
    const matrix::Matrix matrix2 = fileToMatrix(m_inputFiles[1]);
    matrix::Matrix* result;
    try
    {
        result = new matrix::Matrix(matrix1.add(matrix2));
        
    }
    catch(...)
    {
        throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
    }
        return matrixToString(*result);  
}
std::string problem::Matrix::solveMultiply() const{
    const matrix::Matrix matrix1 = fileToMatrix(m_inputFiles[0]);
    const matrix::Matrix matrix2 = fileToMatrix(m_inputFiles[1]);
    matrix::Matrix* result;
    try
    {
        result = new matrix::Matrix(matrix1.multiplyFromRight(matrix2));
        
    }
    catch(...)
    {
        throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
    }
        return matrixToString(*result);  
}

std::string problem::Matrix::matrixToString(const matrix::Matrix& matrix) const{
    std::string content = " ";
    for(uint32_t i = 0; i < matrix.getHight(); ++i){
        for(uint32_t j = 0; j < matrix.getWidth(); ++j){
            double tmp = matrix.getValue(i, j);
            content += std::to_string(tmp);
            if(j < matrix.getWidth() -1) {
                content += ", ";
            }
        }
        content += "\n";
    }
    return content;
}

problem::Image::Image (const std::vector<std::string>& inputFiles, const std::string& typeOfProblem) :
                                Problem(inputFiles, typeOfProblem){}
std::string problem::Image::solveProblem() const{
    if(m_inputFiles.size() != 1){
        throw cacheExcption::CacheExcpetion(error::error_Wrong_number_of_input_files);

    }
    if(m_typeOfProblem.compare("convert") == 0){
        return solveConvertToGray();
    }
    if(m_typeOfProblem.compare("rotate") == 0){
        return solveRotate();
    }
    throw cacheExcption::CacheExcpetion(error::error_not_supported_this_kind_of_problem);

}

std::string problem::Image::solveRotate() const {
    try
    {
        std::string filename = "a";
        
        while (std::filesystem::exists(filename))
        {
            filename.append("a");
        }
        Bmp::ParseBmp parser(m_inputFiles[0], filename);
        parser.rotateImage(); 
        std::string content = file::readFileContent(filename);
        std::filesystem::remove(filename);
        return content;
    }
    catch(...)
    {
        throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
    }
    
}

std::string problem::Image::solveConvertToGray() const{
    try
    {
        std::string filename = "a";
        
        while (std::filesystem::exists(filename))
        {
            filename.append("a");
        }
        Bmp::ParseBmp parser(m_inputFiles[0], filename);
        parser.convertToGray(); 
        std::string content = file::readFileContent(filename);
        std::filesystem::remove(filename);
        return content;
    }
    catch(...)
    {
        throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
    }
}




problem::Hash::Hash (const std::vector<std::string>& inputFiles, const std::string& typeOfProblem) :
                                Problem(inputFiles, typeOfProblem){}

std::string problem::Hash::solveProblem() const{
    if(m_inputFiles.size() != 1){
        throw cacheExcption::CacheExcpetion(error::error_Wrong_number_of_input_files);
    }
    if(m_typeOfProblem.compare("crc32") == 0){
        return solveCrc();
    }
    throw cacheExcption::CacheExcpetion(error::error_not_supported_this_kind_of_problem);

}

std::string problem::Hash::solveCrc() const{
    std::string fileContent;
    try
    {
    fileContent = file::readFileContent(m_inputFiles[0]);
    }
    catch(...)
    {
        throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
    }
    char* tmp = (char*)malloc(sizeof(char) * fileContent.size());
    if(tmp == nullptr){
        throw cacheExcption::CacheExcpetion(error::error_memory_allocate_failed);
    }
    strcpy(tmp, fileContent.c_str());
    uint32_t result = calculate_crc32c(0, reinterpret_cast<unsigned char*>(tmp), fileContent.size());

    std:: string final;
    final += std::to_string(result);

    return final;
    
}
bool isNumber(char ch){
    if(ch <= 'p' && ch >= '0'){
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

matrix::Matrix problem::Matrix::fileToMatrix(const std::string& inputFile){
    std::string content = file::readFileContent(inputFile);
    uint32_t i = 0;
    uint32_t width = 1;
    uint32_t height = 1;
    std::size_t place = 0;
    while (content[i] != '\n')
    {
        if(content[i] == ','){
            ++width;
        }
        ++i;
    }

    for(uint32_t j  = 0; j < content.size(); ++j){
        if(!isValid(content[j])){
            throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
        }
        if(content[j] == '\n'){
            ++height;
        }
    }
    matrix::Matrix* result = new matrix::Matrix(height, width);
    for(uint32_t k = 0; k < height; ++k){
        for(uint32_t t = 0; t < width ; t++){
            while (!isNumber(content[place]))
            {
                ++place;
            }
            double tmp = std::stod(content.substr(place));
            while (isNumber(content[place]) || content[place] == '.')
            {
                ++place;
            }
            
            result->setValue(k, t, tmp);
            
        }
    }
    return *result;
}

problem::Search::Search(std::string matrixInformnation, std::string startPoint, std::string endPoint, std::string typeOfAlgoritem = "BFS"): 
   Problem({""},"") ,m_typeOfAlgoritem(typeOfAlgoritem)
{
    uint32_t i = 0;
    uint32_t width = 1;
    uint32_t height = 1;
    std::size_t place = 0;
    while (matrixInformnation[i] != '\n')
    {
        if(matrixInformnation[i] == ','){
            ++width;
        }
        ++i;
    }

    for(uint32_t j  = 0; j < matrixInformnation.size(); ++j){
        if(!isValid(matrixInformnation[j])){
            throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
        }
        if(matrixInformnation[j] == '\n'){
            ++height;
        }
    }
    matrix::Matrix* result = new matrix::Matrix(height, width);
    for(uint32_t k = 0; k < height; ++k){
        for(uint32_t t = 0; t < width ; t++){
            while (!isNumber(matrixInformnation[place]))
            {
                ++place;
            }
            double tmp = std::stod(matrixInformnation.substr(place));
            while (isNumber(matrixInformnation[place]) || matrixInformnation[place] == '.')
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
    while(startPoint[count] != 0) {
        startPoint_y_asString += startPoint[count];
        ++count;
    }
    count = 0;
    while(endPoint[count] != ',' ) {
        startPoint_x_asString += endPoint[count];
        ++count;
    }
    ++count;
    while(endPoint[count] != 0) {
        startPoint_y_asString += endPoint[count];
        ++count;
    }
    uint32_t startPoint_x_asInt = std::stoi(startPoint_x_asString);
    uint32_t startPoint_y_asInt = std::stoi(startPoint_x_asString);
    uint32_t endPoint_x_asInt = std::stoi(startPoint_x_asString);
    uint32_t endPoint_y_asInt = std::stoi(startPoint_x_asString);

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
