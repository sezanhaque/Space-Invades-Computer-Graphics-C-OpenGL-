#include <windows.h>
#include <mmsystem.h> // To play ".wav" sound and it must come after "<windows.h>"
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "imageloader.h"
#include "StdAfx.h"
#include <sstream>
using namespace std;
/*
Here imageloader.h
https://github.com/badgeek/OpenGL-tutorial/tree/master/GLvbo
http://www.videotutorialsrock.com/index.php
*/
// For Text Font
//www.codersource.net/2011/01/27/displaying-text-opengl-tutorial-5/

// coordinates for backgorund image
float backgorund_X_min = 0, backgorund_Y_min = 0, backgorund_X_max = 1200, backgorund_Y_max = 1000;

// coordinates for spaceship image
float spaceship_X_min = 500, spaceship_Y_min = 800, spaceship_X_max = 150, spaceship_Y_max = 200;

// Coordinates for Enemy UFO_1
float enemy_1_X_min = 200, enemy_1_Y_min = 0, enemy_1_X_max = 328, enemy_1_Y_max = 128;

float UFO_1_X_pos[1000] = {200};
float UFO_1_Y_pos[1000] = {0};
float UFO_1_X2_pos = 128;
float UFO_1_Y2_pos = 128;

int delay_time = 0;

// Coordinates for Enemy UFO_2
float enemy_2_X_min = 800, enemy_2_Y_min = 0, enemy_2_X_max = 928, enemy_2_Y_max = 128;

int enemy_count = 1;
// Coordinates for Bullet
float bullet_X_min = 550, bullet_Y_min = 950, bullet_X_max = 600, bullet_Y_max = 1000;

// To store the position of spaceship
float bullet_X = 550;
float bullet_Y = 950;

// Player will able to fire 1000 bullets
float bullet_X_arr[1000] = {0};
float bullet_Y_arr[1000] = {0};
// Bullet 2
float bullet_2_X_arr[1000] = {0};
float bullet_2_Y_arr[1000] = {0};

bool start = false;
bool pause = false;

bool is_fullscreen;

bool fire = false;
int fire_count = 0;
int clash_count = 0;
int spaceship_clash = 0;

bool is_instruction = false;
bool gameover = false;

char point[4];
char point_char[] = {"Point:   "};

// Make the image into a texture, and return the id of the texture
// Takes the image object and makes it into an OpenGL Texture
GLuint loadTexture(imageloader *image)
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
GLuint texture_instruction;
GLuint texture_game_background;
GLuint texture_pause;
GLuint texture_spaceship;
GLuint texture_enemy_1;
GLuint texture_enemy_2;
GLuint texture_bullet;
GLuint texture_lifebar;
GLuint texture_gameover;

void myInit(void)
{
    //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); //Switch to the drawing perspective
    glLoadIdentity();            //Reset the drawing perspective

    glClearColor(0.0, 1.0, 1.0, 0.0);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    gluOrtho2D(0.0, 1200, 1000, 0.0);

    // Loading BMP image file into an "imageloader" object
    imageloader *background = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/mainmenu.bmp");
    imageloader *game_background = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/game.bmp");
    imageloader *instruction = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/Instruction.bmp");
    imageloader *pause = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/pause.bmp");
    imageloader *spaceship = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/spaceship_5.bmp");
    imageloader *enemy_1 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/UFO_1.bmp");
    imageloader *enemy_2 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/UFO_2.bmp");
    imageloader *bullet = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/Bullet.bmp");
    imageloader *lifebar = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/life_bar_2.bmp");
    imageloader *gameover = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/gameover.bmp");

    // "loadTexture" takes the image object and makes it into an OpenGL Texture
    texture_background = loadTexture(background);
    texture_game_background = loadTexture(game_background);
    texture_instruction = loadTexture(instruction);
    texture_pause = loadTexture(pause);
    texture_spaceship = loadTexture(spaceship);
    texture_enemy_1 = loadTexture(enemy_1);
    texture_enemy_2 = loadTexture(enemy_2);
    texture_bullet = loadTexture(bullet);
    texture_lifebar = loadTexture(lifebar);
    texture_gameover = loadTexture(gameover);

    // We are deleting the Image object because OpenGL made a copy of the pixels array
    delete background;
    delete game_background;
    delete instruction;
    delete pause;
    delete spaceship;
    delete enemy_1;
    delete enemy_2;
    delete bullet;
    delete lifebar;
    delete gameover;

    glutSwapBuffers(); //Send the 3D scene to the screen
}
void drawBitmapText(char *string, float x, float y, float z)
{
    char *c;
    glRasterPos3f(x, y, z);

    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawStrokeText(char *string, int x, int y, int z)
{
    char *c;
    glPushMatrix();
    glTranslatef(x, y + 8, z);
    // glScalef(0.09f,-0.08f,z);

    for (c = string; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

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
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(backgorund_X_min, backgorund_Y_max);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(backgorund_X_max, backgorund_Y_max);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(backgorund_X_max, backgorund_Y_min);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(backgorund_X_min, backgorund_Y_min);

    glEnd();
}

void instruction()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_instruction); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(backgorund_X_min, backgorund_Y_max);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(backgorund_X_max, backgorund_Y_max);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(backgorund_X_max, backgorund_Y_min);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(backgorund_X_min, backgorund_Y_min);

    glEnd();
}

