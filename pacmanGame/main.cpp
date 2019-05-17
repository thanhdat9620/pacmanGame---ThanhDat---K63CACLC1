#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <SFML\Audio.hpp>
using namespace std;
using namespace sf;

// create the window
sf::RenderWindow window(sf::VideoMode(420, 465), "This is PacMan");
SoundBuffer soundIntro, soundDeath, soundFruit, soundEatGhost, soundChomp, soundGame;
Sound soundIntroP, soundDeathP, soundFruitP, soundEatGhostP, soundChompP, soundGameP;

// map
int maze[31][28] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 },
	{ 1, 3, 1, 0, 0, 1, 2, 1, 0, 0, 0, 1, 2, 1, 1, 2, 1, 0, 0, 0, 1, 2, 1, 0, 0, 1, 3, 1 },
	{ 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1 },
	{ 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 },
	{ 1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3, 1 },
	{ 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1 },
	{ 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1 },
	{ 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 },
	{ 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

	sf::Texture wallImage, nothingImage, youWinImage, gameOverImage, menuImage;
	sf::Sprite wall, nothing, youWin, gameOver, menu;
	int eatFruitCount = 0;

void Map_draw(){

	wallImage.loadFromFile("bigwall.png");
	wall.setTexture(wallImage);
	
	nothingImage.loadFromFile("nothing.png");
	nothing.setTexture(nothingImage);

	for (int i = 0; i < 31; i++){
		for (int j = 0; j < 28; j++){
			switch (maze[i][j])
			{
			case 1: wall.setPosition(sf::Vector2f(15 * j, 15 * i));
				window.draw(wall);
				break;
			case 0: nothing.setPosition(Vector2f(15 * j, 15 * i));
				window.draw(nothing);
				break;
			default:
				break;
			}
		}
	}
}

// fruit
Texture fruitImage, bigFruitImage;
Sprite fruit, bigFruit;
vector <Vector2f> fruit_pos(242);
vector <Vector2f> bigFruit_pos(4);

void fruit_draw(){

	int x = 0, y = 0;

	fruitImage.loadFromFile("fruit.png");
	fruit.setTexture(fruitImage);
	bigFruitImage.loadFromFile("bigfruit.png");
	bigFruit.setTexture(bigFruitImage);

	for (int i = 0; i < 31; i++){
		for (int j = 0; j < 28; j++){
			if (maze[i][j] == 2){
				fruit_pos[x] = Vector2f(15 * j, 15 * i);
				fruit.setPosition(fruit_pos[x]);
				window.draw(fruit);
				x++;
			}
			if (maze[i][j] == 3){
				bigFruit_pos[y] = Vector2f(15 * j, 15 * i);
				bigFruit.setPosition(bigFruit_pos[y]);
				window.draw(bigFruit);
				y++;
			}
		}
	}
}

// ghost
Texture ghostImage;
IntRect rectGhost(15, 0, 15, 15);
Sprite ghost1(ghostImage, rectGhost);
Sprite ghost2(ghostImage, rectGhost);
Sprite ghost3(ghostImage, rectGhost);
Sprite ghost4(ghostImage, rectGhost);
Sprite ghost5(ghostImage, rectGhost);
Sprite ghost6(ghostImage, rectGhost);

//vector<Vector2f> ghost_pos(4);
Vector2f ghost_pos1 = Vector2f(180, 210);
Vector2f ghost_pos2 = Vector2f(195, 210);
Vector2f ghost_pos3 = Vector2f(210, 210);
Vector2f ghost_pos4 = Vector2f(225, 210);
Vector2f ghost_pos5 = Vector2f(165, 210);
Vector2f ghost_pos6 = Vector2f(240, 210);

Clock clock2;
bool startToMove = true;
enum direct { LEFT, RIGHT, UP, DOWN };
direct ghost_dir[6] = { UP, UP, UP, UP };
direct player_dir = RIGHT;

void ghost_draw(){

	int x = 0;

	ghostImage.loadFromFile("tileset_pacman_ghost.png");

	if (clock2.getElapsedTime().asSeconds() > 0.1f){
		if (rectGhost.left == 105)
			rectGhost.left = 0;
		else
			rectGhost.left += 15;
		ghost1.setTextureRect(rectGhost);
		ghost2.setTextureRect(rectGhost);
		ghost3.setTextureRect(rectGhost);
		ghost4.setTextureRect(rectGhost);
		ghost5.setTextureRect(rectGhost);
		ghost6.setTextureRect(rectGhost);

		clock2.restart();
	}

	ghost1.setPosition(ghost_pos1);
	window.draw(ghost1);
	ghost2.setPosition(ghost_pos2);
	window.draw(ghost2);
	ghost3.setPosition(ghost_pos3);
	window.draw(ghost3);
	ghost4.setPosition(ghost_pos4);
	window.draw(ghost4); 
	ghost5.setPosition(ghost_pos5);
	window.draw(ghost5);
	ghost6.setPosition(ghost_pos6);
	window.draw(ghost6);

}

// player
Texture playerImage, playerVerImage;
IntRect rectPlayer(45, 0, 15, 15);
Sprite player(playerImage, rectPlayer);
Sprite playerVer(playerVerImage, rectPlayer);
Vector2f player_pos(210, 345);
bool checkHero = false;
int x_step = 0, y_step = 0;
Clock clock3;
const int TILESIZE = 15;

void player_draw(direct &player_dir){

	if (x_step >= 0) player_dir = RIGHT;
	if (x_step < 0) player_dir = LEFT;
	if (y_step > 0) player_dir = DOWN;
	if (y_step < 0) player_dir = UP;

	playerImage.loadFromFile("tileset_pacman_player.png");
	playerVerImage.loadFromFile("tileset_pacman.png");

	if (clock3.getElapsedTime().asSeconds() > 0.1f){
		if (rectPlayer.left == 0)
			rectPlayer.left = 45;
		else
			rectPlayer.left -= 15;
		player.setTextureRect(rectPlayer);
		playerVer.setTextureRect(rectPlayer);
		clock3.restart();
	}

	player.setPosition(player_pos);
	playerVer.setPosition(player_pos);

	switch (player_dir){
	case RIGHT:
		player.setOrigin(0, 0);
		player.setScale(1, 1); 
		window.draw(player); 
		break;
	case LEFT:
		player.setOrigin(player.getLocalBounds().width, 0);
		player.setScale(-1, 1);
		window.draw(player);
		break;
	case UP:
		playerVer.setOrigin(playerVer.getLocalBounds().width, playerVer.getLocalBounds().height);
		playerVer.setScale(-1, -1);
		window.draw(playerVer);
		break;
	case DOWN:
		playerVer.setOrigin(0, 0);
		playerVer.setScale(1, 1);
		window.draw(playerVer);
		break;
	}

}

bool check_Collision(Vector2f &player_pos, int &x_step, int &y_step){

	int x1 = player_pos.x;
	int y1 = player_pos.y;
	int x2 = player_pos.x + 15;
	int y2 = player_pos.y + 15;

	if (x_step) {

		x1 = (x1 + x_step) / TILESIZE;
		y1 = y1 / TILESIZE;
		y2 = (y2 - 1) / TILESIZE;
		x2 = (x2 - 1 + x_step) / TILESIZE;

		if ((x1 >= 0 && x2 <28) && x_step > 0) {
			if (maze[y1][x2] == 1 || maze[y2][x2] == 1) {
				if ((int)player_pos.y % TILESIZE != 0) {
					if (maze[y1][x2] == 1) player_pos.y++;
					if (maze[y2][x2] == 1) player_pos.y--;
				}
				return 1;
			}
		}
		else if ((x1 >= 0 && x2 <28) && (x_step < 0)) {
			if (maze[y1][x1] == 1 || maze[y2][x1] == 1){
				if ((int)player_pos.y % TILESIZE != 0) {
					if (maze[y1][x1] == 1) player_pos.y++;
					if (maze[y2][x1] == 1) player_pos.y--;
				}
				return 1;
			}
		}
	}
	else if (y_step) {
		x1 = x1 / TILESIZE;
		y1 = (y1 + y_step) / TILESIZE;
		y2 = (y2 - 1 + y_step) / TILESIZE;
		x2 = (x2 - 1) / TILESIZE;
		if (y_step > 0) {
			if (maze[y2][x1] == 1 || maze[y2][x2] == 1) {
				if ((int)player_pos.x % TILESIZE != 0) {
					if (maze[y2][x1] == 1) player_pos.x++;
					if (maze[y2][x2] == 1) player_pos.x--;
				}
				return 1;
			}
		}
		else if (y_step < 0) {
			if (maze[y1][x1] == 1 || maze[y1][x2] == 1){
				if ((int)player_pos.x % TILESIZE != 0) {
					if (maze[y1][x1] == 1) player_pos.x++;
					if (maze[y1][x2] == 1) player_pos.x--;
				}
				return 1;
			}
		}
	}
	
	if (x_step < 0 && player_pos.x <= 0) player_pos.x = 405;
	if (x_step > 0 && player_pos.x >= 405) player_pos.x = 0;
	if (player_pos.y < 0) player_pos.y = 450;
	if (player_pos.y > 450) player_pos.y = 0;

	return 0;
}

bool check_PlayerWin(){
	if (eatFruitCount == 246 || Keyboard::isKeyPressed(Keyboard::Space)) return true;
	return false;
}

void player_update(Clock &tik){

	if (Keyboard::isKeyPressed(Keyboard::Key::Left)){
		x_step = -1;
		y_step = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)){
		x_step = 1;
		y_step = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Up)){
		x_step = 0;
		y_step = -1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down)){
		x_step = 0;
		y_step = 1;	
	}
	if ((x_step || y_step) && !check_Collision(player_pos, x_step, y_step)){
		player_pos.x += x_step;
		player_pos.y += y_step;
	}

	for (int i = 0; i < 31; i++){
		for (int j = 0; j < 28; j++){
			if (maze[i][j] == 2 && (player_pos.x == 15 * j && player_pos.y == 15 * i)){
				maze[i][j] = 0;
				soundChompP.setVolume(50);
				soundChompP.play();
				eatFruitCount++;
			}
			if (maze[i][j] == 3 && (player_pos.x == 15 * j && player_pos.y == 15 * i)){
				maze[i][j] = 0;
				soundFruitP.play();
				eatFruitCount++;
				checkHero = true;
				tik.restart();
			}
		}
	}
}

