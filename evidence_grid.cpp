#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include "evidence_grid.h"

EvidenceGrid::EvidenceGrid(const int g) {
    this->grid = new float*[g]();
    for (int i = 0; i < g; i++) {
        this->grid[i] = new float[g]();
        for (int j = 0; j < g; j++) {
            this->grid[i][j] = 0.5f;
        }
    }
    this->size = g;
    this->robot_info = new float[3];
    this->robot_info[0] = 0.0;
    this->robot_info[1] = 0.0;
    this->robot_info[2] = 0.0;
}

void EvidenceGrid::update_grid(std::vector< std::vector<float> > external_grid, std::vector<float> robot_info) {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            this->grid[i][j] = external_grid[i][j];
        }
    }
    this->robot_info[0] = robot_info[0];
    this->robot_info[1] = robot_info[1];
    this->robot_info[2] = robot_info[2];
}

void EvidenceGrid::retrieve_grid(std::vector< std::vector<float> > *external_grid, std::vector<float> *robot_info) {
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            (*external_grid)[i][j] = this->grid[i][j];
        }
    }
    (*robot_info)[0] =  this->robot_info[0];
    (*robot_info)[1] =  this->robot_info[1]/(this->size/2); 
    (*robot_info)[2] =  this->robot_info[2]/(this->size/2); 
}
