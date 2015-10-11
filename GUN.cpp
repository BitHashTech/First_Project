/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#include "GUN.h"


bool GUN::valid_move( Map &map_ ) {
    if ( map_.map[position.first][position.second] == SYMBOL_WALL ||  map_.map[position.first][position.second] == SYMBOL_DOOR )
        return true ;
   if ( position.second == -1 )
        position.second = MapDy-1 ;
    else if ( position.second == MapDy)
        position.second = 0 ;
    return false ;
}
bool GUN::move_shot ( Map &map_ ) {
    if ( direction == "up" )
    {
        position.first-- ;
        if ( valid_move(  map_ ) )
            return false ;
    }
    else if ( direction  == "down" )
    {
        position.first++ ;
        if ( valid_move( map_) )
            return false ;
    }
    else if ( direction == "right" )
    {
        position.second++ ;
        if ( valid_move( map_) )
            return false ;
    }
    else
    {
        position.second-- ;
        if ( valid_move(map_) )
            return false ;
    }
    return true ;
}
