#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

enum RamblerMove {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
};

struct GameMap {
    int width;
    int height;
    
};

struct Rambler {
    int x;
    int y;
    struct GameMap map;
};

void rambler_move(struct Rambler* r, enum RamblerMove movetype) {
    int width = r->map.width;
    int height = r->map.height;
    switch (movetype)
    {
    //default (0,0)
    case MOVE_UP:
        if(r->y == 0)
            return;
        r->y -= 1;
        break;
    
    case MOVE_DOWN:
        if(r->y == height)
            return;
        r->y = r->y+1;
        break;
    
    case MOVE_LEFT:
        if(r->x == 0)
            return;
        r->x = r->x - 1;
        break;
    
    case MOVE_RIGHT:
        if(r->x == width)
            return;
        r->x = r->x + 1;
        break;
    }
};


void PrintGameMap(struct GameMap map, struct Rambler player) {
//    0 1  
//  # # # #
//0 # o   # rambler in (1,1)
//1 #     #
//  # # # # this is a 2x2 game map
    int width = map.width;
    int height = map.height;
    int playerPositionX = player.x;
    int playerPositionY = player.y;


    system("cls");
    for(int i = 1; i <= height + 2; i++) {
        //first row and last row
        if (i == 1 || i == height+2) {
            //print upper and lower wall
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
                    printf("# ");
                }
                else if(j == width + 1) {
                    printf("#\n");
                }
                else {
                    printf("  ");
                }
            }
        }
    }
}

void refresh() {

}


int main(void) {
    struct GameMap map = {30,10};
    struct Rambler ramb = {0,0, map};

    PrintGameMap(map,ramb); //with rambler in it
    int userPressedKey;

    // main game loop
    while(1){
        if(_kbhit()){
            userPressedKey = _getch();
            int currentXPosition = ramb.x;
            int currentYPosition = ramb.y;
            switch (userPressedKey)
            {
            case 119:
                rambler_move(&ramb,MOVE_UP);
                break;
            case 97:
                rambler_move(&ramb,MOVE_LEFT);
                break;
            case 115:
                rambler_move(&ramb,MOVE_DOWN);
                break;
            case 100:
                rambler_move(&ramb,MOVE_RIGHT);
                break;
            
            default:
                break;
            }
            printf("rambler Moved!, From (%d,%d) to (%d,%d)\n",currentXPosition,currentYPosition,ramb.x,ramb.y);
        }
    }
    return 0;
}