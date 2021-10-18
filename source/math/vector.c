#include "Vector.h"

TVector3d math_v3dScale(TVector3d* v1, float s)
{
    TVector3d res;
    res.x = v1->x * s;
    res.y = v1->y * s;
    res.z = v1->z * s;
    return res;
}

TVector3d math_v3dSum(TVector3d* v1, TVector3d* v2)
{
    TVector3d res;
    res.x = v1->x + v2->x;
    res.y = v1->y + v2->y;
    res.z = v1->z + v2->z;
    return res;
}


TVector3d math_Vector3d(float x, float y, float z)
{
    TVector3d res = {x, y, z};
    return res;
}


TVector3d math_v3dDifference(TVector3d* v1, TVector3d* v2)
{
    TVector3d res = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
    return res;
}

TVector3d math_v3dCross(TVector3d* v1, TVector3d* v2)
{
    TVector3d v3 = {v1->y * v2->z - v1->z * v2->y,
                    v1->z * v2->x - v1->x * v2->z,
                    v1->x * v2->y - v1->y * v2->x};
    return v3;
}

float math_v3dDot(TVector3d* v1, TVector3d* v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

float math_v2dDot(TVector2d* v1, TVector2d* v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}


TVector2d math_v2dNormalize(TVector2d* v)
{
    float l = math_v2dLength(v);
    TVector2d res = {0, 0};
    if(l == 0)
        return res;
    res.x = v->x / l;
    res.y = v->y / l;
    return res;
}

TVector3d math_v3dNormalize(TVector3d* v)
{
    float l = math_v3dLength(v);
    TVector3d res = {0, 0, 0};
    if(l==0)
        return res;
    res.x = v->x / l;
    res.y = v->y / l;
    res.z = v->z / l;
    return res;
}

float math_v2dLength(TVector2d* v)
{
    return sqrt(v->x * v->x + v->y * v->y);
}

float math_v3dLength(TVector3d* v)
{
    return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}


void math_v3dPrint(TVector3d* v)
{
    printf("V: %.2f %.2f %.2f\n", v->x, v->y, v->z);
}


