/* 
 * File:   textureManager.h
 * Author: miles
 *
 * Created on May 26, 2014, 11:23 AM
 */

#ifndef __LS_TEXTURE_MANAGER_H__
#define	__LS_TEXTURE_MANAGER_H__

class textureManager {
    private:
        
        
    public:
        textureManager();
        textureManager(const textureManager&) = delete;
        textureManager(textureManager&&);
        
        ~textureManager();
        
        textureManager& operator=(const textureManager&) = delete;
        textureManager& operator=(textureManager&&);
};

#endif	/* __LS_TEXTURE_MANAGER_H__ */

