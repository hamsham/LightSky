/* 
 * File:   bone.cpp
 * Author: hammy
 * 
 * Created on February 18, 2015, 10:28 PM
 */

#include <utility>

#include "lightsky/draw/bone.h"

namespace ls {
namespace draw {

bone::~bone() {
}

bone::bone() {
}

bone::bone(const bone& b) :
    offsetMatrix{b.offsetMatrix},
    weightList{b.weightList}
{}

bone::bone(bone&& b) :
    offsetMatrix{std::move(b.offsetMatrix)},
    weightList{std::move(b.weightList)}
{}

bone& bone::operator=(const bone& b) {
    offsetMatrix = b.offsetMatrix;
    weightList = b.weightList;
    return *this;
}

bone& bone::operator=(bone&& b) {
    offsetMatrix = std::move(b.offsetMatrix);
    weightList = std::move(b.weightList);
    return *this;
}

const math::mat4& bone::getOffsetMatrix() const {
    return offsetMatrix;
}

math::mat4& bone::getOffsetMatrix() {
    return offsetMatrix;
}

void bone::setOffsetMatrix(const math::mat4& om) {
    offsetMatrix = om;
}

unsigned bone::getNumWeights() const {
    return weightList.size();
}

const boneVertex& bone::getVertexWeight(unsigned index) const {
    return weightList[index];
}

boneVertex& bone::getVertexWeight(unsigned index) {
    return weightList[index];
}

void bone::setVertexWeight(unsigned index, const boneVertex& weight) {
    weightList[index] = weight;
}

void bone::addVertexWeight(const boneVertex& weight) {
    weightList.push_back(weight);
}

void bone::addVertexWeight(const boneVertex& weight, unsigned index) {
    weightList.insert(weightList.begin() + index, weight);
}

void bone::removeVertexWeight(unsigned index) {
    weightList.erase(weightList.begin() + index);
}

const std::vector<boneVertex>& bone::getVertexWeights() const {
    return weightList;
}

std::vector<boneVertex>& bone::getVertexWeights() {
    return weightList;
}

void bone::setVertexWeights(const std::vector<boneVertex>& weights) {
    weightList = weights;
}

void bone::setVertexWeights(std::vector<boneVertex>&& weights) {
    weightList = std::move(weights);
}

void bone::clearVertexWeights() {
    weightList.clear();
}

} // end draw namespace
} // end ls namespace