#include "StatesPairTester.hpp"
#include <memory>
int main( ){
 auto tester = std::make_unique<statesPairTester::StatasPairTester>();
    return tester->check();
}