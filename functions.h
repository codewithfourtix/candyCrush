#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;


int pointPerMatch = 0;

const int row = 5;
const int col = 5;
const int cell_size = 70;
const int total_textures = 6;
const int special_textures = 2;
Vector2i suggested_move(-1, -1);

int candies[row][col] = { {0 } };
bool assigned_toBurst[row][col] = { {false} };

Font candyFont;

bool isLoss = false;
bool isWin = false;
int target = 1000;
int score1 = 0;
int prevScore1 = 0;
int moves = 20;

Texture textures[total_textures];
Texture specialTextures[special_textures];

RenderWindow window(VideoMode(1398, 896), "Candy Crush Saga", Style::Close);

Sprite sprite;
Clock clock1;
int timer = 30;

int mid_x = 400;
int mid_y = 150;

int breakTimeout = 30;
bool breakTimeoutActive = false;

Text scoretext;
Text movestext;
Text timertext;

bool SpecialCandy = false;
bool SpecialCandy_1 = false;
bool rowStripeCandy = false;
bool colStripeCandy = false;

bool sweet = false, tasty = false, divine = false, delicious = false;

Vector2i selectedtile(-1, -1);

void loadGame(int candies[row][col], int& score, int& moves) {
    std::ifstream game_saver("load.txt");
    if (game_saver.is_open()) {
        game_saver >> score >> moves;
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                game_saver >> candies[i][j];
            }
        }
        if (moves <= 0) {
            moves = 20;
            score = 0;
        }
        game_saver.close();
    }
    else {
        std::cerr << "No file found." << std::endl;
    }
}

void saveGame(int candies[row][col], int score, int moves) {
    std::ofstream game_loader("load.txt");
    if (game_loader.is_open()) {
        game_loader << score << " " << moves << "\n";
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                game_loader << candies[i][j] << " ";
            }
            game_loader << "\n";
        }
        game_loader.close();
    }
    else {
        std::cerr << "Error faced during file opening!" << std::endl;
    }
}


void loadtextures() {
    int i = 0;
    while (i < total_textures) {
        Texture candytexture;
        char file_nam[60];
        sprintf_s(file_nam, "assests/candies/%d.png", i + 1);

        if (candytexture.loadFromFile(file_nam)) {
            cout << "Candy texture " << i + 1 << " succeeds" << endl;
            textures[i] = candytexture;
            ++i;
        }
        else {
            cout << "Error occurred during candy_texture loading " << i + 1 << endl;
            exit(1);
        }
    }
    int j = 0;
    while (j < special_textures) {
        Texture candytexture;
        char file_nam[60];
        sprintf_s(file_nam, "assests/Special1/%d.png", j + 1);

        if (candytexture.loadFromFile(file_nam)) {
            cout << "Special texture " << j + 1 << " loaded successfully." << endl;
            specialTextures[j] = candytexture;
            ++j;
        }
        else {
            cout << "Error occurred during special_texture loading " << j + 1 << "." << endl;
            exit(1);
        }
    }
}
//void initializegrid()
//{
//    srand(time(0));
//    for (int i = 0; i < row; ++i)
//    {
//        for (int j = 0; j < col; ++j)
//        {
//            while ((j >= 2 && candies[i][j] == candies[i][j - 1] && candies[i][j - 1] == candies[i][j - 2]) ||
//                (i >= 2 && candies[i][j] == candies[i - 1][j] && candies[i - 1][j] == candies[i - 2][j]) )
//            {
//                candies[i][j] = time(0) % total_textures;
//            }
//        }
//    }
//}
void initializegrid()
{
    srand(time(0));
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            int value;
            do {
                value = rand() % total_textures;
            } while ((j>=2 && candies[i][j-1] == value) || (i <= 2 && candies[i-2][j]==candies[i-1][j] == value));
            candies[i][j] = value;
            if (j >= 2 && candies[i][j - 2] == candies[i][j - 1] == value) {
                break;
            }
            if (i >= 2 && candies[i - 2][j] == candies[i - 1][j] == value) {
                break;
            }
        }
    }
}

