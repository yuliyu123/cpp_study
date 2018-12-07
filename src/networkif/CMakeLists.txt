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
add_executable(demo SessionEstablished.cc ${PROTO_SRCS}) 
target_link_libraries(demo protobuf)
