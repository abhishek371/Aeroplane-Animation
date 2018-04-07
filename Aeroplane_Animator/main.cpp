#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
GLfloat x1,y1,x2,y2,x3,y3,x4,y4;
GLfloat div_x1,div_y1,div_x2,div_y2,div_x3,div_y3,div_x4,div_y4;



int SCREEN_WIDTH=1920;
int SCREEN_HEIGHT=1080;

void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,int *le,int *re)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)
            {
              temp=x1;x1=x2;x2=temp;
              temp=y1;y1=y2;y2=temp;
            }
              if((y2-y1)!=0)
                        mx=(x2-x1)/(y2-y1);
            else
                        mx=x2-x1;
            x=x1;
            for(i=y1;i<y2;i++)
            {
                        if(x<le[i])
                                    le[i]=x;
                        if(x>re[i])
                                    re[i]=x;
                        x+=mx;
            }
}

void drawpixel(int x,int y,float r, float g, float b)
{
            glColor3f(r,g,b);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float r,float g,float b)
{
            int le[SCREEN_WIDTH],re[SCREEN_HEIGHT];
            int i,y;
            for(i=0;i<SCREEN_WIDTH;i++)
            {
                        le[i]=SCREEN_WIDTH;
                        re[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le,re);
            edgedetect(x2,y2,x3,y3,le,re);
            edgedetect(x3,y3,x4,y4,le,re);
            edgedetect(x4,y4,x1,y1,le,re);
for(y=0;y<SCREEN_HEIGHT;y++)
{
           if(le[y]<=re[y])
                        for(i=le[y]+1;i<re[y];i++)
                                    drawpixel(i,y,r,g,b);
}
}

void runaway(void)
{
    x1=0,y1=50,x2=0,y2=350,x3=1920,y3=350,x4=1920,y4=50;
    scanfill(x1,y1,x2,y2,x3,y3,x4,y4,0.000,0.000,0.000);
    div_x1=25,div_x2=25,div_x3=75,div_x4=75;
    div_y1=160,div_y2=190,div_y3=190,div_y4=160;
    scanfill(div_x1,div_y1,div_x2,div_y2,div_x3,div_y3,div_x4,div_y4,0.753,0.753,0.753);

    glFlush();



}
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
runaway();
glutSwapBuffers();
}


void myInit(void)
{
	glClearColor(0.878,1.000,1.000,1.0);
	gluOrtho2D(0.0,1920.0,0.0,1080.0);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Frame_1");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
}
