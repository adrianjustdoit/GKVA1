#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535898

void drawCircle(GLfloat x, GLfloat y, GLfloat radius, int circle_points) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= circle_points; i++) {
        float angle = 2.0f * PI * i / circle_points;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

void DrawCircle(GLfloat x, GLfloat y, GLfloat radius, int circle_points) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Titik pusat lingkaran
    for (int i = 0; i <= circle_points; i++) {
        float angle = 2.0f * PI * i / circle_points;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

void DrawSun(GLfloat x, GLfloat y, GLfloat radius) {
    // Warna bulan (abu-abu muda)
    glColor3f(0.8f, 0.8f, 0.8f);
    
    // Gambar lingkaran utama untuk bulan
    DrawCircle(x, y, radius, 50);
    
    // Kawah kecil (random posisi)
    glColor3f(0.6f, 0.6f, 0.6f);
    DrawCircle(x + radius * 0.3, y + radius * 0.3, radius * 0.2, 20);
    DrawCircle(x - radius * 0.2, y - radius * 0.1, radius * 0.15, 20);
    DrawCircle(x + radius * 0.1, y - radius * 0.3, radius * 0.1, 15);
    
    glEnd();
}


void SegiEmpat(float x1, float y1, float x2, float y2){
    glRectf(x1, y1, x2, y2);
}

void wheels(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(0.0f, 0.0f, 0.25f, 20);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.0f, 0.0f, 0.15f, 20);
    glColor3f(0.4f, 0.4f, 0.4f);
    drawCircle(0.0f, 0.0f, 0.1f, 20);
    glColor3f(0.8f, 0.8f, 0.8f);
    drawCircle(0.0f, 0.0f, 0.06f, 20);
    glPopMatrix();
}

void wheels2(void){
	glColor3f(0.0f, 0.0f, 0.0f);
	drawCircle(0.0f, 0.0f, 0.25f, 20);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(0.0f, 0.0f, 0.15f, 20);
	glColor3f(0.4f, 0.4f, 0.4f);
	drawCircle(0.0f, 0.0f, 0.1f, 20);
	glColor3f(0.8f, 0.8f, 0.8f);
	drawCircle(0.0f, 0.0f, 0.06f, 20);
	
	glPushMatrix();
	glTranslatef(0.065f, 0.065f, 0.0f);
	glRotated(-45.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	SegiEmpat(-0.05f, 0.025f, 0.05f, -0.025);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.1f, 0.0f);
	glRotated(90.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.8f, 0.8f, 0.8f);
	SegiEmpat(-0.04f, 0.02f, 0.04f, -0.02);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.1f, 0.04f, 0.0f);
	glRotated(25.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.8f, 0.8f, 0.8f);
	SegiEmpat(-0.045f, 0.02f, 0.04f, -0.02);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.1f, 0.04f, 0.0f);
	glRotated(-25.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.8f, 0.8f, 0.8f);
	SegiEmpat(-0.04f, 0.02f, 0.045f, -0.02);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.07f, -0.06f, 0.0f);
	glRotated(315.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.8f, 0.8f, 0.8f);
	SegiEmpat(-0.03f, 0.02f, 0.05f, -0.02);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.07f, -0.06f, 0.0f);
	glRotated(-315.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.8f, 0.8f, 0.8f);
	SegiEmpat(-0.05f, 0.02f, 0.03f, -0.02);
	glPopMatrix();
	
	glColor3f(0.2f, 0.2f, 0.2f);
	drawCircle(0.0f, 0.0f, 0.03f, 20);
}

void drawTower(float x, float y)
{
    float plus = 1.6;
    x *= plus;
    y *= plus;

    // Menara utama
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 0.2 * plus, y);
    glVertex2f(x + 0.2 * plus, y + 0.5 * plus);
    glVertex2f(x, y + 0.5 * plus);
    glEnd();

    // Jendela
    glColor3f(1.0f,1.0f,0.0f);
    for (float i = y + 0.05 * plus; i < y + 0.5 * plus; i += 0.1 * plus)
    {
        for (float j = x + 0.02 * plus; j < x + 0.2 * plus; j += 0.07 * plus)
        {
            glBegin(GL_QUADS);
            glVertex2f(j, i);
            glVertex2f(j + 0.03 * plus, i);
            glVertex2f(j + 0.03 * plus, i + 0.04 * plus);
            glVertex2f(j, i + 0.04 * plus);
            glEnd();
        }
    }

    // Garis tepi
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 0.2 * plus, y);
    glVertex2f(x + 0.2 * plus, y + 0.5 * plus);
    glVertex2f(x, y + 0.5 * plus);
    glEnd();
}

