//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// height and width of game's paddle in pixels
#define PADDLE_HEIGHT 10
#define PADDLE_WIDTH 80

// paddle position initially
#define POSITION_WIDTH WIDTH / 2 - PADDLE_WIDTH / 2
#define POSITION_HEIGHT HEIGHT - (HEIGHT / 10)

// ball position initally
#define X_BALL  WIDTH / 2 - RADIUS
#define Y_BALL  HEIGHT / 2 - RADIUS



// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // set ball movement to false initially
    bool ball_movement = false;
    
    // velocity of the ball
    double x_velocity = drand48();
    if (x_velocity >= 0.5)
    {
        x_velocity = x_velocity * 4;
    }
    else 
        x_velocity = -x_velocity * 10;
        
    double y_velocity = 2.0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
    
        
        // paddle movements
        
        GEvent event = getNextEvent(MOUSE_EVENT);
        
               
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_CLICKED)
                ball_movement = true;
            
            if (getEventType(event) == MOUSE_MOVED && ball_movement == true)
            {
                if (getX(event) + PADDLE_WIDTH >= WIDTH)
                {
                    setLocation(paddle, WIDTH - PADDLE_WIDTH, POSITION_HEIGHT);
                }
                else if (getX(event) <= 0)
                {
                    setLocation(paddle, 0, POSITION_HEIGHT);
                }
                else 
                {
                    double x = getX(event) ;
                    setLocation(paddle, x, POSITION_HEIGHT);
                }    
            }
        }
        
        
        // ball movements
        

        
        if(ball_movement == true)
        {          
            
            move(ball, x_velocity, y_velocity);
            
            // bounce the ball 
            if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                x_velocity = -x_velocity;
            }
            
            else if (getX(ball) <= 0)
            {
                x_velocity = -x_velocity;
            }
            
            else if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                lives = lives - 1;
                ball_movement = false;
                setLocation(ball, X_BALL, Y_BALL);
                //waitForClick();
                               
            }
            
            else if (getY(ball) <=0)
            {
                y_velocity = -y_velocity;
            }
            
            pause(10);
            
        } 
        
        // collision and boucing
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (object == paddle)
            {
                if (y_velocity > 0)             
                    y_velocity = -y_velocity - 0.1;
            }
            
            else if (strcmp(getType(object), "GRect") == 0)
            {
                y_velocity = -y_velocity;
                removeGWindow(window, object);
                points += 1;
                updateScoreboard(window, label, points);
            }
            
        }
        
        if (lives == 0 || points == ROWS * COLS)
        {
            break;
        }
        
        
         
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // set the gap between bricks
    int GAP = 4; 
    
    // set width and height of the bricks
    int brick_width = (WIDTH - (GAP * (COLS - 1))) / COLS;
    int brick_height = ((HEIGHT / 6) - (GAP * (ROWS - 1))) / ROWS;
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(brick_width * j + GAP * (j + 1) , (HEIGHT / 30) + brick_height * i + GAP * (i + 1), brick_width, brick_height);
            
            // set the color of the brick per each row
            if (i == 1)
                setColor(brick, "CYAN");
            else if (i == 2)
                setColor(brick, "BLUE");
            else if (i == 3)
                setColor(brick, "RED");
            else if (i == 4)
                setColor(brick, "YELLOW");
            else 
                setColor(brick, "GREEN");       
                
            // fill the bricks and add them to the window
            setFilled(brick, true);
            add(window, brick);
        } 
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
   
    GOval ball = newGOval(X_BALL , Y_BALL, RADIUS * 2, RADIUS *2);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    
    GRect rect = newGRect(POSITION_WIDTH, POSITION_HEIGHT, PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(rect, true);
    setColor(rect, "BLACK");
    add(window, rect);
    
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    
    GLabel label;
    
    label = newGLabel("0");
    setFont(label, "SansSerif-36");
    double x = (WIDTH - getWidth(label)) / 2 ;
    double y = (HEIGHT + getFontAscent(label)) / 2 - (RADIUS * 2) - 10;
    setLocation(label, x, y);
    setColor(label, "GREEN");
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
