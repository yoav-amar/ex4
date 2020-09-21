#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string_view>
#include <system_error>

#include "ClientHandle.hpp"
#include "Server.hpp"

void serverSide::SerialServer::open(int16_t port,const client::ClientHandle& handeler){

}