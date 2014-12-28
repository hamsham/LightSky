/* 
 * File:   utils/pointer.h
 * Author: miles
 *
 * Created on November 10, 2014, 10:29 PM
 */

#ifndef __LS_UTILS_POINTER_H__
#define	__LS_UTILS_POINTER_H__

namespace ls {
namespace utils {

/**----------------------------------------------------------------------------
 * Single Pointer Type
-----------------------------------------------------------------------------*/
template <typename data_t>
struct pointer {
    private:
        /**
         * pData represents a pointer to some data within an application
         */
        mutable data_t* pData = nullptr;
        
        /**
         * Clear *this of any data/resources.
         */
        void clear() {
            delete pData;
        }
        
    public:
        /**
         * Destructor
         * 
         * Clear *this of any data/resources.
         */
        ~pointer() {
            clear();
        }
        
        /**
         * Constructor
         * 
         * Creates an empty pointer type. Which should not be dereferenced
         * under any circumstances.
         */
        pointer() :
            pData{nullptr}
        {}
        
        /**
         * Pointer Constructor
         * 
         * @param p
         * A pointer to dynamically-allocated data.
         */
        explicit pointer(data_t* const p) :
            pData{p}
        {}
        
        /**
         * Copy Constructor -- DE:ETED
         */
        pointer(const pointer&) = delete;
        
        /**
         * Move Constructor
         * 
         * Moves data from the input parameter into *this.
         * 
         * @param p
         * A pointer type containing dynamically-allocated data.
         */
        pointer(pointer&& p) :
            pData{p.pData}
        {
            p.pData = nullptr;
        }
        
        /**
         * Copy Operator -- DELETED
         */
        pointer& operator=(const pointer&) = delete;
        
        /**
         * Move Operatpr
         * 
         * Moves data from the input parameter into *this.
         * 
         * @param p
         * A pointer type containing dynamically-allocated data.
         * 
         * @return
         * A reference to *this.
         */
        pointer& operator=(pointer&& p) {
            clear();
            pData = p.pData;
            p.pData = nullptr;
            return *this;
        }
        
        /**
         * Equal-To Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer to the same
         * data as *this, FALSE if not.
         */
        constexpr bool operator == (const pointer& p) const {
            return pData == p.pData;
        }
        
        /**
         * Not-Equal-To Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer to different
         * data than *this, FALSE if so.
         */
        constexpr bool operator != (const pointer& p) const {
            return pData != p.pData;
        }
        
        /**
         * Greater-Than or Equal-To Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer to the same
         * data as or less than, or equal to, *this, FALSE if not.
         */
        constexpr bool operator >= (const pointer& p) const {
            return pData >= p.pData;
        }
        
        /**
         * Greater-Than Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer of less
         * value than *this, FALSE if not.
         */
        constexpr bool operator > (const pointer& p) const {
            return pData > p.pData;
        }
        
        /**
         * Less-Than or Equal-To Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer to the same
         * data as or greater than *this, FALSE if not.
         */
        constexpr bool operator <= (const pointer& p) const {
            return pData <= p.pData;
        }
        
        /**
         * Less-Than Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer of greater
         * value than *this, FALSE if not.
         */
        constexpr bool operator < (const pointer& p) const {
            return pData < p.pData;
        }
        
        /**
         * Retrieve the pointer to data contained within *this.
         * 
         * @return A pointer to a set of dynamically-allocated data.
         */
        constexpr const data_t* get() const {
            return pData;
        }
        
        /**
         * Retrieve the pointer to data contained within *this.
         * 
         * @return A pointer to a set of dynamically-allocated data.
         */
        data_t* get() {
            return pData;
        }
        
        /**
         * Swap the value of the pointers contained within *this and an input
         * pointer object.
         * 
         * @param other
         * A pointer object who's data should be swapped with *this.
         */
        void swap(pointer& other) {
            data_t* temp = other.pData;
            other.pData = this->pData;
            this->pData = temp;
        }
        
        /**
         * Retrieve a reference to the data contained within *this.
         * 
         * @return A reference to the dynamically-allocated data within *this.
         */
        const data_t& operator *() const {
            return *pData;
        }
        
        /**
         * Retrieve a reference to the data contained within *this.
         * 
         * @return A reference to the dynamically-allocated data within *this.
         */
        data_t& operator *() {
            return *pData;
        }
        
        /**
         * Free all data referenced by *this.
         * This method will delete all data that *this object references.
         */
        void release() {
            clear();
            pData = nullptr;
        }
        
        /**
         * Delete the value of the internal pointer managed by this, then use
         * *this to reference a new set of data.
         * 
         * @param pNewData
         * A pointer to a set of dynamically-allocated memory of the same type
         * as *this.
         */
        void reset(data_t* pNewData = nullptr) {
            clear();
            pData = pNewData;
        }
};

/**----------------------------------------------------------------------------
 * Array Pointer Type
 * (Specialized in order to allow for array-types)
-----------------------------------------------------------------------------*/
//template <>
template <typename data_t>
struct pointer<data_t[]> {
    private:
        /**
         * pData represents a pointer to some data within an application
         */
        mutable data_t* pData = nullptr;
        