void game_over()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_gameover); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(backgorund_X_min, backgorund_Y_max);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(backgorund_X_max, backgorund_Y_max);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(backgorund_X_max, backgorund_Y_min);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(backgorund_X_min, backgorund_Y_min);

    glEnd();
}

void pause_it()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_pause); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(backgorund_X_min, backgorund_Y_max);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(backgorund_X_max, backgorund_Y_max);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(backgorund_X_max, backgorund_Y_min);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
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
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(backgorund_X_min, backgorund_Y_max);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(backgorund_X_max, backgorund_Y_max);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(backgorund_X_max, backgorund_Y_min);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
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
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(spaceship_X_min, spaceship_Y_min + spaceship_Y_max);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(spaceship_X_min + spaceship_X_max, spaceship_Y_min + spaceship_Y_max);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(spaceship_X_min + spaceship_X_max, spaceship_Y_min);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(spaceship_X_min, spaceship_Y_min);

    glEnd();
}

void life_bar_fn(float UFO_1_X_pos, float UFO_1_Y_pos)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_lifebar); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(UFO_1_X_pos, UFO_1_Y_pos + 20);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(1170, UFO_1_Y_pos + 20);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(1170, UFO_1_Y_pos);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(UFO_1_X_pos, UFO_1_Y_pos);

    glEnd();
}

void enemy_1(float UFO_1_X_pos, float UFO_1_Y_pos)
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
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(UFO_1_X_pos, UFO_1_Y_pos + 128);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(UFO_1_X_pos + 128, UFO_1_Y_pos + 128);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(UFO_1_X_pos + 128, UFO_1_Y_pos);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(UFO_1_X_pos, UFO_1_Y_pos);

    glEnd();
}

void enemy_2()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_enemy_2); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(enemy_2_X_min, enemy_2_Y_max);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(enemy_2_X_max, enemy_2_Y_max);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(enemy_2_X_max, enemy_2_Y_min);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(enemy_2_X_min, enemy_2_Y_min);

    glEnd();
}

void bullet(float bullet_X_min, float bullet_Y_min)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_bullet); // This will let OpenGl know which texture we want to use

    // When the texture is far away to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
    // When the texture is close to the camera
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

    // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
    glTexCoord2i(0, 0); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(bullet_X_min, bullet_Y_min + 40);

    glTexCoord2i(1, 0); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(bullet_X_min + 25, bullet_Y_min + 40);

    glTexCoord2i(1, 1); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(bullet_X_min + 25, bullet_Y_min);

    glTexCoord2i(0, 1); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(bullet_X_min, bullet_Y_min);

    glEnd();
}
// bool collision_fun(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
// {
//     if (y1 + h1 < y2)
//     {
//         false;
//     }
//     if (y1 > y2 + h2)
//     {
//         false;
//     }
//     if (x1 + w1 < x2)
//     {
//         false;
//     }
//     if (x1 > x2 + w2)
//     {
//         false;
//     }

