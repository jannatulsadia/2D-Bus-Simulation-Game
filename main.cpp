#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>





//..... Scenario 1 and 2.....
const float PI = 3.1416f;

void drawCircle(float cx, float cy, float r) {
    int num_segments = 200;
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawSemiCircleFromPoints(float x1, float y1, float x2, float y2, int up) {
    float cx = (x1 + x2) / 2.0f;
    float cy = (y1 + y2) / 2.0f;
    float dx = (x2 - x1);
    float dy = (y2 - y1);
    float r = sqrt(dx*dx + dy*dy) / 2.0f;

    int num_segments = 200;
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    for (int i = 0; i <= num_segments; i++) {
        float theta = up ? PI * i / num_segments : -PI * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glVertex2f(x2, y2);
    glEnd();
}


// Scenario 1 variables
int currentScenario = 1;
bool isDay = true;
bool rainOn = false;
float rainX[200], rainY[200];
float X = 35.0f;
float Y = -35.0f;
float truckSpeed = -2.0f;
float BusSpeed = 2.0f;
float balloonOffset = 0.0f;
float balloonSpeed = 0.05f;
float balloonAngle = 0.0f;
float starX[50], starY[50];
int starsInitialized = 0;
float cloudX = -30.0f;
float cloudSpeed = 0.15f;


// Function declarations Scenario 1
void drawCircle(float cx, float cy, float r);
void drawSemiCircleFromPoints(float x1, float y1, float x2, float y2, int up);
void drawRain();
void drawMoon(float cx, float cy, float r);
void drawStars();
void drawSun(float cx, float cy, float r);
void drawCloud();
void house1();
void house2();
void palace();
void window1(float tx, float ty, float s);
void window2(float tx, float ty, float s);
void door();
void tree1();
void tree2();
void tree2_translated(float dx, float dy, float scale);
void airbln();
void road();
void drawBench(float dx, float dy, float scale);
void NdrawLampPost(float x, float y, float scale);
void drawLampPost(float x, float y, float scale);
void bus();
void truck();


// Scenario 1 functions
void drawRain() {     // Rain
    if (!rainOn) return;

    glColor3ub(173, 216, 230);
    glBegin(GL_LINES);
    for (int i = 0; i < 200; i++) {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i], rainY[i] - 0.5f);
    }
    glEnd();
}
void updateRain(int value) {   //rainupdate
    if (currentScenario == 1 && rainOn) {
        for (int i = 0; i < 200; i++) {
            rainY[i] -= 0.5f;
            if (rainY[i] < -20) {
                rainY[i] = 25 + (rand() % 10);
                rainX[i] = (rand() % 60) - 30;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, updateRain, 0);
}
void updateTruck(int value) {    //truckupdate
    if(currentScenario == 1){X += truckSpeed;
    if (X < -60.0f) {
        X = 35.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(40, updateTruck, 0);
}
void updateBus(int value) {   //busupdate
    if(currentScenario == 1){Y += BusSpeed;
    if (Y > 60.0f) {
        Y = -35.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(40, updateBus, 0);
}
void updateBalloon(int value) {    //balloonupdate
    if(currentScenario == 1){balloonAngle += balloonSpeed;
    if (balloonAngle > 360) balloonAngle -= 360;

    balloonOffset = sin(balloonAngle) * 0.5f; // up-down floating range
    }
    glutPostRedisplay();
    glutTimerFunc(30, updateBalloon, 0);
}

void updateCloud(int value) {   //cloudypdate
   if(currentScenario == 1) {cloudX += cloudSpeed;
    if (cloudX > 55.0f) {
        cloudX = -55.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(2, updateCloud, 0);
}

void drawMoon(float cx, float cy, float r) {    //Moon1
    glColor3ub(245, 245, 245);
    drawCircle(cx, cy, r);
    glColor3ub(0, 0, 31);
    drawCircle(cx + r*0.3, cy + r*0.1, r);
}
void drawStars() {
    glColor3ub(255, 255, 255);

    // First time e random position generate hobe
    if (!starsInitialized) {
        for (int i = 0; i < 50; i++) {
            starX[i] = (rand() % 60) - 30;  // X position
            starY[i] = (rand() % 30);       // Y position
        }
        starsInitialized = 1;
    }

    // Protibar draw er age position update
    for (int i = 0; i < 50; i++) {     //starsupdate
        starX[i] += 0.02f;

        if (starX[i] > 30) {
            starX[i] = -30;
        }

        drawCircle(starX[i], starY[i], 0.1f);
    }
}

void drawSun(float cx, float cy, float r) {
    glColor3ub(255, 223, 0);
drawCircle(6.2870056371028f, 20.2203980429496f, 3.0178f);  //Sun1

}
void drawCloud() {
      glPushMatrix();
    glTranslatef(cloudX, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.9f);


    drawSemiCircleFromPoints(-24.388065470175f, 12.0581338439182f, -20.1378653661904f, 12.0581338439182f, 1);

    drawSemiCircleFromPoints(-21.1379f, 12.0581338439182f, -15.0f, 12.0581338439182f, 1);   //Cloud1


    drawSemiCircleFromPoints(-15.5840795404926, 12.0581338439182f, -12.2803f, 12.0581338439182f, 1);


    drawSemiCircleFromPoints(-2.3426943662929, 17.0810704184903f, 1.0282607121504768f, 17.0810704184903f, 1);
    drawSemiCircleFromPoints(0.2940501994941f, 17.0810704184903f, 5.2648534447696f, 17.0810704184903f, 1);   //Cloud2
    drawSemiCircleFromPoints(4.8324000753782, 17.0810704184903f, 7.454148627314f, 17.0810704184903f, 1);


    drawSemiCircleFromPoints(-5.7226566168046, 6.9661166948243f, -1.302210412302, 6.9661166948243f, 1);
    drawSemiCircleFromPoints(-2.3137434923944f, 6.9661166948243f, 4.3726730387702f, 6.9661166948243f, 1);   //Cloud3
    drawSemiCircleFromPoints(3.8311674746265, 6.9661166948243f, 7.2450069007493f, 6.9661166948243f, 1);



    drawSemiCircleFromPoints(13.6652907930116f, 9.0f, 20.0f, 9.0f, 1);   //Cloud4
    drawSemiCircleFromPoints(19.3938992451019f, 9.0f, 23.0f, 9.0f, 1);

      glPopMatrix();
}



void house1(){   //House1
   glColor3ub(188, 166, 97);
      glBegin(GL_POLYGON);
glVertex2f(20.2674359636246f, 8.2203286421709f); //
glVertex2f(25.7948042364866f, 8.2203286421709f); //
glVertex2f(28.6133577034712f, 8.2203286421709f); //
glVertex2f(30.0f, 8.2203286421709f); //
glVertex2f(30.0f, -15.7f); //
glVertex2f(20.2674359636246f, -15.7f); //

    glEnd();
 glBegin(GL_POLYGON);
glVertex2f(25.7948042364866f, 8.2203286421709f); //
glVertex2f(25.7948042364866f, 10.3160728993668f);  //
glVertex2f(28.6133577034712f, 10.3160728993668f); //
glVertex2f(28.6133577034712f, 8.2203286421709f); //

    glEnd();

    glColor3ub(255, 255, 255);
    for (int k = 0; k < 5; k++) {
        float dy = k * 4.0f;

        glBegin(GL_POLYGON);
            glVertex2f(22.7781476126662f, 5.0821029178658f - dy); // G2
            glVertex2f(24.2274971165723f, 5.0918991502719f - dy); // H2
            glVertex2f(24.2274971165723f, 3.0134466913368f - dy); // I2
            glVertex2f(22.7781476126662f, 3.0134466913368f - dy); // J2
        glEnd();
    }

    glColor3ub(255, 255, 255);
    for (int k = 0; k < 5; k++) {
        float dy = k * 4.0f;

        glBegin(GL_POLYGON);
            glVertex2f(26.0986153867044f, 5.0918991502719f - dy); //
            glVertex2f(27.6858385145104f, 5.0918991502719f - dy); //
            glVertex2f(27.6858385145104f, 3.0134466913368f - dy); //
            glVertex2f(26.0986153867044f, 3.0134466913368f - dy); //
        glEnd();
    }

}



void house2() {    //House2
 glColor3ub(122, 110, 59);
      glBegin(GL_POLYGON);
glVertex2f(-29.2624050747698f, 8.5951218164833f); //
glVertex2f(-19.9141980503709f, 8.6003233321066f); //
glVertex2f(-19.9141980503709f, -15.7f);  //
glVertex2f(-29.2624050747698f, -15.7f); //

    glEnd();
glColor3ub(255, 255, 255);
    for (int k = 0; k < 4; k++) {
        float dy = k * 5.0f;

        glBegin(GL_POLYGON);
            glVertex2f(-27.3760051395931f, 6.8238351530984f - dy); //
            glVertex2f(-25.5373563379857f, 6.8238351530984f - dy); //
            glVertex2f(-25.5373563379857f, 3.8347239822795f - dy); //
            glVertex2f(-27.3760051395931f, 3.8347239822795f - dy); //
        glEnd();
    }

     for (int k = 0; k < 4; k++) {
        float dy = k * 5.0f;

        glBegin(GL_POLYGON);
            glVertex2f(-23.8702692169538f, 6.8238351530984f - dy);
            glVertex2f(-21.5943915495547f, 6.8238351530984f - dy);
            glVertex2f(-21.5943915495547f, 3.8347239822795f - dy);
            glVertex2f(-23.8702692169538f, 3.8347239822795f - dy);
        glEnd();
    }
}





void palace() {    //Palace



   glColor3ub(179, 151, 139);
    glBegin(GL_POLYGON);
    glVertex2f(-8.0271163642131f,  3.4817070480259f);
    glVertex2f( 7.7841617586916f,  3.4817070480259f);
    glVertex2f( 7.7841617586916f, -14.7765445284154f);
    glVertex2f(-8.0271163642131f, -14.7765445284154f);
glEnd();

for (int i = 0; i < 6; i++) {
    float dx = i * 2.79f;


    glColor3ub(126, 103, 98);
    glBegin(GL_POLYGON);
        glVertex2f(-7.9960828512374f + dx, 5.4580594617819f);   // V5
        glVertex2f(-6.0974715515353f + dx, 5.4599190071244f);   // W5
        glVertex2f(-6.1000000000000f + dx, 3.5000000000000f);   // Z5
        glVertex2f(-8.0271163642131f + dx, 3.4817070480259f);
    glEnd();


    glColor3ub(179, 151, 139);
    glBegin(GL_POLYGON);
        glVertex2f(-8.0041998817170f + dx, 5.2180863652730f);    // A6
        glVertex2f(-6.3073594563530f + dx, 5.2244357869794f);   // B6
        glVertex2f(-6.3073594563530f + dx, 3.5000000000000f);   // C6
        glVertex2f(-8.0271163642131f + dx, 3.4817070480259f);
    glEnd();
}
    glColor3ub(126, 103, 98);
    glBegin(GL_POLYGON);
glVertex2f(-7.4949445367924f, 2.5401296687700f); // K6
glVertex2f(6.7892258244041f, 2.5355883612327f);  // L6
glVertex2f(6.8041963449530f, 2.2137221694342f);  // M6
glVertex2f(-7.5210601650649f, 2.1794841816492f); // N6

    glEnd();

   glColor3ub(230, 210, 202);
glBegin(GL_POLYGON);
    glVertex2f(-8.0421531413157f, 2.3045473539938f);  // D6
    glVertex2f( 7.3133029400450f, 2.3064434114504f);  // E6
    glVertex2f( 7.3133029400450f, 1.7443023598587f);  // F6
    glVertex2f(-8.0413612244495f, 1.7471312691955f);  // G6
glEnd();


for (int row = 0; row < 2; row++) {
    float dy = row * -5.0f;
   glColor3ub(230, 210, 202);
glBegin(GL_POLYGON);
glVertex2f(-8.0504567235002f, -1.7198600137827f + dy); // O6
glVertex2f(7.3140359048354f, -1.7178506203486f + dy);  // P6
glVertex2f(7.3169196511191f, -1.9543178156105f + dy);  // Q6
glVertex2f(-8.0497139508201f, -1.9610064111556f + dy); // R6
glEnd();


for (int i = 0; i < 31; i++) {
    float dx = i * 0.5050f;
   glColor3ub(230, 210, 202);
glBegin(GL_POLYGON);
glVertex2f(-8.0526480313182f + dx, -1.5016148437820f + dy); // S6
glVertex2f(-7.8101829575522f + dx, -1.5016148437820f + dy); // T6
glVertex2f(-7.8097009196322f + dx, -1.7151576423456f + dy);
glVertex2f(-8.0504567235002f + dx, -1.7198600137827f + dy);

glEnd();
}
}

glColor3ub(230, 210, 202);
for (int i = 0; i < 14; i++) {
    float dx = i * 01.130f;

    glBegin(GL_POLYGON);
        glVertex2f(-8.0505659172679f + dx, 2.8083668161245f); // G6
        glVertex2f(-7.3810452503643f + dx, 2.8192239080202f); // H6
        glVertex2f(-7.3792357350483f + dx, 2.3306547727159f); //
        glVertex2f(-8.0421531413157f + dx, 2.3045473539938f); //
    glEnd();
}




    float dx_offset;

    for (int side = 0; side < 2; side++) {
        dx_offset = side * 23.90f;


        for (int i = 0; i < 5; i++) {
            float dx = i * 2.350f + dx_offset;
            glColor3ub(126, 103, 98);
            glBegin(GL_POLYGON);
                glVertex2f(-17.4825039904767f + dx, 12.3768352401587f);
                glVertex2f(-16.1643897597121f + dx, 12.3768352401587f);
                glVertex2f(-16.1643897597121f + dx, 11.1662368584650f);
                glVertex2f(-17.4766208440358f + dx, 11.1662368584650f);
            glEnd();

            glColor3ub(179, 151, 139);
            glBegin(GL_POLYGON);
                glVertex2f(-17.4784739767338f + dx, 12.2222220225777f);
                glVertex2f(-16.2994635010350f + dx, 12.2190928770358f);
                glVertex2f(-16.2963361522931f + dx, 11.1213934686352f);
                glVertex2f(-17.4753466279919f + dx, 11.0995020274420f);
            glEnd();
        }


        glColor3ub(179, 151, 139);
        glBegin(GL_POLYGON);
            glVertex2f(-17.4766208440358f + dx_offset, 11.166236858465f);
            glVertex2f(-6.672269918595f + dx_offset, 11.166236858465f);
            glVertex2f(-6.6959076488449f + dx_offset, 9.7352784248236f);
            glVertex2f(-17.4825039904767f + dx_offset, 9.7352784248236f);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(-16.1056f + dx_offset, -14.7765f);
            glVertex2f(-16.1056f + dx_offset,  9.1424f);
            glVertex2f(-8.0271f + dx_offset,  9.1424f);
            glVertex2f(-8.0271f + dx_offset, -14.7765f);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(-17.4825039904767f + dx_offset, 9.7352784248236f);
            glVertex2f(-6.6959076488449f + dx_offset, 9.7352784248236f);
            glVertex2f(-8.0271163642131f + dx_offset, 9.1423966379571f);
            glVertex2f(-16.1055818350224f + dx_offset, 9.1423966379571f);
        glEnd();

        glColor3ub(230, 210, 202);
        glBegin(GL_POLYGON);
            glVertex2f(-17.4825039904767f + dx_offset, 10.3055461146071f);
            glVertex2f(-6.6959076488449f + dx_offset, 10.3055461146071f);
            glVertex2f(-6.6959076488449f + dx_offset, 9.7352784248236f);
            glVertex2f(-17.4825039904767f + dx_offset, 9.7352784248236f);
        glEnd();


        for (int i = 0; i < 12; i++) {
            float dx = i * 0.940f + dx_offset;

            glColor3ub(136, 122, 16);
            glBegin(GL_POLYGON);
                glVertex2f(-17.4779024591767f + dx, 10.2810600566247f);
                glVertex2f(-17.4969203364241f + dx, 10.7755248650540f);
                glVertex2f(-17.0353045886911f + dx, 10.7737959671224f);
                glVertex2f(-17.0249312011016f + dx, 10.2948912400772f);
            glEnd();

            glColor3ub(230, 210, 202);
            glBegin(GL_POLYGON);
                glVertex2f(-17.4917336426294f + dx, 10.6856221726123f);
                glVertex2f(-17.1182916894071f + dx, 10.6925377643386f);
                glVertex2f(-17.1131049956124f + dx, 10.2983490359404f);
                glVertex2f(-17.4779024591767f + dx, 10.2810600566247f);
            glEnd();
        }

        glColor3ub(113, 93, 88);
        glBegin(GL_POLYGON);
            glVertex2f(-16.1055818350224f + dx_offset,  9.1423966379571f);
            glVertex2f(-8.0271163642131f + dx_offset,   9.1423966379571f);
            glVertex2f(-8.0464202313457f + dx_offset,   8.6798119613416f);
            glVertex2f(-16.1155379769146f + dx_offset,  8.6688879993467f);
        glEnd();

        glColor3ub(113, 93, 88);
        glBegin(GL_POLYGON);
            glVertex2f(-15.6449077159202f + dx_offset,  8.6750711737968f);
            glVertex2f(-15.2487068540256f + dx_offset,  8.6839946166322f);
            glVertex2f(-15.2385000091188f + dx_offset, -14.9687638815836f);
            glVertex2f(-15.8004283786805f + dx_offset, -14.9349127749838f);
        glEnd();

        for (int i = 0; i < 34; i++) {
            float dy = i * -0.7f;

            glColor3ub(113, 93, 88);
            glBegin(GL_POLYGON);
                glVertex2f(-16.1048049480296f + dx_offset, 8.4165153750396f + dy);
                glVertex2f(-16.0428946217140f + dx_offset, 8.5126525971728f + dy);
                glVertex2f(-15.5146086193641f + dx_offset, 8.5405434730730f + dy);
                glVertex2f(-15.5674232431019f + dx_offset, 8.0493450698656f + dy);
                glVertex2f(-16.1000000000000f + dx_offset, 8.1000000000000f + dy);
            glEnd();

            glColor3ub(157, 128, 121);
            glBegin(GL_POLYGON);
                glVertex2f(-16.0428946217140f + dx_offset, 8.5126525971728f + dy);
                glVertex2f(-15.5146086193641f + dx_offset, 8.5405434730730f + dy);
                glVertex2f(-15.5490620543000f + dx_offset, 8.1878059249229f + dy);
                glVertex2f(-16.0396133421963f + dx_offset, 8.2091342417878f + dy);
            glEnd();
        }

        glColor3ub(113, 93, 88);
        glBegin(GL_POLYGON);
            glVertex2f(-9.1858090722583f + dx_offset, 8.6891794340196f);
            glVertex2f(-8.7797717406180f + dx_offset, 8.6905809182058f);
            glVertex2f(-8.6205963217369f + dx_offset, -14.8807927650765f);
            glVertex2f(-9.1534940149376f + dx_offset, -14.8630295086367f);
        glEnd();

        for (int i = 0; i < 34; i++) {
            float dy = i * -0.7f;

            glColor3ub(113, 93, 88);
            glBegin(GL_POLYGON);
                glVertex2f(-8.9028614171028f + dx_offset, 8.5326399056582f + dy);
                glVertex2f(-8.3635427177365f + dx_offset, 8.4993486279198f + dy);
                glVertex2f(-8.2969601622592f + dx_offset, 8.4083524687682f + dy);
                glVertex2f(-8.3036184178070f + dx_offset, 8.1220474802179f + dy);
                glVertex2f(-8.8518147912369f + dx_offset, 8.0532455062252f + dy);
            glEnd();

            glColor3ub(157, 128, 121);
            glBegin(GL_POLYGON);
                glVertex2f(-8.9028614171028f + dx_offset, 8.5326399056582f + dy);
                glVertex2f(-8.3635427177365f + dx_offset, 8.4993486279198f + dy);
                glVertex2f(-8.3635427177365f + dx_offset, 8.2130436393695f + dy);
                glVertex2f(-8.8606924653006f + dx_offset, 8.1841911986629f + dy);
            glEnd();
        }


        glColor3ub(157, 128, 121);
        glBegin(GL_POLYGON);
            glVertex2f(-9.4128888960408f + dx_offset,  8.6715974498580f);
            glVertex2f(-9.1767697014406f + dx_offset,  8.6773564497321f);
            glVertex2f(-9.1770939291912f + dx_offset, -14.7578383927052f);
            glVertex2f(-9.4182321794536f + dx_offset, -14.7578383927052f);
        glEnd();


        glBegin(GL_POLYGON);
            glVertex2f(-15.2514156319079f + dx_offset,  8.6707346791925f);
            glVertex2f(-15.0179765985672f + dx_offset,  8.6747496011418f);
            glVertex2f(-14.9872175154329f + dx_offset, -15.0807448605655f);
            glVertex2f(-15.2256885088584f + dx_offset, -15.0906811519581f);
        glEnd();

        for (int row = 0; row < 3; row++) {
            float dy = row * -5.30f;

            glColor3ub(230, 210, 202);
            glBegin(GL_POLYGON);
                glVertex2f(-15.0543460687325f + dx_offset, 4.4530640858590f + dy);
                glVertex2f(-9.3811561027550f + dx_offset, 4.4591401408216f + dy);
                glVertex2f(-9.3790515368953f + dx_offset, 4.1974724522724f + dy);
                glVertex2f(-15.0537342771379f + dx_offset, 4.1983151370690f + dy);
            glEnd();

            for (int i = 0; i < 12; i++) {
                float dx = i * 0.49f + dx_offset;

                glColor3ub(230, 210, 202);
                glBegin(GL_POLYGON);
                    glVertex2f(-15.0598441279078f + dx, 4.6961046053677f + dy);
                    glVertex2f(-14.8259884068121f + dx, 4.7009513560640f + dy);
                    glVertex2f(-14.8332585328565f + dx, 4.4598255089257f + dy);
                    glVertex2f(-15.0598441279078f + dx, 4.4537670705540f + dy);
                glEnd();
            }
        }
    }



}


void v2f(float x, float y, float tx, float ty, float s) {
    glVertex2f(tx + x * s, ty + y * s);
}
void window1(float tx, float ty, float s) {
    glColor3ub(230, 210, 202);
    drawSemiCircleFromPoints(tx + (-12.8362505f * s), ty + (7.4752202f * s),
                             tx + (-11.8308874f * s), ty + (7.4709960f * s), 1);

    glBegin(GL_POLYGON);
        v2f(-12.8362505f, 7.4752202f, tx, ty, s);
        v2f(-11.8308874f, 7.4709960f, tx, ty, s);
        v2f(-11.8308874f, 5.1223327f, tx, ty, s);
        v2f(-12.8362505f, 5.1223327f, tx, ty, s);
    glEnd();

    glColor3ub(157, 128, 121);
    drawSemiCircleFromPoints(tx + (-12.7505272f * s), ty + (7.4312371f * s),
                             tx + (-11.9241905f * s), ty + (7.4875270f * s), 1);

    glBegin(GL_POLYGON);
        v2f(-12.7505272f, 7.4312371f, tx, ty, s);
        v2f(-11.9241905f, 7.4875270f, tx, ty, s);
        v2f(-11.9249933f, 5.2744680f, tx, ty, s);
        v2f(-12.7487669f, 5.2723878f, tx, ty, s);
    glEnd();

    glColor3ub(230, 210, 202);
    glBegin(GL_POLYGON);
        v2f(-12.7728521f, 7.4957794f, tx, ty, s);
        v2f(-11.8810375f, 7.5071785f, tx, ty, s);
        v2f(-11.8696385f, 7.3561415f, tx, ty, s);
        v2f(-12.7801349f, 7.3604161f, tx, ty, s);
    glEnd();
}



void window2(float tx, float ty, float s) {
    glColor3ub(230, 210, 202);
    drawSemiCircleFromPoints(tx + (-14.2377965f * s), ty + (3.0899985f * s),
                             tx + (-12.8611779f * s), ty + (3.0856144f * s), 1);

    glBegin(GL_POLYGON);
        v2f(-14.2377965f, 3.0899985f, tx, ty, s);
        v2f(-12.8611779f, 3.0856144f, tx, ty, s);
        v2f(-12.8611779f, 1.1039852f, tx, ty, s);
        v2f(-14.2377965f, 1.1039852f, tx, ty, s);
    glEnd();

    glColor3ub(157, 128, 121);
    drawSemiCircleFromPoints(tx + (-14.1238089f * s), ty + (3.0856144f * s),
                             tx + (-12.9707813f * s), ty + (3.1119192f * s), 1);

    glBegin(GL_POLYGON);
        v2f(-14.1238089f, 3.0856144f, tx, ty, s);
        v2f(-12.9707813f, 3.1119192f, tx, ty, s);
        v2f(-12.9707813f, 1.2223568f, tx, ty, s);
        v2f(-14.1238089f, 1.2223568f, tx, ty, s);
    glEnd();

    glColor3ub(210, 180, 160);
    glBegin(GL_POLYGON);
        v2f(-13.8686623f, 3.5775823f, tx, ty, s);
        v2f(-13.7356235f, 3.6438114f, tx, ty, s);
        v2f(-13.7423892f, 1.2267410f, tx, ty, s);
        v2f(-13.8739132f, 1.2267410f, tx, ty, s);
    glEnd();

    glBegin(GL_POLYGON);
        v2f(-13.3564031f, 3.6429188f, tx, ty, s);
        v2f(-13.2238250f, 3.5761641f, tx, ty, s);
        v2f(-13.2162929f, 1.2311251f, tx, ty, s);
        v2f(-13.3609694f, 1.2311251f, tx, ty, s);
    glEnd();

    glBegin(GL_POLYGON);
        v2f(-14.0643705f, 3.3540592f, tx, ty, s);
        v2f(-13.0328204f, 3.3592604f, tx, ty, s);
        v2f(-12.9918280f, 3.2536779f, tx, ty, s);
        v2f(-14.1060803f, 3.2412459f, tx, ty, s);
    glEnd();

    glBegin(GL_POLYGON);
        v2f(-14.1230307f, 3.0578775f, tx, ty, s);
        v2f(-12.9770639f, 3.0598220f, tx, ty, s);
        v2f(-12.9722835f, 2.9564614f, tx, ty, s);
        v2f(-14.1307314f, 2.9564614f, tx, ty, s);
    glEnd();

    glBegin(GL_POLYGON);
        v2f(-14.1276246f, 2.0311994f, tx, ty, s);
        v2f(-12.9703370f, 2.0283905f, tx, ty, s);
        v2f(-12.9787639f, 1.9202459f, tx, ty, s);
        v2f(-14.1318381f, 1.9216504f, tx, ty, s);
    glEnd();

    glBegin(GL_POLYGON);
        v2f(-13.5966099f, 3.6733181f, tx, ty, s);
        v2f(-13.5084831f, 3.6741230f, tx, ty, s);
        v2f(-13.5094656f, 3.3573714f, tx, ty, s);
        v2f(-13.6000000f, 3.3500000f, tx, ty, s);
    glEnd();

    glBegin(GL_POLYGON);
        v2f(-13.7461249f, 3.5732364f, tx, ty, s);
        v2f(-13.3431110f, 3.5762070f, tx, ty, s);
        v2f(-13.3450914f, 3.5276869f, tx, ty, s);
        v2f(-13.7441445f, 3.5227359f, tx, ty, s);
    glEnd();
}

void door(){

 glColor3ub(157, 128, 121);
drawSemiCircleFromPoints(
    -3.8523911f, -11.2821379f,   // Z8
     2.8114257f, -11.2821379f,   // A9
    1);

    glBegin(GL_POLYGON);
        glVertex2f(-3.8523911f, -11.2821379f);   // A
        glVertex2f( 2.8114257f, -11.2821379f);   // B
    glVertex2f( 2.8114258f, -14.7431491f); // B9
    glVertex2f(-3.8523911f, -14.7431491f); // C9
    glEnd();
  glColor3ub(210, 180, 160);
drawSemiCircleFromPoints(
    -3.3650712f, -11.3274700f,   // V8
     2.3467718f, -11.3274700f,   // W8
    1
);
    glBegin(GL_POLYGON);
        glVertex2f(-3.3650712f, -11.3274700f);   // A
        glVertex2f( 2.3467718f, -11.3274700f);   // B
         glVertex2f( 2.3467718f, -14.7431491f); // E9
         glVertex2f(-3.3650712f, -14.7431491f); // D9

    glEnd();

glColor3ub(180, 150, 120);
glBegin(GL_POLYGON);
    glVertex2f(-2.7409422f, -10.9713875f); // L9
    glVertex2f( 1.6895561f, -10.9768123f); // M9
    glVertex2f( 1.6914179f, -14.7674048f); // N9
    glVertex2f(-2.7400978f, -14.7750360f); // O9
glEnd();
//glColor3ub(180, 150, 120);
 glColor3ub(157, 128, 121);
glBegin(GL_POLYGON);
    glVertex2f(-0.2892676f, -14.7431491f); // H9
    glVertex2f(-0.7355753019957f, -14.7480687f); // I9
    glVertex2f(-0.7355753019957f, -11.1166773f); // F9
    glVertex2f(-0.2892676f, -11.0824406f); // G9
glEnd();

drawCircle(-0.5106065f, -12.2121247f, 0.3650f);

glColor3ub(90, 60, 60);
glBegin(GL_POLYGON);
    glVertex2f(-39.9210084117227f, -14.7615755087948f); // C11
     glVertex2f(30.2674359636246f, -14.7615755087948f);  // E11
    glVertex2f(30.2674359636246f, -15.6680574645106f);  // D11
   // glVertex2f(20.2674359636246f, -14.7615755087948f);  // E11
    glVertex2f(-39.9210084117227f, -15.6680574645106f); // F11
glEnd();


}

void tree1() {   //Tree1


 glColor3ub(44, 51, 20);
 drawCircle(-19.0f, -5.0f, 5.013f);
  drawCircle(-22.804788692398f, -5.9501141233611f, 3.3111202508459f);
glColor3ub(72, 80, 48); //
 drawCircle(-21.347964f, -3.749147f, 3.789183f);
 drawCircle(-22.804788692398f, -5.47425690488f, 3.1033614660797f);
 drawCircle(-19.4737881630041f, -4.0942709712848f, 3.6038546802988f);





    glColor3ub(74, 63, 49); //

    glBegin(GL_POLYGON);
 glVertex2f(-19.5293318023835f, -15.4151580585902f);  // M3
glVertex2f(-19.2541336081239f, -7.2381118656848f);   // N3
glVertex2f(-19.1315778764524f, -7.2337997495157f);   // O3
glVertex2f(-18.6088326241928f, -15.4001043571168f);  // P3

    glEnd();

  glBegin(GL_TRIANGLES);
  glVertex2f(-19.1008332420332f, -10.288739931644f);   // Q3
glVertex2f(-17.5773435306102f, -7.490605211825f);    // R3
glVertex2f(-18.9862837078256f, -10.7844304114269f);  // S3
  glEnd();


    glBegin(GL_POLYGON);
 glVertex2f(-19.3018416599835f, -10.5692772622301f);  // T3
glVertex2f(-21.0876127983316f, -6.6965205766861f);   // U3
glVertex2f(-21.030238625212f, -6.5889440020877f);   // V3
glVertex2f(-19.215780400304f, -9.7732106102016f);   // W3
glEnd();

    glBegin(GL_POLYGON);
 glVertex2f(-20.4697106983092f, -7.9555276017788f);  // Z3
glVertex2f(-21.4503183496033f, -7.2370155360526f);  // A4
glVertex2f(-21.3495582537717f, -7.1301906295502f);  // B4
glVertex2f(-20.6821398930106f, -7.5013484710678f);  // C4
glEnd();
}





void tree2() {   //Tree2


 glColor3ub(44, 51, 20);
 drawCircle(20.2493107743873f, -3.9947329514626f, 4.1911524219f);
drawCircle(19.8506426253646f, -2.8867658082662f, 2.9207164922f);
glColor3ub(72, 80, 48); //
drawCircle(19.6351631469011f, -3.3303485648335f, 3.8086332267f);
drawCircle(15.1755186093019f, -4.3868055995045f, 2.0195f);
glColor3ub(44, 51, 20);
drawCircle(19.8506426253646f, -2.8867658082662f, 2.9207164922f);
glColor3ub(72, 80, 48); //
 drawCircle(17.0248443769565f, -1.5488339737673f, 2.1981052991326f);
drawCircle(19.4277035077363f, -0.4215667272374f, 1.3330567225f);
drawCircle(19.5006333407396f, -2.3617518813327f, 2.6647f);


    glColor3ub(74, 63, 49); //


    glBegin(GL_POLYGON);
        glVertex2f(19.2237756431154f, -15.40492744045f);   // F3
        glVertex2f(19.5767688033495f, -5.8815739672427f);  // G3
        glVertex2f(19.7448155441375f, -5.8703708511902f);  // H3
        glVertex2f(20.375305913746f, -15.3484851217807f);  // I3
    glEnd();



  glBegin(GL_TRIANGLES);
glVertex2f(19.7389322524828f, -9.6212501779895f);  // J3
glVertex2f(21.7033686416345f, -6.0753807208692f);  // K3
glVertex2f(19.8995465484512f, -10.2884172535452f); // L3

  glEnd();


    glBegin(GL_POLYGON);
glVertex2f(19.553608064827f, -10.0166084449855f); // M3
glVertex2f(17.4038474880194f, -5.2723092410335f); // N3
glVertex2f(17.4637099452793f, -5.0855679712735f); // O3
glVertex2f(19.6077718902374f, -8.8761428519388f); // P3

glEnd();

    glBegin(GL_POLYGON);
glVertex2f(18.1293106540143f, -6.7473440073331f); // Q3
glVertex2f(16.9604746940313f, -5.8964314284723f); // R3
glVertex2f(17.0820336338695f, -5.7701971447951f); // S3
glVertex2f(17.9002188058575f, -6.2237054972649f); // T3

glEnd();
}




void drawCircleTrans(float cx, float cy, float r, float dx, float dy, float scale) {
    drawCircle(cx * scale + dx, cy * scale + dy, r * scale);
}

void tree2_translated(float dx, float dy, float scale) {   //Tree3
    glColor3ub(44, 51, 20);
    drawCircleTrans(20.2493107743873f, -3.9947329514626f, 4.1911524219f, dx, dy, scale);
    drawCircleTrans(19.8506426253646f, -2.8867658082662f, 2.9207164922f, dx, dy, scale);

    glColor3ub(72, 80, 48);
    drawCircleTrans(19.6351631469011f, -3.3303485648335f, 3.8086332267f, dx, dy, scale);
    drawCircleTrans(15.1755186093019f, -4.3868055995045f, 2.0195f, dx, dy, scale);

    glColor3ub(44, 51, 20);
    drawCircleTrans(19.8506426253646f, -2.8867658082662f, 2.9207164922f, dx, dy, scale);

    glColor3ub(72, 80, 48);
    drawCircleTrans(17.0248443769565f, -1.5488339737673f, 2.1981052991326f, dx, dy, scale);
    drawCircleTrans(19.4277035077363f, -0.4215667272374f, 1.3330567225f, dx, dy, scale);
    drawCircleTrans(19.5006333407396f, -2.3617518813327f, 2.6647f, dx, dy, scale);

    glColor3ub(74, 63, 49);

    glBegin(GL_POLYGON);
        glVertex2f(19.2237756431154f*scale + dx, -15.40492744045f*scale + dy);
        glVertex2f(19.5767688033495f*scale + dx, -5.8815739672427f*scale + dy);
        glVertex2f(19.7448155441375f*scale + dx, -5.8703708511902f*scale + dy);
        glVertex2f(20.375305913746f*scale + dx, -15.3484851217807f*scale + dy);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(19.7389322524828f*scale + dx, -9.6212501779895f*scale + dy);
        glVertex2f(21.7033686416345f*scale + dx, -6.0753807208692f*scale + dy);
        glVertex2f(19.8995465484512f*scale + dx, -10.2884172535452f*scale + dy);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(19.553608064827f*scale + dx, -10.0166084449855f*scale + dy);
        glVertex2f(17.4038474880194f*scale + dx, -5.2723092410335f*scale + dy);
        glVertex2f(17.4637099452793f*scale + dx, -5.0855679712735f*scale + dy);
        glVertex2f(19.6077718902374f*scale + dx, -8.8761428519388f*scale + dy);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(18.1293106540143f*scale + dx, -6.7473440073331f*scale + dy);
        glVertex2f(16.9604746940313f*scale + dx, -5.8964314284723f*scale + dy);
        glVertex2f(17.0820336338695f*scale + dx, -5.7701971447951f*scale + dy);
        glVertex2f(17.9002188058575f*scale + dx, -6.2237054972649f*scale + dy);
    glEnd();
}


void airbln(){  //AirBalloon

glPushMatrix();
glTranslatef(0.0f, balloonOffset, 0.0f);

glColor3ub(208, 96, 115);
drawCircle(19.8210413524093f, 20.0242420203381f, 4.9635440048f);
glBegin(GL_POLYGON);
glVertex2f(15.8415835996751f, 17.0577371501412f); // J4
glVertex2f(18.3539260617721f, 13.4336468986529f); // K4
glVertex2f(21.3036906060299f, 13.4336468986529f); // L4
glVertex2f(24.102323590764f, 17.5128962563607f);  // M4
glEnd();



glColor3ub(194, 178, 167);
glBegin(GL_POLYGON);
glVertex2f(18.3539260617721f, 13.4336468986529f); // K4
glVertex2f(21.3036906060299f, 13.4336468986529f); // L4
glVertex2f(20.9581347766344f, 12.8254739362358f); // N4
glVertex2f(18.6939866764564f, 12.8254739362358f); // O4
glEnd();


glColor3ub(131, 121, 134);
for (int i = 0; i < 5; i++) {
    float shift = i * 0.530f;
    glBegin(GL_POLYGON);
        glVertex2f(18.6939866764564f + shift, 12.8254739362358f); // O4
        glVertex2f(18.8401704126541f + shift, 12.8254739362358f); // P4
        glVertex2f(18.8401704126541f + shift, 11.2310513251621f); // Q4
        glVertex2f(18.6939866764564f + shift, 11.2276517033901f); // R4
    glEnd();

}


glColor3ub(194, 178, 167);
glBegin(GL_POLYGON);
glVertex2f(18.6939866764564f, 11.2276517033901f); // R4
glVertex2f(20.9705827176171f, 11.2276517033901f); // S4
glVertex2f(20.9705827176171f, 9.452659833853f);              // T4
glVertex2f(18.6939866764564f, 9.452659833853f);  // U4

glEnd();


glPopMatrix();

}


void road() {   //Road
    glColor3ub(250, 250, 249);

    glBegin(GL_POLYGON);
        glVertex2f(-30.0f, -15.7f);   // f
        glVertex2f( 30.0f, -15.7f);   // h
        glVertex2f( 30.0f, -16.45f);  // D
        glVertex2f(-30.0f, -16.45f);  // C
    glEnd();
      glColor3ub(157, 145, 145);
        glBegin(GL_POLYGON);
        glVertex2f(-30.0f, -16.45f);  // C
        glVertex2f( 30.0f, -16.45f);  // D
        glVertex2f( 30.0f, -20.0f);   // B
        glVertex2f(-30.0f, -20.0f);   // A
    glEnd();
}


void drawBench(float dx, float dy, float scale) {   //Bench

    glColor3f(0.72f, 0.52f, 0.26f); // brown
    glBegin(GL_POLYGON);
        glVertex2f((-1.1f*scale)+dx, (0.45f*scale)+dy);
        glVertex2f(( 1.1f*scale)+dx, (0.45f*scale)+dy);
        glVertex2f(( 1.1f*scale)+dx, (0.55f*scale)+dy);
        glVertex2f((-1.1f*scale)+dx, (0.55f*scale)+dy);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f((-1.1f*scale)+dx, (0.30f*scale)+dy);
        glVertex2f(( 1.1f*scale)+dx, (0.30f*scale)+dy);
        glVertex2f(( 1.1f*scale)+dx, (0.40f*scale)+dy);
        glVertex2f((-1.1f*scale)+dx, (0.40f*scale)+dy);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f((-1.1f*scale)+dx, (0.15f*scale)+dy);
        glVertex2f(( 1.1f*scale)+dx, (0.15f*scale)+dy);
        glVertex2f(( 1.1f*scale)+dx, (0.25f*scale)+dy);
        glVertex2f((-1.1f*scale)+dx, (0.25f*scale)+dy);
    glEnd();


    glColor3f(0.82f, 0.62f, 0.32f); // lighter brown
    glBegin(GL_POLYGON);
        glVertex2f((-1.1f*scale)+dx, (-0.05f*scale)+dy);
        glVertex2f(( 1.1f*scale)+dx, (-0.05f*scale)+dy);
        glVertex2f(( 1.1f*scale)+dx, ( 0.10f*scale)+dy);
        glVertex2f((-1.1f*scale)+dx, ( 0.10f*scale)+dy);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);


    glBegin(GL_POLYGON);
        glVertex2f((-0.9f*scale)+dx, (-0.05f*scale)+dy);
        glVertex2f((-0.8f*scale)+dx, (-0.05f*scale)+dy);
        glVertex2f((-0.75f*scale)+dx, (-0.5f*scale)+dy);
        glVertex2f((-0.95f*scale)+dx, (-0.5f*scale)+dy);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f((0.8f*scale)+dx, (-0.05f*scale)+dy);
        glVertex2f((0.9f*scale)+dx, (-0.05f*scale)+dy);
        glVertex2f((0.95f*scale)+dx, (-0.5f*scale)+dy);
        glVertex2f((0.75f*scale)+dx, (-0.5f*scale)+dy);
    glEnd();
}



void NdrawLampPost(float x, float y, float scale)  //night //Lamp Post
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
glColor3ub(60, 60, 60);
glBegin(GL_TRIANGLES);
glVertex2f(-0.0999972230711f, 0.3678357897559f);   // C
glVertex2f(0.0017907454311f, 0.4285170786707f);    // D
glVertex2f(0.1035787139334f, 0.3678357897559f);    // E
    glEnd();

    glBegin(GL_POLYGON);
glVertex2f(-0.0027512159813f, 0.369085422458f);    // F
glVertex2f(0.00829192775f, 0.369085422458f);       // G
glVertex2f(0.006847272371f, 0.0428342171723f);     // H
glVertex2f(-0.0023571686306f, 0.0431251382217f);   // I
    glEnd();
    glBegin(GL_QUADS);
glVertex2f(-0.01416660614f, 0.0421829013818f);     // J
glVertex2f(0.0178229243695f, 0.0428481447829f);    // K
glVertex2f(0.0387311841765f, -0.5570573069378f);   // M
glVertex2f(-0.0349897360619f, -0.5570573069378f);  // L
    glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.0584832161379f, -0.5566522469365f);  // N
glVertex2f(0.0614145442498f, -0.5566522469365f);   // O
glVertex2f(0.0614153096089f, -0.5645279202426f);   // P
glVertex2f(-0.0572617225083f, -0.5660557171482f);  // Q

    glEnd();

        glBegin(GL_POLYGON);
glVertex2f(-0.0807132430039f, 0.3678789164698f);   // R
glVertex2f(-0.0718274031606f, 0.3686522467811f);   // S
glVertex2f(-0.0532693123104f, 0.265707365461f);    // T
glVertex2f(-0.06f, 0.26f);                         // U
    glEnd();

        glBegin(GL_POLYGON);
glVertex2f(0.0755868656684f, 0.3683020941235f);    // V
glVertex2f(0.0864415980525f, 0.367951941466f);     // W
glVertex2f(0.0647321332843f, 0.2643067548308f);    // Z
glVertex2f(0.055628164188f, 0.268858739379f);      // A1
    glEnd();

        glBegin(GL_POLYGON);
glVertex2f(-0.06f, 0.26f);                         // U
glVertex2f(-0.0532693123104f, 0.265707365461f);    // T
glVertex2f(0.055628164188f, 0.268858739379f);      // A1
glVertex2f(0.0647321332843f, 0.2643067548308f);    // Z
glVertex2f(0.0542275535578f, 0.2397960688022f);    // B1
glVertex2f(-0.0490674804198f, 0.2380453055145f);   // C1

    glEnd();

   glColor3f(1.0f, 1.0f, 1.0f);

 glBegin(GL_POLYGON);
glVertex2f(-0.0718274031606f, 0.3686522467811f);   // S
glVertex2f(-0.0027512159813f, 0.369085422458f);    // F
glVertex2f(-0.0037392251347f, 0.2665978245209f);  // D1
glVertex2f(-0.0532693123104f, 0.265707365461f);    // T
  glColor3f(1.0f, 1.0f, 1.0f);
glVertex2f(-0.0718274031606f, 0.3686522467811f);   // S
glVertex2f(-0.0027512159813f, 0.369085422458f);    // F
glVertex2f(-0.0037392251347f, 0.2665978245209f);  // D1
glVertex2f(-0.0532693123104f, 0.265707365461f);    // T
    glEnd();

   glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_POLYGON);
glVertex2f(0.00829192775f, 0.369085422458f);       // G
glVertex2f(0.0755868656684f, 0.3683020941235f);    // V
glVertex2f(0.055628164188f, 0.268858739379f);      // A1
glVertex2f(0.0078592756183f, 0.2663148771995f);   // E1
glColor3f(1.0f, 1.0f, 1.0f);

glVertex2f(0.00829192775f, 0.369085422458f);       // G
glVertex2f(0.0755868656684f, 0.3683020941235f);    // V
glVertex2f(0.055628164188f, 0.268858739379f);      // A1
glVertex2f(0.0078592756183f, 0.2663148771995f);   // E1
    glEnd();

    glPopMatrix();
}



void drawLampPost(float x, float y, float scale)  //day//Lamp Post
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
glColor3ub(60, 60, 60);
glBegin(GL_TRIANGLES);
glVertex2f(-0.0999972230711f, 0.3678357897559f);   // C
glVertex2f(0.0017907454311f, 0.4285170786707f);    // D
glVertex2f(0.1035787139334f, 0.3678357897559f);    // E
    glEnd();

    glBegin(GL_POLYGON);
glVertex2f(-0.0027512159813f, 0.369085422458f);    // F
glVertex2f(0.00829192775f, 0.369085422458f);       // G
glVertex2f(0.006847272371f, 0.0428342171723f);     // H
glVertex2f(-0.0023571686306f, 0.0431251382217f);   // I
    glEnd();
    glBegin(GL_QUADS);
glVertex2f(-0.01416660614f, 0.0421829013818f);     // J
glVertex2f(0.0178229243695f, 0.0428481447829f);    // K
glVertex2f(0.0387311841765f, -0.5570573069378f);   // M
glVertex2f(-0.0349897360619f, -0.5570573069378f);  // L
    glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.0584832161379f, -0.5566522469365f);  // N
glVertex2f(0.0614145442498f, -0.5566522469365f);   // O
glVertex2f(0.0614153096089f, -0.5645279202426f);   // P
glVertex2f(-0.0572617225083f, -0.5660557171482f);  // Q

    glEnd();

        glBegin(GL_POLYGON);
glVertex2f(-0.0807132430039f, 0.3678789164698f);   // R
glVertex2f(-0.0718274031606f, 0.3686522467811f);   // S
glVertex2f(-0.0532693123104f, 0.265707365461f);    // T
glVertex2f(-0.06f, 0.26f);                         // U
    glEnd();

        glBegin(GL_POLYGON);
glVertex2f(0.0755868656684f, 0.3683020941235f);    // V
glVertex2f(0.0864415980525f, 0.367951941466f);     // W
glVertex2f(0.0647321332843f, 0.2643067548308f);    // Z
glVertex2f(0.055628164188f, 0.268858739379f);      // A1
    glEnd();

        glBegin(GL_POLYGON);
glVertex2f(-0.06f, 0.26f);                         // U
glVertex2f(-0.0532693123104f, 0.265707365461f);    // T
glVertex2f(0.055628164188f, 0.268858739379f);      // A1
glVertex2f(0.0647321332843f, 0.2643067548308f);    // Z
glVertex2f(0.0542275535578f, 0.2397960688022f);    // B1
glVertex2f(-0.0490674804198f, 0.2380453055145f);   // C1

    glEnd();

   glColor3f(1.0f, 1.0f, 1.0f);

 glBegin(GL_POLYGON);
glVertex2f(-0.0718274031606f, 0.3686522467811f);   // S
glVertex2f(-0.0027512159813f, 0.369085422458f);    // F
glVertex2f(-0.0037392251347f, 0.2665978245209f);  // D1
glVertex2f(-0.0532693123104f, 0.265707365461f);    // T
  glColor3f(1.0f, 1.0f, 0.0f);
glVertex2f(-0.0718274031606f, 0.3686522467811f);   // S
glVertex2f(-0.0027512159813f, 0.369085422458f);    // F
glVertex2f(-0.0037392251347f, 0.2665978245209f);  // D1
glVertex2f(-0.0532693123104f, 0.265707365461f);    // T
    glEnd();

   glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_POLYGON);
glVertex2f(0.00829192775f, 0.369085422458f);       // G
glVertex2f(0.0755868656684f, 0.3683020941235f);    // V
glVertex2f(0.055628164188f, 0.268858739379f);      // A1
glVertex2f(0.0078592756183f, 0.2663148771995f);   // E1
glColor3f(1.0f, 1.0f, 0.0f);

glVertex2f(0.00829192775f, 0.369085422458f);       // G
glVertex2f(0.0755868656684f, 0.3683020941235f);    // V
glVertex2f(0.055628164188f, 0.268858739379f);      // A1
glVertex2f(0.0078592756183f, 0.2663148771995f);   // E1
    glEnd();

    glPopMatrix();
}


void bus()  //Bus
{
    glPushMatrix();
    glTranslatef(Y, 0.0f, 0.0f);
glColor3ub(220, 220, 80);
glBegin(GL_POLYGON);
    glVertex2f(-13.3174904f, -14.9663542f); // F1
    glVertex2f(-13.3245834f, -17.8782113f); // G1
    glVertex2f(-14.8677225f, -17.9623160f); // P9
    glVertex2f(-23.0449874f, -17.8767267f); // Q9
    glVertex2f(-23.7351665f, -17.7754849f); // R9
    glVertex2f(-23.7090819f, -15.1670307f); // S9
    glVertex2f(-21.7571181f, -13.1405568f); // T9
    glVertex2f(-15.0193556f, -13.1272433f); // U9
glEnd();



drawSemiCircleFromPoints(-16.8891376f, -13.7911176f,
                         -13.8022257f, -16.4788598f, 1);

drawSemiCircleFromPoints(-23.5421486f, -16.1485503f,
                         -19.5677025f, -14.4016426f, 1);
glColor3ub(0, 0, 0);
glBegin(GL_POLYGON);
    glVertex2f(-13.2503928f, -16.9527661f); // H10
    glVertex2f(-13.2503928f, -18.0021207f); // I10
    glVertex2f(-23.7365428650237f, -18.0021207435351f); // J10
    glVertex2f(-23.7365428f, -16.9527661f); // J10
glEnd();
// Circle p (D1, E1)
glColor3ub(35, 39, 42);
drawCircle(-21.8284569f, -18.1186368f, 1.0466f);

// Circle q (D1, F1)
glColor3ub(255, 255, 255);
drawCircle(-21.8284569f, -18.1186368f, 0.6620f);

// Circle k2 (D1, G1)
glColor3ub(177, 173, 167);
drawCircle(-21.8284569f, -18.1186368f, 0.3839f);

// Circle P2 (B9, C9)
glColor3ub(35, 39, 42);
drawCircle(-16.1844107f, -17.8683715f, 1.0376f);

// Circle 42 (B9, D9)
glColor3ub(255, 255, 255);
drawCircle(-16.1844107f, -17.8683715f, 0.6579f);

// Circle 12 (B9, E9)
glColor3ub(177, 173, 167);
drawCircle(-16.1844107f, -17.8683715f, 0.3763f);

glColor3ub(0, 0, 0);
glBegin(GL_POLYGON);
  glVertex2f(-22.6741786f, -14.0390766f); // F4
    glVertex2f(-20.9322264f, -14.0495703f); // G9
    glVertex2f(-20.9303138f, -15.1791799f); // I9
    glVertex2f(-22.6741786f, -15.1896301f); // H9
glEnd();


glBegin(GL_POLYGON);
    glVertex2f(-20.4180769f, -13.9800241f); // J9
    glVertex2f(-17.6033651f, -13.9800241f); // K9
    glVertex2f(-17.6033651f, -15.1913238f); // L9
    glVertex2f(-20.4180769f, -15.1913238f); // N9
    glEnd();
    glBegin(GL_POLYGON);
   glVertex2f(-16.9641999f, -13.9854352f); // M9
    glVertex2f(-14.2631042f, -13.9854352f); // O9
    glVertex2f(-14.2631042f, -15.2162589f); // P9
    glVertex2f(-16.9641999f, -15.2162589f); // Q9
    glEnd();



    glLineWidth(1.0f);
    glColor3ub(0, 0, 0);

glBegin(GL_LINES);

glVertex2f(-22.9307549f, -13.6896524f); // R9
glVertex2f(-13.9013911f, -13.6896524f); // S9


glVertex2f(-20.6801970128134f, -14.0495703581168f); // T
glVertex2f(-20.6801970128134f, -17.9249528202196f);   //


glVertex2f(-17.4241835f, -13.9443297f); // V
glVertex2f(-17.4241835f, -17.9209192f); // W


glVertex2f(-23.7202877f, -15.4915536f); // Z
glVertex2f(-13.2863125f, -15.4915536f); // A10


glVertex2f(-13.8018435f, -17.0303840f); // B10
glVertex2f(-13.8018435f, -13.7397609f); // C10


glVertex2f(-18.2108438f, -15.9408812f); // D10
glVertex2f(-17.6967128f, -15.9408812f); // E10

glVertex2f(-17.0627231f, -15.9881938f); // F10
glVertex2f(-16.5454380f, -15.9881938f); // G10

glEnd();
 glPopMatrix();

}




void truck() {  //Truck
    glPushMatrix();
    glTranslatef(X, 0.0f, 0.0f);

   glColor3ub(15, 60, 60);

    glBegin(GL_POLYGON);
     glVertex2f(19.3514489f, -14.8726f);    // R21
     glVertex2f(19.3514488523538f, -13.1877503f);    // S21
     glVertex2f(17.3083816f, -13.1315749f);    // T21
     glVertex2f(16.6808681f, -13.7635484f);    // U21
     glVertex2f(16.2205f, -14.51695f);    // V21
     glVertex2f(13.2514339f, -15.1398463f);    // W21
     glVertex2f(12.731690f, -15.672f);      // B3
     glVertex2f(12.9303805f, -16.8251089277018f);    // Z21=
     glVertex2f(24.39544f, -16.8251089277018f);         // Q21
     glVertex2f(24.39544f, -14.8726f);         // P21
    glEnd();
    glColor3f(0.6f, 0.8f, 0.9f);   // Light sky-blue glass
        glBegin(GL_POLYGON);
     glVertex2f(18.753122f, -14.5512587735755f);         // E22
     glVertex2f(18.753122f, -13.44053f);                // F22
     glVertex2f(17.4297366159573f, -13.44053f);          // G22
     glVertex2f(16.8624297082772f, -14.5512587735755f);  // H22
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f); // black lines
    glLineWidth(1.0f);           // optional: line thickness
    glBegin(GL_LINE_LOOP);
    glVertex2f(16.7087f, -16.4509f);   // I22
    glVertex2f(19.05972f, -16.4509f);   // J22
    glVertex2f(19.05972f, -14.706525f);  // K22
    glVertex2f(16.7087f, -14.706525f);   // L22
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(16.7087f, -14.706525f);   // L22
    glVertex2f(16.7087f, -14.43161153381f);   // F2
    glVertex2f(17.3622007, -13.299388);   // L2
    glVertex2f(19.05972, -13.299388);   // G5
    glVertex2f(19.05972f, -14.706525f);  // K22
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(15.7177079f, -16.8251089f);   // B22
    glVertex2f(20.8399692f, -16.8251089f);   // C22
    glEnd();
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(18.2f, -15.3f);    // I13
    glVertex2f(18.765f, -15.3f);  // J13
    glEnd();

    drawSemiCircleFromPoints(13.3389939165829f, - 16.8251089277018f,15.7177078838903f, - 16.8251089277018f, 1);

    drawSemiCircleFromPoints(20.8399692490737f, - 16.8251089277018f,23.189496f, - 16.8251089277018f, 1);

    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(22.0169f, -16.8468f, 0.9651f);
    drawCircle(14.5552f, -16.6912f, 0.9692f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(14.5551583f, -16.6911657f, 0.5910f);  // e2
    drawCircle(22.0168756f, -16.8468462f, 0.6066f);  // f2


    glPopMatrix();
}
void timer(int value) {
    if (currentScenario == 1) {
        isDay = !isDay;
        glutPostRedisplay();
        glutTimerFunc(3000, timer, 0);
    }
}
//.................................................end scnario1.............................

///.....................// Scenario 2............................

//...... Scenario 2 variables...
float V = 35.0f;
float W = -35.0f;
float suvSpeed = -2.0f;
float BusS268Speed = 2.0f;  // Normal smooth speed
float planeX= 15.0f;
float planeSpeed = -.250f;
float cloudSX = -30.0f;    // Starting position (left side)
float cloudSSpeed = 0.15f; // Speed


// Function declarations Scenario 2
void planeS268();
void cloudS268();
void sun(float a, float b, float c);
void moon(float a, float b, float c);
void sky268();
void Factory268();
void wareHouse();
void road268();
void palace268();
void doggo();
void suv268();
void treeS1268(float baseX, float baseY);
void drawAllTrees();
void lampPost(float baseX, float baseY);
void lampPostNight(float baseX, float baseY);
void drawAllLampPosts();
void drawNightAllLampPosts();
void bus268();


//.....Animation function Scenario 2.....


///Sanim01SUV.................................................................................................
void animationSUV(int value) { //Sanim01SUV
    V += suvSpeed;   // move SUV
    if (V < -60.0f) {
        V = 35.0f;     // reset to right side
    }
    glutPostRedisplay();
    glutTimerFunc(40, animationSUV, 0);  // 16 ms
}
///Sanim02Plane...............................................................................................
void animationPlane(int value) { //
   if (currentScenario == 2){
            planeX += planeSpeed;   // move truck
    if (planeX < -60.0f) {
        planeX = 35.0f;     // reset to right side
    }}
    glutPostRedisplay();
    glutTimerFunc(40, animationPlane, 0);  // 16 ms
}
///Sanim03Bus..................................................................................................
void animationBus(int value) {
    if (currentScenario == 2){W += BusS268Speed;   // move truck
    if (W > 60.0f) {
        W = -35.0f;     // reset to right side
    }}
    glutPostRedisplay();
    glutTimerFunc(40, animationBus, 0);  // 16 ms
}
///Sanim04Cloud.................................................................................................

void animationCloudS268(int value) {
   if (currentScenario == 2) {
        cloudSX += cloudSSpeed;      // Move right
    if (cloudSX > 55.0f) {      // If goes off screen, reset to left
        cloudSX = -55.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(10, animationCloudS268, 0);  // Call again after 40ms
}

void timers(int value) {
    if (currentScenario == 2)
        {isDay = !isDay;
    glutPostRedisplay();
    glutTimerFunc(1500, timers, 0);}
}

void planeS268() //SobjPlane
{
          glPushMatrix();
    glTranslatef(planeX, 0.0f, 0.0f);

    glColor3f(1.0f, 0.7804f, 0.1725f);//plane body color
    glBegin(GL_POLYGON);
     glVertex2f(17.5107595089209f, 14.985971f);   // P12
     glVertex2f(23.6134957679064f, 14.985971f);   // O12
     glVertex2f(25.3076349041688f, 15.0519290472096f); // Q12
     glVertex2f(25.319492374082f, 14.1162269106237f);  // R12
     glVertex2f(23.5341889234929f, 13.385206132629f);  // S12
     glVertex2f(21.0f, 13.0f);                     // T12
     glVertex2f(17.9766510655651f, 12.7146917842688f); // U12
     glVertex2f(17.043910849305f, 12.7324561224488f);  // V12
     glVertex2f(16.7587308858718f, 12.7672710415682f); // W12
     glVertex2f(16.4324804430059f, 12.8379134285362f); // Z12
     glVertex2f(15.8941672122771f, 13.0262931271174f); // A13
    glEnd();

    drawSemiCircleFromPoints(15.8126046015606f, 14.0702306234216f,16.585274694493f, 13.2027426054281f, 1);//p1
    drawSemiCircleFromPoints(16.3406398067912f, 14.1997891072959f,18.6448920239578f, 13.3200611977235f, 1);//p5
    drawSemiCircleFromPoints(25.3076349041688f, 15.0519290472096f,25.319492374082f, 14.1162269106237f, 1);//s

    glBegin(GL_POLYGON);
    glVertex2f(18.120339568556f, 14.9904332643219f);  // F13
    glVertex2f(17.9340025451997f, 15.7189243888237f); // G14
    glVertex2f(18.5279518071464f, 15.7133206109429f); // H14
    glVertex2f(19.2034235168113f, 15.0240559316066f); // I14
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(19.6808055248428f, 13.2614940768375f); // J14
    glVertex2f(21.1299604723837f, 13.7541104614997f); // O14
    glVertex2f(25.3404405189701f, 13.0325315318536f); // P14
    glVertex2f(24.309449685645f, 12.4774708167413f);  // Q14
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(23.6134957679064f, 14.985971f);   // O12
    glVertex2f(24.933395025051f, 16.6316601988283f);   // k16
    glVertex2f(25.6804421462071f, 16.8063507053844f);   // k16
    glVertex2f(25.3076349041688f, 15.0519290472096f); // Q12

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(25.3404405189701f, 13.0325315318536f); // P14
    glVertex2f(25.5707438077477f, 13.0585895992545f); // E16
    glVertex2f(25.4604229979309f, 12.8887225427855f); // D16
    glVertex2f(24.5910950165749f, 12.5235083713769f); // C16
    glVertex2f(24.309449685645f, 12.4774708167413f);  // Q14
    glVertex2f(24.5069490520683f, 12.6625756821016f); // B16

    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(25.3076349041688f, 15.0519290472096f);  // Q12
    glVertex2f(25.319492374082f, 14.1162269106237f);   // R12
    glVertex2f(26.5405160735786f, 14.6548408875011f);  // D17
    glVertex2f(26.8271179040287f, 14.985971f);   // C17
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(16.585274694493f, 13.2027426054281f);  // C13
    glVertex2f(18.6448920239578f, 13.3200611977235f); // E13
     glVertex2f(17.049135057163f, 14.1017096157146f);  // A17
     glVertex2f(16.516337638988f, 14.2904249655874f);  // B17
     glVertex2f(16.0f, 13.5f);  // j16
    glEnd();


  glColor3f(0.7529f, 0.3686f, 0.2392f);
    drawSemiCircleFromPoints(15.8941672122771f, 13.0262931271174f,15.8126046015606f, 14.0702306234216f, 1);//t
    glColor3f(0.0f, 0.0f, 0.0f);//black
    drawCircle(21.3678814339203f, 12.3733969326577f, 0.6447f); //q5
    drawCircle(23.3289269350701f, 12.352582155841f, 0.6871f); //r5
    drawCircle(20.165900153547f, 14.385379031992f, 0.2814f);//e6
    drawCircle(20.7714271602684f, 14.3958786203313f, 0.2573f);//f6
    drawCircle(21.3714989687311f, 14.3958786203313f, 0.2445f);//g6
    drawCircle(21.9608878992107f, 14.4015193645316f, 0.2363f);//h6

    glColor3f(0.0078f, 0.5176f, 0.7804f);// enginee
    drawCircle(21.3678814339203f, 12.3733969326577f, 0.4921f);
    drawCircle(23.3289269350701f, 12.352582155841f, 0.4847f);

    glColor3f(0.2f, 0.7373f, 0.7843f);//light blue
    drawCircle(21.3678814339203f, 12.3733969326577f, 0.3295f);
    drawCircle(23.3289269350701f, 12.352582155841f, 0.2258f);
    // k6:
    drawCircle(21.9608878992107f, 14.4015193645316f, 0.1737f);
    // P6:
    drawCircle(21.3714989687311f, 14.3958786203313f, 0.1717f);
    // 96:
    drawCircle(20.7714271602684f, 14.3958786203313f, 0.1715f);
    // r6:
    drawCircle(20.165900153547f, 14.385379031992f, 0.1980f);

    glBegin(GL_POLYGON);
    glVertex2f(16.9936353261032f, 14.7283870039714f); // V16
    glVertex2f(17.7706315609405f, 14.61445660652f);   // W16
    glVertex2f(17.8039313995764f, 14.0625422789485f); // Z16
    glVertex2f(17.049135057163f, 14.1017096157146f);  // A17
    glVertex2f(16.516337638988f, 14.2904249655874f);  // B17
    glEnd();

 glPopMatrix();

}



void cloudS268() //SobjCloud
{
          glPushMatrix();
    glTranslatef(cloudSX, 0.0f, 0.0f);

    glColor3ub(255, 255, 255);

    //SobjCloud1  start
    drawCircle(-10.2035787695785f, 19.5722960591032f, 1.607f);
    drawSemiCircleFromPoints(-20.4049868503314f, 19.1219962631988f,-19.2878910577392f, 19.2713065250388f,1);
    drawSemiCircleFromPoints(-19.6757715412782f, 19.4355478130628f,-18.5897061873691f, 20.1373060437109f,1);
    drawSemiCircleFromPoints(-19.1637693030068f, 20.0477198866069f,-17.3019429820199f, 21.0480986409351f,1);
    drawSemiCircleFromPoints(-17.9535821943653f, 21.3019260860631f,-13.0f, 20.0f,1);
    drawSemiCircleFromPoints(-13.159379417824f, 20.9286504314631f,-11.4527052902526f, 20.1223750175269f,1);
    drawSemiCircleFromPoints(-11.6699183610345f, 20.420995541207f,-9.42928000211f, 18.6507358251385f,1);
    drawSemiCircleFromPoints(-9.5133028725579f, 19.4355478130628f,-11.0648248067137f, 18.3455829016307f,0);
    drawSemiCircleFromPoints(-10.8010660779072f, 18.7785826609667f,-15.7349058285225f, 20.734547091071f,0);
    drawSemiCircleFromPoints(-14.5092035005395f, 17.8379280113746f,-17.0f, 20.0f,0);
    drawSemiCircleFromPoints(-16.7123646470407f, 18.3903759801827f,-18.4655844326367f, 19.3758237083268f,0);
    drawSemiCircleFromPoints(-18.3259474585627f, 18.4948931634707f,-20.0636520248171f, 19.3011685774068f,0);
    drawSemiCircleFromPoints(-19.3034062770808f, 18.3455829016307f,-21.1497173787261f, 19.2115824203028f,0);
    drawSemiCircleFromPoints(-21.1216604015636f, 18.76975169766f,-20.2106844499344f, 19.3627965885558f,1);

    glBegin(GL_POLYGON); //First cloud polygon
    glVertex2f(-21.2f, 18.8f);                     // I25
    glVertex2f(-20.447395667382f, 19.4523611871131f); // J25
    glVertex2f(-20.3062482829839f, 19.3301116899407f); // K25
    glVertex2f(-19.8f, 19.6f);                     // L25
    glVertex2f(-19.0448598233984f, 20.333151895285f); // M25
    glVertex2f(-17.7320274254586f, 21.257621137537f); // N25
    glVertex2f(-13.0141282806729f, 20.9352035816671f); // O25
    glVertex2f(-11.1637490130606f, 20.5194742967855f); // P25
    glVertex2f(-9.3565692614238f, 19.8750939052191f);  // Q25
    glVertex2f(-9.6373661152638f, 18.6417636934037f);  // R25
    glVertex2f(-11.1997486097068f, 18.5170449079392f); // S25
    glVertex2f(-15.6996981904758f, 18.2676073370103f); // T25
    glVertex2f(-17.6004768933926f, 18.3161090869132f); // U25
    glVertex2f(-18.6948646314357f, 18.3923261224748f); // V25
    glVertex2f(-19.6380540635649f, 18.2191055871075f); // W25
    glVertex2f(-20.7324418016079f, 18.0805291588136f); // Z25
    glEnd();

    //SobjCloud2 ...... 2nd cloud start
    drawSemiCircleFromPoints(-9.5133028725579f, 19.4355478130628f,-11.0648248067137f, 18.3455829016307f,0);
    drawSemiCircleFromPoints(14.1817250877318f, 6.4128110756509f, 18.3655032280869f, 6.5050151989768f, 1);
    drawSemiCircleFromPoints(16.9922020064437f, 8.2261588343921f, 20.4094864416955f, 9.2711388987514f, 1);
    drawSemiCircleFromPoints(19.8665534005808f, 8.994526528774f, 21.8466621387641f, 6.8430969845048f, 1);
    drawSemiCircleFromPoints(21.3037290976493f, 7.2426481855833f, 23.3157750735453f, 5.6444433812691f, 1);
    drawSemiCircleFromPoints(23.1241516472695f, 6.2591375367746f, 26.3498126562456f, 4.7838715635614f, 1);
    drawSemiCircleFromPoints(26.0f, 6.0f, 26.0f, 4.0f, 1);
    drawSemiCircleFromPoints(26.3411941457847f, 4.4282324225062f, 20.8332563221859f, 6.9737843190244f, 0);
    drawSemiCircleFromPoints(22.3158793424227f, 5.2507437402087f, 17.302232899498f, 6.6543417226433f, 0);
    drawSemiCircleFromPoints(18.0356266027376f, 5.5720724094616f, 13.81472134188f, 5.661506867517f, 0);
    drawSemiCircleFromPoints(13.81472134188f, 5.661506867517f, 11.8909279906751f, 6.466444664598f, 0);
    drawSemiCircleFromPoints(12.352317451564f, 6.2563898038276f, 11.2647264765043f, 7.279242540829f, 0);
    drawSemiCircleFromPoints(11.1253193681113f, 7.0686561224345f, 14.3409620413613f, 6.3261885325742f, 1);

    glBegin(GL_POLYGON); //2nd Cloud polygon
        glVertex2f(11.5f, 7.5f);               // H25
        glVertex2f(14.8444165681509f, 6.9346758384104f); // A26
        glVertex2f(17.3523668319477f, 8.8414148370216f); // B26
        glVertex2f(19.6744495298269f, 9.74013258159f);   // C26
        glVertex2f(20.4190303949077f, 8.8899941745659f); // D26
        glVertex2f(21.7693719637831f, 7.9426970924533f); // E26
        glVertex2f(22.375132667577f, 7.0196896791128f);  // F26
        glVertex2f(23.9273944710513f, 6.5703308068286f); // G26
        glVertex2f(26.03493691967f, 6.4003031254238f);   // H26
        glVertex2f(26.2747171982553f, 5.7444820685766f); // I26
        glVertex2f(25.6941965237855f, 3.8498879043514f); // J26
        glVertex2f(22.0974923450052f, 3.7284395604909f); // K26
        glVertex2f(21.113131201339f, 4.590722801901f);   // L26
        glVertex2f(19.2201290019809f, 4.2749571078635f);// M26
        glVertex2f(16.7844661721402f, 4.7486056489198f);// N26
        glVertex2f(14.2604632396628f, 5.0157920054131f);// O26
        glVertex2f(13.5663624332315f, 5.9630890875257f);// P26
        glVertex2f(12.1781608203689f, 5.9023649155954f);// Q26
        glVertex2f(11.5219200579248f, 6.655344647531f); // R26
    glEnd();
    drawCircle(24.910308830362f, 5.3322804683784f, 2.149f);
    drawCircle(12.7000531365453f, 6.7635448696408f, 1.568f);
    drawCircle(21.1278837582925f, 8.0887896856245f, 1.146f);
    //2nd cloud end


   //SobjCloud3 small cloud start
    drawSemiCircleFromPoints(5.9079811491751f, 21.514692807656f,8.1155753997891f, 21.9486274942209f, 1); // Z26-A27
    drawSemiCircleFromPoints(7.8243608390698f, 21.9847887181013f,8.5758822860874f, 21.7859019867593f, 1); // B27-C27
    drawSemiCircleFromPoints(5.776464895947f, 20.9180326136307f, 4.7525169243856f, 21.3338866882548f, 0); // D27-E27
    drawSemiCircleFromPoints(4.8840331776137f, 21.0717178151222f,6.1240435651926f, 21.2434836285539f, 1); // F27-G27
    drawSemiCircleFromPoints(8.5f, 22.0f,9.3274037331049f, 21.0626775091521f, 2); // H27-127
    drawSemiCircleFromPoints(9.367541810388f, 21.3327361038586f,8.5f, 21.0f, 0); // J27-K27
    drawSemiCircleFromPoints(8.8295207744558f, 21.2587699641034f,6.7799168280443f, 21.8669360020912f, 0); // L27-M27
    drawSemiCircleFromPoints(7.2837777982038f, 20.9464684851366f,5.6184745917445f, 21.5875083630157f,0); // N27-O27
    drawCircle(5.1782143160222f, 21.0460001592137f, sqrt(0.3742794491029f)); // P27
    drawCircle(9.2341195833437f, 21.4969661763767f, sqrt(0.2892486880927f)); // Q27

    glBegin(GL_POLYGON);
        glVertex2f(5.3721221375674f, 20.7738654936843f); // S27
        glVertex2f(5.3236451821811f, 21.372561757849f);  // T27
        glVertex2f(7.1334515166035f, 22.1500893736473f); // U27
        glVertex2f(9.2018016130862f, 21.7691008419061f); // V27
        glVertex2f(8.2080240276668f, 20.8049665983162f); // W27
        glVertex2f(6.5517280519677f, 20.8205171506322f); // Z27
    glEnd();
    //Small cloud end




 glPopMatrix();

}



 void sun(float a, float b, float c)//SobjSun
 {
      glColor3ub(255, 255, 0);
     drawCircle(15.7977373429029f, 19.7825631123478f, 3.965f);

 }

void moon(float a, float b, float c)//SobjMoon
 {
      glColor3f(0.85f, 0.85f, 0.80f);//moon color
     drawCircle(15.7977373429029f, 19.7825631123478f, 3.965f);

     glColor3f(0.0f, 0.0f, 0.2f);
     drawCircle(17.3214f, 19.79195f, 3.493f);

 }


void sky268() { //SobjSky
    glColor3ub(219, 241, 249); // Sky blue color

    glBegin(GL_POLYGON);
        glVertex2f(-30.0f, -20.0f);    // A
        glVertex2f( 30.0f, -20.0f);    // B
        glVertex2f( 30.0f,  26.7742f); // D
        glVertex2f(-30.0f,  26.7742f); // C
    glEnd();
}
void Factory268() { //SobjFactory

    //glColor3f(0.945f, 0.478f, 0.380f);//factory pink color
    glColor3f(0.110f, 0.141f, 0.231f);//Deep blue factory color
    glBegin(GL_POLYGON);
    glVertex2f(-30.0f, -15.758f);              // F
    glVertex2f(-30.0f, -4.23515f);            // W23
    glVertex2f(-25.5323f, -4.23515f);         // U23
    glVertex2f(-25.5323f, -15.758f);          // T23
    glEnd();
    glColor3f(0.945f, 0.478f, 0.380f);//factory pink color
    glBegin(GL_POLYGON);
    glVertex2f(-14.58349f, -4.23515f);        // R23
    glVertex2f(-14.58349f, -15.758f);         // S23
    glVertex2f(-25.5323f, -15.758f);          // T23
    glVertex2f(-25.5323f, -4.23515f);         // U23
    glVertex2f(-20.057895f, -0.01f);          // V23
    glEnd();

    glColor3f(0.133f, 0.176f, 0.388f);//lite blue color
    glBegin(GL_POLYGON);
    glVertex2f(-25.5323f, -4.23515f);         // U23
    glVertex2f(-20.057895f, -0.01f);          // V23
    glVertex2f(-24.525595f, -0.014f);         // Z23
    glVertex2f(-30.0f, -3.4013079f);          // L13
    glVertex2f(-30.0f, -4.23515f);            // W23
    glEnd();
    glColor3f(0.945f, 0.478f, 0.380f);//factory pink color
    glBegin(GL_POLYGON);
    glVertex2f(-25.50068f, -1.77947f);   // K29
    glVertex2f(-25.50068f, 1.435742f);   // L29
    glVertex2f(-24.35716f, 1.435742f);   // M29
    glVertex2f(-24.35716f, -1.777947f);  // N29
    glEnd();
    glColor3f(0.133f, 0.176f, 0.388f);//lite blue color
    glBegin(GL_POLYGON);
     glVertex2f(-24.35716f, 1.435742f);   // M29
    glVertex2f(-24.35716f, -1.777947f);  // N29
    glVertex2f(-23.62661f, -0.850111f);  // O29
    glVertex2f(-23.62661f, 0.975159f);   // P29
    glEnd();



// factory top  windows
    for (int i = 0; i < 3; i++) {
    float dx = i * 3.0f;
   glColor3f(0.133f, 0.176f, 0.388f);
   glBegin(GL_POLYGON);
   glVertex2f(-23.78491f + dx,  -6.06618f ); // S6
   glVertex2f(-21.7766f + dx, -6.06618f ); // T6
   glVertex2f(-21.7766f + dx, -8.124336f );
   glVertex2f(-23.78491f + dx, -8.124336f );
   glEnd();
   for (int i = 0; i < 3; i++)
    {
        float dx = i * 3.0f;
   drawSemiCircleFromPoints(-23.78491f +  dx ,-6.06618f ,-21.7766f+dx, -6.06618f, 1);
   }
   }
   // factory down big single windows
   glColor3f(0.133f, 0.176f, 0.388f);
   glBegin(GL_POLYGON);
   glVertex2f(-23.78491f, -13.04067f);   // W28
   glVertex2f(-23.78491f, -15.26442f);   // Z28
   glVertex2f(-15.40073f, -15.26442f);   // A29
   glVertex2f(-15.40073f, -13.04067f);   // B29
   glEnd();
   //factory downwindows
   for (int i = 0; i < 3; i++)
   {
        float dx = i * 3.0f;
        glColor3f(0.133f, 0.176f, 0.388f);
        glBegin(GL_POLYGON);
        glVertex2f(-23.78491f + dx, -10.5552f ); // S6
        glVertex2f(-21.7766f + dx, -10.5552f ); // T6
        glVertex2f(-21.7766f + dx,  -12.21259f );
        glVertex2f(-23.78491f + dx,   -12.21259f );
        glEnd();
        for (int i = 0; i < 3; i++) {
                float dx = i * 3.0f;
        drawSemiCircleFromPoints(-23.78491f+dx, -10.5552f,-21.7766f +dx, -10.5552f, 1);
        }

}



}
void wareHouse() { //SobjWareHouse

    glColor3f(0.184f, 0.275f, 0.161f);//ware house left color
    glBegin(GL_POLYGON);
    glVertex2f(17.0205300f, -2.2647000f);   // S22
    glVertex2f(23.1842000f, 4.2119391f);    // W22
    glVertex2f(23.1842000f, -15.6720000f);  // V22
    glVertex2f(17.0205300f, -15.6720000f);  // R22
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);// white color
    glBegin(GL_POLYGON);
    glVertex2f(21.6089500f, -3.8470000f);   // A23
    glVertex2f(21.6089500f, -6.8260000f);   // B23
    glVertex2f(18.1264400f, -6.8260000f);   // C23
    glVertex2f(18.1264400f, -3.8470000f);   // D23
    glEnd();
    glColor3f(0.184f, 0.275f, 0.161f);//ware house left color
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(19.8676950f, -3.8470000f);   // I23
    glVertex2f(19.867695f, -6.826f);          // J23
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(21.60895f, -5.3365f);          // K23
    glVertex2f(18.12644f, -5.3365f);          // L23
    glEnd();

    glColor3f(0.161f, 0.224f, 0.122f); //ware house right color
    glBegin(GL_POLYGON);
    glVertex2f(23.1842000f, 4.2119391f);    // W22
    glVertex2f(23.1842000f, -15.6720000f);  // V22
    glVertex2f(29.6269000f, -15.6720000f);  // Q22
    glVertex2f(29.6269000f, -2.2647000f);   // T22
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);// white color
    glBegin(GL_POLYGON);
    glVertex2f(24.7594500f, -3.8470000f);   // E23
    glVertex2f(28.2419600f, -3.8470000f);   // F23
    glVertex2f(28.2419600f, -6.8260000f);   // G23
    glVertex2f(24.7594500f, -6.8260000f);   // H23
    glEnd();
    glColor3f(0.161f, 0.224f, 0.122f); //ware house right color
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(28.24196f, -5.3365f);          // P23
    glVertex2f(24.75945f, -5.3365f);          // Q23
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(26.6287163009564f, -3.847f);  // M23
    glVertex2f(26.6287163009564f, -6.826f);  // O23
    glEnd();

}
void road268() { //SobjRoad
    glColor3ub(250, 250, 249); // Light road color

    glBegin(GL_POLYGON);
        glVertex2f(-30.0f, -15.7f);   // f
        glVertex2f( 30.0f, -15.7f);   // h
        glVertex2f( 30.0f, -16.45f);  // D
        glVertex2f(-30.0f, -16.45f);  // C
    glEnd();
      glColor3ub(157, 145, 145);
        glBegin(GL_POLYGON);
        glVertex2f(-30.0f, -16.45f);  // C
        glVertex2f( 30.0f, -16.45f);  // D
        glVertex2f( 30.0f, -20.0f);   // B
        glVertex2f(-30.0f, -20.0f);   // A
    glEnd();
}


void palace268() {//SobjPalace
      glColor3f(0.878f, 0.353f, 0.183f); // triangle color
    glBegin(GL_TRIANGLES); // left triangle
    glVertex2f(-9.575f, 7.575f);     // I
    glVertex2f(-12.507536f, 0.975f); // K
    glVertex2f(-6.6534912f, 0.975f); // L
    glEnd();
    glBegin(GL_TRIANGLES); // Right triangle
    glVertex2f(9.1161196f, 7.575f);// J
    glVertex2f(6.175f, 0.975f);    // M
    glVertex2f(12.0f, 0.975f);     // N
    glEnd();
        glBegin(GL_TRIANGLES); // TOp triangle
    glVertex2f(-0.5273494083299f, 14.6806895544131f); // Q
    glVertex2f(-0.2640942f, 17.5370083f);             // R
    glVertex2f(0.012323718762f, 14.6806895544131f);   // S
    glEnd();
    glBegin(GL_POLYGON); //top triangle polygon
    glVertex2f(-2.6465536f, 9.0338659f);               // P
    glVertex2f(-0.5273494083299f, 14.6806895544131f);  // Q
    glVertex2f(0.012323718762f, 14.6806895544131f);    // S
    glVertex2f(2.0262259f, 9.0338658587443f);          // T
    glEnd();

    glColor3f(0.393, 0.215, 0.097);// khuti color
    //Right khuti semi circle
    drawSemiCircleFromPoints(3.9516f, 0.5758f,6.4697f, 0.5758f, 1);

    glBegin(GL_POLYGON); //Right khuti down
    glVertex2f(0.5758f, 0.651f);    // M3
    glVertex2f(6.4697f, 0.5758f);   // Q1
    glVertex2f(6.4697f, -3.189f);    // I5
    glVertex2f(5.8607f, -4.76f);      // T1
    glVertex2f( 5.399f, -4.3561f);    // H12
    glVertex2f( 5.399f, -3.8480f);    // I12
    glVertex2f(4.119304f, -3.848f);   // J12
    glVertex2f(3.96792f, -3.67321f);  // N3

    glEnd();

    glBegin(GL_POLYGON); //Right khuti down
    glVertex2f(5.0101f, -14.45f);          // K4
    glVertex2f(5.0101f, -9.409f);          // A6
    glVertex2f(6.1378f, -9.409f);         // R2
    glVertex2f(6.1378f, -14.45f);        // V5
    glEnd();
    glColor3f(0.393, 0.215, 0.097);
    glBegin(GL_POLYGON); //Right khuti middle
    glVertex2f(5.0101f, -9.409f);          // A6
    glVertex2f(5.0101f, -8.09120f);        // B24
    glVertex2f(5.55922f, -8.0912f);        // C6
    glVertex2f(5.55922f, -9.409f);         // T2
    glEnd();
    glColor3f(0.393, 0.215, 0.097);
    glBegin(GL_POLYGON); //Right khuti middle

    glVertex2f(5.0101f, -8.09120f);         // B24
    glVertex2f(5.8607f, -8.0912f);         // B6
    glVertex2f(5.8607f, -4.3561f);         // D6
    glVertex2f(5.0101f, -4.3561f);         // J4

    glEnd();
    glColor3f(0.393, 0.215, 0.097);
    glBegin(GL_POLYGON); //Left khuti
    glVertex2f(-5.5352f, -14.45f);         // E4
    glVertex2f(-6.667540f, -14.45f);       // U5
    glVertex2f(-6.649153f, -9.409f);       // O5
    glVertex2f(-5.5352f, -9.409f);         // F6
    glEnd();

        glColor3f(0.393, 0.215, 0.097);
    glBegin(GL_POLYGON); //left khuti upside up
    glVertex2f(-5.5352f, -9.409f);         // F6
    glVertex2f(-6.022f, -9.409f);          // E6
    glVertex2f(-6.022f, -8.13f);           // G6
    glVertex2f(-5.5352f, -8.130f);         // A24
    glEnd();
    glBegin(GL_POLYGON); //left khutir uporere nicher part
    glVertex2f(-6.9922f, -3.189f);              // E5
    glVertex2f(-6.9751076557263f, -4.76f);     // H13
    glVertex2f(-5.805f, -4.76f);              // O4
    glVertex2f(-5.9876f, -3.8480f);            // F12
    glVertex2f(-5.9876f, -4.3561f);          // E12
    glEnd();
    glBegin(GL_POLYGON); //left khuti upside low
    glVertex2f(-5.5352f, -8.130f);          // A24
    glVertex2f(-6.3991f, -8.13f);          // Z5
    glVertex2f(-6.3991f, -4.3561f);        // H6
    glVertex2f(-5.5352f, -4.3561f);        // F4
    glEnd();
    //left khuti semi circle
    drawSemiCircleFromPoints(-6.975108f, 0.5758f, -4.470539f, 0.651f, 1);

    glBegin(GL_POLYGON); //uP middle  khuti up
    glVertex2f(-6.975108f, 0.5758f);       // T4
    glVertex2f(-4.470539f, 0.651f);        // L3
    glVertex2f(-4.4843f, -3.6944f);        // T3
    glVertex2f(-4.568254f, -3.848f);      // G12
    glVertex2f(-5.9876f, -3.8480f);        // F12
    glVertex2f(-6.9922f, -3.189f);         // E5
    glEnd();

   glColor3f(0.3f, 0.0f, 0.0f);// sunshade mati color

    glBegin(GL_POLYGON); //uP middle  khuti
    glVertex2f(-5.9876f, -4.3561f);           // E12
    glVertex2f(-5.9876f, -3.8480f);           // F12
    glVertex2f(-4.7298053795947f, -3.8480f);  // G12
    glVertex2f(-4.491633f, -4.3561f);        // G4
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(-4.7298053795947f, -3.8480f);  // G12
    glVertex2f(-0.280748f, -0.711561f);       // Q3
    glVertex2f(4.119304f, -3.848f);            // J12
    glVertex2f( 5.399f, -3.8480f);            // I12
    glVertex2f( 5.399f, -4.3561f);          // H12
    glVertex2f(3.91171f, -4.3561f);        // I4
    glVertex2f(-0.251013f, -1.431846f);    // H4
    glVertex2f(-4.491633f, -4.3561f);      // G4
    glVertex2f(-5.5352f, -4.3561f);        // F4

    glEnd();


    glColor3f(0.90f, 0.65f, 0.47f);
    glBegin(GL_POLYGON); //Palace base
    glVertex2f(14.931f, -14.45f);           // A3
    glVertex2f(14.931f, -15.692f);         // C3
    glVertex2f(-14.261178f, -15.692f);     // G3
    glVertex2f(-14.261178f, -14.45f);      // F3
    glEnd();
//palace middle part
    glColor3f(0.82f, 0.62f, 0.45f);
    glBegin(GL_POLYGON); //Palace Middle part
    glVertex2f(-5.5352f, -14.45f);         // E4
    glVertex2f(-5.5352f, -4.3561f);        // F4
    glVertex2f(-4.491633f, -4.3561f);      // G4
    glVertex2f(-0.251013f, -1.431846f);    // H4
    glVertex2f(3.91171f, -4.3561f);        // I4
    glVertex2f(5.0101f, -4.3561f);         // J4
    glVertex2f(5.0101f, -14.45f);          // K4
    glEnd();
    glColor3f(0.3216f, 0.0706f, 0.0275f);// Door color
    glBegin(GL_POLYGON); //Palace Middle part Door
    glVertex2f(2.23f, -14.45f);            // J3
    glVertex2f(-2.7321f, -14.45f);         // K3
    glVertex2f(-2.7321f, -11.067f);        // H3
    glVertex2f(2.23f, -11.067f);           // I3
    glEnd();
    drawSemiCircleFromPoints(-2.7321f, -11.067f,2.23f, -11.067f, 1);
    glBegin(GL_POLYGON); //Palace Middle part Door
    glVertex2f(-3.3824f, -5.4552f);        // A4
    glVertex2f(-1.4f, -5.4552f);           // C4
    glVertex2f(-1.4f, -6.744f);            // W3
    glVertex2f(-3.3824f, -6.744f);         // Z3
    glEnd();
    drawSemiCircleFromPoints(-3.3824f, -5.4552f,-1.4f, -5.4552f, 1);
    glBegin(GL_POLYGON); //Palace Middle part Door
    glVertex2f(0.897f, -5.4552f);          // B4
    glVertex2f(2.8193f, -5.4552f);         // D4
    glVertex2f(2.8193f, -6.744f);          // U3
    glVertex2f(0.897f, -6.744f);           // V3
    glEnd();
    //semi circle
    drawSemiCircleFromPoints(0.897f, -5.4552f,2.8193f, -5.4552f, 1);

//palace middle upper part
    glColor3f(0.973f, 0.749f, 0.471f);
    glBegin(GL_POLYGON); //Palace Middle part 1

    glVertex2f(3.9516f, 0.651f);           // M3
    glVertex2f(3.96792f, -3.79521f);        // N3
    glVertex2f(-0.280748f, -0.711561f);    // Q3
    glVertex2f(-0.28074f, 0.651f);         // C24
    glEnd();
    glBegin(GL_POLYGON); //Palace Middle part 2
    glVertex2f(-0.280748f, -0.711561f);    // Q3
    glVertex2f(-4.4843f, -3.6944f);        // T3
    glVertex2f(-4.4843f, 0.651f);          // L3
    glVertex2f(-0.28074f, 0.651f);        // C24
    glEnd();
//triangle color semi big windows
    glColor3f(0.878f, 0.353f, 0.183f); // triangle Left
    drawSemiCircleFromPoints(-3.490f, -0.9108035f,-1.13290925759f, -0.910803503927f, 1);
    glBegin(GL_POLYGON);
    glVertex2f(-3.490f, -0.9108035f);                     // B2
    glVertex2f(-1.13290925759f, -0.9108035f);        // M8
    glVertex2f(-1.13290925759f, -1.325465f);          // R3
    glVertex2f(-3.490f,-2.9987f);                         // S3
    glEnd();
    drawSemiCircleFromPoints(0.57141f, -0.87842f,3.0f, -0.87842f, 1);
    glBegin(GL_POLYGON);
    glVertex2f(0.57141f, -0.87842f);   // O8
    glVertex2f(3.0f, -0.87842f);        // Z22
    glVertex2f(3.0f, -3.09f);              // O3
    glVertex2f(0.57141f, -1.365f);   // P3
    glEnd();



//palace left side
   glColor3f(0.922f, 0.706f, 0.533f);// tringle base color
    glBegin(GL_POLYGON);
    glVertex2f(-5.805f, -4.76f);           // O4
    glVertex2f(-5.805f, -5.45f);           // P4
    glVertex2f(-9.962f, -5.45f);           // Q4
    glVertex2f(-9.962f, -4.76f);           // R4
    glEnd();

   glColor3f(0.82f, 0.62f, 0.45f);
    glBegin(GL_POLYGON);
    glVertex2f(-12.27f, -9.409f);          // N5
    glVertex2f(-6.649153f, -9.409f);       // O5
    glVertex2f(-6.3991f, -8.13f);          // Z5
    glVertex2f(-6.3991f, -5.450f);         // W5
    glVertex2f(-9.962f, -5.45f);           // Q4
    glVertex2f(-12.27f, -5.874f);          // L5
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-12.27f, -5.874f);          // L5
    glVertex2f(-9.962f, -5.45f);           // Q4
    glVertex2f(-9.962f, -4.76f);           // R4
    glVertex2f(-12.27f, -1.868f);          // A5
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-12.27f, -1.868f);          // A5
    glVertex2f(-8.26374f, -1.868f);        // K5
    glVertex2f(-9.379669f, -4.76f);        // M4
    glVertex2f(-9.962f, -4.76f);           // R4
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-12.27f, -1.868f);          // A5
    glVertex2f(-8.26374f, -1.868f);        // K5
    glVertex2f(-9.379669f, -4.76f);        // M4
    glVertex2f(-9.962f, -4.76f);           // R4
    glEnd();

    glBegin(GL_TRIANGLES); // left triangle
    glVertex2f(-6.9751076557263f, -3.189f);         // E5
    glVertex2f(-7.486f, -1.868f);                   // F5
    glVertex2f(-6.9751076557263f, -1.868f);         // B5
    glEnd();



    glColor3f(0.737f, 0.220f, 0.137f);
    glBegin(GL_POLYGON);
    glVertex2f(-12.931f, -5.874f);         // I6
    glVertex2f(-12.931f, -6.325f);         // J6
    glVertex2f(-9.4415f, -6.325f);         // K6
    glVertex2f(-9.4415f, -5.874f);         // L6
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-10.223f, -5.874f);         // M6
    glVertex2f(-10.223f, -3.75f);          // N6
    glVertex2f(-10.887f, -3.75f);          // O6
    glVertex2f(-10.887f, -5.874f);         // P6
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-6.413f, -1.868f);          // C5
    glVertex2f(-6.413f, -1.3152f);         // D5
    glVertex2f(-12.882f, -1.3152f);        // W4
    glVertex2f(-12.882f, -1.868f);         // Z4
    glEnd();

    glColor3f(0.82f, 0.62f, 0.45f);// middle wall color
    glBegin(GL_POLYGON);
    glVertex2f(-12.284760f, 0.5758f);      // S4
    glVertex2f(-6.975108f, 0.5758f);       // T4
    glVertex2f(-6.985792f, -1.3152f);      // U4
    glVertex2f(-12.265098f, -1.3152f);     // V4
    glEnd();

