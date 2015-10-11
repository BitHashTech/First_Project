/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***        first year project       ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#ifndef THEGAME_H_INCLUDED
#define THEGAME_H_INCLUDED

#include "GHOST.h"


struct The_Game
{
    bool is_valid_move (string &temp_direction ,  Map &map_ , PacMan &PacMan_ );

    void getKey_move(PacMan &PacMan_ , Map &map_ , player &player1_ ,curser &Curser_ ,vector < GUN > &SHOTS) ;/// get the key from the player and apply movePlayer

    void CLEAR_SHOTS(curser &Curser_ , Map &map_ , vector < GUN >  &SHOTS , vector < Ghosts > &ghosts ) ;

    void set_game(curser &Curser_ , PacMan &PacMan_ , vector < Ghosts > &ghosts , Map &map_ , vector < GUN> &SHOTS) ; /// when player loses a life reset the game

    void display_score(curser &Curser_s , player &player1_) ; /// show the score

    bool win(player &player1_ , curser &Curser_) ; /// check if in a win situation

    bool comp(player p1 , player p2 ) ;/// for the sort function

    void Sort(vector < player >&List ) ; /// to sort high scores

    void get_high_score(); /// show high scores

    void update_high(curser &Curser_ , player &player1_) ; /// update high scores file

    int get_game(curser &Curser_ ) ; /// choose level

    int is_dead(PacMan &PacMan_ , vector < Ghosts > &ghosts , curser &Curser_ , Map &map_
                , player &player1_ ,GUN &SHOT, vector < GUN > &SHOTS) ;
     /// check if dead or eating enemy

    bool init_game(curser &Curser_ , Map &map_ , PacMan &PacMan_ , vector < Ghosts > &ghosts , vector < GUN > &SHOTS) ; /// init every level

    void move_enemy(curser &Curser_ , vector < Ghosts > &ghosts , Map &map_  , PacMan &PacMan_ , vector < GUN > &SHOTS ) ;/// smart enemy or random one

    void back_to_menu(curser &Curser_ ) ;/// after finishing a level

    void clean_option(curser &Curser_) ; /// clean the pause and exit part

    int move_fires(curser &Curser_ ,Map &map_ , PacMan &PacMan_ , vector <Ghosts >&ghosts , vector < GUN > &SHOTS ,player &player1_);

    void game_loop(curser &Curser_ , Map &map_ , PacMan &PacMan_ , vector < Ghosts > &ghosts , player &player1_, vector < GUN > &SHOTS) ; /// move and check in win

    void instructions() ; /// instructions part

    void credits() ;/// credits part

    void Exit() ; /// Exit part

    void play(player &player1_ , curser &Curser_ , PacMan &PacMan_ , vector < Ghosts > &ghosts , Map &map_, vector < GUN > &SHOTS) ; /// get game loop

    void show_options() ; /// show menu

    void menu(player &player1_ , curser &Curser_  , PacMan &PacMan_ , vector < Ghosts > &ghosts , Map &map_ , vector < GUN > &SHOTS) ; /// take choice from the player

    void make_game() ;

};
///
#endif // THEGAME_H_INCLUDED