//     return true;
// }
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (start == false && gameover == false)
    {
        if (is_instruction == true)
        {
            instruction();
        }
        else
        {
            background();
        }
    }
    else if (start == true && gameover == false)
    {
        gameover = false;
        if (is_instruction == true)
        {
            instruction();
        }
        else
        {
            if (!pause)
            {
                game_background();
                spaceship();

                for (int i = 0; i < enemy_count; i++)
                {
                    // Increasing Y co. of UFO
                    UFO_1_Y_pos[i] += 0.2;
                    // Then creating new Enemy with new indexed of new coordinates
                    enemy_1(UFO_1_X_pos[i], UFO_1_Y_pos[i]);
                }

                // Delaying 2 sec for next enemy
                if (delay_time > 2000)
                {
                    // DEfinig the new coordinates a new enemy in new index of UFO array with initial coordinates
                    UFO_1_X_pos[enemy_count] = 200;
                    UFO_1_Y_pos[enemy_count] = 0;
                    enemy_count++;
                    delay_time = 0;
                }
                // cout << enemy_count << endl;
                delay_time++;

                // Bullet fire
                for (int i = 0; i < fire_count; i++)
                {
                    bullet_Y_arr[i] -= 0.3;
                    bullet_2_Y_arr[i] -= 0.3;

                    bullet(bullet_X_arr[i], bullet_Y_arr[i]);
                    bullet(bullet_2_X_arr[i], bullet_2_Y_arr[i]);
                }

                // Collision between bullet and UFO
                for (int i = 0; i < fire_count; i++)
                {
                    for (int j = 0; j < enemy_count; j++)
                    {
                        // If "UFO_X_min <= bullet_X_min <= UFO_X_max   and     UFO_Y_max <= bullet_Y_max <= UFO_Y_min"
                        // if (bullet_X_arr[i] >= UFO_1_X_pos[j] - 20 && bullet_X_arr[i] <= UFO_1_X_pos[i] + UFO_1_X2_pos + 10 && bullet_Y_arr[i] <= UFO_1_Y_pos[j] && bullet_Y_arr[i] >= UFO_1_Y_pos[j] - 1)
                        // if ((bullet_X_arr[i] >= UFO_1_X_pos[j] - 20 && bullet_X_arr[i] <= UFO_1_X_pos[j] + UFO_1_X2_pos + 10 && bullet_Y_arr[i] <= UFO_1_Y_pos[j] && bullet_Y_arr[i] >= UFO_1_Y_pos[j] - 1) || (bullet_2_X_arr[i] >= UFO_1_X_pos[j] - 20 && bullet_2_X_arr[i] <= UFO_1_X_pos[j] + UFO_1_X2_pos + 10 && bullet_2_Y_arr[i] <= UFO_1_Y_pos[j] && bullet_2_Y_arr[i] >= UFO_1_Y_pos[j] - 1))
                        // {
                        //     clash_count++;
                        //     fire_count--;
                        //     enemy_count--;
                        //     cout << clash_count << endl;

                        //     // To vanish blusted UFO, we are replacing the current UFO to next UFO
                        //     for (int b = j; b < enemy_count; b++)
                        //     {
                        //         // cout << "UFO_1_Y_pos[b]: " << UFO_1_Y_pos[b] << endl;
                        //         // cout << "UFO_1_Y_pos[b + 1]: " << UFO_1_Y_pos[b + 1] << endl;
                        //         UFO_1_X_pos[b] = UFO_1_X_pos[b + 1];
                        //         UFO_1_Y_pos[b] = UFO_1_Y_pos[b + 1];
                        //     }
                        //     // Explosion Sound
                        //     PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/sound/Explosion3.wav"), NULL, SND_ASYNC);
                        // }

                        // if (collision_fun(UFO_1_X_pos[j], UFO_1_Y_pos[j], 128, 128, bullet_X_arr [i], bullet_Y_arr[i], 25, 40))
                        // {
                        //     clash_count++;
                        //     fire_count--;
                        //     enemy_count--;
                        //     cout << clash_count << endl;
                        // }

                        // Perfect collision
                        // If U_X_min < B_X_min < U_X_max      and     U_Y_min < B_Y_max < U_Y_max
                        if ((UFO_1_X_pos[j] - 10 < bullet_X_arr[i] && bullet_X_arr[i] < UFO_1_X_pos[j] + 128 && UFO_1_Y_pos[j] < bullet_Y_arr[i] + 25 && bullet_Y_arr[i] + 25 < UFO_1_Y_pos[j] + 128) || (UFO_1_X_pos[j] - 10 < bullet_2_X_arr[i] && bullet_2_X_arr[i] < UFO_1_X_pos[j] + 128 && UFO_1_Y_pos[j] < bullet_2_Y_arr[i] + 25 && bullet_2_Y_arr[i] + 25 < UFO_1_Y_pos[j] + 128))
                        {
                            clash_count++;
                            fire_count--;
                            enemy_count--;
                            cout << clash_count << endl;
                            PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/sound/Explosion3.wav"), NULL, SND_ASYNC);
                        }
                    }
                }

                // collision between spaceship and UFO
                for (int i = 0; i < enemy_count; i++)
                {
                    // if (spaceship_X_min >= UFO_1_X_pos[i] - 20 && spaceship_X_min <= UFO_1_X_pos[i] + UFO_1_X2_pos + 10 && spaceship_Y_max <= UFO_1_Y_pos[i] && spaceship_Y_max >= UFO_1_Y_pos[i] - 1)
                    // if ((UFO_1_X_pos[i] >= spaceship_X_min && UFO_1_X_pos[i] + 128 <= spaceship_X_min + spaceship_X_max && spaceship_Y_max <= UFO_1_Y_pos[i] && spaceship_Y_max >= UFO_1_Y_pos[i] - 0.2) || (UFO_1_X_pos[i] + UFO_1_X2_pos >= spaceship_X_min && spaceship_Y_max <= UFO_1_Y_pos[i] && spaceship_Y_max >= UFO_1_Y_pos[i] - 0.2))
                    // {
                    //     spaceship_clash++;
                    //     if (spaceship_clash > 0)
                    //     {
                    //         // Explosion Sound
                    //         PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/sound/Explosion3.wav"), NULL, SND_ASYNC);
                    //     }
                    //     cout << "Spaceship Clash: " << spaceship_clash << endl;
                    // }

                    // if ((spaceship_X_min < UFO_1_X_pos[i] && spaceship_Y_min + spaceship_Y_max > UFO_1_Y_pos[i] ) && (UFO_1_X_pos[i] < spaceship_X_min + spaceship_X_max  && UFO_1_Y_pos[i] > spaceship_Y_min + spaceship_Y_max))

                    if ((spaceship_X_min < UFO_1_X_pos[i] && UFO_1_X_pos[i] < spaceship_X_min + spaceship_X_max && spaceship_Y_min + spaceship_Y_max < UFO_1_Y_pos[i] && UFO_1_Y_pos[i] < spaceship_Y_min + spaceship_Y_max + 0.1) || (spaceship_X_min < UFO_1_X_pos[i] + 128 && UFO_1_X_pos[i] + 128 < spaceship_X_min + spaceship_X_max && spaceship_Y_min + spaceship_Y_max < UFO_1_Y_pos[i] && UFO_1_Y_pos[i] < spaceship_Y_min + spaceship_Y_max + 0.1))
                    {
                        spaceship_clash++;
                        // Explosion Sound
                        PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/sound/Explosion3.wav"), NULL, SND_ASYNC);
                        cout << "Spaceship Clash: " << spaceship_clash << endl;
                    }
                }

                // Value for health bar
                if (spaceship_clash == 0)
                {
                    life_bar_fn(980, 30);
                    // cout << "1 crosses " << spaceship_clash << endl;
                }
                else if (spaceship_clash == 1)
                {
                    life_bar_fn(1010, 30);
                    // cout << "1 crosses " << spaceship_clash << endl;
                }
                else if (spaceship_clash == 2)
                {
                    life_bar_fn(1040, 30);
                    // cout << "1 crosses " << spaceship_clash << endl;
                }
                else if (spaceship_clash == 3)
                {
                    life_bar_fn(1070, 30);
                    // cout << "1 crosses " << spaceship_clash << endl;
                }
                else if (spaceship_clash == 4)
                {
                    life_bar_fn(1100, 30);
                    // cout << "1 crosses " << spaceship_clash << endl;
                }
                else if (spaceship_clash == 5)
                {
                    life_bar_fn(1130, 30);
                    // cout << "1 crosses " << spaceship_clash << endl;
                }
                if (spaceship_clash > 6)
                {
                    gameover = true;
                    start = false;
                }

                // Game Point
                glColor3f(0, 1, 0);
                sprintf(point, "%d", clash_count);

                drawBitmapText(point_char, 1000, 90, 0);
                drawBitmapText(point, 1070, 90, 0);
            }
            else
            {
                pause_it();
            }
        }
    }
    else if (gameover == true)
    {
        game_over();
    }

    glutSwapBuffers(); //Send the 3D scene to the screen
    glFlush();
    glutPostRedisplay();
}

