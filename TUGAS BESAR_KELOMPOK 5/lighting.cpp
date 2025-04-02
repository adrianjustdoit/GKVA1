#include <math.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "imageloader.h"  // File header image loader yang sudah ada


enum ViewMode { PERSPECTIVE, TOP, FRONT, SIDE, ISOMETRIC };
ViewMode currentView = PERSPECTIVE;

// Global variables
GLuint buildingTexture;
GLuint windowTexture;
GLuint roofTexture;
float angle = 0.0, angleVertical = 0.0,ratio;
float x = 0.0f, y = 1.75f, z = 15.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float deltaMoveForward = 0, deltaMoveSide = 0, deltaMoveVertical = 0;
int h, w;
int bitmapHeight = 12;


// Movement constants
const float ROTATION_SPEED = 2.0f;
const float MOVE_SPEED = 15.0f;
const float PITCH_LIMIT = 85.0f; // Degrees
const float MOUSE_SENSITIVITY = 0.3f;

// Mouse control
int mouseX = 0, mouseY = 0;
bool mouseCaptured = false;

GLuint groundTexture;

void loadGroundTexture() {
    Image* image = loadBMP("textures/R.bmp");
    glGenTextures(1, &groundTexture);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 
                0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    delete image;
}

void loadTextures() {
    // Memuat tekstur untuk dinding bangunan
    Image* buildingImage = loadBMP("textures/BG.bmp");
    glGenTextures(1, &buildingTexture);
    glBindTexture(GL_TEXTURE_2D, buildingTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, buildingImage->width, buildingImage->height, 
                0, GL_RGB, GL_UNSIGNED_BYTE, buildingImage->pixels);
    delete buildingImage;

    // Memuat tekstur untuk jendela
    Image* windowImage = loadBMP("textures/Win.bmp");
    glGenTextures(1, &windowTexture);
    glBindTexture(GL_TEXTURE_2D, windowTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowImage->width, windowImage->height, 
                0, GL_RGB, GL_UNSIGNED_BYTE, windowImage->pixels);
    delete windowImage;

    // Memuat tekstur untuk atap (opsional)
    Image* roofImage = loadBMP("textures/R.bmp");
    glGenTextures(1, &roofTexture);
    glBindTexture(GL_TEXTURE_2D, roofTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, roofImage->width, roofImage->height, 
                0, GL_RGB, GL_UNSIGNED_BYTE, roofImage->pixels);
    delete roofImage;
}

// Game objects
struct Target {
    float tx, ty, tz;
    int hp;
};

struct Bullet {
    float bx, by, bz;
    float dx, dy, dz;
    float lifetime;
};

std::vector<Target> targets;
std::vector<Bullet> bullets;

void drawCube(float size) {
    glutSolidCube(size);
}

// View setup functions
void setupTopView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 50, 0, 0, 0, 0, 0, 0, -1);
}

void setupFrontView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
}

void setupSideView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(50, 0, 0, 0, 0, 0, 0, 1, 0);
}

void setupIsometricView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(30, 30, 30, 0, 0, 0, 0, 1, 0);
}

