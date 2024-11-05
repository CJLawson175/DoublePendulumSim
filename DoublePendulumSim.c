#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

#define G 1.5          // Gravitational constant
#define DT 0.01        // Time step (s)
#define WIDTH 1000     // Window width
#define HEIGHT 800     // Window height
#define TWO_PI (1 * M_PI) // Define Pi

double M1_ratio, M2_ratio; // Mass ratio values
double L1_ratio, L2_ratio; // Length ratio values
double IC1, IC2;           // Initial Conditions

typedef struct {
    double theta1;   // Angle of pendulum 1 (radians)
    double omega1;   // Angular velocity of pendulum 1 (radians/s)
    double theta2;   // Angle of pendulum 2 (radians)
    double omega2;   // Angular velocity of pendulum 2 (radians/s)
} PendulumState;

// Function initializations
PendulumState update_state(PendulumState state, double L1, double L2, double M1, double M2);
void draw_pendulum(SDL_Renderer *renderer, PendulumState state, double L1, double L2);
void InputFunction(double *M1_r, double *M2_r, double *L1_r, double *L2_r, double *IC1, double *IC2);

int main(int argc, char *argv[]) { 
    // Prompt the User for Mass/Length ratios and IC's
    InputFunction(&M1_ratio, &M2_ratio, &L1_ratio, &L2_ratio, &IC1, &IC2);
    
    // Multiplies the provided multiple of pi with pi for initial angle
    IC1 = IC1 * M_PI;
    IC2 = IC2 * M_PI;
    
    // Calculate masses and lengths based on the ratios
    double M1 = M1_ratio;
    double M2 = M2_ratio;
    double L1 = L1_ratio * 100.0;
    double L2 = L2_ratio * 100.0;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Double Pendulum Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    // Initial conditions
    PendulumState state = {IC1 + (M_PI / 2), 0, IC2 + (M_PI / 2), 0}; // Initial angles (radians)

    // Main loop
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Update the state of the pendulum
        state = update_state(state, L1, L2, M1, M2);

        // Draw the pendulum
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set background color to white
        SDL_RenderClear(renderer);
        draw_pendulum(renderer, state, L1, L2);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

PendulumState update_state(PendulumState state, double L1, double L2, double M1, double M2) {
    double delta_theta = state.theta2 - state.theta1;

    // Calculate the accelerations using the equations of motion for the double pendulum resulting from Euler-Lagrange Eq's
    double denom1 = L1 * (2 * M1 + M2 - M2 * cos(2 * state.theta1 - 2 * state.theta2));
    double denom2 = L2 * (2 * M1 + M2 - M2 * cos(2 * state.theta1 - 2 * state.theta2));

    double alpha1 = (-G * (2 * M1 + M2) * sin(state.theta1) - M2 * G * sin(state.theta1 - 2 * state.theta2) -
                    2 * sin(state.theta1 - state.theta2) * M2 * ((state.omega2 * state.omega2) * L2 + (state.omega1 * state.omega1) * L1 * cos(state.theta1 - state.theta2)))
                    / denom1;

    double alpha2 = (2 * sin(state.theta1 - state.theta2) * ((state.omega1 * state.omega1) * L1 * (M1 + M2) +
                    G * (M1 + M2) * cos(state.theta1) + (state.omega2 * state.omega2) * L2 * M2 * cos(state.theta1 - state.theta2)))
                    / denom2;

    // Update the angular velocities and angles
    state.omega1 += alpha1 * DT;
    state.omega2 += alpha2 * DT;
    state.theta1 += state.omega1 * DT;
    state.theta2 += state.omega2 * DT;

    return state;
}

void draw_pendulum(SDL_Renderer *renderer, PendulumState state, double L1, double L2) {
    // Calculate the positions of the pendulum
    double x1 = WIDTH / 2 + L1 * sin(state.theta1);
    double y1 = HEIGHT / 2 + L1 * cos(state.theta1);
    double x2 = x1 + L2 * sin(state.theta2);
    double y2 = y1 + L2 * cos(state.theta2);

    // Draw pendulum 1
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for pendulum 1
    SDL_RenderDrawLine(renderer, WIDTH / 2, HEIGHT / 2, x1, y1);
    SDL_RenderFillRect(renderer, &(SDL_Rect){(int)(x1 - 5), (int)(y1 - 5), 10, 10}); // Mass of pendulum 1

    // Draw pendulum 2
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color for pendulum 2
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    SDL_RenderFillRect(renderer, &(SDL_Rect){(int)(x2 - 5), (int)(y2 - 5), 10, 10}); // Mass of pendulum 2
}

void InputFunction(double *M1_r, double *M2_r, double *L1_r, double *L2_r, double *IC1, double *IC2){
    // Prompts and accepts input from User for mass/length ratios, and Initial angles
    printf("Enter mass ratio (M1:M2) e.g. 1 2 for 1:2: ");
    scanf("%lf %lf", M1_r, M2_r);
    
    // While loop to prompt the user to choose a valid number that will fit in the display
    while(1) {
        printf("Enter length ratio (L1:L2) where L1 - L2 <= 4: ");
        scanf("%lf %lf", L1_r, L2_r);
        double absolutevalue = fabs(*L1_r - *L2_r);
        if (absolutevalue > 4) {
            printf("Please Enter values whose difference is not greater than 4: \n");
        } else {
            break;
        }
    }
    
    printf("Enter Initial angle for rod1 and rod2 in radians as multiples of pi. \nExample: (pi/2, 2pi) = 0.5 2 OR 0.5 0 \nEnter Values: ");
    scanf("%lf %lf", IC1, IC2);
	
}
