/****************************************************************************/
/***                                                                      ***/
/***   (C) 2012-2014 Dierk Ohlerich et al., all rights reserved.          ***/
/***                                                                      ***/
/***   Released under BSD 2 clause license, see LICENSE.TXT               ***/
/***                                                                      ***/
/****************************************************************************/

#ifndef FILE_ALTONA2_EXAMPLES_GRAPHICS_CUBE_MAIN_HPP
#define FILE_ALTONA2_EXAMPLES_GRAPHICS_CUBE_MAIN_HPP

#include "Altona2/Libs/Base/Base.hpp"
#include "Altona2/Libs/Util/DebugPainter.hpp"
#include "shader.hpp"

using namespace Altona2;

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

class App : public sApp
{
  sMaterial *Mtrl;
  sResource *Tex[2];
  uint *Buffer;
  sGeometry *Geo;
  sCBuffer<CubeShader_cbvs> *cbv0;
  sDebugPainter *DPaint;
  sInt DBuffer;
  sRandomKISS Random;

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

#endif  // FILE_ALTONA2_EXAMPLES_GRAPHICS_CUBE_MAIN_HPP

