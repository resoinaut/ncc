all:
	g++ -o ncc.exe --std=c++20 *.cc lexer/*.cc utilities/*.cc
