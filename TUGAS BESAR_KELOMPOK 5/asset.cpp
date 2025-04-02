void drawCube(float size) {
    glutSolidCube(size);
}

void drawTransformerCharacter() {
    glPushMatrix();
    
    // Main body core
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.3f); // Dark metallic blue
    glTranslatef(0.0f, 1.4f, 0.0f);
    glScalef(1.2f, 1.8f, 0.8f);
    glutSolidCube(0.7);
    glPopMatrix();

    // Head - Angular transformer design
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // Metallic silver
    glTranslatef(0.0f, 2.1f, 0.0f);
    
    // Main head structure
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Faceplate
    glPushMatrix();
    glColor3f(0.1f, 0.5f, 0.9f); // Blue visor
    glTranslatef(0.0f, 0.0f, 0.26f);
    glScalef(0.4f, 0.3f, 0.05f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Crest/horn
    glPushMatrix();
    glColor3f(0.8f, 0.1f, 0.1f); // Red
    glTranslatef(0.0f, 0.35f, 0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.05, 0.4, 10, 10);
    glPopMatrix();
    
    glPopMatrix();

    // Shoulder armor
    glPushMatrix();
    glColor3f(0.8f, 0.1f, 0.1f); // Red
    glTranslatef(-0.7f, 1.7f, 0.0f);
    // glRotatef(45, 0.0f, 0.0f, 1.0f);
    glScalef(0.8f, 0.5f, 0.6f);
    glutSolidCube(0.7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.8f, 0.1f, 0.1f); // Red
    glTranslatef(0.7f, 1.7f, 0.0f);
    // glRotatef(-45, 0.0f, 0.0f, 1.0f);
    glScalef(0.8f, 0.5f, 0.6f);
    glutSolidCube(0.7);
    glPopMatrix();

    // Left Arm - Mechanical with armor
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

    // Right Arm - Similar but with different pose
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

    // Legs - Heavy armored
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
    glColor3f(0.8f, 0.6f, 0.1f); // Gold/yellow
    glTranslatef(0.0f, 1.0f, -0.5f);
    glScalef(0.8f, 0.6f, 0.2f);
    glutSolidCube(0.7);
    glPopMatrix();

    glPopMatrix();
}

