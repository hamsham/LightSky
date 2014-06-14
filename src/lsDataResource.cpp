/* 
 * File:   dataResource.cpp
 * Author: hammy
 * 
 * Created on February 1, 2014, 11:09 PM
 */

#include <utility> // std::move
#include <new> // std::nothrow
#include <algorithm> // std::copy
#include <fstream> // std::fstream

#include "lsDataResource.h"

/******************************************************************************
 * Data Resource Construction
*******************************************************************************/
/**
 * Move Constructor
 */
lsDataResource::lsDataResource(lsDataResource&& f) :
    lsResource{}
{
    this->operator =(std::move(f));
}

/******************************************************************************
 * Data Resource Unloading
*******************************************************************************/
/*
 * Unload a resource
 */
void lsDataResource::unload() {
    delete [] pData;
    pData = nullptr;
    
    dataSize = 0l;
}

/******************************************************************************
 * Moving
******************************************************************************/
lsDataResource& lsDataResource::operator =(lsDataResource&& f) {
    unload();
    
    pData = f.pData;
    f.pData = nullptr;
    dataSize = f.dataSize;
    f.dataSize = 0l;
    
    return *this;
}

/******************************************************************************
 * Opening files
*******************************************************************************/
/*
 * Open a file
 * ANSI
 */
bool lsDataResource::loadFile(const char* filename) {
    LS_LOG_MSG("Attempting to load the file ", filename, '.');
    unload();
    
    std::ifstream fin;
    long size = 0;
    char* buffer = nullptr;
    
    fin.open(filename, std::ios_base::binary | std::ios_base::in);
    
    if (!fin.good()) {
        LS_LOG_ERR("Unable to open the file ", filename, ".\n");
        return false;
    }
    
    // get the file size
    fin.seekg(0, std::ios_base::end);
    size = fin.tellg();
    fin.seekg(0, std::ios_base::beg);
    
    // Determine of the file can successfully scanned,
    if (fin.bad() || fin.fail()) {
        LS_LOG_ERR("An error occurred while scanning the file ", filename, ".\n");
        fin.close();
        return false;
    }
    
    // load the file into memory
    buffer = new(std::nothrow) char[size];
    if (buffer != nullptr) {
        fin.read(buffer, size);
    }
    else {
        LS_LOG_ERR("Unable to allocate memory to open the file ", filename, ".\n");
        fin.close();
        return false;
    }
    
    // check for errors when reading the file
    if (fin.bad() || fin.fail()) {
        LS_LOG_ERR("Unable to read open the file ", filename, ".\n");
        delete [] buffer;
        fin.close();
        return false;
    }
    
    // everything passed, set the data at *this
    LS_LOG_MSG("Successfully loaded ", filename, ".\n");
    this->pData = buffer;
    this->dataSize = size;
    fin.close();
    return true;
}

/******************************************************************************
 * Saving files
*******************************************************************************/
/*
 * Save with an ANSI filename
 */
bool lsDataResource::saveFile(const char* filename) const {
    std::ofstream fout;
    
    LS_LOG_MSG("Attempting to save data to the file", filename, '.');
    fout.open(filename, std::ios_base::binary);
    
    if (!fout.good()) {
        LS_LOG_ERR(
            "An error occurred while attempting to create the file ",
            filename, ".\n"
        );
        return false;
    }
    
    fout.write(pData, dataSize);
    
    if (!fout.good()) {
        LS_LOG_ERR(
            "An error occurred while attempting to saving data to ",
            filename, ".\n"
        );
    }
    else {
        LS_LOG_MSG("Successfully saved data to ",filename, ".\n");
    }
    
    fout.close();
    return true;
}

/******************************************************************************
 * Data manipulation
*******************************************************************************/
/*
 * Set a resource's data
 */
bool lsDataResource::setData(char* data, long size, bool copyMemory) {
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
