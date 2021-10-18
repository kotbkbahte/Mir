#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"


void matrixScale(float*, float, float, float );

void matrixFrustum(float* matrix, float left, float right, float bottom, float top, float zNear, float zFar);
void matrixPerspective(float* matrix, float fieldOfView, float aspectRatio, float zNear, float zFar);

void matrixLookAt(float*, TVector3d*, TVector3d*, TVector3d* );
void matrixOrtho(float*, float, float, float, float, float, float);
void matrixTranslate(float*, float, float, float );

void matrixRotateX(float*, float);
void matrixRotateY(float*, float);
void matrixRotateZ(float*, float);

void loadIdentity(float* );
void multiplyMatrix(float*, float*, float* );

float to_radians(float degrees);
int copyMatrix_fd(float* , double* );
int glhUnProjectf(float winx, float winy, float winz, float *modelview, float *projection, int *viewport, float *objectCoordinate);
void MultiplyMatrices4by4OpenGL_FLOAT(float *result, float *matrix1, float *matrix2);
int glhInvertMatrixf2(float *m, float *out);


void printMatrix(float*);
#endif // MATRIX_H_INCLUDED
