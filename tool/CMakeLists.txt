add_library(uart src/uart.cpp)
add_library(crc src/crc.cpp)
target_include_directories(uart PUBLIC include)
target_include_directories(crc PUBLIC include)