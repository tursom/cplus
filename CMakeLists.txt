# cmake_minimum_required(VERSION <specify CMake version here>)
project(cplus)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

add_executable(cplus main.cpp cplus/utils/Int.cpp cplus/utils/Int.h cplus/utils/String.cpp cplus/utils/String.h cplus/utils/Long.cpp cplus/utils/Long.h cplus/utils/StringBuilder.cpp cplus/utils/StringBuilder.h cplus/utils/Object.cpp cplus/utils/Object.h cplus/thread/ThreadMutex.cpp cplus/thread/ThreadMutex.h cplus/thread/Thread.cpp cplus/thread/Thread.h cplus/system/time.cpp cplus/system/io.cpp cplus/system/io.h cplus/system/OutputStream.cpp cplus/system/OutputStream.h cplus/tools/Class.h cplus/utils/Float.cpp cplus/utils/Float.h cplus/utils/Double.cpp cplus/utils/Double.h cplus/utils/Short.cpp cplus/utils/Short.h cplus/utils/Char.cpp cplus/utils/Char.h cplus/utils/StringBuffer.cpp cplus/utils/StringBuffer.h cplus/utils/List.hpp cplus/utils/ArrayList.hpp cplus/test/utils.cpp cplus/test/utils.h cplus/utils/Size.cpp cplus/utils/Size.h cplus/utils/Stack.cpp cplus/utils/Stack.h cplus/utils/ArrayStack.h)