// Template untuk mainan objek 3D  
// Kamera bisa maju mundur kiri kanan  
// Sudah dilengkapi pencahayaan  
// Sekarang pake texture  
 
#include <math.h>  
#include <GL/glut.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> 
#include <vector>
 
float angle=0.0, deltaAngle = 0.0, ratio;  
float x=0.0f,y=1.75f,z=15.0f; // posisi awal kamera  
float lx=0.0f,ly=0.0f,lz=-1.0f;  
int deltaMove = 0,h,w;  
int bitmapHeight=12;  
// GLuint _textureId;
int deltaMoveVertical = 0; // Variabel untuk gerakan vertikal

//Membuat gambar menjadi tekstur kemudian berikan ID pada tekstur
// GLuint loadTexture(Image* image) {
//     GLuint textureId;
//     glGenTextures(1, &textureId);
//     glBindTexture(GL_TEXTURE_2D, textureId);

//     // ✅ Pastikan parameter tekstur diatur dengan benar
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//     glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
//     return textureId;
// }

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    // Image* image = loadBMP("test.bmp");
    // _textureId = loadTexture(image);
    // delete image;
}

// Struktur untuk menyimpan target (kotak kayu)
struct Target {
    float tx, ty, tz; // Posisi
    int hp; // Health Point (HP)
};

struct Bullet {
    float bx, by, bz;
    float dx, dz; // Arah gerak peluru
};

std::vector<Bullet> bullets;

std::vector<Target> targets;

// Fungsi untuk membuat target
void createTargets() {
    targets.push_back({0, 1.5, -10, 3}); // Target pertama
    targets.push_back({-3, 1.5, -12, 2}); // Target kedua
}

// Fungsi menembakkan peluru
void shootBullet() {
    Bullet b;
    b.bx = x;
    b.by = y;
    b.bz = z;
    b.dx = lx * 0.2f;
    b.dz = lz * 0.2f;
    bullets.push_back(b);
}

// Mengecek apakah peluru mengenai target
void checkCollision() {
    for (size_t i = 0; i < bullets.size(); i++) {
        for (size_t j = 0; j < targets.size(); j++) {
            // Jika peluru dekat dengan target
            if (fabs(bullets[i].bx - targets[j].tx) < 1.5 &&
                fabs(bullets[i].bz - targets[j].tz) < 1.5) {
                targets[j].hp--; // Kurangi HP target
                bullets.erase(bullets.begin() + i); // Hapus peluru
                i--; // Sesuaikan indeks peluru
                break;
            }
        }
    }

    // Hapus target yang HP-nya <= 0
    for (size_t i = 0; i < targets.size(); i++) {
        if (targets[i].hp <= 0) {
            targets.erase(targets.begin() + i);
            i--;
        }
    }
}

// Gambar kotak kayu sebagai target
void drawTargets() {
    for (size_t i = 0; i < targets.size(); i++) {
        glPushMatrix();
        glTranslatef(targets[i].tx, targets[i].ty, targets[i].tz);
        glColor3f(1.0f, 0.0f, 0.0f); // Warna merah

        glutSolidCube(2.0);
        glPopMatrix();
    }
}

// Struktur untuk menyimpan peluru


void movePlayer(int direction) {
    x += direction * 0.1f;  // Gerak kiri (-1) atau kanan (+1)
}


void drawBullets() {
    glColor3f(1, 1, 0); // Warna kuning
    for (size_t i = 0; i < bullets.size(); i++) {
        glPushMatrix();
        glTranslatef(bullets[i].bx, bullets[i].by, bullets[i].bz);
        glutSolidSphere(0.2, 10, 10);
        glPopMatrix();
        
        // Gerakkan peluru ke arah yang ditembak
        bullets[i].bx += bullets[i].dx;
        bullets[i].bz += bullets[i].dz;
    }
}


