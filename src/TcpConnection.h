//
// Created by looperX on 2019-07-17.
//

#ifndef CPP_STUDY_TCPCONNECTION_H
#define CPP_STUDY_TCPCONNECTION_H


class TcpConnection {
public:
    int send();
    void setReadCb();
    EventLoop* getLoop() const { return loop_; }

private:
    EventLoop* loop_;

};


#endif //CPP_STUDY_TCPCONNECTION_H