void drawTower2(float x, float y)
{
    float plus = 1.6;
    x *= plus;
    y *= plus;

    float height = 0.35 * plus;  // Tinggi bangunan lebih pendek

    // Fondasi
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.05 * plus, y);
    glVertex2f(x + 0.25 * plus, y);
    glVertex2f(x + 0.25 * plus, y + 0.1 * plus);
    glVertex2f(x - 0.05 * plus, y + 0.1 * plus);
    glEnd();

    // Badan menara
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(x, y + 0.1 * plus);
    glVertex2f(x + 0.2 * plus, y + 0.1 * plus);
    glVertex2f(x + 0.2 * plus, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Atap Segitiga
    glColor3f(0.7f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.02 * plus, y + height);
    glVertex2f(x + 0.22 * plus, y + height);
    glVertex2f(x + 0.1 * plus, y + (height + 0.1 * plus));
    glEnd();

    // Jendela besar
    glColor3f(0.8f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.05 * plus, y + 0.2 * plus);
    glVertex2f(x + 0.15 * plus, y + 0.2 * plus);
    glVertex2f(x + 0.15 * plus, y + 0.27 * plus);
    glVertex2f(x + 0.05 * plus, y + 0.27 * plus);
    glEnd();

    // Pintu
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.07 * plus, y + 0.1 * plus);
    glVertex2f(x + 0.13 * plus, y + 0.1 * plus);
    glVertex2f(x + 0.13 * plus, y + 0.17 * plus);
    glVertex2f(x + 0.07 * plus, y + 0.17 * plus);
    glEnd();

    // Garis tepi
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y + 0.1 * plus);
    glVertex2f(x + 0.2 * plus, y + 0.1 * plus);
    glVertex2f(x + 0.2 * plus, y + height);
    glVertex2f(x, y + height);
    glEnd();
}




