#include "stdio.h"
#include "stdlib.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "time.h"

#include "formulas.h"
#include "wall.h"
#include "robot.h"

int done = 0;


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    clock_t start_time, end_time;
    int msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    int left_sensor, right_sensor,front_sensor=0;

    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
    
    /*
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
     */
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/4, OVERALL_WINDOW_HEIGHT/4-50, 10, OVERALL_WINDOW_HEIGHT/4*3+50);
        insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/4, OVERALL_WINDOW_HEIGHT/4-50, OVERALL_WINDOW_WIDTH/3*2-60, 10);
        insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/4+100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/4+20);
        insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/4+100, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/8, 10);
        insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/4, OVERALL_WINDOW_HEIGHT/2+10, 90, 10);
        insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/4+180, OVERALL_WINDOW_HEIGHT/4-50+100, 10, 240);
        insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/4+100, OVERALL_WINDOW_HEIGHT/4-50+100, 180, 10);
        insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/4+400-40, OVERALL_WINDOW_HEIGHT/4-50, 10, 110);
        insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/4+280, OVERALL_WINDOW_HEIGHT/4-50+200-10, 10, 80);
        insertAndSetFirstWall(&head, 10, OVERALL_WINDOW_WIDTH/4+280, OVERALL_WINDOW_HEIGHT/4-50+200-10, 70, 10);
        insertAndSetFirstWall(&head, 11, OVERALL_WINDOW_WIDTH/4+280+70, OVERALL_WINDOW_HEIGHT/4-50+200-10, 10, 80);
        insertAndSetFirstWall(&head, 12, OVERALL_WINDOW_WIDTH/4+280, OVERALL_WINDOW_HEIGHT/4-50+280-10, 80, 10);
        insertAndSetFirstWall(&head, 13, OVERALL_WINDOW_WIDTH/4+400-40, OVERALL_WINDOW_HEIGHT/4-50+100, 100-10, 10);
        insertAndSetFirstWall(&head, 14, OVERALL_WINDOW_WIDTH/4+500-60, OVERALL_WINDOW_HEIGHT/4-50+100, 10, 240);
        insertAndSetFirstWall(&head, 15, OVERALL_WINDOW_WIDTH/4+180, OVERALL_WINDOW_HEIGHT/4-50+340, 90, 10);
        insertAndSetFirstWall(&head, 16, OVERALL_WINDOW_WIDTH/4+280+80, OVERALL_WINDOW_HEIGHT/4-50+340, 90, 10);
        insertAndSetFirstWall(&head, 17, OVERALL_WINDOW_WIDTH/4+280-10, OVERALL_WINDOW_HEIGHT/4-50+340, 10, 70);
        insertAndSetFirstWall(&head, 18, OVERALL_WINDOW_WIDTH/4+280+80, OVERALL_WINDOW_HEIGHT/4-50+340, 10, 70);
        insertAndSetFirstWall(&head, 19, OVERALL_WINDOW_WIDTH/4+280-10, OVERALL_WINDOW_HEIGHT-10, 90, 10);
    setup_robot(&robot);
    updateAllWalls(head, renderer);

    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, left_sensor, right_sensor, front_sensor);
            robotMotorMove(&robot);

        //Check if robot reaches endpoint. and check sensor values
        if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }
        else if(checkRobotHitWalls(&robot, head))
            robotCrash(&robot);
        //Otherwise compute sensor information
        else {
            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            front_sensor = checkRobotSensorFrontAllWalls(&robot, head);
            
            if (left_sensor > 0 || right_sensor > 0 || front_sensor > 0) printf("L: %d  F: %d  R: %d\n", left_sensor, front_sensor, right_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                start_time = clock();
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
