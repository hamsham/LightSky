/* 
 * File:   utils/dataResource.h
 * Author: Miles Lacey
 *
 * Created on February 1, 2014, 11:09 PM
 */

#ifndef __LS_UTILS_DATA_RESOURCE_H__
#define	__LS_UTILS_DATA_RESOURCE_H__

#include <string>

#include "lightsky/utils/setup.h"
#include "lightsky/utils/resource.h"

namespace ls {
namespace utils {

/**
 * @brief Basic memory object/file abstraction.
 * 
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
         * @brief Constructor
         * 
         * Initializes all members in *this and in the base resource class.
         */
        dataResource();

        /**
         * @brief Copy constructor
         * 
         * Attempts to copy all data from the source operand into *this.
         * 
         * @param dr
         * A constant reference to another data resource.
         */
        dataResource(const dataResource& dr);

        /**
         * @brief Move Constructor
         * 
         * Move all memory from the source object into *this. No copies are
         * performed during this operation.
         * 
         * @param dr
         * An r-value reference to another data resource.
         */
        dataResource(dataResource&& dr);

        /**
         * @brief Destructor
         * 
         * Calls "unload()" and releases all memory from *this.
         */
        virtual ~dataResource() override;

        /**
         * @brief Copy Operator
         * 
         * Attempts to copy all data from the source operand into *this.
         * 
         * @param dr
         * A constant reference to another data resource.
         * 
         * @return a reference to *this.
         */
        dataResource& operator =(const dataResource& dr);
        
        /**
         * @brief Move operator
         * 
         * Move all memory from the source file object into *this. No copies
         * are performed during this operation.
         * 
         * @param dr
         * An r-value reference to another data resource.
         * 
         * @return a reference to *this.
         */
        dataResource& operator =(dataResource&& dr);

        /**
         * @param Load a file
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be loadable into memory.
         * 
         * @return true if the file was successfully loaded. False if not.
         */
        virtual bool loadFile(const std::string& filename) override;

        /**
         * @param Save a file
         * 
         * @param filename
         * A string object containing the relative path name to a file that
         * should be saved to the computer.
         * 
         * @return true if the file was successfully saved. False if not.
         */
        virtual bool saveFile(const std::string& filename) const override;

        /**
         * @param Unload
         * 
         * Free all memory used by *this.
         */
        virtual void unload() override;

        /**
         * Copy data into *this.
         * 
         * @param data
         * A pointer to some other data that will be copied into
         * *this.
         * 
         * @param size
         * The size, in bytes of the data being copied.
         * 
         * @param copyMemory
         * Used to determine if the input data should be copied or moved into
         * *this.
         * 
         * @return true if the copy was successful. False if otherwise.
         */
        bool setData(char* data, long size, bool copyMemory);
};

} // end utils namespace
} // end ls namespace

#endif	/* __LS_UTILS_DATA_RESOURCE_H__ */
