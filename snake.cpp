#include "snake.hpp"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <utility>
#include <algorithm>

Snake::Snake(): GameOver(false), length(5),n(1), e(2), score(0), difficulty(1), size(0), dir(RIGHT){
					MaxScore = getMaxScore();
					speed = 120/difficulty;
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
	speed = 120/difficulty;
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
		score+=5*difficulty;
		update_score();
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

void Snake::update_score(){
	x = 24; y = 5; setcursor(x,y); std::cout<<score;	
}

void Snake::draw_border_limits(){
	x = 1; y = 4; setcursor(x,y); std::cout<<" Max Score is: "<<MaxScore;
	x = 1; y = 5; setcursor(x, y); std::cout<<"Your current score is: ";
	std::cout<<"\t\tDifficulty is: ";
	switch(difficulty){
		case 1: std::cout<<"EASY"; break;
		case 2: std::cout<<"MEDIUM"; break;
		case 4: std::cout<<"HARD"; break;
	}
	update_score();
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

int Snake::getMaxScore(){
	std::ifstream fin("scr.txt");
	int Max = 0;
	if(fin.is_open()){
		Player tmp;
		while(fin>>tmp.name){
			fin>>tmp.score;
			rating.push_back(tmp);
		}
		if(rating.size() == 0){
			Max = 0;
		}
		else if(rating.size() == 1){
			Max = rating[0].score;
		}
		else{		
			sort(rating.begin(), rating.end(),
			[](Player const&p1, Player const &p2){return p1.score > p2.score;});
			Max = rating[0].score;
		}
		fin.close();
	}
	return Max;
}

void Snake::saveNewRecord(){
	clear_screen();
	setcursor(20, 12);
	std::cout<<"Input Your name: ";
	CONSOLE_CURSOR_INFO cci = {15, TRUE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	Player tmp;
	MaxScore = score;
	if(std::cin>>tmp.name){
		tmp.score = score;
		rating.push_back(tmp);
		setcursor(20, 14);
		std::cout<<"DONE! CONGRATULATION!";
		Sleep(2000);
	}
	sort(rating.begin(), rating.end(),
			[](Player const&p1, Player const &p2){return p1.score > p2.score;});
	std::ofstream fout("scr.txt");
	if(fout.is_open()){
		for(auto i: rating){
			fout<<i.name<<" "<<i.score<<std::endl;
		}
	}
	fout.close();
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
	update_score();
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
	if(score> MaxScore){
		setcursor(25, 17); 
		std::cout<<"New Record!";
		setcursor(25, 18);
		std::cout<<"Press ENTER to save it";
		button = getch();
		if(button == 13){
			saveNewRecord();
		}		
	}
	else{
		getch();
	}
}

void Snake::showRating(){
	clear_screen();
	for(int i = 0; i < rating.size(); ++i){
		setcursor(16,8+i);
		std::cout<<rating[i].name<<" ---- "<<rating[i].score<<std::endl;
		if(i>10) break;
	}
	getch();	
}

void Snake::start_menu(){
	while(true){
	CONSOLE_CURSOR_INFO cci = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	clear_screen();
	setcursor(16,10); std::cout<<"Press SPACE to play NEW GAME";
	setcursor(12,12); std::cout<<"Press BACKSPACE to change difficulty";
	setcursor(16,14); std::cout<<"Press ESC to show view TOP";
	setcursor(20,16); std::cout<<"Press ENTER to exit";
		button = (int)getch();
		if(button == 13){   //enter pressed
			break;
		}
		else if(button == 32){   //space pressed
			clear_screen();
			refresh_values();
			start_game();
		}
		else if(button == 8){  //backspace pressed
			clear_screen();
			change_difficulty();
		}
		else if(button == 27){
			showRating();
		}
	}		
}

void Snake::change_difficulty(){
	setcursor(17,10); std::cout<<"Press 1 to play on easy ";
	setcursor(14,12); std::cout<<"Press 2 to play on medium mode";
	setcursor(15,14); std::cout<<"Press 3 to play on hard mode";
	setcursor(18,16); std::cout<<"Press ENTER to exit";
	while(true){
		button = (int)getch();
		if(button == 49){   //1 pressed
			difficulty = 1;
			break;
		}
		else if(button == 50){   //2 pressed
			difficulty = 2;
			break;
		}
		else if(button == 51){  //3 pressed
			difficulty = 4;
			break;
		}
		else if(button == 13)   //enter pressed
			break;
	}
}
