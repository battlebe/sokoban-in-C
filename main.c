#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct GameMap {
    int width;
    int height;
    
};

struct Rambler {
    int x;
    int y;
};

void PrintGameMap(int width, int height) {
//    0 1  
//  # # # #
//0 # o   # rambler in (1,1)
//1 #     #
//  # # # # this is a 2x2 game map
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
    struct GameMap map = {10,10};
    PrintGameMap(30,10);
    int ch;
    while(1){
        if(_kbhit()){
            ch = _getch();
            switch (ch)
            {
            case 119:
                printf("W hitted!");
                break;
            case 97:
                printf("A hitted!");
                break;
            case 115:
                printf("S hitted!");
                break;
            case 100:
                printf("D hitted!");
                break;
            
            default:
                break;
            }
        }
    }
    return 0;
}