/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */


#include <stdlib.h>
#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "bmploader.h"
#include <iostream>
#include<cstdlib>
#include<string>
using namespace std;

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=1000;
GLfloat alpha = 0.0, theta = 0.0,gama=0.0,shootangle=0.0, axis_x=20, axis_y=50, axis_z=20,zT=-6;
GLboolean lRotate = false,rRotate = false, uRotate = false, dRotate = false;
GLboolean zpRotate=false,znRotate=false,shootleft=false,shootright=false;
GLboolean fronT=false,backT=false,bzshoot=false,bzshootup=false,shoot=false,goal=false;
GLfloat bx=0,by=0,bz=0,gx=0,gy=0,gz=0,save=0;
unsigned int ID[1000];
int randd=0,score=0,counter=0;
double ex=0, ey=0.5, ez=5, lx=0,ly=0,lz=0, hx=0,hy=1,hz=0;

/* GLUT callback Handlers */

GLboolean spotLight = false, ambL0 = false,diffL0 = false, specL0 = false;
GLboolean Light1 = false, ambL1 = false,diffL1 = false, specL1 = false;
GLboolean Light2 = false, ambL2 = false,diffL2 = false, specL2 = false;
GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 }, light_specular[] = { 0.5,0.5,0.5, 1.0 };
GLfloat light_ambient0[]  = { 0.5, 0.5, 0.5, 1.0 }, light_diffuse0[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient1[]  = { 0.5, 0.5, 0.5, 1.0 }, light_diffuse1[]  = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient2[]  = { 0.5, 0.5, 0.5, 1.0 }, light_diffuse2[]  = { 1.0, 1.0, 1.0, 1.0 };


void Material(GLfloat rCol, GLfloat gCol, GLfloat bCol)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { rCol*0.5, gCol*0.5, bCol*0.5, 1.0 };
    GLfloat mat_diffuse[] = { rCol, gCol, bCol, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void LightThree()
{
    glPushMatrix();
    GLfloat light_position[] = {0,10,10};
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}


void LightOne()
{
    glPushMatrix();
    GLfloat light_position[] = {-15,10,-4};
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}
void LightTwo()
{
    glPushMatrix();
    GLfloat light_position[] = {15,10,-4};
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    glPopMatrix();
}


static GLfloat surface[8][3]
{
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 0.0, 1.0},
    {1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0},
};

static GLubyte quadIndices[6][4] =
{
    {1,5,4,0},   //bottom clockwise
    {3,7,6,2},   //top
    {0,4,7,3},   //left clockwise
    {2,6,5,1},   //right
    {4,5,6,7},   //front
    {3,2,1,0},   //back clockwise
};

static void getNormal3p(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1; Uy = y2-y1; Uz = z2-z1;
    Vx = x3-x1; Vy = y3-y1; Vz = z3-z1;
    Nx = Uy*Vz - Uz*Vy; Ny = Uz*Vx - Ux*Vz; Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void mycube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(surface[quadIndices[i][0]][0], surface[quadIndices[i][0]][1], surface[quadIndices[i][0]][2],
                    surface[quadIndices[i][1]][0], surface[quadIndices[i][1]][1], surface[quadIndices[i][1]][2],
                    surface[quadIndices[i][2]][0], surface[quadIndices[i][2]][1], surface[quadIndices[i][2]][2]);

        glVertex3fv(&surface[quadIndices[i][0]][0]); glTexCoord2f(1,1);
        glVertex3fv(&surface[quadIndices[i][1]][0]); glTexCoord2f(1,0);
        glVertex3fv(&surface[quadIndices[i][2]][0]); glTexCoord2f(0,0);
        glVertex3fv(&surface[quadIndices[i][3]][0]); glTexCoord2f(0,1);
    }
    glEnd();
}


void drawfield(){

    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,1);
    //drawfield

         glPushMatrix();

        glTranslatef(-10,-1.2,-9);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(20,0.01,24);
        glBindTexture(GL_TEXTURE_2D,1);

        mycube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);



}


void drawgoalnet(){

    for(float x=0;x<6;x+=0.2){
            for(float y=0;y<2;y+=0.20){


    glPushMatrix();

        glTranslated(x-2.9,0.9-y,-7);
        glScalef(0.3,2,0.3);
        glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
        Material(0.722, 0.845, 0.870);
        glTranslated(x-3,0.9-y,-7);
        glScalef(2,0.3,0.3);
        glutSolidCube(0.2);
    glPopMatrix();
    }}

}

