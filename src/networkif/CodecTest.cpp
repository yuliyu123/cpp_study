//
// Created by looperX on 2019-03-13.
//

#include "Codec.h"

int main()
{
    Codec codec;
    google::protobuf::Message* newMessage = codec.createMessage("networkif.Query");
    if (newMessage)
    {
        std::cout << "new message has create by protobuf factory, new message: " << newMessage << std::endl;
    }
    assert(newMessage != nullptr);
    return 0;
}

