#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


using namespace std;

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 900;
const char* WINDOW_TITLE = "Hello World!";

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());


    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void drawSomething(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white
    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   // red
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH - 400;
    filled_rect.y = SCREEN_HEIGHT - 150;
    filled_rect.w = 320;
    filled_rect.h = 100;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
    SDL_RenderFillRect(renderer, &filled_rect);
}
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                     "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Load texture %s", IMG_GetError());
      }

	return texture;
}

void renderTexture(SDL_Texture *texture, int x, int y,
                   SDL_Renderer* renderer)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
void renderCenteredTexture(SDL_Texture *texture, SDL_Renderer *renderer, int newWidth, int newHeight)
{
    int imgWidth, imgHeight;

    // Lấy kích thước của hình ảnh gốc
    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    // Tính toán tọa độ để căn giữa
    int x = (SCREEN_WIDTH - newWidth) / 2;
    int y = (SCREEN_HEIGHT - newHeight) / 2;

    // Tạo rect để xác định vị trí và kích thước hình ảnh mới
    SDL_Rect destRect = {x, y, newWidth, newHeight};

    // Vẽ texture với kích thước mới
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}
void renderTopLeftTexture(SDL_Texture *texture, SDL_Renderer *renderer, int newWidth, int newHeight)
{
    int imgWidth, imgHeight;

    // Lấy kích thước của hình ảnh
    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    // Tạo rect để xác định vị trí và kích thước hình ảnh
    SDL_Rect destRect = {0, 0, newWidth, newHeight};

    // Vẽ texture
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}
void renderBottomLeftTexture(SDL_Texture *texture, SDL_Renderer *renderer, int newWidth, int newHeight)
{
    int imgWidth, imgHeight;

    // Lấy kích thước của hình ảnh
    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    // Tính toán vị trí để căn chỉnh ở góc dưới trái
    int x = 0;
    int y = SCREEN_HEIGHT - imgHeight;

    // Tạo rect để xác định vị trí và kích thước hình ảnh
    SDL_Rect destRect = {x, y, newWidth, newHeight};

    // Vẽ texture
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}
void renderTopRightTexture(SDL_Texture *texture, SDL_Renderer *renderer, int newWidth, int newHeight)
{
    int imgWidth, imgHeight;

    // Lấy kích thước của hình ảnh
    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    // Tính toán vị trí để căn chỉnh ở góc trên phải
    int x = SCREEN_WIDTH - imgWidth;
    int y = 0;

    // Tạo rect để xác định vị trí và kích thước hình ảnh
    SDL_Rect destRect = {x, y, newWidth, newHeight};

    // Vẽ texture
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}
void renderBottomRightTexture(SDL_Texture *texture, SDL_Renderer *renderer,int newWidth, int newHeight)
{
    int imgWidth, imgHeight;

    // Lấy kích thước của hình ảnh
    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    // Tính toán vị trí để căn chỉnh ở góc dưới phải
    int x = SCREEN_WIDTH - imgWidth;
    int y = SCREEN_HEIGHT - imgHeight;

    // Tạo rect để xác định vị trí và kích thước hình ảnh
    SDL_Rect destRect = {x, y, newWidth, newHeight};

    // Vẽ texture
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}




int main(int argc, char *argv[])
{
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    SDL_Texture* background = loadTexture("Night-Sky.jpg", renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);

     SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    SDL_Texture* spongeBob = loadTexture("Skibidi-Toilet-Wallpaper-11.jpg", renderer);
    renderCenteredTexture(spongeBob, renderer, 300, 450);

    SDL_RenderPresent( renderer );
    waitUntilKeyPressed();

    SDL_DestroyTexture( spongeBob );
    spongeBob = NULL;
    SDL_DestroyTexture( background );
    background = NULL;


    quitSDL(window, renderer);
    return 0;
}



