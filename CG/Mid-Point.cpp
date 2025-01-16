
#include <SDL2/SDL.h>
#include <math.h>
#include <iostream>
#include <conio.h>

using namespace std;

const int windowWidth = 900;
const int windowHeight = 600;

void drawPixel(SDL_Renderer * renderer, int x, int y){
    int centerX = windowHeight/2;
    int centerY = windowWidth/2;
    SDL_RenderDrawPoint(renderer, x + centerX, y + centerY);
}
void circleMidPoint(SDL_Renderer *renderer, int r){
    int x = 0;
    int y = r;
    int p_init = 1 - r;
    int p = 0;
    drawPixel(renderer, x, y);
    while (x < y)
    {
        ++x;
        if (p_init < 0)
        {
            p = p +2 * x +1;
        }
        else
        {
            
        }
        
    }
    
}

int main(int argc, char const *argv[])
{
    int radii, CirCenterX, CirCenterY;

    return 0;
}
