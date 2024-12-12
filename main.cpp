#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cmath>
#include "functions.h"


using namespace std;
using namespace sf;

int main()
{
	//main menu implementation 
	RectangleShape startButton(Vector2f(200, 50));
	startButton.setPosition(300, 200);
	startButton.setFillColor(Color::Blue);

	RectangleShape loadButton(Vector2f(200, 50));
	loadButton.setPosition(300, 300);
	loadButton.setFillColor(Color::Green);

	RectangleShape credits(Vector2f(200, 50));
	credits.setPosition(300, 400);
	credits.setFillColor(Color::Magenta);

	RectangleShape howToPlay(Vector2f(200, 50));
	howToPlay.setPosition(300, 500);
	howToPlay.setFillColor(Color::Blue);

	RectangleShape exitButton(Vector2f(200, 50));
	exitButton.setPosition(300, 600);
	exitButton.setFillColor(Color::Red);

	RectangleShape backButton(sf::Vector2f(200.0f, 50.0f));
	backButton.setPosition(100.0f, 850.0f);
	backButton.setFillColor(sf::Color::Red);



	if (!candyFont.loadFromFile("assests/font/candyfont.ttf")) {
		cout << "Error loading font" << endl;
		return -1;
	}

	Text startText, loadText, exitText, creditsText, howToPlayText, backText;
	startText.setFont(candyFont);
	startText.setString("Start Game");
	startText.setCharacterSize(24);
	startText.setPosition(330, 210);

	loadText.setFont(candyFont);
	loadText.setString("Load Game");
	loadText.setCharacterSize(24);
	loadText.setPosition(330, 310);

	creditsText.setFont(candyFont);
	creditsText.setString("Credits");
	creditsText.setCharacterSize(24);
	creditsText.setPosition(330, 410);

	howToPlayText.setFont(candyFont);
	howToPlayText.setString("How to Play");
	howToPlayText.setCharacterSize(24);
	howToPlayText.setPosition(330, 510);

	exitText.setFont(candyFont);
	exitText.setString("Exit");
	exitText.setCharacterSize(24);
	exitText.setPosition(330, 610);

	backText.setFont(candyFont);
	backText.setString("Back");
	backText.setCharacterSize(24);
	backText.setFillColor(sf::Color::White);
	backText.setPosition(120.0f, 860.0f);

	//main menu booleans 
	bool isMainMenu = true;
	bool isLoadGame = false;
	bool isCreditsVisible = false;
	bool isHowToPlay = false;
	//end of main menu implementation

	loadtextures();
	initializegrid();
	// game(score1, moves);

	Texture backgroundtexture;
	if (!backgroundtexture.loadFromFile("assests/background/back1.jpg")) {
		cout << "Error occurred while loading background image." << endl;
		return 1;
	}
	Texture creditTexture;
	if (!creditTexture.loadFromFile("assests/credits/credit.png")) {
		cout << "Error occured while loading the credits image" << endl;
		return 1;
	}
	Texture howToPlayTexture;
	if (!howToPlayTexture.loadFromFile("assests/howtoplay/howtoplay.png")) {
		cout << "Error occured while loading the how to play texture " << endl;
		return 1;
	}

	Texture celltexture;
	if (!celltexture.loadFromFile("assests/background/cell.png")) {
		cout << "Error occurred while loading cell image." << endl;
		return 1;
	}
	Texture winTexture;
	if (!winTexture.loadFromFile("assests/winscreen/winscreen.png")) {
		cout << "Error while loading win screen" << endl;
		return 1;
	}
	Texture lossTexture;
	if (!lossTexture.loadFromFile("assests/lossscreen/lossscreen.png")) {
		cout << "Error loading loss screen texture" << std::endl;
		return 1;
	}

	//MUSIC 
	Music mainMenuMusic;
	if (!mainMenuMusic.openFromFile("assests/music/mainmenumusic.mp3")) {
		cout << "Could not load music" << endl;
	}
	mainMenuMusic.setLoop(true); // Ensure the music loops
	mainMenuMusic.play(); // Start playing the music

	Music startGameMusic;
	if (!startGameMusic.openFromFile("assests/music/startgamemusic.MP3")) {
		cout << "Could not load start game music" << endl;
	}
	startGameMusic.setLoop(true);

	Music loadGameMusic;
	if (!loadGameMusic.openFromFile("assests/music/loadgamemusic.MP3")) {
		cout << "Could not load load game music" << endl;
	}
	loadGameMusic.setLoop(true);

	Music winMusic;
	if (!winMusic.openFromFile("assests/music/win.MP3")) {
		cout << "Could not load win music" << endl;
	}

	Music msweet, mdivine, mtasty, mdelicious;
	if (!msweet.openFromFile("assests/music/sweet.MP3")) {
		cout << "Could not open sweet music" << endl;
	}
	if (!mdivine.openFromFile("assests/music/divine.MP3")) {
		cout << "Could not open divine music" << endl;
	}
	if (!mtasty.openFromFile("assests/music/tasty.MP3")) {
		cout << "Could not open tasty music" << endl;
	}
	if (!mdelicious.openFromFile("assests/music/delicious.MP3")) {
		cout << "Could not open delicious music" << endl;
	}
	

	//background
	RectangleShape background(Vector2f(1400.0f, 900.0f));
	background.setTexture(&backgroundtexture);

	const float candysize = 60.0f;
	float candyscale = candysize / static_cast<float>(textures[0].getSize().x);

	//score
	scoretext.setFont(candyFont);
	scoretext.setCharacterSize(30);
	scoretext.setFillColor(Color::Black);
	scoretext.setPosition(10, 75);

	//moves
	movestext.setFont(candyFont);
	movestext.setCharacterSize(30);
	movestext.setFillColor(Color::Black);
	movestext.setPosition(10, 125);

	//timer
	timertext.setFont(candyFont);
	timertext.setCharacterSize(30);
	timertext.setFillColor(Color::Black);
	timertext.setPosition(10, 175);

	//credits shape rectangle 
	RectangleShape creditsPage(Vector2f(1200.0f, 750.0f));
	creditsPage.setTexture(&creditTexture);
	creditsPage.setPosition(100.0f, 75.0f); // Position it in the center with padding

	//how to play shape rectangle 
	RectangleShape howToPlayPage(Vector2f(1200.0f, 750.0f));
	howToPlayPage.setTexture(&howToPlayTexture);
	howToPlayPage.setPosition(100.0f, 75.0f); // center 

	RectangleShape winPage(Vector2f(400.0f, 200.0f));
	winPage.setTexture(&winTexture);
	winPage.setPosition(499.0f, 348.0f);

	RectangleShape lossScreen(Vector2f(400.0f, 200.0f));
	lossScreen.setTexture(&lossTexture); // Set the color to red or any desired color
	lossScreen.setPosition(499.0f, 348.0f);

	//Hint button
	RectangleShape hintButton(Vector2f(70.0f, 50.0f));
	hintButton.setFillColor(Color::Red);
	hintButton.setPosition(1230, 30);

	//save button
	RectangleShape saveButton(Vector2f(140.0f, 50.0f));
	saveButton.setFillColor(Color::Blue);
	saveButton.setPosition(1230, 80);

	RectangleShape bButton(sf::Vector2f(140.0f, 50.0f));
	bButton.setFillColor(sf::Color::Red);
	bButton.setPosition(1230, 130);
	//savegame button
	/*RectangleShape button2(Vector2f(140.0f, 50.0f));
	button2.setFillColor(Color::Green);
	button2.setPosition(1230, 130);*/

	//text of hint
	Text bText;
	bText.setFont(candyFont);
	bText.setCharacterSize(24);
	bText.setFillColor(Color::Black);
	bText.setString("Back");
	bText.setPosition(bButton.getPosition().x + 10, bButton.getPosition().y + 10);

	Text hintText;
	hintText.setFont(candyFont);
	hintText.setCharacterSize(24);
	hintText.setFillColor(Color::Black);
	hintText.setString("Hint");
	hintText.setPosition(hintButton.getPosition().x + 10, hintButton.getPosition().y + 10);

	//text of save_game 
	Text saveButtonText;
	saveButtonText.setFont(candyFont);
	saveButtonText.setCharacterSize(24);
	saveButtonText.setFillColor(Color::Black);
	saveButtonText.setString("Save Game");
	saveButtonText.setPosition(saveButton.getPosition().x + 10, saveButton.getPosition().y + 12);

	//text of load_game
	/*Text butn2text;
	butn2text.setFont(candyFont);
	butn2text.setCharacterSize(24);
	butn2text.setFillColor(Color::Black);
	butn2text.setString("Load Game");
	butn2text.setPosition(button2.getPosition().x + 10, button2.getPosition().y + 12);*/


	movesText_updation(movestext);
	scoreText_updation(scoretext);

	RectangleShape cell(Vector2f(cell_size, cell_size));
	cell.setTexture(&celltexture);
	bool hintrequested = false;
	//highlightening
	RectangleShape contrast_light(Vector2f(cell_size, cell_size));
	contrast_light.setOutlineThickness(4);
	contrast_light.setOutlineColor(Color::Black);

	
	//timer
	int timer = 60;
	window.setFramerateLimit(60);
	while (window.isOpen()) {


		//done to avoid sudden increade in score
		if (score1 - prevScore1 < 0 || score1 - prevScore1 > 100) score1 = prevScore1;
		prevScore1 = score1;
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				//game_loader(score1, moves);
				window.close();
				cout << "Game over\n";
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (!breakTimeoutActive && event.mouseButton.button == Mouse::Left) {
					if (isWin) {
						winMusic.play();
						if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isWin = false; 
							isMainMenu = true; 
							score1 = 0; 
							moves = 20; 
							shuffleBoard(); 
						} 
					}
					else if (isLoss) {
						if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isLoss = false;
							isMainMenu = true;
							score1 = 0;
							moves = 20;
							shuffleBoard();
						}
					}
					else if (isMainMenu) {
						if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isMainMenu = false;
							mainMenuMusic.stop();
							startGameMusic.play();
						}
						else if (loadButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isMainMenu = false;
							isLoadGame = true;
							mainMenuMusic.stop();
							startGameMusic.stop();
							loadGameMusic.play();
						}
						else if (credits.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isCreditsVisible = true;
							isMainMenu = false;
						}
						else if (howToPlay.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isMainMenu = false;
							isHowToPlay = true;
						}
						else if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							window.close();
						}
					}
					else if (isCreditsVisible) {
						if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isCreditsVisible = false;
							isMainMenu = true;
							mainMenuMusic.play();
						}
					}
					else if (isHowToPlay) {
						if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isHowToPlay = false;
							isMainMenu = true;
							mainMenuMusic.play();
						}
					}
					else {
						int mouse_x = event.mouseButton.x - mid_x;
						int mouse_y = event.mouseButton.y - mid_y;

						//save game
						if (saveButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
							saveGame(candies, score1, moves);
						}
						else if (bButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							isMainMenu = true;
							startGameMusic.stop();
							mainMenuMusic.play();
							loadGameMusic.stop();
							shuffleBoard();
						}
						//load game
						else if (isLoadGame) {
							loadGame(candies, score1, moves);
							scoreText_updation(scoretext);
							movesText_updation(movestext);
							isLoadGame = false;
						}
						//HINT
						else if (hintButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
							cout << "Button clicked!\n";
							hintrequested = true;
							Vector2i tile;
							suggested_move = { -1,-1 };
							for (int i = 0; i < row; i++) {
								if (suggested_move.x != -1) break;
								for (int j = 0; j < col; j++) {
									if (suggested_move.x != -1) break;
									tile = { i,j };
									HINT(suggested_move, tile);
								}
							}
							cout << suggested_move.x << " " << suggested_move.y;

						}
						else {

							int grid_x = mouse_x / cell_size;
							int grid_y = mouse_y / cell_size;

							//2D array index
							if (grid_x >= 0 && grid_x < col && grid_y >= 0 && grid_y < row) {
								if (selectedtile.x == -1 && selectedtile.y == -1)
									selectedtile = Vector2i(grid_x, grid_y);
								else {
									if (valid_swap(selectedtile.y, selectedtile.x, grid_y, grid_x)) {

										suggested_move = { -1,-1 };
										swap(candies[selectedtile.y][selectedtile.x], candies[grid_y][grid_x]);
										selectedtile = Vector2i(-1, -1);
										row_col_matching();
										if (sweet) {
											msweet.play();
											sweet = false;
										}
										else if (divine) {
											mdivine.play();
											divine = false;
										}
										else if (delicious) {
											mdelicious.play();
											delicious = false;
										}
										else if (tasty) {
											mtasty.play();
											tasty = false;
										}
										sameCandies_bursting();
										score1++;
										clock1.restart();
										scoreText_updation(scoretext);
										moves -= 1;
										movesText_updation(movestext);
										if (score1 > target) {
											isWin = true;
											score1 = 0;
											moves = 20;
											cout << "You won " << endl;
										}
										if (moves == 0) {
											isLoss = true;
											shuffleBoard();
											moves = 20;
											score1 = 0;
											//loadGame(candies, score1, moves);
											cout << "You loss! " << endl;
											cout << "Game over\n";
										}

										if (breakTimeoutActive) {
											if (!isAnyMoveValid()) {
												shuffleBoard();
											}
										}
									}

									else {
										selectedtile = Vector2i(grid_x, grid_y);
									}
								}
							}
						}
					}
				}

			}
		}
		if (isMainMenu) {
			window.clear();
			window.draw(background);
			window.draw(startButton);
			window.draw(loadButton);
			window.draw(exitButton);
			window.draw(howToPlay);
			window.draw(startText);
			window.draw(credits);
			window.draw(creditsText);
			window.draw(howToPlayText);
			window.draw(loadText);
			window.draw(exitText);
			window.display();
		}
		else if (isCreditsVisible) {
			window.clear();
			window.draw(background);
			window.draw(creditsPage);
			window.draw(backButton);
			window.draw(backText);
			window.display();
		}
		else if (isHowToPlay) {
			window.clear();
			window.draw(background);
			window.draw(howToPlayPage);
			window.draw(backButton);
			window.draw(backText);
			window.display();
		}
		else if (isWin) {
			winMusic.play();
			window.clear(); 
			window.draw(background); 
			window.draw(winPage); 
			window.draw(bButton);
			window.draw(bText);
			window.display();
			//continue;
		}
		else if (isLoss) {
			window.clear();
			window.draw(background);
			window.draw(lossScreen);
			window.draw(bButton);
			window.draw(bText);
			window.display();
		}
		else {
			window.clear();
			window.draw(background);

			row_col_matching();
			//means any bursting happens, time pauses
			if (breakTimeoutActive) {
				clock1.restart();
				breakTimeout--;
			}
			else breakTimeout = 30;
			if ((breakTimeoutActive && moves == 20) || breakTimeout == 0) {
				breakTimeoutActive = false;
				breakTimeout = 30;
				sameCandies_bursting();
			}

			/*if (breakTimeoutActive) {
				if (!isAnyMoveValid()) {
					shuffleBoard();
				}
			}*/
			//means any valid move
			if (suggested_move.x != -1 && suggested_move.y != -1)
			{
				contrast_light.setPosition(mid_x + suggested_move.x * cell_size, mid_y + suggested_move.y * cell_size);
				window.draw(contrast_light);
			}

			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j)
				{
					cell.setPosition(mid_x + j * cell_size, mid_y + i * cell_size);
					Color cellcolor = cell.getFillColor();
					cellcolor.a = 170;
					cell.setFillColor(cellcolor);
					//differentiate between special and normal candies
					if (candies[i][j] > 5) {
						sprite.setTexture(specialTextures[candies[i][j] - 6]);
					}
					else {
						sprite.setTexture(textures[candies[i][j]]);
					}

					sprite.setScale(candyscale, candyscale);
					sprite.setPosition(cell.getPosition().x + (cell_size - candysize) / 2, cell.getPosition().y + (cell_size - candysize) / 2);

					// highlight the selected candy
					if (assigned_toBurst[i][j] || (selectedtile.x == j && selectedtile.y == i)) {
						contrast_light.setPosition(cell.getPosition());
						window.draw(contrast_light);
					}

					window.draw(scoretext);
					window.draw(movestext);

				label:
					timer = 30 - static_cast<int>(clock1.getElapsedTime().asSeconds());
					if (timer <= 0) {
						moves -= 1;
						score1 -= 5;
						prevScore1 = score1;
						movesText_updation(movestext);
						scoreText_updation(scoretext);
						TimerText_updation(timertext);
						if (moves <= 0) {
							moves = 0;
							score1 = 0;
							cout << "Game over\n";
							window.close();
						}
						else {
							clock1.restart();
							goto label;
						}
					}
					else {
						TimerText_updation(timertext);
						window.draw(timertext);
						window.draw(timertext);
						window.draw(cell);
					}
					window.draw(sprite);
				}
				//window.draw(hintButton);
				//window.draw(saveButton);
				////window.draw(button2);

				//window.draw(bButton);
				//window.draw(bText);

				//window.draw(hintText);
				//window.draw(saveButtonText);
				////window.draw(butn2text);
			}
			window.draw(hintButton);
			window.draw(saveButton);
			//window.draw(button2);

			window.draw(bButton);
			window.draw(bText);

			window.draw(hintText);
			window.draw(saveButtonText);
			//window.draw(butn2text);
			window.display();
		}
	}
return 0;
}