void ghost_move(Vector2f &ghost_pos, direct &ghost_dir) {

	int x_step = 0; int y_step = 0;

	switch (ghost_dir)
	{
	case LEFT: x_step = -1;
		break;
	case RIGHT: x_step = 1;
		break;
	case UP: y_step = -1;
		break;
	case DOWN: y_step = 1;
		break;
	}

	if (check_Collision(ghost_pos, x_step, y_step)) {
		switch (ghost_dir)
		{
		case LEFT: ghost_dir = (rand() % 2) ? UP : DOWN;
			break;
		case RIGHT: ghost_dir = (rand() % 2) ? UP : DOWN;
			break;
		case UP: ghost_dir = (rand() % 2) ? LEFT : RIGHT;
			break;
		case DOWN: ghost_dir = (rand() % 2) ? LEFT : RIGHT;
			break;
		}
	}
	else {
		ghost_pos.x += x_step;
		ghost_pos.y += y_step;
	}
}

bool checkGameIsOver(bool checkHero){
	if (checkHero) return false;
	if ((abs(player_pos.x - ghost_pos1.x) <= 3 && abs(player_pos.y - ghost_pos1.y) <= 3) || (abs(player_pos.x - ghost_pos2.x) <= 3 && abs(player_pos.y - ghost_pos2.y) <= 3) || (abs(player_pos.x - ghost_pos3.x) <= 3 && abs(player_pos.y - ghost_pos3.y) <= 3) || (abs(player_pos.x - ghost_pos4.x) <= 3 && abs(player_pos.y - ghost_pos4.y) <= 3) || (abs(player_pos.x - ghost_pos5.x) <= 3 && abs(player_pos.y - ghost_pos5.y) <= 3) || (abs(player_pos.x - ghost_pos6.x) <= 3 && abs(player_pos.y - ghost_pos6.y) <= 3)) return true;
	return false;
}

