#include "texture_handler.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../extern/stb_image.h"


extern GLuint m_Textures[TEXTURES_COUNT];
extern GLuint m_GameTextures[TG_COUNT];
//extern FT_Library ft2_lib;
extern FT_Face ft2_face;
extern TCharTexture m_Characters[128];


void LoadTextures()
{
    LoadTexture("assets/buttons/PlayGame.png", &m_Textures[BUTTON_PLAYGAME]);
    LoadTexture("assets/buttons/Settings.png", &m_Textures[BUTTON_SETTINGS]);
    LoadTexture("assets/buttons/Quit.png",     &m_Textures[BUTTON_QUIT]);

    LoadTexture("assets/buttons/Back.png",  &m_Textures[BUTTON_BACK]);
    LoadTexture("assets/warrior1.png",      &m_Textures[BUTTON_WAR1]);
    LoadTexture("assets/warrior2.png",      &m_Textures[BUTTON_WAR2]);
    LoadTexture("assets/warrior3.png",      &m_Textures[BUTTON_WAR3]);

    LoadTexture("assets/Change_bg_dark.png",          &m_Textures[BUTTON_CHANGE_BG_DARK]);
    LoadTexture("assets/buttons/Change_bg.png",       &m_Textures[BUTTON_CHANGE_BG]);
    LoadTexture("assets/Test_1_dark.png",             &m_Textures[BUTTON_TEST_1_DARK]);
    LoadTexture("assets/buttons/Test_1.png",          &m_Textures[BUTTON_TEST_1] );
    LoadTexture("assets/Print_Log_dark.png",          &m_Textures[BUTTON_PRINT_LOG_DARK]);
    LoadTexture("assets/buttons/Print_Log.png",       &m_Textures[BUTTON_PRINT_LOG]);

    LoadTexture("assets/background.png",        &m_Textures[BACKGROUND_IMAGE]);
    LoadTexture("assets/background1.png",       &m_Textures[BACKGROUND_IMAGE_SPACE]);

    LoadTexture("assets/field/grass_dark_1.png",   &m_GameTextures[TG_GRASS_DARK]);
    LoadTexture("assets/field/grass_light_1.png",  &m_GameTextures[TG_GRASS_LIGHT]);
    LoadTexture("assets/field/blue1.png",          &m_GameTextures[TG_SEA]);
    LoadTexture("assets/field/blue2.png",          &m_GameTextures[TG_BLUE]);
    LoadTexture("assets/field/blue3.png",          &m_GameTextures[TG_OCEAN]);
    LoadTexture("assets/field/selected.png",       &m_GameTextures[TG_SELECTED]);

    LoadTexture("assets/field/tower.png",          &m_GameTextures[TG_TOWER]);
    LoadTexture("assets/field/warrior.png",        &m_GameTextures[TG_WARRIOR]);
    LoadTexture("assets/field/rock.png",           &m_GameTextures[TG_ROCK]);
}

//int LoadTexture(const char* file_name, TScene* scene, int texture_type)
void LoadTexture(const char* file_name, GLuint* texture)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;

    //printf("%s\n", file_name);
    unsigned char *data = stbi_load(file_name, &width, &height, &nrChannels, 0);
    if (nrChannels < 4)
    {
        h_error_msg("Loaded image have < 4 color channels\n", ERROR);
    }

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        h_log_msg_arg("Failed load texture: %s\n", (char*)file_name);
    }
    stbi_image_free(data);
}

/*
void LoadCharactersStrokesTextures()
{

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(ft2_face, c, FT_LOAD_RENDER))
        {
            h_log_msg_arg("Failed to load Glyph: %c\n", (char*)c);
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            ft2_face->glyph->bitmap.width,
            ft2_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            ft2_face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use


        m_Characters[c].m_TextureID = texture;
        m_Characters[c].m_Size.x = ft2_face->glyph->bitmap.width;
        m_Characters[c].m_Size.y = ft2_face->glyph->bitmap.rows;
        m_Characters[c].m_Bearing.x = ft2_face->glyph->bitmap_left;
        m_Characters[c].m_Bearing.y = ft2_face->glyph->bitmap_top;
        m_Characters[c].m_Advance = ft2_face->glyph->advance.x;


    }

}
*/


void LoadCharactersTextures()
{

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(ft2_face, c, FT_LOAD_RENDER))
        {
            h_log_msg_arg("Failed to load Glyph: %c\n", (char*)&c);
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            ft2_face->glyph->bitmap.width,
            ft2_face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            ft2_face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use


        m_Characters[c].m_TextureID = texture;
        m_Characters[c].m_Size.x = ft2_face->glyph->bitmap.width;
        m_Characters[c].m_Size.y = ft2_face->glyph->bitmap.rows;
        m_Characters[c].m_Bearing.x = ft2_face->glyph->bitmap_left;
        m_Characters[c].m_Bearing.y = ft2_face->glyph->bitmap_top;
        m_Characters[c].m_Advance = ft2_face->glyph->advance.x;


    }

}


void SetupTexture(GLuint* texture, int w, int h)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}
