/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "FOOD.h"


struct Map
{
    string map[MapDx] ;
    Food foods[MapDx][MapDy] ;

    void clean_map() ;/// initialize the map with nothing

    void read_map(curser &Curser_) ; /// get the map from a file

    void Generate() ;/// put food in food map

    void get_life(curser &Curser_) ; /// randomly put a life in the level

    void showMap(curser &Curser_) ;/// show the map

} ;
#endif // MAP_H_INCLUDED