void setupPerspectiveView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}
void drawTransformerCharacter() {
    glPushMatrix();

    glTranslatef(0.5f, 1.0f, 0.0f);
    
    // Main body core
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.3f);
    glTranslatef(0.0f, 1.4f, 0.0f);
    glScalef(1.2f, 1.8f, 0.8f);
    glutSolidCube(0.7);
    glPopMatrix();

    // Head
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslatef(0.0f, 2.1f, 0.0f);
    
    // Main head structure
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Faceplate
    glPushMatrix();
    glColor3f(0.1f, 0.5f, 0.9f);
    glTranslatef(0.0f, 0.0f, 0.26f);
    glScalef(0.4f, 0.3f, 0.05f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Crest/horn
    glPushMatrix();
    glColor3f(0.8f, 0.1f, 0.1f);
    glTranslatef(0.0f, 0.35f, 0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.05, 0.4, 10, 10);
    glPopMatrix();
    
    glPopMatrix();

    // Shoulder armor
    glPushMatrix();
    glColor3f(0.8f, 0.1f, 0.1f);
    glTranslatef(-0.7f, 1.7f, 0.0f);
    glScalef(0.8f, 0.5f, 0.6f);
    glutSolidCube(0.7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8f, 0.1f, 0.1f);
    glTranslatef(0.7f, 1.7f, 0.0f);
    glScalef(0.8f, 0.5f, 0.6f);
    glutSolidCube(0.7);
    glPopMatrix();

    // Left Arm
    glPushMatrix();
    glTranslatef(-1.0f, 1.3f, 0.0f);
    
    // Upper arm
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.5f);
    glRotatef(20, 0.0f, 0.0f, 1.0f);
    glScalef(0.3f, 0.9f, 0.4f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Elbow joint
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslatef(-0.15f, -0.45f, 0.0f);
    glutSolidSphere(0.15, 10, 10);
    glPopMatrix();
    
    // Lower arm
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.6f);
    glTranslatef(-0.3f, -0.9f, 0.0f);
    glRotatef(-30, 0.0f, 0.0f, 1.0f);
    glScalef(0.35f, 0.8f, 0.35f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Hand/weapon
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(-0.5f, -1.4f, 0.0f);
    glScalef(0.4f, 0.3f, 0.5f);
    glutSolidCube(0.7);
    
    // Weapon barrel
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(-0.35f, 0.0f, 0.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glutSolidCylinder(0.05, 0.4, 10, 10);
    glPopMatrix();
    
    glPopMatrix();
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glTranslatef(1.0f, 1.3f, 0.0f);
    
    // Upper arm
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.5f);
    glRotatef(-20, 0.0f, 0.0f, 1.0f);
    glScalef(0.3f, 0.9f, 0.4f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Elbow joint
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslatef(0.15f, -0.45f, 0.0f);
    glutSolidSphere(0.15, 10, 10);
    glPopMatrix();
    
    // Lower arm
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.6f);
    glTranslatef(0.3f, -0.9f, 0.0f);
    glRotatef(30, 0.0f, 0.0f, 1.0f);
    glScalef(0.35f, 0.8f, 0.35f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Hand/weapon
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.5f, -1.4f, 0.0f);
    glScalef(0.4f, 0.3f, 0.5f);
    glutSolidCube(0.7);
    
    // Weapon barrel
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.35f, 0.0f, 0.0f);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glutSolidCylinder(0.05, 0.4, 10, 10);
    glPopMatrix();
    
    glPopMatrix();
    glPopMatrix();

    // Legs
    // Left Leg
    glPushMatrix();
    glTranslatef(-0.4f, 0.5f, 0.0f);
    
    // Thigh
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.4f);
    glScalef(0.5f, 0.9f, 0.6f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Knee
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    glutSolidSphere(0.2, 10, 10);
    glPopMatrix();
    
    // Shin
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.5f);
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(0.45f, 0.9f, 0.5f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Foot
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.0f, -1.4f, 0.2f);
    glScalef(0.5f, 0.2f, 0.8f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glTranslatef(0.4f, 0.5f, 0.0f);
    
    // Thigh
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.4f);
    glScalef(0.5f, 0.9f, 0.6f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Knee
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslatef(0.0f, -0.5f, 0.0f);
    glutSolidSphere(0.2, 10, 10);
    glPopMatrix();
    
    // Shin
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.5f);
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(0.45f, 0.9f, 0.5f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Foot
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.0f, -1.4f, 0.2f);
    glScalef(0.5f, 0.2f, 0.8f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    glPopMatrix();

    // Back thrusters/engine
    glPushMatrix();
    glColor3f(0.8f, 0.6f, 0.1f);
    glTranslatef(0.0f, 1.0f, -0.5f);
    glScalef(0.8f, 0.6f, 0.2f);
    glutSolidCube(0.7);
    glPopMatrix();

    glPopMatrix();
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    // Inisialisasi tekstur
    loadTextures();
    
    // Pengaturan material untuk tekstur
    GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void createTargets() {
    // Parameter: x, y, z, hp (jumlah lantai)
    targets.push_back({0, 1.5, -20, 5});  // Gedung tinggi
    targets.push_back({-10, 1.5, -25, 3}); // Gedung sedang
    targets.push_back({10, 1.5, -15, 4});  // Gedung tinggi
    targets.push_back({-5, 1.5, -30, 2});  // Gedung pendek
    targets.push_back({5, 1.5, -10, 6});   // Gedung sangat tinggi
}

void shootBullet() {
    Bullet b;
    b.bx = x;
    b.by = y;
    b.bz = z;
    b.dx = lx * 5.0f;
    b.dy = ly * 5.0f;
    b.dz = lz * 5.0f;
    b.lifetime = 2.0f; // 2 seconds
    bullets.push_back(b);
}

void updateBullets(float deltaTime) {
    for (size_t i = 0; i < bullets.size(); i++) {
        bullets[i].bx += bullets[i].dx * deltaTime;
        bullets[i].by += bullets[i].dy * deltaTime;
        bullets[i].bz += bullets[i].dz * deltaTime;
        bullets[i].lifetime -= deltaTime;
        
        if (bullets[i].lifetime <= 0) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

void checkCollision() {
    for (size_t i = 0; i < bullets.size(); i++) {
        for (size_t j = 0; j < targets.size(); j++) {
            float dx = bullets[i].bx - targets[j].tx;
            float dy = bullets[i].by - targets[j].ty;
            float dz = bullets[i].bz - targets[j].tz;
            float distance = sqrt(dx*dx + dy*dy + dz*dz);
            
            if (distance < 1.5f) {
                targets[j].hp--;
                bullets.erase(bullets.begin() + i);
                i--;
                break;
            }
        }
    }

    for (size_t i = 0; i < targets.size(); i++) {
        if (targets[i].hp <= 0) {
            targets.erase(targets.begin() + i);
            i--;
        }
    }
}

void drawTexturedCube(float width, float height, float depth, float texScale = 1.0f) {
    float w = width/2.0f;
    float h = height/2.0f;
    float d = depth/2.0f;
    
    // Hitung koordinat tekstur berdasarkan skala
    float texW = width * texScale;
    float texH = height * texScale;
    float texD = depth * texScale;
    
    // Sisi depan
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, d);
    glTexCoord2f(texW, 0.0f); glVertex3f(w, -h, d);
    glTexCoord2f(texW, texH); glVertex3f(w, h, d);
    glTexCoord2f(0.0f, texH); glVertex3f(-w, h, d);
    glEnd();
    
    // Sisi belakang
    glBegin(GL_QUADS);
    glTexCoord2f(texW, 0.0f); glVertex3f(-w, -h, -d);
    glTexCoord2f(texW, texH); glVertex3f(-w, h, -d);
    glTexCoord2f(0.0f, texH); glVertex3f(w, h, -d);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(w, -h, -d);
    glEnd();
    
    // Sisi kiri
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, -d);
    glTexCoord2f(texD, 0.0f); glVertex3f(-w, -h, d);
    glTexCoord2f(texD, texH); glVertex3f(-w, h, d);
    glTexCoord2f(0.0f, texH); glVertex3f(-w, h, -d);
    glEnd();
    
    // Sisi kanan
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(w, -h, -d);
    glTexCoord2f(texD, 0.0f); glVertex3f(w, h, -d);
    glTexCoord2f(texD, texH); glVertex3f(w, h, d);
    glTexCoord2f(0.0f, texH); glVertex3f(w, -h, d);
    glEnd();
    
    // Atap
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, h, -d);
    glTexCoord2f(texW, 0.0f); glVertex3f(-w, h, d);
    glTexCoord2f(texW, texD); glVertex3f(w, h, d);
    glTexCoord2f(0.0f, texD); glVertex3f(w, h, -d);
    glEnd();
    
    // Lantai (biasanya tidak terlihat)
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, -d);
    glTexCoord2f(texW, 0.0f); glVertex3f(w, -h, -d);
    glTexCoord2f(texW, texD); glVertex3f(w, -h, d);
    glTexCoord2f(0.0f, texD); glVertex3f(-w, -h, d);
    glEnd();
}

