/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/
/***          Mohamed Yousry         ***/
/***          BitHashTech            ***/
/***       first year project        ***/
/*** @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ***/

#include "THEGAME.h"

bool The_Game::is_valid_move (string &temp_direction ,  Map &map_ , PacMan &PacMan_ )
{
    int x = PacMan_.position.first , y = PacMan_.position.second ;
    if ( temp_direction == "up" )
        x--;
    else if ( temp_direction == "down" )
        x++;
    else if ( temp_direction == "left" )
        y-- ;
    else
        y++;
    char ch = map_.map[x][y];

    if (ch == SYMBOL_WALL || ch == SYMBOL_DOOR )
    {
        return 0 ;
    }
    return 1 ;
}
void The_Game::getKey_move(PacMan &PacMan_ , Map &map_ , player &player1_ ,curser &Curser_ ,vector < GUN > &SHOTS) /// get the key from the player and apply movePlayer
{

    if (GetAsyncKeyState(VK_UP)  )
    {
        PacMan_.direction = "up" ;
    }

    else if (GetAsyncKeyState(VK_DOWN) )
    {
        PacMan_.direction = "down" ;
    }

    else if (GetAsyncKeyState(VK_LEFT) )
    {
        PacMan_.direction = "left";
    }

    else if (GetAsyncKeyState(VK_RIGHT) )
    {
        PacMan_.direction = "right" ;
    }
    if ( !is_valid_move( PacMan_.direction , map_ , PacMan_ ) )
    {
        if ( is_valid_move( PacMan_.last_direction , map_ , PacMan_ ) )
            PacMan_.movePlayer( PacMan_.last_direction , map_ , player1_ , Curser_ ) ;
    }
    else
        PacMan_.movePlayer( PacMan_.direction , map_ , player1_ , Curser_ ) ;

    if ( Curser_.STAR_WARS && GetAsyncKeyState(VK_SPACE) && !PacMan_.Delay_shot) {
        GUN shot ;
        shot.color = -1 ;
        if ( PacMan_.last_direction == "up" || PacMan_.last_direction == "down" )
            shot.shape = SHOT_UP ;
        else
            shot.shape = SHOT_RIGHT ;
        shot.direction = PacMan_.last_direction ;
        shot.position = PacMan_.position ;
        shot.owner = "PLAYER" ;
        PacMan_.Delay_shot = 3 ;
        SHOTS.push_back(shot) ;
    }
    if ( Curser_.STAR_WARS && PacMan_.Delay_shot )
        PacMan_.Delay_shot-- ;
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void The_Game::CLEAR_SHOTS(curser &Curser_ , Map &map_ , vector < GUN >  &SHOTS , vector < Ghosts > & ghosts )
{
    for ( int i = 0 ; i < SHOTS.size() ; i++ )
    {
        if ( map_.foods[SHOTS[i].position.first][SHOTS[i].position.second].shape == HEART_NUM )
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
        else
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
        Curser_.gotoxy(SHOTS[i].position.second,SHOTS[i].position.first);
        cout << map_.foods[SHOTS[i].position.first][SHOTS[i].position.second].shape ;
        SHOTS.erase(SHOTS.begin()+i);
        i--;
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
    for ( int i = 4 ; i < Curser_.num_of_enemy ; i++ )
    {
        Curser_.gotoxy(ghosts[i].position.second,ghosts[i].position.first);
        cout << map_.foods[ghosts[i].position.first][ghosts[i].position.second].shape ;
    }
}

void The_Game::set_game(curser &Curser_ , PacMan &PacMan_ , vector < Ghosts > &ghosts , Map &map_ , vector < GUN > &SHOTS )
/// when player loses a life reset the game
{
    CLEAR_SHOTS(Curser_,map_,SHOTS, ghosts );
    PacMan_.last_direction = PacMan_.direction = "up";
    PacMan_.Delay_shot  = 0 ;
    PacMan_.get_shape();
    Curser_.num_of_enemy = 1;
    Curser_.turns = 0 ;
    Curser_.is_super.resize(4);
    Curser_.is_super[0] = 1;
    Curser_.time_afraid = 0 ;
    PacMan_.position = Pac_pos[(Curser_.level + 1 )%2] ;
    ghosts.resize(4);
    for ( int i = 0 ; i < total_enemy ; i++ )
    {
        ghosts[i].Delay_shot = 0 ;
        ghosts[i].color = i ;
        Curser_.enemy_shapes[i] = 0 ;
        ghosts[i].shape = SYMBOL_ENEMY_NORMAL ;
        if (  map_.foods[ghosts[i].position.first][ghosts[i].position.second].shape == HEART_NUM )
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
        else
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
        Curser_.gotoxy(ghosts[i].position.second,ghosts[i].position.first);
        cout << map_.foods[ghosts[i].position.first][ghosts[i].position.second].shape;
        map_.map[ghosts[i].position.first][ghosts[i].position.second] = map_.foods[ghosts[i].position.first][ghosts[i].position.second].shape ;
        switch ( Curser_.level )
        {
        case 1:
        case 3:
            ghosts[i].position = positions[i];
            ghosts[i].get_color(i);
            Curser_.gotoxy(ghosts[i].position.second,ghosts[i].position.first);
            break;
        default :
            ghosts[i].position =  {positions[i].first-1,positions[i].second};
            ghosts[i].get_color(i);
            Curser_.gotoxy(ghosts[i].position.second,ghosts[i].position.first);
            break;
        }
        cout << ghosts[i].shape ;
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
    Curser_.gotoxy(PacMan_.position.second,PacMan_.position.first);
    cout << PacMan_.shape ;

}

void The_Game::display_score(curser &Curser_ , player &player1_) /// show the score
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
    Curser_.gotoxy(-20,12);
    cout << player1_.name ;
    Curser_.gotoxy(45,10);
    cout << player1_.score_food;
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0x9 );
    Curser_.gotoxy(45,12);
    cout << player1_.score_ghosts;
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0x2 );
    Curser_.gotoxy(45,14);
    cout << player1_.bonus_score;
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xF );
    Curser_.gotoxy(45,16);
    cout << player1_.total_score;

}

