#include "ClientHandle.hpp"
#include "CacheManager.hpp"
#include "Problem.hpp"
#include "CacheException.hpp"
#include "ErrorCache.hpp"
#include "file_reading.hpp"
#include <iostream>

client::ClientHandle::ClientHandle(int argc, char** argv){
    if(argc < 3){
        throw cacheExcption::CacheExcpetion(error::error_wrong_number_of_arguments);
    }
    m_nameOfProblem = argv[1];
    m_typeOfProblem = argv[2];
    if(m_nameOfProblem.compare("cache") == 0){
        buildCacheProblem(argc, argv);
    }else{
        m_outpotFile = argv[argc - 1];
        for(int i = 3; i < argc - 1; ++i){
            m_inputFiles.push_back(argv[i]);
        }
        m_cache = new manager::CacheManager(m_inputFiles, m_typeOfProblem, m_nameOfProblem);
    }
}
void client::ClientHandle::solve(){
    if(m_nameOfProblem.compare("cache") == 0){
        solveCache();
        return;
    }
    if(m_cache->solutionAlreadyExistInCache()){
        m_cache->useExistingSolution(m_outpotFile);
        return;
    }
    problem::Problem* problem;
    if(m_nameOfProblem.compare("Matrix") == 0){
        //problem = new problem::Matrix(m_inputFiles, m_typeOfProblem);
    }
    else if(m_nameOfProblem.compare("Image") == 0){
        problem = new problem::Image(m_inputFiles, m_typeOfProblem);
    }
    else if(m_nameOfProblem.compare("Hash") == 0){
        problem = new problem::Hash(m_inputFiles, m_typeOfProblem);
    }
    else{
        throw cacheExcption::CacheExcpetion(error::error_not_supported_this_kind_of_problem);
    }
    std::string solution = problem->solveProblem();
    m_cache->addSolution(solution);
    file::writeFileContent(m_outpotFile, solution);

}

void client::ClientHandle::buildCacheProblem(int argc, char** argv){
    if(m_typeOfProblem.compare("clear") == 0){
        if(argc != 3){
        throw cacheExcption::CacheExcpetion(error::error_wrong_number_of_arguments);
        }
    }
    if (m_typeOfProblem.compare("search") == 0){
        if(argc < 6){
        throw cacheExcption::CacheExcpetion(error::error_wrong_number_of_arguments);
        }
        m_nameOfProblem = argv[3];
        m_typeOfProblem = argv[4];
        for(int i = 5; i < argc; ++i){
            m_inputFiles.push_back(argv[i]);
        }
        m_cache = new manager::CacheManager(m_inputFiles, m_typeOfProblem, m_nameOfProblem);
    }
    throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);

}

void client::ClientHandle::solveCache(){
    if(m_typeOfProblem.compare("clear") == 0){
        m_cache->clear();
        return;
    }
    if(m_typeOfProblem.compare("search") == 0){
        if (m_cache->solutionAlreadyExistInCache()){
            std::cout << "result found in cache" << std::endl;
            return;
        }
        std::cout << "result wasn't found in cache" << std::endl;
        return;
    }
    throw cacheExcption::CacheExcpetion(error::error_cant_solve_the_problem);
}