void drawgoalbar(){

    Material(0.274, 0.662, 0.740);

        glPushMatrix();
        glTranslatef(-3.1 ,0,-7);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(1,11,1);
        glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,1,-7);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(30,1,1);
        glutSolidCube(.2);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(3,0,-7);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(1,10,1);
        glutSolidCube(0.2);
    glPopMatrix();


}
void drawgoalnetleft(){

    Material(0.722, 0.845, 0.870);
    //glRotated(90,0,1,0);
    //glTranslated(-3,1,0);
    for(float x=0;x<1;x+=0.2){
            for(float y=0;y<2;y+=0.20){

    glPushMatrix();

        glTranslated(-3,0.9-y,x-7);
        glScalef(0.3,2,0.3);
        glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-3,0.9-y,x-7);
        glScalef(0.3,0.3,2);
        glutSolidCube(0.2);
    glPopMatrix();
    }}



    glPushMatrix();
        glTranslatef(-3,1,-6.5);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(1,1,5);
        glutSolidCube(.2);
    glPopMatrix();

}

void drawgoalnetright(){
    for(float x=0;x<1;x+=0.2){
            for(float y=0;y<2;y+=0.20){

    glPushMatrix();
        glTranslated(3,0.9-y,x-7);
        glScalef(0.3,2,0.3);
        glutSolidCube(0.2);
    glPopMatrix();
    glPushMatrix();
        glTranslated(3,0.9-y,x-7);
        glScalef(0.3,0.3,2);
        glutSolidCube(0.2);
    glPopMatrix();
    }}



    glPushMatrix();
        glTranslatef(3,1,-6.5);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(1,1,5);
        glutSolidCube(.2);
    glPopMatrix();
}


void drawsoccer(){
    glPushMatrix();
    Material(0.558, 0.820, 0.741);
    glTranslatef(0+bx,-1+by,0+bz);


    glutSolidSphere(0.18,10,5);

    glPopMatrix();


}
void drawplayer(){

    Material(0.760, 0.205, 0.205);

    glPushMatrix();
    glTranslatef(5,0,0.5);
    //head
    glPushMatrix();
    glTranslatef(-5.27,0.4,-0.1);

    glutSolidSphere(0.18,10,5);

    glPopMatrix();

    glEnable(GL_TEXTURE_2D);

     //body
         glPushMatrix();
        Material(1, 1,1);
        glTranslatef(-5.5,-0.55,0);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(-0.5,0.8,0.2);
        glBindTexture(GL_TEXTURE_2D,3);
        glRotated(180,0,1,0);

        mycube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    Material(0.760, 0.205, 0.205);
    //legs
     glPushMatrix();

        glTranslatef(-5.4,-0.8,-0.1);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(0.1,0.4,0.05);
        //glBindTexture(GL_TEXTURE_2D,3);
        //glRotated(180,0,1,0);
        glBindTexture(GL_TEXTURE_2D,4);
        glutSolidSphere(1,10,10);
    glPopMatrix();

    glPushMatrix();

    glRotated(shootangle,1,0,0);

    glPushMatrix();

        glTranslatef(-5.15,-0.8,-0.1);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(0.1,0.4,0.05);
        //glBindTexture(GL_TEXTURE_2D,3);
        //glRotated(180,0,1,0);
        glBindTexture(GL_TEXTURE_2D,4);
        glutSolidSphere(1,10,10);
    glPopMatrix();
    Material(0.0276, 0.206, 0.920);

    //shoesright
    glPushMatrix();

        glTranslatef(-5.15,-1.15,-0.15);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(0.05,0.05,0.1);
        //glBindTexture(GL_TEXTURE_2D,3);
        //glRotated(180,0,1,0);
        glBindTexture(GL_TEXTURE_2D,4);
        glutSolidSphere(1,10,10);
    glPopMatrix();
    glPopMatrix();

    //shoesleft
    glPushMatrix();

        glTranslatef(-5.4,-1.15,-0.15);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(0.05,0.05,0.1);
        //glBindTexture(GL_TEXTURE_2D,3);
        //glRotated(180,0,1,0);
        glBindTexture(GL_TEXTURE_2D,4);
        glutSolidSphere(1,10,10);
    glPopMatrix();

    //lefthand
    glPushMatrix();

        glTranslatef(-5.6,-0.1,-0.1);
        glRotated(-30,0,0,1);
        glScalef(0.05,0.4,0.05);
        glutSolidSphere(1,10,10);

        glPopMatrix();


        glPushMatrix();

        glTranslatef(-5.755,-0.4,-0.1);
        glScalef(0.05,0.05,0.05);
        glRotated(180,0,1,0);
        glutSolidSphere(1,10,10);
    glPopMatrix();

    //right hand
    glPushMatrix();

        glTranslatef(-4.9,-0.1,-0.1);

        glRotated(30,0,0,1);
        glScalef(0.05,0.4,0.05);
        glutSolidSphere(1,10,10);

    glPopMatrix();
    glPushMatrix();

        glTranslatef(-4.745,-0.4,-0.1);
        glScalef(0.05,0.05,0.05);

        glRotated(180,0,1,0);
        glutSolidSphere(1,10,10);
    glPopMatrix();


    glPopMatrix();



}