int valid_swap(int row1, int col1, int row2, int col2)
{
    if (abs(row1 - row2) > 1 || abs(col1 - col2) > 1 || abs(row1 - row2) == abs(col1 - col2)) return 0;
    swap(candies[row1][col1], candies[row2][col2]);
    int result = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            //L Shape checking
            if ( i < row-2 && j < col-2 && candies[i][j] == candies[i + 1][j] && candies[i][j] == candies[i + 2][j] && candies[i][j] == candies[i + 2][j + 1] && candies[i][j] == candies[i + 2][j + 2]) {
                result = 1;
                break;
            }
            //-| shape checking
            if ( i < row-2 && j < col-2 &&candies[i][j] == candies[i][j+1] && candies[i][j] == candies[i][j+2] && candies[i][j+2] == candies[i+1][j+2] && candies[i+2][j+2] == candies[i+2][j+2]) {
                result = 1;
                break;
            }
            //5 matches horizontal 
            if (j == 0 && candies[i][j] == candies[i][j + 1] && candies[i][j+1] == candies[i][j+2] && candies[i][j + 2] == candies[i][j + 3] && candies[i][j + 3] == candies[i][j + 4]) {
                result = 1;
                break;
            }
            //5 matches vertical 
            if (i == 0 && candies[i][j] == candies[i+1][j] && candies[i+1][j] == candies[i+2][j] && candies[i+2][j] == candies[i+3][j] && candies[i+3][j] == candies[i+4][j]) {
                result = 1;
                break;
            }
            // 4 matches horizontal 
            if (j < col - 1 && candies[i][j] == candies[i][j + 1] && candies[i][j + 1] == candies[i][j + 2] && candies[i][j + 2] == candies[i][j + 3]) {
                result = 1;
                break;
            }
            // 4 matches vertical
            if (i < row-1 && candies[i][j] == candies[i + 1][j] && candies[i + 1][j] == candies[i + 2][j] && candies[i + 2][j] == candies[i + 3][j]) {
                result = 1;
                break;
            }
             //forward row
            if (j < col - 2 && candies[i][j] == candies[i][j + 1] && candies[i][j] == candies[i][j + 2]) {
                result = 1;
                break;
            }
            //backward row
            if (j > 1 && candies[i][j] == candies[i][j - 1] && candies[i][j - 1] == candies[i][j - 2]) {
                result = 1;
                break;
            }
            //column downward
            if (i < row - 2 && candies[i][j] == candies[i + 1][j] && candies[i][j] == candies[i + 2][j]) {
                result = 1;
                break;
            }
            // column upward
            if (i > 1 && candies[i][j] == candies[i - 1][j] && candies[i - 1][j] == candies[i - 2][j]) {
                result = 1;
                break;
            }
            
        }
    }

    swap(candies[row1][col1], candies[row2][col2]);

    return result;

}