void initLighting() {
    GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 5.0f, 5.0f, 5.0f, 1.0f };  

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    
}

 
void Reshape(int w1, int h1)  
{  
  // Fungsi reshape  
  if(h1 == 0) h1 = 1;  
  w = w1;  
  h = h1;  
  ratio = 1.0f * w / h;  
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();  
  glViewport(0, 0, w, h);  
  gluPerspective(45,ratio,0.1,1000);  
  glMatrixMode(GL_MODELVIEW);  
  glLoadIdentity();  
  gluLookAt( 
     x, y, z,  
     x + lx,y + ly,z + lz,  
     0.0f,1.0f,0.0f);  
}  
 
void orientMe(float ang)  
{  
  // Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)  
  lx = sin(ang);  
  lz = -cos(ang);  
  glLoadIdentity();  
  gluLookAt(x, y, z,  
  x + lx,y + ly,z + lz,  
  0.0f,1.0f,0.0f);  
}  
 
void moveMeFlat(int i) {
    // Fungsi ini untuk maju mundur kamera
    x = x + i*(lx)*0.005;
    z = z + i*(lz)*0.005;
    y = y + deltaMoveVertical * 0.005; // Gerakan vertikal
    glLoadIdentity();
    gluLookAt(x, y, z,
              x + lx, y + ly, z + lz,
              0.0f, 1.0f, 0.0f);
}
 
void Grid() {  
  // Fungsi untuk membuat grid di "lantai"  
  double i;  
  const float Z_MIN = -50, Z_MAX = 50;  
  const float X_MIN = -50, X_MAX = 50;  
  const float gap = 1.5;  
  glColor3f(0.5, 0.5, 0.5);  
  glBegin(GL_LINES);  
    for(i=Z_MIN;i<Z_MAX;i+=gap)  
    {  
       glVertex3f(i, 0, Z_MIN);  
       glVertex3f(i, 0, Z_MAX);   
    }  
 
    for(i=X_MIN;i<X_MAX;i+=gap)  
    {  
       glVertex3f(X_MIN, 0, i);  
       glVertex3f(X_MAX, 0, i);  
    }  
  glEnd();  
}  
 
void KotakKayu()  
{  
    // Depan (abu-abu)
    glPushMatrix();
    glTranslatef(0, 0, 3);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f); // Warna putih untuk tekstur
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -3.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, -3.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();

    glPopMatrix();

    // Atas (merah)
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glTranslatef(0, 0, 3);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // Warna merah
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Belakang (hijau)
    glPushMatrix();
    glRotated(-180, 1, 0, 0);
    glTranslatef(0, 0, 3);
    glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f); // Warna hijau
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Bawah (biru)
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslatef(0, 0, 3);
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f); // Warna biru
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Kiri (kuning)
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(0, 0, 3);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // Kanan (ungu)
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(0, 0, 3);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 1.0f); // Warna ungu
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
        glVertex3f(-3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, -3.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 0.0f);
        glVertex3f(-3.0f, 3.0f, 0.0f);
    glEnd();
    glPopMatrix();
}    

void drawCar() {
    // Body mobil (kubus utama)
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Warna biru
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(2.0f, 0.5f, 1.0f); // Skala untuk membuat bentuk mobil
    glutSolidCube(1.0);
    glPopMatrix();

    // Atap mobil (kubus kecil)
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 1.0f); // Warna cyan
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(1.0f, 0.5f, 0.8f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Roda depan kiri
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    glTranslatef(-0.8f, 0.2f, 0.5f);
    glutSolidTorus(0.1, 0.2, 10, 10); // Menggunakan torus untuk roda
    glPopMatrix();

    // Roda depan kanan
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    glTranslatef(0.8f, 0.2f, 0.5f);
    glutSolidTorus(0.1, 0.2, 10, 10);
    glPopMatrix();

    // Roda belakang kiri
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    glTranslatef(-0.8f, 0.2f, -0.5f);
    glutSolidTorus(0.1, 0.2, 10, 10);
    glPopMatrix();

    // Roda belakang kanan
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Warna hitam
    glTranslatef(0.8f, 0.2f, -0.5f);
    glutSolidTorus(0.1, 0.2, 10, 10);
    glPopMatrix();
}
 
 
 
 
void display() {
    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaMoveVertical)
        moveMeFlat(deltaMoveVertical); // Panggil moveMeFlat untuk gerakan vertikal
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Grid();
    drawCar();
    KotakKayu();
    drawBullets();
    glutSwapBuffers();
    glFlush();
}
 
