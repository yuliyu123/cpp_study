//
// Created by looperX on 2019-07-25.
//

#ifndef CPP_STUDY_SERVER_H
#define CPP_STUDY_SERVER_H


class Server {
public:
    void start();
    void handleNewConn();


private:
    int threadNum_;
    int port_;
    int listenFd_;
    static const int MAXFDS = 100000;
};


#endif //CPP_STUDY_SERVER_H