void drawfieldboundary(){
        glPushMatrix();

        glTranslatef(-10,-0.15,-9);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(20,-1,0.1);
        glBindTexture(GL_TEXTURE_2D,2);
        //glRotated(180,,1,0);
        mycube();
    glPopMatrix();

}

void drawgallery(){
    Material(1,1,1);
    glEnable(GL_TEXTURE_2D);

    //drawfieldboundary
    drawfieldboundary();
    glPushMatrix();
    glTranslated(-1,0,-2);
    glRotated(90,0,1,0);
    glScaled(0.7,1,1);
    drawfieldboundary();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-1,0,10);
    glRotated(90,0,1,0);
    glScaled(0.495,1,1);
    drawfieldboundary();
    glPopMatrix();

    glPushMatrix();
    glTranslated(1,0,-2);
    glRotated(-90,0,1,0);
    glScaled(0.7,1,1);
    drawfieldboundary();
    glPopMatrix();
    glPushMatrix();
    glTranslated(1,0,10);
    glRotated(-90,0,1,0);
    glScaled(0.495,1,1);
    drawfieldboundary();
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-0.15,24);
    glScaled(1,1,1);
    drawfieldboundary();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //drawgallery
    glPushMatrix();
     Material(0.374, 0.310, 0.690);


        glTranslatef(-11,-1.2,-15);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(22,1,5);
        glBindTexture(GL_TEXTURE_2D,2);

        mycube();
    glPopMatrix();



}
void drawchair(){


    Material(0.274, 0.662, 0.740);
float y=0.8;
    for(float z=0;z<2;z+=1.2){

        for(float x=0;x<22;x+=1.2){

            glPushMatrix();

            glTranslated(-6.8+x,-0.7,-10+z);
            glScaled(0.8,0.8,0.5);

            glPushMatrix();


            glTranslated(-5,1,-5);
            glScaled(1,0.1,1);
            mycube();
            glPopMatrix();

            glPushMatrix();


            glTranslated(-5,0,-5);
            glScaled(1,2,0.1);
            mycube();
            glPopMatrix();

            glPushMatrix();


            glTranslated(-5,0,-4);
            glScaled(1,1,0.1);
            mycube();
            glPopMatrix();


            glPopMatrix();

        }
        y-=0.8;
    }



}


void drawgoalpost2(){
    glPushMatrix();
    glTranslated(0,0,6);
    glRotated(180,0,1,0);
     glPushMatrix();
        glTranslatef(-3  ,0,-6);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(1,10,1);
        glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,1,-6);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(30,1,1);
        glutSolidCube(.2);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(3,0,-6);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(1,10,1);
        glutSolidCube(0.2);
    glPopMatrix();


    //goalnetback
    drawgoalnet();
    drawgoalbar();
    //drawgoalnetleft
    drawgoalnetleft();
    //drawgoalnetright
    drawgoalnetright();
    glPopMatrix();

}
void drawgoalkeeper(){
    Material(0.809, 0.820, 0.148);
            glPushMatrix();
            glTranslatef(0.5+gx,-1.5+gy,-2+gz);
            glScaled(0.7,0.7,0.7);



             glPushMatrix();
            glTranslatef(-0.5,2.3,-5);
            glScalef(1.4,1.4,1.4);
            glutSolidSphere(0.18,10,5);

            glPopMatrix();



                 glPushMatrix();


                glTranslatef(0,1,-5);
                //glRotated(60,1,0,0);
                //glRotatef(90,0,0,1);
                glScalef(1,1,0.1);

                glRotated(180,0,1,0);

                mycube();
            glPopMatrix();

            //hands
            Material(0.0490, 0.700, 0.266);

             glPushMatrix();

                glTranslatef(0,1.5,-5.1);
                 //glRotatef(90,0,0,1);
                glScalef(0.2,0.6,0.1);
                //glRotated(180,0,0,1);
                mycube();
            glPopMatrix();



            glPushMatrix();

                glTranslatef(-1.2,1.5,-5.1);
                 //glRotatef(90,0,0,1);
                glScalef(0.2,0.6,0.1);
                //glRotated(180,0,0,1);
                mycube();
            glPopMatrix();
            glPopMatrix();

}

