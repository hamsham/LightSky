/* 
 * File:   lsDataResource.h
 * Author: hammy
 *
 * Created on February 1, 2014, 11:09 PM
 */

#ifndef __LS_DATA_RESOURCE_H__
#define	__LS_DATA_RESOURCE_H__

#include <string>

#include "lsSetup.h"
#include "lsResource.h"

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
class lsDataResource final : public lsResource {
    public:
        /**
         * Constructor
         */
        lsDataResource();

        /**
         * Copy constructor
         * Attempts to copy all data from the source operand into *this.
         */
        lsDataResource(const lsDataResource&);

        /**
         * Move constructor
         * Move all memory from the source object into *this. No copies are
         * performed during this operation.
         */
        lsDataResource(lsDataResource&&);

        /**
         * Destructor.
         * Calls "unload()" and releases all memory from *this.
         */
        virtual ~lsDataResource() override;

        /**
         * Copy operator
         * Attempts to copy all data from the source operand into *this.
         * 
         * @return a reference to *this.
         */
        lsDataResource& operator =(const lsDataResource& f);
        
        /**
         * Move operator
         * Move all memory from the source file object into *this. No copies
         * are performed during this operation.
         * 
         * @return a reference to *this.
         */
        lsDataResource& operator =(lsDataResource&& f);

        /**
         * Load a file
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const std::string& filename) override;

        /**
         * Save a file
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const std::string&) const override;

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
        bool setData(char* data, long size, bool copyMemory);
};

#endif	/* __LS_DATA_RESOURCE_H__ */

