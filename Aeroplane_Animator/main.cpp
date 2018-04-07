#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
GLfloat x1,y1,x2,y2,x3,y3,x4,y4;

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

void drawpixel(int x,int y)
{
            glColor3f(1.0,0.0,0.0);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
            int le[500],re[500];
            int i,y;
            for(i=0;i<500;i++)
            {
                        le[i]=500;
                        re[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le,re);
            edgedetect(x2,y2,x3,y3,le,re);
            edgedetect(x3,y3,x4,y4,le,re);
            edgedetect(x4,y4,x1,y1,le,re);
for(y=0;y<500;y++)
{
           if(le[y]<=re[y])
                        for(i=le[y]+1;i<re[y];i++)
                                    drawpixel(i,y);
}
}

void runaway(void)
{
    x1=0,y1=0,x2=0,y2=500,x3=1920,y3=500,x4=1920,y4=0;

    glBegin(GL_LINE_LOOP);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();

    scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
    glFlush();



}
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
runaway();
/*glPointSize(10.0);
glBegin(GL_POINTS);
glColor3f(1.0,1.0,1.0);
glVertex2d(10,10);
glVertex2d(20,50);
glEnd();*/
glutSwapBuffers();
}


void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0.0,1920.0,0.0,1080.0);
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(1920,1080);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Frame_1");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
}
