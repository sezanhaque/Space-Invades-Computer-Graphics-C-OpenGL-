#include <windows.h>
#include <mmsystem.h>   // To play ".wav" sound and it must come after "<windows.h>"
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "imageloader.h"
/*
Here imageloader.h
https://github.com/badgeek/OpenGL-tutorial/tree/master/GLvbo
*/

static int riverFlag = 0;

bool start = false;
bool gameover = false;
bool pause = false;

// coordinates for backgorund image
float backgorund_X_min = 0, backgorund_Y_min = 0, backgorund_X_max = 1200, backgorund_Y_max = 1000;

// coordinates for spaceship image
float spaceship_X_min = 500, spaceship_Y_min = 800, spaceship_X_max = 650, spaceship_Y_max = 1000;

float enemy_1_X_min = 200, enemy_1_Y_min = 128, enemy_1_X_max = 328, enemy_1_Y_max = 228;
float enemy_1_fixed_Y = 128;

float enemy_count = 0;


float cloud1X1 = 400 , cloud1X2 = 1200 , cloud1Y1 =100 , cloud1Y2 = -100 ;
float cloud2X1 = -500 , cloud2X2 = 200 , cloud2Y1 = 200 , cloud2Y2 = -200 ;

float logoX1 =300 , logoX2 =900 , logoY1 =500 , logoY2 =150 ;
float tutorialX1 =250, tutorialX2=1000, tutorialY1 =800 , tutorialY2 =500;

float river1X1 = 0 , river1X2 =1200 , river1Y1 = 1450 ,river1Y2 = 850 ;
float river2X1 = -1200 , river2X2 =-0 , river2Y1 = 1450 ,river2Y2 = 850 ;

float gameoverX1 = 300, gameoverX2 =900, gameoverY1 =550 , gameoverY2 =350 ;
float yourScoreX1 = 460, yourScoreX2 =660, yourScoreY1 =600 , yourScoreY2 =550 ;
float pauseX1 = 300, pauseX2 = 900 , pauseY1 = 800, pauseY2 = 200;

float planeX1 =0, planeY1 = 150, planeX2 =200 , planeY2 =150;
float bombX1 = 50 , bombX2 =60 , bombY1 = 280 , bombY2 = 80 ;

float shipX1[1000] = { 1200};
float shipY1[1000] = { 900 };
float shipX2 = 100, shipY2 =100 ;

int length = 0;
float fighterPlaneX[1000] = {0};
float fighterPlaneY[1000] = {0};

int no_of_ships = 1;
int delay_time = 0;
int destroy = 0;
int collisionCount = 0;


// Make the image into a texture, and return the id of the texture
// Takes the image object and makes it into an OpenGL Texture
GLuint loadTexture(imageloader* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId);            // Make room for out texture
    glBindTexture(GL_TEXTURE_2D, textureId); // Tell OpenGL which texture to edit
    // Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    return textureId;
}

// GLunit = GL type unsigned int, for loading texture
GLuint texture_background;
GLuint texture_game_background;
GLuint texture_spaceship;
GLuint texture_enemy_1;
GLuint texture_gameover;
GLuint texture_your_score;
GLuint texture_pause;
GLuint _texturePlane;
GLuint _textureBomb;
GLuint _textureShip;

void myInit(void)
{
    //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); //Switch to the drawing perspective
    glLoadIdentity();           //Reset the drawing perspective

    // glClearColor(1.0, 1.0, 1.0, 0.0);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    gluOrtho2D(0.0, 1200, 1000, 0.0);

    // Loading BMP image file into an "imageloader" object
    imageloader *background = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/mainmenu.bmp");
    imageloader *game_background = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/game.bmp");
    imageloader *spaceship = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/spaceship_5.bmp");
    imageloader *enemy_1 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/UFO_1.bmp");
    imageloader *plane = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Plane.bmp");
    imageloader *bomb = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Atomic Bomb.bmp");
    imageloader *ship = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Ship.bmp");
    imageloader *gameover = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Game Over.bmp");
    imageloader *yourScore = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Your Score.bmp");
    imageloader *pause = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Paused.bmp");

    // "loadTexture" takes the image object and makes it into an OpenGL Texture
    texture_background = loadTexture(background);
    texture_game_background = loadTexture(game_background);
    texture_spaceship = loadTexture(spaceship);
    texture_enemy_1 = loadTexture(enemy_1);
    _texturePlane = loadTexture(plane);
    _textureBomb = loadTexture(bomb);
    _textureShip = loadTexture(ship);
    texture_gameover = loadTexture(gameover);
    texture_your_score = loadTexture(yourScore);
    texture_pause = loadTexture(pause);

    // We are deleting the Image object because OpenGL made a copy of the pixels array
    delete background;
    delete game_background;
    delete spaceship;
    delete enemy_1;
    delete plane;
    delete bomb;
    delete ship;
    delete gameover;
    delete yourScore;
    delete pause;

    glutSwapBuffers(); //Send the 3D scene to the screen
}

