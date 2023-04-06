cmake_minimum_required(VERSION 3.25)
project(NodeMesh)

set(CMAKE_CXX_STANDARD 23)

add_executable(NodeMesh main.cpp src/Node.h src/NetOfNodes.h)