void drawBuilding(float x, float y, float z, float width, float height, float depth, int floors) {
    glPushMatrix();
    glTranslatef(x, y+1.0f, z);
    
    // Aktifkan tekstur dan lighting
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    
    // Gambar badan gedung utama
    glBindTexture(GL_TEXTURE_2D, buildingTexture);
    glPushMatrix();
    glScalef(width, height, depth);
    drawTexturedCube(1.0f, 1.0f, 1.0f, 2.0f); // Scale tekstur 2x
    glPopMatrix();
    
    // Gambar jendela-jendela
    glBindTexture(GL_TEXTURE_2D, windowTexture);
    float windowWidth = width * 0.2f;
    float windowHeight = height * 0.8f / floors;
    float windowSpacing = height * 0.9f / floors;
    
    for (int i = 0; i < floors; i++) {
        glPushMatrix();
        glTranslatef(0.0f, -height/2 + windowSpacing * (i + 0.5f), depth/2 + 0.01f);
        glScalef(width * 0.9f, windowHeight, 0.01f);
        drawTexturedCube(1.0f, 1.0f, 1.0f);
        glPopMatrix();
    }
    
    // Gambar atap
    glBindTexture(GL_TEXTURE_2D, roofTexture);
    glPushMatrix();
    glTranslatef(0.0f, height/2 + 0.1f, 0.0f);
    glScalef(width * 1.2f, 0.2f, depth * 1.2f);
    drawTexturedCube(1.0f, 1.0f, 1.0f, 1.0f);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawTargets() {
    for (size_t i = 0; i < targets.size(); i++) {
        // Ubah dari kubus sederhana menjadi gedung
        drawBuilding(targets[i].tx, targets[i].ty, targets[i].tz, 
                    2.0f, 3.0f + targets[i].hp, 2.0f, targets[i].hp + 1);
    }
}

void drawBullets() {
    glColor3f(1, 1, 0);
    for (size_t i = 0; i < bullets.size(); i++) {
        glPushMatrix();
        glTranslatef(bullets[i].bx, bullets[i].by, bullets[i].bz);
        glutSolidSphere(0.1, 10, 10);
        glPopMatrix();
    }
}

void updateCamera() {
    // Calculate direction vector based on angles
    lx = sin(angle) * cos(angleVertical);
    ly = sin(angleVertical);
    lz = -cos(angle) * cos(angleVertical);
    
    glLoadIdentity();
    gluLookAt(x, y, z, 
              x + lx, y + ly, z + lz,
              0.0f, 1.0f, 0.0f);
}

void moveMe(float deltaTime) {
    // Forward/backward movement
    x += deltaMoveForward * lx * MOVE_SPEED * deltaTime;
    y += deltaMoveForward * ly * MOVE_SPEED * deltaTime;
    z += deltaMoveForward * lz * MOVE_SPEED * deltaTime;
    
    // Side movement (strafe)
    float sideX = -lz;
    float sideZ = lx;
    x += deltaMoveSide * sideX * MOVE_SPEED * deltaTime;
    z += deltaMoveSide * sideZ * MOVE_SPEED * deltaTime;
    
    // Vertical movement
    y += deltaMoveVertical * MOVE_SPEED * deltaTime;
    
    // Keep minimum height
    if (y < 0.5f) y = 0.5f;
    
    updateCamera();
}

void Grid() {
    const float Z_MIN = -100, Z_MAX = 100; // Perbesar area grid
    const float X_MIN = -100, X_MAX = 100;
    const float gap = 5.0; // Lebih besar untuk gedung-gedung besar
    
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for(float i = Z_MIN; i < Z_MAX; i += gap) {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for(float i = X_MIN; i < X_MAX; i += gap) {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

// Variabel global untuk tekstur tanah


void drawTexturedGround() {
    const float SIZE = 100.0f;
    const float REPEAT = 20.0f; // Pengulangan tekstur
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glColor3f(1.0f, 1.0f, 1.0f); // Warna netral untuk tekstur
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-SIZE, 0.0f, -SIZE);
    glTexCoord2f(0.0f, REPEAT); glVertex3f(-SIZE, 0.0f,  SIZE);
    glTexCoord2f(REPEAT, REPEAT); glVertex3f( SIZE, 0.0f,  SIZE);
    glTexCoord2f(REPEAT, 0.0f); glVertex3f( SIZE, 0.0f, -SIZE);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    // Tambahkan grid halus di atas tanah
    glColor4f(0.5f, 0.5f, 0.5f, 0.3f); // Warna grid semi-transparan
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_LINES);
    for(int i = -10; i <= 10; i++) {
        float pos = i * 10.0f;
        glVertex3f(-SIZE, 0.02f, pos);
        glVertex3f( SIZE, 0.02f, pos);
        glVertex3f(pos, 0.02f, -SIZE);
        glVertex3f(pos, 0.02f,  SIZE);
    }
    glEnd();
    
    glDisable(GL_BLEND);
}

const GLfloat light_ambient[] = {0.5f, 0.3f, 0.3f, 1.0f};  // Reduced ambient
const GLfloat light_diffuse[] = {0.9f, 0.8f, 0.8f, 1.0f};  // Reduced diffuse
const GLfloat light_specular[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Reduced specular
const GLfloat light_position[] = {10.0f, 10.0f, 5.0f, 1.0f}; // Light position

const GLfloat mat_ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
const GLfloat mat_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat mat_shininess[] = {20.0f}; // Moderate shininess

void lighting(bool isOrthographic = false) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    
    // Lighting configuration
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Adjust light properties based on view mode
    if(isOrthographic) {
        // Reduced intensity for orthographic view
        GLfloat ortho_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
        GLfloat ortho_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
        GLfloat ortho_specular[] = {0.2f, 0.2f, 0.2f, 1.0f};
        
        glLightfv(GL_LIGHT0, GL_AMBIENT, ortho_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, ortho_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, ortho_specular);
        
        // Position light differently for orthographic view
        GLfloat ortho_position[] = {0.0f, 0.0f, 1.0f, 0.0f}; // Directional light
        glLightfv(GL_LIGHT0, GL_POSITION, ortho_position);
    } else {
        // Standard lighting for perspective view
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        
        GLfloat perspective_position[] = {5.0f, 10.0f, 5.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, perspective_position);
    }
    
    // Material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void display() {

    // Barisan gedung di kejauhan
    for (int i = -8; i <= 8; i++) {
        for (int j = 2; j <= 5; j++) {
            float height = 5.0f + (rand() % 10);
            drawBuilding(i * 10.0f, height/2, -50.0f - j * 15.0f, 
                        4.0f + (rand() % 3), height, 4.0f + (rand() % 3), 
                        (int)(height / 3));
        }
    }
    static int lastTime = glutGet(GLUT_ELAPSED_TIME);
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) * 0.001f; // Convert to seconds
    lastTime = currentTime;

    moveMe(deltaTime);
    updateBullets(deltaTime);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set up lighting
    GLfloat light_position[] = {x + 5.0f, y + 5.0f, z + 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    switch(currentView) {
        case TOP:       
            setupTopView(); 
            lighting(true); // Orthographic view
            break;
        case FRONT:     
            setupFrontView(); 
            lighting(true); // Orthographic view
            break;
        case SIDE:      
            setupSideView(); 
            lighting(true); // Orthographic view
            break;
        case ISOMETRIC: 
            setupIsometricView(); 
            lighting(true); // Orthographic view
            break;
        default:        
            setupPerspectiveView(); 
            lighting(false); // Perspective view
            break;
    }
    
    if(currentView == PERSPECTIVE) Grid();


    
    //Grid();
    drawTexturedGround();
    drawTransformerCharacter();
    drawTargets();
    drawBullets();
    checkCollision();
    
    glutSwapBuffers();
}

void mouseMotion(int mx, int my) {
    if (!mouseCaptured) return;

    int centerX = w / 2;
    int centerY = h / 2;

    // Calculate mouse movement difference
    int deltaX = mx - centerX;
    int deltaY = my - centerY;

    // Update angles based on mouse movement
    angle += deltaX * MOUSE_SENSITIVITY * 0.001f;
    angleVertical -= deltaY * MOUSE_SENSITIVITY * 0.001f;

    // Limit vertical rotation
    if (angleVertical > PITCH_LIMIT * 0.0174533f)
        angleVertical = PITCH_LIMIT * 0.0174533f;
    if (angleVertical < -PITCH_LIMIT * 0.0174533f)
        angleVertical = -PITCH_LIMIT * 0.0174533f;

    // Move mouse back to center
    glutWarpPointer(centerX, centerY);

    updateCamera();
    glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseCaptured = true;
        glutSetCursor(GLUT_CURSOR_NONE);
        glutWarpPointer(w/2, h/2);
    }
}

void keyboard(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w': deltaMoveForward = 1.0f; break;
        case 's': deltaMoveForward = -1.0f; break;
        case 'a': deltaMoveSide = -1.0f; break;
        case 'd': deltaMoveSide = 1.0f; break;
        case 'q': deltaMoveVertical = -1.0f; break;
        case 'e': deltaMoveVertical = 1.0f; break;
        case ' ': shootBullet(); break;
        case '1': currentView = PERSPECTIVE; break;
        case '2': currentView = TOP; break;
        case '3': currentView = FRONT; break;
        case '4': currentView = SIDE; break;
        case '5': currentView = ISOMETRIC; break;
        case 27: // ESC key
            mouseCaptured = false;
            glutSetCursor(GLUT_CURSOR_INHERIT);
            exit(0); 
            break;
    }
}

void keyboardUp(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'w': 
        case 's': deltaMoveForward = 0.0f; break;
        case 'a': 
        case 'd': deltaMoveSide = 0.0f; break;
        case 'q':
        case 'e': deltaMoveVertical = 0.0f; break;
    }
}

void Reshape(int w1, int h1) {
    if (h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, ratio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    
    if (mouseCaptured) {
        glutWarpPointer(w/2, h/2);
    }
    
    updateCamera();
}





int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Transformer Game - Smooth Camera");
    
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMotion);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(Reshape);
    
    //lighting();
    initRendering();
    createTargets();
    
    // Hide cursor and capture mouse
    mouseCaptured = true;
    glutSetCursor(GLUT_CURSOR_NONE);
    
    glutMainLoop();
    return 0;
}