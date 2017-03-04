#include <iostream>
#include "snake.hpp"
#include <windows.h>

int main(){
	system("color f1");
	SetConsoleTitle("Snake");
	system("mode 64,27");
	std::cout<<"\t  Game 'Snake'. Control by keyboard-arrows"<<std::endl;
	Snake sk;
	sk.start_menu();
	system("exit");
		
	return 0;
}