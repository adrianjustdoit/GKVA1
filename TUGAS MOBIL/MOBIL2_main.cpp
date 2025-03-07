#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535898

void DrawCircle(GLfloat x, GLfloat y, GLfloat radius, int circle_points) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Titik pusat lingkaran
    for (int i = 0; i <= circle_points; i++) {
        float angle = 2.0f * PI * i / circle_points;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

void DrawSun(GLfloat x, GLfloat y, GLfloat radius, int rays, GLfloat ray_length) {
    // Draw the sun's core (circle)
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    DrawCircle(x, y, radius, 50);
    
    // Draw the sun rays
    glColor3f(1.0f, 0.8f, 0.0f); // Orange color
    glBegin(GL_LINES);
    for (int i = 0; i < rays; i++) {
        float angle = 2.0f * PI * i / rays;
        float x_start = x + radius * cos(angle);
        float y_start = y + radius * sin(angle);
        float x_end = x + (radius + ray_length) * cos(angle);
        float y_end = y + (radius + ray_length) * sin(angle);
        glVertex2f(x_start, y_start);
        glVertex2f(x_end, y_end);
    }
    glEnd();
}


void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
        glColor3f(0.52f, 0.80f, 0.92f);
        glRectf(-1.0, 0.0, 1.0, 1.0);
    glPopMatrix();
    
    glPushMatrix();
        DrawSun(0.60f, 0.60f, 0.2f, 12, 0.1f);
    glPopMatrix();

    // Badan mobil
    glPushMatrix();
        glColor3f(0.66f, 0.10f, 0.10f);
        glRectf(-0.40, 0.10, 0.40, -0.10);
    glPopMatrix();
    
    glPushMatrix();
    	glLineWidth(5.0f);
		glColor3f(0.80f, 0.125f, 0.161f);
        glBegin(GL_LINE_STRIP);
		glVertex2f(-0.39f,0.0f);
		glVertex2f(-0.19f, 0.09f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.19f, -0.09f);
        glVertex2f(0.39f, 0.0f);
		glEnd();
    glPopMatrix();
    
    
    
    

    // Atap mobil
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f); 
        glRectf(-0.20, 0.25, 0.20, 0.10);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.52f, 0.80f, 0.92f);
        glRectf(-0.18, 0.23, -0.009, 0.10);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.52f, 0.80f, 0.92f); 
        glRectf(0.009, 0.23, 0.18, 0.10);
    glPopMatrix();
    
    glPushMatrix();
		glLineWidth(2.0f);
		glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.04, 0.20, 0.0);
			glVertex3f(-0.15, 0.12, 0.0);
		glEnd();
	glPopMatrix();
	
	glPushMatrix();
		glLineWidth(2.0f);
		glTranslatef(0.2,0,0);
		glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-0.04, 0.20, 0.0);
			glVertex3f(-0.15, 0.12, 0.0);
		glEnd();
	glPopMatrix();

    // Roda kiri
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f); 
        DrawCircle(-0.30, -0.10, 0.08, 500);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f); 
        DrawCircle(-0.30, -0.10, 0.03, 5);
    glPopMatrix();

    // Roda kanan
    glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        DrawCircle(0.30, -0.10, 0.08, 500);
    glPopMatrix();
    
     glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        DrawCircle(0.30, -0.10, 0.03, 5);
    glPopMatrix();

    glFlush();
}

void Setup(void) {
    glClearColor(0.196f, 0.90f, 0.196f, 1.0f); // Latar belakang putih
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil Sederhana dengan OpenGL");
    Setup();
    glutDisplayFunc(RenderScene);
    glutMainLoop();
    return 0;
}