glColor3f(0.3f, 0.0f, 0.0f);// sunshade mati color

    glBegin(GL_POLYGON);
    glVertex2f(-12.77f, 0.72f);    // B1
    glVertex2f(-12.77f, 0.5758f);  // C1
    glVertex2f(-6.67f, 0.5758f);   // D1
    glVertex2f(-6.67f, 0.72f);     // E1
    glEnd();
    glColor3f(0.737f, 0.220f, 0.137f);// sunshade red color
    glBegin(GL_POLYGON);
    glVertex2f(-12.99f, 0.72f);    // W
    glVertex2f(-12.99f, 0.975f);   // V
    glVertex2f(-6.296f, 0.975f);   // Z
    glVertex2f(-6.296f, 0.72f);    // A1
    glEnd();

    glColor3f(0.82f, 0.62f, 0.45f);// middle wall color
    glBegin(GL_POLYGON);
    glVertex2f(-9.157f, -14.45f);          // S5
    glVertex2f(-9.157f, -9.409f);          // T5
    glVertex2f(-6.649153f, -9.409f);       // O5
    glVertex2f(-6.667540f, -14.45f);       // U5
    glEnd();

    glColor3f(0.9176f, 0.7255f, 0.3922f);// up wall color
    glBegin(GL_POLYGON);
    glVertex2f(-9.157f, -10.312f);         // Q5
    glVertex2f(-9.157f, -14.45f);          // S5
    glVertex2f(-13.3f, -14.45f);           // D3
    glVertex2f(-13.3f, -10.312f);          // R5
    glEnd();
    glColor3f(0.878f, 0.353f, 0.183f); // triangle color
    glBegin(GL_TRIANGLES); // left triangle
    glVertex2f(-7.8944479833138f, -0.7497f);// L4
    glVertex2f(-9.379669f, -4.76f);        // M4
    glVertex2f(-6.3991f, -4.76f);          // N4
    glEnd();
    glColor3f(0.878f, 0.353f, 0.183f); // triangle color
    glBegin(GL_POLYGON);
    glVertex2f(-9.157f, -9.409f);          // T5
    glVertex2f(-9.157f, -10.312f);         // Q5
    glVertex2f(-13.3f, -10.312f);          // R5
    glVertex2f(-13.244f, -9.409f);         // H5
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-10.35384054f, -9.409f); // R15
    glVertex2f(-10.35384054f, -8.559f); // S15
    glVertex2f(-6.0220f, -8.559f);     // G5
    glVertex2f(-6.022f, -9.409f);      // E6
    glEnd();

