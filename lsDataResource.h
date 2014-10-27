/* 
 * File:   dataResource.h
 * Author: hammy
 *
 * Created on February 1, 2014, 11:09 PM
 */

#ifndef __LS_DATA_RESOURCE_H__
#define	__LS_DATA_RESOURCE_H__

#include "main.h"
#include "resource.h"

/**
 * Basic memory object/file abstraction.
 * The dataResource base class can be fully constructed and will load a
 * complete file into RAM. When calling either openFile() or saveFile()
 * using a wide character string, the function merely converts the wide string
 * into a multi-byte character string, then delegates the rest of the file
 * operation to the c-string openFile/closeFile methods. This means that if
 * this class is derived from, there is little need to overload the wide-string
 * methods.
 */
class dataResource final : public resource {
    public:
        /**
         * Constructor
         */
        constexpr dataResource() :
            resource{}
        {}

        /**
         * Copy constructor
         * Attempts to copy all data from the source operand into *this.
         */
        dataResource(const dataResource& f) :
            resource{}
        {
            setData(const_cast<char*>(f.pData), f.dataSize, true);
        }

        /**
         * Move constructor
         * Move all memory from the source object into *this. No copies are
         * performed during this operation.
         */
        dataResource(dataResource&&);

        /**
         * Destructor.
         * Calls "unload()" and releases all memory from *this.
         */
        virtual ~dataResource() {
            unload();
        }

        /**
         * Copy operator
         * Attempts to copy all data from the source operand into *this.
         * 
         * @return a reference to *this.
         */
        dataResource& operator =(const dataResource& f) {
            setData(const_cast<char*>(f.pData), f.dataSize, true);
            return *this;
        }
        
        /**
         * Move operator
         * Move all memory from the source file object into *this. No copies
         * are performed during this operation.
         * 
         * @return a reference to *this.
         */
        dataResource& operator =(dataResource&& f);

        /**
         * Load a file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const char* filename) override;

        /**
         * Save a file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const char*) const override;

        /**
         * Unload
         * Free all memory used by *this.
         */
        virtual void unload() override;

        /**
         * Copy data into *this.
         * 
         * @param data a pointer to some other data that will be copied into
         * *this.
         * 
         * @param size the size, in bytes of the data being copied.
         * 
         * @param should the data be copied or inherited?
         * 
         * @return true if the copy was successful. False if otherwise.
         */
        virtual bool setData(char* data, long size, bool copyMemory);
};

#endif	/* __LS_DATA_RESOURCE_H__ */

