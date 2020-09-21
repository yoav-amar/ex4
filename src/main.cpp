#include "ClientHandle.hpp"
#include "CacheException.hpp"
int main(int argc, char** argv) {
    try{
    client::ClientHandle* client = new client::ClientHandle(argc, argv);
    client->solve();
    }
    catch(cacheExcption::CacheExcpetion *error){
        error->printErrorMessage();
    }

}