// right wall start
    glColor3f(0.82f, 0.62f, 0.45f);// middle wall color
    glBegin(GL_POLYGON);
    glVertex2f(11.8f, 0.5758f);     // N1
    glVertex2f(11.8f, -9.409f);     // P2
    glVertex2f(6.1378f, -9.409f);   // R2
    glVertex2f(5.8607f, -8.0912f);         // B6
    glVertex2f(5.8607f, -4.76f);           // T1
    glVertex2f(6.4697f, -3.189f);          // I5
    glVertex2f(6.4697f, 0.5758f);         // Q1
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(6.1378f, -9.409f);           // R2
    glVertex2f(8.606240f, -9.409f);        // P5
    glVertex2f(8.6109825f, -14.45f);      // Z2
    glVertex2f(6.1378f, -14.45f);        // V5
    glEnd();
    glColor3f(0.9176f, 0.7255f, 0.3922f);// up wall color
    glBegin(GL_POLYGON);
    glVertex2f(8.6109825f, -10.312f);// U2
    glVertex2f(12.734512f, -10.312f);// V2
    glVertex2f(12.776016f, -14.45f);// W2
    glVertex2f(8.6109825f, -14.45f);// Z2
    glEnd();

    glColor3f(0.737f, 0.220f, 0.137f);//sun shade red color
    glBegin(GL_POLYGON);
    glVertex2f(5.96f, -1.868f);      // C2
    glVertex2f(5.96f, -1.3152f);     // D2
    glVertex2f(12.3214f, -1.3152f);  // A2
    glVertex2f(12.3214f, -1.868f);   // O1
    glEnd();
    glColor3f(0.878f, 0.353f, 0.183f); // triangle color
    glBegin(GL_TRIANGLES); // Right down triangle
    glVertex2f(7.3502270f, -0.7497f); // R1
    glVertex2f(8.8463115f, -4.76f);   // S1
    glVertex2f(5.8607f, -4.76f);      // T1
    glEnd();
    glColor3f(0.922f, 0.706f, 0.533f);// tringle base color
    glBegin(GL_POLYGON);
    glVertex2f(9.352f, -4.76f);     // U1
    glVertex2f(9.352f, -5.45f);     // V1
    glVertex2f(5.288f, -5.45f);     // W1
    glVertex2f(5.288f, -4.76f);     // Z1
    glEnd();

    glColor3f(0.3f, 0.0f, 0.0f);// sunshade mati color
    glBegin(GL_POLYGON);
    glVertex2f(12.18f, 0.72f);     // H1
    glVertex2f(12.18f, 0.5758f);   // I1
    glVertex2f(6.1f, 0.5758f);     // J1
    glVertex2f(6.1f, 0.72f);       // K1
    glEnd();
    glColor3f(0.737f, 0.220f, 0.137f);//sun shade red color
    glBegin(GL_POLYGON);
    glVertex2f(12.433f, 0.975f);   // F1
    glVertex2f(12.433f, 0.72f);    // G1
    glVertex2f(5.76f, 0.72f);      // L1
    glVertex2f(5.76f, 0.975f);     // M1
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(12.3332f, -5.874f);  // G2
    glVertex2f(12.3332f, -6.325f);  // H2
    glVertex2f(8.8698f, -6.325f);   // J2
    glVertex2f(8.8698f, -5.874f);   // K2
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(9.64f, -5.874f);     // L2
    glVertex2f(10.25f, -5.874f);    // M2
    glVertex2f(10.25f, -3.75f);     // N2
    glVertex2f(9.64f, -3.75f);      // O2
    glEnd();

    glColor3f(0.878f, 0.353f, 0.183f); // triangle color
    glBegin(GL_POLYGON);
    glVertex2f(5.55922, -8.5625);      // P1
    glVertex2f(5.55922f, -9.409f);     // T2
    glVertex2f(9.8482298f, -9.409f);   // Q2
    glVertex2f(9.80098247f, -8.5625f); // T16
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(12.71693f, -9.409f);         // E2
    glVertex2f(12.71693f, -10.312f);        // V2
    glVertex2f(8.6109825f, -10.312f);      // U2
    glVertex2f(8.606240f, -9.409f);        // P5
    glEnd();




