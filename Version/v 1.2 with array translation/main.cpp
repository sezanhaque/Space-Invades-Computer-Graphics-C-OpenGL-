#include <windows.h>
#include <mmsystem.h> // To play ".wav" sound and it must come after "<windows.h>"
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "imageloader.h"
using namespace std;
/*
Here imageloader.h
https://github.com/badgeek/OpenGL-tutorial/tree/master/GLvbo
http://www.videotutorialsrock.com/index.php
*/

// coordinates for backgorund image
float backgorund_X_min = 0, backgorund_Y_min = 0, backgorund_X_max = 1200, backgorund_Y_max = 1000;

// coordinates for spaceship image
float spaceship_X_min = 500, spaceship_Y_min = 800, spaceship_X_max = 650, spaceship_Y_max = 1000;

// Coordinates for Enemy UFO_1
float enemy_1_X_min = 200, enemy_1_Y_min = 0, enemy_1_X_max = 328, enemy_1_Y_max = 128;

float UFO_1_X_pos[1000] = {200};
float UFO_1_Y_pos[1000] = {0};
float UFO_1_X2_pos = 128;
float UFO_1_Y2_pos = 128;

int delay_time = 0;

// Coordinates for Enemy UFO_2
float enemy_2_X_min = 800,
      enemy_2_Y_min = 0, enemy_2_X_max = 928, enemy_2_Y_max = 128;

int enemy_count = 1;
// Coordinates for Bullet
float bullet_X_min = 550, bullet_Y_min = 950, bullet_X_max = 600, bullet_Y_max = 1000;

bool start = false;
bool pause = false;

int translate_enemy_1_Y_axis = 0.0;
int translate_enemy_1_Y_axis_2 = 0.0;
int translate_enemy_2_Y_axis = 0.0;

bool is_fullscreen;

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
GLuint texture_game_background;
GLuint texture_spaceship;
GLuint texture_enemy_1;
GLuint texture_enemy_2;
GLuint texture_bullet;

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
    imageloader *spaceship = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/spaceship_5.bmp");
    imageloader *enemy_1 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/UFO_1.bmp");
    imageloader *enemy_2 = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/UFO_2.bmp");
    imageloader *bullet = loadBMP("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/assets/Bullet.bmp");

    // "loadTexture" takes the image object and makes it into an OpenGL Texture
    texture_background = loadTexture(background);
    texture_game_background = loadTexture(game_background);
    texture_spaceship = loadTexture(spaceship);
    texture_enemy_1 = loadTexture(enemy_1);
    texture_enemy_2 = loadTexture(enemy_2);
    texture_bullet = loadTexture(bullet);

    // We are deleting the Image object because OpenGL made a copy of the pixels array
    delete background;
    delete game_background;
    delete spaceship;
    delete enemy_1;
    delete enemy_2;
    delete bullet;

    glutSwapBuffers(); //Send the 3D scene to the screen
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
    glTexCoord2i(0, 0); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(UFO_1_X_pos, UFO_1_Y_pos + 128);

    glTexCoord2i(1, 0); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(UFO_1_X_pos + 128, UFO_1_Y_pos + 128);

    glTexCoord2i(1, 1); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(UFO_1_X_pos + 128, UFO_1_Y_pos);

    glTexCoord2i(0, 1); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(UFO_1_X_pos, UFO_1_Y_pos);

    glEnd();
}

// void enemy_1()
// {
//     glEnable(GL_TEXTURE_2D);
//     glBindTexture(GL_TEXTURE_2D, texture_enemy_1); // This will let OpenGl know which texture we want to use

//     // When the texture is far away to the camera
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // "GL_LINEAR" if we want to use blury texture mapping
//     // When the texture is close to the camera
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // "GL_NEAREST" if we want to use block texture mapping
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//     glColor3f(1.0, 1.0, 1.0);

//     glBegin(GL_QUADS);