void drawwatchers(){

float y=0.8;
     for(float z=0;z<2;z+=1.2){


        for(float x=0;x<22;x+=1.2){



            glPushMatrix();
            glTranslatef(-10+x,-0.7+y,-9.5+z);
            glScaled(0.8,0.8,0.5);



             glPushMatrix();
             Material(0.357, 0.322, 0.370);
            glTranslatef(-0.5,2.3,-5);
            glScalef(1.4,1.4,1.4);
            glutSolidSphere(0.18,10,5);

            glPopMatrix();



                 glPushMatrix();
            Material(0.731, 0.212, 0.920);


                glTranslatef(0,1,-5);
                //glRotated(60,1,0,0);
                //glRotatef(90,0,0,1);
                glScalef(1,1,0.1);

                glRotated(180,0,1,0);

                mycube();
            glPopMatrix();



             glPushMatrix();
             Material(0.920, 0.0573, 0.0276);


                glTranslatef(0,1.5,-5.1);
                 //glRotatef(90,0,0,1);
                glScalef(0.2,0.6,0.1);
                //glRotated(180,0,0,1);
                mycube();
            glPopMatrix();



            glPushMatrix();
                Material(0.920, 0.0573, 0.0276);

                glTranslatef(-1.2,1.5,-5.1);
                 //glRotatef(90,0,0,1);
                glScalef(0.2,0.6,0.1);
                //glRotated(180,0,0,1);
                mycube();
            glPopMatrix();

            glPopMatrix();




        }

        y-=0.8;
        }






}

void drawgallery2(){
    glPushMatrix();
    glRotated(90,0,1,0);
    drawchair();
    drawwatchers();
    glPopMatrix();
    glPushMatrix();
    glRotated(-90,0,1,0);
    drawchair();
    drawwatchers();
    glPopMatrix();
}
void drawbuilding()
{
     Material(1, 1,1);

    glEnable(GL_TEXTURE_2D);

            glPushMatrix();

                glTranslatef(-12,-1.2,-20);
                 //glRotatef(90,0,0,1);
                glScalef(24,10,5);
                glBindTexture(GL_TEXTURE_2D,6);
                //glRotated(180,0,0,1);
                mycube();
            glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void drawlights(){
    glPushMatrix();
    Material(0.504, 0.518, 0.530);
    glTranslated(-15,10,-4);
    glRotated(90,1,0,0);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic,0.3f,0.5f,10.0f,15,15);

    //gluCylinder();

    glPopMatrix();

    glPushMatrix();
    Material(0.504, 0.518, 0.530);
    glTranslated(-15.25,9.5,-5);
    glRotated(-30,0,0,1);
    glScaled(1,2,2);

    mycube();
    glPopMatrix();
glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    Material(1, 1, 1);
    glTranslated(-14.4,9,-5);
    glRotated(-30,0,0,1);
    glScaled(0.1,2,2);
glBindTexture(GL_TEXTURE_2D,15);

    mycube();
    glPopMatrix();
 glDisable(GL_TEXTURE_2D);

}
void drawlightsright(){

    glPushMatrix();
    glTranslated(0,0,-8);
    glRotated(180,0,1,0);
    drawlights();

    glPopMatrix();

}

