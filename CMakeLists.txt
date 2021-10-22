cmake_minimum_required(VERSION 3.10)

project(CPU)

add_executable(CPU
	main.cpp
	system.cpp
	Functional-Blocks/DECODER/Decoder.cpp
	Functional-Blocks/DECODER/Adder.cpp
	Data-Handler/Event.cpp
	Data-Handler/Instruction.cpp
)

target_include_directories(CPU PRIVATE
	${CMAKE_SOURCE_DIR}
	Data-Handler
	Functional-Blocks/DECODER
	Functional-Blocks/ADDER
)