bool The_Game::win(player &player1_ , curser &Curser_) /// check if in a win situation
{
    if ( Curser_.STAR_WARS )
        return player1_.total_score >= 500 ;
    if ( player1_.total_score >= 350 || player1_.score_ghosts >= 200 )
        return 1 ;
    switch (Curser_.level)
    {
    case 1:
        return player1_.score_food == 183 ;
    default:
        return player1_.score_food == 161 ;
    }
}

bool The_Game::comp(player p1 , player p2 ) /// for the sort function
{
    if ( p1.total_score > p2.total_score )
        return true ;
    return false ;
}

void The_Game::Sort(vector < player >&List ) /// to sort high scores
{
    for ( int i = 0 ; i < List.size() ; i++ )
    {
        for ( int j = i+1 ; j < List.size() ; j++ )
        {
            if ( comp(List[j],List[i]) )
                swap(List[j],List[i]);
        }
    }
}

void The_Game::get_high_score() /// show high scores
{
    system("CLS");
    ifstream getin("Data\\choose_level.txt");
    string temp ;
    for ( int i = 0 ; i < 15 ; i++ )
        cout << '\n';
    while ( getin >> temp )
    {
        cout << "\t\t\t";
        for ( int i = 0 ; i < temp.size() ; i++ )
        {
            if ( temp[i] == SYMBOL_SPACE )
                cout << SYMBOL_EMPTY ;
            else if ( temp[i] == SYMBOL_AT )
                cout << char(DIAMON_NUM) ;
            else
                cout << temp[i] ;
        }
        cout << endl;
    }
    getin.close();
    char c = getch();
    while ( c != '1' && c != '2' && c != '3' && c != '4')
        c = getch();
    system("CLS");
    ifstream fin;
    switch(c)
    {
    case '1':
        fin.open("Data\\High_Score1.txt");
        break;
    case '3':
        fin.open("Data\\High_Score3.txt");
        break;
    case '4':
        return ;
    default:
        fin.open("Data\\High_Score2.txt");
        break;
    }
    player tmp ;
    int ctr = 1 ;
    cout<<"\n\n\trank"<<setw(15)<<"\t NAME"<<setw(10)<<"   FOOD"<<setw(10)<<"   GHOST"<<setw(10)<<"     TOTAL\n\n";
    while ( getline(fin,tmp.name) )
    {
        fin >> tmp.score_food  >> tmp.score_ghosts >> tmp.total_score ;
        cout << "\t" << ctr <<" -->" << setw(16) << tmp.name << setw(10) << tmp.score_food << setw(10) << tmp.score_ghosts
             <<setw(10)<<  tmp.total_score << endl;
        ctr++;
        fin.ignore();
        cout << "\n\n\n" ;
    }
    if ( ctr == 1 )
    {
        cout << "\n\n\tthere is no scores in this level .. \n\n" << endl;
    }
    fin.close();
    cout << "\t\tPRESS any key to go back to the menu \n";
    getch();
}