void drawHealthBarRight()
{

    if (collisionCount == 0)
    {
        glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glVertex2i(900, 140);
        glVertex2i(1190, 140);
        glVertex2i(1190, 120);
        glVertex2i(900, 120);
        glEnd();
    }

    else if (collisionCount == 1)
    {
        glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glVertex2i(950, 140);
        glVertex2i(1190, 140);
        glVertex2i(1190, 120);
        glVertex2i(950, 120);
        glEnd();
    }

    else if (collisionCount == 2)
    {
        glBegin(GL_QUADS);
        glColor3f(0, 0, 1);
        glVertex2i(1000, 140);
        glVertex2i(1190, 140);
        glVertex2i(1190, 120);
        glVertex2i(1000, 120);
        glEnd();
    }

    else if (collisionCount == 3)
    {
        glBegin(GL_QUADS);
        glColor3f(0, 0, 1);
        glVertex2i(1050, 140);
        glVertex2i(1190, 140);
        glVertex2i(1190, 120);
        glVertex2i(1050, 120);
        glEnd();
    }

    else if (collisionCount == 4)
    {
        glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2i(1100, 140);
        glVertex2i(1190, 140);
        glVertex2i(1190, 120);
        glVertex2i(1100, 120);
        glEnd();
    }

    else if (collisionCount == 5)
    {
        glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2i(1150, 140);
        glVertex2i(1190, 140);
        glVertex2i(1190, 120);
        glVertex2i(1150, 120);
        glEnd();
    }
}

void drawBitmapText(char *string, float x, float y, float z){

        glColor3f(0.0, 0.0, 1.0);

        char *c;
        glRasterPos3f(x, y, z);

        for (c = string; *c != '\0'; c++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }

}

void drawBitmapText2(char *string, float x, float y, float z){

        glColor3f(0.0, 0.0, 1.0);

        char *c;
        glRasterPos3f(x, y, z);

        for (c = string; *c != '\0'; c++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        }

}



/* --------- END : CUSTOM FUNTIONS --------- */



/* --------- START : TEXTURE FUNCTIONS --------- */

void background()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_background); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(backgorund_X_min, backgorund_Y_max);

    glTexCoord2i(1, 0); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(backgorund_X_max, backgorund_Y_max);

    glTexCoord2i(1, 1); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(backgorund_X_max, backgorund_Y_min);

    glTexCoord2i(0, 1); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(backgorund_X_min, backgorund_Y_min);

    glEnd();
}
void game_background()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_game_background); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(backgorund_X_min, backgorund_Y_max);

    glTexCoord2i(1, 0); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(backgorund_X_max, backgorund_Y_max);

    glTexCoord2i(1, 1); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(backgorund_X_max, backgorund_Y_min);

    glTexCoord2i(0, 1); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(backgorund_X_min, backgorund_Y_min);

    glEnd();
}

void spaceship()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_spaceship); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(spaceship_X_min, spaceship_Y_max);

    glTexCoord2i(1, 0); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(spaceship_X_max, spaceship_Y_max);

    glTexCoord2i(1, 1); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(spaceship_X_max, spaceship_Y_min);

    glTexCoord2i(0, 1); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(spaceship_X_min, spaceship_Y_min);

    glEnd();
}

void plane()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texturePlane);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    glTexCoord2i(0, 0);
    glVertex2i(planeX1, planeY1 + planeY2);

    glTexCoord2i(0, 1);
    glVertex2i(planeX1, planeY2);

    glTexCoord2i(1, 1);
    glVertex2i(planeX1 + planeX2, planeY2);

    glTexCoord2i(1, 0);
    glVertex2i(planeX1 + planeX2, planeY1 + planeY2);
    glEnd();
}

void pause_game()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_pause);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    glTexCoord2i(0, 0);
    glVertex2i(pauseX1, pauseY1);

    glTexCoord2i(0, 1);
    glVertex2i(pauseX1, pauseY2);

    glTexCoord2i(1, 1);
    glVertex2i(pauseX2, pauseY2);

    glTexCoord2i(1, 0);
    glVertex2i(pauseX2, pauseY1);
    glEnd();
}

