#include <GL/glut.h>
#include <stdio.h>

/* Nome: Eirene de Oliveira Fireman
 *
 * Comandos do keyboard:
 *		y: Ativa translação dos planetas
 */

//TRANSLAÇÃO é o movimento que um objeto realiza de um ponto a outro.
//ROTAÇÃO É movimento circular de um objeto ao redor de um centro ou ponto de rotação

//definindo as cores dos planetas
#define ORANGE  0.8, 0.5, 0.1
#define YELLOW  1.0, 1.0, 0.0
#define RED 1.0, 0.0, 0.0
#define PINK     0.7, 0.1, 0.6
#define PINK_RED     0.8, 0.4, 0.3
#define BLUE     0.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0
#define GRAY    0.6, 0.6, 0.6

//definindo tamanho da janela
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 500

//definindo x e y iniciais
#define x_position 200
#define y_position 200


//iniciando as variáveis de frame e velocidade
int frame = 0;
double speed = 1.0;

void reshape(int width, int height) {

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, (double)width / height, 1, 20);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

void frameControl(int value) {

    glutTimerFunc(10, frameControl, 0);
    frame++;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 'y':
            glutTimerFunc(10, frameControl, 1);
            break;
        default:
            break;
    }
}

void planetWithTwoMoons() {

    // ------- PLANETA COM DUAS LUAS -------
    glPushMatrix();

    glColor3f(BLUE);
    speed = 0.5;
    glRotatef(speed * frame, 0, 1, 0);
    glTranslatef(-2.5, 0.4, -1);
    glPushMatrix();
    glutSolidSphere(0.2, 100, 100);
    glPopMatrix();

    // ------- LUA 1 -------
    glPushMatrix();
    glColor3f(GRAY);
    speed = 1.5;
    glRotatef(speed * frame, 0, 1, 0);
    glTranslatef(0.45, 0.1, 0);
    glutSolidSphere(0.05, 100, 100);
    glPopMatrix();

    // ------- LUA 2 -------
    glPushMatrix();
    glColor3f(PINK_RED);
    speed = 2.0;
    glRotatef(speed * frame, 5, 3, 0);
    glTranslatef(0.45, 0, 0);
    glutSolidSphere(0.07, 100, 100);
    glPopMatrix();

    glPopMatrix();
}

void solarSystem() {

    // ------- SOL -------
    glPushMatrix();
    //cria uma esfera laranja parada
    glColor3f(ORANGE);
    glutSolidSphere(0.5, 100, 100);
    glPopMatrix();

    // ------- PLANETA COM DUAS LUAS -------
    planetWithTwoMoons();

    // ------- PLANETA 2 -------
    glColor3f(GREEN);
    speed = 1;
    glRotatef(speed * frame, 0, -1, 0);
    glTranslatef(-1, -0.05, 0);
    glutSolidSphere(0.1, 100, 100); 
    glPopMatrix();

    //obs: as velocidades vão aumentando de 0.5 em 0.5 para que um fique atrás do outro
    //obs: em rotate o angulo é cumulativo

    // ------- PLANETA 3 -------
    glPushMatrix();
    glColor3f(RED);
    speed = 1.5;
    glRotatef(speed * frame, 0, 1, 0);
    glTranslatef(1.1, 0.4, 1);
    glutSolidSphere(0.1, 100, 100); 
    glPopMatrix();

    // ------- PLANETA 4 -------
    glPushMatrix();
    glColor3f(YELLOW);
    speed = 2;
    glRotatef(speed * frame, 0, -1, 0);
    glTranslatef(-2, -0.4, 0);
    glutSolidSphere(0.1, 100, 100);
    glPopMatrix();

    // ------- PLANETA 5 -------
    glPushMatrix();
    glColor3f(PINK);
    speed = 2.5;
    glRotatef(speed * frame, 0, 1, 0);
    glTranslatef(2, 0, 0);
    glutSolidSphere(0.1, 100, 100);
    glPopMatrix();
}

void display() {

    // Limpa o buffer de profundidade a cada quadro utilizado
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    solarSystem();
    glPopMatrix();

    // Executa os comandos OpenGL
    glutSwapBuffers();
}

int main(int argc, char** argv) {

    //iniciando janela
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Solar System");
    glutInitWindowPosition(x_position, y_position);

    //definindo cor do background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //iniciando armazenamento de valores no buffer de profundidade
    glEnable(GL_DEPTH_TEST);

    //habilitando cores para utilizar o gl color material
    glEnable(GL_COLOR_MATERIAL);

    //especifica a técnica de coloração desejada, no caso a GL_FLAT permite que os polígonos sejam preenchidos com uma única cor
    glShadeModel(GL_FLAT);

    //define a função de callback para a janela atual
    glutDisplayFunc(display);

    //seta o callback do keyboard para a janela atual
    glutKeyboardFunc(keyboard);

    //define a função callback para a alteração de tamanho da janela
    glutReshapeFunc(reshape);

    //é a função que faz com que comece a execução da “máquina de estados” 
    glutMainLoop();

    return 0;
}