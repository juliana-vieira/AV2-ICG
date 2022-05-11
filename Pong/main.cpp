#include <windows.h>
#include <gl/glut.h>

float posicaoX, posicaoY, posicao2X, posicao2Y = 0;

// Tamanho e posição inicial da bola
GLfloat xbola = 100.0f;
GLfloat ybola = 150.0f;
GLsizei tamBola = 5;

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


/*void campo(){
    glBegin(GL_QUADS);
    //linha direita
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(10.0f, -0.85f);
        glVertex2f(0.98f, -0.85f);
        glVertex2f(0.98f, 0.85f);
        glVertex2f(10.0f, 0.85f);
    glEnd();
    //linha esquerda
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-10.0f, -0.85f);
        glVertex2f(-0.98f, -0.85f);
        glVertex2f(-0.98f, 0.85f);
        glVertex2f(-10.0f, 0.85f);
    glEnd();
    //linha superior
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-10.0f, 0.9f);
        glVertex2f(-10.0f, 0.85f);
        glVertex2f(10.0f, 0.9f);
        glVertex2f(10.0f, 0.85f);
    glEnd();
    //linha inferior
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-10.0f, -0.9f);
        glVertex2f(-10.0f, -0.85f);
        glVertex2f(10.0f, -0.9f);
        glVertex2f(10.0f, -0.85f);
    glEnd();
}*/


void eventoTeclado(unsigned char tecla, int x, int y)
{
    switch (tecla) {
    case 'w':
        posicaoY += 10.0;
        break;
    case 's':
        posicaoY -= 10.0;
        break;
    case 'r':
        posicao2Y += 10.0;
        break;
    case 'f':
        posicao2Y -= 10.0;
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
        glVertex2i(xbola,ybola+tamBola);
        glVertex2i(xbola,ybola);
        glVertex2i(xbola+tamBola,ybola);
        glVertex2i(xbola+tamBola,ybola+tamBola);
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

// Função callback chamada pela GLUT a cada intervalo de tempo
void timer(int id)
{
    // Muda a direção quando chega na borda esquerda ou direita
    if(xbola > windowWidth-tamBola || xbola < 0)
            xstep = -xstep;

    // Muda a direção quando chega na borda superior ou inferior
    if(ybola > windowHeight-tamBola || ybola < 0)
          ystep = -ystep;

    // Verifica as bordas.  Se a window for menor e o
    // quadrado sair do volume de visualização
    if(xbola > windowWidth-tamBola)
         xbola = windowWidth-tamBola-1;

    if(ybola > windowHeight-tamBola)
         ybola = windowHeight-tamBola-1;

    // Move o quadrado
    xbola += xstep;
    ybola += ystep;

    // Redesenha o quadrado com as novas coordenadas
    glutPostRedisplay();
    glutTimerFunc(33, timer, 1);
}

void inicializar(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void alteraTamanhoJanela(GLsizei w, GLsizei h)
{
     // Evita a divisao por zero
     if(h == 0) h = 1;

     // Especifica as dimensões da Viewport
     glViewport(0, 0, w, h);

     // Inicializa o sistema de coordenadas
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     // Estabelece a janela de seleção (left, right, bottom, top)
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