void bomb(float bombX1, float bombY1)
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureBomb);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    glTexCoord2i(0, 0);
    glVertex2i(bombX1, bombY1);

    glTexCoord2i(0, 1);
    glVertex2i(bombX1, bombY1 - bombY2);

    glTexCoord2i(1, 1);
    glVertex2i(bombX1 + bombX2, bombY1 - bombY2);

    glTexCoord2i(1, 0);
    glVertex2i(bombX1 + bombX2, bombY1);
    glEnd();
}

void enemy_1()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_enemy_1); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(enemy_1_X_min, enemy_1_Y_max);

    glTexCoord2i(1, 0); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(enemy_1_X_max, enemy_1_Y_max);

    glTexCoord2i(1, 1); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(enemy_1_X_max, enemy_1_Y_min);

    glTexCoord2i(0, 1); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(enemy_1_X_min, enemy_1_Y_min);

    glEnd();
}

void ship(float shipX1, float shipY1)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureShip);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    glTexCoord2i(0, 0);
    glVertex2i(shipX1, shipY1);

    glTexCoord2i(1, 0);
    glVertex2i(shipX1 + shipX2, shipY1);

    glTexCoord2i(1, 1);
    glVertex2i(shipX1 + shipX2, shipY1 - shipY2);

    glTexCoord2i(0, 1);
    glVertex2i(shipX1, shipY1 - shipY2);

    glEnd();
}

void game_Over()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_gameover);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    glTexCoord2i(0, 0);
    glVertex2i(gameoverX1, gameoverY1);

    glTexCoord2i(0, 1);
    glVertex2i(gameoverX1, gameoverY2);

    glTexCoord2i(1, 1);
    glVertex2i(gameoverX2, gameoverY2);

    glTexCoord2i(1, 0);
    glVertex2i(gameoverX2, gameoverY1);
    glEnd();
}

void you_score()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_your_score);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    glTexCoord2i(0, 0);
    glVertex2i(yourScoreX1, yourScoreY1);

    glTexCoord2i(0, 1);
    glVertex2i(yourScoreX1, yourScoreY2);

    glTexCoord2i(1, 1);
    glVertex2i(yourScoreX2, yourScoreY2);

    glTexCoord2i(1, 0);
    glVertex2i(yourScoreX2, yourScoreY1);
    glEnd();
}

