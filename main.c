#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

enum KeyEvent {
    GAME_EXIT,      // q
    GAME_RESTART,   // r
    RAMBLER_MOVE_UP,
    RAMBLER_MOVE_DOWN,
    RAMBLER_MOVE_LEFT,
    RAMBLER_MOVE_RIGHT,
};

typedef struct {
    int x,y;
} Position;

typedef struct {
    // field size
    int width;
    int height;

    // box Position
    // todo: Multi box 
    Position boxPosition;
} GameMap ;

typedef struct {
    int x;
    int y;
    GameMap map;
} Rambler ;

void Rambler_move(Rambler* r, enum KeyEvent movetype);

void SetBox(Position pos, GameMap *map);

void PrintGameMap(GameMap map, Rambler player);

enum KeyEvent CaptureKeyEvent(int userPressedKey);

void refresh() {}





int main(void) {
    // init gamemap: rambler box
    GameMap map = {5,5};
    Rambler ramb = {1,1, map};
    Position pos = {3,3};
    SetBox(pos,&map);

    PrintGameMap(map,ramb); //with rambler in it
    int userPressedKey;

    // main game loop
    while(1){
        if(_kbhit()){
            enum KeyEvent evnet = CaptureKeyEvent(_getch());
            if(evnet == GAME_EXIT)
                return 0;

            Rambler_move(&ramb,evnet);
            PrintGameMap(map, ramb);
            printf("rambler Moved!,  current pos(%d,%d)\n",ramb.x,ramb.y);
        }
    }
    return 0;
}


void PrintGameMap(GameMap map, Rambler player) {
//    0 1  
//  # # # #
//0 # o   # rambler in (0, 0)
//1 #     #
//  # # # # this is a 2x2 game map
    int width = map.width;
    int height = map.height;
    int playerPositionX = player.x;
    int playerPositionY = player.y;


    system("cls");

    for(int i = 0; i <= height + 1; i++) {
        if (i == 0 || i == height+1) {      // lower and upper wall
            for(int j = 0; j < width+2; j++) {
                if(j == width +1){
                    printf("#\n");
                }
                else {
                    printf("# ");
                }
            }
        }
        else { 
            for(int j = 0; j < width +2 ; j++){
                if(j == 0) {
                    printf("# ");       // Left wall
                }
                else if(j == width + 1) {
                    printf("#\n");      // Right wall
                }
                else if(i == player.y && j == player.x) {
                    printf("O ");       // represents Playe
                }
                else if (i == map.boxPosition.y && j == map.boxPosition.x) {
                    printf("X ");        // represents Box
                }
                else {
                    printf("  ");       // Game Field
                }
            }
        }
    }
}

enum KeyEvent CaptureKeyEvent(int userPressedKey)
{
    switch (userPressedKey)
    {
    case 119:
        return RAMBLER_MOVE_UP;
        break;
    case 97:
        return RAMBLER_MOVE_LEFT;
        break;
    case 115:
        return RAMBLER_MOVE_DOWN;
        break;
    case 100:
        return RAMBLER_MOVE_RIGHT;
        break;
    case 113:   // q
        return GAME_EXIT;
        break;
    case 114:   // r
        return GAME_RESTART;
        break;
    
    default:
        printf("undefined Key input! key's value = %d\n",userPressedKey);
        break;
    }
}

void Rambler_move(Rambler* r, enum KeyEvent movetype) {
    int width = r->map.width;
    int height = r->map.height;
    switch (movetype)
    {
    //default (1,1)
    case RAMBLER_MOVE_UP:
        if(r->y == 1)
            return;
        r->y -= 1;
        break;
    
    case RAMBLER_MOVE_DOWN:
        if(r->y == height)
            return;
        r->y = r->y+1;
        break;
    
    case RAMBLER_MOVE_LEFT:
        if(r->x == 1)
            return;
        r->x = r->x - 1;
        break;
    
    case RAMBLER_MOVE_RIGHT:
        if(r->x == width)
            return;
        r->x = r->x + 1;
        break;

    default:        // other key event
        return;
    }
};

void SetBox(Position pos, GameMap *map) {
    int x = pos.x;
    int y = pos.y;
    int width = map->width;
    int height = map->height;
    if( x < 1 || x > width || y < 1 || y > height) {
        return;
    }
    map->boxPosition = pos;
}
