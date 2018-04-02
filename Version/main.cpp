#include<windows.h>
#include <mmsystem.h>
#include<stdio.h>
#include<GL/glut.h>
#include "imageloader.h"
/*
Here imageloader.h
https://github.com/badgeek/OpenGL-tutorial/tree/master/GLvbo
*/

static int riverFlag = 0;

bool start = false;
bool gameOver = false;
bool pause = false;

float backX1=0 , backX2 =1200, backY1=0, backY2 =1000;

float cloud1X1 = 400 , cloud1X2 = 1200 , cloud1Y1 =100 , cloud1Y2 = -100 ;
float cloud2X1 = -500 , cloud2X2 = 200 , cloud2Y1 = 200 , cloud2Y2 = -200 ;

float logoX1 =300 , logoX2 =900 , logoY1 =500 , logoY2 =150 ;
float tutorialX1 =250, tutorialX2=1000, tutorialY1 =800 , tutorialY2 =500;

float river1X1 = 0 , river1X2 =1200 , river1Y1 = 1450 ,river1Y2 = 850 ;
float river2X1 = -1200 , river2X2 =-0 , river2Y1 = 1450 ,river2Y2 = 850 ;

float gameOverX1 = 300, gameOverX2 =900, gameOverY1 =550 , gameOverY2 =350 ;
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
GLuint loadTexture(imageloader* image) {

        GLuint textureId;
        glGenTextures(1, &textureId);            // Make room for out texture
        glBindTexture(GL_TEXTURE_2D, textureId); // Tell OpenGL which texture to edit
        // Map the image to the texture
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGB,
            image->width, image->height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            image->pixels);
        return textureId;

}

GLuint _textureBackground;
GLuint _textureCloud1;
GLuint _textureCloud2;
GLuint _textureRiver1;
GLuint _textureRiver2;
GLuint _textureLogo;
GLuint _textureTutorial;
GLuint _texturePlane;
GLuint _textureBomb;
GLuint _textureShip;
GLuint _textureGameOver;
GLuint _textureYourScore;
GLuint _texturePause;

void myInit(void) {

        glClearColor(1.0, 1.0, 1.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 1200, 1000, 0.0);

        imageloader* background = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Background.bmp");
        imageloader* cloud1 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Cloud1.bmp");
        imageloader* cloud2 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Cloud2.bmp");
        imageloader* river1 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/River1.bmp");
        imageloader* river2 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/River2.bmp");
        imageloader* logo = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Logo.bmp");
        imageloader* tutorial = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Tutorial.bmp");
        imageloader* plane = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Plane.bmp");
        imageloader* bomb = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Atomic Bomb.bmp");
        imageloader* ship = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Ship.bmp");
        imageloader* gameOver = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Game Over.bmp");
        imageloader* yourScore = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Your Score.bmp");
        imageloader* pause = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/image/Paused.bmp");


        _textureBackground = loadTexture(background);
        _textureCloud1 = loadTexture(cloud1);
        _textureCloud2 = loadTexture(cloud2);
        _textureRiver1 = loadTexture(river1);
        _textureRiver2 = loadTexture(river2);
        _textureLogo = loadTexture(logo);
        _textureTutorial = loadTexture(tutorial);
        _texturePlane = loadTexture(plane);
        _textureBomb = loadTexture(bomb);
        _textureShip = loadTexture(ship);
        _textureGameOver = loadTexture(gameOver);
        _textureYourScore = loadTexture(yourScore);
        _texturePause = loadTexture(pause);

        delete background;
        delete cloud1;
        delete cloud2;
        delete river1;
        delete river2;
        delete logo;
        delete tutorial;
        delete plane;
        delete bomb;
        delete ship;
        delete gameOver;
        delete yourScore;
        delete pause;

}


/* --------- START : CUSTOM FUNTIONS --------- */

