struct Block {
    int id;
    char Block[2][4];
    int maxR;
    int offset[4][2];
    int colOffset[4][2];
    int color;
};

extern void SpawnBlock(int x, int y, char obj[2][4], int color, int rotation);
extern void DrawPX(int x, int y, int color);
extern void debugMap(int map[20][10]);
extern void debugPixel(int x, int y, int color);
extern void intToStr(int num, char* str);
extern void drawString(int x, int y, const char* str);
extern void DrawBlock(int x, int y, int color);
extern void MoveBlock(int oldX, int oldY, int newX, int newY);
extern void drawTitle();
extern int Rand(int min, int max);
extern struct Block blocks[7];
extern volatile unsigned int seed;
extern volatile int tick;
extern volatile int topScore;

void ClearBlock(int x, int y, char obj[2][4], int rotation);
int spawn(struct Block block);
int moveDown();
int checkUnder(int x, int y);
void RegisterBlock(int x, int y, int value);
void PushBlock();
void RotateBlock();
void ClearLocation(int x, int y, char obj[2][4], int rotation);
void RegisterLocation(int x, int y, char obj[2][4], int rotation);
void UpdateScore();
int initialize();
int CheckLines();
int GetBlock(int x, int y);

int map[20][10] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int currentX;
int currentY;
int currentR;
int maxR;
int offset[4][2];
int colOffset[4][2];
struct Block currentBlock;
int spawned;
char currentObj[2][4];

int temp = 1;

int score;

int nextBlockID;

int defSpeed = 100;
int fastSpeed = 5;
int initialize(){
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            map[i][j] = 0;
        }
    }
    score = 0;
    UpdateScore();
    seed = tick;
    nextBlockID = Rand(0, 7);
    spawn(blocks[nextBlockID]);
    nextBlockID = Rand(0, 7);
    SpawnBlock(13, 15, blocks[nextBlockID].Block, blocks[nextBlockID].color, 0);
}
int spawn(struct Block block){
    spawned = 0;
    currentBlock = block;
    currentY = 3;
    currentX = 0;
    currentR = 0;

    maxR = block.maxR;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            offset[i][j] = block.offset[i][j];
            colOffset[i][j] = block.colOffset[i][j];
            currentObj[j][i] = block.Block[j][i];
        }
    }

    int canSpawn = 1;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(map[currentX + i + colOffset[currentR][0] + 1][currentY + j + colOffset[0][1]] == 1 && block.Block[i][j] == 1){
                canSpawn = 0;
            }
            map[currentX + i + colOffset[currentR][0]][currentY + j + colOffset[0][1]] = block.Block[i][j];
        }   
    }
    if(canSpawn == 1){
        SpawnBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, block.color, currentR);
        //debugMap(map);
        spawned = 1;
        return 1;

    }else {
        //Game Over!
        temp++;
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 10; j++){
                map[i][j] = 0;
            }
        }
        score = 0;
        drawTitle();
        return 0;
    }

}

int checkUnder(int x, int y){
    if(x < 19){
        return map[x + 1][y];
    }
    return 1;
}