void The_Game::update_high(curser &Curser_ , player &player1_) /// update high scores file
{
    ifstream fin ;
    switch ( Curser_.level )
    {
    case 1 :
        fin.open("Data\\High_Score1.txt");
        break;
    case 3:
        fin.open("Data\\High_Score3.txt");
        break;
    default:
        fin.open("Data\\High_Score2.txt");
        break;
    }
    vector < player  > List ;
    player tmp ;
    while ( getline(fin,tmp.name)  )
    {
        fin >> tmp.score_food  >> tmp.score_ghosts >> tmp.total_score ;
        List.push_back(tmp);
        fin.ignore();
    }
    List.push_back(player1_);
    Sort(List);
    fin.close() ;
    ofstream fout ;
    switch ( Curser_.level )
    {
    case 1:
        remove("Data\\High_Score1.txt");
        fout.open("Data\\High_Score1.txt");
        break;
    case 3:
        remove("Data\\High_Score3.txt");
        fout.open("Data\\High_Score3.txt");
        break;
    default:
        remove("Data\\High_Score2.txt");
        fout.open("Data\\High_Score2.txt");
        break;
    }
    for ( int i = 0 ; i < min((int)List.size(),8) ; i++ )
    {
        fout << List[i].name << "\n " << List[i].score_food << " " << List[i].score_ghosts <<" " << List[i].total_score << endl;
    }

}

int The_Game::get_game( curser &Curser_  ) /// choose level
{
    ifstream getin("Data\\choose_level.txt");
    string temp ;
    for ( int i = 0 ; i < 15 ; i++ )
        cout << '\n';

    while ( getin>> temp )
    {
        cout << "\t\t\t";
        for ( int i = 0 ; i < temp.size() ; i++ )
        {
            if ( temp[i] == SYMBOL_SPACE)
                cout << SYMBOL_EMPTY ;
            else if ( temp[i] == SYMBOL_AT )
                cout << char(4) ;
            else
                cout << temp[i] ;
        }
        cout << endl;
    }

    char input ;
    input = getch() ;
    while ( input != '1' && input != '2' && input != '3' && input != '4'  )
        input = getch();
    if ( input == '1' )
    {
        Curser_.level = 1 ;
        Curser_.STAR_WARS = 0 ;
    }
    else if ( input == '2' )
    {
        Curser_.level = 2 ;
        Curser_.STAR_WARS = 0 ;
    }
    else if ( input == '3' )
    {
        Curser_.level = 3 ;
        Curser_.STAR_WARS = 1 ;
    }
    else
    {
        return 0 ;
    }
    system("CLS");
    getin.close();
    if ( Curser_.level == 1   )
        getin.open("Data\\level 1.txt");
    else if ( Curser_.level == 3 )
        getin.open("Data\\STARWARS.txt");
    else
        getin.open("Data\\level 2.txt");
    for ( int i = 0 ; i < 12 ; i++ )
        cout << '\n';
    while ( getin >> temp )
    {
        for ( int i = 0 ; i < temp.size() ; i++ )
        {
            if ( temp[i] == SYMBOL_SPACE )
                cout << SYMBOL_EMPTY ;
            else if ( temp[i] == SYMBOL_AT && Curser_.STAR_WARS)
                cout << SYMBOL_EMPTY;
            else
                cout << char(DIAMON_NUM);
        }
        cout << endl;
    }
    Sleep(4*GameSpeed);
    system("CLS");
    return 1 ;
}

