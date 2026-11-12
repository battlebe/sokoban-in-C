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

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

typedef struct {
    int x,y;
} Box;

typedef struct {
    int x,y;
} Wall;

typedef struct {
    // field size
    int width;
    int height;

    Box *boxes;
    Wall * walls;

    int boxCount;
    int wallCount;
} GameMap ;

typedef struct {
    int x;
    int y;

    GameMap map;
    
} Rambler ;

void Rambler_move(Rambler* r,GameMap* m, enum KeyEvent movetype);

/**
 * \brief check a direction for a rambler, to see if it's possible to move
 * 
 * \details let's see the situations below
 *          situation0.  O      yes
 *          situation1.  O #    no, blocked by wall
 *          situation2.  O X    yes, and push box
 *          situation2.  O X #  no, can't push box thru wall
 *          situation3.  O X X  no, can't push more than one box
 */
int Rambler_isThereSpace4Move(Rambler r, GameMap m, enum Direction dir);

void GameMap_Print(GameMap map, Rambler player);

void Box_move(Box *b, enum Direction dir, GameMap map);

int isPosEqual(int lhs[2],int rhs[2]);

int isPosEqualBox(int lhs[2],Box *boxes, int boxcount);

enum KeyEvent CaptureKeyEvent(int userPressedKey);


int main(void) {
    // init gamemap: box
    Box boxes[3] = {{2,2},{3,3},{2,3}};
    Wall walls[2] = {{2,1},{3,1}};

    GameMap map = {5,5,boxes,walls,3,2};



    Rambler ramb = {1,1, map};
    GameMap_Print(map,ramb); //with rambler in it

    int userPressedKey;

    // main game loop
    while(1){
        if(_kbhit()){
            enum KeyEvent evnet = CaptureKeyEvent(_getch());

            if(evnet == GAME_EXIT)
                return 0;   //exit game

            Rambler_move(&ramb,&map,evnet);
            GameMap_Print(map, ramb);
            printf("rambler Moved!,  current pos(%d,%d)\n",ramb.x,ramb.y);
        }
    }
    return 0;
}

int Rambler_isThereSpace4Move(Rambler r, GameMap m, enum Direction dir)
{
    
    return 1;   // always space
}

void GameMap_Print(GameMap map, Rambler player)
{
    //    0 1
    //  # # # #
    // 0 # o   # rambler in (0, 0)
    // 1 #     #
    //  # # # # this is a 2x2 game map
    int width = map.width;
    int height = map.height;

    int ramblerPos[2] = {player.x, player.y};
    int boxCount = map.boxCount;


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
                int scanningPos[2] = {j ,i}; 
                if(j == 0) {
                    printf("# ");       // Left wall
                }
                else if(j == width + 1) {
                    printf("#\n");      // Right wall
                }
                else if(isPosEqual(scanningPos,ramblerPos)) {
                    printf("O ");       // represents Player
                }
                else if(isPosEqualBox(scanningPos, map.boxes, boxCount)) {
                    printf("X ");       // represents Box
                }
                else if(isPosEqualBox(scanningPos, map.walls, map.wallCount)) {
                    printf("# ");       // represents Inner wall
                }
                else {
                    printf("  ");       // Game Field
                }
            }
        }
    }
}

void Box_move(Box *b,enum Direction dir, GameMap map)
{
    int yMax = map.height;
    int xMax = map.width;
    // open issue: how to assure that rambler/box  and another box's collision?


    switch (dir)
    {
    case UP:
        if(b->y == 1)
            return;

        b->y -= 1;
        break;
    case DOWN:
        if(b->y == yMax)
            return;

        b->y += 1;
        break;
    case LEFT:
        if(b->x == 1)
            return;

        b->x -= 1;
        break;
    case RIGHT:
        if(b->x == xMax)
            return;

        b->x += 1;
        break;
    
    default:
        break;
    }

}

int isPosEqual(int lhs[2], int rhs[2])
{
    if(lhs[0] == rhs[0] && lhs[1] == rhs[1])
        return 1;
    else
    return 0;
}

int isPosEqualBox(int lhs[2],Box *boxes, int boxcount)
{

    for(int i = 0; i < boxcount ; i++) {
        int x = lhs[0];
        int y = lhs[1];
        int boxX = boxes->x;
        int boxY = boxes->y;
        if(lhs[0]== boxes->x && lhs[1] ==boxes->y) {
            return 1;
        }
        ++boxes;
    }
    return 0;
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

void Rambler_move(Rambler* r,GameMap* m, enum KeyEvent movetype) {
    int width = r->map.width;
    int height = r->map.height;
    Box *box = m->boxes;
    int boxCount = m->boxCount;
    
    
    switch (movetype)
    {
    //default (1,1)
    case RAMBLER_MOVE_UP:
        if(r->y == 1)
            return;
        if(! Rambler_isThereSpace4Move(*r,*m,UP))
            return;

        r->y -= 1;
        break;
    
    case RAMBLER_MOVE_DOWN:
        if(r->y == height)
            return;
        if(! Rambler_isThereSpace4Move(*r,*m,DOWN))
            return;

        r->y = r->y+1;
        break;

    case RAMBLER_MOVE_LEFT:
        if(r->x == 1)
            return;
        if(! Rambler_isThereSpace4Move(*r,*m,LEFT))
            return;

        r->x = r->x - 1;
        break;
    
    case RAMBLER_MOVE_RIGHT:
        if(r->x == width)
            return;
        if(! Rambler_isThereSpace4Move(*r,*m,RIGHT))
            return;

        r->x = r->x + 1;
        break;

    default:        // other key event
        return;
    }
};