int main()
{

//	SoundBuffer soundIntro, soundDeath, soundFruit, soundEatGhost, soundChomp, soundGame;
	soundIntro.loadFromFile("pacman_beginning.wav");
	soundDeath.loadFromFile("pacman_death.wav");
	soundFruit.loadFromFile("pacman_eatfruit.wav");
	soundEatGhost.loadFromFile("pacman_eatghost.wav");
	soundChomp.loadFromFile("pacman_chomp.wav");
	soundGame.loadFromFile("pacman_intermission.wav");
//	Sound soundIntroP, soundDeathP, soundFruitP, soundEatGhostP, soundChompP, soundGameP;
	soundIntroP.setBuffer(soundIntro);
	soundDeathP.setBuffer(soundDeath);
	soundFruitP.setBuffer(soundFruit);
	soundEatGhostP.setBuffer(soundEatGhost);
	soundChompP.setBuffer(soundChomp);
	soundGameP.setBuffer(soundGame);

	soundIntroP.setLoop(true);
	soundIntroP.play();

	bool start = false;

	youWinImage.loadFromFile("youwin.png");
	gameOverImage.loadFromFile("gameover.png");
	menuImage.loadFromFile("pacmenu.png");
	youWin.setTexture(youWinImage);
	gameOver.setTexture(gameOverImage);
	menu.setTexture(menuImage);
	youWin.setScale(420 / youWinImage.getSize().x + 0.88, 465 / youWinImage.getSize().y + 0.1);
	gameOver.setScale(420 / youWinImage.getSize().x + 0.88, 465 / youWinImage.getSize().y + 0.1);
	menu.setScale(0.72, 0.8);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();
		window.draw(menu);
		window.display();
		if (Keyboard::isKeyPressed(Keyboard::Enter)) start = true;
		if (start == true) break;
	}
	
	if (start == true){

		soundIntroP.pause();
		soundGameP.setVolume(10);
		soundGameP.setLoop(true);
		soundGameP.play();

		Clock tik, tik2;

		// run the program as long as the window is open
		while (window.isOpen())
		{

			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
			}

			// clear the window with black color
			window.clear(sf::Color::Black);

			// update
			player_update(tik);

			Time time;
			time = tik.getElapsedTime();
			if (time.asSeconds() > 7) checkHero = false;
			if (checkHero == true){
				player.setColor(Color(255, 85, 255));
				playerVer.setColor(Color(255, 85, 255));
				ghost1.setColor(Color(50, 255, 255));
				ghost2.setColor(Color(50, 255, 255));
				ghost3.setColor(Color(50, 255, 255));
				ghost4.setColor(Color(50, 255, 255));
				ghost5.setColor(Color(50, 255, 255));
				ghost6.setColor(Color(50, 255, 255));

				if (abs(player_pos.x - ghost_pos1.x)<5 && abs(player_pos.y - ghost_pos1.y)<5){
					soundEatGhostP.play();
					ghost_pos1 = Vector2f(180, 210);
					ghost_dir[0] = UP;
				}
				else if (abs(player_pos.x - ghost_pos2.x)<5 && abs(player_pos.y - ghost_pos2.y)<5) {
					soundEatGhostP.play();
					ghost_pos2 = Vector2f(195, 210);
					ghost_dir[1] = UP;
				}
				else if (abs(player_pos.x - ghost_pos3.x)<5 && abs(player_pos.y - ghost_pos3.y)<5) {
					soundEatGhostP.play();
					ghost_pos3 = Vector2f(210, 210);
					ghost_dir[2] = UP;
				}
				else if (abs(player_pos.x - ghost_pos4.x)<5 && abs(player_pos.y - ghost_pos4.y)<5){
					soundEatGhostP.play();
					ghost_pos4 = Vector2f(225, 210);
					ghost_dir[3] = UP;
				}
				else if (abs(player_pos.x - ghost_pos5.x)<5 && abs(player_pos.y - ghost_pos5.y)<5){
					soundEatGhostP.play();
					ghost_pos5 = Vector2f(165, 210);
					ghost_dir[4] = UP;
				}
				else if (abs(player_pos.x - ghost_pos6.x)<5 && abs(player_pos.y - ghost_pos6.y)<5){
					soundEatGhostP.play();
					ghost_pos6 = Vector2f(240, 210);
					ghost_dir[5] = UP;
				}

			}
			else {
				player.setColor(Color::Yellow);
				playerVer.setColor(Color::Yellow);
				ghost1.setColor(Color::White);
				ghost2.setColor(Color::White);
				ghost3.setColor(Color::White);
				ghost4.setColor(Color::White);
				ghost5.setColor(Color::White);
				ghost6.setColor(Color::White);
			}

			if (tik2.getElapsedTime().asSeconds() < 5) startToMove = false;
			else startToMove = true;
			cout << tik2.getElapsedTime().asSeconds() << "\n";
			if (startToMove == true){
				ghost_move(ghost_pos5, ghost_dir[4]);
			}
			if (tik2.getElapsedTime().asSeconds() < 10) startToMove = false;
			else startToMove = true;
			cout << tik2.getElapsedTime().asSeconds() << "\n";
			if (startToMove == true){
				ghost_move(ghost_pos1, ghost_dir[0]);
			}
			if (tik2.getElapsedTime().asSeconds() < 15) startToMove = false;
			else startToMove = true;
			cout << tik2.getElapsedTime().asSeconds() << "\n";
			if (startToMove == true){
				ghost_move(ghost_pos2, ghost_dir[1]);
			}
			if (tik2.getElapsedTime().asSeconds() < 20) startToMove = false;
			else startToMove = true;
			cout << tik2.getElapsedTime().asSeconds() << "\n";
			if (startToMove == true){
				ghost_move(ghost_pos3, ghost_dir[2]);
			}
			if (tik2.getElapsedTime().asSeconds() < 25) startToMove = false;
			else startToMove = true;
			cout << tik2.getElapsedTime().asSeconds() << "\n";
			if (startToMove == true){
				ghost_move(ghost_pos4, ghost_dir[3]);
			}
			if (tik2.getElapsedTime().asSeconds() < 30) startToMove = false;
			else startToMove = true;
			cout << tik2.getElapsedTime().asSeconds() << "\n";
			if (startToMove == true){
				ghost_move(ghost_pos6, ghost_dir[5]);
			}

			if (check_PlayerWin() == true){
				Sleep(1000);
				window.draw(youWin);
				window.display();
				Sleep(2000);
				return 0;
			}

			if (checkGameIsOver(checkHero)){
				soundDeathP.play();
				Sleep(1000);
				window.draw(gameOver);
				window.display();
				Sleep(2000);
				return 0;
			}

			// draw everything here...
			Map_draw();
			fruit_draw();
			ghost_draw();
			player_draw(player_dir);
			// end the current frame
			window.display();
		}
	}

	return 0;
}