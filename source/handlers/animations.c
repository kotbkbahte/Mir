#include "animations.h"

extern TAnimations m_MirAnimations;
extern TTextures m_MirTextures;

void InitAnimations()
{
    m_MirAnimations.m_TextureAnimationsCount = 8;
    m_MirAnimations.m_TextureAnimations = malloc(sizeof(TTextureAnimation) * m_MirAnimations.m_TextureAnimationsCount);

    for(int i = 0; i < 8; i++)
    {
        BindTextureToAnimation( m_MirAnimations.m_TextureAnimations + i , &m_MirTextures.m_AnimatedTextures[AT_WATER], i);

    }
}

void BindTextureToAnimation(TTextureAnimation* texture_animation,
                            TAnimatedTexture* animated_texture, int frame)
{
    texture_animation->m_AnimatedTexture = animated_texture;
    texture_animation->m_Frame = frame;
}



void InitTexAnimations()
{

}



void UpdateAnimations(float dt)
{
#define a m_MirAnimations
    for(int i = 0; i < a.m_TextureAnimationsCount; i++)
    {
        int tmp = a.m_TextureAnimations[i].m_AnimatedTexture->m_Count > a.m_TextureAnimations[i].m_Frame;
//        print_i(tmp);
        if(tmp)
        {
            a.m_TextureAnimations[i].m_Frame++;
//            print_i(a.m_TextureAnimations[i].m_Frame);
        }
        else
        {
            a.m_TextureAnimations[i].m_Frame = 0;
        }
    }
#undef a
}
