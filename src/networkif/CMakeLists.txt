FILE(GLOB proto_files ${CMAKE_CURRENT_LIST_DIR}/proto/*.proto)
FOREACH(proto_file ${proto_files})
    STRING(REGEX REPLACE "[^/]proto" "" proto_file_name ${proto_file})
    LIST(APPEND PROTO_SRCS "${proto_file_name}.pb.cc")
	ADD_CUSTOM_COMMAND(
		OUTPUT "${proto_file_name}.pb.h" "${proto_file_name}.pb.cc"
		COMMAND protoc --proto_path=${CMAKE_CURRENT_LIST_DIR}/proto
                       --cpp_out=${CMAKE_CURRENT_LIST_DIR}/proto/ ${proto_file}
		DEPENDS ${proto_file}
	)
ENDFOREACH(proto_file)
message(STATUS ${PROTO_SRCS})
include_directories(./proto)
include_directories("${PROJECT_SOURCE_DIR}/src")

add_library(protobuf_codec Codec.cpp)
add_executable(networkifDemo CodecTest.cpp ${PROTO_SRCS})
target_link_libraries(networkifDemo protobuf_codec protobuf)
