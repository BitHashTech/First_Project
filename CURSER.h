/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#ifndef CURSER_H_INCLUDED
#define CURSER_H_INCLUDED


#include <conio.h>
#include <cstdio>
#include <Windows.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <mmsystem.h>
#include <string>
#include <queue>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;
///
const char SYMBOL_EMPTY = ' ' ;
const char SYMBOL_SUPER = '$' ;
const char SYMBOL_SPACE = '_' ;
const char SYMBOL_DOOR  = '-' ;
const char SYMBOL_WALL  = '#' ;
const char SYMBOL_AT    = '@' ;
const char SYMBOL_FOOD  = '.' ;
const char SYMBOL_ENEMY_NORMAL = char(224) ;
const char SYMBOL_ENEMY_AFRAID = char(126) ;
const char SYMBOL_PLAYER_UP    = char(342) ;
const char SYMBOL_PLAYER_DOWN  = char(350) ;
const char SYMBOL_PLAYER_LEFT  = char(318) ;
const char SYMBOL_PLAYER_RIGHT = char(316) ;
const char SYMBOL_SUPER_WALL   = char(177) ;
const char SYMBOL_ARROW_UP     = char(24)  ;
const char SYMBOL_ARROW_DOWN   = char(25)  ;
const char SYMBOL_ARROW_RIGHT  = char(26)   ;
const char SYMBOL_ARROW_LEFT   = char(27)   ;
const char SYMBOL_STAR  = '*' ;
const char SYMBOL_SMILY_FACE = char(2);
const int score_per_ghost = 20 ;
const int score_per_heart = 40 ;
const int score_per_food  = 1  ;
const int col_pos1 = 23 , col_pos2 = 21 ;
const char SYMBOL_UP = '8' ;
const char SYMBOL_DOWN  = '9' ;
const char SYMBOL_LEFT = '4' ;
const char SYMBOL_RIGHT = '6' ;
const char SHOT_UP   = '|' ;
const char SHOT_RIGHT= '-' ;
const int HEART_NUM  = 3  ;
const int PAC_NUM_END= 219;
const int WALL_NUM1  = 177;
const int WALL_NUM2  = 178;
const int DIAMON_NUM = 4  ;
const int time_Afraid= 20 ;
const int MapDx      = 22 ;
const int MapDy      = 23 ;
const int GameSpeed  = 250;
const int turns_change = 12 ;
const int total_enemy  = 4  ;
const char SYMBOL_SUPER_FOOD  = char(15) ;
const int LASER = -5 ;
const char SYMBOL_NORMAL_FOOD = '.'       ;
const pair < int , int > life_pos1 = {11,12} , life_pos2 = {11,11};
const pair < int , int > positions[4] = { {8,11}, {10,10},{10,11} , {10,12}};
const pair < int , int > Pac_pos[2] = { { 20,11} , {15,11 } } ;
const pair < int , int > SUPER_FOOD[4] = { { 3,1} , {3,21} ,{16,1},{16,21} };
///

struct curser /// move in console
{
    bool STAR_WARS ;
    vector < int > enemy_shapes ;/*** if afraid  1 for afraid 0 for not afraid */  ;
    int  level  ;
    vector < bool > is_super ;
    int  num_of_enemy /** for release */ ,last_life_pos /** hearts position */ , life_ctr  ;
    int  time_afraid /** enemy afraid */ ,turns ;
    ///

    void gotoxy( int x, int y );
};



#endif // CURSER_H_INCLUDED