int row_col_matching() {
    pointPerMatch = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            //-| shape 
            if (i < row - 2 && j < col - 2 && candies[i][j] == candies[i][j + 1] && candies[i][j+1] == candies[i][j + 2] && candies[i][j+2] == candies[i + 1][j + 2] && candies[i+1][j+2] == candies[i + 2][j + 2]
                && assigned_toBurst[i][j] == false && assigned_toBurst[i][j + 1] == false && assigned_toBurst[i][j + 2] == false && assigned_toBurst[i + 1][j + 2] == false && assigned_toBurst[i + 2][j + 2] == false) {
                assigned_toBurst[i][j] = assigned_toBurst[i][j + 1] = assigned_toBurst[i][j + 2] = assigned_toBurst[i + 1][j + 2] = assigned_toBurst[i + 2][j + 2] = true;
                SpecialCandy = true; 
                breakTimeoutActive = true;
                delicious = true;
                pointPerMatch = 50;
            }
            // L shape 
            if (i < row - 2 && j < col - 2 && candies[i][j] == candies[i + 1][j] && candies[i + 1][j] == candies[i + 2][j] && candies[i + 2][j] == candies[i + 2][j + 1] && candies[i + 2][j + 1] == candies[i + 2][j + 2] && assigned_toBurst[i][j] == false && assigned_toBurst[i + 1][j] == false && assigned_toBurst[i + 2][j] == false && assigned_toBurst[i + 2][j + 1] == false && assigned_toBurst[i + 2][j + 2] == false) {
                assigned_toBurst[i][j] = assigned_toBurst[i+1][j] = assigned_toBurst[i+2][j] = assigned_toBurst[i + 2][j + 1] = assigned_toBurst[i + 2][j + 2] = true;
                SpecialCandy = true;
                breakTimeoutActive = true;
                delicious = true;
                pointPerMatch = 40;
            }
            //horizntal
            if (j < col - 2 && candies[i][j] == candies[i][j + 1] && candies[i][j + 1] == candies[i][j + 2]
                && assigned_toBurst[i][j] == false && assigned_toBurst[i][j + 1] == false && assigned_toBurst[i][j + 2] == false) {
                if (j < col - 3 && candies[i][j] == candies[i][j + 3]
                    && assigned_toBurst[i][j + 3] == false) {
                    if (j < col - 4 && candies[i][j] == candies[i][j + 4]
                        && assigned_toBurst[i][j + 4] == false) {
                        assigned_toBurst[i][j] = assigned_toBurst[i][j + 1] = assigned_toBurst[i][j + 2] = assigned_toBurst[i][j + 3] = assigned_toBurst[i][j + 4] = true;
                        SpecialCandy_1 = true; breakTimeoutActive = true;
                        divine = true;
                        pointPerMatch = 80;
                    }
                    else {

                        assigned_toBurst[i][j] = assigned_toBurst[i][j + 1] = assigned_toBurst[i][j + 2] = assigned_toBurst[i][j + 3] = true;
                        breakTimeoutActive = true;
                        rowStripeCandy = true;
                        tasty = true;
                        pointPerMatch = 40;
                    }
                }
                else {
                    assigned_toBurst[i][j] = assigned_toBurst[i][j + 1] = assigned_toBurst[i][j + 2] = true;
                    breakTimeoutActive = true;
                    sweet = true;
                    pointPerMatch = 20;
                }
            }
            //vertical
            if (i < row - 2 && candies[i][j] == candies[i + 1][j] && candies[i + 1][j] == candies[i + 2][j]
                && assigned_toBurst[i][j] == false && assigned_toBurst[i + 1][j] == false && assigned_toBurst[i + 2][j] == false) {
                if (i < row - 3 && candies[i][j] == candies[i + 3][j]
                    && assigned_toBurst[i + 3][j] == false) {
                    if (i < row - 4 && candies[i][j] == candies[i + 4][j]
                        && assigned_toBurst[i + 4][j] == false) {
                        assigned_toBurst[i][j] = assigned_toBurst[i + 1][j] = assigned_toBurst[i + 2][j] = assigned_toBurst[i + 3][j] = assigned_toBurst[i+4][j] = true;
                        SpecialCandy_1 = true; breakTimeoutActive = true;
                        divine = true;
                        pointPerMatch = 80;
                    }
                    else {
                        assigned_toBurst[i][j] = assigned_toBurst[i + 1][j] = assigned_toBurst[i + 2][j] = assigned_toBurst[i + 3][j] = true;
                        breakTimeoutActive = true;
                        colStripeCandy = true;
                        delicious = true;
                        pointPerMatch = 40;
                    }
                }
                else {
                    assigned_toBurst[i][j] = assigned_toBurst[i + 1][j] = assigned_toBurst[i + 2][j] = true;
                    breakTimeoutActive = true;
                    tasty = true;
                    pointPerMatch = 20;
                }
            }
            

        }
    }
    score1 += pointPerMatch;
    return breakTimeoutActive;
}
void scoreText_updation(Text& scoreText) {
    char scorestorage[15];
    const int s = score1;
    snprintf(scorestorage, sizeof(scorestorage), "Score: %d", s);
    scoreText.setString(scorestorage);
}

void movesText_updation(Text& movesText) {
    char movesstorage[30];
    snprintf(movesstorage, sizeof(movesstorage), "Moves: %d", moves);
    movesText.setString(movesstorage);
}

void TimerText_updation(Text& timertext) {

    int time_left = timer - static_cast<int>(clock1.getElapsedTime().asSeconds());
    char timerstorage[30];
    snprintf(timerstorage, sizeof(timerstorage), "Timer: %d", time_left);
    timertext.setString(timerstorage);
}

