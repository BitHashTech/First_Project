/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#ifndef GUN_H_INCLUDED
#define GUN_H_INCLUDED

#include "MAP.h"

struct GUN {
    char shape ;
    pair < int , int > position ;
    string direction ;
    int color ;
    string owner ;
    bool valid_move( Map &map_ ) ;
    bool move_shot ( Map &map_ ) ;
};

#endif // GUN_H_INCLUDED
