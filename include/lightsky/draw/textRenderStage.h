/* 
 * File:   textRenderStage.h
 * Author: Miles Lacey
 *
 * Created on January 31, 2015, 4:52 PM
 */

#ifndef __LS_DRAW_TEXT_RENDER_STAGE_H__
#define	__LS_DRAW_TEXT_RENDER_STAGE_H__

#include "lightsky/draw/renderStage.h"
#include "lightsky/draw/shaderObject.h"
#include "lightsky/draw/shaderProgram.h"

namespace ls {
namespace draw {

class textRenderStage : public renderStage {
    private:
    
    public:
        virtual ~textRenderStage() override;
        
        textRenderStage();
        
        textRenderStage(const textRenderStage& rs);
        
        textRenderStage(textRenderStage&& rs);
        
        textRenderStage& operator=(const textRenderStage& rs);
        
        textRenderStage& operator=(textRenderStage&& rs);
};

} // end draw namespace
} // end ls namespace

#endif	/* __LS_DRAW_TEXT_RENDER_STAGE_H__ */