void riverMove(){

            if(riverFlag == 0)
            {
                river1Y1 -= 0.01;
                river1X1 += 0.01;
                river1Y2 -= 0.01;
                river1X2 += 0.01;

                river2Y1 -= 0.01;
                river2X1 += 0.01;
                river2Y2 -= 0.01;
                river2X2 += 0.01;


                if(river1Y1 <= 1430 && river1Y2 <= 830)
                {
                       riverFlag = 1;
                }

                if(river1X1 > 1200 && river1X2 > 1200)
                {
                      river1X1 = -1190;
                      river1X2 = 0;
                }

                if(river2X1 > 1200 && river2X2 > 1200)
                {
                       river2X1 = -1190;
                       river2X2 = 0;
                }
            }

            else if(riverFlag == 1)
            {
                river1Y1 += 0.01;
                river1X1 += 0.01;
                river1Y2 += 0.01;
                river1X2 += 0.01;

                river2Y1 += 0.01;
                river2X1 += 0.01;
                river2Y2 += 0.01;
                river2X2 += 0.01;


                if(river1Y1 > 1450 && river1Y2 >= 850)
                {
                       riverFlag = 0;
                }

                if(river1X1 >= 1200 && river1X2 > 1200)
                {
                       river1X1 = -1190;
                       river1X2 = 0;
                }

                if(river2X1 > 1200 && river2X2 > 1200)
                {
                       river2X1 = -1200;
                       river2X2 = 0;
                }
            }
}

void cloudMove(){

        cloud1X1 += 0.03;
        cloud1X2 +=0.03;

        cloud2X1 += 0.03;
        cloud2X2 +=0.03;

        if(cloud1X1 >= 1200 && cloud1X2 >=1200 ){
            cloud1X1 = -800;
            cloud1X2 = 0;
        }

        if(cloud2X1 >= 1200 && cloud2X2 >=1200 ){
            cloud2X1 = -800;
            cloud2X2 = 0;
        }
}

void drawHealthBarRight(){

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

void background(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureBackground);   // This will let OpenGl know which texture we want to use

        // When the texture is far away to the camera
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
        // When the texture is close to the camera
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0); // picking up the lower left coordinates of the image, X(min) Y(min)
        glVertex2i(backX1, backY1);

        glTexCoord2i(0, 1); // picking up the upper right coordinates of the image, X(min) Y(max)
        glVertex2i(backX1, backY2);

        glTexCoord2i(1, 1); // picking up the upper right coordinates of the image, X(max) Y(max)
        glVertex2i(backX2, backY2);

        glTexCoord2i(1, 0); // picking up the lower left coordinates of the image, X(max) Y(min)
        glVertex2i(backX2, backY1);
        glEnd();

}

void cloud1(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureCloud1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(cloud1X1, cloud1Y1);

        glTexCoord2i(0, 1);
        glVertex2i(cloud1X1, cloud1Y2);

        glTexCoord2i(1, 1);
        glVertex2i(cloud1X2, cloud1Y2);

        glTexCoord2i(1, 0);
        glVertex2i(cloud1X2, cloud1Y1);
        glEnd();

}

void cloud2(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureCloud2);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(cloud2X1, cloud2Y1);

        glTexCoord2i(0, 1);
        glVertex2i(cloud2X1, cloud2Y2);

        glTexCoord2i(1, 1);
        glVertex2i(cloud2X2, cloud2Y2);

        glTexCoord2i(1, 0);
        glVertex2i(cloud2X2, cloud2Y1);
        glEnd();

}

void logo(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureLogo);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(logoX1, logoY1);

        glTexCoord2i(0, 1);
        glVertex2i(logoX1, logoY2);

        glTexCoord2i(1, 1);
        glVertex2i(logoX2, logoY2);

        glTexCoord2i(1, 0);
        glVertex2i(logoX2, logoY1);
        glEnd();

}

void tutorial(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureTutorial);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(tutorialX1, tutorialY1);

        glTexCoord2i(0, 1);
        glVertex2i(tutorialX1, tutorialY2);

        glTexCoord2i(1, 1);
        glVertex2i(tutorialX2, tutorialY2);

        glTexCoord2i(1, 0);
        glVertex2i(tutorialX2, tutorialY1);
        glEnd();

}

void river1(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureRiver1);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(river1X1, river1Y1);

        glTexCoord2i(0, 1);
        glVertex2i(river1X1, river1Y2);

        glTexCoord2i(1, 1);
        glVertex2i(river1X2, river1Y2);

        glTexCoord2i(1, 0);
        glVertex2i(river1X2, river1Y1);
        glEnd();

}

void river2(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureRiver2);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(river2X1, river2Y1);

        glTexCoord2i(0, 1);
        glVertex2i(river2X1, river2Y2);

        glTexCoord2i(1, 1);
        glVertex2i(river2X2, river2Y2);

        glTexCoord2i(1, 0);
        glVertex2i(river2X2, river2Y1);
        glEnd();

}