int The_Game::is_dead(PacMan &PacMan_ , vector < Ghosts > &ghosts , curser &Curser_ , Map &map_ , player &player1_
                      , GUN &SHOT , vector < GUN > &SHOTS)
 /// check if dead or eating enemy
{
    for ( int i = 0 ; i < Curser_.num_of_enemy ; i++ )
    {
        if ( (PacMan_.position == ghosts[i].position  && !Curser_.enemy_shapes[i]) || (SHOT.owner == "GHOST" && SHOT.position == PacMan_.position ) )
        {
            if ( Curser_.life_ctr )
            {
                Curser_.life_ctr--;
                switch( Curser_.level)
                {
                case 1:
                case 3:
                    Curser_.gotoxy(Curser_.last_life_pos,col_pos1);
                    break;
                default:
                    Curser_.gotoxy(Curser_.last_life_pos,col_pos2);
                    break;
                }
                cout << SYMBOL_EMPTY ;
                Curser_.last_life_pos -= 2;
                PlaySoundA(TEXT("Data\\pacman_death.wav"),NULL ,SND_FILENAME) ;
                set_game(Curser_,PacMan_,ghosts,map_,SHOTS);
            }
            else
            {
                switch( Curser_.level)
                {
                case 1:
                case 3:
                    Curser_.gotoxy(Curser_.last_life_pos,col_pos1);
                    break;
                default:
                    Curser_.gotoxy(Curser_.last_life_pos,col_pos2);
                    break;
                }
                cout << SYMBOL_EMPTY ;
                if ( ghosts[i].position == PacMan_.position )
                    return i ;
                else
                    return LASER ;
            }

        }
        else if ( SHOT.owner == "PLAYER" && SHOT.position == ghosts[i].position  )
        {
            player1_.score_ghosts += score_per_ghost ;
            player1_.total_score += score_per_ghost ;
            PlaySound(TEXT("Data\\pacman_eatghost.wav"),NULL,SND_FILENAME);
            Curser_.enemy_shapes[i] = 0 ;
            Curser_.gotoxy(ghosts[i].position.second, ghosts[i].position.first) ;
            if ( map_.foods[ghosts[i].position.first][ghosts[i].position.second].shape == HEART_NUM )
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
            else
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE );
            cout <<  map_.foods[ghosts[i].position.first][ghosts[i].position.second].shape ;
            ghosts[i].death_ctr++ ;
            if ( ghosts[i].death_ctr == 2 ) {
                ghosts[i].death_ctr = 0 ;
                Ghosts ghost ;
                ghost.death_ctr = 0 ;
                ghost.position = positions[0];
                ghost.shape = SYMBOL_ENEMY_NORMAL ;
                ghost.color = ghosts[i].color ;
                ghosts.push_back(ghost);
                Curser_.is_super.push_back(0);
                Curser_.enemy_shapes.push_back(0);
                Curser_.gotoxy(positions[0].second,positions[0].first);
                ghosts[Curser_.num_of_enemy].get_color(ghost.color);
                cout << ghosts[Curser_.num_of_enemy].shape    ;
                Curser_.num_of_enemy++;
            }
            ghosts[i].position = positions[0] ;
            Curser_.gotoxy(positions[0].second,positions[0].first);
            ghosts[i].get_color(ghosts[i].color);
            cout << ghosts[i].shape    ;
        }
        else if ( PacMan_.position == ghosts[i].position  )
        {
            player1_.score_ghosts += score_per_ghost ;
            player1_.total_score += score_per_ghost ;
            PlaySound(TEXT("Data\\pacman_eatghost.wav"),NULL,SND_FILENAME);
            Curser_.enemy_shapes[i] = 0 ;
            Curser_.gotoxy(ghosts[i].position.second, ghosts[i].position.first) ;
            map_.map[PacMan_.position.first][PacMan_.position.second] = PacMan_.shape;
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
            cout <<  PacMan_.shape ;
            switch ( Curser_.level )
            {
            case 1:
            case 3:
                ghosts[i].position = positions[0] ;
                Curser_.gotoxy(positions[0].second,positions[0].first);
                break;
            default :
                ghosts[i].position = {positions[0].first-1,positions[0].second} ;
                Curser_.gotoxy(positions[0].second,positions[0].first-1);
                break;
            }
        }
    }
    return -1 ;
}

