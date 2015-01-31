/* 
 * File:   utils/dataResource.cpp
 * Author: Miles Lacey
 * 
 * Created on February 1, 2014, 11:09 PM
 */

#include <utility> // std::move
#include <new> // std::nothrow
#include <algorithm> // std::copy
#include <fstream> // std::fstream
#include <string>

#include "lightsky/utils/dataResource.h"

namespace ls {
namespace utils {

/*-------------------------------------
    Constructor
-------------------------------------*/
dataResource::dataResource() :
    resource{}
{}

/*-------------------------------------
    Copy Constructor
-------------------------------------*/
dataResource::dataResource(const dataResource& f) :
    resource{}
{
    setData(const_cast<char*>(f.pData), f.dataSize, true);
}

/*-------------------------------------
    Move Constructor
-------------------------------------*/
dataResource::dataResource(dataResource&& f) :
    resource{}
{
    pData = f.pData;
    f.pData = nullptr;
    dataSize = f.dataSize;
    f.dataSize = 0l;
}

/*-------------------------------------
    Destructor
-------------------------------------*/
dataResource::~dataResource() {
    unload();
}

/*-------------------------------------
    Unload a resource
-------------------------------------*/
void dataResource::unload() {
    delete [] pData;
    pData = nullptr;
    
    dataSize = 0l;
}

/*-------------------------------------
    Copy Operator
-------------------------------------*/
dataResource& dataResource::operator=(const dataResource& f) {
    setData(const_cast<char*>(f.pData), f.dataSize, true);
    return *this;
}

/*-------------------------------------
    Move Operator
-------------------------------------*/
dataResource& dataResource::operator =(dataResource&& f) {
    unload();
    
    pData = f.pData;
    f.pData = nullptr;
    dataSize = f.dataSize;
    f.dataSize = 0l;
    
    return *this;
}

/*-------------------------------------
    Open a file using UTF-8
-------------------------------------*/
bool dataResource::loadFile(const std::string& filename) {
    unload();
    
    std::ifstream fin;
    long size = 0;
    char* buffer = nullptr;
    
    fin.open(filename, std::ios_base::binary | std::ios_base::in);
    
    if (!fin.good()) {
        return false;
    }
    
    // get the file size
    fin.seekg(0, std::ios_base::end);
    size = fin.tellg();
    fin.seekg(0, std::ios_base::beg);
    
    // Determine of the file can successfully scanned,
    if (fin.bad() || fin.fail()) {
        fin.close();
        return false;
    }
    
    // load the file into memory
    buffer = new(std::nothrow) char[size];
    if (buffer != nullptr) {
        fin.read(buffer, size);
    }
    else {
        fin.close();
        return false;
    }
    
    // check for errors when reading the file
    if (fin.bad() || fin.fail()) {
        delete [] buffer;
        fin.close();
        return false;
    }
    
    // everything passed, set the data at *this
    this->pData = buffer;
    this->dataSize = size;
    fin.close();
    return true;
}

/*-------------------------------------
    Save with a UTF-8 filename
-------------------------------------*/
bool dataResource::saveFile(const std::string& filename) const {
    std::ofstream fout;
    
    fout.open(filename, std::ios_base::binary);
    
    if (!fout.good()) {
        return false;
    }
    
    fout.write(pData, dataSize);
    const bool ret = fout.good();
    fout.close();
    
    return ret;
}

/*-------------------------------------
    Set a resource's data
-------------------------------------*/
bool dataResource::setData(char* data, long size, bool copyMemory) {
    unload();
    
    if (data == nullptr || size == 0) {
        return true;
    }
    
    if (copyMemory == true) {
        pData = new char[size];

        if (pData == nullptr) {
            return false;
        }
        else {
            // make sure that there are no buffer overflows
            if (size > dataSize) {
                size = dataSize;
            }
            
            std::copy(data, data + size, pData);
            dataSize = size;
        }
    }
    else {
        pData = data;
        dataSize = size;
    }
    
    return true;
}

} // end utils namespace
} // end ls namespace
