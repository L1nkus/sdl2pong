#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include <cstdlib>

SDL_DisplayMode DM;

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
SDL_Texture* gBall = NULL;

void loadMedia(){
  SDL_Surface* loadedSurface = IMG_Load("ball.png");
  gBall = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

  SDL_FreeSurface( loadedSurface );
  loadedSurface = NULL;
}

void freeMem(){
  std::cout << "Exiting!\n";
  SDL_DestroyTexture( gBall );
  gBall = NULL;
  SDL_DestroyRenderer( gRenderer );
  gRenderer = NULL;
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
}

int main(int argc, char* argv[]){
  srand( time( NULL ) );
  SDL_Init( SDL_INIT_VIDEO );
  SDL_GetDesktopDisplayMode( 0, &DM );
  gWindow = SDL_CreateWindow( "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DM.w, DM.h, SDL_WINDOW_SHOWN);
  SDL_SetWindowFullscreen( gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP );
  gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

  loadMedia();

  bool quit = false;
  SDL_Event e;
  const int ylength = DM.h/6;
  const int xlength = DM.w/40;
  unsigned int height = DM.h/2 - ylength/2;
  const int heighLengthDelta = DM.h - ylength;
  const int ballSize = DM.w/20;
  float ballYPos = DM.h/2-ballSize/2;
  float ballXPos = DM.w-ballSize-5;
  float Xaddition;
  bool left = true;
  float angle = ( rand() % 90 ) + 45;

  while(!quit){
    if( SDL_PollEvent( &e ) ){
      if( e.type == SDL_QUIT )
        quit = true;
      else if( e.type == SDL_KEYDOWN )
        if( e.key.keysym.sym == SDLK_ESCAPE )
          quit = true;
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if(keystate[SDL_SCANCODE_UP])
    {
      if( height )
        height--;
    }
    if(keystate[SDL_SCANCODE_DOWN])
    {
      if( height < heighLengthDelta )
        height++;
    }

    if(left && ballXPos <= xlength+1){
      if(ballXPos >= xlength && ballYPos+ballSize >= height && ballYPos <= height+ylength){
        left = false;
        std::cout << "Ball hit the rectangle!\n";
        angle = ( rand() % 90 ) + 45;
      }
      else if(ballXPos <= 1){
      left = false;
      std::cout << "Ball hit the left border!\n";
      if(angle > 90)
        angle = 90 - (angle-90);
      else
        angle = 90 + (90-angle);
      }
    }
    else if(ballXPos >= DM.w-1-ballSize){
      left = true;
      std::cout << "Ball hit the right border!\n";
      if(angle > 90)
        angle = 90 - (angle-90);
      else
        angle = 90 + (90-angle);
    }
    if(ballYPos <= 1){
      std::cout << "Ball hit the upper border!\n";
      if(angle > 90)
        angle = 90 - (angle-90);
      else
        angle = 90 + (90-angle);
    }
    else if(ballYPos >= DM.h-ballSize){
      std::cout << "Ball hit the bottom border!\n";
      if(angle > 90)
        angle = 90 - (angle-90);
      else
        angle = 90 + (90-angle);
    }
    if(left){
      Xaddition = 1-(abs(angle-90)/90);
      ballXPos -= Xaddition;
      if(angle > 90)
        ballYPos -= 1-Xaddition;
      else
        ballYPos += 1-Xaddition;
    }
    else{
      Xaddition = 1-(abs(angle-90)/90);
      ballXPos += Xaddition;
      if(angle > 90)
        ballYPos += 1-Xaddition;
      else if(angle < 90)
        ballYPos -= 1-Xaddition;
    }

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    //std::cout << "BallPos X: " << ballXPos << " Y: " << ballYPos << std::endl;
    SDL_Rect rectBall = {ballXPos, ballYPos, ballSize, ballSize};
    SDL_RenderCopy( gRenderer, gBall, NULL, &rectBall );

    SDL_Rect gRect = {0, height, xlength, ylength};
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0, 0xFF );
    SDL_RenderFillRect( gRenderer, &gRect );
    SDL_RenderPresent( gRenderer );
  }
  freeMem();
  return 0;
}
