cmake_minimum_required(VERSION 3.15)
project(COMSerial)



find_package(serial REQUIRED)
find_package(Poco REQUIRED)
find_package(RdKafka REQUIRED)


add_executable(${PROJECT_NAME} src/consumer.cpp src/common.cpp)
target_link_libraries(${PROJECT_NAME} serial::serial)
target_link_libraries(${PROJECT_NAME} Poco::Poco)
target_link_libraries(${PROJECT_NAME} RdKafka::rdkafka++)
















