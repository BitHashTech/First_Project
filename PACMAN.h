/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED

#include "GUN.h"


struct PacMan
{
    char shape ;
    pair < int , int > position ;
    string direction ;
    string last_direction ;
    int Delay_shot ;
    void get_shape() ;/// direction shape

    bool isValidPos(int y) ;

    void teleport(curser &Curser_ , Map &map_) ;

    void movePlayer( string &temp_direction , Map &map_ ,player &player1_, curser &Curser_ ) ; /// if valid move

};


#endif // PACMAN_H_INCLUDED