bool HINT(Vector2i& suggested_move, Vector2i& selectedtile) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {

            if (valid_swap(selectedtile.y, selectedtile.x, i, j)) {
                suggested_move.x = j;
                suggested_move.y = i;
                //when suggested move happens, it stops
                return true;
            }
        }
    }
    //No valid move is found
    return false;
}

bool isAnyMoveValid() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i > 0) { if (valid_swap(i, j, i - 1, j)) return true; }
            if (i < 4) { if (valid_swap(i, j, i + 1, j)) return true; }
            if (j > 0) { if (valid_swap(i, j, i, j - 1)) return true; }
            if (i > 0) { if (valid_swap(i, j, i, j + 1)) return true; }
        }
    }
    return false;
}

void shuffleBoard() {

    int sumcandies[special_textures + total_textures] = { 0 };
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            sumcandies[candies[i][j]]++;
        }
    }
    int random_Candy;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            do {
                random_Candy = rand() % (special_textures + total_textures);
            } while (sumcandies[random_Candy] <= 0);
            candies[i][j] = random_Candy;
            sumcandies[random_Candy]--;
        }
    }
}

void sameCandies_bursting() {
    int burstcount = 0;
    //already done our swapping process. Just to mark that candies about it
    for (int i = row - 1; i >= 0; --i)
    {
        for (int j = 0; j < col; ++j) {
            if (assigned_toBurst[i][j]) {
                if (i == 0) {
                    candies[i][j] = rand() % total_textures;
                }
                else {
                    candies[i][j] = -1;
                }
                assigned_toBurst[i][j] = false;
                ++burstcount;
            }
        }
    }
    cout << "BURST COUNT " << burstcount << endl;
    for (int i = row - 1; i >= 0; --i) {
        for (int j = 0; j < col; ++j) {
            if (candies[i][j] == -1) {
                for (int k = i; k >= 0; k--) {
                    if (candies[k][j] != -1) {
                        if (SpecialCandy_1 == true) {

                            candies[i][j] = 7;
                            if (moves != 20) score1 += 10;
                            scoreText_updation(scoretext);
                            assigned_toBurst[i][j] = true;
                            breakTimeout = 30;
                            breakTimeoutActive = true;
                            SpecialCandy_1 = false;

                            //row column bursting
                            //row bursting
                            for (int k = 0; k < col; k++) {
                                assigned_toBurst[i][k] = true;
                            }
                            //column bursting
                            for (int k = 0; k < row; k++) {
                                assigned_toBurst[k][j] = true;
                            }
                            break;
                        }

                        else if (SpecialCandy == true) {
                            candies[i][j] = 6;
                            if (moves != 20) score1 += 5;
                            scoreText_updation(scoretext);
                            //bursting of 3 by 3 region
                            assigned_toBurst[i][j] = true;
                            breakTimeout = 30;
                            breakTimeoutActive = true;
                            //above row
                            if (i > 0) {
                                assigned_toBurst[i - 1][j] = true;
                                if (j > 0) {
                                    assigned_toBurst[i - 1][j - 1] = true;
                                }
                                if (j < row - 1) {
                                    assigned_toBurst[i - 1][j + 1] = true;
                                }
                            }
                            //below row
                            if (i < col - 1) {
                                assigned_toBurst[i + 1][j] = true;
                                if (j > 0) {
                                    assigned_toBurst[i + 1][j - 1] = true;
                                }
                                if (j < row - 1) {
                                    assigned_toBurst[i + 1][j + 1] = true;
                                }
                            }
                            //row in which special candy is present
                            if (j > 0) {
                                assigned_toBurst[i][j - 1] = true;
                            }
                            if (j < row - 1) {
                                assigned_toBurst[i][j + 1] = true;
                            }
                            SpecialCandy = 0;
                            break;
                        }
                        else {
                            candies[i][j] = candies[k][j];
                            candies[k][j] = -1;
                            break;
                        }
                    }
                    if (candies[i][j] == -1) {
                        candies[i][j] = rand() % total_textures;
                    }
                }
            }
        }
    }
}