bool The_Game::init_game(curser &Curser_ , Map &map_ , PacMan &PacMan_ , vector<Ghosts >&ghosts, vector < GUN > &SHOTS ) /// init every level
{
    Curser_.life_ctr = 2 ;
    Curser_.enemy_shapes.resize(4);
    Curser_.num_of_enemy = 1;
    Curser_.last_life_pos = 4 ;
    map_.clean_map();
    for ( int i = 0 ; i < total_enemy ; i++ )
        Curser_.enemy_shapes[i] = 0 , ghosts[i].death_ctr = 0  , ghosts[i].color = i ;
    if ( !get_game(Curser_) )
        return 0 ;
    map_.read_map(Curser_);
    map_.Generate();
    map_.showMap(Curser_);

    for ( int i = 0 ; i < total_enemy ; i++ ) {
        switch ( Curser_.level )
        {
        case 1:
        case 3:
            ghosts[i].position = positions[i];
            break;
        default :
            ghosts[i].position =  {positions[i].first-1,positions[i].second};
            break;
        }
    }
    srand(time(NULL));
    ///
    set_game(Curser_ , PacMan_ , ghosts ,map_,SHOTS);
    PlaySound(TEXT("Data\\pacman_beginning.wav"),0,SND_FILENAME);
    return 1 ;
}

void The_Game::move_enemy(curser &Curser_ ,vector < Ghosts >&ghosts , Map &map_  , PacMan &PacMan_,  vector < GUN > &SHOTS ) /// smart enemy or random one
{
    for ( int i = 0 ; i < ghosts.size() ; i++ )
    {
        bool mask = 0 ;
        for ( int j = 1 ; j < 4 ; j++ ) {
            if ( ghosts[i].position == positions[j] )
                mask = 1 ;
        }
        if ( mask )
            continue ;
        if  ( Curser_.is_super[i] )
        {
            ghosts[i].clear_temp();
            ghosts[i].attack(0, {} ,ghosts[i].position , map_ ,Curser_, PacMan_ );
        }
        else
        {
            ghosts[i].move_random(ghosts[i].position , PacMan_ , map_,Curser_);
        }
        ghosts[i].select_way(i , map_ , Curser_ , SHOTS);

    }
}

void The_Game::back_to_menu( curser &Curser_ ) /// after finishing a level
{
    Curser_.gotoxy(-3,29);
    cout <<"PRESS b key to go back to the menu " << endl;
    char c = getch() ;
    while ( c != 'b' )
        c = getch();
}

void The_Game::clean_option(curser &Curser_) /// clean the pause and exit part
{
    for ( int i = 0 ; i < 50 ; i++ )
    {
        for ( int j = 0 ; j < 2 ; j++ ) {
            Curser_.gotoxy(i,30+j);
            cout << SYMBOL_EMPTY ;
        }
    }
}