void drawSkyBox()
{
    Material(1.0,1.0,1.0);
    //up anticlockwise
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,7);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-40,20,-40);
	glTexCoord2f(1, 1); glVertex3f(-40,20,40);
	glTexCoord2f(1, 0); glVertex3f(40,20,40);
	glTexCoord2f(0, 0); glVertex3f(40,20,-40);
	glEnd();

    //right anticlockwise
	glBindTexture(GL_TEXTURE_2D,8);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(40,20,-40);
	glTexCoord2f(1, 1); glVertex3f(40,20,40);
	glTexCoord2f(1, 0); glVertex3f(40,-3,40);
	glTexCoord2f(0, 0); glVertex3f(40,-3,-40);
	glEnd();

   //left clockwise
	glBindTexture(GL_TEXTURE_2D,9);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3f(-40,-3,-40);
	glTexCoord2f(0, 0); glVertex3f(-40,-3,40);
	glTexCoord2f(0, 1); glVertex3f(-40,20,40);
	glTexCoord2f(1, 1); glVertex3f(-40,20,-40);
	glEnd();

     //back clockwise
    glBindTexture(GL_TEXTURE_2D,10);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-40,20,40);
	glTexCoord2f(1, 1); glVertex3f(40,20,40);
	glTexCoord2f(1, 0); glVertex3f(40,-3,40);
	glTexCoord2f(0, 0); glVertex3f(-40,-3,40);
	glEnd();

    //front anticlockwise
	glBindTexture(GL_TEXTURE_2D,11);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3f(-40,-3,-40);
	glTexCoord2f(0, 0); glVertex3f(40,-3,-40);
	glTexCoord2f(0, 1); glVertex3f(40,20,-40);
	glTexCoord2f(1, 1); glVertex3f(-40,20,-40);
	glEnd();

    //down clockwise
	glBindTexture(GL_TEXTURE_2D,12);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3f(40,-3,-40);
	glTexCoord2f(0, 0); glVertex3f(40,-3,40);
	glTexCoord2f(0, 1); glVertex3f(-40,-3,40);
	glTexCoord2f(1, 1); glVertex3f(-40,-3,-40);
	glEnd();
 	glDisable(GL_TEXTURE_2D);

}
int clikd=0;

float wcsClkDn[3],wcsClkUp[3];
///////////////////////////////
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
} clkpt[2];
int flag=0;
GLboolean buttonclk=false;
GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info

//////////////////////////
void scsToWcs(float sx,float sy, float wcsv[3] );
void processMouse(int button, int state, int x, int y);
void matColor(float kdr, float kdg, float kdb,  float shiny, int frnt_Back=0, float ambFactor=1.0, float specFactor=1.0);
///////////////////////////

void scsToWcs(float sx,float sy, float wcsv[3] )
{

    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    //glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

    winX = sx;
    winY = (float)viewport[3] - (float)sy;
    winZ = 0;

    //get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    wcsv[0]=worldX;
    wcsv[1]=worldY;
    wcsv[2]=worldZ;


}
void processMouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(flag!=1)
        {
            flag=1;
            clkpt[0].x=x;
            clkpt[0].y=y;
        }


        scsToWcs(clkpt[0].x,clkpt[0].y,wcsClkDn);
        cout<<"\nD: "<<x<<" "<<y<<" wcs: "<<wcsClkDn[0]<<" "<<wcsClkDn[1];
         if(x>458 && x<585){
            if(y>233 && y<302){
                buttonclk=true;
                counter=0;
                score=0;
            }
        }

    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if (flag==1)
        {
            clkpt[1].x=x;
            clkpt[1].y=y;
            flag=0;
        }
        float wcs[3];
        scsToWcs(clkpt[1].x,clkpt[1].y,wcsClkUp);
        cout<<"\nU: "<<x<<" "<<y<<" wcs: "<<wcsClkUp[0]<<" "<<wcsClkUp[1];

        clikd=!clikd;
    }
}
GLfloat playx=1.5,playy=-1,playz=0.05;
void drawplaybutton(){
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslated(-0.5,2.5,5);
    glScaled(playx,playy,playz);
    glBindTexture(GL_TEXTURE_2D,13);
    mycube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}