// inner downside  blocks
    for(int i = 0; i < 2; i++){
        float dt = i * 15.6859f;
        for (int i = 0; i < 5; i++) {
    float dx = i * 0.9f;
   glColor3f(0.878f, 0.353f, 0.183f); // triangle color
   glBegin(GL_POLYGON);
   glVertex2f(5.55922f + dx -dt, -8.027057f ); // C17
   glVertex2f(6.038701f+ dx-dt, -8.027057f); // k17
   glVertex2f(6.038701f +dx-dt, -8.5625f);//L17
   glVertex2f(5.55922f + dx-dt, -8.5625f);//p1
   glEnd();
   }
    }

    for(int i = 0; i < 2; i++){
        float dt = i * 22.8859f;
        for (int i = 0; i < 3; i++) {
                float dx = i * 1.2f;
        glColor3f(0.878f, 0.353f, 0.183f); // triangle color
        glBegin(GL_POLYGON);
        glVertex2f(12.0186622f - dx -dt, -8.5625f); // N16
        glVertex2f(12.71693f -dx -dt, -8.5625f); // M16
        glVertex2f(12.71693f -dx -dt, -9.409f);//E2
        glVertex2f(12.0186622f -dx -dt, -9.409f);//O16
        glEnd();
   }
    }



 //up wall
    glColor3f(0.878f, 0.353f, 0.183f); // triangle color
    glBegin(GL_POLYGON);
    glVertex2f(-4.6404f, 0.651f);           // K8
    glVertex2f(-4.6404f, 1.5413f);          // G13
    glVertex2f(4.083f, 1.5413f);            // K13
    glVertex2f(4.083f, 0.651f);             // I8
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-3.36865f, 8.546f);  // O
    glVertex2f(-2.6465536f,  9.033865f); // P
    glVertex2f(2.0262259f,  9.033865f); // T
    glVertex2f(2.82694f, 8.546f);    // U
    glEnd();
     glColor3f(0.973f, 0.749f, 0.471f);
    glBegin(GL_TRIANGLES); //up wall triangle middle
    glVertex2f(-0.268f, 3.8587f);          // C7
    glVertex2f(-3.217416f, 1.5413f);       // D7
    glVertex2f(2.7053913f, 1.5413f);       // E7
    glEnd();

    glColor3f(0.9176f, 0.7255f, 0.3922f);// up wall  deep color
    glBegin(GL_TRIANGLES); //up wall triangle left
    glVertex2f(-1.1749f, 3.682f);          // I7
    glVertex2f(-3.807f, 1.5413f);          // J7
    glVertex2f(-3.807f, 3.682f);           // G7
    glEnd();
    glBegin(GL_TRIANGLES); //up wall triangle right
    glVertex2f(0.623427f, 3.682f);         // K7
    glVertex2f(3.368f, 3.683558f);         // L7
    glVertex2f(3.380815f, 1.5413f);        // N7
    glEnd();
    glColor3f(0.3f, 0.0f, 0.0f);// sunshade color
    glBegin(GL_POLYGON);
    glVertex2f(-4.026f, 4.1357f);          // Q6
    glVertex2f(3.524f, 4.1357f);           // R6
    glVertex2f(3.524f, 3.682f);            // S6
    glVertex2f(-4.026f, 3.682f);           // T6
    glEnd();
    glColor3f(0.737f, 0.220f, 0.137f);// sunshade color
    glBegin(GL_POLYGON);
    glVertex2f(-3.807f, 1.5413f);          // J7
    glVertex2f(-0.268f, 4.382822f);        // F7
    glVertex2f(-0.268f, 3.8587f);          // C7
    glVertex2f(-3.217416f, 1.5413f);       // D7
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-0.268f, 4.382822f);        // F7
    glVertex2f(-0.268f, 3.8587f);          // C7
    glVertex2f(2.7053913f, 1.5413f);       // E7
    glVertex2f(3.380815f, 1.5413f);        // N7
    glEnd();
    glColor3f(0.973f, 0.749f, 0.471f);//up wall middle lite color
    glBegin(GL_POLYGON);
    glVertex2f(-3.36865f, 8.546f);  // O
    glVertex2f(2.82694f, 8.546f);    // U
    glVertex2f(2.82694f, 6.2012063f);          // L8
    glVertex2f(-3.36865f, 6.2012063f);        // J8
    glEnd();
    glColor3f(0.737f, 0.220f, 0.137f);// sunshade color
    glLineWidth(3.0f);           // line thickness
    glBegin(GL_LINES);
        glVertex2f(2.82694f, 6.2012063f);   // L8
        glVertex2f(-3.36865f, 6.2012063f);  // J8
    glEnd();
    glColor3f(0.9176f, 0.7255f, 0.3922f);// up wall  deep color
    glBegin(GL_POLYGON);
    glVertex2f(-3.36865f, 6.2012063f);        // J8
    glVertex2f(2.82694f, 6.2012063f);          // L8
    glVertex2f(2.82694f, 5.608f);            // B7
    glVertex2f(2.501f, 5.0f);              // V6
    glVertex2f(-3.088f, 5.0f);             // U6
    glVertex2f(-3.36865f, 5.621f);          // A7
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-3.088f, 5.0f);             // U6
    glVertex2f(2.501f, 5.0f);              // V6
    glVertex2f(2.501f, 4.1357f);           // W6
    glVertex2f(-3.088f, 4.1357f);          // Z6
    glEnd();
//4th floor windows
    for(int i = 0; i < 2; i++){
        float dt = i * 18.6859f;

        for (int i = 0; i < 3; i++) {
                float dx = i * 1.7f;
        glColor3f(0.878f, 0.353f, 0.183f); // triangle color
        glBegin(GL_POLYGON);
        glVertex2f(-11.65f+dx +dt, -0.4761f);//R8
        glVertex2f(-11.65f+dx+dt, 0.1865f);//N8
        glVertex2f(-11.120f+dx+dt, 0.1865f);//P8
        glVertex2f(-11.120f+dx+dt, -0.4761f);//Q8
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(-11.81831f + dx+dt, -0.65361f);// R16
        glVertex2f(-11.81831f +dx+dt, -0.4761f);//S16
        glVertex2f(-10.95808f+dx+dt, -0.4761f);//P16
        glVertex2f(-10.95808f+dx+dt, -0.6536f);//Q16
        glEnd();
        }
    }

//3rd floor window
     for(int i = 0; i < 2; i++){
        float dt = i * 18.6859f;

        for (int i = 0; i < 3; i++) {
                float dx = i * 1.7f;
        glColor3f(0.878f, 0.353f, 0.183f); // triangle color
        glBegin(GL_POLYGON);
        glVertex2f(-11.65f+dx +dt,  -2.431f);//C9
        glVertex2f(-11.120f+dx+dt,-2.431f);//N8
        glVertex2f(-11.120f+dx+dt, -3.18f);//P8
        glVertex2f(-11.65f+dx+dt, -3.18f);//Q8
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(-11.88209f + dx+dt, -3.18f);// R16
        glVertex2f(-10.881001f +dx+dt,  -3.18f);//S16
        glVertex2f(-10.881001f+dx+dt,-3.346276f);//P16
        glVertex2f(-11.88209f+dx+dt, -3.346276f);//Q16
        glEnd();
        }
    }
//2nd Floor windows
    for(int i = 0; i < 2; i++){
        float dt = i * 20.6859f;

        for (int i = 0; i < 2; i++) {
                float dx = i * 1.7f;
        glColor3f(0.878f, 0.353f, 0.183f); // triangle color
        glBegin(GL_POLYGON);
        glVertex2f(-11.65f+dx +dt,  -6.753f);//k9
        glVertex2f(-11.120f+dx+dt, -6.753f);//L9
        glVertex2f(-11.120f+dx+dt, -7.3827f);//N9
        glVertex2f(-11.65f+dx+dt, -7.3827);//M9
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(-11.88209f + dx+dt,-7.3827f);// B9
        glVertex2f(-10.881001f +dx+dt,  -7.3827f);//W8
        glVertex2f(-10.881001f+dx+dt,-7.57772f);//Z8
        glVertex2f(-11.88209f+dx+dt, -7.57772f);//A9
        glEnd();
        }
    }
    //2N FLOOR SEMI WINDOWS
    for (int i = 0; i < 2; i++)
    {
        float dt = i * 15.0f;


    for (int i = 0; i < 2; i++)
   {
        float dx = i * 1.0f;
        glColor3f(0.3216f, 0.0706f, 0.0275f);// Door color
        glBegin(GL_POLYGON);
        glVertex2f(-8.611f + dx +dt, -10.59f ); //M14
        glVertex2f(-8.054f + dx+dt, -10.59f ); //N14
        glVertex2f(-8.054f + dx+dt,  -11.094f );//K14
        glVertex2f(-8.611f + dx+dt,   -11.094f );//L14
        glEnd();
        for (int i = 0; i < 2; i++)
            {
                float dx = i * 1.0f;
                drawSemiCircleFromPoints(-8.611f + dx+dt, -10.59f,-8.054f + dx+dt, -10.59f, 1);
                }
        }
   }
   //3rd floor semi window
   for (int i = 0; i < 2; i++)
    {
        float dt = i * 15.0f;


    for (int i = 0; i < 1; i++)
   {
        float dx = i * 1.0f;
        glColor3f(0.3216f, 0.0706f, 0.0275f);// Door color
        glBegin(GL_POLYGON);
        glVertex2f(-8.424f + dx +dt,  -6.201f ); //E15
        glVertex2f(-7.208f + dx+dt, -6.201f ); //F15
        glVertex2f(-7.208f + dx+dt,  -7.077f );//C15
        glVertex2f(-8.424f + dx+dt,   -7.077f );//D15
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.922f, 0.706f, 0.533f);// tringle base color
        glVertex2f(-8.84516f + dx +dt, -7.077f ); //G9
        glVertex2f(-6.848644f + dx+dt, -7.077f ); //H9
        glVertex2f(-6.848644f + dx+dt,  -7.40093f );//I9
        glVertex2f(-8.84516f + dx+dt,   -7.40093f );//J9
        glEnd();
        for (int i = 0; i < 1; i++)
            {
                float dx = i * 1.0f;
                glColor3f(0.3216f, 0.0706f, 0.0275f);// Door color
                drawSemiCircleFromPoints(-8.424f + dx +dt,  -6.201f,-7.208f + dx+dt, -6.201f, 1);
                }
        }
   }
   //1ST FLOOR SEMI WINDOW
   for (int i = 0; i < 2; i++)
    {
        float dt = i * 15.0f;


    for (int i = 0; i < 1; i++)
   {
        float dx = i * 1.0f;
        glColor3f(0.3216f, 0.0706f, 0.0275f);// Door color
        glBegin(GL_POLYGON);
        glVertex2f(-8.424f + dx +dt,  -13.606f ); //E15
        glVertex2f(-7.208f + dx+dt,  -13.606f ); //F15
        glVertex2f(-7.208f + dx+dt,  -14.45f );//C15
        glVertex2f(-8.424f + dx+dt,    -14.45f );//D15
        glEnd();

        for (int i = 0; i < 1; i++)
            {
                float dx = i * 1.0f;
                glColor3f(0.3216f, 0.0706f, 0.0275f);// Door color
                drawSemiCircleFromPoints(-8.424f + dx +dt,  -13.606f,-7.208f + dx+dt,  -13.606f, 1);
                }
        }
   }
   //7th floor square windows
   for (int i = 0; i <6; i++) {
                float dx = i * 1.0f;
        glColor3f(0.3216f, 0.0706f, 0.0275f);// Door color
        glBegin(GL_POLYGON);
        glVertex2f(-3.14f+dx, 8.546f);//W10
        glVertex2f(-2.662f+dx, 8.546f);//Z10
        glVertex2f(-2.662f+dx, 7.402f);//A11
        glVertex2f(-3.14f+dx, 7.402f);//B11
        glEnd();

        }

    //6th floor semi windows
    for (int i = 0; i < 5; i++)
   {
        float dx = i * 1.15f;
        glColor3f(0.878f, 0.353f, 0.183f); // triangle color
        glBegin(GL_POLYGON);
        glVertex2f(-2.9116f+dx, 5.608); //M12
        glVertex2f(-2.212f+dx, 5.608); //N12
        glVertex2f(-2.212f+dx, 5.221);//K12
        glVertex2f(-2.9116f+dx, 5.221);//L12
        glEnd();

        for (int i = 0; i < 5; i++)
            {
                float dx = i * 1.15f;
                glColor3f(0.878f, 0.353f, 0.183f); // triangle color
                drawSemiCircleFromPoints(-2.9116f+dx, 5.608f,-2.212f+dx, 5.608f, 1);
                }
        }
        //5th floor blocks
   for (int i = 0; i <6; i++) {
                float dx = i * 1.55f;
        glColor3f(0.878f, 0.353f, 0.183f); // triangle color
        glBegin(GL_POLYGON);
        glVertex2f(-4.6404f+dx, 1.8568f);//W10
        glVertex2f(-3.6405f+dx, 1.8568f);//Z10
        glVertex2f(-3.6405f+dx, 1.5413f);//A11
        glVertex2f(-4.6404f+dx, 1.5413f);//B11
        glEnd();

        }
        //5th floor circle
        drawCircle(-0.2648f, 2.6495f, 0.532f); // circle k





}