//     // OpenGL picks the coordinates of an image starting from top left, so (0,0) will be on X(min) Y(max) position
//     glTexCoord2i(0, 0); // picking up the bottom left coordinates of the image, X(min) Y(min)
//     glVertex2i(enemy_1_X_min, enemy_1_Y_max);

//     glTexCoord2i(1, 0); // picking up the bottom right coordinates of the image, X(max) Y(min)
//     glVertex2i(enemy_1_X_max, enemy_1_Y_max);

//     glTexCoord2i(1, 1); // picking up the top right coordinates of the image, X(max) Y(max)
//     glVertex2i(enemy_1_X_max, enemy_1_Y_min);

//     glTexCoord2i(0, 1); // picking up the top left coordinates of the image, X(min) Y(max)
//     glVertex2i(enemy_1_X_min, enemy_1_Y_min);

//     glEnd();
// }

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
    glTexCoord2i(0, 0); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(enemy_2_X_min, enemy_2_Y_max);

    glTexCoord2i(1, 0); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(enemy_2_X_max, enemy_2_Y_max);

    glTexCoord2i(1, 1); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(enemy_2_X_max, enemy_2_Y_min);

    glTexCoord2i(0, 1); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(enemy_2_X_min, enemy_2_Y_min);

    glEnd();
}

void bullet()
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
    glTexCoord2i(0, 0); // picking up the bottom left coordinates of the image, X(min) Y(min)
    glVertex2i(bullet_X_min, bullet_Y_max);

    glTexCoord2i(1, 0); // picking up the bottom right coordinates of the image, X(max) Y(min)
    glVertex2i(bullet_X_max, bullet_Y_max);

    glTexCoord2i(1, 1); // picking up the top right coordinates of the image, X(max) Y(max)
    glVertex2i(bullet_X_max, bullet_Y_min);

    glTexCoord2i(0, 1); // picking up the top left coordinates of the image, X(min) Y(max)
    glVertex2i(bullet_X_min, bullet_Y_min);

    glEnd();
}
// void enemy_1_coming()
// {
//     enemy_1_Y_min += 228;
//     enemy_1_Y_max += 328;

//     if (enemy_1_Y_max > 1000)
//     {
//         enemy_1_Y_min = 128;
//         enemy_1_Y_max = 228;
//     }
//     glPushMatrix();
//     gltranslate_enemy_1_Y_axisf(enemy_1_X_min, enemy_1_Y_min, 0);
//     enemy_1();
//     glPopMatrix();
// }

void update(int value)
{
    // Enemy 1
    translate_enemy_1_Y_axis += 5.1f;
    if (translate_enemy_1_Y_axis > 1050)
    {
        translate_enemy_1_Y_axis = 0.0;
        glutPostRedisplay(); //Tell GLUT that the display has changed
    }

    // Enemy 2
    translate_enemy_2_Y_axis += 3.1f;
    if (translate_enemy_2_Y_axis > 1050)
    {
        translate_enemy_2_Y_axis = 0.0;
        glutPostRedisplay(); //Tell GLUT that the display has changed
    }

    glutPostRedisplay(); //Tell GLUT that the display has changed

    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}

