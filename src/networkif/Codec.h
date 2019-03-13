//
// Created by looperX on 2019-03-13.
//

#ifndef CPP_STUDY_CODEC_H
#define CPP_STUDY_CODEC_H

#include "CommonDef.h"
#include <google/protobuf/message.h>

class Codec : boost::noncopyable
{
public:
    static google::protobuf::Message* createMessage(const std::string& type_name);
};

#endif //CPP_STUDY_CODEC_H