void doggo(){
    glColor3f(0.0f, 0.0f, 0.0f);//black dog
    glBegin(GL_POLYGON);
     glVertex2f(4.1175574528607f, -13.7236038748292f); // I17
     glVertex2f(4.2360041066532f, -13.7404215983271f); // J17
     glVertex2f(4.2787076111745f, -13.7320451308721f); // N17
     glVertex2f(4.3175924489007f, -13.6964954559628f); // O17
     glVertex2f(4.4f, -13.7f);                         // P17
     glVertex2f(4.4797315791943f, -13.7269345191367f); // Q17
     glVertex2f(4.5585708660376f, -13.7565715340863f); // R17
     glVertex2f(4.5942949178885f, -13.782652107242f);  // S17
     glVertex2f(4.6300189697394f, -13.8194020057795f); // T17
     glVertex2f(4.6460331998795f, -13.8525954625231f); // U17
     glVertex2f(4.6583518384487f, -13.9592887163418f); // V17
     glVertex2f(4.68665048109f, -14.01888315733f);     // W17
     glVertex2f(4.7f, -14.1f);                         // Z17
     glVertex2f(4.722659951434f, -14.288966142696f);   // A18
     glVertex2f(4.8f, -14.4f);                         // B18
     glVertex2f(5.1101177802319f, -14.8298189976369f); // C18
     glVertex2f(5.2208410177458f, -14.9380246817145f); // D18
     glVertex2f(5.2904919813913f, -15.0127134727148f); // E18
     glVertex2f(5.3800432203642f, -15.1448551798691f); // F18
     glVertex2f(5.4705205381982f, -15.3181459754711f); // G18
     glVertex2f(5.514993812213f, -15.3692683000951f);  // P18
     glVertex2f(5.561238268751f, -15.5495063337154f);  // Q18
     glVertex2f(5.586672719847f, -15.662989540069f);   // R18
     glVertex2f(5.6f, -15.8f);                         // S18
     glVertex2f(5.561238268751f, -15.8387772518715f);  // T18
     glVertex2f(5.3655131760843f, -15.4714268180436f); // Q29
    glVertex2f(4.8536753803826f, -14.837621392952f); // R29
    glVertex2f(4.4175029033386f, -14.3588974231073f); // J21
     glVertex2f(4.3969791396697f, -14.0307272233841f); // K21
     glEnd();
     glBegin(GL_POLYGON);
     glVertex2f(5.3655131760843f, -15.4714268180436f); // Q29
     glVertex2f(5.561238268751f, -15.5495063337154f);  // Q18
     glVertex2f(5.586672719847f, -15.662989540069f);   // R18
     glVertex2f(5.6f, -15.8f);                         // S18
     glVertex2f(5.561238268751f, -15.8387772518715f);  // T18
     glVertex2f(5.0377091875162f, -15.7685723401789f); // T19

     glEnd();

     glBegin(GL_POLYGON);
     glVertex2f(5.561238268751f, -15.8387772518715f);  // T18
     glVertex2f(5.5737946844986f, -15.8832703732372f); // L21
    glVertex2f(5.5679969272162f, -15.9432495128659f); // M21
    glVertex2f(5.5556766929912f, -15.9871877198032f); // N21
    glVertex2f(5.5310362245412f, -16.0387976771582f); // O21
    glVertex2f(5.5027721577897f, -16.0743667018218f); // U21
    glVertex2f(5.4737833713779f, -16.1008691123554f); // H22
    glVertex2f(5.4411709866646f, -16.1203972043275f); // G26
    glVertex2f(5.420154116516f, -16.1343458414505f); // E28
    glVertex2f(5.3824686941807f, -16.143412455804f); // F28
    glVertex2f(5.3496911906885f, -16.1440880373177f); // M19
    glVertex2f(4.5901492831504f, -16.1397387847556f); // N19
    glVertex2f(4.6248230479043f, -16.0513130637388f); // P19
    glVertex2f(4.6751000067974f, -16.0079344081456f);  // Q19
    glVertex2f(5.1f, -16.0f);                         // R19

     glEnd();

     glBegin(GL_POLYGON);
     glVertex2f(5.1f, -16.0f);                         // R19
     glVertex2f(5.0523129766491f, -15.9389516062156f); // S19
     glVertex2f(4.8714933064434f, -15.6324265034842f); // W19
     glVertex2f(4.7569300151168f, -15.5435154953967f); // Z19
     glVertex2f(4.6774748291967f, -15.4901688905442f); // A20
     glVertex2f(4.5499769727203f, -15.4314876252064f); // B20
     glVertex2f(4.3135871152031f, -15.1923756892649f); // C20
     glVertex2f(4.2164959948216f, -14.8182309253058f); // G20
     glVertex2f(4.2413949082803f, -14.6000958123916f); // I20
     glVertex2f(4.8536753803826f, -14.837621392952f); // R29
     glVertex2f(5.3655131760843f, -15.4714268180436f); // Q29
     glEnd();//
     glBegin(GL_POLYGON);
     glVertex2f(4.2413949082803f, -14.6000958123916f); // I20
     glVertex2f(4.2872470838504f, -14.2738311697197f); // K20
     glVertex2f(4.722659951434f, -14.288966142696f);   // A18
     glVertex2f(4.8477609240542f, -14.7222491344541f);   // A18
     glEnd();//

     glBegin(GL_POLYGON);
     glVertex2f(4.3969791396697f, -14.0307272233841f); // K21
     glVertex2f(4.18195500948f, -14.0382045930526f);   // N20
     glVertex2f(4.1099529009238f, -13.9966559416416f); // O20
     glVertex2f(4.0615154008326f, -13.9553050900405f); // P20
     glVertex2f(4.0185466507517f, -13.9139542384393f); // Q20
     glVertex2f(3.9966716507105f, -13.892902895806f);  // R20
     glVertex2f(3.9841716506869f, -13.8748588878346f); // S20
     glVertex2f(3.9758098179942f, -13.8562770268683f); // H17
    glEnd();//
    // front legs
    glBegin(GL_POLYGON);
    glVertex2f(4.5499769727203f, -15.4314876252064f); // B20
    glVertex2f(4.322831260026f, -16.1321295545021f);  // T20
    glVertex2f(4.1058883752249f, -16.127384682823f);  // U20
    glVertex2f(4.1221028176753f, -16.0961768398068f); // V20 (2nd)
    glVertex2f(4.0337039266741f, -16.0927280391779f); // W20
    glVertex2f(4.0f, -16.1f);                         // Z20
    glVertex2f(3.9966719588223f, -16.0674368345657f); // A21
    glVertex2f(4.070735894526f, -16.0007600224061f);  // B21
    glVertex2f(4.1615239447434f, -15.9927128209386f); // C21
    glVertex2f(4.2391716192714f, -15.8179735890723f); // D21
    glVertex2f(4.2683239969354f, -15.6139964769009f); // E21
    glVertex2f(4.2988963314732f, -15.3583998264274f); // F21
    glVertex2f(4.3135871152031f, -15.1923756892649f); // C20
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(4.1099529009238f, -13.9966559416416f); // O20
glVertex2f(4.0615154008326f, -13.9553050900405f); // P20
glVertex2f(4.0185466507517f, -13.9139542384393f); // Q20
glVertex2f(3.9966716507105f, -13.892902895806f);  // R20
glVertex2f(3.9841716506869f, -13.8748588878346f); // S20                      // G17
     glVertex2f(3.9758098179942f, -13.8562770268683f); // H17
     glVertex2f(3.9633711939967f, -13.6795948392241f); //G17
     glVertex2f(4.1175574528607f, -13.7236038748292f); // I17
     glVertex2f(4.2360041066532f, -13.7404215983271f); // J17
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(4.1175574528607f, -13.7236038748292f); // I17
     glVertex2f(4.2360041066532f, -13.7404215983271f); // J17
     glVertex2f(4.3969791396697f, -14.0307272233841f); //k21
     glVertex2f(4.18195500948f, -14.0382045930526f); // N20 (2nd)

    glEnd();

    // S6
    drawSemiCircleFromPoints(5.561238268751f, -15.8387772518715f,5.1136534144313f, -15.9805395999226f, 1);
    // t6
    drawSemiCircleFromPoints(5.0523129766491f, -15.9389516062156f,5.0377091875162f, -15.7685723401789f, 1);
    // C7
    drawSemiCircleFromPoints(4.988404117127f, -15.8393989651328f,5.0041093317412f, -15.5161947199233f, 1);
    // d7
    drawSemiCircleFromPoints(4.3135871152031f, -15.1923756892649f,4.8477609240542f, -14.722491344541f, 1);
    // e7
    drawSemiCircleFromPoints(4.3043603356979f, -15.0755537387715f,4.5289113306573f, -14.6433617456616f, 1);
    // f7
    drawSemiCircleFromPoints(4.2164959948216f, -14.8182309253058f,4.6631921776108f, -14.6482416315855f, 1);
    // g7
    glColor3f(0.82f, 0.62f, 0.45f);
    drawSemiCircleFromPoints(3.9743911974697f, -14.0032594097415f,4.115609774762f, -14.4686183618902f, 1);
    //eyes
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_POLYGON);
    glVertex2f(4.2922399522337f, -13.7769407918978f); // S29
    glVertex2f(4.3355044931162f, -13.800256674708f);  // T29
    glVertex2f(4.3678086836418f, -13.7780510720316f); // U29
    glVertex2f(4.3753078707281f, -13.7458529481508f); // V29
    glVertex2f(4.3603094965555f, -13.7203165050729f); // W29
    glVertex2f(4.340119377477f, -13.707548283534f);   // Z29
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);//black dog
    glBegin(GL_LINES);
    glVertex2f(5.6f, -15.8f);                         // S18
    glVertex2f(5.7365057846376f, -15.837475086711f);  // A30
    glEnd();
    glBegin(GL_LINES);

    glVertex2f(5.7365057846376f, -15.837475086711f);  // A30
    glVertex2f(5.8f, -15.9f);                         // B30
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(5.8f, -15.9f);                         // B30
    glVertex2f(5.8407272109061f, -16.0134062167514f); // C30
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(5.8407272109061f, -16.0134062167514f); // C30
    glVertex2f(5.9022349378842f, -16.1465877264082f); // D30
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(5.9022349378842f, -16.1465877264082f); // D30
    glVertex2f(6.1f, -16.2f);
    glEnd();                       // E30
    glBegin(GL_LINES);
    glVertex2f(6.1f, -16.2f);                         // E30
    glVertex2f(6.2456530801787f, -16.176183617443f);  // F30
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); // white belt
    glBegin(GL_POLYGON);
    glVertex2f(4.2872470838504f, -14.2738311697197f); // K20
    glVertex2f(4.2739253849667f, -14.4056950364523f); // J20
    glVertex2f(4.7f, -14.1f);                         // Z17
    glVertex2f(4.722659951434f, -14.288966142696f);   // A18
    glEnd();

}
void suv268() { //SobjSuv
    glColor3f(0.502f, 0.0f, 0.0f);//meroon truck
        glPushMatrix();
    glTranslatef(V, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
     glVertex2f(19.3514489f, -14.8726f);    // R21
     glVertex2f(19.3514488523538f, -13.1877503f);    // S21
     glVertex2f(17.3083816f, -13.1315749f);    // T21
     glVertex2f(16.6808681f, -13.7635484f);    // U21
     glVertex2f(16.2205f, -14.51695f);    // V21
     glVertex2f(13.2514339f, -15.1398463f);    // W21
     glVertex2f(12.731690f, -15.672f);      // B3
     glVertex2f(12.9303805f, -16.8251089277018f);    // Z21=
     glVertex2f(24.39544f, -16.8251089277018f);         // Q21
     glVertex2f(24.39544f, -14.8726f);         // P21
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(19.3514489f, -14.8726f);    // R21
     glVertex2f(19.3514488523538f, -13.1877503f);    // S21
     glVertex2f(24.0097196149843f, -13.187750324804f);  // L11
     glVertex2f(24.39544f, -14.8726f);         // P21
    glEnd();
    glColor3f(0.6f, 0.8f, 0.9f);   // Light sky-blue glass
        glBegin(GL_POLYGON);
     glVertex2f(18.753122f, -14.5512587735755f);         // E22
     glVertex2f(18.753122f, -13.44053f);                // F22
     glVertex2f(17.4297366159573f, -13.44053f);          // G22
     glVertex2f(16.8624297082772f, -14.5512587735755f);  // L22
    glEnd();
    glBegin(GL_POLYGON);
     glVertex2f(19.46438f, -13.44053f);         // E22
     glVertex2f(23.7167f, -13.44053f);                // F22
     glVertex2f(24.0724f, -14.5512587735755f);          // G22
     glVertex2f(19.46438f, -14.5512587735755f);  // L22
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f); // black lines
    glLineWidth(1.0f);           // optional: line thickness
    glBegin(GL_LINE_LOOP);
    glVertex2f(16.7087f, -16.4509f);   // I22
    glVertex2f(19.05972f, -16.4509f);   // J22
    glVertex2f(19.05972f, -14.706525f);  // K22
    glVertex2f(16.7087f, -14.706525f);   // L22
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(16.7087f, -14.706525f);   // L22
    glVertex2f(16.7087f, -14.43161153381f);   // F2
    glVertex2f(17.3622007, -13.299388);   // L2
    glVertex2f(19.05972, -13.299388);   // G5
    glVertex2f(19.05972f, -14.706525f);  // K22
    glEnd();
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(15.7177079f, -16.8251089f);   // B22
    glVertex2f(20.8399692f, -16.8251089f);   // C22
    glEnd();
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(18.2f, -15.3f);    // I13
    glVertex2f(18.765f, -15.3f);  // J13
    glEnd();
    //semicircle for front wheel
    drawSemiCircleFromPoints(13.3389939165829f, - 16.8251089277018f,15.7177078838903f, - 16.8251089277018f, 1);
    //for rare wheel
    drawSemiCircleFromPoints(20.8399692490737f, - 16.8251089277018f,23.189496f, - 16.8251089277018f, 1);

    // Rare wheel tyre (O22, P22)
    glColor3f(0.2f, 0.2f, 0.2f);  // 20% black (dark grey)
    drawCircle(22.0169f, -16.8468f, 0.9651f);
    // front wheel tyre
    drawCircle(14.5552f, -16.6912f, 0.9692f);
    // front wheel rim
    glColor3f(1.0f, 1.0f, 1.0f);  // Pure white
    drawCircle(14.5551583f, -16.6911657f, 0.5910f);  // e2
    //rare while rim
    drawCircle(22.0168756f, -16.8468462f, 0.6066f);  // f2


 glPopMatrix();
}


void treeS1268(float baseX, float baseY) { // shohan tree code
    glPushMatrix();

    glTranslatef(baseX + 11.1799f, baseY + 15.066f, 0.0f);

    glColor3f(0.690f, 0.871f, 0.498f); // tree color (পাতা)

    glBegin(GL_TRIANGLES);
    glVertex2f(-11.1723f, -9.233f);   //U18
    glVertex2f(-12.1352f, -10.8125f);  //V18
    glVertex2f(-10.32588f, -10.8125f); //W18
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-12.0289f, -11.14627f);
    glVertex2f(-11.1628f, -10.1217f);
    glVertex2f(-10.3693f, -11.14627f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-12.181f, -11.6298f);
    glVertex2f(-11.19586f, -10.6753f);
    glVertex2f(-10.1908f, -11.6298f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-12.3331f, -12.094f);
    glVertex2f(-11.19586f, -10.6753f);
    glVertex2f(-10.0916407f, -12.094f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-12.7419169f, -12.8008f);
    glVertex2f(-11.1447123f, -11.2115461f);
    glVertex2f(-9.71048f, -12.8008f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2f(-9.30555f, -13.649f);
    glVertex2f(-13.109f, -13.649f);
    glVertex2f(-11.1799f, -12.421f);
    glEnd();

    // Trunk color
    glColor3f(0.396f, 0.263f, 0.129f);
    glLineWidth(3.0f);

    glBegin(GL_LINES);
    glVertex2f(-11.1799f, -15.066f); //I18
    glVertex2f(-11.1799f, -11.4668f); //J18
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-11.1799f, -12.421f);
    glVertex2f(-11.8523317f, -11.9521729f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-11.1799f, -13.019f);
    glVertex2f(-10.5159004f, -12.5992727f);
    glEnd();

    glPopMatrix();
}
void drawAllTrees() {
    //SobjTree1  at R17
    treeS1268(-28.0f, -16.0f);
    // SobjTree2 at O18
    treeS1268(-14.0546f, -16.0f);
    // SobjTree3 at I18 (original)
    treeS1268(-11.1799f, -15.066f);
    // SobjTree4 at M19
    treeS1268(11.8235f, -15.066f);
    // SobjTree5 at T19
    treeS1268(14.1765f,  -16.0f);

   //SobjTree6R17
    treeS1268(26.441f, -16.0f);
}
void lampPost(float baseX, float baseY) { //Shohan DAY Lamp post code
    glPushMatrix();
    // Translate so that new L10 = (baseX, baseY)
    glTranslatef(baseX + 24.31032f, baseY + 15.87511f, 0.0f);
    // White part (lamp light)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-24.76265f, -7.55161f);     // R10
    glVertex2f(-24.76265f, -6.6f);         // S10
    glVertex2f(-23.85358f, -6.6f);         // T10
    glVertex2f(-23.85358f, -7.55161f);     // U10
    glVertex2f(-24.144692f, -7.87664f);    // P10
    glVertex2f(-24.45878f, -7.87664f);     // O10
    glEnd();
    // Lamp head (circle bulb)
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-24.31032f, -5.835851f, 0.1812f);
    // Lamp cap
    glBegin(GL_TRIANGLES);
    glVertex2f(-24.6471f, -6.380439f);     // V10
    glVertex2f(-23.91594f, -6.380439f);    // C11
    glVertex2f(-24.31032f, -6.100917f);    // D11
    glEnd();
   // Pole
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(-24.31032f, -15.87511f);    // L10
    glVertex2f(-24.31032f, -8.16925f);     // M10
    glEnd();

    // Extra details
    glBegin(GL_LINES);
    glVertex2f(-24.31032f, -6.100917f);    // D11
    glVertex2f(-24.31032f, -7.9691733f);   // H11
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.872296f, -15.66339f);   // U7
    glVertex2f(-23.7205f, -15.66339f);     // V7
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-25.148059f, -15.803893f);  // S7
    glVertex2f(-23.53294f, -15.803893f);   // T7
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.034f, -15.548578f);     // B8
    glVertex2f(-24.58965f, -15.548578f);   // W7
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.83459f, -14.07425f);    // C8
    glVertex2f(-23.77953f, -14.07425f);    // D8
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.719959f, -13.81336f);   // E8
    glVertex2f(-23.89087f, -13.81336f);    // K10
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.5941f, -13.57281f);     // Z7
    glVertex2f(-24.034f, -13.57281f);      // A8
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.31032f, -7.9691733f);   // H11
    glVertex2f(-24.76265f, -7.55161f);     // R10
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-23.85358f, -7.55161f);     // U10
    glVertex2f(-24.31032f, -7.9691733f);   // H11
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.76265f, -7.55161f);     // R10
    glVertex2f(-24.76265f, -6.6f);         // S10
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-23.85358f, -6.6f);         // T10
    glVertex2f(-23.85358f, -7.55161f);     // U10
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.31032f, -6.100917f);    // D11
    glVertex2f(-24.31032f, -5.94717f);     // E11
    glEnd();

    // Base polygons
    glBegin(GL_POLYGON);
    glVertex2f(-24.5941f, -15.567645f);    // W7
    glVertex2f(-24.5941f, -13.57281f);     // Z7
    glVertex2f(-24.034f, -13.57281f);      // A8
    glVertex2f(-24.034f, -15.548578f);     // B8
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-24.45878f, -8.149902f);    // N10
    glVertex2f(-24.45878f, -7.87664f);     // O10
    glVertex2f(-24.144692f, -7.87664f);    // P10
    glVertex2f(-24.144692f, -8.149902f);   // Q10
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-24.76265f, -6.6f);         // S10
    glVertex2f(-23.85358f, -6.6f);         // T10
    glVertex2f(-23.91594f, -6.380439f);    // C11
    glVertex2f(-24.6471f, -6.380439f);     // V10
    glEnd();

    glPopMatrix();
}
void lampPostNight(float baseX, float baseY) { // Shohan Night lamp post code
    glPushMatrix();
    // Translate so that new L10 = (baseX, baseY)
    // Original base L10 was (-24.31032f, -15.87511f)
    glTranslatef(baseX + 24.31032f, baseY + 15.87511f, 0.0f);
    // yellow part (lamp light)
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-24.76265f, -7.55161f);     // R10
    glVertex2f(-24.76265f, -6.6f);         // S10
    glVertex2f(-23.85358f, -6.6f);         // T10
    glVertex2f(-23.85358f, -7.55161f);     // U10
    glVertex2f(-24.144692f, -7.87664f);    // P10
    glVertex2f(-24.45878f, -7.87664f);     // O10
    glEnd();

    // Lamp head (circle bulb)
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-24.31032f, -5.835851f, 0.1812f);

    // Lamp cap
    glBegin(GL_TRIANGLES);
    glVertex2f(-24.6471f, -6.380439f);     // V10
    glVertex2f(-23.91594f, -6.380439f);    // C11
    glVertex2f(-24.31032f, -6.100917f);    // D11
    glEnd();

    // Pole
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(-24.31032f, -15.87511f);    // L10
    glVertex2f(-24.31032f, -8.16925f);     // M10
    glEnd();

    // Extra details
    glBegin(GL_LINES);
    glVertex2f(-24.31032f, -6.100917f);    // D11
    glVertex2f(-24.31032f, -7.9691733f);   // H11
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.872296f, -15.66339f);   // U7
    glVertex2f(-23.7205f, -15.66339f);     // V7
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-25.148059f, -15.803893f);  // S7
    glVertex2f(-23.53294f, -15.803893f);   // T7
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.034f, -15.548578f);     // B8
    glVertex2f(-24.58965f, -15.548578f);   // W7
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.83459f, -14.07425f);    // C8
    glVertex2f(-23.77953f, -14.07425f);    // D8
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.719959f, -13.81336f);   // E8
    glVertex2f(-23.89087f, -13.81336f);    // K10
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.5941f, -13.57281f);     // Z7
    glVertex2f(-24.034f, -13.57281f);      // A8
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.31032f, -7.9691733f);   // H11
    glVertex2f(-24.76265f, -7.55161f);     // R10
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-23.85358f, -7.55161f);     // U10
    glVertex2f(-24.31032f, -7.9691733f);   // H11
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.76265f, -7.55161f);     // R10
    glVertex2f(-24.76265f, -6.6f);         // S10
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-23.85358f, -6.6f);         // T10
    glVertex2f(-23.85358f, -7.55161f);     // U10
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-24.31032f, -6.100917f);    // D11
    glVertex2f(-24.31032f, -5.94717f);     // E11
    glEnd();

    // Base polygons
    glBegin(GL_POLYGON);
    glVertex2f(-24.5941f, -15.567645f);    // W7
    glVertex2f(-24.5941f, -13.57281f);     // Z7
    glVertex2f(-24.034f, -13.57281f);      // A8
    glVertex2f(-24.034f, -15.548578f);     // B8
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-24.45878f, -8.149902f);    // N10
    glVertex2f(-24.45878f, -7.87664f);     // O10
    glVertex2f(-24.144692f, -7.87664f);    // P10
    glVertex2f(-24.144692f, -8.149902f);   // Q10
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-24.76265f, -6.6f);         // S10
    glVertex2f(-23.85358f, -6.6f);         // T10
    glVertex2f(-23.91594f, -6.380439f);    // C11
    glVertex2f(-24.6471f, -6.380439f);     // V10
    glEnd();

    glPopMatrix();
}
void drawAllLampPosts() {
    //SobjLamp1
    lampPost(-24.31032f, -15.87511f);
    //SobjLamp2
    lampPost(-7.624247f, -15.68853f);
    //SobjLamp3
    lampPost(7.12588f, -15.76047f);
    //SobjLamp4
    lampPost(22.443958f, -15.76047f);
}
void drawNightAllLampPosts() {
    //SobjLamp1
    lampPostNight(-24.31032f, -15.87511f);
    //SobjLamp2
    lampPostNight(-7.624247f, -15.68853f);
    //SobjLamp3
    lampPostNight(7.12588f, -15.76047f);
    //SobjLamp4
    lampPostNight(22.443958f, -15.76047f);
}

void bus268() { //SobjBus
      glPushMatrix();
    glTranslatef(W, 0.0f, 0.0f);
    glColor3f(0.133f, 0.545f, 0.133f);   // Forest Green

    glBegin(GL_POLYGON);
    glVertex2f(-25.91924f, -13.254f);       // Q9
    glVertex2f(-25.91924f, -17.9189352f);   // O9
    glVertex2f(-11.64338f, -17.9189352f);   // P9
    glVertex2f(-11.64338f, -16.0f);         // T9
    glVertex2f(-12.012591229149f, -13.254f);// R9
    glEnd();

    glColor3f(0.6f, 0.8f, 0.9f);   // Light sky-blue glass
        glBegin(GL_POLYGON);
        glVertex2f(-25.3318f, -13.59169f);      // C10
        glVertex2f(-25.3318f, -15.56674f);      // D10
        glVertex2f(-11.74416f, -15.56674f); // E10
        glVertex2f(-12.000855f, -13.59169f); // F10

    glEnd();
    glColor3f(0.6f, 0.6f, 0.6f);

    glLineWidth(4.0f);     // optional: line thickness
    glBegin(GL_LINE_LOOP);
    glVertex2f(-21.6953f, -13.1954f);     // G10
    glVertex2f(-13.587795f, -13.1954f);   // H10
    glEnd();

        for (int i = 0; i < 4; i++) {
                float dx = i * 2.5f;
                glColor3f(0.3f, 0.3f, 0.3f);// ashe color
    glLineWidth(1.0f);           // optional: line thickness
    glBegin(GL_LINE_LOOP);
    glVertex2f(-22.78325f+dx, -13.59169f);   // I10
    glVertex2f(-22.78325f+dx, -15.56674f);   // J10
    glEnd();
    }
    // Rare wheel tyre (, )
    glColor3f(0.2f, 0.2f, 0.2f);  // 20% black (dark grey)
    drawCircle(-22.6182411861375f, -17.97391f, 0.8792f);
    // front wheel tyre
    drawCircle(-13.6126f, -17.97391f, 0.8791f);
    // front wheel rim
    glColor3f(1.0f, 1.0f, 1.0f);  // Pure white
    // Circle h1 (center U9, through B10)
    drawCircle(-13.6126f, -17.97391f, 0.5057f);
    //rare while rim
    // Circle g1 (center V9, through A10)
    drawCircle(-22.6182411861375f, -17.97391f, 0.5061f);

 glPopMatrix();
}



//.................................end Scenario 2...............



///.....................// Scenario 3............................

//cloud variables
float cloudgPos1 = 0.0f;
float cloudgPos2 = 0.0f;
float cloudgPos3 = 0.0f;
float cloudgPos4 = 0.0f;
float cloudgSpeed = 0.1f; // slow drifting speed
//Blue car Variables
float _carMove1 = 0.0f;
float carSpeed1 = 0.20f; // Car speed
float _carAngle1 = 0.0f;
//Red car variables
float _carMove2 = 0.0f; // Car 2 movement
float carSpeed2 = 0.20f; // Car 2 speed
float _carAngle2 = 0.0f; // Car 2 wheel rotation
//plane variables
float planemove=0.0;
float planespeed=0.15;
//Day And Night
bool isDayG = true;
int showLight = 0;   // 0 = off, 1 = on
void drawCircle1(float cx, float cy, float r, int num_segments) {
 glBegin(GL_POLYGON);
 for (int i = 0; i < num_segments; i++) {
 float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
 float x = r * cosf(theta);
 float y = r * sinf(theta);
 glVertex2f(x + cx, y + cy);
 }
 glEnd();
}

//.................Scenario 3 vari.............
void drawCircle1(float cx, float cy, float r, int num_segments);
void DayandNightTransation();
void Roadg();
void GrassPartg();
void Skyg();
void cloudg1();
void cloudg2();
void cloudg3();
void cloudg4();
void Sung();
void Moong();
void BuildingSideGrassg();
void Treeg();
void BuildingBigg();
void Carg1();
void Carg2();
void LampPostg();
void DayScene();
void Starsg();
void NightScene();
void Planeg();
void LampPostg2();
void Building1();
void Building2();
void Lightg();

///.................................................................Cloud animation.................??
///ANIM_01
void updateClouds(int value) {
 if(currentScenario == 3){cloudgPos1+= cloudgSpeed;
 if (cloudgPos1 > 60) cloudgPos1 = -60;
 cloudgPos2 += cloudgSpeed;
 if (cloudgPos2 > 60) cloudgPos2 = -60;
 cloudgPos3 += cloudgSpeed;
 if (cloudgPos3 > 60) cloudgPos3 = -60;
 cloudgPos4 += cloudgSpeed;
 if (cloudgPos4 > 60) cloudgPos4 = -60;}

 glutPostRedisplay();
 glutTimerFunc(20, updateClouds, 0);
}
///ANIM_02
void updateCar1(int value) {
 // Move car
 if(currentScenario == 3){_carMove1 += carSpeed1;
 if (_carMove1 > 35.0f) {
 _carMove1 = -35.0f; // Reset to left edge
 }

 _carAngle1 -= 5.0f;
 if (_carAngle1 < -360.0f) {
 _carAngle1 += 360.0f;
 }}
 glutPostRedisplay();
 glutTimerFunc(20, updateCar1, 0);
}
///ANIM_03
void updateCar2(int value) {
 // Move car
 if(currentScenario == 3){_carMove2 -= carSpeed2; // Car 2 moves LEFT
 if (_carMove2 < -60.0f) { // If out of screen
 _carMove2 = 30.0f; // Reset to right side
 }
 // Rotate wheels
 _carAngle2 -= 5.0f;
 if (_carAngle2 < -360.0f) {
 _carAngle2 += 360.0f;
 }}
 glutPostRedisplay();
 glutTimerFunc(20, updateCar2, 0);
}

///ANIM_04
void updatePlaneg(int value) {
 // Move car
 if(currentScenario == 3){planemove += planespeed; // Car 2 moves LEFT
 if (planemove > 60.0f) { // If out of screen
 planemove = -60.0f; // Reset to right side
 }
 }
 glutPostRedisplay();
 glutTimerFunc(20, updatePlaneg, 0);
}


void DayandNightTransation() {

 if (isDayG)
 DayScene();
 else
 NightScene();

}