int The_Game::move_fires(curser &Curser_ , Map &map_ , PacMan &PacMan_ , vector <Ghosts >&ghosts , vector < GUN > &SHOTS , player &player1_)
{
    for ( int j = 0 ; j < 3 ; j++ ) {
        for ( int i = 0 ; i < SHOTS.size() ; i++ )
        {
            bool mask = 1;
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xE);
            Curser_.gotoxy(SHOTS[i].position.second,SHOTS[i].position.first) ;
            if ( SHOTS[i].position == PacMan_.position && SHOTS[i].owner == "PLAYER" )
                cout << PacMan_.shape , mask = 0 ;
            else if ( SHOTS[i].owner == "GHOST" ) {
                for ( int k = 0 ; k < Curser_.num_of_enemy ; k++ ) {
                    if ( ghosts[k].position == SHOTS[i].position )
                    {
                        ghosts[k].get_color(k%4) ;
                        cout << ghosts[k].shape;
                        mask = 0 ;
                        break;
                    }
                }
            }
            if ( mask ){
                if (  map_.foods[SHOTS[i].position.first][SHOTS[i].position.second].shape == char(HEART_NUM) )
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC);
                cout << map_.foods[SHOTS[i].position.first][SHOTS[i].position.second].shape;
            }
            int temp = is_dead(PacMan_,ghosts,Curser_,map_,player1_ , SHOTS[i], SHOTS) ;
            if ( temp == LASER )
                return LASER ;
            else if ( temp != -1 )
                return SHOTS[i].color ;
            if ( SHOTS[i].move_shot(map_) ){
                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xD );
                Curser_.gotoxy(SHOTS[i].position.second,SHOTS[i].position.first) ;
                cout << SHOTS[i].shape ;
                int temp = is_dead(PacMan_,ghosts,Curser_,map_,player1_ , SHOTS[i], SHOTS) ;
                if ( temp  == LASER  )
                    return LASER ;
                else if ( temp != -1 )
                    return SHOTS[i].color ;
            }
            else {
                SHOTS.erase(SHOTS.begin()+i);
                i--;
            }
        }
        Sleep(10);
    }
    return -1 ;
}

