#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"
#include "timer.h"
#include "ball.h"
#include "rect.h"
#include "semi.h"
#include "trampoline.h"
#include "porcupine.h"
#include "magnet.h"
#include "life.h"
#include "score.h"
#include "digit.h"
#include "slope.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1, balls[10],ba;
Rect base;
Semi sball;
Trampoline trampoline;
Porcupine porcupine;
Magnet magnet;
Life life;
pid_t pid = 0;
Score score;
Slope slope[5];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
extern double drag_oldx, drag_oldy;
bool sound = true;

Timer t60(1.0 / 60);
int magnet_start_time = 1000;
int magnet_duration = 700;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ba.draw(VP);
    base.draw(VP);
    sball.draw(VP);
    ball1.draw(VP);
    trampoline.draw(VP);
    porcupine.draw(VP);
    if (magnet.alive == 1){
        magnet.draw(VP);
    }
    //cout<<"11"<<endl;

    for(int i=0;i<2;i++)
        balls[i].draw(VP);
    for(int i=0;i<2;i++)
        slope[i].draw(VP);

    life.draw(VP);
    score.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int key_a = glfwGetKey(window, GLFW_KEY_A);
    int key_s = glfwGetKey(window, GLFW_KEY_S);
    int key_d = glfwGetKey(window, GLFW_KEY_D);
    int key_w = glfwGetKey(window, GLFW_KEY_W);
    int mouse_clicked = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    bounding_box_t b =ball1.bounding_box();
    if (left)
    {
        if(b.y<=-2.2f && b.x>=-1.5f && b.x<=1.5f)
            ball1.set_position(b.x+0.05f,b.y+0.1f);
        if(b.y<=-1.8f && b.y>=-2.2f && b.x>=-1.5f && b.x<=1.5f)
            ball1.set_position(b.x+0.02f,b.y+0.2f);
        if(b.y<=-1.5f && b.y>=-1.8f && b.x>=-1.5f && b.x<=1.5f)
            ball1.set_position(b.x+0.02f,b.y+0.3f);
        ball1.left();
    }
    if (right)
    {
        if(b.y<=-2.2f && b.x>=-1.5f && b.x<=1.5f)
            ball1.set_position(b.x-0.05f,b.y+0.1f);
        if(b.y<=-1.8f && b.y>=-2.2f && b.x>=-1.5f && b.x<=1.5f)
            ball1.set_position(b.x-0.02f,b.y+0.2f);
        if(b.y<=-1.5f && b.y>=-1.8f && b.x>=-1.5f && b.x<=1.5f)
            ball1.set_position(b.x-0.02f,b.y+0.3f);
        ball1.right();
    }
    if (up)
    {
        if(b.y<-1.5f)
            ball1.up(0.2f);
        else
            ball1.up(0.3f);
    }
    ball1.tick();

    if (key_a && screen_center_x - 4/screen_zoom > -4) {
        screen_center_x -= 0.07;
        reset_screen();
    }
    if (key_s && screen_center_y - 4/screen_zoom > -4) {
        screen_center_y -= 0.07;
        reset_screen();
    }
    if (key_d && screen_center_x + 4/screen_zoom < 4) {
        screen_center_x += 0.07;
        reset_screen();
    }
    if (key_w && screen_center_y + 4/screen_zoom < 4) {
        screen_center_y += 0.07;
        reset_screen();
    }

    if (mouse_clicked) {
        if (drag_oldx == -1 && drag_oldy == -1) {
            glfwGetCursorPos(window, &drag_oldx, &drag_oldy);
        }
        else {
            int w, h;
            double new_x, new_y;
            glfwGetCursorPos(window, &new_x, &new_y);
            glfwGetWindowSize(window, &w, &h);
            float pos_x, pos_y;
            pos_x = 8 * (new_x - drag_oldx) / (w * screen_zoom);
            ball1.position.x = pos_x;
        }
    }
}

