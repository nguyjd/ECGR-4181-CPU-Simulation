cmake_minimum_required(VERSION 3.10)

project(CPU)

add_executable(CPU
	main.cpp
	system.cpp
	Functional-Blocks/DECODER/Decoder.cpp
	Functional-Blocks/ADDER/Adder.cpp
	Functional-Blocks/ALU/Alu.cpp
	Functional-Blocks/MUX/Mux2to1.cpp
	Functional-Blocks/MUX/Mux4to1.cpp
	Functional-Blocks/EXTEND/Extend.cpp
	Functional-Blocks/EXTEND/SignExtend.cpp
	Functional-Blocks/EXTEND/ZeroExtend.cpp
	Functional-Blocks/SHIFT/ShiftLeft.cpp
	Data-Handler/Event.cpp
	Data-Handler/Instruction.cpp
	Data-Handler/Data.cpp
	Data-Handler/Wire.cpp
)

target_include_directories(CPU PRIVATE
	${CMAKE_SOURCE_DIR}
	Data-Handler
	Functional-Blocks/DECODER
	Functional-Blocks/ADDER
	Functional-Blocks/ALU
	Functional-Blocks/MUX
	Functional-Blocks/EXTEND
	Functional-Blocks/SHIFT
)