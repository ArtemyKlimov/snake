#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <iostream>
#include <string>
#include <vector>



class Snake{
private:
	enum direction{
		UP = 72,
		LEFT = 75,
		RIGHT = 77,
		DOWN = 80
	};
	struct Position{
		int X;
		int Y;
		bool operator==(Position &rhs){
			return (this->X == rhs.X) && (this->Y ==rhs.Y);
		}
	};
	struct Player{
		std::string name;
		int score;
	};
	bool GameOver;
	char snake_head;
	int button;
	int length;
	int n,e; ////????
	int score;
	int difficulty;
	int speed;
	int size;
	int x, y;
	int MaxScore;
	std::vector<Player> rating;
	direction dir;
	Position tail[600];
	Position current;
	Position food;
	
	void setcursor(int x, int y);
	void refresh_values();
	void generate_food();
	void clear_screen();
	void draw_border_limits();
	void check_collisions();
	void check_buttons();
	void draw_head();
	void draw_body();
	void clear_tail();
	void automatic_movement();
	void start_game();
	void update_score();
	void change_difficulty();
	int getMaxScore();
	void showRating();
	void saveNewRecord();
	
public:
	Snake();
	~Snake();
	void start_menu();
	
};


#endif