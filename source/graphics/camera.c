#include "camera.h"

extern float m_ProjectionMatrix[16];

void InitCamera()
{
    float k = 1280.0f / 720.0f;
    loadIdentity(m_ProjectionMatrix);
    matrixOrtho(m_ProjectionMatrix, -1, 1, -k, k, -50.0f, 50.0f);
}
void UpdateCamProjection(float scale)
{
    float k = 1280.0f / 720.0f;
    matrixOrtho(m_ProjectionMatrix, -1 * scale, 1 * scale, -k * scale, k * scale, -50.0f, 50.0f);
}