void plane(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _texturePlane);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(planeX1, planeY1 + planeY2 );

        glTexCoord2i(0, 1);
        glVertex2i(planeX1, planeY2);

        glTexCoord2i(1, 1);
        glVertex2i(planeX1 + planeX2, planeY2);

        glTexCoord2i(1, 0);
        glVertex2i(planeX1 + planeX2, planeY1 + planeY2);
        glEnd();

}

void pause_game(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _texturePause);

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

void bomb(float bombX1, float bombY1){

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

void ship(float shipX1, float shipY1){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureShip);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(shipX1, shipY1);

        glTexCoord2i(0, 1);
        glVertex2i(shipX1, shipY1 - shipY2);

        glTexCoord2i(1, 1);
        glVertex2i(shipX1 + shipX2, shipY1 - shipY2);

        glTexCoord2i(1, 0);
        glVertex2i(shipX1 + shipX2, shipY1);
        glEnd();

}

void game_Over(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureGameOver);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(gameOverX1, gameOverY1);

        glTexCoord2i(0, 1);
        glVertex2i(gameOverX1, gameOverY2);

        glTexCoord2i(1, 1);
        glVertex2i(gameOverX2, gameOverY2);

        glTexCoord2i(1, 0);
        glVertex2i(gameOverX2, gameOverY1);
        glEnd();

}

void you_score(){

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureYourScore);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glColor3f(1.0, 1.0, 1.0);

        glBegin(GL_QUADS);

        glTexCoord2i(0, 0);
        glVertex2i(yourScoreX1,yourScoreY1);

        glTexCoord2i(0, 1);
        glVertex2i(yourScoreX1, yourScoreY2);

        glTexCoord2i(1, 1);
        glVertex2i(yourScoreX2, yourScoreY2);

        glTexCoord2i(1, 0);
        glVertex2i(yourScoreX2, yourScoreY1);
        glEnd();

}

/* --------- END : TEXTURE FUNCTIONS --------- */


void display(void) {

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        if(start == false)
        {
                /*--------- START : TEXTURES --------- */

                background();
                cloud1();
                cloud2();
                logo();
                river1();
                river2();
                tutorial();

                /*--------- END : TEXTURES --------- */


                /*--------- START : CUSTOM FUNCTIONS --------- */

                riverMove();
                cloudMove();

                /*--------- END : CUSTOM FUNCTIONS --------- */
        }

        else
        {
                 /*--------- START : TEXTURES --------- */

                background();
                cloud1();
                cloud2();
                river1();
                river2();
                plane();

                /*--------- END : TEXTURES --------- */

                for (int i = 0; i < length; i++)
                {
                        fighterPlaneY[i] += 0.09;  //How Fast it will increase in the Y-Axis
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

                for(int i = 0; i < length; i++)
                {
                    for (int j = 0; j < no_of_ships; j++)
                    {
                        if (fighterPlaneX[i] >= shipX1[j] && fighterPlaneX[i] <= shipX1[j] + shipX2 && fighterPlaneY[i] <= shipY1[j] - shipY2 && fighterPlaneY[i] >= shipY1[j] - shipY2  - 20)
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

                for(int i = 0; i < length; i++)
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

                        if(collisionCount > 5)
                        {
                            gameOver = true;
                        }
                    }
                }

                /*--------- END : COLLISION DETECTION BETWEEN THE BOMB AND THE RIVER  --------- */

                 /*--------- START : CUSTOM FUNCTIONS --------- */

                riverMove();
                cloudMove();

                drawHealthBarRight();
                char score[4];
                char scr[] = { "Score:   " };
                sprintf(score, "%d", destroy);

                drawBitmapText(score, 1150, 110, 0);
                drawBitmapText(scr, 1070, 110, 0);

                 /*--------- END : CUSTOM FUNCTIONS --------- */
        }


        if(start == true && pause == true)
        {
             background();
             pause_game();
        }


        /*--------- START : GAME OVER  --------- */

        if(gameOver == true)
        {
                /*--------- START : TEXTURES --------- */

                background();
                game_Over();
                you_score();

                /*--------- END : TEXTURES --------- */

                /*--------- START : CUSTOM FUNCTIONS --------- */

                char score[4];
                char scr[] = { "" };
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

        else if (key == 'E' || key == 'e')
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

int main(int argc, char** argv) {

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

        glutInitWindowSize(900, 650);
        glutInitWindowPosition(250, 50);
        glutCreateWindow("Space Invaders");

        glutDisplayFunc(display);
        myInit();
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(SpecialKeys);

        PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/music/Title.wav"), NULL, SND_LOOP | SND_ASYNC);

        glutMainLoop();

        return 0;
}

