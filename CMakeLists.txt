#
#	 .o88b.  .d88b.  d8888b. d888888b d888888b  .o88b.  .d8b.  db      d888888b
#	d8P  Y8 .8P  Y8. 88  `8D `~~88~~'   `88'   d8P  Y8 d8' `8b 88        `88'  
#	8P      88    88 88oobY'    88       88    8P      88ooo88 88         88   
#	8b      88    88 88`8b      88       88    8b      88~~~88 88         88   
#	Y8b  d8 `8b  d8' 88 `88.    88      .88.   Y8b  d8 88   88 88booo.   .88.  
#	 `Y88P'  `Y88P'  88   YD    YP    Y888888P  `Y88P' YP   YP Y88888P Y888888P
#
#	Copyright (C) 2025 Matthew E. Majfud-Wilinski. All Rights Reserved.
#

# ... 
cmake_minimum_required(VERSION 3.10)

# ... 
project(Corticali C)

# ... 
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/source/*.c)

# ... 
include_directories(${CMAKE_SOURCE_DIR}/include)

# ... 
add_executable(corticali ${SOURCES})

# ... 
if(NOT WIN32)
# ... 
	target_link_libraries(corticali PRIVATE m)
endif()