// For Full Screen
void toggle_fullscreen()
{
    if (is_fullscreen)
    {
        glutReshapeWindow(900, 650);
        glutPositionWindow(250, 50);
    }
    else
    {
        glutFullScreen();
    }
    // To exit from full screen
    is_fullscreen = !is_fullscreen;
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{                  //The current mouse coordinates
    if (key == 13) // If user press Enter
    {
        start = true;
        pause = false;
        glutPostRedisplay();
    }
    if (key == 27) // If user press Enter
    {
        exit(0); //Exit the program
        glutPostRedisplay();
    }
    if (key == 102 || key == 70) // If user press "f/F"
    {
        toggle_fullscreen();
    }
    if (key == 105 || key == 73) // If user press "I/i"
    {
        if (!is_instruction)
        {
            is_instruction = true;
        }
        else
        {
            is_instruction = false;
        }
    }
    if (key == 112 || key == 80) // If user press "I/i"
    {
        if (!pause)
        {
            pause = true;
        }
        else
        {
            pause = false;
        }
    }
    if (key == 32) // If user press space
    {
        bullet_X_arr[fire_count] = spaceship_X_min + 51;
        bullet_Y_arr[fire_count] = spaceship_Y_min - 40;
        bullet_2_X_arr[fire_count] = spaceship_X_min + 74;
        bullet_2_Y_arr[fire_count] = spaceship_Y_min - 40;
        fire_count++;

        PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/sound/Laser Gun Sound Effect.wav"), NULL, SND_ASYNC);

        glutPostRedisplay();
    }
}

void navigator_Keys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:

        if (spaceship_X_min - 30 <= -20)
        {
            break;
        }
        else
        {
            spaceship_X_min -= 30;
            bullet_X = spaceship_X_min + 50;
        }
        break;

    case GLUT_KEY_RIGHT:

        if (spaceship_X_min + spaceship_X_max + 30 >= 1220)
        {
            break;
        }
        else
        {
            spaceship_X_min += 30;
            bullet_X = spaceship_X_min + 50;
        }
        break;
    }
    glutPostRedisplay();
}

