#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SCREEN_WIDTH = 409;
const int SCREEN_HEIGHT = 659;
const int GRID_SIZE = 4;
const int CELL_SIZE = 90;
const int PADDING = 10;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* tileTextures[12] = {nullptr};

int board[GRID_SIZE][GRID_SIZE] = {0};

// Hàm load ảnh số
SDL_Texture* loadTexture(const string& path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        cerr << "ERROR: " << path << " SDL_image Error: " << IMG_GetError() << endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

// Khởi tạo SDL
bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;

    // Load ảnh các số
    tileTextures[1] = loadTexture("2.png");
    tileTextures[2] = loadTexture("4.png");
    tileTextures[3] = loadTexture("8.png");
    tileTextures[4] = loadTexture("16.png");
    tileTextures[5] = loadTexture("32.png");
    tileTextures[6] = loadTexture("64.png");
    tileTextures[7] = loadTexture("128.png");
    tileTextures[8] = loadTexture("256.png");
    tileTextures[9] = loadTexture("512.png");
    tileTextures[10] = loadTexture("1024.png");
    tileTextures[11] = loadTexture("2048.png");

    return true;
}

// Lấy chỉ số ảnh tương ứng với giá trị số
int getTileIndex(int value) {
    if (value == 0) return 0;
    int index = 1, num = 2;
    while (num < value && index < 11) {
        num *= 2;
        index++;
    }
    return index;
}

// Hiển thị bảng game
void renderBoard() {
    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_RenderClear(renderer);

    const int OFFSET_Y = 250;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int x = j * (CELL_SIZE + PADDING) + PADDING;
            int y = i * (CELL_SIZE + PADDING) + PADDING + OFFSET_Y;
            int tileIndex = getTileIndex(board[i][j]);

            if (tileTextures[tileIndex]) {
                SDL_Rect tileRect = {x, y, CELL_SIZE, CELL_SIZE};
                SDL_RenderCopy(renderer, tileTextures[tileIndex], nullptr, &tileRect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

// Hàm di chuyển
bool moveLeft() {
    bool moved = false;
    for (int i = 0; i < GRID_SIZE; i++) {
        int target = 0;
        int lastValue = 0;
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] != 0) {
                if (board[i][j] == lastValue) {
                    board[i][target - 1] *= 2;
                    board[i][j] = 0;
                    lastValue = 0;
                    moved = true;
                } else {
                    if (j != target) {
                        board[i][target] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    lastValue = board[i][target];
                    target++;
                }
            }
        }
    }
    return moved;
}

bool moveRight() {
    bool moved = false;
    for (int i = 0; i < GRID_SIZE; i++) {
        int target = GRID_SIZE - 1;
        int lastValue = 0;
        for (int j = GRID_SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (board[i][j] == lastValue) {
                    board[i][target + 1] *= 2;
                    board[i][j] = 0;
                    lastValue = 0;
                    moved = true;
                } else {
                    if (j != target) {
                        board[i][target] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    lastValue = board[i][target];
                    target--;
                }
            }
        }
    }
    return moved;
}

bool moveUp() {
    bool moved = false;
    for (int j = 0; j < GRID_SIZE; j++) { // Duyệt từng cột
        int target = 0;
        int lastValue = 0;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (board[i][j] != 0) {
                if (board[i][j] == lastValue) {
                    board[target - 1][j] *= 2;
                    board[i][j] = 0;
                    lastValue = 0;
                    moved = true;
                } else {
                    if (i != target) {
                        board[target][j] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    lastValue = board[target][j];
                    target++;
                }
            }
        }
    }
    return moved;
}

bool moveDown() {
    bool moved = false;
    for (int j = 0; j < GRID_SIZE; j++) { // Duyệt từng cột
        int target = GRID_SIZE - 1;
        int lastValue = 0;
        for (int i = GRID_SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (board[i][j] == lastValue) {
                    board[target + 1][j] *= 2;
                    board[i][j] = 0;
                    lastValue = 0;
                    moved = true;
                } else {
                    if (i != target) {
                        board[target][j] = board[i][j];
                        board[i][j] = 0;
                        moved = true;
                    }
                    lastValue = board[target][j];
                    target--;
                }
            }
        }
    }
    return moved;
}


// Hàm thêm số 2 vào vị trí ngẫu nhiên
void addRandomTile() {
    int emptyTiles[GRID_SIZE * GRID_SIZE][2], count = 0;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (board[i][j] == 0) {
                emptyTiles[count][0] = i;
                emptyTiles[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int r = rand() % count;
        board[emptyTiles[r][0]][emptyTiles[r][1]] = (rand() % 10 < 9) ? 2 : 4;
    }
}

// Xử lý sự kiện bàn phím
void handleInput(SDL_Event& event) {
    bool moved = false;
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT: moved = moveLeft(); break;
            case SDLK_RIGHT: moved = moveRight(); break;
            case SDLK_UP: moved = moveUp(); break;
            case SDLK_DOWN: moved = moveDown(); break;
        }
        if (moved) addRandomTile();
    }
}

// Dọn dẹp bộ nhớ
void closeSDL() {
    for (int i = 0; i < 12; i++) if (tileTextures[i]) SDL_DestroyTexture(tileTextures[i]);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

bool checkWin(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==2048){return true;}
        }
    }
    return false;
}

bool canMove() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) return true;  // Còn ô trống
            if (j < 3 && board[i][j] == board[i][j + 1]) return true; // Có thể gộp ngang
            if (i < 3 && board[i][j] == board[i + 1][j]) return true; // Có thể gộp dọc
        }
    }
    return false;
}
SDL_Texture* gameOverTexture = nullptr;

void loadGameOverImage() {
    SDL_Surface* tempSurface = IMG_Load("gameover.jpg");
    if (!tempSurface) {
        cout << "Failed to load Game Over image: " << IMG_GetError() << endl;
        return;
    }
    gameOverTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_RenderPresent(renderer);
}
void renderGameOver() {
    if (!gameOverTexture) return;

    SDL_Rect gameOverRect = { 50, 200, 300, 100 };  // Vị trí và kích thước ảnh
    SDL_RenderCopy(renderer, gameOverTexture, nullptr, &gameOverRect);
    SDL_RenderPresent(renderer);
}



int main(int argc, char* argv[]) {
    srand(time(nullptr));
    if (!initSDL()) return -1;

    addRandomTile();
    addRandomTile();

    bool running = true;
    SDL_Event event;
    while (running) {

        if (checkWin()) {
            cout << "You Win!" << endl;
            break;
        }
        if (!canMove()) {
            renderGameOver();
            SDL_Delay(3000);  // Dừng lại 3 giây
            running = false;   // Thoát game
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            handleInput(event);
        }
        renderBoard();
        SDL_Delay(100);
    }

    closeSDL();
    return 0;
}
