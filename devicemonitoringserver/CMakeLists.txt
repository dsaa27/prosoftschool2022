cmake_minimum_required(VERSION 3.22)
project(devicemonitoringserver)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(handlers)
include_directories(server)
include_directories(servermock)

add_executable(devicemonitoringserver
        handlers/abstractaction.h
        handlers/abstractmessagehandler.h
        handlers/abstractnewconnectionhandler.h
        server/abstractclientconnection.h
        server/abstractconnection.h
        server/abstractconnectionserver.h
        servermock/clientconnectionmock.cpp
        servermock/clientconnectionmock.h
        servermock/connectionchannel.cpp
        servermock/connectionchannel.h
        servermock/connectionmock.cpp
        servermock/connectionmock.h
        servermock/connectionservermock.cpp
        servermock/connectionservermock.h
        servermock/object.cpp
        servermock/object.h
        servermock/servertests.cpp
        servermock/servertests.h
        servermock/taskqueue.cpp
        servermock/taskqueue.h
        common.h
        devicemock.cpp
        devicemock.h
        devicemonitoringserver.cpp
        devicemonitoringserver.h
        deviceworkschedule.h
        main.cpp
        test_runner.h
        tests.cpp
        tests.h encoding/BaseEncoderExecutor.h encoding/ROT3.cpp encoding/Mirror.cpp serialization/MessageSerializator.cpp serialization/MessageSerializator.h)
