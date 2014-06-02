/* 
 * File:   text.h
 * Author: miles
 *
 * Created on June 1, 2014, 9:25 PM
 */

#ifndef __LS_TEXT_H__
#define	__LS_TEXT_H__

#include "main.h"
#include "bufferObject.h"
#include "renderer.h"
#include "vertexArray.h"
#include "vertex.h"
#include "textureAtlas.h"

enum text_properties {
    SPACES_PER_TAB      = 4,
    VERTICES_PER_GLYPH  = 6
};

/**
 * Renderable character strings that can be loaded using font/texture atlases.
 * 
 * This object type follows similar functionality as meshResource->mesh
 */
class text {
    private:
        /**
         * Vertex array to be used with this text object
         */
        vertexArray vao;
        
        /**
         * Vertex Buffer Object to be used with this text
         */
        vertexBuffer vbo;
        
        /**
         * Vertex Buffer that will be used specifically for model matrices.
         */
        vertexBuffer modelVbo;
        
        /**
         * Member to help determine the number of vertices contained within a
         * text object.
         */
        unsigned numVertices = 0;
        
        /**
         * Counter of the number of instances that are currently reserved for
         * drawing in the vao & vbo. This is also a cound of the number of model
         * matrices that are held within the vbo.
         */
        unsigned numInstances = 1;
        
        /**
         * Helper function to ensure that the vao/vbo combos are loaded.
         */
        bool initVertices(unsigned numVerts);
        
        /**
         * Helper function to ensure all vertex attributes are setup properly.
         */
        void setVertexAttribs();
        
    public:
        /**
         * Constructor
         */
        constexpr text() :
            vao{},
            vbo{},
            numVertices{},
            numInstances{}
        {}
        
        /**
         * Copy Constructor -- DELETED
         */
        text(const text&) = delete;
        
        /**
         * Move Constructor.
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        text(text&&);
        
        /**
         * Destructor
         * Unloads all resources used by *this.
         */
        ~text() {
            terminate();
        }
        
        /**
         * Copy Operator -- DELETED
         */
        text& operator=(const text&) = delete;
        
        /**
         * Move Operator
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         */
        text& operator=(text&&);
        
        /**
         * Get an general identification to be used for this object
         */
        inline unsigned getId() {
            return vbo.getId();
        }
        
        /**
         * Send a loaded text to the GPU
         * @param ta
         * A texture atlas containing glyph metrics
         * 
         * @param str
         * A string that should be loaded from the texture Atlas (containing a
         * table of font bitmaps).
         */
        bool init(const textureAtlas& ta, const std::string& str);
        
        /**
         * Unload all GPU-based resource that are used by *this;
         */
        void terminate() {
            vao.terminate();
            vbo.terminate();
            modelVbo.terminate();
            numVertices = 0;
            numInstances = 1;
        }
        
        /**
         * All meshes support instanced draws by default. This will set the
         * number of instances that will appear when drawing text.
         * 
         * @param instanceCount
         * The number of instances (and modelMatrices) that will be drawn by
         * this text.
         * 
         * @param modelMatrices
         * A pointer to an array of model matrices that will be applied to each
         * text instance.
         */
        void setNumInstances(int instanceCount, const math::mat4* const modelMatrices);
        
        /**
         * Change the model matrix for a single instance
         * 
         * @param index
         * @param modelMatrix
         */
        void modifyInstance(int index, const math::mat4& modelMatrix);
        
        /**
         * Get the number of instances that will be rendered when a call to
         * "draw()" is made.
         * 
         * @return the number of meshes/model matrices rendered by/with this
         * text.
         * 
         * Changing this will cause the same text to be repeated in the
         * positions specified by each model matrix contained within this.
         */
        unsigned getNumInstances() const {
            return numInstances;
        }
        
        /**
         * Draw a string of text
         * 
         * This method renders a mesh to the currently bound framebuffer.
         */
        void draw() const;
        
        /**
         * Draw a substring of text using the vertices contained within this.
         * 
         * @param startPos
         * indicates the starting offset to the first character that should be
         * rendered.
         * 
         * @param endPos
         * indicates the offset to the final character contained within *this
         * that should be drawn.
         */
        void drawSubMesh(int startPos, int endPos) const;
};

inline void text::draw() const {
    vao.bind();
    glDrawArraysInstanced(LS_TRIANGLES, 0, numVertices, numInstances);
    vao.unbind();
}

inline void text::drawSubMesh(int startPos, int endPos) const {
    vao.bind();
    glDrawArraysInstanced(LS_TRIANGLES, startPos, endPos, numInstances);
    vao.unbind();
}

#endif	/* __LS_TEXT_H__ */

