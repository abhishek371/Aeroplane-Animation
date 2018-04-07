#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
GLfloat x1,y1,x2,y2,x3,y3,x4,y4;
GLfloat div_x1,div_y1,div_x2,div_y2,div_x3,div_y3,div_x4,div_y4;
GLfloat bside_x1,bside_y1,bside_x2,bside_y2,bside_x3,bside_y3,bside_x4,bside_y4;
GLfloat tside_x1,tside_y1,tside_x2,tside_y2,tside_x3,tside_y3,tside_x4,tside_y4;

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
                        re[i]=x2;
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
void scanfill_bushes(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float r,float g,float b)
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
    div_x1=0,div_x2=20,div_x3=140,div_x4=120;
    div_y1=185,div_y2=215,div_y3=215,div_y4=185;
    scanfill(div_x1,div_y1,div_x2,div_y2,div_x3,div_y3,div_x4,div_y4,0.753,0.753,0.753);
    int k=100;
    while(k<1920)
    {
        div_x1+=250,div_x2+=250,div_x3+=250,div_x4+=250;
        scanfill(div_x1,div_y1,div_x2,div_y2,div_x3,div_y3,div_x4,div_y4,0.753,0.753,0.753);
        k+=200;


    }
    glFlush();
}
    void bottomsideBushes(void)
    {
        bside_x1=0,bside_y1=0,bside_x2=0,bside_y2=50,bside_x3=1920,bside_y3=50,bside_x4=1920,bside_y4=0;
        scanfill(bside_x1,bside_y1,bside_x2,bside_y2,bside_x3,bside_y3,bside_x4,bside_y4,0.133,0.545,0.133);
        glFlush();
    }
    void topsideBushes(void)
    {
        tside_x1=0,tside_y1=350,tside_x2=0,tside_y2=400,tside_x3=1920,tside_y3=400,tside_x4=1920,tside_y4=350;
        scanfill_bushes(tside_x1,tside_y1,tside_x2,tside_y2,tside_x3,tside_y3,tside_x4,tside_y4,0.133,0.545,0.133);
        glFlush();
    }




void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
runaway();
bottomsideBushes();
topsideBushes();
glutSwapBuffers();
}


void myInit(void)
{
	glClearColor(0.854,0.964,0.933,1);
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
