extern void Print(const char *str);
extern void DrawBlock(int x, int y, int color);
extern void DrawPX(int x, int y, int color);
extern void play_melody();
extern int moveDown();
extern volatile int tick;
extern void SetupPit();
extern int initialize();
extern void ClearScreen();
extern void drawString(int x, int y, const char* str);
extern void intToStr(int num, char* str);
extern void InitSount();

void startGame();
void drawTitle();
void wait_one_second();
void DrawWalls();
void FillBlocks();
volatile int timedelay;
int GetInMenu();
void sleep(int milliseconds);
volatile int inMainMenu;
struct Block {
    int id;
    char Block[2][4];
    int maxR;
    int offset[4][2];
    int colOffset[4][2];
    int color;
};


struct Block blocks[7];

int IntantiateBlocks(){
    blocks[0].id = 0;
    char tempBlock0[2][4] = {
        {0, 0, 0, 0,},
        {1, 1, 1, 1,}
    };
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            blocks[0].Block[i][j] = tempBlock0[i][j];
        }
    }
    blocks[0].maxR = 2;
    int tempOffset0[4][2] = {
        {0, 0},
        {1, -1},
        {0, 0},
        {0, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[0].offset[i][j] = tempOffset0[i][j];
        }
    }
    int tempColOffset0[4][2] = {
        {0, 0},
        {-1, 1},
        {0, 0},
        {0, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[0].colOffset[i][j] = tempColOffset0[i][j];
        }
    }
    blocks[0].color = 5;
    

    blocks[1].id = 1;
    char tempBlock1[2][4] = {
        {1, 0, 0, 0,},
        {1, 1, 1, 0,},
    };
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            blocks[1].Block[i][j] = tempBlock1[i][j];
        }
    }
    blocks[1].maxR = 4;
    int tempOffset1[4][2] = {
        {1, 0},
        {1, 0},
        {3, 2},
        {-1, 2}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[1].offset[i][j] = tempOffset1[i][j];
        }
    }
    int tempColOffset1[4][2] = {
        {0, 1},
        {0, 1},
        {2, 3},
        {2, -1}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[1].colOffset[i][j] = tempColOffset1[i][j];
        }
    }
    blocks[1].color = 6;

    
    blocks[2].id = 4;
    char tempBlock2[2][4] = {
        {0, 0, 1, 0,},
        {1, 1, 1, 0,},
    };
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            blocks[2].Block[i][j] = tempBlock2[i][j];
        }
    }
    blocks[2].maxR = 4;
    int tempOffset2[4][2] = {
        {1, 0},
        {1, 0},
        {3, 2},
        {-1, 2}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[2].offset[i][j] = tempOffset2[i][j];
        }
    }
    int tempColOffset2[4][2] = {
        {0, 1},
        {0, 1},
        {2, 3},
        {2, -1}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[2].colOffset[i][j] = tempColOffset2[i][j];
        }
    }
    blocks[2].color = 8;

    
    blocks[3].id = 3;
    char tempBlock3[2][4] = {
        {1, 1, 1, 0,},
        {0, 1, 0, 0,},
    };
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            blocks[3].Block[i][j] = tempBlock3[i][j];
        }
    }
    blocks[3].maxR = 4;
    int tempOffset3[4][2] = {
        {1, 0},
        {0, -1},
        {3, 0},
        {0, 1}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[3].offset[i][j] = tempOffset3[i][j];
        }
    }
    int tempColOffset3[4][2] = {
        {0, 1},
        {-1, 0},
        {0, 3},
        {1, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[3].colOffset[i][j] = tempColOffset3[i][j];
        }
    }
    blocks[3].color = 7;

    
    blocks[4].id = 4;
    char tempBlock4[2][4] = {
        {0, 1, 1, 0,},
        {0, 1, 1, 0,},
    };
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            blocks[4].Block[i][j] = tempBlock4[i][j];
        }
    }
    blocks[4].maxR = 1;
    int tempOffset4[4][2] = {
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[4].offset[i][j] = tempOffset4[i][j];
        }
    }
    int tempColOffset4[4][2] = {
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[4].colOffset[i][j] = tempColOffset4[i][j];
        }
    }
    blocks[4].color = 4;

    
    blocks[5].id = 5;
    char tempBlock5[2][4] = {
        {0, 1, 1, 0,},
        {1, 1, 0, 0,},
    };
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            blocks[5].Block[i][j] = tempBlock5[i][j];
        }
    }
    blocks[5].maxR = 2;
    int tempOffset5[4][2] = {
        {1, 0},
        {1, -1},
        {0, 0},
        {0, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[5].offset[i][j] = tempOffset5[i][j];
        }
    }
    int tempColOffset5[4][2] = {
        {0, 1},
        {-1, 1},
        {0, 0},
        {0, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[5].colOffset[i][j] = tempColOffset5[i][j];
        }
    }
    blocks[5].color = 2;

    
    blocks[6].id = 6;
    char tempBlock6[2][4] = {
        {1, 1, 0, 0,},
        {0, 1, 1, 0,},
    };
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            blocks[6].Block[i][j] = tempBlock6[i][j];
        }
    }
    blocks[6].maxR = 2;
    int tempOffset6[4][2] = {
        {0, 0},
        {0, -1},
        {0, 0},
        {0, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[6].offset[i][j] = tempOffset6[i][j];
        }
    }
    int tempColOffset6[4][2] = {
        {0, 0},
        {-1, 0},
        {0, 0},
        {0, 0}
    };
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            blocks[6].colOffset[i][j] = tempColOffset6[i][j];
        }
    }
    blocks[6].color = 3;
}
volatile int inMainMenu;
volatile int timedelay;
volatile int topScore;
// screen size height(200) width(320)
int main(){
    //draw title screen
    inMainMenu = 1;
    SetupPit();
    //InitSount();
    timedelay = 100;
    topScore = 0;
    drawTitle();

    return 0;
}