///....................................................................Road......................//
///OBJ_01
void Roadg(){
 // Road (Dark Gray)
glColor3f(0.2f, 0.2f, 0.2f);
glBegin(GL_QUADS);
 glVertex2f(-30.0f, -20.0f);
 glVertex2f(-30.0f, -12.0f);
 glVertex2f(30.0f, -12.0f);
 glVertex2f(30.0f, -20.0f);
glEnd();
glColor3f(0.0f, 0.5f, 0.0f);
}
///.............................................................LowerGrass.................
///OBJ_02
void GrassPartg(){
glColor3f(0.0f, 0.5f, 0.0f);
////Grass part//
glBegin(GL_QUADS);
 glVertex2f(-30.0f, -12.0f);
 glVertex2f(30.0f, -12.0f);
 glVertex2f(30.0f, -10.0f);
 glVertex2f(-30.0f, -10.0f);
glEnd();
}
///......................................................SKY.....................///
///OBJ_03
void Skyg(){

glColor3f(0.53f, 0.81f, 0.92f);

glBegin(GL_QUADS);
 glVertex2f(-30.0f, -10.0f);
 glVertex2f(-30.0f, 26.7742f);
 glVertex2f(30.0f, 26.7742f);
 glVertex2f(30.0f, -10.0f);
glEnd();
}
///................................................Clouds..............//
///OBJ_04
void cloudg1() {
 glPushMatrix();
 glTranslatef(cloudgPos1, 0.0f, 0.0f);
 glColor3f(0.9f, 0.9f, 0.9f);
 drawCircle1(-27.65225903352f, 25.3830989325321f, 1.39f, 100);
 drawCircle1(-25.7474436814346f, 24.5040162549081f, 1.43f, 100);
 drawCircle1(-27.3442819412418f, 23.0424730312177f, 1.22f, 100);
 drawCircle1(-28.3914040549877f, 23.7200226342297f, 1.24f, 100);
 glPopMatrix();
}
///OBJ_05.......................
void cloudg2() {
 glPushMatrix();
 glTranslatef(cloudgPos2, 0.0f, 0.0f);
 glColor3f(0.9f, 0.9f, 0.9f);
 drawCircle1(-26.9431130019689f, 8.3800524170014f, 1.74f, 100);
 drawCircle1(-24.7869688882709f, 8.5563977502651f, 1.5f, 100);
 drawCircle1(-25.4527971139064f, 7.469303818741f, 1.4f, 100);
 drawCircle1(-27.4021871270372f, 6.1503969706f, 1.3f, 100);
 glPopMatrix();
}
///OBJ_06................
void cloudg3() {
 glPushMatrix();
 glTranslatef(cloudgPos3, 0.0f, 0.0f);
 glColor3f(0.9f, 0.9f, 0.9f);
 drawCircle1(7.7830464418251f, 24.3979551999847f, 1.15f, 100);
 drawCircle1(9.4247396595125f, 24.6075330575618f, 1.15f, 100);
 drawCircle1(8.9420755026682f, 23.1881193857895f, 1.31f, 100);
 drawCircle1(7.1193832261642f, 22.8959805540153f, 1.25f, 100);
 glPopMatrix();
}
///OBJ_07............
void cloudg4() {
 glPushMatrix();
 glTranslatef(cloudgPos4, 0.0f, 0.0f);
 glColor3f(0.9f, 0.9f, 0.9f);
 drawCircle1(22.1951514052582f, 14.9774637849285f, 1.5f, 100);
 drawCircle1(24.3904420663329f, 15.2906751728646f, 1.7f, 100);
 drawCircle1(24.9909623384184f, 13.4411172588441f, 1.6f, 100);
 drawCircle1(22.3475820201871f, 12.9118828363611f, 1.8f, 100);
 glPopMatrix();
}


///............................................Sun..........................
///OBJ_08...............
void Sung(){

glColor3f(1.0f, 0.55f, 0.0f);

drawCircle1(25.1135813211313f, 23.044367369624f, 3.33f, 100);
}
void Moong(){
glColor3f(0.9f, 0.9f, 1.0f);
drawCircle1(25.1135813211313f, 23.044367369624f, 3.33f, 100);
}
///............................................Building Side Grass.......
///OBJ_09
void BuildingSideGrassg(){
// builiding side grass

glColor3f(0.0f, 0.8f, 0.0f);

drawCircle1(-20.2153707858518f, -6.8852545048653f, 3.06f, 100);

glColor3f(0.0f, 0.8f, 0.0f);

drawCircle1(-23.6701075005248f, -5.503359818996f, 3.70f, 100);

glColor3f(0.0f, 0.8f, 0.0f);

drawCircle1(-26.20f, -8.20f, 1.51f, 100);
}
///................................................Trees............................
///OBJ_10
void Treeg(){
//Treee

glColor3f(0.55f, 0.27f, 0.07f);

glBegin(GL_QUADS);
 glVertex2f(24.21f, -9.0f);
 glVertex2f(25.87f, -9.0f);
 glVertex2f(25.59f, -2.02f);
 glVertex2f(24.37f, -2.01f);
glEnd();
//tree leaf

glColor3f(0.0f, 0.8f, 0.0f);

drawCircle1(24.9529186948063f, 1.5347462601062f, 3.88f, 100);

glColor3f(0.0f, 0.8f, 0.0f);

drawCircle1(22.4875420365928f, 0.1201858824427f, 3.2f, 100);

glColor3f(0.0f, 0.8f, 0.0f);

drawCircle1(27.0545512559063f, -0.3648062470419f, 2.78f, 100);
}
///...........................................................Building Big,..............................
///OBJ_11
void BuildingBigg(){
//buliding lower part above grass
glColor3f(0.76f, 0.58f, 0.36f);
glBegin(GL_QUADS);
 glVertex2f(-28.0f, -10.0f);
 glVertex2f(-28.0f, -9.0f);
 glVertex2f(29.0f, -9.0f);
 glVertex2f(29.0f, -10.0f);
glEnd();
//lower part structure //
glBegin(GL_QUADS);
 glColor3f(0.76f, 0.58f, 0.36f);
 glVertex2f(-18.0f, -9.0f);
 glVertex2f(-18.0f, 5.0f);
 glVertex2f(17.99f, 5.0f);
 glVertex2f(17.99f, -9.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.7f, 0.55f, 0.3f);
 glVertex2f(-18.0f, 5.0f);
 glVertex2f(-18.0f, 6.0f);
 glVertex2f(18.0f, 6.0f);
 glVertex2f(17.99f, 5.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.7f, 0.55f, 0.3f);
 glVertex2f(-10.0f, 5.0f);
 glVertex2f(-8.0f, 5.0f);
 glVertex2f(-8.0f, -1.99f);
 glVertex2f(-10.0f, -1.99f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.7f, 0.55f, 0.3f);
 glVertex2f(8.0f, 5.0f);
 glVertex2f(10.0f, 5.0f);
 glVertex2f(10.0f, -1.99f);
 glVertex2f(8.0f, -1.99f);
glEnd();
// column of the building //...
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-6.0f, 5.0f);
 glVertex2f(-5.01f, 5.0f);
 glVertex2f(-5.0f, -9.0f);
 glVertex2f(-6.0f, -9.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-4.04f, 5.0f);
 glVertex2f(-3.03f, 5.0f);
 glVertex2f(-3.0f, -9.0f);
 glVertex2f(-4.0f, -9.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(3.99f, 5.0f);
 glVertex2f(4.99f, 5.0f);
 glVertex2f(5.0f, -9.0f);
 glVertex2f(4.0f, -9.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(5.96f, 5.0f);
 glVertex2f(7.0f, 5.0f);
 glVertex2f(7.0f, -9.0f);
 glVertex2f(6.0f, -9.0f);
glEnd();
//colum er majhe bown
glBegin(GL_QUADS);
glColor3f(0.7f, 0.55f, 0.3f);
 glVertex2f(-18.0f, -3.0f);
 glVertex2f(-18.0f, -2.0f);
 glVertex2f(17.99f, -1.99f);
 glVertex2f(17.99f, -2.99f);
glEnd();
// colum //
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-1.00f, 5.0f);
 glVertex2f(-0.02f, 5.0f);
 glVertex2f(0.0f, -1.99f);
 glVertex2f(-1.0f, -1.99f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(0.99f, 5.0f);
 glVertex2f(1.99f, 5.0f);
 glVertex2f(1.99f, -1.99f);
 glVertex2f(0.99f, -1.99f);
glEnd();
// left side windows //
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-17.0f, -2.0f);
 glVertex2f(-17.0f, 2.5f);
 glVertex2f(-16.5f, 4.0f);
 glVertex2f(-16.0f, 2.5f);
 glVertex2f(-16.0f, -1.99f);
glEnd();
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-15.0f, -2.0f);
 glVertex2f(-15.0f, 2.5f);
 glVertex2f(-14.5f, 4.0f);
 glVertex2f(-14.0f, 2.5f);
 glVertex2f(-14.0f, -1.99f);
glEnd();
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-13.0f, -2.0f);
 glVertex2f(-13.0f, 2.5f);
 glVertex2f(-12.5f, 4.0f);
 glVertex2f(-12.0f, 2.5f);
 glVertex2f(-12.0f, -1.99f);
glEnd();
//Right side windows
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(12.0f, -2.0f);
 glVertex2f(12.0f, 2.5f);
 glVertex2f(12.5f, 4.0f);
 glVertex2f(13.0f, 2.5f);
 glVertex2f(13.0f, -1.99f);
glEnd();
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(14.0f, -2.0f);
 glVertex2f(14.0f, 2.5f);
 glVertex2f(14.5f, 4.0f);
 glVertex2f(15.0f, 2.5f);
 glVertex2f(15.0f, -1.99f);
glEnd();
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(16.0f, -2.0f);
 glVertex2f(16.0f, 2.5f);
 glVertex2f(16.5f, 4.0f);
 glVertex2f(17.0f, 2.5f);
 glVertex2f(17.0f, -1.99f);
glEnd();
//left side big window//
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-17.0f, -9.0f);
 glVertex2f(-17.0f, -6.0f);
 glVertex2f(-16.0f, -4.0f);
 glVertex2f(-15.0f, -6.0f);
 glVertex2f(-15.0f, -9.0f);
glEnd();
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(15.0f, -9.0f);
 glVertex2f(15.0f, -6.0f);
 glVertex2f(16.0f, -4.0f);
 glVertex2f(17.0f, -6.0f);
 glVertex2f(17.0f, -9.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-14.0f, -9.0f);
 glVertex2f(-14.0f, -3.0f);
 glVertex2f(-13.0f, -3.0f);
 glVertex2f(-13.0f, -9.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-12.0f, -9.0f);
 glVertex2f(-12.0f, -3.0f);
 glVertex2f(-11.0f, -3.0f);
 glVertex2f(-11.0f, -9.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(11.0f, -9.0f);
 glVertex2f(11.0f, -3.0f);
 glVertex2f(12.0f, -3.0f);
 glVertex2f(12.0f, -9.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(13.0f, -9.0f);
 glVertex2f(13.0f, -3.0f);
 glVertex2f(14.0f, -3.0f);
 glVertex2f(14.0f, -9.0f);
glEnd();
//Main door
glBegin(GL_POLYGON);
 glColor3f(0.7f, 0.55f, 0.3f);
 glVertex2f(-2.0f, -9.0f);
 glVertex2f(-2.0f, -6.0f);
 glVertex2f(0.5f, -4.0f);
 glVertex2f(3.0f, -6.0f);
 glVertex2f(3.0f, -9.0f);
glEnd();
glBegin(GL_POLYGON);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-1.0f, -9.0f);
 glVertex2f(-1.0f, -6.5f);
 glVertex2f(0.5f, -5.0f);
 glVertex2f(2.0f, -6.5f);
 glVertex2f(2.0f, -9.0f);
glEnd();
// Building upper middle part //


glColor3f(0.0f, 0.0f, 0.35f);

drawCircle1(-0.0104052967522f, 20.8869907869479f, 5.23f, 100);
glColor3f(0.76f, 0.58f, 0.36f);

glBegin(GL_QUADS);
 glVertex2f(-6.02f, 7.54f);
 glVertex2f(-6.0f, 14.0f);
 glVertex2f(6.0f, 14.0f);
 glVertex2f(6.0f, 7.54f);
glEnd();

glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(-5.0f, 9.0f);
 glVertex2f(-5.0f, 13.0f);
 glVertex2f(-4.0f, 13.0f);
 glVertex2f(-4.0f, 9.0f);
glEnd();

glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(-3.0f, 9.0f);
 glVertex2f(-3.0f, 13.0f);
 glVertex2f(-2.0f, 13.0f);
 glVertex2f(-2.0f, 9.0f);
glEnd();

glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(-1.0f, 9.0f);
 glVertex2f(-1.0f, 13.0f);
 glVertex2f(0.0f, 13.0f);
 glVertex2f(0.0f, 9.0f);
glEnd();

glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(1.0f, 9.0f);
 glVertex2f(1.0f, 13.0f);
 glVertex2f(2.0f, 13.0f);
 glVertex2f(2.0f, 9.0f);
glEnd();

glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(3.0f, 9.0f);
 glVertex2f(3.0f, 13.0f);
 glVertex2f(4.0f, 13.0f);
 glVertex2f(4.0f, 9.0f);
glEnd();
// Set pure black color
glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(-6.5f, 14.0f);
 glVertex2f(-6.5f, 15.5f);
 glVertex2f(6.5f, 15.5f);
 glVertex2f(6.5f, 14.0f);
glEnd();
// Set sandy brown color
glColor3f(0.76f, 0.58f, 0.36f);

glBegin(GL_QUADS);
 glVertex2f(-4.98f, 15.5f);
 glVertex2f(-5.0f, 19.0f);
 glVertex2f(5.0f, 19.0f);
 glVertex2f(5.01f, 15.5f);
glEnd();
// Set pure black color
glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(-5.2f, 19.0f);
 glVertex2f(-5.2f, 19.6f);
 glVertex2f(5.2f, 19.6f);
 glVertex2f(5.2f, 19.0f);
glEnd();
// Set pure black color
glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(-4.0f, 16.0f);
 glVertex2f(-4.0f, 18.5f);
 glVertex2f(-3.0f, 18.5f);
 glVertex2f(-3.0f, 16.0f);
glEnd();
// Set pure black color
glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(-2.0f, 16.0f);
 glVertex2f(-2.0f, 18.5f);
 glVertex2f(-1.0f, 18.5f);
 glVertex2f(-1.0f, 16.0f);
glEnd();
// Set pure black color
glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(0.0f, 16.0f);
 glVertex2f(0.0f, 18.5f);
 glVertex2f(1.0f, 18.5f);
 glVertex2f(1.0f, 16.0f);
glEnd();
// Set pure black color
glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(2.0f, 16.0f);
 glVertex2f(2.0f, 18.5f);
 glVertex2f(3.0f, 18.5f);
 glVertex2f(3.0f, 16.0f);
glEnd();
//builiding triangle//
glBegin(GL_TRIANGLES);
 glColor3f(0.7f, 0.55f, 0.3f); // Deep yellow-brown
 glVertex2f(-10.0f, 5.0f);
 glVertex2f(0.0f, 11.4f);
 glVertex2f(10.0f, 5.0f);
glEnd();
glBegin(GL_TRIANGLES);
 glColor3f(0.0f, 0.0f, 0.0f); // Pure black
 glVertex2f(-7.0f, 6.0f);
 glVertex2f(0.0f, 10.0f);
 glVertex2f(7.0f, 6.0f);
glEnd();

glColor3f(0.0f, 0.0f, 0.35f);
// Draw the circle
drawCircle1(-13.9622452066649f, 19.4336780999729f, 3.72f, 100);
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(-18.6053f, 5.9961f);
 glVertex2f(-18.5900f, 6.9852f);
 glVertex2f(-9.0f, 7.0f);
 glVertex2f(-9.0f, 6.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.7f, 0.55f, 0.3f);
 glVertex2f(-18.0f, 6.98f);
 glVertex2f(-18.0f, 12.0f);
 glVertex2f(-10.0f, 12.0f);
 glVertex2f(-10.0f, 6.99f);
glEnd();
glColor3f(0.0f, 0.0f, 0.0f);
drawCircle1(-14.0f, 10.0f, 1.5f, 100);
glColor3f(0.7f, 0.55f, 0.3f);

glBegin(GL_QUADS);
 glVertex2f(-17.8f, 12.0f);
 glVertex2f(-17.8f, 16.0f);
 glVertex2f(-10.2f, 16.0f);
 glVertex2f(-10.2f, 12.0f);
glEnd();

glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(-18.0f, 16.0f);
 glVertex2f(-18.0f, 16.5f);
 glVertex2f(-10.0f, 16.5f);
 glVertex2f(-10.0f, 16.0f);
glEnd();

glColor3f(0.7f, 0.55f, 0.3f);
// Draw rectangle
glBegin(GL_QUADS);
 glVertex2f(-17.8f, 16.5f); //
 glVertex2f(-17.8f, 19.0f);
 glVertex2f(-10.2f, 19.0f);
 glVertex2f(-10.2f, 16.5f);
glEnd();

glColor3f(0.76f, 0.58f, 0.36f);

glBegin(GL_POLYGON);
 glVertex2f(-17.0f, 12.0f);
 glVertex2f(-17.0f, 14.0f);
 glVertex2f(-16.5f, 15.0f);
 glVertex2f(-16.0f, 14.0f);
 glVertex2f(-16.0f, 12.0f);
glEnd();

glColor3f(0.76f, 0.58f, 0.36f);

glBegin(GL_POLYGON);
 glVertex2f(-15.0f, 12.0f);
 glVertex2f(-15.0f, 14.0f);
 glVertex2f(-14.5f, 15.0f);
 glVertex2f(-14.0f, 14.0f);
 glVertex2f(-14.0f, 12.0f);
glEnd();

glColor3f(0.76f, 0.58f, 0.36f);

glBegin(GL_POLYGON);
 glVertex2f(-13.0f, 12.0f);
 glVertex2f(-13.0f, 14.0f);
 glVertex2f(-12.5f, 15.0f);
 glVertex2f(-12.0f, 14.0f);
 glVertex2f(-12.0f, 12.0f);
glEnd();


glColor3f(0.0f, 0.0f, 0.35f);

drawCircle1(14.0377547933351f, 19.4336780999729f, 3.72f, 100);
glBegin(GL_QUADS);
 glColor3f(0.0f, 0.0f, 0.0f);
 glVertex2f(9.0f, 6.0f);
 glVertex2f(9.0f, 7.0f);
 glVertex2f(18.5f, 7.0f);
 glVertex2f(18.0f, 6.0f);
glEnd();
glBegin(GL_QUADS);
 glColor3f(0.7f, 0.55f, 0.3f);
 glVertex2f(10.0f, 7.0f);
 glVertex2f(10.0f, 12.0f);
 glVertex2f(18.0f, 12.0f);
 glVertex2f(18.0f, 7.0f);
glEnd();
glColor3f(0.0f, 0.0f, 0.0f);
drawCircle1(14.0f, 10.0f, 1.5f, 100);

glColor3f(0.7f, 0.55f, 0.3f);

glBegin(GL_QUADS);
 glVertex2f(10.2f, 12.0f);
 glVertex2f(10.2f, 16.0f);
 glVertex2f(17.8f, 16.0f);
 glVertex2f(17.8f, 12.0f);
glEnd();

glColor3f(0.0f, 0.0f, 0.0f);

glBegin(GL_QUADS);
 glVertex2f(10.0f, 16.0f);
 glVertex2f(10.0f, 16.5f);
 glVertex2f(18.0f, 16.5f);
 glVertex2f(18.0f, 16.0f);
glEnd();

glColor3f(0.7f, 0.55f, 0.3f);

glBegin(GL_QUADS);
 glVertex2f(10.2f, 16.5f);
 glVertex2f(10.2f, 19.0f);
 glVertex2f(17.8f, 19.0f);
 glVertex2f(17.8f, 16.5f);
glEnd();

glColor3f(0.76f, 0.58f, 0.36f);

glBegin(GL_POLYGON);
 glVertex2f(12.0f, 12.0f);
 glVertex2f(12.0f, 14.0f);
 glVertex2f(12.5f, 15.0f);
 glVertex2f(13.0f, 14.0f);
 glVertex2f(13.0f, 12.0f);
glEnd();

glColor3f(0.76f, 0.58f, 0.36f);

glBegin(GL_POLYGON);
 glVertex2f(14.0f, 12.0f);
 glVertex2f(14.0f, 14.0f);
 glVertex2f(14.5f, 15.0f);
 glVertex2f(15.0f, 14.0f);
 glVertex2f(15.0f, 12.0f);
glEnd();

glColor3f(0.76f, 0.58f, 0.36f);

glBegin(GL_POLYGON);
 glVertex2f(16.0f, 12.0f);
 glVertex2f(16.0f, 14.0f);
 glVertex2f(16.5f, 15.0f);
 glVertex2f(17.0f, 14.0f);
 glVertex2f(17.0f, 12.0f);
glEnd();
}

///............................................................Cars.......................
///OBJ_12
void Carg1() {
 glPushMatrix();
 glTranslatef(_carMove1, 0.0f, 0.0f);

 glColor3f(0.0f, 0.4f, 0.7f);
 glBegin(GL_POLYGON);
 glVertex2f(-5.4557f, -14.0f);
 glVertex2f(-5.45f, -12.0f);
 glVertex2f(-3.34f, -12.0f);
 glVertex2f(-1.57f, -10.0f);
 glVertex2f(2.5f, -10.0f);
 glVertex2f(4.0f, -12.0f);
 glVertex2f(6.0f, -12.0f);
 glVertex2f(6.0f, -14.0f);
 glEnd();

 glColor3f(0.7f, 0.85f, 0.9f);
 glBegin(GL_QUADS);
 glVertex2f(-2.81f, -12.0f);
 glVertex2f(-1.18f, -10.0f);
 glVertex2f(0.45f, -10.0f);
 glVertex2f(0.45f, -12.0f);
 glEnd();

 glColor3f(0.7f, 0.85f, 0.9f);
 glBegin(GL_QUADS);
 glVertex2f(0.76f, -12.0f);
 glVertex2f(0.76f, -10.0f);
 glVertex2f(2.15f, -10.0f);
 glVertex2f(3.59f, -12.0f);
 glEnd();

 glPushMatrix();
 glTranslatef(-2.0f, -14.0f, 0.0f);
 glRotatef(_carAngle1, 0.0f, 0.0f, 1.0f);
 glColor3f(0.0f, 0.0f, 0.0f);
 drawCircle1(0, 0, 0.9f, 50);
 glPopMatrix();
 glPushMatrix();
 glTranslatef(2.2710f, -14.0347f, 0.0f);
 glRotatef(_carAngle1, 0.0f, 0.0f, 1.0f);
 glColor3f(0.0f, 0.0f, 0.0f);
 drawCircle1(0, 0, 0.9f, 50);
 glPopMatrix();
 glPopMatrix();
}
///OBJ_13
void Carg2() {
 glPushMatrix();
 glTranslatef(_carMove2, 0.0f, 0.0f); // Apply movement

 glColor3f(0.7f, 0.1f, 0.1f);
 glBegin(GL_POLYGON);
 glVertex2f(16.2251f, -18.8750f);
 glVertex2f(16.2251f, -16.5030f);
 glVertex2f(18.5972f, -16.4717f);
 glVertex2f(19.5648f, -14.5678f);
 glVertex2f(23.4975f, -14.5054f);
 glVertex2f(24.4651f, -16.4405f);
 glVertex2f(26.4002f, -16.4405f);
 glVertex2f(26.4002f, -18.8439f);
 glEnd();

 glColor3f(0.6f, 0.85f, 0.9f);
 glBegin(GL_POLYGON);
 glVertex2f(18.90f, -16.47f);
 glVertex2f(19.80f, -14.56f);
 glVertex2f(21.45f, -14.53f);
 glVertex2f(21.56f, -16.44f);
 glEnd();

 glColor3f(0.6f, 0.85f, 0.9f);
 glBegin(GL_POLYGON);
 glVertex2f(21.93f, -16.45f);
 glVertex2f(21.79f, -14.53f);
 glVertex2f(23.26f, -14.50f);
 glVertex2f(24.15f, -16.44f);
 glEnd();

 glPushMatrix();
 glTranslatef(19.4399f, -18.8750f, 0.0f);
 glRotatef(_carAngle2, 0.0f, 0.0f, 1.0f);
 glColor3f(0.0f, 0.0f, 0.0f);
 drawCircle1(0, 0, 0.9f, 50);
 glPopMatrix();

 glPushMatrix();
 glTranslatef(23.3720f, -18.7825f, 0.0f);
 glRotatef(_carAngle2, 0.0f, 0.0f, 1.0f);
 glColor3f(0.0f, 0.0f, 0.0f);
 drawCircle1(0, 0, 0.9f, 50);
 glPopMatrix();
 glPopMatrix();
}

///.........................................................Lamp Post.......................
///OBJ_14
void LampPostg(){

glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
 glVertex2f(-25.0f, -12.0f);
 glVertex2f(-25.0f, -1.5f);
 glVertex2f(-24.0f, -1.5f);
 glVertex2f(-24.0f, -12.0f);
glEnd();

glColor3f(1.0f, 1.0f, 0.6f);
glBegin(GL_POLYGON);
 glVertex2f(-25.0f, -1.5f);
 glVertex2f(-26.0f, 0.0f);
 glVertex2f(-23.0f, 0.0f);
 glVertex2f(-24.0f, -1.5f);
glEnd();

glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_TRIANGLES);
 glVertex2f(-26.0f, 0.0f);
 glVertex2f(-24.5f, 1.5f);
 glVertex2f(-23.0f, 0.0f);
