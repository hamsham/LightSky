/* 
 * File:   bone.h
 * Author: hammy
 *
 * Created on February 18, 2015, 10:28 PM
 */

#ifndef __LS_DRAW_BONE_H__
#define	__LS_DRAW_BONE_H__

#include <vector>

#include "lightsky/math/mat4.h"

#include "lightsky/draw/vertex.h"

namespace ls {
namespace draw {

class bone {
    private:
        math::mat4 offsetMatrix;
        
        std::vector<boneVertex> weightList;

    public:
        ~bone();
        
        bone();
        
        bone(const bone& b);
        
        bone(bone&& b);
        
        bone& operator =(const bone& b);
        
        bone& operator =(bone&& b);
        
        const math::mat4& getOffsetMatrix() const;
        
        math::mat4& getOffsetMatrix();
        
        void setOffsetMatrix(const math::mat4& om);
        
        unsigned getNumWeights() const;
        
        const boneVertex& getVertexWeight(unsigned index) const;
        
        boneVertex& getVertexWeight(unsigned index);
        
        void setVertexWeight(unsigned index, const boneVertex& weight);
        
        void addVertexWeight(const boneVertex& weight);
        
        void addVertexWeight(const boneVertex& weight, unsigned index);
        
        void removeVertexWeight(unsigned index);
        
        const std::vector<boneVertex>& getVertexWeights() const;
        
        std::vector<boneVertex>& getVertexWeights();
        
        void setVertexWeights(const std::vector<boneVertex>& weights);
        
        void setVertexWeights(std::vector<boneVertex>&& weights);
        
        void clearVertexWeights();
};

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_BONE_H__ */

