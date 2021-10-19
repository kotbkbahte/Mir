#include "main_menu.h"

void DrawMainMenu()
{
    gltInit();

    // Creating text
    GLTtext *text = gltCreateText();
    gltSetText(text, "Hello World!");

    // Begin text drawing (this for instance calls glUseProgram)
    gltBeginDraw();

    // Draw any amount of text between begin and end
    glEnable(GL_BLEND);
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);

    gltDrawText2D(text, 2, 4, 7.0f);
    glDisable(GL_BLEND);

    // Finish drawing text
    gltEndDraw();

    // Deleting text
    gltDeleteText(text);

    // Destroy glText
    gltTerminate();

    /*
    glBindTexture(GL_TEXTURE_2D, m_Textures[1]);

    glUseProgram(m_GlProgram.ID);
    float m[16];
    loadIdentity(m);

    glUniformMatrix4fv(m_GlProgram.projectionLocation, 1, GL_FALSE, m_ProjectionMatrix);
    glUniformMatrix4fv(m_GlProgram.viewLocation, 1, GL_FALSE, m);
    glUniformMatrix4fv(m_GlProgram.modelLocation, 1, GL_FALSE, m);


    glVertexAttribPointer(m_GlProgram.vertexLocation, 3, GL_FLOAT, GL_FALSE, 0 , squareVertices);
    glEnableVertexAttribArray(m_GlProgram.vertexLocation);

    glVertexAttribPointer(m_GlProgram.textureCoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
    glEnableVertexAttribArray(m_GlProgram.textureCoordsLocation);


    //glLineWidth(10.0f);
    //glPointSize(7.0f);
    //glDrawArrays(GL_POINTS, 0, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


    glBindTexture(GL_TEXTURE_2D, 0);

    //printMatrix(m);
    //printMatrix(m_ProjectionMatrix);
    //exit(0);
    */
}