GLfloat textx=.008,texty=0.01,textz=1;
void textDisplay(string str,int x,int y,int z)
{

    GLfloat mat_ambient[] = { 1, 0, 0, 1.0 };
    GLfloat mat_diffuse[] = { 1, 0, 0, 1.0 };
    GLfloat mat_specular[] = { 1,1,1, 1.0 };
    GLfloat mat_shininess[] = {10};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1);
    //glColor3b(1,0,0);
    glPushMatrix();
    glTranslatef(x, y,z);
    glScalef(.008,0.01,1);

    for (int i=0; i<str.size(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}
void drawtv(){
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslated(-3,11,-15);
    glScaled(6,-3.5,0.1);
        glBindTexture(GL_TEXTURE_2D,14);
    mycube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

float xT=0,yT=0;

static void display(void)
{

   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5,5,-5,5, 4,50);
    gluPerspective(90,1,1,200);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(ex,ey,ez,lx,ly,lz,hx,hy,hz);
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT1);
    LightThree();
    LightOne();
    LightTwo();

    //glViewport(0, 0, windowHeight, windowWidth);
     glRotatef( alpha,axis_x, axis_y, axis_z );
    glRotatef( theta, axis_x, axis_y, axis_z );
    glRotatef( gama, axis_x, axis_y, axis_z );
    //goalbar
    glTranslatef(xT,yT,zT);

    drawSkyBox();
    Material(0.274, 0.662, 0.740);
    glPushMatrix();
        glTranslatef(-3  ,0,-6);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(1,11,1);
        glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,1,-6);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(30,1,1);
        glutSolidCube(.2);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(3,0,-6);
        //glRotated(60,1,0,0);
        //glRotatef(90,0,0,1);
        glScalef(1,11,1);
        glutSolidCube(0.2);
    glPopMatrix();


    //goalnetback
    drawgoalnet();
    drawgoalbar();
    //drawgoalnetleft
    drawgoalnetleft();
    //drawgoalnetright
    drawgoalnetright();


    drawfield();
    drawgoalpost2();

    drawplayer();
    drawgoalkeeper();

    drawsoccer();
    drawgallery();
    drawgallery2();

    drawchair();

    drawwatchers();
    drawbuilding();
    drawlights();
    drawlightsright();
    if(buttonclk==true){
    playx=0;
    playy=0;
    playz=0;
    }
    drawplaybutton();


    drawplaybutton();

    if(counter>=10){
        buttonclk=false;
        playx=1.5;
        playy=-1;
        playz=0.05;

        textx=texty=textz=0.5;

        //cout<<buttonclk;
    }
    else{
         textx=texty=textz=0;

    }
    string str1="Score: "+to_string(score);
    drawtv();

    textDisplay(str1,-2.7,8,-14.7);
    glPushMatrix();
    glScaled(0.5,0.5,1);
    string str2="Chances Left: "+to_string(10-counter);
    textDisplay(str2,-4.5,19,-14.7);

    glPopMatrix();
    glPushMatrix();
        glScaled(textx,texty,textz);
        string str3="SCORED: "+to_string(score);
        textDisplay(str3,-2,8,6);
        glPopMatrix();
    glutSwapBuffers();


}
void goalornot(){
    randd= rand()%4;
    cout<<"rand"<<randd;
    save=rand()%2;
    cout<<"save"<<save;

}

void goalkeeper(){
    float i=1*(0.5);
    float j=3*(0.5);

    if(randd==0 && gy>i*(-1)){
        gy-=0.5;
    }
    else if(randd==2 && gy<i){
        gy+=0.5;


    }
    else if(randd==1 && gx>j*(-1)){
        gx-=0.55;


    }
    else if(randd==3 && gx<j){
        gx+=0.5;


    }

}
void shooton(){
    shootangle+=10;
}
GLfloat rr=90;
void roll() // z axis
{
    hx = cos(rr*3.1416/180.0);
    hy = sin(rr*3.1416/180.0);
    printf("%lf %faR\n" , rr,cos(rr*3.1416/180.0));
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'w':
        uRotate = !uRotate;
        lRotate= false;
        dRotate= false;
        rRotate = false;
        zpRotate=false;
        znRotate=false;
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        break;

    case 's':
        dRotate = !dRotate;
        lRotate= false;
        uRotate= false;
        rRotate = false;
        zpRotate=false;
        znRotate=false;
        axis_x=1.0;
        axis_y=0.0;
        axis_z=0.0;
        break;
    case 'a':
        lRotate = !lRotate;
        uRotate = false;
        rRotate= false;
        dRotate= false;
        zpRotate=false;
        znRotate=false;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0.0;
        break;
    case 'd':
        rRotate = !rRotate;
        uRotate = false;
        lRotate= false;
        dRotate= false;
        zpRotate=false;
        znRotate=false;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0.0;
        break;
    case 'f':
        fronT=!fronT;
        backT=false;
        break;
    case 'b':
        backT=!backT;
        fronT=false;
        break;
    //other movement
    case 'g':
        xT+=2;
        break;
    case 'G':
        xT-=2;
        break;
    case 'v':
        yT+=2;
        break;
    case 'V':
        yT-=2;
        break;
    case 'X':           //Camera Right along X axis
        ex += 2;
        break;
    case 'x':           //Camera left along X axis
        ex -= 2;
        break;
    case 'u':
        ey += 0.5;
        break;
    case 'U':
        ey -= 0.5;
        break;
    //pitch
    case 'p':
        ly+=0.20;
        break;
    case 'P':
        ly-=0.20;
        break;
    //yaw
    case 'y':
        lx+=0.30;
        break;
    case 'Y':
        lx-=0.30;
        break;

    case 'r':
        rr+=2;
        roll();
        break;


    case 'R':
        rr-=2;
        roll();
        break;
    case '0':
        if(buttonclk==true){
            counter++;
                cout<<"counter"<<counter;

            bzshoot=true;
            shoot=true;
            goalornot();
            if(save==1){
                randd=0;
            }
            shooton();

        }

        break;
    case '2':
        if(buttonclk==true){
            counter++;
                cout<<"counter"<<counter;

            bzshootup=true;
            shoot=true;
            goalornot();
            if(save==1){
                randd=2;
            }
            shooton();
        }

        break;
    case '1':
        if(buttonclk==true){
            counter++;
                cout<<"counter"<<counter;

            shootleft=true;
            shoot=true;
            goalornot();
            if(save==1){
                randd=1;
            }
            shooton();
        }

        break;
    case '3':
        if(buttonclk==true){
            counter++;
            cout<<"counter"<<counter;
            shootright=true;
            shoot=true;
            goalornot();
            if(save==1){
                randd=3;
            }
            shooton();
        }

        break;
    case 'L':   //light1 white
        if(Light1 == false)
        {
            Light1 = true; ambL1 = true; diffL1 = true; specL1 = true;
            glEnable(GL_LIGHT1);   //Turn on spot light
        }
        else if(Light1 == true)
        {
            Light1 = false; ambL1 = false; diffL1 = false; specL1 = false;
            glDisable(GL_LIGHT1);  //Turn off spot light
        }
        break;
    case 'K':   //front light white
        if(Light2 == false)
        {
            Light2 = true; ambL2 = true; diffL2 = true; specL2 = true;
            glEnable( GL_LIGHT2);    //Turn on light 2
        }
        else if(Light2 == true)
        {
            Light2 = false; ambL2 = false; diffL2 = false; specL2 = false;
            glDisable( GL_LIGHT2);  //Turn off light 2
        }
        break;

    case 'T':   //spotlight
        if(spotLight == false)
        {
            spotLight = true;
            ambL0 = true;
            diffL0 = true;
            specL0 = true;
            glEnable( GL_LIGHT0);
            //Turn on spot light
        }
        else if(spotLight == true)
        {
            spotLight = false;
            ambL0 = false;
            diffL0 = false;
            specL0 = false;
            glDisable( GL_LIGHT0);  //Turn off spot light
        }
        break;
    /*case 'i':
        ex += dx_norm*5;
        ez += dz_norm*5;


        lx += dx_norm*5;
        lz += dz_norm*5;
        break;*/



    case '+':
        Tzval+=0.2;
        break;

    case '-':
        Tzval-=0.2;
        break;

    case 27:	// Escape key
        exit(1);
    }
}
void delay(float secs)
{
	float endd = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < endd);
}