void The_Game::game_loop(curser &Curser_ , Map &map_ , PacMan &PacMan_ , vector < Ghosts >&ghosts , player &player1_ , vector < GUN > &SHOTS) /// move and check in win
{
    if ( !init_game(Curser_ , map_ , PacMan_ , ghosts , SHOTS) )
        return ;
    GUN SHOT = {};
    SHOT.position = {-1,-1};
    int temp1 = -1 , temp = -1 ;
    while (true)
    {
        map_.get_life(Curser_);
        temp = is_dead(PacMan_ , ghosts , Curser_ ,map_ , player1_ , SHOT, SHOTS);
        if ( temp == -1 )
            temp1 = move_fires(Curser_ ,map_ , PacMan_ ,ghosts ,SHOTS , player1_);
        if ( temp != -1 || temp1 != -1  )
        {
            if ( temp == -1 )
                temp = temp1 ;

            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xF );
            Curser_.gotoxy(PacMan_.position.second,PacMan_.position.first);

            if ( temp == LASER )
                cout << SYMBOL_EMPTY ;
            else
                cout << ghosts[temp].shape ;
            clean_option(Curser_);
            PlaySoundA(TEXT("Data\\pacman_death.wav"),NULL ,SND_FILENAME) ;
            Curser_.gotoxy(-3,27);
            cout << "You lose\n" ;
            back_to_menu(Curser_);
            return ;
        }
        if ( kbhit() )
        {
            char c = getch() ;
            if ( c == 'p' )
                getch();
            if ( c == 'e'   )
                return ;
        }
        getKey_move(PacMan_, map_ , player1_ , Curser_ , SHOTS);
        display_score(Curser_ , player1_);
        if ( win(player1_ , Curser_) )
        {
            clean_option(Curser_);
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ) , 0xC );
            Curser_.gotoxy(-3,27);
            cout << "You Win\n" ;
            PlaySoundA(TEXT("Data\\clapping.wav"),NULL ,SND_FILENAME) ;
            update_high(Curser_,player1_);
            back_to_menu(Curser_);
            return ;
        }
        if ( Curser_.turns == turns_change  )
        {
            int num = -1  ;
            if ( !Curser_.STAR_WARS )
                num = Curser_.num_of_enemy ;
            else {
                for ( int i = 0 ; i < ghosts.size() ; i++ ) {
                    for ( int j = 1 ; j < 4 ; j++ ) {
                        if ( ghosts[i].position == positions[j] )
                            num = i ;
                        if ( num != -1 )
                            break;
                    }
                    if ( num != -1 )
                        break;
                }
            }
            if ( num < total_enemy && num != -1)
            {

                Curser_.gotoxy(ghosts[num].position.second,ghosts[num].position.first);
                cout << SYMBOL_EMPTY ;
                switch ( Curser_.level )
                {
                case 1:
                case 3:
                    ghosts[num].position = positions[0];
                    break;
                default:
                    ghosts[num].position = {positions[0].first-1,positions[0].second};
                    break;
                }
                ghosts[num].get_color(num%4);
                Curser_.gotoxy(ghosts[num].position.second,ghosts[num].position.first);
                cout << ghosts[num].shape ;
                Curser_.num_of_enemy++;
            }
            for ( int i = 0 ; i < Curser_.num_of_enemy ; i++ )
                Curser_.is_super[i] = 0 ;
            for ( int i = 0 ; i < (Curser_.STAR_WARS ? ceil(Curser_.num_of_enemy /3.) : 1 ) ; i++ )
                Curser_.is_super[rand()%Curser_.num_of_enemy] = 1  ;
            Curser_.turns  = 0 ;
        }

        if ( Curser_.time_afraid )
            Curser_.time_afraid--;

        if ( !Curser_.time_afraid )
        {
            for ( int i = 0 ; i < total_enemy ;  i++ )
                Curser_.enemy_shapes[i] = 0 ;
        }

        move_enemy(Curser_ , ghosts , map_ , PacMan_ , SHOTS);
        Curser_.turns++;
        Sleep(GameSpeed);
    }
}

void The_Game::instructions() /// instructions part
{
    system("CLS");
    ifstream fin("Data\\instructions.txt");
    string temp ;
    fin >> temp ;
    cout << "\n\n";
    while ( fin >> temp )
    {
        if ( temp[1] == 'P'  )
            cout << "\n     " ;
        else
            cout << "       ";
        for ( int i = 0 ; i < temp.size() ; i++ )
        {
            if ( temp[i] == SYMBOL_SPACE )
                cout << SYMBOL_EMPTY;
            else if ( temp[i] == SYMBOL_AT )
                cout << char(DIAMON_NUM);
            else if ( temp[i] == SYMBOL_STAR )
                cout << char(SYMBOL_SMILY_FACE);
            else if ( temp[i] == SYMBOL_UP )
                cout << SYMBOL_ARROW_UP   ;
            else if ( temp[i] == SYMBOL_DOWN )
                cout << SYMBOL_ARROW_DOWN ;
            else if ( temp[i] == SYMBOL_RIGHT )
                cout << SYMBOL_ARROW_RIGHT;
            else if ( temp[i] == SYMBOL_LEFT )
                cout << SYMBOL_ARROW_LEFT ;
            else
                cout << temp[i] ;
        }
        cout << endl;
    }
    getch();
}

