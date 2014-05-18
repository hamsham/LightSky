/* 
 * File:   resource.h
 * Author: hammy
 *
 * Created on February 1, 2014, 11:09 PM
 */

#ifndef __LS_RESOURCE_H__
#define	__LS_RESOURCE_H__

/**
 * Basic file/resource abstraction.
 * Resource Objects can open a file by calling either openFile() or saveFile()
 * using a wide character string, The function merely converts the wide string
 * into a multi-byte character string, then delegates the rest of the file
 * operation to the c-string openFile/closeFile methods. This means that if this
 * class is derived from, there is little need to overload the wide-string
 * methods.
 */
class resource {
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
        constexpr resource() {
        }

        /**
         * Copy constructor
         * Attempts to copy all data from the source operand into *this.
         */
        resource(const resource&) = delete;

        /**
         * Move constructor
         * Move all memory from the source object into *this. No copies
         * are performed during this operation.
         */
        resource(resource&& f) = delete;

        /**
         * Destructor.
         * Make sure to call "unload()" before an object goes out of scope.
         */
        virtual ~resource() = 0;

        /**
         * Copy operator
         * Attempts to copy all data from the source operand into *this.
         * 
         * @return a reference to *this.
         */
        resource& operator =(const resource&) = delete;
        
        /**
         * Move operator
         * Move all memory from the source object into *this. No copies are
         * performed during this operation.
         */
        resource& operator =(resource&& f) = delete;

        /**
         * Load a file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const char* filename) = 0;

        /**
         * Load a file using a c-style string of wide (UTF-8) characters
         * 
         * This method merely converts the filename into a multi-byte string
         * and calls "openFile()" using the ANSI equivalent string.
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const wchar_t* filename);

        /**
         * Save a file
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const char*) const = 0;

        /**
         * Save a file using a c-style string of wide (UTF-8) characters
         * 
         * This method merely converts the filename into a multi-byte string
         * and calls "saveFile()" using the ANSI equivalent string.
         * 
         * @param filename a c-style string containing the relative path name
         * to a file that should be saved to the computer.
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const wchar_t*) const;

        /**
         * Unload
         * Free all memory used by *this.
         */
        virtual void unload() = 0;

        /**
         * Get the size, in bytes, of the current file loaded into memory.
         */
        virtual long getByteSize() const {
            return dataSize;
        }

        /**
         * Get the raw, loaded, data contained within *this.
         */
        virtual void* getData() const {
            return pData;
        }
};

#endif	/* __LS_RESOURCE_H__ */