void update_2(int value)
{
    // Enemy 1
    translate_enemy_1_Y_axis_2 += 4.1f;
    if (translate_enemy_1_Y_axis_2 > 1050)
    {
        translate_enemy_1_Y_axis_2 = 0.0;
        glutPostRedisplay(); //Tell GLUT that the display has changed
    }

    glutPostRedisplay(); //Tell GLUT that the display has changed

    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update_2, 0);
}

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
        spaceship();
        // enemy_1(200, 0);

        for (int i = 0; i < enemy_count; i++)
        {
            UFO_1_Y_pos[i] += 0.2;
            enemy_1(UFO_1_X_pos[i], UFO_1_Y_pos[i]);
        }

        if (delay_time > 2000)
        {
            UFO_1_X_pos[enemy_count] = 200;
            UFO_1_Y_pos[enemy_count] = 0;
            enemy_count++;
            delay_time = 0;
        }

        delay_time++;

        // There is one problem! In "else" condition, translation is not working rather than it starting at "if" condition.
        // So i need to apply some other method to translate things. :(

        // Enemy 1.1
        // glPushMatrix();
        // glTranslatef(-150, translate_enemy_1_Y_axis, 0);
        // enemy_1();
        // glPopMatrix();

        // // Enemy 1.2
        // glPushMatrix();
        // glTranslatef(100, translate_enemy_1_Y_axis_2, 0);
        // enemy_1();
        // glPopMatrix();

        // // Enemy 2.1
        // glPushMatrix();
        // glTranslatef(0, translate_enemy_2_Y_axis, 0);
        // enemy_2();
        // glPopMatrix();

        // // Enemy 2.2
        // glPushMatrix();
        // glTranslatef(200, translate_enemy_1_Y_axis_2, 0);
        // enemy_2();
        // glPopMatrix();
        // bullet();

        // ___________End of if/else problem____________

        // cout << enemy_count << endl;
        // while (enemy_count < 5)
        // {
        //     enemy_1();
        //     enemy_count++;
        //     // cout<<enemy_count<<endl;
        // }
        // enemy_1_coming();

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
    }

    glutSwapBuffers(); //Send the 3D scene to the screen
    glFlush();
    glutPostRedisplay();
}
void display_bullet(void)
{
    // glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glTranslatef(-150, translate_enemy_1_Y_axis, 0);
    bullet();
    glPopMatrix();

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
        // pause = false;
        glutPostRedisplay();
    }
    if (key == 27) // If user press Enter
    {
        exit(0); //Exit the program
        glutPostRedisplay();
    }
    if (key == 102 || key == 70) // If user press "f"
    {
        toggle_fullscreen();
    }
    if (key == 32) // If user press space
    {
        // glutDisplayFunc(display_bullet);
        // for(float i = 0.0; i<100.0; i+=5.0)
        // {
        //     bullet_Y_min += i;
        //     bullet_Y_max += i;
        //     cout<<bullet_Y_min<<" "<<bullet_Y_max<<endl;
        // }

        if (bullet_Y_max < 0)
        {
            bullet_Y_min = 950;
            bullet_Y_max = 1000;
        }
        bullet_Y_min -= 20;
        bullet_Y_max -= 20;
        glutSwapBuffers(); //Send the 3D scene to the screen
        glFlush();
        glutPostRedisplay();
    }
}

// void navigator_Keys(int key, int x, int y)
// {

//     switch (key)
//     {
//     case GLUT_KEY_LEFT:

//         if (planeX1 - 20 <= -20)
//         {
//             break;
//         }

//         else
//         {
//             planeX1 -= 20.0f;
//         }

//         break;

//     case GLUT_KEY_RIGHT:

//         if (planeX1 + planeX2 + 20 >= 1210)
//         {
//             break;
//         }

//         else
//         {
//             planeX1 += 20.0f;
//         }

//         break;

//     case GLUT_KEY_DOWN:

//         bombX1 = planeX1 + 60;
//         bombY1 = 280;
//         fighterPlaneX[length] = bombX1;
//         fighterPlaneY[length] = bombY1;
//         length += 1;

//         break;
//     }

//     glutPostRedisplay();
// }
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
    glutKeyboardFunc(handleKeypress); // For normal button
    // glutSpecialFunc(navigator_Keys);    // For Nav button

    glutTimerFunc(25, update, 0);   //Add a timer
    glutTimerFunc(25, update_2, 0); //Add a timer

    //PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/music/Yellow Magic Orchestra - Theme From The Space Invaders   Firecracker.wav"), NULL, SND_LOOP | SND_ASYNC);
    // PlaySound(TEXT("F:/Study/Semester 9/Computer Graphics/Project/Space Invaders/music/Space Invaders - Space Invaders.wav"), NULL, SND_LOOP | SND_ASYNC);

    glutMainLoop(); // Start the main loop.  glutMainLoop doesn't return.

    return 0;
}
