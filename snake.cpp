#include "snake.hpp"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>

Snake::Snake(): GameOver(false), length(5),n(1), e(2), score(0), speed(40), size(0), dir(RIGHT){
					current.X = 30;
					current.Y = 12;
					food.X = 20;
					food.Y = 20;
				}
Snake::~Snake(){}

void Snake::setcursor(int x, int y){
	HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);	
}

void Snake::refresh_values(){
	GameOver = false;
	n = 1, e = 2;
	length = 5;
	dir = RIGHT;
	current.X = 30;
	current.Y = 12;
	score = 0;
}

void Snake::generate_food(){
	srand(time(NULL));
	if(food == current){
		food.X = (rand() % 57) + 2;
		food.Y = (rand() % 17) + 7;
		length+=2;
		setcursor(food.X,food.Y);
		std::cout<<"@";
		score+=10;
	}
	else{
		setcursor(food.X, food.Y);
		std::cout<<"@";
	}
}
void Snake::clear_screen(){
	for (int i = 1; i <= 1; i++){ 
		for (int line = 1; line <= 25; line++){
			for (int i = 1; i <= 60; i++){
				y = line ;
				setcursor(i, line);
				std::cout<<(char)219;
			}
			Sleep(1);
		}
		for (int line = 1; line <= 25; line++){
			for (int i = 1; i <= 60; i++){
				y = line ;
				setcursor(i, line);
				std::cout<<' ';
			}
			Sleep(1);
		}
	}
}
void Snake::draw_border_limits(){
	x = 1; y = 6; setcursor(x, y); std::cout<<(char)201; //верхний левый угол
	x = 60; y = 6; setcursor(x, y); std::cout<<(char)187; //верхний правый угол
	x = 1; y = 25; setcursor(x, y); std::cout<<(char)200; //нижний левый угол
	x = 60; y = 25;setcursor(x, y); std::cout<<(char)188; //нижний парвый угол
	//Bordes
	for (int B_su = 2; B_su <= 59; B_su ++) {y = 6; setcursor(B_su, y);  std::cout<<(char)205;}//верхн¤¤ граница
	for (int B_in = 2; B_in <= 59; B_in ++) {y = 25; setcursor(B_in, y); std::cout<<(char)205;} //нижн¤¤ граница	
	for (int B_iz = 7; B_iz <= 24; B_iz ++) {x = 1; setcursor(x, B_iz); std::cout<<' ';}
	for (int B_de = 7; B_de <= 24; B_de ++) {x = 60; setcursor(x, B_de); std::cout<<' ';}//
}
void Snake::check_collisions(){
	int i=1;
	while(i<=length){
		if(tail[i]==current){
			GameOver=true;
			break;
		}
		i++;
	}
	if(current.X ==1) {
		current.X = 59;
		draw_border_limits();
	}
	if(current.X == 60){
		current.X = 2;
		draw_border_limits();
	}
	if (current.Y == 6 || current.Y == 25) {
		GameOver = true;
	}
}

void Snake::check_buttons(){
	if(kbhit()){    //проверка ввода клавиш
		button = (int)getch();
		switch(button){
			case UP:
				if(dir != DOWN)
					dir = UP; break;
			case RIGHT:
				if(dir !=LEFT)
					dir = RIGHT; break;
			case DOWN:
				if(dir !=UP)
					dir = DOWN; break;
			case LEFT:
				if(dir !=RIGHT)
					dir = LEFT; break;				
		}
	}
}
void Snake::draw_head(){
	setcursor(current.X,current.Y);
	switch(dir){
		case UP: snake_head = '^'; break;
		case RIGHT: snake_head = '>'; break;
		case DOWN: snake_head = 'V'; break;
		case LEFT: snake_head = '<'; break;
	}
	std::cout<<snake_head;
}
void Snake::draw_body(){
	tail[n].X = current.X;
	tail[n].Y = current.Y;
	if (n>length) n=0;
	n++;
}
void Snake::clear_tail(){
	setcursor(tail[e].X, tail[e].Y);
	std::cout<<' ';
	tail[e].X = 0;
	tail[e].Y = 0;
	if(e>length) e=0; e++;
	//std::cout<<e<<" "<<std::endl;
}
void Snake::automatic_movement(){
	switch(dir){                    
		case UP: current.Y--; break;
		case RIGHT: current.X++; break;
		case DOWN: current.Y++; break;
		case LEFT: current.X--; break;
	}
}
void Snake::start_game(){
	draw_border_limits();
	while(!GameOver){
		check_buttons();
		check_buttons();
		draw_head();
		check_collisions();
		generate_food();
		draw_body();
		clear_tail();
		Sleep(speed);
		automatic_movement();
		
	}
	setcursor(25, 15);
	std::cout<<"GAME OVER\n";
	getch();
}

void Snake::start_menu(){
	while(true){
	CONSOLE_CURSOR_INFO cci = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	clear_screen();
	setcursor(16,12); std::cout<<"Press SPACE to play new game";
	setcursor(20,14); std::cout<<"Press ENTER to exit";
		button = (int)getch();
		if(button == 13){   //enter pressed
			break;
		}
		else if(button == 32){   //space pressed
			clear_screen();
			refresh_values();
			start_game();
		}
	}		
}