int checkLeft(int x, int y){
    if(y > 0){
        return map[x][y - 1];
    }
    return 1;
}
int checkRight(int x, int y){
    if(y < 9){
        return map[x][y + 1];
    }
    return 1;
}
int checkAt(int x, int y){
    if(y > 0 && y < 9 && x < 19){
        return map[x][y];
    }
}
int moveDown(){
    if(spawned = 0) return 0;
    int canMove = 1;
    
    // check if can move down
    for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(currentR == 0){
                if(currentObj[i + 1][j] == 0 && currentObj[i][j] == 1){
                    //check under
                    if(checkUnder(currentX + i + colOffset[currentR][0], currentY + j + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 1){
                if(currentObj[i][j + 1] == 0 && currentObj[i][j] == 1){
                    //check under
                    if(checkUnder(j + currentX + colOffset[currentR][0], -i + currentY + 2 + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 2){
                if(currentObj[i - 1][j] == 0 && currentObj[i][j] == 1 || i == 0 && currentObj[i][j] == 1){
                    //check under
                    if(checkUnder(currentX + -i + colOffset[currentR][0], currentY + -j + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 3){
                if(currentObj[i][j - 1] == 0 && currentObj[i][j] == 1){
                    //check under
                    if(checkUnder(-j + currentX + colOffset[currentR][0], i + currentY + 2 + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }
        }
    }

    if(canMove == 1){
        //clear location
        ClearLocation(currentX + colOffset[currentR][0], currentY + colOffset[currentR][1], currentObj, currentR);

        //Destroy Block
        ClearBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, currentR);
        currentX++;

        //Spawn New BLock
        RegisterLocation(currentX + colOffset[currentR][0], currentY + colOffset[currentR][1], currentObj, currentR);

        SpawnBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, currentBlock.color, currentR);

        return 1;
    }else{
        CheckLines();
        ClearBlock(13, 15, blocks[nextBlockID].Block, 0);
        
        spawn(blocks[nextBlockID]);
        nextBlockID = Rand(0, 7);
        SpawnBlock(13, 15, blocks[nextBlockID].Block, blocks[nextBlockID].color, 0);
    }
}

int MoveLeft(){
    int canMove = 1;

   for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(currentR == 0){
                if(currentObj[i][j - 1] == 0 && currentObj[i][j] == 1){
                    //check left
                    if(checkLeft(currentX + i + colOffset[currentR][0], currentY + j + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 1){
                if(currentObj[i + 1][j] == 0 && currentObj[i][j] == 1){
                    //check left
                    if(checkLeft(j + currentX + colOffset[currentR][0], -i + currentY + 2 + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 2){
                if(currentObj[i][j + 1] == 0 && currentObj[i][j] == 1){
                    //check left 
                    if(checkLeft(currentX + -i + colOffset[currentR][0], currentY + -j + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 3){
                if(currentObj[i - 1][j] == 0 && currentObj[i][j] == 1 || i == 0 && currentObj[i][j] == 1){
                    //check left 
                    if(checkLeft(-j + currentX + colOffset[currentR][0], i + currentY + 2 + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }
        }
    }

    if(canMove == 1){
        // clear location
        ClearLocation(currentX + colOffset[currentR][0], currentY + colOffset[currentR][1], currentObj, currentR);

        // Destroy Block
        ClearBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, currentR);
        currentY--;

        // Spawn New BLock
        RegisterLocation(currentX + colOffset[currentR][0], currentY + colOffset[currentR][1], currentObj, currentR);

        SpawnBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, currentBlock.color, currentR);

        return 1;
    }
}

int MoveRight(){
    int canMove = 1;

   for (int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(currentR == 0){
                if(currentObj[i][j + 1] == 0 && currentObj[i][j] == 1){
                    //check right
                    if(checkRight(currentX + i + colOffset[currentR][0], currentY + j + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 1){
                if(currentObj[i - 1][j] == 0 && currentObj[i][j] == 1 || i == 0 && currentObj[i][j] == 1){
                    //check right
                    if(checkRight(j + currentX + colOffset[currentR][0], -i + currentY + 2 + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 2){
                if(currentObj[i][j - 1] == 0 && currentObj[i][j] == 1){
                    //check left 
                    if(checkRight(currentX + -i + colOffset[currentR][0], currentY + -j + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }else if(currentR == 3){
                if(currentObj[i + 1][j] == 0 && currentObj[i][j] == 1){
                    //check left 
                    if(checkRight(-j + currentX + colOffset[currentR][0], i + currentY + 2 + colOffset[currentR][1]) == 1){
                        canMove = 0;
                    }
                }
            }
        }
    }

    if(canMove == 1){
        //clear location
        ClearLocation(currentX + colOffset[currentR][0], currentY + colOffset[currentR][1], currentObj, currentR);

        //Destroy Block
        ClearBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, currentR);
        currentY++;

        //Spawn New BLock
        RegisterLocation(currentX + colOffset[currentR][0], currentY + colOffset[currentR][1], currentObj, currentR);

        SpawnBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, currentBlock.color, currentR);

        return 1;
    }
}

void RegisterBlock(int x, int y, int value){
    map[x][y] = value;
}
int GetBlock(int x, int y){
    return map[x][y];
}

void PushBlock(){
    spawned = 0;
    while(spawned == 0){
        moveDown();
    }
}

void RotateBlock(){

    int tempMap[20][10];
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            tempMap[i][j] = map[i][j];
        }
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            int _x;
            int _y;
            if(currentR == 0){
                _x = i + currentX + colOffset[currentR][0];
                _y = j + currentY + colOffset[currentR][1];
            }else if(currentR == 1){
                _x = j + currentX + colOffset[currentR][0];
                _y = -i + currentY + 2 + colOffset[currentR][1];
            }else if(currentR == 2){
                _x = currentX - i + colOffset[currentR][0];
                _y = currentY - j + colOffset[currentR][1];
            }else if(currentR == 3){
                _x = -j + currentX + colOffset[currentR][0];
                _y = i + currentY + 2 + colOffset[currentR][1];
            }
            if(tempMap[_x][_y] == 1 && currentObj[i][j] == 1){
                tempMap[_x][_y] = 0;
            }

        }   
    }

    int nextR;
    if(currentR >= maxR - 1 ){
        nextR = 0;
    }else{
        nextR = currentR + 1;
    }
    int canRotate = 1;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            int _x;
            int _y;
            if(nextR == 0){
                _x = i + currentX + colOffset[nextR][0];
                _y = j + currentY + colOffset[nextR][1];
            }else if(nextR == 1){
                _x = j + currentX + colOffset[nextR][0];
                _y = -i + currentY + 2 + colOffset[nextR][1];
            }else if(nextR == 2){
                _x = currentX - i + colOffset[nextR][0];
                _y = currentY - j + colOffset[nextR][1];
            }else if(nextR == 3){
                _x = -j + currentX + colOffset[nextR][0];
                _y = i + currentY + 2 + colOffset[nextR][1];
            }

            if(currentObj[i][j] == 1){
                if(tempMap[_x][_y] == 1){
                    canRotate = 0;
                }
                if(_y < 0 || _y > 9 || _x > 19 ){
                    canRotate = 0;
                }
            }



        }   
    }

    if(canRotate == 1){
        ClearBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, currentR);
        ClearLocation(currentX + colOffset[currentR][0], currentY + colOffset[currentR][1], currentObj, currentR);
        currentR = nextR;
        RegisterLocation(currentX + colOffset[currentR][0], currentY + colOffset[currentR][1], currentObj, currentR);
        SpawnBlock(currentY + offset[currentR][0], currentX + offset[currentR][1], currentObj, currentBlock.color, currentR);
    }
}

void ClearLocation(int x, int y, char obj[2][4], int rotation){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(rotation == 0){
                if(map[i + x][j + y] == 1 && obj[i][j] == 1){
                    RegisterBlock(x + i, y + j, 0);
                }
            }else if(rotation == 1){
                if(map[j + x][-i + y + 2] == 1 && obj[i][j] == 1){
                    
                    RegisterBlock(j + x, -i + y + 2, 0);
                }
            }else if(rotation == 2){
                if(map[x - i][y - j] == 1 && obj[i][j] == 1){
                    RegisterBlock(x - i, y - j, 0);
                }
            }else if(rotation == 3){
                if(map[-j + x][i + y + 2] == 1 && obj[i][j] == 1){
                    RegisterBlock(-j + x, i + y + 2, 0);
                }
            }

        }   
    }
    //debugMap(map);
}
void RegisterLocation(int x, int y, char obj[2][4], int rotation){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 4; j++){
            if(currentObj[i][j] == 1){
                if(rotation == 0){
                    RegisterBlock(x + i, y + j, 1);
                }else if(rotation == 1){
                    RegisterBlock(j + x, -i + y + 2, 1);
                }else if(rotation == 2){
                    RegisterBlock(x - i, y - j, 1);
                }else if(rotation == 3){
                    RegisterBlock(-j + x, i + y + 2, 1);
                }
               
            }
        }   
    }
    //debugMap(map);
}

int CheckLines(){
    int fullLines = 0;
    for(int i = 0; i < 20; i++){
        int isFull = 1;
        for(int j = 0; j < 10; j++){
            if(map[i][j] == 0){
                isFull = 0;
            }
        }
        if(isFull == 1){
            fullLines++;
        
            for(int j = 0; j < 10; j++){
                map[i][j] = 0;
                for(int row = i; row > 0; row--){
                    MoveBlock(row - 1, j, row, j);
                }
                
            }
            i--;
        }
    }
    if(fullLines == 1){
        score += 40;
    }else if(fullLines == 2){
        score += 100;
    }
    else if(fullLines == 3){
        score += 300;
    }
    else if(fullLines == 4){
        score += 1200;
    }
    UpdateScore();
}

void UpdateScore() {
    char str[7];
    intToStr(score, str);


    int len = 0;
    while (str[len] != '\0') len++;


    for (int i = 5; i >= 0; i--) {
        if (i >= 6 - len) {
            str[i] = str[i - (6 - len)];
        } else {
            str[i] = '0';
        }
    }
    str[6] = '\0';

    if(score > topScore){
        topScore = score;
    }

    char topStr[7];
    intToStr(topScore, topStr);


    len = 0;
    while (topStr[len] != '\0') len++;


    for (int i = 5; i >= 0; i--) {
        if (i >= 6 - len) {
            topStr[i] = topStr[i - (6 - len)];
        } else {
            topStr[i] = '0';
        }
    }
    topStr[6] = '\0';

    drawString(221 + 20, 85, str);

    drawString(221 + 20, 45, topStr);
}