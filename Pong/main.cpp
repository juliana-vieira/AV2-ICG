#include <windows.h>
#include <gl/glut.h>

float posicaoX, posicaoY, posicao2X, posicao2Y = 0;

// Tamanho e posição inicial da bola
GLfloat xbola = 100.0f;
GLfloat ybola = 150.0f;
GLsizei alturaBola = 5;
GLsizei larguraBola = 5;

//Tamanho e posição inicial do jogador 1
GLfloat xJogador1 = 20.0f;
GLfloat yJogador1 = 120.0f;
GLsizei alturaJogador1 = 33;
GLsizei larguraJogador1 = 8;

//Tamanho e posição inicial do jogador 1
GLfloat xJogador2 = 300.0f;
GLfloat yJogador2 = 120.0f;
GLsizei alturaJogador2 = 33;
GLsizei larguraJogador2 = 8;

// Tamanho do incremento nas direções x e y
// (número de pixels para se mover a cada
// intervalo de tempo)
GLfloat xstep = 2.0f;
GLfloat ystep = 2.0f;

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

void eventoTeclado(unsigned char tecla, int x, int y)
{
    switch (tecla) {
    case 'w':
        yJogador1 += 15.0;
        break;
    case 's':
        yJogador1 -= 15.0;
        break;
    case 'r':
        yJogador2 += 15.0;
        break;
    case 'f':
        yJogador2 -= 15.0;
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
    //glutSwapBuffers();
}

void bola(){
    glBegin(GL_QUADS);
        glVertex2i(xbola,ybola+alturaBola);
        glVertex2i(xbola,ybola);
        glVertex2i(xbola+larguraBola,ybola);
        glVertex2i(xbola+larguraBola,ybola+alturaBola);
     glEnd();
}

void jogador1(){
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(xJogador1,yJogador1+alturaJogador1);
        glVertex2i(xJogador1,yJogador1);
        glVertex2i(xJogador1+larguraJogador1,yJogador1);
        glVertex2i(xJogador1+larguraJogador1,yJogador1+alturaJogador1);
    glEnd();
}

void jogador2(){
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(xJogador2,yJogador2+alturaJogador2);
        glVertex2i(xJogador2,yJogador2);
        glVertex2i(xJogador2+larguraJogador2,yJogador2);
        glVertex2i(xJogador2+larguraJogador2,yJogador2+alturaJogador2);
    glEnd();
}

void desenhar(void)
{
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(1.0f, 0.0f, 0.0f);

     bola();

     glPushMatrix();
     glTranslatef(posicaoX, posicaoY, 0);
     jogador1();
     glPopMatrix();
     glPushMatrix();
     glTranslatef(posicao2X, posicao2Y, 0);
     jogador2();
     glPopMatrix();

     glFlush();

     glutSwapBuffers();
}

void timer(int id)
{
    if(xbola < xJogador1 + larguraJogador1 &&
    xbola + larguraBola > xJogador1 &&
    ybola < yJogador1 + alturaJogador1 &&
    ybola + alturaBola > yJogador1)
    {
        xstep = -xstep;
        ystep = -ystep;
        xstep++;
        ystep++;
    }

    if(xbola < xJogador2 + larguraJogador2 &&
    xbola + larguraBola > xJogador2 &&
    ybola < yJogador2 + alturaJogador2 &&
    ybola + alturaBola > yJogador2)
    {
        xstep = -xstep;
        ystep = -ystep;
    }

    if(xbola > windowWidth-larguraBola || xbola < 0){
          glutTimerFunc(33, NULL, 1);
    }

    if(ybola > windowHeight-alturaBola || ybola < 0){
         ystep = -ystep;
    }

    if(xbola > windowWidth-larguraBola)
         xbola = windowWidth-larguraBola-1;

    if(ybola > windowHeight-alturaBola)
         ybola = windowHeight-alturaBola-1;

    xbola += xstep;
    ybola += ystep;
	
    //IA simples
    yJogador1 += ystep-0.03;

    glutPostRedisplay();
    glutTimerFunc(33, timer, 1);
}

void inicializar(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void alteraTamanhoJanela(GLsizei w, GLsizei h)
{
     if(h == 0) h = 1;

     glViewport(0, 0, w, h);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     if (w <= h)  {
		windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
     }
     else  {
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
     }

     gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

int main(int argc, char **argv)
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(800,600);
     glutInitWindowPosition(10,10);
     glutCreateWindow("Pong");
     glutDisplayFunc(desenhar);
     glutReshapeFunc(alteraTamanhoJanela);
     glutKeyboardFunc(eventoTeclado);
     glutTimerFunc(33, timer, 1);
     inicializar();
     glutMainLoop();
}

