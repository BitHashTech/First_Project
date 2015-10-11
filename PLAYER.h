/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***        first year project       ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "CURSER.h"


struct player
{
    string name ;
    int score_food ;
    int score_ghosts ;
    int bonus_score ;
    int total_score ;
    void getname(curser &Curser_) ; /// the name of the player

} ;


#endif // PLAYER_H_INCLUDED