//Called when the window is resized
void handleResize(int w, int h)
{
    // //Tell OpenGL how to convert from coordinates to pixel values
    // glViewport(0, 0, w, h);

    // glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

    // //Set the camera perspective
    // glLoadIdentity();                     //Reset the camera
    // gluPerspective(45.0,                  //The camera angle
    //                (double)w / (double)h, //The width-to-height ratio
    //                1.0,                   //The near z clipping coordinate
    //                200.0);                //The far z clipping coordinate

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // glTranslatef(0.0, 0.0, -3.6);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //glutFullScreen();
    glutInitWindowSize(900, 650);
    glutInitWindowPosition(250, 50);

    //glutGameModeString( "1024x768:32@75" ); //the settings for fullscreen mode
    //glutEnterGameMode(); //set glut to fullscreen using the settings in the line above

    glutCreateWindow("Space Invaders");
    myInit();
    glutDisplayFunc(display);
    // glutReshapeFunc(handleResize);
    glutKeyboardFunc(handleKeypress); // For normal button
    glutSpecialFunc(navigator_Keys);  // For Nav button

    // PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/sound/Yellow Magic Orchestra - Theme From The Space Invaders   Firecracker.wav"), NULL, SND_LOOP | SND_ASYNC);
    // PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/sound/Space Invaders - Space Invaders.wav"), NULL, SND_LOOP | SND_ASYNC);

    glutMainLoop(); // Start the main loop.  glutMainLoop doesn't return.

    return 0;
}