void The_Game::credits() /// credits part
{
    system("CLS");
    ifstream fin("Data\\credits.txt");
    string reading ;
    fin >> reading ;
    for ( int i = 0 ; i < 3 ; i++ )
        cout << endl;
    while ( fin >> reading  )
    {
        if ( reading[1] == 'P' )
            cout << "\n    " ;
        else
            cout << "\t    ";
        for ( int i = 0 ; i < reading.size() ; i++ )
        {
            if ( reading[i] == SYMBOL_SPACE )
                cout << SYMBOL_EMPTY ;
            else if ( reading[i] == SYMBOL_AT )
                cout << char(DIAMON_NUM);
            else
                cout << reading[i] ;
        }
        cout << endl;
    }
    getch() ;
}

void The_Game::Exit() /// Exit part
{
    system("CLS");
    string temp ;
    ifstream fin("Data\\pac.txt");
    while ( fin >> temp)
    {
        fin >> temp ;
        for ( int i = 0 ; i < temp.size() ; i++ )
        {
            switch (temp[i])
            {
            case SYMBOL_AT :
                cout << " " ;
                break;
            default :
                cout << char(PAC_NUM_END) ;
                break;
            }
        }
        cout << endl;

    }
}

void The_Game::play(player &player1_ , curser &Curser_ , PacMan &PacMan_ , vector <Ghosts >&ghosts , Map &map_ , vector < GUN > &SHOTS) /// get game loop
{
    player1_.score_ghosts = player1_.bonus_score = 0;
    player1_.score_food = player1_.total_score = 1 ;
    system("CLS");
    game_loop( Curser_ , map_ , PacMan_ , ghosts , player1_ , SHOTS);
}

void The_Game::show_options() /// shoe menu
{
    ifstream fin2("Data\\pacman.txt");
    string temp ;
    fin2 >> temp ;
    cout << "\n\n\n";
    while ( fin2 >>temp )
    {
        cout << "\t" ;
        for ( int i = 0 ; i < temp.size() ; i++ )
        {
            if ( temp[i] == SYMBOL_SPACE )
                cout << SYMBOL_EMPTY ;
            else if ( temp[i] == SYMBOL_AT )
                cout << char(DIAMON_NUM);
            else
                cout << char(WALL_NUM2);
        }
        cout << endl;
    }
    fin2.close();

    ifstream fin("Data\\Menu.txt");

    fin >> temp;
    while ( fin >> temp )
    {
        cout << "\t   " ;
        for ( int i =0 ; i < temp.size() ; i++ )
        {
            if ( temp[i] == SYMBOL_AT )
                cout << char(4);
            else if ( temp [i] == SYMBOL_SPACE )
                cout << SYMBOL_EMPTY;
            else
                cout << temp[i];
        }
        cout << endl;
    }
}

void The_Game::menu(player &player1_ , curser &Curser_ , PacMan &PacMan_ , vector < Ghosts > &ghosts, Map &map_ , vector < GUN > &SHOTS) /// take choice from the player
{
    char choice ;
    player1_.getname(Curser_);
    system("CLS");
    show_options();
    while(1)
    {
        system("color E");
        choice = getch();
        switch (choice)
        {
        case '1':
            play( player1_ , Curser_ , PacMan_ , ghosts, map_,SHOTS);
            system("CLS");
            show_options();
            break;
        case '2':
            instructions() ;
            system("CLS");
            show_options();
            break;
        case '3':
            get_high_score();
            system("CLS");
            show_options();
            break;
        case '4':
            system("CLS");
            player1_.getname(Curser_);
            system("CLS");
            show_options();
            break;
        case '5':
            credits();
            system("CLS");
            show_options();
            break;
        case '6':
            Exit() ;
            Sleep(4*GameSpeed);
            return ;
        default :
            break;
        }
    }
}
void The_Game::make_game() {
    system("mode 80,35");
    curser Curser_ ;
    Curser_.enemy_shapes.resize(4);
    vector < GUN > SHOTS ;
    vector < Ghosts > ghosts(4) ;
    Curser_.is_super.resize(4) ;
    Map map_ ;
    PacMan PacMan_;
    player player1_ ;
    menu(player1_,Curser_,PacMan_,ghosts ,map_ , SHOTS);
}
///