glEnd();
}
void DayScene(){
 glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
 glClear(GL_COLOR_BUFFER_BIT);
Sung();
}
///................................STARs..........
///OBJ_15
void Starsg()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(5.0f);

    glBegin(GL_POINTS);
        glVertex2f(-21.0265997704159f, 13.4024441205689f);
        glVertex2f(-23.9145543877325f, 14.0302603417247f);
        glVertex2f(-27.3047619819737f, 16.3531803600011f);
        glVertex2f(-23.3495197886923f, 20.3084225532826f);
        glVertex2f(-18.0758635309837f, 24.3892279907953f);
        glVertex2f(-10.4792872549988f, 23.8241933917551f);
        glVertex2f(-7.2146429049887f, 20.3084225532826f);
        glVertex2f(-7.4029877713354f, 10.9539608580613f);
        glVertex2f(8.6063258681369f, 19.1783533552022f);
        glVertex2f(8.7946707344837f, 14.2186052080715f);
        glVertex2f(15.0f, 25.0f);
        glVertex2f(20.0f, 20.0f);
        glVertex2f(22.8577540883732f, 9.9494549042121f);
        glVertex2f(27.943065479735f, 9.1332938167095f);
    glEnd();
}
void NightScene(){
 glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // dark navy sky
 glClear(GL_COLOR_BUFFER_BIT);
Moong();
Starsg();
}
///......................................................................Plane..........................
///OBJ_16
void Planeg(){
glPushMatrix();
 glTranslatef(planemove, 0.0f, 0.0f); // Apply movement

glColor3f(0.2f, 0.4f, 0.8f); // deeper blue

glBegin(GL_QUADS);
    glVertex2f(-27.0f, 17.0f);
    glVertex2f(-27.0f, 19.0f);
    glVertex2f(-22.0f, 19.0f);
    glVertex2f(-20.0f, 17.0f);
glEnd();


glColor3f(0.2f, 0.4f, 0.8f);

glBegin(GL_POLYGON);
    glVertex2f(-26.849444f, 18.226596f);
    glVertex2f(-27.987031f, 19.809325f);
    glVertex2f(-27.492428f, 20.328658f);
    glVertex2f(-26.317746f, 18.745929f);
glEnd();

glColor3f(0.2f, 0.4f, 0.8f);

glBegin(GL_POLYGON);
    glVertex2f(-24.7f, 18.4f);
    glVertex2f(-25.563718f, 20.133467f);
    glVertex2f(-24.8f, 20.2f);
    glVertex2f(-23.9f, 18.4f);
glEnd();

glColor3f(0.2f, 0.4f, 0.8f);

glBegin(GL_POLYGON);
    glVertex2f(-24.6f, 17.4f);
    glVertex2f(-23.8f, 17.4f);
    glVertex2f(-24.4f, 16.2f);
    glVertex2f(-25.166845f, 16.193858f);
glEnd();


glColor3f(0.75f, 0.94f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(-26.0f, 17.7f);
    glVertex2f(-26.0f, 18.4f);
    glVertex2f(-25.5f, 18.4f);
    glVertex2f(-25.5f, 17.7f);
glEnd();

glColor3f(0.75f, 0.94f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(-25.2f, 17.7f);
    glVertex2f(-25.2f, 18.4f);
    glVertex2f(-24.7f, 18.4f);
    glVertex2f(-24.7f, 17.7f);
glEnd();

glColor3f(0.75f, 0.94f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(-24.4f, 17.7f);
    glVertex2f(-24.4f, 18.4f);
    glVertex2f(-23.9f, 18.4f);
    glVertex2f(-23.9f, 17.7f);
glEnd();

glColor3f(0.75f, 0.94f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(-23.6f, 17.7f);
    glVertex2f(-23.6f, 18.4f);
    glVertex2f(-23.1f, 18.4f);
    glVertex2f(-23.1f, 17.7f);
glEnd();

glColor3f(0.75f, 0.94f, 1.0f);
glBegin(GL_QUADS);
    glVertex2f(-22.8f, 17.7f);
    glVertex2f(-22.8f, 18.4f);
    glVertex2f(-22.3f, 18.4f);
    glVertex2f(-22.3f, 17.7f);
glEnd();


glColor3f(1.0f, 0.0f, 0.0f);


glLineWidth(2.0f);  // increase for thicker line


glBegin(GL_LINES);
    glVertex2f(-26.523507f, 17.359941f);
    glVertex2f(-20.999841f, 17.349669f);
glEnd();
 glPopMatrix();



}
///OBJ_17
void LampPostg2(){
// Pole
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_QUADS);
    glVertex2f(19.98f, -12.0f);
    glVertex2f(19.98f, -1.5f);
    glVertex2f(20.98f, -1.5f);
    glVertex2f(20.98f, -12.0f);
glEnd();

// Light box
glColor3f(1.0f, 1.0f, 0.6f);
glBegin(GL_POLYGON);
    glVertex2f(19.98f, -1.5f);
    glVertex2f(18.98f, 0.0f);
    glVertex2f(21.98f, 0.0f);
    glVertex2f(20.98f, -1.5f);
glEnd();

// Top cover
glColor3f(0.0f, 0.0f, 0.0f);
glBegin(GL_TRIANGLES);
    glVertex2f(18.98f, 0.0f);
    glVertex2f(20.48f, 1.5f);
    glVertex2f(21.98f, 0.0f);
glEnd();



}
///.......................................Building 1......................
///OBJ_18
void Building1(){

// Deep Pink Building
glColor3f(1.0f, 0.43f, 0.63f); // Deep Pink
glBegin(GL_QUADS);
    glVertex2f(-29.0f, -10.0f);
    glVertex2f(-29.0f,  4.0f);
    glVertex2f(-19.0f,  4.0f);
    glVertex2f(-19.0f, -10.0f);
glEnd();
// Glass Window
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(-28.0f, 0.0f);
    glVertex2f(-28.0f, 2.0f);
    glVertex2f(-26.0f, 2.0f);
    glVertex2f(-26.0f, 0.0f);
glEnd();
// Glass Window (shifted down by 4)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(-28.0f, -4.0f);
    glVertex2f(-28.0f, -2.0f);
    glVertex2f(-26.0f, -2.0f);
    glVertex2f(-26.0f, -4.0f);
glEnd();
// Glass Window (shifted down again by 4)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(-28.0f, -8.0f);
    glVertex2f(-28.0f, -6.0f);
    glVertex2f(-26.0f, -6.0f);
    glVertex2f(-26.0f, -8.0f);
glEnd();
// Glass Window (shifted right by 6)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(-22.0f, -8.0f);
    glVertex2f(-22.0f, -6.0f);
    glVertex2f(-20.0f, -6.0f);
    glVertex2f(-20.0f, -8.0f);
glEnd();
// Glass Window (shifted up by 4)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(-22.0f, -4.0f);
    glVertex2f(-22.0f, -2.0f);
    glVertex2f(-20.0f, -2.0f);
    glVertex2f(-20.0f, -4.0f);
glEnd();
// Glass Window (shifted up again by 4)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(-22.0f, 0.0f);
    glVertex2f(-22.0f, 2.0f);
    glVertex2f(-20.0f, 2.0f);
    glVertex2f(-20.0f, 0.0f);
glEnd();




}

void Building2(){

// Deep Blue Building
glColor3f(0.0f, 0.0f, 0.30f);   // Deep Blue
glBegin(GL_QUADS);
    glVertex2f(19.0f, -10.0f);
    glVertex2f(19.0f,  4.0f);
    glVertex2f(29.0f,  4.0f);
    glVertex2f(29.0f, -10.0f);
glEnd();
// Glass Window (shifted right by 48)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(20.0f, -4.0f);
    glVertex2f(20.0f, -2.0f);
    glVertex2f(22.0f, -2.0f);
    glVertex2f(22.0f, -4.0f);
glEnd();
// Glass Window (shifted down by 4)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(20.0f, -8.0f);
    glVertex2f(20.0f, -6.0f);
    glVertex2f(22.0f, -6.0f);
    glVertex2f(22.0f, -8.0f);
glEnd();
// Glass Window (shifted right by 6)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(26.0f, -8.0f);
    glVertex2f(26.0f, -6.0f);
    glVertex2f(28.0f, -6.0f);
    glVertex2f(28.0f, -8.0f);
glEnd();
// Glass Window (shifted up by 4)
glColor3f(0.68f, 0.85f, 0.90f);   // Glass (light cyan)
glBegin(GL_QUADS);
    glVertex2f(26.0f, -4.0f);
    glVertex2f(26.0f, -2.0f);
    glVertex2f(28.0f, -2.0f);
    glVertex2f(28.0f, -4.0f);
glEnd();
// Triangle (roof or top decoration)
glColor3f(0.0f, 0.0f, 0.55f);   // Same deep blue as building
glBegin(GL_TRIANGLES);
    glVertex2f(19.0f, 4.0f);   // Left
    glVertex2f(24.0f, 9.0f);   // Top
    glVertex2f(29.0f, 4.0f);   // Right
glEnd();



}
void Lightg(){



glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_POLYGON);
 glVertex2f(-25.0f, -1.5f);
 glVertex2f(-26.0f, 0.0f);
 glVertex2f(-23.0f, 0.0f);
 glVertex2f(-24.0f, -1.5f);
glEnd();
///Light box
glColor3f(1.0f, 1.0f, 1.0f);
glBegin(GL_POLYGON);
    glVertex2f(19.98f, -1.5f);
    glVertex2f(18.98f, 0.0f);
    glVertex2f(21.98f, 0.0f);
    glVertex2f(20.98f, -1.5f);
glEnd();


}
//............................ end scenario3.............




///............................  scenario 4......................................

GLfloat position1 = -1.2f;
GLfloat position2 =  1.2f;
GLfloat position3 =  0.0f;
GLfloat position4 =  0.0f;
GLfloat positionSun = -1.2f;
GLfloat position7 = -1.2f;
bool paused = false;
bool isDayE = true;
int extraCloudState = 0;

GLfloat speedPlane = 0.003f;
GLfloat speed = 0.02f;
GLfloat speedCloud = 0.004f;
GLfloat speedSun = 0.0015f;

// Function declarations JANNATUL FERDAUS EVA (SL02)

void circle(GLfloat x, GLfloat y, GLfloat r);
void field();
void hill1();
void hill2();
void hill3();
void smallTree1();
void smallTree2();
void smallTree3();
void smallTree4();
void palaceE();
void leftTree();
void rightTree();
void mainRoad();
void moveCar();
void moveBus();
void leftCloud();
void airplane();
void rightCloud();
void extraCloud1();
void extraCloud2();
void extraCloud3();
void sun1();
void moon();
void morningScene();
void nightScene();



void circle(GLfloat x, GLfloat y, GLfloat r)
{
    int i;
    int triangleAmount = 40;
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(i = 0; i <= triangleAmount;i++)
    {
        glVertex2f( x+(r*cos(i * twicePi / triangleAmount)), y+(r*sin(i * twicePi / triangleAmount)) );
    }
    glEnd();
}


void rightToLeft(int value)
{if(currentScenario == 4){
    if (!paused) {
        position1 -= speed;
        if(position1 < -2.0f) position1 = 2.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(16, rightToLeft, 0);
}

void leftToRight(int value)
{if(currentScenario == 4)
    {if (!paused) {
        position2 += speed;
        if(position2 > 2.0f) position2 = -2.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(16, leftToRight, 0);
}

void rightToLeftCloud(int value)
{if(currentScenario == 4){
    if (!paused) {
        position3 -= speedCloud;
        if(position3 < -2.0f) position3 = 2.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(33, rightToLeftCloud, 0);
}

void leftToRightCloud(int value)
{if(currentScenario == 4)
    {if (!paused) {
        position4 += speedCloud;
        if(position4 > 2.0f) position4 = -2.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(33, leftToRightCloud, 0);
}


void movePlane(int value)
{if(currentScenario == 4)
    {if (!paused) {
        position7 += speedPlane;
        if (position7 > 2.0f) position7 = -2.0f;
    }}
    glutPostRedisplay();
    glutTimerFunc(16, movePlane, 0);
}


void mSun(int value)
{if(currentScenario == 4)
    {if (!paused) {
        positionSun += speedSun;
        if(positionSun > 2.0f) positionSun = -2.0f;
    }}

    glutPostRedisplay();
    glutTimerFunc(33, mSun, 0);
}
//field starts
void field()       //obj Field1
{
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3ub(54, 128, 45);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f( 1.0f, -0.5f);
    glVertex2f( 1.0f,  0.1f);
    glVertex2f(-1.0f,  0.1f);
    glEnd();

    glPopMatrix();
}
//field ends


//hills starts
void hill1()   //obj SandHill1
{
    glPushMatrix();

    glColor3ub(237, 201, 175);
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 3.14f; angle += 0.05f) {
        float x = -0.7f + 0.4f * cos(angle);
        float y = 0.1f + 0.25f * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}


    void hill2()      //obj SandHill2
{
    glPushMatrix();

    glColor3ub(237, 201, 175);
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 3.14f; angle += 0.05f) {
        float x = 0.0f + 0.5f * cos(angle);
        float y = 0.1f + 0.3f * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}


void hill3()     //obj Sand Hill3
{
    glPushMatrix();

    glColor3ub(237, 201, 175);
    glBegin(GL_POLYGON);
    for (float angle = 0; angle <= 3.14f; angle += 0.05f) {
        float x = 0.7f + 0.35f * cos(angle);
        float y = 0.1f + 0.22f * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}
//hills ended




// background small trees starts here
void smallTree1()           //  obj BackTree1
{
    glPushMatrix();


glBegin(GL_QUADS);
glColor3ub(101, 67, 33);
glVertex2f(-0.82f, 0.10f);
glVertex2f(-0.78f, 0.10f);
glVertex2f(-0.78f, 0.22f);
glVertex2f(-0.82f, 0.22f);
glEnd();

glColor3ub(34, 139, 34);
circle(-0.80f, 0.30f, 0.06f);
circle(-0.84f, 0.24f, 0.045f);
circle(-0.76f, 0.24f, 0.045f);


glPopMatrix();
}


void smallTree2()                //Obj BacjTree2
{
    glPushMatrix();

glBegin(GL_QUADS);
glColor3ub(101, 67, 33);
glVertex2f(-0.42f, 0.10f);
glVertex2f(-0.38f, 0.10f);
glVertex2f(-0.38f, 0.22f);
glVertex2f(-0.42f, 0.22f);
glEnd();

glColor3ub(34, 139, 34);
circle(-0.40f, 0.30f, 0.06f);
circle(-0.44f, 0.24f, 0.045f);
circle(-0.36f, 0.24f, 0.045f);


glPopMatrix();
}


void smallTree3()              //obj BackTree3
{
    glPushMatrix();

glBegin(GL_QUADS);
glColor3ub(101, 67, 33);
glVertex2f(0.38f, 0.10f);
glVertex2f(0.42f, 0.10f);
glVertex2f(0.42f, 0.22f);
glVertex2f(0.38f, 0.22f);
glEnd();

glColor3ub(34, 139, 34);
circle(0.40f, 0.30f, 0.06f);
circle(0.36f, 0.24f, 0.045f);
circle(0.44f, 0.24f, 0.045f);

glPopMatrix();
}


void smallTree4()       //obj BackTree4
{
    glPushMatrix();

glBegin(GL_QUADS);
glColor3ub(101, 67, 33);
glVertex2f(0.78f, 0.10f);
glVertex2f(0.82f, 0.10f);
glVertex2f(0.82f, 0.22f);
glVertex2f(0.78f, 0.22f);
glEnd();

glColor3ub(34, 139, 34);
circle(0.80f, 0.30f, 0.06f);
circle(0.76f, 0.24f, 0.045f);
circle(0.84f, 0.24f, 0.045f);

glPopMatrix();
}






//palace starts here
void palaceE()       //obj Palace1
{
    glPushMatrix();


	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.57f, -0.1f);
	glVertex2f(0.57f, -0.1f);
	glVertex2f(0.57f, 0.25f);
	glVertex2f(-0.57f, 0.25f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.285f, 0.2575f);
	glVertex2f(0.285f, 0.2575f);
	glVertex2f(0.285f, 0.3f);
	glVertex2f(-0.285f, 0.3f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.57f, -0.1f);
	glVertex2f(0.57f, -0.1f);
	glVertex2f(0.575f, -0.11f);
	glVertex2f(-0.575f, -0.11f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.575f, -0.11f);
	glVertex2f(0.575f, -0.11f);
	glVertex2f(0.575f, -0.12f);
	glVertex2f(-0.575f, -0.12f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.605f, -0.15f);
	glVertex2f(0.605f, -0.15f);
	glVertex2f(0.575f, -0.12f);
	glVertex2f(-0.575f, -0.12f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.17, -0.125f);
	glVertex2f(0.17f, -0.125f);
	glVertex2f(0.18f, -0.135f);
	glVertex2f(-0.18f, -0.135f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.605f, -0.16f);
	glVertex2f(0.605f, -0.16f);
	glVertex2f(0.605f, -0.15f);
	glVertex2f(-0.605f, -0.15f);
	glEnd();

	// Door (Left)
	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.41f, -0.1f);
	glVertex2f(-0.31f, -0.1f);
	glVertex2f(-0.31f, 0.01f);
	glVertex2f(-0.41f, 0.01f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.41f, 0.01f);
	glVertex2f(-0.31f, 0.01f);
	glVertex2f(-0.315f, 0.025f);
	glVertex2f(-0.325f, 0.045f);
	glVertex2f(-0.335f, 0.06f);
	glVertex2f(-0.35f, 0.075f);
	glVertex2f(-0.355f, 0.081f);
	glVertex2f(-0.36f, 0.085f);
	glVertex2f(-0.365f, 0.081f);
	glVertex2f(-0.37f, 0.075f);
	glVertex2f(-0.385f, 0.06f);
	glVertex2f(-0.395f, 0.045f);
	glVertex2f(-0.405f, 0.025f);
	glEnd();

// Door (Right)

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.41f, -0.1f);
	glVertex2f(0.31f, -0.1f);
	glVertex2f(0.31f, 0.01f);
	glVertex2f(0.41f, 0.01f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(0.41f, 0.01f);
	glVertex2f(0.31f, 0.01f);
	glVertex2f(0.315f, 0.025f);
	glVertex2f(0.325f, 0.045f);
	glVertex2f(0.335f, 0.06f);
	glVertex2f(0.35f, 0.075f);
	glVertex2f(0.355f, 0.081f);
	glVertex2f(0.36f, 0.085f);
	glVertex2f(0.365f, 0.081f);
	glVertex2f(0.37f, 0.075f);
	glVertex2f(0.385f, 0.06f);
	glVertex2f(0.395f, 0.045f);
	glVertex2f(0.405f, 0.025f);
	glEnd();

	// Pillar (Left)

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.24f, -0.085f);
	glVertex2f(-0.21f, -0.085f);
	glVertex2f(-0.21f, 0.38f);
	glVertex2f(-0.24f, 0.38f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.225f, 0.4f);
	glVertex2f(-0.21f, 0.38f);
	glVertex2f(-0.24f, 0.38f);
	glEnd();

    glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.235f, -0.085f);
	glVertex2f(-0.215f, -0.085f);
	glVertex2f(-0.215f, 0.34f);
	glVertex2f(-0.235f, 0.34f);
	glEnd();

// Pillar (Right)
	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.24f, -0.085f);
	glVertex2f(0.21f, -0.085f);
	glVertex2f(0.21f, 0.38f);
	glVertex2f(0.24f, 0.38f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3ub(135, 206, 235);
	glVertex2f(0.225f, 0.4f);
	glVertex2f(0.21f, 0.38f);
	glVertex2f(0.24f, 0.38f);
	glEnd();


    glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.235f, -0.085f);
	glVertex2f(0.215f, -0.085f);
	glVertex2f(0.215f, 0.34f);
	glVertex2f(0.235f, 0.34f);
	glEnd();

    // windows left
	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.195f, -0.01f);
	glVertex2f(-0.165f, -0.01f);
	glVertex2f(-0.165f, 0.05f);
	glVertex2f(-0.195f, 0.05f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135,206,235);
	glVertex2f(-0.195f, 0.065f);
	glVertex2f(-0.165f, 0.065f);
	glVertex2f(-0.165f, 0.115f);
	glVertex2f(-0.195f, 0.115f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.195f, 0.13f);
	glVertex2f(-0.165f, 0.13f);
	glVertex2f(-0.165f, 0.175f);
	glVertex2f(-0.195f, 0.175f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.195f, 0.19f);
	glVertex2f(-0.165f, 0.19f);
	glVertex2f(-0.165f, 0.235f);
	glVertex2f(-0.195f, 0.235f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135,206, 206);
	glVertex2f(-0.19f, -0.005f);
	glVertex2f(-0.17f, -0.005f);
	glVertex2f(-0.17f, 0.045f);
	glVertex2f(-0.19f, 0.045f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.19f, 0.07f);
	glVertex2f(-0.17f, 0.07f);
	glVertex2f(-0.17f, 0.11f);
	glVertex2f(-0.19f, 0.11f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.19f, 0.135f);
	glVertex2f(-0.17f, 0.135f);
	glVertex2f(-0.17f, 0.17f);
	glVertex2f(-0.19f, 0.17f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.19f, 0.195f);
	glVertex2f(-0.17f, 0.195f);
	glVertex2f(-0.17f, 0.23f);
	glVertex2f(-0.19f, 0.23f);
	glEnd();

    // windows right
	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.195f, -0.01f);
	glVertex2f(0.165f, -0.01f);
	glVertex2f(0.165f, 0.05f);
	glVertex2f(0.195f, 0.05f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.195f, 0.065f);
	glVertex2f(0.165f, 0.065f);
	glVertex2f(0.165f, 0.115f);
	glVertex2f(0.195f, 0.115f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.195f, 0.13f);
	glVertex2f(0.165f, 0.13f);
	glVertex2f(0.165f, 0.175f);
	glVertex2f(0.195f, 0.175f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.195f, 0.19f);
	glVertex2f(0.165f, 0.19f);
	glVertex2f(0.165f, 0.235f);
	glVertex2f(0.195f, 0.235f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.19f, -0.005f);
	glVertex2f(0.17f, -0.005f);
	glVertex2f(0.17f, 0.045f);
	glVertex2f(0.19f, 0.045f);
	glEnd();

	glBegin(GL_QUADS);
    glColor3ub(135, 206, 235);
	glVertex2f(0.19f, 0.07f);
	glVertex2f(0.17f, 0.07f);
	glVertex2f(0.17f, 0.11f);
	glVertex2f(0.19f, 0.11f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.19f, 0.135f);
	glVertex2f(0.17f, 0.135f);
	glVertex2f(0.17f, 0.17f);
	glVertex2f(0.19f, 0.17f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.19f, 0.195f);
	glVertex2f(0.17f, 0.195f);
	glVertex2f(0.17f, 0.23f);
	glVertex2f(0.19f, 0.23f);
	glEnd();

    // borders
	glBegin(GL_QUADS);
	glColor3f(0.53f, 0.81f, 0.92f);
	glVertex2f(-0.245f, 0.25f);
	glVertex2f(0.245f, 0.25f);
	glVertex2f(0.245f, 0.2575f);
	glVertex2f(-0.245f, 0.2575f);
	glEnd();


	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.285f, 0.25f);
	glVertex2f(-0.245f, 0.25f);
	glVertex2f(-0.245f, 0.2575f);
	glVertex2f(-0.285f, 0.2575f);
	glEnd();

	glBegin(GL_QUADS);
    glColor3ub(135, 206, 235);
	glVertex2f(0.285f, 0.25f);
	glVertex2f(0.245f, 0.25f);
	glVertex2f(0.245f, 0.2575f);
	glVertex2f(0.285f, 0.2575f);
	glEnd();

	//Door in middle
	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.13f, -0.1f);
	glVertex2f(0.13f, -0.1f);
	glVertex2f(0.13f, 0.195f);
	glVertex2f(-0.13f, 0.195f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.12f, -0.1f);
	glVertex2f(0.12f, -0.1f);
	glVertex2f(0.12f, 0.18f);
	glVertex2f(-0.12f, 0.18f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.05f, -0.1f);
	glVertex2f(0.05f, -0.1f);
	glVertex2f(0.05f, 0.0f);
	glVertex2f(-0.05f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.05f, 0.0f);
	glVertex2f(0.05f, 0.0f);
	glVertex2f(0.0475f, 0.01f);
	glVertex2f(0.045f, 0.015f);
	glVertex2f(0.04f, 0.025f);
	glVertex2f(0.03f, 0.04f);
	glVertex2f(0.02f, 0.05f);
	glVertex2f(0.01f, 0.055f);
	glVertex2f(0.0f, 0.06f);
	glVertex2f(-0.01f, 0.055f);
	glVertex2f(-0.02f, 0.05f);
	glVertex2f(-0.03f, 0.04f);
	glVertex2f(-0.04f, 0.025f);
	glVertex2f(-0.045f, 0.015f);
	glVertex2f(-0.0475f, 0.01f);
	glEnd();

    // Tomb (Left)
    glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.56f, 0.25f);
	glVertex2f(-0.46f, 0.25f);
	glVertex2f(-0.46f, 0.3f);
	glVertex2f(-0.56f, 0.3f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.555f, 0.3f);
	glVertex2f(-0.465f, 0.3f);
	glVertex2f(-0.465f, 0.4f);
	glVertex2f(-0.555f, 0.4f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.57f, 0.4f);
	glVertex2f(-0.45f, 0.4f);
	glVertex2f(-0.46f, 0.415f);
	glVertex2f(-0.56f, 0.415f);
	glEnd();


    glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.55f, 0.415f);
	glVertex2f(-0.47f, 0.415f);
	glVertex2f(-0.47f, 0.48f);
	glVertex2f(-0.55f, 0.48f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.55f, 0.48f);
	glVertex2f(-0.47f, 0.48f);
	glVertex2f(-0.475f, 0.49f);
	glVertex2f(-0.48f, 0.50f);
	glVertex2f(-0.485f, 0.505f);
	glVertex2f(-0.49f, 0.51f);
	glVertex2f(-0.50f, 0.515f);
	glVertex2f(-0.51f, 0.52f);
	glVertex2f(-0.52f, 0.515f);
	glVertex2f(-0.53f, 0.51f);
	glVertex2f(-0.535f, 0.505f);
	glVertex2f(-0.54f, 0.50f);
	glVertex2f(-0.545f, 0.49f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.55f, 0.31f);
	glVertex2f(-0.53f, 0.31f);
	glVertex2f(-0.53f, 0.37f);
	glVertex2f(-0.55f, 0.37f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.55f, 0.37f);
	glVertex2f(-0.53f, 0.37f);
	glVertex2f(-0.531f, 0.372f);
	glVertex2f(-0.532f, 0.374f);
	glVertex2f(-0.533f, 0.376f);
	glVertex2f(-0.534f, 0.378f);
	glVertex2f(-0.535f, 0.38f);
	glVertex2f(-0.537f, 0.382f);
	glVertex2f(-0.539f, 0.384f);
	glVertex2f(-0.54f, 0.386f);
	glVertex2f(-0.541f, 0.384f);
	glVertex2f(-0.543f, 0.382f);
	glVertex2f(-0.545f, 0.38f);
	glVertex2f(-0.546f, 0.378f);
	glVertex2f(-0.547f, 0.376f);
	glVertex2f(-0.548f, 0.374f);
	glVertex2f(-0.549f, 0.372f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.525f, 0.31f);
	glVertex2f(-0.495f, 0.31f);
	glVertex2f(-0.495f, 0.37f);
	glVertex2f(-0.525f, 0.37f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.525f, 0.37f);
	glVertex2f(-0.495f, 0.37f);
	glVertex2f(-0.497f, 0.373f);
	glVertex2f(-0.499f, 0.376f);
	glVertex2f(-0.501f, 0.379f);
	glVertex2f(-0.503f, 0.382f);
	glVertex2f(-0.505f, 0.385f);
	glVertex2f(-0.507f, 0.388f);
	glVertex2f(-0.509f, 0.391f);
	glVertex2f(-0.51f, 0.394f);
	glVertex2f(-0.511f, 0.391f);
	glVertex2f(-0.513f, 0.388f);
	glVertex2f(-0.515f, 0.385f);
	glVertex2f(-0.517f, 0.382f);
	glVertex2f(-0.519f, 0.379f);
	glVertex2f(-0.521f, 0.376f);
	glVertex2f(-0.523f, 0.373f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.49f, 0.31f);
	glVertex2f(-0.47f, 0.31f);
	glVertex2f(-0.47f, 0.37f);
	glVertex2f(-0.49f, 0.37f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.49f, 0.37f);
	glVertex2f(-0.47f, 0.37f);
	glVertex2f(-0.471f, 0.372f);
	glVertex2f(-0.472f, 0.374f);
	glVertex2f(-0.473f, 0.376f);
	glVertex2f(-0.474f, 0.378f);
	glVertex2f(-0.475f, 0.38f);
	glVertex2f(-0.477f, 0.382f);
	glVertex2f(-0.479f, 0.384f);
	glVertex2f(-0.48f, 0.386f);
	glVertex2f(-0.481f, 0.384f);
	glVertex2f(-0.483f, 0.382f);
	glVertex2f(-0.485f, 0.38f);
	glVertex2f(-0.486f, 0.378f);
	glVertex2f(-0.487f, 0.376f);
	glVertex2f(-0.488f, 0.374f);
	glVertex2f(-0.489f, 0.372f);
	glEnd();

// Tomb (Right)
    glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(0.56f, 0.25f);
	glVertex2f(0.46f, 0.25f);
	glVertex2f(0.46f, 0.3f);
	glVertex2f(0.56f, 0.3f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(0.555f, 0.3f);
	glVertex2f(0.465f, 0.3f);
	glVertex2f(0.465f, 0.4f);
	glVertex2f(0.555f, 0.4f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.57f, 0.4f);
	glVertex2f(0.45f, 0.4f);
	glVertex2f(0.46f, 0.415f);
	glVertex2f(0.56f, 0.415f);
	glEnd();

    glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(0.55f, 0.415f);
	glVertex2f(0.47f, 0.415f);
	glVertex2f(0.47f, 0.48f);
	glVertex2f(0.55f, 0.48f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(0.55f, 0.48f);
	glVertex2f(0.47f, 0.48f);
	glVertex2f(0.475f, 0.49f);
	glVertex2f(0.48f, 0.50f);
	glVertex2f(0.485f, 0.505f);
	glVertex2f(0.49f, 0.51f);
	glVertex2f(0.50f, 0.515f);
	glVertex2f(0.51f, 0.52f);
	glVertex2f(0.52f, 0.515f);
	glVertex2f(0.53f, 0.51f);
	glVertex2f(0.535f, 0.505f);
	glVertex2f(0.54f, 0.50f);
	glVertex2f(0.545f, 0.49f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.55f, 0.31f);
	glVertex2f(0.53f, 0.31f);
	glVertex2f(0.53f, 0.37f);
	glVertex2f(0.55f, 0.37f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(0.55f, 0.37f);
	glVertex2f(0.53f, 0.37f);
	glVertex2f(0.531f, 0.372f);
	glVertex2f(0.532f, 0.374f);
	glVertex2f(0.533f, 0.376f);
	glVertex2f(0.534f, 0.378f);
	glVertex2f(0.535f, 0.38f);
	glVertex2f(0.537f, 0.382f);
	glVertex2f(0.539f, 0.384f);
	glVertex2f(0.54f, 0.386f);
	glVertex2f(0.541f, 0.384f);
	glVertex2f(0.543f, 0.382f);
	glVertex2f(0.545f, 0.38f);
	glVertex2f(0.546f, 0.378f);
	glVertex2f(0.547f, 0.376f);
	glVertex2f(0.548f, 0.374f);
	glVertex2f(0.549f, 0.372f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.525f, 0.31f);
	glVertex2f(0.495f, 0.31f);
	glVertex2f(0.495f, 0.37f);
	glVertex2f(0.525f, 0.37f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(0.525f, 0.37f);
	glVertex2f(0.495f, 0.37f);
	glVertex2f(0.497f, 0.373f);
	glVertex2f(0.499f, 0.376f);
	glVertex2f(0.501f, 0.379f);
	glVertex2f(0.503f, 0.382f);
	glVertex2f(0.505f, 0.385f);
	glVertex2f(0.507f, 0.388f);
	glVertex2f(0.509f, 0.391f);
	glVertex2f(0.51f, 0.394f);
	glVertex2f(0.511f, 0.391f);
	glVertex2f(0.513f, 0.388f);
	glVertex2f(0.515f, 0.385f);
	glVertex2f(0.517f, 0.382f);
	glVertex2f(0.519f, 0.379f);
	glVertex2f(0.521f, 0.376f);
	glVertex2f(0.523f, 0.373f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(135, 206, 235);
	glVertex2f(0.49f, 0.31f);
	glVertex2f(0.47f, 0.31f);
	glVertex2f(0.47f, 0.37f);
	glVertex2f(0.49f, 0.37f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(0.49f, 0.37f);
	glVertex2f(0.47f, 0.37f);
	glVertex2f(0.471f, 0.372f);
	glVertex2f(0.472f, 0.374f);
	glVertex2f(0.473f, 0.376f);
	glVertex2f(0.474f, 0.378f);
	glVertex2f(0.475f, 0.38f);
	glVertex2f(0.477f, 0.382f);
	glVertex2f(0.479f, 0.384f);
	glVertex2f(0.48f, 0.386f);
	glVertex2f(0.481f, 0.384f);
	glVertex2f(0.483f, 0.382f);
	glVertex2f(0.485f, 0.38f);
	glVertex2f(0.486f, 0.378f);
	glVertex2f(0.487f, 0.376f);
	glVertex2f(0.488f, 0.374f);
	glVertex2f(0.489f, 0.372f);
	glEnd();

	// Tomb (Middle)
    glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.1f, 0.3f);
	glVertex2f(0.1f, 0.3f);
	glVertex2f(0.1f, 0.34f);
	glVertex2f(-0.1f, 0.34f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(-0.09f, 0.34f);
	glVertex2f(0.09f, 0.34f);
	glVertex2f(0.09f, 0.365f);
	glVertex2f(-0.09f, 0.365f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(125, 206, 235);
	glVertex2f(-0.085f, 0.365f);
	glVertex2f(0.085f, 0.365f);
	glVertex2f(0.085f, 0.43f);
	glVertex2f(-0.085f, 0.43f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(135, 206, 235);
	glVertex2f(-0.085f, 0.43f);
	glVertex2f(0.085f, 0.43f);
	glVertex2f(0.075f, 0.46f);
	glVertex2f(0.065f, 0.48f);
	glVertex2f(0.055f, 0.495f);
	glVertex2f(0.045f, 0.51f);
	glVertex2f(0.025f, 0.53f);
	glVertex2f(0.0f, 0.54f);
	glVertex2f(-0.025f, 0.53f);
	glVertex2f(-0.045f, 0.51f);
	glVertex2f(-0.055f, 0.495f);
	glVertex2f(-0.065f, 0.48f);
	glVertex2f(-0.075f, 0.46f);
	glEnd();


    glPopMatrix();
}
//palace ends here



//left tree starts here
void leftTree()        //obj Tree1
{
    glPushMatrix();

    glBegin(GL_QUADS);
    glColor3ub(58,28,28);
    glVertex2f(-0.80f,-0.475f);
    glVertex2f(-0.80f,-0.3f);
    glVertex2f(-0.85f,-0.3f);
    glVertex2f(-0.85f,-0.475f);
    glEnd();

    glBegin(GL_TRIANGLES);
	glColor3ub(0,100,0);
	glVertex2f(-0.74f, -0.3f);
	glVertex2f(-0.91f, -0.3f);
	glVertex2f(-0.825f, 0.1f);
	glVertex2f(-0.75f, -0.2f);
	glVertex2f(-0.90f, -0.2f);
	glVertex2f(-0.825f, 0.2f);
	glVertex2f(-0.76f, -0.1f);
	glVertex2f(-0.89f, -0.1f);
	glVertex2f(-0.825f, 0.2f);
	glVertex2f(-0.77f, 0.0f);
	glVertex2f(-0.88f, 0.0f);
	glVertex2f(-0.825f, 0.2f);
	glEnd();

    glPopMatrix();
}
// left tree ends here


//right tree starts
void rightTree()         //obj Tree2
{
    glPushMatrix();


    glBegin(GL_QUADS);
    glColor3ub(58,28,28);
    glVertex2f(0.80f,-0.475f);
    glVertex2f(0.80f,-0.3f);
    glVertex2f(0.85f,-0.3f);
    glVertex2f(0.85f,-0.475f);
    glEnd();

    glBegin(GL_TRIANGLES);
	glColor3ub(0,100,0);
	glVertex2f(0.74f, -0.3f);
	glVertex2f(0.91f, -0.3f);
	glVertex2f(0.825f, 0.1f);
	glVertex2f(0.75f, -0.2f);
	glVertex2f(0.90f, -0.2f);
	glVertex2f(0.825f, 0.2f);
	glVertex2f(0.76f, -0.1f);
	glVertex2f(0.89f, -0.1f);
	glVertex2f(0.825f, 0.2f);
	glVertex2f(0.77f, 0.0f);
	glVertex2f(0.88f, 0.0f);
	glVertex2f(0.825f, 0.2f);
	glEnd();

    glPopMatrix();
}
//right tree ends




// main road starts here
void mainRoad()   // obj Road1
{
    glPushMatrix();

    // Road
    glBegin(GL_QUADS);
    glColor3ub(84, 84, 84);
    glVertex2f(-1.0f,-1.0f);
    glVertex2f( 1.0f,-1.0f);
    glVertex2f( 1.0f,-0.5f);
    glVertex2f(-1.0f,-0.5f);
    glEnd();

    // road Divider
    glLineWidth(5); //obj RoadDivider1
    glBegin(GL_LINES);
    glColor3ub(252, 250, 250);
    glVertex2f(-0.975f,-0.65f); glVertex2f(-0.825f,-0.65f);
    glVertex2f(-0.675f,-0.65f); glVertex2f(-0.525f,-0.65f);
    glVertex2f(-0.375f,-0.65f); glVertex2f(-0.225f,-0.65f);
    glVertex2f(-0.075f,-0.65f);  glVertex2f(0.075f,-0.65f);
    glVertex2f(0.225f,-0.65f);   glVertex2f(0.375f,-0.65f);
    glVertex2f(0.525f,-0.65f);   glVertex2f(0.675f,-0.65f);
    glVertex2f(0.825f,-0.65f);   glVertex2f(0.975f,-0.65f);
    glEnd();
    glPopMatrix();
}
//main road ends



//car1 starts here
void moveCar()     //obj Car1
{
    glLoadIdentity();
    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);
    glTranslatef(position1, 0.1f, 0.0f);
    glBegin(GL_POLYGON);
    glColor3ub(0,0,128);
    glVertex2f(0.7f, -0.67f);
    glVertex2f(0.98f, -0.67f);
    glVertex2f(0.98f, -0.615f);
    glVertex2f(0.945f, -0.59f);
    glVertex2f(0.9f, -0.51f);
    glVertex2f(0.8f, -0.51f);
    glVertex2f(0.76f, -0.59f);
    glVertex2f(0.7f, -0.615f);
    glEnd();

    // Head light
    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(0.697f, -0.65f);
    glVertex2f(0.703f, -0.65f);
    glVertex2f(0.703f, -0.63f);
    glVertex2f(0.697f, -0.63f);
    glEnd();

    // windows
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(0.775f,-0.58f);
    glVertex2f(0.845f,-0.58f);
    glVertex2f(0.845f,-0.525f);
    glVertex2f(0.805f,-0.525f);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.0f,0.0f,0.0f);
    glVertex2f(0.855f,-0.58f);
    glVertex2f(0.925f,-0.58f);
    glVertex2f(0.895f,-0.525f);
    glVertex2f(0.855f,-0.525f);
    glEnd();

    // wheels
    glColor3ub(84, 84, 84);
    circle(0.77f,-0.67f,0.036f);
    circle(0.92f,-0.67f,0.036f);
    glColor3ub(0, 0, 0);
    circle(0.77f,-0.67f,0.033f);
    circle(0.92f,-0.67f,0.033f);
    glColor3ub(37, 35, 36);
    circle(0.77f,-0.67f,0.025f);
    circle(0.92f,-0.67f,0.025f);

    glPopMatrix();
}


//car 2 starts here
void moveBus()     //obj Car2
{
    glLoadIdentity();
    glPushMatrix();

    glScalef(30.0f, 26.7742f, 1.0f);


    glTranslatef(position2, 0.2f, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-0.98f, -0.94f);
    glVertex2f(-0.62f, -0.94f);
    glVertex2f(-0.62f, -0.83f);
    glVertex2f(-0.66f, -0.81f);
    glVertex2f(-0.70f, -0.79f);
    glVertex2f(-0.96f, -0.79f);
    glVertex2f(-0.98f, -0.83f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.96f, -0.86f);
    glVertex2f(-0.875f, -0.86f);
    glVertex2f(-0.875f, -0.80f);
    glVertex2f(-0.945f, -0.80f);
    glVertex2f(-0.96f, -0.83f);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.865f, -0.86f);
    glVertex2f(-0.78f, -0.86f);
    glVertex2f(-0.78f, -0.80f);
    glVertex2f(-0.865f, -0.80f);
    glEnd();

glBegin(GL_POLYGON);
glColor3f(1.0f,1.0f,1.0f);
glVertex2f(-0.77f,-0.86f);
glVertex2f(-0.70f,-0.86f);
glVertex2f(-0.70f,-0.82f);
glVertex2f(-0.73f,-0.80f);
glVertex2f(-0.77f,-0.80f);
glEnd();

    //headlight
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.6f);
    glVertex2f(-0.62f, -0.90f);
    glVertex2f(-0.62f, -0.86f);
    glVertex2f(-0.625f, -0.86f);
    glVertex2f(-0.625f, -0.90f);
    glEnd();

    // wheels
    glColor3ub(84, 84, 84);
    circle(-0.70f, -0.94f, 0.036f);
    circle(-0.90f, -0.94f, 0.036f);

    glColor3ub(0, 0, 0);
    circle(-0.70f, -0.94f, 0.030f);
    circle(-0.90f, -0.94f, 0.030f);

    glColor3ub(37, 35, 36);
    circle(-0.70f, -0.94f, 0.022f);
    circle(-0.90f, -0.94f, 0.022f);

    glPopMatrix();
}
//car 2 ends here


//left cloud starts
void leftCloud()     //obj Cloud1
{
    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);
    glTranslatef(position4, 0.0f, 0.0f);
    glColor3ub(239, 238, 237);
    circle(-0.84f,0.8f,0.07f);
    circle(-0.865f,0.855f,0.07f);
    circle(-0.92f,0.76f,0.07f);
    circle(-0.955f,0.81f,0.07f);
    circle(-1.0f,0.72f,0.07f);
    glPopMatrix();
}
//left cloud ends


//airplane starts
void airplane()    //obj Airplane
{
    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);
    glTranslatef(position7, 0.72f, 0.0f);

    glBegin(GL_QUADS);
    glColor3ub(245, 245, 245);
    glVertex2f(-0.12f, 0.00f);
    glVertex2f( 0.10f, 0.00f);
    glVertex2f( 0.10f, 0.09f);
    glVertex2f(-0.12f, 0.09f);
    glEnd();

    glColor3ub(200, 0, 0);
    circle(0.10f, 0.045f, 0.045f);

    glBegin(GL_TRIANGLES);
    glColor3ub(200, 0, 0);
    glVertex2f(-0.12f, 0.09f);
    glVertex2f(-0.18f, 0.13f);
    glVertex2f(-0.12f, 0.00f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(200, 0, 0);
    glVertex2f(-0.03f, 0.09f);
    glVertex2f( 0.03f, 0.09f);
    glVertex2f( 0.00f, 0.20f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0); // black
    glVertex2f(0.07f, 0.03f);
    glVertex2f(0.095f, 0.03f);
    glVertex2f(0.095f, 0.06f);
    glVertex2f(0.07f, 0.06f);
    glEnd();

    glColor3ub(0, 0, 0);

    glBegin(GL_QUADS);
    glVertex2f(-0.07f, 0.025f);
    glVertex2f(-0.04f, 0.025f);
    glVertex2f(-0.04f, 0.06f);
    glVertex2f(-0.07f, 0.06f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.02f, 0.025f);
    glVertex2f( 0.01f, 0.025f);
    glVertex2f( 0.01f, 0.06f);
    glVertex2f(-0.02f, 0.06f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.03f, 0.025f);
    glVertex2f(0.06f, 0.025f);
    glVertex2f(0.06f, 0.06f);
    glVertex2f(0.03f, 0.06f);
    glEnd();

    glPopMatrix();
}
//airplane ends




//right cloud starts
void rightCloud()        //obj Cloud2
{
    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);
    glTranslatef(position3, 0.0f, 0.0f);
    glColor3ub(239, 238, 237);
    circle(0.84f,0.64f,0.07f);
    circle(0.865f,0.73f,0.07f);
    circle(0.92f,0.68f,0.07f);
    circle(0.955f,0.775f,0.07f);
    circle(1.0f,0.72f,0.07f);
    glPopMatrix();
}
//right cloud ends




// extra clouds starts

void extraCloud1()  //obj MouseCloud1
{
    glColor3ub(255, 255, 255);

    if (extraCloudState >= 1) {
        circle(-10.0f, 15.0f, 2.5f);
        circle(-12.5f, 15.5f, 2.0f);
        circle(-7.5f, 15.5f, 2.0f);
        circle(-10.0f, 17.0f, 1.8f);
        circle(-8.5f, 16.8f, 1.5f);
        circle(-11.5f, 16.8f, 1.5f);
    }
}


    void extraCloud2()       //Obj MouseCloud2
{
    glColor3ub(255, 255, 255);


    if (extraCloudState >= 2) {
        circle(12.0f, 14.0f, 2.3f);
        circle(10.0f, 14.5f, 1.8f);
        circle(14.0f, 14.5f, 1.8f);
        circle(12.0f, 15.8f, 1.7f);
        circle(13.5f, 15.5f, 1.5f);
        circle(10.5f, 15.5f, 1.5f);
    }
}



    void extraCloud3() //obj MouseCloud3
{
    glColor3ub(255, 255, 255);
    // cloud 3
    if (extraCloudState == 3) {
        circle(0.0f, 18.0f, 2.5f);
        circle(-2.5f, 18.5f, 2.0f);
        circle(2.5f, 18.5f, 2.0f);
        circle(0.0f, 19.5f, 1.8f);
        circle(1.5f, 19.2f, 1.5f);
        circle(-1.5f, 19.2f, 1.5f);

        // cloud 4
        circle(20.0f, 17.0f, 2.3f); //obj MouseCloud4
        circle(18.0f, 17.5f, 1.8f);
        circle(22.0f, 17.5f, 1.8f);
        circle(20.0f, 18.8f, 1.7f);
        circle(21.5f, 18.5f, 1.5f);
        circle(18.5f, 18.5f, 1.5f);
    }
}

// extra clouds ends



// Sun starts
void sun1()   //obj Sun1
{
    glLoadIdentity();
    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);
    glTranslatef(positionSun, 0.75f, 0.0f);
    glColor3ub(252, 209, 77);
    circle(0.0f, 0.0f, 0.08f);
    glPopMatrix();
}
//sun ends




//moon starts
void moon()   //obj Moon1
{
    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);
    glTranslatef(0.65f, 0.8f, 0.0f);
    glColor3ub(244, 241, 201);
    circle(0.0f, 0.0f, 0.06f);
    glPopMatrix();
}
//moon ends