void drawRoboticHumanoid() {
    glPushMatrix();
    
    // Head - More robotic design
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // Metallic color
    glTranslatef(0.0f, 1.8f, 0.0f);
    
    // Main head structure
    glPushMatrix();
    glScalef(0.5f, 0.6f, 0.5f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Visor/eyes
    glPushMatrix();
    glColor3f(0.1f, 0.3f, 0.8f); // Blue visor
    glTranslatef(0.0f, 0.0f, 0.31f);
    glScalef(0.4f, 0.2f, 0.05f);
    glutSolidCube(0.6);
    glPopMatrix();
    
    // Antenna
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.0f, 0.4f, 0.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glutSolidCylinder(0.02, 0.3, 10, 10);
    glPopMatrix();
    
    glPopMatrix();

    // Neck
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, 1.5f, 0.0f);
    glScalef(0.2f, 0.2f, 0.2f);
    glutSolidCube(0.7);
    glPopMatrix();

    // Torso - More detailed robotic torso
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.8f); // Blue metallic
    glTranslatef(0.0f, 1.2f, 0.0f);
    
    // Main torso
    glPushMatrix();
    glScalef(1.0f, 1.5f, 0.6f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Chest plate/details
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.6f);
    glTranslatef(0.0f, 1.3f, 0.35f);
    glScalef(0.7f, 0.8f, 0.1f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    glPopMatrix();

    // Left Arm - Articulated robotic arm
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslatef(-0.6f, 1.3f, 0.0f);
    
    // Upper arm
    glPushMatrix();
    glRotatef(15, 0.0f, 0.0f, 1.0f);
    glScalef(0.25f, 0.8f, 0.25f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Elbow joint
    glPushMatrix();
    glTranslatef(-0.1f, -0.35f, 0.0f);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
    
    // Lower arm
    glPushMatrix();
    glTranslatef(-0.2f, -0.7f, 0.0f);
    glScalef(0.25f, 0.7f, 0.25f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Hand
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(-0.2f, -1.05f, 0.0f);
    glutSolidSphere(0.15, 10, 10);
    glPopMatrix();
    
    glPopMatrix();

    // Right Arm - Mirror of left arm with slight variation
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glTranslatef(0.6f, 1.3f, 0.0f);
    
    // Upper arm
    glPushMatrix();
    glRotatef(-15, 0.0f, 0.0f, 1.0f);
    glScalef(0.25f, 0.8f, 0.25f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Elbow joint
    glPushMatrix();
    glTranslatef(0.1f, -0.35f, 0.0f);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();
    
    // Lower arm
    glPushMatrix();
    glTranslatef(0.2f, -0.7f, 0.0f);
    glScalef(0.25f, 0.7f, 0.25f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Hand
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(0.2f, -1.05f, 0.0f);
    glutSolidSphere(0.15, 10, 10);
    glPopMatrix();
    
    glPopMatrix();

    // Left Leg - Articulated robotic leg
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glTranslatef(-0.25f, 0.5f, 0.0f);
    
    // Upper leg
    glPushMatrix();
    glScalef(0.3f, 0.8f, 0.3f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Knee joint
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    glutSolidSphere(0.12, 10, 10);
    glPopMatrix();
    
    // Lower leg
    glPushMatrix();
    glTranslatef(0.0f, -0.8f, 0.0f);
    glScalef(0.3f, 0.8f, 0.3f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Foot
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.0f, -1.1f, 0.15f);
    glScalef(0.35f, 0.15f, 0.7f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    glPopMatrix();

    // Right Leg - Mirror of left leg
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glTranslatef(0.25f, 0.5f, 0.0f);
    
    // Upper leg
    glPushMatrix();
    glScalef(0.3f, 0.8f, 0.3f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Knee joint
    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    glutSolidSphere(0.12, 10, 10);
    glPopMatrix();
    
    // Lower leg
    glPushMatrix();
    glTranslatef(0.0f, -0.8f, 0.0f);
    glScalef(0.3f, 0.8f, 0.3f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    // Foot
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glTranslatef(0.0f, -1.1f, 0.15f);
    glScalef(0.35f, 0.15f, 0.7f);
    glutSolidCube(0.7);
    glPopMatrix();
    
    glPopMatrix();

    // Backpack/energy unit
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.0f, 1.2f, -0.4f);
    glScalef(0.8f, 1.0f, 0.3f);
    glutSolidCube(0.7);
    glPopMatrix();

    glPopMatrix();
}

// Function to draw a Roblox-like character
void drawRobloxCharacter() {
    glPushMatrix();
    
    // Head
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.6f); // Skin tone
    glTranslatef(0.0f, 1.8f, 0.0f);
    drawCube(0.6);
    glPopMatrix();

    // Torso
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Blue Shirt
    glTranslatef(0.0f, 1.2f, 0.0f);
    glScalef(1.0f, 1.5f, 0.5f);
    drawCube(0.7);
    glPopMatrix();

    // Left Arm
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.6f); // Skin tone
    glTranslatef(-0.6f, 1.3f, 0.0f);
    glScalef(0.3f, 1.0f, 0.3f);
    drawCube(0.7);
    glPopMatrix();

    // Right Arm
    glPushMatrix();
    glColor3f(1.0f, 0.8f, 0.6f); // Skin tone
    glTranslatef(0.6f, 1.3f, 0.0f);
    glScalef(0.3f, 1.0f, 0.3f);
    drawCube(0.7);
    glPopMatrix();

    // Left Leg
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Black Pants
    glTranslatef(-0.3f, 0.5f, 0.0f);
    glScalef(0.4f, 1.2f, 0.4f);
    drawCube(0.7);
    glPopMatrix();

    // Right Leg
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Black Pants
    glTranslatef(0.3f, 0.5f, 0.0f);
    glScalef(0.4f, 1.2f, 0.4f);
    drawCube(0.7);
    glPopMatrix();

    glPopMatrix();
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