cmake_minimum_required(VERSION 3.14)

project(server_monitoring_device_prosoft LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(server_monitoring_device_prosoft
  main.cpp
  tests.h
  tests.cpp
  test_runner.h
  deviceworkschedule.h
  devicemonitoringserver.h
  devicemonitoringserver.cpp
  devicemock.h
  devicemock.cpp
  common.h
  randomgenerate.h
  randomgenerate.cpp
  servermock/servertests.cpp
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
  server/abstractclientconnection.h
  server/abstractconnection.h
  server/abstractconnectionserver.h
  handlers/abstractaction.h
  handlers/abstractmessagehandler.h
  handlers/abstractnewconnectionhandler.h
  clientservercomponents/messageserializer.h
  clientservercomponents/messageserializer.cpp
  clientservercomponents/commandcenter.h
  clientservercomponents/commandcenter.cpp
  clientservercomponents/messageencoder.h
  clientservercomponents/messageencoder.cpp
  clientservercomponents/baseencoderexecutor.h
  clientservercomponents/abstractmessage.h
  deviceworkschedule.cpp
  unittest/unittest.h
  unittest/unittest.cpp
  unittest/deserialization.cpp
  unittest/serialization.cpp
  unittest/codealgorithm.cpp
  unittest/commandcenter.cpp
)
target_link_libraries(server_monitoring_device_prosoft Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS server_monitoring_device_prosoft
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