void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    float times = 1.5;
    
    
    

    
    glPushMatrix();
    glScalef(2.0f, 2.0f, 1.0f);
    
    glColor3f(0.42f, 0.60f, 0.92f);
    glRectf(-1.0, 0.0, 1.0, 1.0);
    
    drawTower(-0.4,0.0);
    drawTower(0.0,0.0);
    drawTower2(0.4,0.0);
    
    
    //glTranslatef(-0.1,0.05,1);
    
    
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f*times,-0.05f*times);
        glVertex2f(-0.475f*times,-0.05f*times);
        glVertex2f(-0.475f*times,0.0f*times);
        glVertex2f(-0.45f*times,0.0f*times);
        //depan
        glVertex2f(-0.45f*times,0.05f*times);
        glVertex2f(-0.40f*times,0.07f*times);
        glVertex2f(-0.15f*times,0.125f*times);

        
        
        glVertex2f(-0.125f*times,0.225f*times);
        glVertex2f(0.40f*times,0.225f*times);
        glVertex2f(0.425f*times,0.10f*times);
        
        glVertex2f(0.425f*times,-0.015f*times);
        glVertex2f(0.40f*times,-0.05f*times);
        
    glEnd();
    
    glPopMatrix();
    
    //PINTU
    glPushMatrix();
    	glTranslatef(-0.1,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.915f, 0.900f, 0.910f);
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.20f*times,-0.025f*times);
	    glVertex2f(0.015f*times,-0.025f*times);
	    glVertex2f(0.05f*times,0.025f*times);
	    glVertex2f(0.05f*times,0.20f*times);
	    glVertex2f(-0.10f*times,0.20f*times);
	    glVertex2f(-0.20f*times,0.10f*times);
	    
    	glEnd();
    
	glPopMatrix();
	
	 glPushMatrix();
        DrawSun(1.2f, 1.7f, 0.2f);
    glPopMatrix();
	
	//PINTU
    glPushMatrix();
    	glTranslatef(0.1,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.915f, 0.900f, 0.910f);
	    glBegin(GL_POLYGON);
	    glVertex2f(0.0f*times,-0.01f*times);
	    glVertex2f(0.01f*times,-0.025f*times);
	    glVertex2f(0.168f*times,-0.025f*times);
	    glVertex2f(0.225f*times,0.05f*times);
	    glVertex2f(0.225f*times,0.20f*times);
	    glVertex2f(0.0f*times,0.20f*times);
	    
	    
	    
    	glEnd();
    
	glPopMatrix();
	
	    //GARIS JALAN
    
    
    glPushMatrix();
    	glTranslatef(0,-0.9,1);
    	glLineWidth(10.0f);
    	glScalef(2.0f, 2.0f, 1.0f);
	    glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(1.0,0.00,0.0);
		glVertex3f(-1.0,0.00,0.0);
	    
    	glEnd();
    
	glPopMatrix();
	
	    glPushMatrix();
    	glTranslatef(0,-0.45,1);
    	glLineWidth(10.0f);
    	glScalef(2.0f, 2.0f, 1.0f);
    	glColor3f(1.0f,1.0f,1.0f);
	    glBegin(GL_LINES);
		glVertex3f(-0.80,0.00,0.0);
		glVertex3f(-1.0,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(-0.50,0.00,0.0);
		glVertex3f(-0.70,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(-0.20,0.00,0.0);
		glVertex3f(-0.40,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(0.10,0.00,0.0);
		glVertex3f(-0.10,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(0.40,0.00,0.0);
		glVertex3f(0.20,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(0.70,0.00,0.0);
		glVertex3f(0.50,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(1.0,0.00,0.0);
		glVertex3f(0.80,0.00,0.0);
    	glEnd();
    
	glPopMatrix();
	
	//JALAN BAWAH
	
	glPushMatrix();
    	glTranslatef(0,-1.4,1);
    	glLineWidth(10.0f);
    	glScalef(2.0f, 2.0f, 1.0f);
    	glColor3f(1.0f,1.0f,1.0f);
	    glBegin(GL_LINES);
		glVertex3f(-0.80,0.00,0.0);
		glVertex3f(-1.0,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(-0.50,0.00,0.0);
		glVertex3f(-0.70,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(-0.20,0.00,0.0);
		glVertex3f(-0.40,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(0.10,0.00,0.0);
		glVertex3f(-0.10,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(0.40,0.00,0.0);
		glVertex3f(0.20,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(0.70,0.00,0.0);
		glVertex3f(0.50,0.00,0.0);
    	glEnd();
    	glBegin(GL_LINES);
		glVertex3f(1.0,0.00,0.0);
		glVertex3f(0.80,0.00,0.0);
    	glEnd();
    
	glPopMatrix();
	
	
	 //JENDELA
    glPushMatrix();
    	glTranslatef(-0.1,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.578f, 0.586f, 0.594f);
	    glBegin(GL_POLYGON);
	    glVertex2f(0.04f*times,0.19f*times);
	    glVertex2f(-0.09f*times,0.19f*times);
	    glVertex2f(-0.19f*times,0.10f*times);
	    glVertex2f(0.04f*times,0.10f*times);
	    
    	glEnd();
    
	glPopMatrix();
	
	//JENDELA 2
    glPushMatrix();
    	glTranslatef(0.1,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.578f, 0.586f, 0.594f);
	    glBegin(GL_POLYGON);
	    glVertex2f(0.215f*times,0.1f*times);
	    glVertex2f(0.215f*times,0.19f*times);
	    glVertex2f(0.01f*times,0.19f*times);
	    glVertex2f(0.01f*times,0.1f*times);
	    
	    
	    
    	glEnd();
    
	glPopMatrix();
	
	//JENDELA 3
    glPushMatrix();
    	glTranslatef(0.08,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.578f, 0.586f, 0.594f);
	    glBegin(GL_POLYGON);
	    glVertex2f(0.24f*times,0.1f*times);
	    glVertex2f(0.24f*times,0.19f*times);
	    glVertex2f(0.365f*times,0.19f*times);
	    glVertex2f(0.3854f*times,0.1f*times);
	    
	    
	    
    	glEnd();
    	
    	
    	
    	
    //tuas pintu
    
	glPopMatrix();
	
	glPushMatrix();
		glLineWidth(2.0f);
		glTranslatef(-0.40,0.35,1);
		glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(0.15,0.15,0.0);
		glVertex3f(0.00,0.00,0.0);
	glEnd();
	
	glPopMatrix();
	
	glPushMatrix();
		glLineWidth(2.0f);
		glTranslatef(-0.30,0.35,1);
		glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(0.15,0.15,0.0);
		glVertex3f(0.00,0.00,0.0);
	glEnd();
	
	glPopMatrix();
	
	
		glPushMatrix();
		glLineWidth(2.0f);
		glTranslatef(0.40,0.35,1);
		glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(0.15,0.15,0.0);
		glVertex3f(0.00,0.00,0.0);
	glEnd();
	
	glPopMatrix();
	
	glPushMatrix();
		glLineWidth(2.0f);
		glTranslatef(0.30,0.35,1);
		glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(0.15,0.15,0.0);
		glVertex3f(0.00,0.00,0.0);
	glEnd();
	
	glPopMatrix();
	
	
		glPushMatrix();
		glLineWidth(2.0f);
		glTranslatef(0.90,0.35,1);
		glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(0.15,0.15,0.0);
		glVertex3f(0.00,0.00,0.0);
	glEnd();
	
	glPopMatrix();
	
	glPushMatrix();
		glLineWidth(2.0f);
		glTranslatef(1.0,0.35,1);
		glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex3f(0.15,0.15,0.0);
		glVertex3f(0.00,0.00,0.0);
	glEnd();
	
	glPopMatrix();
	
		
    
        glPushMatrix();
    	glTranslatef(0.3,0.4,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.0f, 0.0f, 0.0f);
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.15f*times,-0.045f*times);
	    glVertex2f(-0.10f*times,-0.045f*times);
	    glVertex2f(-0.10f*times,-0.065f*times);
	    glVertex2f(-0.15f*times,-0.065f*times);
	    
    	glEnd();


	
	
		glPopMatrix();
    
        glPushMatrix();
    	glTranslatef(1,0.4,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.0f, 0.0f, 0.0f);
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.15f*times,-0.045f*times);
	    glVertex2f(-0.10f*times,-0.045f*times);
	    glVertex2f(-0.10f*times,-0.065f*times);
	    glVertex2f(-0.15f*times,-0.065f*times);
	    
    	glEnd();
    
    glPopMatrix();
    
    
    glPushMatrix();
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.0f, 0.0f, 0.0f);
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.25f*times,-0.045f*times);
	    glVertex2f(0.30f*times,-0.045f*times);
	    glVertex2f(0.30f*times,-0.065f*times);
	    glVertex2f(-0.25f*times,-0.065f*times);
	    
    	glEnd();
    
    glPopMatrix();
    
    //under
    
    glPushMatrix();
    	glTranslatef(1.8,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.0f, 0.0f, 0.0f);
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.30f*times,-0.045f*times);
	    glVertex2f(-0.20f*times,-0.045f*times);
	    glVertex2f(-0.20f*times,-0.065f*times);
	    glVertex2f(-0.30f*times,-0.065f*times);
	    
    	glEnd();
    
	glPopMatrix();
    
        glPushMatrix();
    	glTranslatef(-0.5,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.0f, 0.0f, 0.0f);
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.30f*times,-0.045f*times);
	    glVertex2f(-0.10f*times,-0.045f*times);
	    glVertex2f(-0.10f*times,-0.065f*times);
	    glVertex2f(-0.30f*times,-0.065f*times);
	    
    	glEnd();
    
    glPopMatrix();
    
    
    //cover roda
    
    glPushMatrix();
    
    	glTranslatef(0.1,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.40f, 0.40f, 0.40f);
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.25f*times,-0.045f*times);
	    glVertex2f(-0.30f*times,0.035f*times);
	    glVertex2f(-0.4f*times,0.035f*times);
	    glVertex2f(-0.45f*times,-0.045f*times);
	    
	    
    	glEnd();
    
    glPopMatrix();
    
    glPushMatrix();
    
    	glTranslatef(2,0.0,1);
    	glScalef(2.0f, 2.0f, 1.0f);
    	times = 1.5;
    
	    glColor3f(0.40f, 0.40f, 0.40f);
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.25f*times,-0.045f*times);
	    glVertex2f(-0.30f*times,0.035f*times);
	    glVertex2f(-0.4f*times,0.035f*times);
	    glVertex2f(-0.45f*times,-0.05f*times);
	    
	    
    	glEnd();
    
    glPopMatrix();
    
    
    //GARIS JALAN
    
    	
	glPopMatrix();
    
    glScalef(1, 1, 1.0);
	glTranslatef(-0.95, -0.17f, 0.0f);
	wheels2();
	glTranslatef(1.9, 0.0, 0.0f);
	wheels2();
    
    glFlush();
}

void Setup(void) {
    glClearColor(0.815f, 0.800f, 0.810f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
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
