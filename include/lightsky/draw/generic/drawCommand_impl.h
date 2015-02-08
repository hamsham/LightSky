
namespace ls {
namespace draw {

/*-----------------------------------------------------------------------------
 * draw_index_pair_t
-----------------------------------------------------------------------------*/
/*-------------------------------------
 * Index Constructor
-------------------------------------*/
constexpr draw_index_pair_t::draw_index_pair_t(const unsigned f, const unsigned c) : 
    first{f},
    count{c}
{}

/*-------------------------------------
 * Copy Constructor
-------------------------------------*/
constexpr draw_index_pair_t::draw_index_pair_t(const draw_index_pair_t& drawIndex) : 
    first{drawIndex.first},
    count{drawIndex.count}
{}

/*-------------------------------------
 * Move Constructor
-------------------------------------*/
constexpr draw_index_pair_t::draw_index_pair_t(draw_index_pair_t&& drawIndex) : 
    first{drawIndex.first},
    count{drawIndex.count}
{}

/*-------------------------------------
 * Copy Operator
-------------------------------------*/
inline draw_index_pair_t& draw_index_pair_t::operator=(const draw_index_pair_t& drawIndex) {
    first = drawIndex.first;
    count = drawIndex.count;
    return *this;
}

/*-------------------------------------
 * Move Operator
-------------------------------------*/
inline draw_index_pair_t& draw_index_pair_t::operator=(draw_index_pair_t&& drawIndex) {
    first = drawIndex.first;
    count = drawIndex.count;
    return *this;
}
        
} // end draw namespace
} // end ls namespace

