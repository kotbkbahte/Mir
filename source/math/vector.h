#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <math.h>



typedef struct
{
    float x, y;
} TVector2d;

typedef struct
{
    float x, y, z;
} TVector3d;

typedef struct
{
    float yaw, pitch, roll;
} TRotation3d;

TVector3d math_Vector3d(float x, float y, float z);
TVector2d math_v2dNormalize(TVector2d* v);
TVector3d math_v3dNormalize(TVector3d* v);
TVector3d math_v3dDifference(TVector3d* v1, TVector3d* v2);
TVector3d math_v3dCross(TVector3d* v1, TVector3d* v2);

TVector3d math_v3dScale(TVector3d* v1, float s);
TVector3d math_v3dSum(TVector3d* v1, TVector3d* v2);

float math_v3dDot(TVector3d* v1, TVector3d* v2);


float math_v2dLength(TVector2d* v);
float math_v3dLength(TVector3d* v);

void math_v3dPrint(TVector3d* v);

#endif // VECTOR_H_INCLUDED