void drawTitle(){
    inMainMenu = 1;

    ClearScreen();

    int xOffset = 4;
    int yOffset = 4;
    DrawBlock(-11 + xOffset, 0 + yOffset, 2);
    DrawBlock(-10 + xOffset, 0 + yOffset, 2);
    DrawBlock(-9 + xOffset, 0 + yOffset, 2);
    DrawBlock(-10 + xOffset, 1 + yOffset, 2);
    DrawBlock(-10 + xOffset, 2 + yOffset, 2);
    DrawBlock(-10 + xOffset, 3 + yOffset, 2);
    DrawBlock(-10 + xOffset, 4 + yOffset, 2);

    DrawBlock(-7 + xOffset, 0 + yOffset, 3);
    DrawBlock(-6 + xOffset, 0 + yOffset, 3);
    DrawBlock(-5 + xOffset, 0 + yOffset, 3);
    DrawBlock(-6 + xOffset, 2 + yOffset, 3);
    DrawBlock(-5 + xOffset, 2 + yOffset, 3);
    DrawBlock(-6 + xOffset, 4 + yOffset, 3);
    DrawBlock(-5 + xOffset, 4 + yOffset, 3);
    DrawBlock(-7 + xOffset, 1 + yOffset, 3);
    DrawBlock(-7 + xOffset, 2 + yOffset, 3);
    DrawBlock(-7 + xOffset, 3 + yOffset, 3);
    DrawBlock(-7 + xOffset, 4 + yOffset, 3);

    DrawBlock(-3 + xOffset, 0 + yOffset, 4);
    DrawBlock(-2 + xOffset, 0 + yOffset, 4);
    DrawBlock(-1 + xOffset, 0 + yOffset, 4);
    DrawBlock(-2 + xOffset, 1 + yOffset, 4);
    DrawBlock(-2 + xOffset, 2 + yOffset, 4);
    DrawBlock(-2 + xOffset, 3 + yOffset, 4);
    DrawBlock(-2 + xOffset, 4 + yOffset, 4);

    DrawBlock(1 + xOffset, 0 + yOffset, 5);
    DrawBlock(2 + xOffset, 0 + yOffset, 5);
    DrawBlock(3 + xOffset, 1 + yOffset, 5);
    DrawBlock(2 + xOffset, 2 + yOffset, 5);
    DrawBlock(3 + xOffset, 3 + yOffset, 5);
    DrawBlock(3 + xOffset, 4 + yOffset, 5);
    DrawBlock(1 + xOffset, 1 + yOffset, 5);
    DrawBlock(1 + xOffset, 2 + yOffset, 5);
    DrawBlock(1 + xOffset, 3 + yOffset, 5);
    DrawBlock(1 + xOffset, 4 + yOffset, 5);

    DrawBlock(5 + xOffset, 0 + yOffset, 6);
    DrawBlock(6 + xOffset, 0 + yOffset, 6);
    DrawBlock(7 + xOffset, 0 + yOffset, 6);
    DrawBlock(6 + xOffset, 1 + yOffset, 6);
    DrawBlock(6 + xOffset, 2 + yOffset, 6);
    DrawBlock(6 + xOffset, 3 + yOffset, 6);
    DrawBlock(5 + xOffset, 4 + yOffset, 6);
    DrawBlock(6 + xOffset, 4 + yOffset, 6);
    DrawBlock(7 + xOffset, 4 + yOffset, 6);

    DrawBlock(9 + xOffset, 0 + yOffset, 7);
    DrawBlock(10 + xOffset, 0 + yOffset, 7);
    DrawBlock(11 + xOffset, 0 + yOffset, 7);
    DrawBlock(9 + xOffset, 1 + yOffset, 7);
    DrawBlock(9 + xOffset, 2 + yOffset, 7);
    DrawBlock(10 + xOffset, 2 + yOffset, 7);
    DrawBlock(11 + xOffset, 2 + yOffset, 7);
    DrawBlock(11 + xOffset, 3 + yOffset, 7);
    DrawBlock(9 + xOffset, 4 + yOffset, 7);
    DrawBlock(10 + xOffset, 4 + yOffset, 7);
    DrawBlock(11 + xOffset, 4 + yOffset, 7);

    for(int i = 0; i < 25; i++){
        DrawBlock(-12 + xOffset + i, -2 + yOffset, 1);
        DrawBlock(-12 + xOffset + i, 6 + yOffset, 1);
    }



    drawString(65, 150, "PRESS ENTER TO START");
    while (inMainMenu == 1)
    {
        
    }
    startGame();
}
int GetInMenu(){
    return inMainMenu;
}
void startGame(){
    ClearScreen();
    IntantiateBlocks();
    DrawWalls();
    drawString(221 + 20, 30, "TOP");
    drawString(221 + 20, 70, "SCORE");
    drawString(221 + 20, 140, "NEXT");

    initialize();
    timedelay = 100;
    int lastUsedTick = tick;
    
    while(1 == 1){
        if(inMainMenu == 1){
            return;
        }
        if(tick - lastUsedTick >= timedelay){
            moveDown();
            lastUsedTick = tick;
        }
        sleep(10);
    }

}
void DrawWalls(){
    for(int i = 0; i < 20; i++){
        DrawBlock(-1, i, 1);
    }
        for(int i = 0; i < 20; i++){
        DrawBlock(10, i, 1);
    }

}

void FillBlocks(){
    for(int x = 0; x < 10; x++){
        for(int j = 0; j < 20; j++){
            DrawBlock(j, x, 2);
        }
    }
}

void sleep(int milliseconds) {
    int startTick = tick;


    int waitTicks = milliseconds * (100 / 1000); 

    while ((tick - startTick) < waitTicks) {

    }
}