void tick_elements() {
    porcupine.tick();
    if (magnet.alive) {
            magnet_duration -= 1;
            if (magnet.alive) {
                if (ball1.position.y >= 2 && ball1.position.y <= 2.8 && ball1.position.x >= -2.3) {
                    ball1.position.x -= 0.05;
                }
            }
            if (magnet_duration <= 0) {
                magnet_duration = 700;
                magnet.alive = 0;
            }
        }
        else {
            magnet_start_time -= 1;
            if (magnet_start_time <= 0) {
                magnet_start_time = 1000;
                //int rand_magnet = rand() % 2;
                magnet.alive = 1;
                //cout<<"Magnet"<<endl;
            }
        }
    for(int i=0;i<2;i++)
    {
        balls[i].tick();
        bounding_box_t a =balls[i].bounding_box();
        bounding_box_t b =ball1.bounding_box();
        float r=rand()%4;
        float y=(r>=1)?rand()%4:-1*(rand()%4);
        if (detect_collision(ball1.bounding_box(), balls[i].bounding_box(),1) && b.yspeed>0) {
            float sp = b.yspeed;
            ball1.set_speedy(sp - 0.03f,0);
            balls[i].set_position(-4,y);
            score.add2();
        }
        if(a.x>=5)
            balls[i].set_position(-4,y);
    }
    for(int i=0;i<2;i++)
    {
        slope[i].tick();
        bounding_box_t a =slope[i].bounding_box();
        bounding_box_t b =slope[i].bounding_box();
        float r=rand()%4;
        float y=(r>=1)?rand()%4:-1*(rand()%4);
        if (detect_collision(ball1.bounding_box(), slope[i].bounding_box(),1)) {
            float sp = b.yspeed;
            float sp1 = b.xspeed;
            ball1.set_speedy(sp - 2.0f, 0);
            ball1.set_speedx(sp1 - 2.0f, 0);
            slope[i].set_position(-4,y);
            //ball1.position.x = ball1.yspeed;
            ball1.yspeed=0;
            score.add1();
            //cout<<"Collide"<<endl;
        }
        if(a.x>=5)
            slope[i].set_position(-4,y);
    }
    gravity();
    bounding_box_t b =ball1.bounding_box();
    if(b.y==-1.5f && ((b.x>=-1.4f && b.x<=1.6f) || (b.x>=1.6f && b.x<=1.7f)))
        ball1.set_position(b.x+0.3f,b.y);
    ball1.tick();
    if (detect_collision_trampoline(ball1.bounding_box(), trampoline.bounding_box(), 0) && ball1.yspeed < 0) {
        //printf("11\n");
        //ball1.yspeed += 0.15;
        ball1.yspeed = -1 * ball1.yspeed;
        }
    if (detect_collision_porcupine()) {
            ball1.position.x = 0;
            ball1.position.y = -1.8;
            if(life.decrease()) {
                quit(window);
            }
            score.subtract();
        }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    base = Rect(-0,0,COLOR_BLACK);
    ba = Ball(0,-2,1.5f,0,COLOR_BACKGROUND);
    ball1 = Ball(0, -1.5f, 0.5f, 0, COLOR_RED);
    sball = Semi(0,-2,1.5,COLOR_BLUE);
    trampoline = Trampoline(0.75f, 2.5f, -0.75f, 1.25f, 0.1f, COLOR_GOLD);
    porcupine = Porcupine(-3, -1.4, -2.5, -4, 0.01, COLOR_PURPLE);
    magnet = Magnet(-3.5, 2, COLOR_MAGNET, 0);
    life.init();
    //ball2       = Ball(-2, 0, 1, COLOR_RED);
    for(int i=0;i<5;i++)
    {
        float v=rand()%3;
        float r=rand()%4;
        float y=(abs(rand()/double(RAND_MAX)))*5+1.5f;
        v = (v==0)?0.5:v;
        //float y=(r<=3)?-1*r:r;
        balls[i]=Ball(-4,y,r/3,v/10,COLOR_GREEN);
        //cout<<"22"<<endl;
    }

    for(int i=0;i<5;i++)
    {
        float v=rand()%3;
        float r=rand()%4;
        float y=(abs(rand()/double(RAND_MAX)))*5+1.5f;
        v = (v==0)?0.5:v;
        //float y=(r<=3)?-1*r:r;
        slope[i]=Slope(-4,y,COLOR_PLANK,r/3,v/10);
        //cout<<"22"<<endl;
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    score.update(0);
    audio_init();
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        audio_play();
        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            //cout<<"pp"<<endl;
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b , int i) {
    double ss = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
    return (ss< (a.ri + i*b.ri)*(a.ri + i*b.ri))?true:false;
}

bool detect_collision_trampoline(bounding_box_t a, bounding_box_t b , int i) {
    return (a.x<=(b.x+b.ri) && a.x>=(b.x-b.ri) && (a.y-a.ri)<=b.y);
}

int detect_collision_porcupine() {
    float xmin = porcupine.position.x;
    float xmax = porcupine.position.x + 0.3;
    float xl = ball1.position.x - ball1.rad;
    float xr = ball1.position.x + ball1.rad;
    if (ball1.position.y <= -1 && ((xl <= xmax && xl >= xmin) || (xr >= xmin && xr <= xmax))) {
        return 1;
    }
    return 0;
}

bool detect_collision_pl(bounding_box_t a, bounding_box_t b) {
    if((a.x>(b.x-b.ri*sqrt(2)) && a.x<b.x) && (a.y<(b.y+b.ri*sqrt(2)) && a.y>b.y))
        return 1;
    else
        return 0;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void gravity()
{
    ball1.set_speedx(0,1);
    bounding_box_t b =ball1.bounding_box();
    bounding_box_t c =ba.bounding_box();
    if(b.y>-1.5)
    {
        float sp = b.yspeed;
        ball1.set_speedy(sp+(0.001f-0.0001f),1);
    }
    else if(b.y<=-1.5f && b.x>=-1.5f && b.x<=1.7f)
    {
        if(!detect_collision(ball1.bounding_box(), ba.bounding_box(),-1))
        {
            //cout <<"1"<<endl;
            ball1.set_speedy(0,1);
            if(b.x>=-1.3f && b.x<0)
                ball1.set_speedx(0.01f,1);
            else if(b.x>0 && b.x<=1.5f)
                ball1.set_speedx(-0.01f,1);
            else
                ball1.set_speedx(0,1);
        }
        else
        {
            float sp = b.yspeed;
            ball1.set_speedy(sp+(0.002f-0.001f),1);
        }
    }
    else if(b.y<=-1.5f)
    {
        ball1.set_speedy(0,1);
    }

    if(b.x>=1.65 && b.x<=3.35 && b.y<=-0.7 && b.y>=-0.8)
    {
        float spd=b.yspeed;
        ball1.set_speedy(-1.5*spd,0);
    }
}
