/* 
 * File:   lsResource.h
 * Author: hammy
 *
 * Created on February 1, 2014, 11:09 PM
 */

#ifndef __LS_RESOURCE_H__
#define	__LS_RESOURCE_H__

#include <string>

#include "lsSetup.h"
#include "lsUtil.h"

/**
 * Basic file/resource abstraction.
 * Resource Objects can open a file by calling either openFile() or saveFile()
 * using a wide character string, The function merely converts the wide string
 * into a multi-byte character string, then delegates the rest of the file
 * operation to the c-string openFile/closeFile methods. This means that if this
 * class is derived from, there is little need to overload the wide-string
 * methods.
 */
class lsResource {
    protected:
        /**
         * pData is a pointer to an array of bytes that hold a complete resource
         * in RAM. Data is automatically freed during a file object's
         * destruction but can also be freed by calling "unload()."
         */
        char* pData = nullptr;

        /**
         * dataSize holds the current size, in bytes, of the memory being used
         * by pData.
         */
        long dataSize = 0l;

    public:

        /**
         * Constructor
         */
        lsResource() = default;

        /**
         * Copy constructor
         * Attempts to copy all data from the source operand into *this.
         */
        lsResource(const lsResource&) = delete;

        /**
         * Move constructor
         * Move all memory from the source object into *this. No copies
         * are performed during this operation.
         */
        lsResource(lsResource&&) = delete;

        /**
         * Destructor.
         * Make sure to call "unload()" before an object goes out of scope.
         */
        virtual ~lsResource() = 0;

        /**
         * Copy operator
         * Attempts to copy all data from the source operand into *this.
         * 
         * @return a reference to *this.
         */
        lsResource& operator =(const lsResource&) = delete;
        
        /**
         * Move operator
         * Move all memory from the source object into *this. No copies are
         * performed during this operation.
         */
        lsResource& operator =(lsResource&& f) = delete;

        /**
         * Load a file
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const std::string&) = 0;

        /**
         * Load a file using a c-style string of wide (UTF-8) characters
         * 
         * This method merely converts the filename into a multi-byte string
         * and calls "openFile()" using the ANSI equivalent string.
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const std::wstring&);

        /**
         * Save a file
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const std::string&) const = 0;

        /**
         * Save a file using a c-style string of wide (UTF-8) characters
         * 
         * This method merely converts the filename into a multi-byte string
         * and calls "saveFile()" using the ANSI equivalent string.
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const std::wstring&) const;

        /**
         * Unload
         * Free all memory used by *this.
         */
        virtual void unload() = 0;

        /**
         * Get the size, in bytes, of the current file loaded into memory.
         */
        virtual long getByteSize() const;

        /**
         * Get the raw, loaded, data contained within *this.
         */
        virtual void* getData() const;
};

//-----------------------------------------------------------------------------
//      Inlined Methods
//-----------------------------------------------------------------------------
/*
 * Get the size, in bytes, of the current file loaded into memory.
 */
inline long lsResource::getByteSize() const {
    return dataSize;
}

/*
 * Get the raw, loaded, data contained within *this.
 */
inline void* lsResource::getData() const {
    return pData;
}

/*
 * Open a file with UTF-8
 */
inline bool lsResource::loadFile(const std::wstring& filename) {
    // attempt to load the file
    return loadFile(lsUtil::convertWtoMb(filename));
}

/*
 * Save with an UTF-8 filename
 */
inline bool lsResource::saveFile(const std::wstring& filename) const {
    // attempt to save the file
    return saveFile(lsUtil::convertWtoMb(filename));
}

#endif	/* __LS_RESOURCE_H__ */

