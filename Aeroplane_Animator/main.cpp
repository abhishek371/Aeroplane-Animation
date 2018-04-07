#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
GLfloat x1,y1,x2,y2,x3,y3,x4,y4;
GLfloat div_x1,div_y1,div_x2,div_y2,div_x3,div_y3,div_x4,div_y4;
GLfloat bside_x1,bside_y1,bside_x2,bside_y2,bside_x3,bside_y3,bside_x4,bside_y4;
GLfloat tside_x1,tside_y1,tside_x2,tside_y2,tside_x3,tside_y3,tside_x4,tside_y4;
GLfloat tower_base_x1,tower_base_y1,tower_base_x2,tower_base_y2,tower_base_x3,tower_base_y3,tower_base_x4,tower_base_y4;
GLfloat tower_top_x1,tower_top_y1,tower_top_x2,tower_top_y2,tower_top_x3,tower_top_y3,tower_top_x4,tower_top_y4;
GLfloat tx1,ty1,tx2,ty2,tx3,ty3,tx4,ty4;

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
                        re[i]=x1;
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
    x1=0,y1=50,x2=0,y2=300,x3=1920,y3=300,x4=1920,y4=50;
    scanfill(x1,y1,x2,y2,x3,y3,x4,y4,0.000,0.000,0.000);
    div_x1=0,div_x2=20,div_x3=140,div_x4=120;
    div_y1=160,div_y2=190,div_y3=190,div_y4=160;
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
        tside_x1=0,tside_y1=300,tside_x2=0,tside_y2=350,tside_x3=1920,tside_y3=350,tside_x4=1920,tside_y4=300;
        scanfill_bushes(tside_x1,tside_y1,tside_x2,tside_y2,tside_x3,tside_y3,tside_x4,tside_y4,0.133,0.545,0.133);
        glFlush();
    }

    void tower(void)
    {
        tower_base_x1=100,tower_base_x2=100,tower_base_x3=230,tower_base_x4=230,tower_base_y1=350,tower_base_y2=650,tower_base_y3=650,tower_base_y4=350;
        scanfill_bushes(tower_base_x1,tower_base_y1,tower_base_x2,tower_base_y2,tower_base_x3,tower_base_y3,tower_base_x4,tower_base_y4,0.541,0.541,0.458);
        tower_top_x1=80,tower_top_x2=80,tower_top_x3=250,tower_top_x4=250,tower_top_y1=630,tower_top_y2=700,tower_top_y3=700,tower_top_y4=630;
        scanfill(tower_top_x1,tower_top_y1,tower_top_x2,tower_top_y2,tower_top_x3,tower_top_y3,tower_top_x4,tower_top_y4,0.541,0.541,0.458);

        glFlush();


    }




void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
runaway();
bottomsideBushes();
topsideBushes();
tower();
glutSwapBuffers();
}


void myInit(void)
{
	glClearColor(0.854,0.964,0.933,0.5);
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
