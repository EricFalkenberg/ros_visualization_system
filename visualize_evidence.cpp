#include <GL/glut.h>  
#include <stdlib.h>
#include <stdio.h> 
#include <vector>
#include <math.h>
#include "visualize_evidence.h"
#define PI 3.14159265

// GLOBAL VARIABLES
bool has_refreshed = false;
std::vector< std::vector<float> > vec;
float granularity;
EvidenceGrid shared_grid(0);
std::vector<float> robot_info(3, 0.0);

void updateEvidenceGrid() {
    shared_grid.retrieve_grid(&vec, &robot_info);
}

void dispatch_gfx() {
    int    argc          = GFX_ARGS.argc;
    char **argv          = GFX_ARGS.argv;
    int GRANULARITY      = GFX_ARGS.GRANULARITY;
    EvidenceGrid *n_grid = GFX_ARGS.grid;
    VisualizeEvidence(argc, argv, GRANULARITY, *n_grid);
}

void drawCircle(GLfloat x, GLfloat y, GLfloat radius) {
    double theta = robot_info[0];
    double r = 0.1;
    double dx = r*cosf(theta+PI/8);
    double dy = r*sinf(theta+PI/8);
    glLineWidth(1.0);
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex2f(robot_info[1], robot_info[2]);
        glVertex2f(robot_info[1]+dx, robot_info[2]+dy);
    glEnd();
    dx = r*cosf(theta-PI/8);
    dy = r*sinf(theta-PI/8);
    glLineWidth(1.0);
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex2f(robot_info[1], robot_info[2]);
        glVertex2f(robot_info[1]+dx, robot_info[2]+dy);
    glEnd();
    int i;
    int triangleAmount = 1000;
    GLfloat twicePi = 2.0f * PI;

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(5.0);

    glBegin(GL_LINES);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    for(i = 0; i <= triangleAmount; i++) {
        glVertex2f(x, y);
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();

}

void display() {
    float interval = 2.0 / granularity;
    float x = -1.0f;
    float y =  1.0f;

    // RETRIEVE GRID UPDATES FROM EVIDENCE GRID OBJECT

    updateEvidenceGrid();
    // WRITE EVIDENCE GRID TO GL BUFFER
    for (int i = 0; i < granularity; i++) {
        for (int j = 0; j < granularity; j++) {
            float c_val = 1.0 - vec[i][j];
            glBegin(GL_QUADS);         
                glColor3f(c_val, c_val, c_val);
                glVertex2f(x, y);   
                glVertex2f(x+interval, y);
                glVertex2f(x+interval, y-interval);
                glVertex2f(x, y-interval);
            glEnd();
            x = x + interval;
        }
        y = y - interval;
        x = -1.0f;
    }
    drawCircle(robot_info[1], robot_info[2], 0.001);    

    // FLUSH BUFFER TO SCREEN
    glFlush(); 
    glutPostRedisplay();
}
void VisualizeEvidence(int argc, char** argv, int g, EvidenceGrid v) {
    // INITIALIZE GRID
    vec.resize(g);
    for (int i = 0; i < g; i++) { 
        vec[i].resize(g); 
        for (int j = 0; j < g; j++) {
            vec[i][j] = 0.5f;
        }
    }
    
    // STORE SHARED OBJECT
    shared_grid = v;

    // SET GRANULARITY
    granularity = g;
    
    // SET UP OPENGL WINDOW
    glutInit(&argc, argv);                 
    glutCreateWindow("Evidence Grid Visualization"); 
    glutInitWindowSize(600, 600);  
    glutInitWindowPosition(0, 0);
    glutDisplayFunc(display); 
    glutMainLoop();      
}
