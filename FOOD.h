/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "PLAYER.h"

struct Food
{
    char shape ;
    void get_power(player &player1_ , curser &Curser_); /// apply foods power
};


#endif // FOOD_H_INCLUDED