//morning scene starts
void morningScene()
{
    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);

    glBegin(GL_QUADS);
    glColor3ub(135, 206, 250);
    glVertex2f(-1.0f, 0.1f);
    glVertex2f( 1.0f, 0.1f);
    glColor3ub(0, 133, 255);
    glVertex2f( 1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    glLineWidth(8);
    glBegin(GL_LINES);
    glColor3ub(115, 115, 115);
    glVertex2f(-1.0,0.1);
    glVertex2f( 1.0,0.1);
    glEnd();

    glPopMatrix();

    sun1();
    leftCloud();
    rightCloud();
    extraCloud1();
     extraCloud2();
      extraCloud3();
    airplane();

    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);
    field();
    hill1();
    hill2();
    hill3();
    smallTree1();
    smallTree2();
    smallTree3();
    smallTree4();
    palaceE();
    leftTree();
    rightTree();
    mainRoad();
    glPopMatrix();

    moveCar();
    moveBus();
}
//morning scene ends




// Night scene starts
void nightScene()
{
    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);

    glBegin(GL_QUADS);
    glColor3ub(3, 0, 46);
    glVertex2f(-1.0,0.1);
    glVertex2f( 1.0,0.1);
    glVertex2f( 1.0,1.0);
    glVertex2f(-1.0,1.0);
    glEnd();

    glLineWidth(8);
    glBegin(GL_LINES);
    glColor3ub(115, 115, 115);
    glVertex2f(-1.0,0.1);
    glVertex2f( 1.0,0.1);
    glEnd();

    glPopMatrix();

    moon();
    extraCloud1();
 extraCloud2();
  extraCloud3();




    glPushMatrix();
    glScalef(30.0f, 26.7742f, 1.0f);
    field();
    hill1();
    hill2();
    hill3();
    smallTree1();
    smallTree2();
    smallTree3();
    smallTree4();
    palaceE();
    leftTree();
    rightTree();
    mainRoad();
    glPopMatrix();

    moveCar();
    moveBus();
}
















///.................................................Display function...............//scenario1...........................


void drawScenario1(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    // Sky
    if (isDay) glClearColor(0.859f, 0.945f, 0.976f, 1.0f); // light blue
    else       glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // dark navy         //day night transformation

    glClear(GL_COLOR_BUFFER_BIT);

    // Sun or Moon
        if (isDay) drawSun(6.0f, 20.0f, 3.0f);   //Sunmoon_ transformation
    else {
        drawMoon(6.0f, 20.0f, 3.0f);
        drawStars();
    }



    //Sky();
    //drawSun(0.0f,0.0f,0.0f);
    drawCloud();
    road();
    house1();
    house2();
    palace();
    window1(0.0f, 0.0f, 01.0f);
    window1(24.0f, 0.0f, 01.0f);

    window2(2.1f, -0.7f, 1.15f);
    window2(4.6f, -0.7f, 1.15f);
    window2(26.1f, -0.7f, 1.15f);
    window2(28.6f, -0.7f, 1.15f);

    window2(2.1f, -6.0f, 1.15f);
    window2(4.6f, -6.0f, 1.15f);
    window2(26.1f, -6.0f, 1.15f);
    window2(28.6f, -6.0f, 1.15f);
    window2(19.90f, -7.0f, 1.15f);
    window2(10.6f, -7.0f, 1.15f);
    window2(20.6f, -8.0f, 1.550f);
    window2(7.0f, -15.0f, 1.0f);
    window2(7.0f, -11.20f, 1.0f);
    window2(19.5f, -15.0f, 1.0f);
    window2(19.5f, -11.20f, 1.0f);

    window2(21.6f, -17.0f, 2.50f);
    window2(45.6f, -17.0f, 2.50f);

    window1(10.0f, -6.50f, 01.0f);
    window1(6.0f, -6.50f, 01.0f);
    window1(10.0f, -6.50f, 01.0f);
    window1(14.0f, -6.50f, 01.0f);
    window1(18.0f, -6.50f, 01.0f);
    door();
    //house1();
    //house2();
    tree1();
    tree2();
    tree2_translated(4.0f, -7.50f, 0.53f);
    airbln();
    drawBench(-15.0f, -14.20f, 3.0f);
    drawBench(23.0f, -14.20f, 3.0f);



    if (!isDay) {
    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);

    glBegin(GL_QUADS);
        glVertex2f(-30.0f, -20.0f);
        glVertex2f(30.0f, -20.0f);
        glVertex2f(30.0f, 26.7742f);
        glVertex2f(-30.0f, 26.7742f);
    glEnd();
}

if (isDay){   //Lamppost_ transformation

    NdrawLampPost(-18.0f, -11.90f, 6.7f);
    NdrawLampPost(-28.0f, -11.90f, 6.7f);
   NdrawLampPost(-8.0f, -11.90f, 6.7f);
    NdrawLampPost(8.0f, -11.90f, 6.7f);
    NdrawLampPost(18.0f, -11.90f, 6.7f);
    NdrawLampPost(28.0f, -11.90f, 6.7f);


}

 else  {

   drawLampPost(-18.0f, -11.90f, 6.7f);
    drawLampPost(-28.0f, -11.90f, 6.7f);
   drawLampPost(-8.0f, -11.90f, 6.7f);
    drawLampPost(8.0f, -11.90f, 6.7f);
    drawLampPost(18.0f, -11.90f, 6.7f);
    drawLampPost(28.0f, -11.90f, 6.7f);
}
    if (isDay) drawSun(6.0f, 20.0f, 3.0f);
    else {
        drawMoon(6.0f, 20.0f, 3.0f);

    }

    truck();
    bus();
    drawRain();

    glFlush();
}


///.................................................Display function...............//scenario2...........................
void drawScenario2(void) {
    glClear(GL_COLOR_BUFFER_BIT);
///Stranzition01 day-night....................................................................................................
        if (isDay) glClearColor(0.859f, 0.945f, 0.976f, 1.0f); // light blue
    else       glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // dark navy

    glClear(GL_COLOR_BUFFER_BIT);

///Stranzition02  Sun-Moon.....................................................................................................
    if (isDay) sun(6.0f, 20.0f, 3.0f);
    else {
        moon(6.0f, 20.0f, 3.0f);

    }
///Stranzition03 Lamp post ...................................................................................................
    if (isDay)
        drawAllLampPosts();
    else {
        drawNightAllLampPosts();

    }
    planeS268();
    cloudS268();
    Factory268();
    wareHouse();
    road268();
    palace268();
    doggo();
     drawAllTrees();
    if (isDay){

        drawAllLampPosts();}
    else {

        drawNightAllLampPosts();

    }
    suv268();
    bus268();

glFlush();

}

///.................................................Display function...............//scenario3...........................
void drawScenario3() {
 glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
 glClear(GL_COLOR_BUFFER_BIT);

DayandNightTransation();
Roadg();
GrassPartg();

cloudg1();
cloudg2();
cloudg3();
cloudg4();

Planeg();
Building1();
Building2();
BuildingSideGrassg();
Treeg();
BuildingBigg();
LampPostg();
LampPostg2();
Carg1();
Carg2();
if (showLight) {
        Lightg();
    }
 glFlush();
}


///.................................................Display function...............//scenario 4...........................


void drawScenario4(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (isDayE) {
        morningScene();
    } else {
        nightScene();
    }

    glFlush();
}



///......................................main Display function

void display() {
    if (currentScenario == 1) {
        drawScenario1();}

    else if(currentScenario == 2) {
        drawScenario2();
    }

    else if(currentScenario == 3) {
        drawScenario3();
    }
    else if(currentScenario == 4) {
        drawScenario4();
    }

    glFlush();

}
//...........................................


// Input handling

//.....Scenario 1......
void truckKeys(int key, int x, int y) {
    if (currentScenario == 1) {
        switch (key) {
            case GLUT_KEY_UP:
                truckSpeed -= 1.0f;
                break;
            case GLUT_KEY_DOWN:
                truckSpeed += 0.1f;
                break;
            case GLUT_KEY_RIGHT:
                truckSpeed = -2.0f;
                break;
            case GLUT_KEY_LEFT:
                truckSpeed = 0.0f;
                break;
        }
        glutPostRedisplay();
    }
}

void Keys(unsigned char key, int x, int y) {

    ///........Scenario 1...........
    if (currentScenario == 1) {
        switch (key) {
            case 'a': case 'A':
                BusSpeed += 1.0f;
                break;
            case 'b': case 'B':
                BusSpeed -= 0.1f;
                break;
            case 'c':  case 'C':
                BusSpeed = 2.0f;
                break;
            case 'd': case 'D':
                BusSpeed = 0.0f;
                break;
            case 'r': case 'R':
                rainOn = true;
                break;
            case 's': case 'S':
                rainOn = false;
                break;

         case '9': isDay = true; break; // Day
         case '0': isDay = false; break; // Night
         }
        glutPostRedisplay();
    }


 ///........Scenario 2...........

  else if (currentScenario == 2) {
    switch (key) {
        case 'w':
            BusS268Speed += 1.0f;    // right e speed barabe
            break;
        case 's':
            BusS268Speed -= 0.9f;    // slow korbe
            break;
        case 'r':
            BusS268Speed = 2.0f;     // normal speed e reset
            break;
        case ' ':
            BusS268Speed = 0.0f;     // stop
            break;
         case '9': isDay = true; break; // Day
         case '0': isDay = false; break; // Night
    }
    glutPostRedisplay();
}

 ///........Scenario 3...........
else if (currentScenario == 3) {
  switch (key) {
      case 'q': carSpeed1 = 0.0f; break;           // Stop car
        case 'w': carSpeed1 = 0.20f; break;           // Start car
        case 'e': carSpeed2 = 0.0f; break;           // Stop bus
        case 'r': carSpeed2 = 0.20f; break;           // Start bus
        case 't': carSpeed2 +=0.5f; break;           // Increase bus speed
        case 'y': carSpeed2 -=0.5f; break;           // Decrease bus speed
        case 'u': cloudgSpeed= 0.0f; break;         // Stop clouds
        case 'i': cloudgSpeed = 0.1f; break;         // Start clouds
        case 'o': cloudgSpeed += 0.1f; break;        // Increase clouds Speed
        case 'p': cloudgSpeed -= 0.1f; break;        // Decrease clouds Speed
 case 'd': isDayG = true; break; // Day
 case 'n': isDayG = false; break; // Night
 case'm':planespeed  =0.0f;break;
 case'b':planespeed =0.15;break;

  // --- light controls ---
        case 'l': showLight = 1; break;        // turn ON light
        case 'k': showLight = 0; break;        // turn OFF light

 }
        glutPostRedisplay();
    }

///........Scenario 4...........
else if (currentScenario == 4){

    switch (key)
    {
        case 'm':
        case 'M':
            isDayE = true;
            glutPostRedisplay();
            break;

        case 'n':
        case 'N':
            isDayE = false;
            glutPostRedisplay();
            break;

        case 27: // ESC to exit
            exit(0);
            break;
    }

}


    // Global keys for switching scenarios
    if (key == '1') {
        currentScenario = 1;
        glutPostRedisplay();
    }
    else if (key == '2') {
        currentScenario = 2;
        glutPostRedisplay();
    }
     else if (key == '3') {
        currentScenario = 3;
        glutPostRedisplay();
    }
     else if (key == '4') {
        currentScenario = 4;
        glutPostRedisplay();
    }


}



void handledisplayMouse(int button, int state, int x, int y) {
     if (currentScenario == 3){ if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       carSpeed1 += 0.2f; // Increase car speed on left click
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        carSpeed1 -= 0.2f; // Decrease car speed on right click
    }

    glutPostRedisplay();}

    else if (currentScenario == 4){    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        paused = !paused;   // pause/resume
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        extraCloudState++;
        if (extraCloudState > 3) {
            extraCloudState = 0;   // reset after 4th click
        }
    }

    glutPostRedisplay();}

}

///Sanim05 Special keys.............Scenario2.................................................................................
void suvKeys(int key, int x, int y) { //Sanim05 Special keys // special keys (Arrow keys) for SUV
    switch (key) {
        case GLUT_KEY_UP:
            suvSpeed -= 1.0f;
            break;
        case GLUT_KEY_DOWN:
            suvSpeed += 0.8f;
            break;
        case GLUT_KEY_RIGHT:
            suvSpeed = -2.0f;
            break;
        case GLUT_KEY_LEFT:
            suvSpeed = 0.0f;
            break;
    }
    glutPostRedisplay();
}


void specialKeys(int key, int x, int y) {
    if (currentScenario == 1) {  //....Scenario1
        truckKeys(key, x, y);
    }
    else if (currentScenario == 2) {   //...Scenario2
        suvKeys( key,  x,  y);
        glutPostRedisplay();
    }
}




//......................................


void initGL(void) {
    for (int i = 0; i < 200; i++) {
    rainX[i] = (rand() % 60) - 30;
    rainY[i] = (rand() % 50);
}
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-30.0, 30.0, -20.0, 26.7742);
    glMatrixMode(GL_MODELVIEW);
}





int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1026.4951/2, 800.3333/2);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Merged Scenarios");

    initGL();
    glutDisplayFunc(display);
///.........Scenario 1.....
    // Set up timers
    glutTimerFunc(3000, timer, 0);
    glutTimerFunc(40, updateTruck, 0);
    glutTimerFunc(40, updateBus, 0);
    glutTimerFunc(2, updateCloud, 0);
    glutTimerFunc(30, updateBalloon, 0);
    glutTimerFunc(30, updateRain, 0);
   // glutTimerFunc(16, updateScenario2, 0);


     ///.......Scenario 2.......
    glutTimerFunc(1500, timers, 0); //day night tranzition
    glutTimerFunc(40, animationSUV, 0);
    glutTimerFunc(40, animationPlane, 0);
    glutTimerFunc(40, animationBus, 0);
    glutTimerFunc(2, animationCloudS268, 0);


    ///.......Scenario 3.......

 // Start cloud animation
 glutTimerFunc(20, updateClouds, 0);
 // Start car animation (movement + wheels together)
 glutTimerFunc(20, updateCar1, 0);
 glutTimerFunc(20, updateCar2, 0);
  glutTimerFunc(20, updatePlaneg, 0);



  ///.......Scenario 4.......
      glutTimerFunc(16, rightToLeft, 0);
    glutTimerFunc(16, leftToRight, 0);
    glutTimerFunc(33, rightToLeftCloud, 0);
    glutTimerFunc(33, leftToRightCloud, 0);
    glutTimerFunc(33, mSun, 0);
    glutTimerFunc(0, movePlane, 0);


        /// Set up input handlers
    glutKeyboardFunc(Keys);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(handledisplayMouse);

    glutMainLoop();
    return 0;
}