        /**
         * Clear *this of any data/resources.
         */
        void clear() {
            delete [] pData;
        }
        
    public:
        /**
         * Destructor
         * 
         * Clear *this of any data/resources.
         */
        ~pointer() {
            clear();
        }
        
        /**
         * Constructor
         * 
         * Creates an empty pointer type. Which should not be dereferenced
         * under any circumstances.
         */
        pointer() :
            pData{nullptr}
        {}
        
        /**
         * Pointer Constructor
         * 
         * @param p
         * A pointer to dynamically-allocated data.
         */
        explicit pointer(data_t* const p) :
            pData{p}
        {}
        
        /**
         * Copy Constructor -- DE:ETED
         */
        pointer(const pointer&) = delete;
        
        /**
         * Move Constructor
         * 
         * Moves data from the input parameter into *this.
         * 
         * @param p
         * A pointer type containing dynamically-allocated data.
         */
        pointer(pointer&& p) :
            pData{p.pData}
        {
            p.pData = nullptr;
        }
        
        /**
         * Copy Operator -- DELETED
         */
        pointer& operator=(const pointer&) = delete;
        
        /**
         * Move Operatpr
         * 
         * Moves data from the input parameter into *this.
         * 
         * @param p
         * A pointer type containing dynamically-allocated data.
         * 
         * @return
         * A reference to *this.
         */
        pointer& operator=(pointer&& p) {
            clear();
            pData = p.pData;
            p.pData = nullptr;
            return *this;
        }
        
        /**
         * Equal-To Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer to the same
         * data as *this, FALSE if not.
         */
        constexpr bool operator == (const pointer& p) const {
            return pData == p.pData;
        }
        
        /**
         * Not-Equal-To Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer to different
         * data than *this, FALSE if so.
         */
        constexpr bool operator != (const pointer& p) const {
            return pData != p.pData;
        }
        
        /**
         * Greater-Than or Equal-To Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer to the same
         * data as or less than, or equal to, *this, FALSE if not.
         */
        constexpr bool operator >= (const pointer& p) const {
            return pData >= p.pData;
        }
        
        /**
         * Greater-Than Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer of less
         * value than *this, FALSE if not.
         */
        constexpr bool operator > (const pointer& p) const {
            return pData > p.pData;
        }
        
        /**
         * Less-Than or Equal-To Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer to the same
         * data as or greater than *this, FALSE if not.
         */
        constexpr bool operator <= (const pointer& p) const {
            return pData <= p.pData;
        }
        
        /**
         * Less-Than Operator
         * 
         * @param p
         * A constant reference to a pointer object of the same type as *this.
         * 
         * @return TRUE if the input parameter contains a pointer of greater
         * value than *this, FALSE if not.
         */
        constexpr bool operator < (const pointer& p) const {
            return pData < p.pData;
        }
        
        /**
         * Iterate through all of the memory managed by *this.
         * 
         * @param i
         * The index of the data in the internal array managed by *this.
         * 
         * @return
         * A constant reference to some data contained within the
         * heap-allocated array managed by *this.
         */
        constexpr data_t& operator [] (std::size_t i) const {
            return pData[i];
        }
        
        /**
         * Iterate through all of the memory managed by *this.
         * 
         * @param i
         * The index of the data in the internal array managed by *this.
         * 
         * @return
         * A reference to some data contained within the heap-allocated array
         * managed by *this.
         */
        inline data_t& operator [] (std::size_t i) {
            return pData[i];
        }
        
        /**
         * Retrieve the pointer to data contained within *this.
         * 
         * @return A pointer to a set of dynamically-allocated data.
         */
        constexpr const data_t* get() const {
            return pData;
        }
        
        /**
         * Retrieve the pointer to data contained within *this.
         * 
         * @return A pointer to a set of dynamically-allocated data.
         */
        data_t* get() {
            return pData;
        }
        
        /**
         * Swap the value of the pointers contained within *this and an input
         * pointer object.
         * 
         * @param other
         * A pointer object who's data should be swapped with *this.
         */
        void swap(pointer& other) {
            data_t* temp = other.pData;
            other.pData = this->pData;
            this->pData = temp;
        }
        
        /**
         * Retrieve a reference to the data contained within *this.
         * 
         * @return A reference to the dynamically-allocated data within *this.
         */
        const data_t& operator *() const {
            return *pData;
        }
        
        /**
         * Retrieve a reference to the data contained within *this.
         * 
         * @return A reference to the dynamically-allocated data within *this.
         */
        data_t& operator *() {
            return *pData;
        }
        
        /**
         * Free all data referenced by *this.
         * This method will delete all data that *this object references.
         */
        void release() {
            clear();
            pData = nullptr;
        }
        
        /**
         * Delete the value of the internal pointer managed by this, then use
         * *this to reference a new set of data.
         * 
         * @param pNewData
         * A pointer to a set of dynamically-allocated memory of the same type
         * as *this.
         */
        void reset(data_t* pNewData = nullptr) {
            clear();
            pData = pNewData;
        }
};

} // ens utils namespace
} // end ls namespace

#endif	/* __LS_UTILS_POINTER_H__ */