void pressKey(int key, int xx, int yy) {
    // Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas
    switch (key) {
        case GLUT_KEY_LEFT: deltaAngle = -0.0005f; break;
        case GLUT_KEY_RIGHT: deltaAngle = 0.0005f; break;
        case GLUT_KEY_UP: deltaMove = 1; break;
        case GLUT_KEY_DOWN: deltaMove = -1; break;
        case GLUT_KEY_F11: deltaMoveVertical = 1; break; // Gerakan ke atas
        case GLUT_KEY_F12: deltaMoveVertical = -1; break; // Gerakan ke bawah
        case GLUT_KEY_F1: shootBullet(); break;
    }
}

void releaseKey(int key, int xx, int yy) {
    // Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
    switch (key) {
        case GLUT_KEY_LEFT:
            if (deltaAngle < 0.0f) deltaAngle = 0.0f;
            break;
        case GLUT_KEY_RIGHT:
            if (deltaAngle > 0.0f) deltaAngle = 0.0f;
            break;
        case GLUT_KEY_UP:
            if (deltaMove > 0) deltaMove = 0;
            break;
        case GLUT_KEY_DOWN:
            if (deltaMove < 0) deltaMove = 0;
            break;
        case GLUT_KEY_F11:
            if (deltaMoveVertical > 0) deltaMoveVertical = 0; // Berhenti gerakan ke atas
            break;
        case GLUT_KEY_F12:
            if (deltaMoveVertical < 0) deltaMoveVertical = 0; // Berhenti gerakan ke bawah
            break;
    }
}  

 
// Variable untuk pencahayaan  
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };  
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };  
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };  
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
const GLfloat high_shininess[] = { 100.0f };  
 
void lighting(){  
  // Fungsi mengaktifkan pencahayaan  
  glEnable(GL_DEPTH_TEST);  
  glDepthFunc(GL_LESS);  
  glEnable(GL_LIGHT0);  
  glEnable(GL_NORMALIZE);  
  glEnable(GL_COLOR_MATERIAL);  
  glEnable(GL_LIGHTING);  
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);  
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);  
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);  
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);  
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);  
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);  
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);  

  glClearColor(0.1, 0.1, 0.3, 1.0);
}  
 
// void init(void)  
// {  
//   glEnable (GL_DEPTH_TEST);  
//   glEnable(GL_TEXTURE_2D);

//   Image* image = loadBMP("feit.bmp");
//   if (!image) {
//       printf("Gagal memuat tekstur!\n");
//       exit(1);
//   }
//   _textureId = loadTexture(image);
//   delete image;
//   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
// }  
 
int main(int argc, char **argv)  
{  
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  
  glutInitWindowPosition(100,100);  
  glutInitWindowSize(640,480);  
  glutCreateWindow("3D Lighting");  
  glutIgnoreKeyRepeat(1); // Mengabaikan key repeat (saat tombol keyboard dipencet terus)  
  glutSpecialFunc(pressKey); 
  glutSpecialUpFunc(releaseKey);  
  glutDisplayFunc(display);  
  glutIdleFunc(display); // Fungsi display-nya dipanggil terus menerus  
  glutReshapeFunc(Reshape);  
  lighting();  
  initLighting();
  //init();
  createTargets();  
  glutMainLoop();  
  return(0);  
} 