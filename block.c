extern void DrawPX(int x, int y, int color);
extern int GetPX(int x, int y);
extern void RegisterBlock(int x, int y, int value);
extern int GetBlock(int x, int y);


void DrawBlock(int x, int y, int color);
void SpawnBlock(int x, int y, char obj[2][4], int color, int rotation);
void ClearBlock(int x, int y, char obj[2][4], int rotation);
void MoveBlock(int oldX, int oldY, int newX, int newY);

const int blockSize = 10;
const int borderSize = 1;


struct Position {
    int x;
    int y;
};

const int areaWidthPadding = (320 - (blockSize * 10)) / 2;
const int areaHeightPadding = 200 - (blockSize * 20);

struct Position GetBlockPos(int x, int y){
    struct Position calcPos;
    calcPos.x = areaWidthPadding + (x * blockSize);
    calcPos.y = areaHeightPadding + (y * blockSize);
    return calcPos;
}
void DrawBlock(int x, int y, int color){

    struct Position pos = GetBlockPos(x, y);
    // variables
    int C1;
    int C2;
    int C3;
    int C4;

    int _x = 0;
    int _y = 0;


    switch (color)
    {
        case 0: // black
            C1 = 0x00;
            C2 = 0x00;
            break;
        case 1: // gray
            C1 = 0x17;
            C2 = 0x0F;
            break;
        case 2: // light blue
            C1 = 0x35;
            C2 = 0x0F;
            break;
        case 3: // dark blue
            C1 = 0x37;
            C2 = 0x0F;
            break;
        case 4: // green
            C1 = 0x02;
            C2 = 0x0F;
            break;
        case 5: // orange
            C1 = 0x2A;
            C2 = 0x0F;
            break;
        case 6: // red
            C1 = 0x28;
            C2 = 0x0F;
            break;
        case 7: // yellow
            C1 = 0x2C;
            C2 = 0x0F;
            break;
        case 8: // purple
            C1 = 0x05;
            C2 = 0x0F;
            break;
    }

    //Base
    int xOffset = pos.x + borderSize;
    int yOffset = pos.y + borderSize;


    _x = 0;
    _y = 0;
    while(_x < blockSize - (borderSize * 2)){
        while(_y < blockSize - (borderSize * 2)){
            DrawPX(xOffset + _x, yOffset + _y, C1);
            _y++;
        }
        _y = 0;
        DrawPX(xOffset + _y, yOffset + _x, C1);
        _x++;
    }

    //glow
    DrawPX(pos.x + 1, pos.y + 1, C2);
    DrawPX(pos.x + 2, pos.y + 2, C2);
    DrawPX(pos.x + 2, pos.y + 3, C2);
    DrawPX(pos.x + 3, pos.y + 2, C2);

}


void SpawnBlock(int x, int y, char obj[2][4], int color, int rotation){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 4; j++){
            if(obj[i][j] == 1){
               if(rotation == 0){
                    DrawBlock(x + j, y + i, color);
                }else if(rotation == 1){
                    DrawBlock(-i + x + 2, j + y, color);
                }else if(rotation == 2){
                    DrawBlock(x - j, y - i, color);
                }else if(rotation == 3){
                    DrawBlock(i + x + 2, -j + y, color);
                } 
            }
                
        }
    }
}

void ClearBlock(int x, int y, char obj[2][4], int rotation){
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 4; j++){
            if(obj[i][j] == 1){
               if(rotation == 0){
                    DrawBlock(x + j, y + i, 0);
                }else if(rotation == 1){
                    DrawBlock(-i + x + 2, j + y, 0);
                }else if(rotation == 2){
                    DrawBlock(x - j, y - i, 0);
                }else if(rotation == 3){
                    DrawBlock(i + x + 2, -j + y, 0);
                }
            }
        }
    }
}

void MoveBlock(int oldX, int oldY, int newX, int newY){
    struct Position oldPos = GetBlockPos(oldY, oldX);
    struct Position newPos = GetBlockPos(newY, newX);
    for(int i = 0; i < blockSize; i++){
        for(int j = 0; j < blockSize; j++){
            DrawPX(newPos.x + i, newPos.y + j, GetPX(oldPos.x + i, oldPos.y + j));
            DrawPX(oldPos.x + i , oldPos.y + j, 0x00);

        }
    }
    RegisterBlock(newX, newY, GetBlock(oldX, oldY));
    RegisterBlock(oldX, oldY, 0);
   
}
