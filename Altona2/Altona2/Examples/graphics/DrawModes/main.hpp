/****************************************************************************/
/***                                                                      ***/
/***   (C) 2012-2014 all rights reserved.                                 ***/
/***                                                                      ***/
/***   Released under BSD 2 clause license, see LICENSE.TXT               ***/
/***                                                                      ***/
/****************************************************************************/

#ifndef FILE_ALTONA2_EXAMPLES_GRAPHICS_DRAW_MODE_HPP
#define FILE_ALTONA2_EXAMPLES_GRAPHICS_DRAW_MODE_HPP

#include "Altona2/Libs/Base/Base.hpp"
#include "Altona2/Libs/Util/DebugPainter.hpp"
#include "shader.hpp"

using namespace Altona2;

class DrawerBase;

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

class App : public sApp
{
    static const uint MAXMODE = 10;
    sInt DrawMode;
    DrawerBase * Drawer[MAXMODE];

    sDebugPainter *DPaint;
    sAdapter *Adapter;
    sContext *Context;
    sScreen *Screen;
public:
    App();
    ~App();

    void OnInit();
    void OnExit();
    void OnFrame();
    void OnPaint();
    void OnKey(const sKeyData &kd);
    void OnDrag(const sDragData &dd);
};

/****************************************************************************/

class DrawerBase
{
public:
    sMaterial *Mtrl;
    sResource *Tex;
    sCBuffer<CubeShader_cbvs> *cbv0;
    sAdapter *Adapter;
    sContext *Context;

public:
    DrawerBase(sAdapter * Adapter);
    virtual ~DrawerBase();
    virtual void Draw(const sTargetPara &tp) = 0;
};

/****************************************************************************/

class Draw1 : public DrawerBase
{
public:
    Draw1(sAdapter * Adapter);
    ~Draw1();
    void Draw(const sTargetPara &tp);
};

/****************************************************************************/

class Draw2 : public DrawerBase
{
    sGeometry *Geo;
public:
    Draw2(sAdapter * Adapter);
    ~Draw2();
    void Draw(const sTargetPara &tp);
};

#endif  // FILE_ALTONA2_EXAMPLES_GRAPHICS_DRAW_MODE_HPP