void animate()
{

    if(buttonclk==true){
        if(zT<0){
                zT+=0.1;
        }
    }
    else{
        //cout<<"buttonclk false";
         if(zT>-6 && shoot==false){
            zT-=0.1;

        }
    }


    if(ambL1 == true) {glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient1);}
    else if(ambL1 == false) {glLightfv(GL_LIGHT1, GL_AMBIENT, no_light);}
    if(diffL1 == true) {glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse1);}
    else if(diffL1 == false) {glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);}
    if(specL1 == true) {glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);}
    else if(specL1 == false) {glLightfv(GL_LIGHT1, GL_SPECULAR, no_light);}

     //Light2 white
    if(ambL2 == true) {glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient2);}
    else if(ambL2 == false) {glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);}
    if(diffL2 == true) {glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse2);}
    else if(diffL2 == false) {glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);}
    if(specL2 == true) {glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);}
    else if(specL2 == false) {glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);}
    //spotlight
    if(ambL0 == true) {glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient0);}
    else if(ambL0 == false) {glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);}
    if(diffL0 == true) {glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse0);}
    else if(diffL0 == false) {glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);}
    if(specL0 == true) {glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);}
    else if(specL0 == false) {glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);}



     if (lRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }
    if (rRotate == true)
    {
        theta -= 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (dRotate == true)
    {
        alpha -= 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    if (zpRotate == true)
    {
        gama += 0.2;
        if(gama > 360.0)
            gama -= 360.0*floor(gama/360.0);
    }
    if (znRotate == true)
    {
        gama -= 0.2;
        if(gama > 360.0)
            gama -= 360.0*floor(gama/360.0);
    }
    if (fronT == true)
    {
        zT+=1;
        fronT=false;
    }
    if (backT == true)
    {
        zT-=1;
        backT=false;
    }
    if (bzshoot == true && randd==0)
    {
            float i=55.0*(-0.1);

            bz=bz-0.1;


            if (bz<i){
                //glutPostRedisplay();


                bzshoot=false;
                delay(2);
                bz=0;
                shoot=false;
                shootangle=0;
                gy=0;
                gx=0;


           }
    }
    if (bzshoot == true && randd!=0)
    {

        float i=70.0*(-0.1);

           bz=bz-0.1;


        if (bz<i){
                //glutPostRedisplay();
                score+=1;
                cout<<"score="<<score;
                 bzshoot=false;
                 delay(2);
                 bz=0;
                 shoot=false;
                shootangle=0;

                gy=0;
                gx=0;
           }

    }
    if (bzshootup == true && randd==2)
    {
        float i=55.0*(-0.1);
        bz-=0.05;
        by+=0.01;
        if (bz<i){
                //bz+=1;
                by=0;
                 bzshootup=false;
                 delay(2);
                bz=0;
                shoot=false;
                shootangle=0;
                gy=0;
                gx=0;
           }
        }
    if (bzshootup == true && randd!=2)
    {

        float i=70.0*(-0.1);
        bz-=0.05;
        by+=0.01;
        if (bz<i){
                score+=1;
                cout<<"score="<<score;
                //bz+=1;
                by=0;

                 bzshootup=false;
                 delay(2);
                bz=0;
                shoot=false;
                shootangle=0;
                gy=0;
                gx=0;
           }
        //bzshoot=false;
    }

    if (shootleft == true && randd==1)
    {
        float i=55.0*(-0.1);
        bz-=0.05;
        by+=0.005;
        bx-=0.015;
        if (bz<i){
                //bz+=1;
                 shootleft=false;
                 delay(2);
                by=0;
                bx=0;
                bz=0;
                shoot=false;
                shootangle=0;
                gy=0;
                gx=0;
           }
        }
    if (shootleft == true && randd!=1)
    {

        float i=70.0*(-0.1);
        bz-=0.05;
        by+=0.01;
        bx-=0.015;
        if (bz<i){
                score+=1;
                cout<<"score="<<score;
                bz+=1;


                 shootleft=false;
                 delay(2);
                  by=0;
                  bx=0;
                bz=0;
                shoot=false;
                shootangle=0;
                gy=0;
                gx=0;
           }
        //bzshoot=false;
    }
    if (shootright == true && randd==3)
    {
        float i=55.0*(-0.1);
        bz-=0.05;
        by+=0.005;
        bx+=0.015;
        if (bz<i){
                //bz+=1;
                 shootright=false;
                 delay(2);
                by=0;
                bx=0;
                bz=0;
                shoot=false;
                shootangle=0;
                gy=0;
                gx=0;
           }
        }
    if (shootright == true && randd!=3)
    {

        float i=70.0*(-0.1);
        bz-=0.05;
        by+=0.01;
        bx+=0.015;
        if (bz<i){
                score+=1;
                cout<<"score="<<score;
                //bz+=1;


                 shootright=false;
                 delay(2);
                  by=0;
                  bx=0;
                bz=0;
                shoot=false;
                shootangle=0;
                gy=0;
                gx=0;
           }
        //bzshoot=false;
    }
    if(shoot==true){

        goalkeeper();
    }

    glutPostRedisplay();

}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    // gluPerspective(60,ar, 2.0, 100.0);

    glOrtho(-8.0, 8.0, -8.0*(GLfloat)height/(GLfloat)width, 8.0*(GLfloat)height/(GLfloat)width, 2.0, 25.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt(ex,ey,ez,lx,ly,lz,hx,hy,hz);
}


/* Program entry point */
void LoadTexture(const char*filename,int index)
{

    glGenTextures(1, &ID[index]);
    glBindTexture(GL_TEXTURE_2D, ID[index]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[index]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Penalty Shooting Game");
    glutReshapeFunc(resize);

    //LoadTexture("C:\\field.bmp");
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\field.bmp",1);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\advertisement2.bmp",2);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\jersy.bmp",3);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\pant.bmp",4);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\watchers1.bmp",5);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\building.bmp",6);


    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\skyup2.bmp",7);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\skyfront4.bmp",8);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\skyfront4.bmp",9);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\skyfront4.bmp",10);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\skyfront4.bmp",11);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\skydown2.bmp",12);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\button2.bmp",13);

    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\tv.bmp",14);
    LoadTexture("D:\\STUDY\\CSE 4.2\\graphics lab\\l2\\project1\\images\\light.bmp",15);





    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);


    //glClearColor(0,0,0,1);


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glutMouseFunc(processMouse);

    //glDisable(GL_BLEND);
    //glEnable(GL_LIGHTING);

//    light();


    glutMainLoop();
    return EXIT_SUCCESS;
}
