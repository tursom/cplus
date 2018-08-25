cmake_minimum_required(VERSION 2.8.12)
project(cplus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
add_definitions(-std=c++11)

add_executable(
        cplus main.cpp cplus/lang/Int.cpp cplus/lang/Int.h cplus/lang/String.cpp cplus/lang/String.h
        cplus/lang/Long.cpp cplus/lang/Long.h cplus/utils/StringBuilder.cpp cplus/utils/StringBuilder.h
        cplus/lang/Object.cpp cplus/lang/Object.h cplus/thread/ThreadMutex.cpp cplus/thread/ThreadMutex.h
        cplus/thread/Thread.cpp cplus/thread/Thread.h cplus/system/time.cpp cplus/system/io.cpp
        cplus/system/io.h cplus/system/OutputStream.cpp cplus/system/OutputStream.h cplus/tools/class.h
        cplus/lang/Float.cpp cplus/lang/Float.h cplus/lang/Double.cpp cplus/lang/Double.h cplus/lang/Short.cpp
        cplus/lang/Short.h cplus/lang/Char.cpp cplus/lang/Char.h cplus/utils/StringBuffer.cpp
        cplus/utils/StringBuffer.h cplus/utils/List.hpp cplus/utils/ArrayList.hpp cplus/test/utils.cpp
        cplus/test/utils.h cplus/lang/Size.cpp cplus/lang/Size.h cplus/utils/Stack.cpp cplus/utils/Stack.h
        cplus/utils/ArrayStack.hpp cplus/memory/dark_magic.h cplus/memory/dark_magic.cpp cplus/lang/Byte.h
        cplus/thread/ThreadPool.cpp
        cplus/thread/ThreadPool.h cplus/thread/Runnable.cpp cplus/thread/Runnable.h cplus/test/memory.cpp
        cplus/test/memory.h cplus/socket/ServerSocket.cpp cplus/socket/ServerSocket.h cplus/socket/Socket.cpp
        cplus/socket/Socket.h cplus/lang/ByteArray.cpp cplus/lang/ByteArray.h cplus/lang/Byte.cpp
        cplus/system/Exception.cpp cplus/system/Exception.h cplus/utils/Set.hpp cplus/utils/Queue.cpp
        cplus/utils/Queue.h cplus/lang/CPlusString.cpp cplus/lang/CPlusString.h cplus/utils/Map.hpp cplus/system/OutOfIndexException.cpp cplus/system/OutOfIndexException.h)

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    target_compile_options(cplus PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(cplus "${CMAKE_THREAD_LIBS_INIT}")
endif()