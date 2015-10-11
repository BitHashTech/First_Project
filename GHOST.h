/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "PACMAN.h"


struct Ghosts
{
    char shape ;
    string direction ;
    pair < int , int > position ;
    int Delay_shot ;
    int death_ctr ;
    int color ;
    vector < queue < pair < int , int > > > move_sequenses ;

    int temp_map[MapDx][MapDy] ;

    void get_color(int i ) ;/// each enemy has a color

    void clear_temp() ;/// temp map for the smart enemy

    void is_possible(int x , int y , Map &map_ ,curser &Curser_) ;/// check if possible for a move

    void update_shape(int i , curser &Curser_) ;/// if afraid change shape

    void move_random( pair < int ,int > Position , PacMan &PacMan_ , Map &map_ ,curser &Curser_) ; /// random enemy move

    void attack (int ctr_moves , queue < pair < int , int > > temp , pair < int , int > position , Map &map_ ,curser &Curser_ ,PacMan &PacMan_) ; /// smart enemy

    void select_way (int i , Map &map_ , curser &Curser_ ,vector < GUN > &SHOTS); /// if more than one way choose randomly
};

#endif // GHOST_H_INCLUDED
