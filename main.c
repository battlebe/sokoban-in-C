#include <stdio.h>

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

    return 0;
}