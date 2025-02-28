#define GRAPHIC_MEMORY 0x0A0000
#define SCREEN_WIDTH 80

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80


void DrawPX(int x, int y, int color);
void Print(const char *str);
void debugMap(int map[20][10]);
void debugPixel(int x, int y, int color);
int GetPX(int x, int y);
void ClearScreen();
int Rand(int min, int max);
int nextRandom();

int DebugMap[20][10];



void DrawPX(int x, int y, int color){
    int pos = 0;
    pos += x;
    pos += (y * 320);
    volatile char *video = (volatile char*) GRAPHIC_MEMORY;
    video[pos] = color;
    return;
}

int GetPX(int x, int y){
    int pos = 0;
    pos += x;
    pos += (y * 320);
    volatile char *video = (volatile char*) GRAPHIC_MEMORY;
    return video[pos];
}
void Print(const char *str) {
    volatile char *video = (volatile char*) VIDEO_MEMORY;
    int i = 0;
    
    while (str[i] != '\0') {
        video[i * 2] = str[i];      // Write the character
        video[i * 2 + 1] = 0x07;    // Set the color (light gray on black)
        i++;
    }
    return;
}

void debugMap(int map[20][10]){
    //draw walls
    for(int i = 0; i < 40; i++){
        DrawPX(9, i + 5, 0x0F);
        DrawPX(30, i + 5, 0x0F);
    }
    for(int i = 0; i < 20; i++){
        DrawPX(i + 10, 5, 0x0F);
        DrawPX(i + 10, 45, 0x0F);
    }

    // draw block 40/20
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            if(map[i][j] == 1 && DebugMap[i][j] == 0){
                DrawPX(j * 2 + 10, i * 2 + 5, 0x1F);
                DrawPX(j * 2 + 11, i * 2 + 5, 0x1F);
                DrawPX(j * 2 + 10, i * 2 + 6, 0x1F);
                DrawPX(j * 2 + 11, i * 2 + 6, 0x1F);
            }
            if(map[i][j] == 0 && DebugMap[i][j] == 0){
                DrawPX(j * 2 + 10, i * 2 + 5, 0x00);
                DrawPX(j * 2 + 11, i * 2 + 5, 0x00);
                DrawPX(j * 2 + 10, i * 2 + 6, 0x00);
                DrawPX(j * 2 + 11, i * 2 + 6, 0x00);
            }
        }
    }
}

void ClearScreen(){
    for(int i = 0; i < 320; i++){
        for(int j = 0; j < 200; j++){
            DrawPX(i, j, 0x00);
        }
    }
}

int DebugMap[20][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
void debugPixel(int x, int y, int color){
    DebugMap[x][y] = 1;
    DrawPX(y * 2 + 10, x * 2 + 5, color);
    DrawPX(y * 2 + 11, x * 2 + 5, color);
    DrawPX(y * 2 + 10, x * 2 + 6, color);
    DrawPX(y * 2 + 11, x * 2 + 6, color);
}

volatile unsigned int seed;

int nextRandom(){
    seed = seed * 1103515245 + 12345;
    return seed % 65536;
}

int Rand(int min, int max){
    if(max <= min){
        return min;
    }
    int range = max - min;
    return min + (nextRandom() % range);
}