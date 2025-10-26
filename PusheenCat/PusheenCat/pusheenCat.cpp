#include <iostream>
#include <SDL3/SDL.h>
#include <cmath>
#define M_PI 3.14159265358979323846

static SDL_Renderer* renderer = NULL;
static SDL_Window* window = NULL;
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    SDL_SetAppMetadata("Example Renderer Lines", "1.0", "com.example.renderer-lines");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Cat", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  
    }
    return SDL_APP_CONTINUE;  
}


void polygon(SDL_Renderer * renderer, int n, double x, double y, double radius)
{
    for (int side = 0; side < n; side++)
    {
        double x1 = radius * cos(side * 2.0 * M_PI / n) + x;
        double y1 = radius * sin(side * 2.0 * M_PI / n) + y;
        double x2 = radius * cos((side + 1) * 2.0 * M_PI / n) + x;
        double y2 = radius * sin((side + 1) * 2.0 * M_PI / n) + y;

        for (double t = 0; t <= 1.0; t += 0.002)
        {
            double px1 = x + t * (x1 - x);
            double py1 = y + t * (y1 - y);
            double px2 = x + t * (x2 - x);
            double py2 = y + t * (y2 - y);

            SDL_RenderLine(renderer, (int)px1, (int)py1, (int)px2, (int)py2);
        }
    }
}
void halfCircle(SDL_Renderer* renderer, double x, double y, double radius, int direction)
{

    int startDeg = (direction == 0) ? 0 : 180;
    int endDeg = (direction == 0) ? 180 : 360;

    for (int angle = startDeg; angle <= endDeg; angle++)
    {
        double rad = angle * M_PI ;
        double x1 = x + radius * cos(rad);
        double y1 = y + radius * sin(rad);

       
        SDL_RenderLine(renderer, (int)x, (int)y, (int)x1, (int)y1);
    }
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    int i;

 
    static const SDL_FPoint line_points[] = {
        { 100, 354 }, { 220, 230 }, { 140, 230 }, { 320, 100 }, { 500, 230 },
        { 420, 230 }, { 540, 354 }, { 400, 354 }, { 100, 354 }
    };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  
    SDL_RenderClear(renderer);  

    //body
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(renderer, 180, 110, 160, 100);
    SDL_RenderLine(renderer, 160, 100, 0, 100);
    SDL_RenderLine(renderer, 320, 400, 0, 400);
    SDL_RenderLine(renderer, 320, 400, 370, 350);
    SDL_RenderLine(renderer, 370, 350, 370, 200);
    SDL_RenderLine(renderer, 370, 200, 200, 200);
	polygon(renderer, 200, 0, 120, 20);
    polygon(renderer, 200, 80, 120, 20);
    //paws
    SDL_RenderLine(renderer, 320, 400, 310, 420);
    SDL_RenderLine(renderer, 310, 420, 300, 430);
    SDL_RenderLine(renderer, 300, 430, 280, 430);
    SDL_RenderLine(renderer, 280, 430, 270, 420);
    SDL_RenderLine(renderer, 270, 420, 260, 400);
    
    SDL_RenderLine(renderer, 240, 400, 230, 420);
    SDL_RenderLine(renderer, 230, 420, 220, 430);
    SDL_RenderLine(renderer, 220, 430, 200, 430);
    SDL_RenderLine(renderer, 200, 430, 190, 420);
    SDL_RenderLine(renderer, 190, 420, 180, 400);

    SDL_RenderLine(renderer, 100, 400, 90, 420);
    SDL_RenderLine(renderer, 90, 420, 80, 430);
    SDL_RenderLine(renderer, 80, 430, 60, 430);
    SDL_RenderLine(renderer, 60, 430, 50, 420);
    SDL_RenderLine(renderer, 50, 420, 40, 400);

    SDL_RenderLine(renderer, 30, 400, 20, 420);
    SDL_RenderLine(renderer, 20, 420, 10, 430);
    SDL_RenderLine(renderer, 10, 430, 0, 430);
    //head
    SDL_RenderLine(renderer, 200, 200, 180, 180);
    SDL_RenderLine(renderer, 370, 200, 390, 180);
    SDL_RenderLine(renderer, 180, 180, 180, 90);
    SDL_RenderLine(renderer, 390, 180, 390, 90);
    SDL_RenderLine(renderer, 390, 90, 360, 50);
    SDL_RenderLine(renderer, 180, 90, 210, 50);
	SDL_RenderLine(renderer, 210, 50, 360, 50);
    //ears
    SDL_RenderLine(renderer, 390, 90, 385, 20);
    SDL_RenderLine(renderer, 180, 90, 185, 20);
    SDL_RenderLine(renderer, 385, 20, 360, 50);
    SDL_RenderLine(renderer, 185, 20, 210, 50);
    //eyes
    polygon(renderer, 301, 325, 130, 6);
    polygon(renderer, 301, 255, 130, 6);
    //mouth
    SDL_RenderLine(renderer, 290, 140, 290, 160);
	halfCircle(renderer, 285, 160, 5, 0);
    halfCircle(renderer, 295, 160, 5, 0);
	//moustache
	SDL_RenderLine(renderer, 220, 130, 185, 120);
	SDL_RenderLine(renderer, 220, 140, 185, 150);
	SDL_RenderLine(renderer, 360, 130, 385, 120);
    SDL_RenderLine(renderer, 360, 140, 385, 150);



    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
}
int main(int argc, char* argv[])
{
    if (SDL_AppInit(NULL, argc, argv) != SDL_APP_CONTINUE)
        return 1;

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (SDL_AppEvent(NULL, &event) != SDL_APP_CONTINUE) {
                running = false;
                break;
            }
        }

        if (SDL_AppIterate(NULL) != SDL_APP_CONTINUE)
            break;

        SDL_RenderPresent(renderer);
        SDL_Delay(16); 
    }
    SDL_AppQuit(NULL, SDL_APP_SUCCESS);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
