//
// Created by looperX on 2019-07-25.
//

#include "Server.h"
#include <glog/logging.h>

void Server::start()
{

}

void Server::handleNewConn()
{
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    socklen_t client_addr_len = sizeof(client_addr);
    int acceptFd = accept(listenFd_, (struct sockaddr*)&client_addr, &client_addr_len);

    while (acceptFd > 0)
    {
        // 限制服务器的最大并发连接数
        if (acceptFd >= MAXFDS)
        {
            close(accept_fd);
            continue;
        }

        if (setSocketNonBlocking(acceptFd) < 0)
        {
            LOG(info) << "Set non block failed!";
            //perror("Set non block failed!");
            // abort();
            return;
        }
    }


}

