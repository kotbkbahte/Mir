#include "camera.h"

extern float m_ProjectionMatrix[16];
extern float m_IdentityMatrix[16];
extern float m_ViewMatrix[16];

extern TCore *Core;

void InitCamera()
{
    loadIdentity(m_ProjectionMatrix);
    loadIdentity(m_IdentityMatrix);
    loadIdentity(m_ViewMatrix);
    UpdateCamProjection(1/1.5f);
}
void UpdateCamProjection(float scale)
{
    float k = 1280.0f / 720.0f;
    matrixOrtho(m_ProjectionMatrix, -1 * scale, 1 * scale, -k * scale, k * scale, -25.0f, 25.0f);
//    print_f(k * scale);
}
