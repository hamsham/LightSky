
namespace ls {
namespace draw {

/*-------------------------------------
    Get a runtime ID associated with this object
-------------------------------------*/
inline unsigned atlas::getId() const {
    return atlasTex.getId();
}

/*-------------------------------------
    Retrieve the texture rectangle used by *this.
-------------------------------------*/
inline const texture& atlas::getTexture() const {
    return atlasTex;
}

/*-------------------------------------
    Get the texture object associated with *this
-------------------------------------*/
inline texture& atlas::getTexture() {
    return atlasTex;
}

/*-------------------------------------
    Retrieve the atlas entry specified by at a specific index.
-------------------------------------*/
inline const atlasEntry& atlas::getEntry(unsigned index) const {
    return entries[index];
}

/*-------------------------------------
    Retrieve the array of atlas entries contained within *this. 
-------------------------------------*/
inline const atlasEntry* atlas::getEntries() const {
    return entries;
}

/*-------------------------------------
    Get the number of atlas entries currently loaded
-------------------------------------*/
inline unsigned atlas::getNumEntries() const {
    return numEntries;
}

} // end draw namespace
} // end ls namespace
