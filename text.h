/* 
 * File:   text.h
 * Author: miles
 *
 * Created on February 17, 2014, 5:12 PM
 */

#ifndef __LS_TEXT_H__
#define	__LS_TEXT_H__

#include <GL/glew.h>

#include "bufferObject.h"
#include "renderer.h"
#include "textureAtlas.h"
#include "vertex.h"
#include "vertexArray.h"

enum text_properties : int {
    SPACES_PER_TAB = 4, // change as desired
    
    VERTICES_PER_GLYPH = 6 // Magic Number Eradicator.
};

/**
 * Utility function to get all of the non-whitespace characters in a string
 */
int getDrawableCharCount(const char* const str);

/**
 * Text mesh class
 */
class text {
    private:
        /**
         * Vertex array to describe the layout of the text buffer data
         */
        vertexArray vao;
        
        /**
         * A Vertex buffer object to hold all of the vertex data
         */
        vertexBuffer vbo;
        
        /**
         * The number of glyphs that will be drawn
         */
        int numGlyphs = 0;
        
        /**
         * Helper function to generate an array of indices
         */
        bool generateBufferData(int numIndices);
        
    public:
        /**
         * Constructor
         */
        constexpr text() :
            vao{},
            vbo{}
        {}
        
        /**
         * Copy Constructor -- DELETED
         */
        text(const text&) = delete;
        
        /**
         * Move Constructor
         * Moves the data from the input parameter into *this. No copies are
         * performed
         */
        text(text&&);
        
        /**
         * Destructor
         * Unloads all data used by *this
         */
        ~text() {
            terminate();
        }
        
        /**
         * Copy operator -- DELETED
         */
        text& operator=(const text&) = delete;
        
        /**
         * Move operator.
         * Moves all data from the input parameter into *this. No copies are
         * performed
         */
        text& operator=(text&&);
        
        /**
         * Generate vertex data by referencing the texture atlas
         * @param str the string to load into OpenGL.
         * @param ta the texture atlas to reference for the loading.
         * @return true if the load was successful. False if otherwise.
         */
        bool init(const char* str, const textureAtlas& ta);
        
        /**
         * Unload all data and free all memory used by *this.
         */
        void terminate();
        
        /**
         * Draw the textual content loaded into OpenGL.
         * 
         * @param instanceCount - determines the number of instances that
         * need to be drawn at runtime.
         */
        void draw(int instanceCount = 1) const;
        
        /**
         * Draw a single part of the total sub-meshes contained within *this.
         * This function already takes the vertex counts into account.
         * 
         * @param startPos
         * indicates the starting offset to the the mesh contained within *this
         * that should be drawn.
         * 
         * @param endPos
         * indicates the offset to the final sub-mesh contained within *this
         * that should be drawn.
         * 
         * @param instanceCount - determines the number of instances that
         * need to be drawn at runtime.
         */
        void drawSubMesh(int startPos, int endPos, int instanceCount = 1) const;
};

inline void text::draw(int instanceCount) const {
    vao.bind();
    glDrawArraysInstanced(LS_TRIANGLES, 0, numGlyphs, instanceCount);
    vao.unbind();
}

inline void text::drawSubMesh(int startPos, int endPos, int instanceCount) const {
    vao.bind();
    glDrawArraysInstanced(
        LS_TRIANGLES,
        startPos*VERTICES_PER_GLYPH, endPos*VERTICES_PER_GLYPH,
        instanceCount
    );
    vao.unbind();
}

#endif	/* __LS_TEXT_H__ */