/* --------- END : TEXTURE FUNCTIONS --------- */


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (start == false)
    {
        background();
    }
    else
    {
        game_background();
        // plane();
        spaceship();
        enemy_1();

        glPushMatrix();
        glTranslatef(0, 10, 0);
        enemy_1();
        glPopMatrix();

        // while(enemy_count < 5)
        // {
        //     enemy_1();

        //     while(enemy_1_Y_min < 600)
        //     {
        //         enemy_1_Y_min += 1.5;
        //         enemy_1_Y_max += 1.5;
        //     }
        //     enemy_1();
        //     enemy_count++;
        // }

        for (int i = 0; i < length; i++)
        {
            fighterPlaneY[i] += 0.09;                 //How Fast it will increase in the Y-Axis
            bomb(fighterPlaneX[i], fighterPlaneY[i]); //For Drawing the Texture
        }

        /*---------START :  DROPPING MULTIPLE BOMB --------- */

        /*--------- START : APPEARING  MULTIPLE SHIP --------- */

        /*--------- FIRST SHIP APPEARING --------- */

        for (int i = 0; i < no_of_ships; i++)
        {
            shipX1[i] -= 0.05; //How Fast the ship decrease in the X-axis
            ship(shipX1[i], shipY1[i]);
        }

        /*--------- NEW SHIPS APPEARING AFTER A TIME PERIOD  --------- */

        if (delay_time > 5000)
        {
            shipX1[no_of_ships] = 1200;
            shipY1[no_of_ships] = 900;
            no_of_ships++;
            delay_time = 0;
        }

        delay_time++;

        /*--------- END : APPEARING  MULTIPLE SHIP  --------- */

        /*--------- START : COLLISION DETECTION BETWEEN THE BOMB AND THE SHIP  --------- */

        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < no_of_ships; j++)
            {
                if (fighterPlaneX[i] >= shipX1[j] && fighterPlaneX[i] <= shipX1[j] + shipX2 && fighterPlaneY[i] <= shipY1[j] - shipY2 && fighterPlaneY[i] >= shipY1[j] - shipY2 - 20)
                {
                    destroy += 10;
                    length--;

                    for (int k = i; k < length; k++)
                    {
                        fighterPlaneY[k] = fighterPlaneY[k + 1];
                        fighterPlaneX[k] = fighterPlaneX[k + 1];
                    }

                    for (int k = j; k < no_of_ships; k++)
                    {
                        shipY1[k] = shipY1[k + 1];
                        shipX1[k] = shipX1[k + 1];
                    }
                    break;
                }
            }
        }

        /*--------- END : COLLISION DETECTION BETWEEN THE BOMB AND THE SHIP  --------- */

        /*--------- START : COLLISION DETECTION BETWEEN THE BOMB AND THE RIVER  --------- */

        for (int i = 0; i < length; i++)
        {
            if (fighterPlaneY[i] >= river1Y2 || fighterPlaneY[i] >= river2Y2)
            {
                collisionCount++;
                length--;

                for (int k = i; k < length; k++)
                {
                    fighterPlaneY[k] = fighterPlaneY[k + 1];
                    fighterPlaneX[k] = fighterPlaneX[k + 1];
                }

                if (collisionCount > 5)
                {
                    gameover = true;
                }
            }
        }

        /*--------- END : COLLISION DETECTION BETWEEN THE BOMB AND THE RIVER  --------- */

        /*--------- START : CUSTOM FUNCTIONS --------- */

        drawHealthBarRight();
        char score[4];
        char scr[] = {"Score:   "};
        sprintf(score, "%d", destroy);

        drawBitmapText(score, 1150, 110, 0);
        drawBitmapText(scr, 1070, 110, 0);

        /*--------- END : CUSTOM FUNCTIONS --------- */
    }

    if (start == true && pause == true)
    {
        game_background();
        pause_game();
    }

    /*--------- START : GAME OVER  --------- */

    if (gameover == true)
    {
        /*--------- START : TEXTURES --------- */

        game_background();
        game_Over();
        you_score();

        /*--------- END : TEXTURES --------- */

        /*--------- START : CUSTOM FUNCTIONS --------- */

        char score[4];
        char scr[] = {""};
        sprintf(score, "%d", destroy);

        drawBitmapText2(score, 625, 585, 0);
        drawBitmapText2(scr, 625, 585, 0);

        /*--------- END : CUSTOM FUNCTIONS --------- */
    }

    /*--------- END : GAME OVER  --------- */

    glutSwapBuffers();
    glFlush();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){

        if (key == 13)
        {
            start = true;
            pause = false;
            glutPostRedisplay();
        }

        else if (key == 27)
        {
            exit(0);
            glutPostRedisplay();
        }

        else if (key == 'P' || key == 'p')
        {
            pause = true;
            glutPostRedisplay();
        }

}

void SpecialKeys(int key, int x, int y) {

        switch (key) {

            case GLUT_KEY_LEFT:

                if (planeX1 - 20 <= -20)
                {
                    break;
                }

                else
                {
                    planeX1 -= 20.0f;
                }

            break;

            case GLUT_KEY_RIGHT:

                if (planeX1+ planeX2 + 20 >= 1210)
                {
                    break;
                }

                else
                {
                    planeX1 += 20.0f;

                    // glPushMatrix(); //Save the current state of transformations
                    // glTranslatef(20.0, 0.0, 0.0); //Move to the center of the triangle
                    // //glRotatef(_anglee, 0.0,0.0, -1.0); //Rotate about the the vector (1, 2, 3)
                    // plane
                    // // Sun
                    // glColor3f(1.0,1.0,0.0);//(R,G,B)
                    // glutWireSphere(0.60, 20, 20);

                    // glPopMatrix();
                }

            break;

            case GLUT_KEY_DOWN:

                bombX1 = planeX1 + 60;
                bombY1 = 280;
                fighterPlaneX[length] = bombX1;
                fighterPlaneY[length] = bombY1;
                length += 1;

		break;

	}

	glutPostRedisplay();

}
//Called when the window is resized
void handleResize(int w, int h)
{
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

    //Set the camera perspective
    glLoadIdentity();                     //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

int main(int argc, char** argv) {

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

        glutInitWindowSize(900, 650);
        glutInitWindowPosition(250, 50);
        glutCreateWindow("Space Invaders");

        myInit();
        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(SpecialKeys);
        // glutReshapeFunc(handleResize);

        // PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/music/Yellow Magic Orchestra - Theme From The Space Invaders   Firecracker.wav"), NULL, SND_LOOP | SND_ASYNC);
        // PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/music/Space Invaders - Space Invaders.wav"), NULL, SND_LOOP | SND_ASYNC);

        glutMainLoop(); // Start the main loop.  glutMainLoop doesn't return.

        return 0;
}
