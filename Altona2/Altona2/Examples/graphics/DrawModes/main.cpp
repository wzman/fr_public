/****************************************************************************/
/***                                                                      ***/
/***   (C) 2012-2014 Dierk Ohlerich et al., all rights reserved.          ***/
/***                                                                      ***/
/***   Released under BSD 2 clause license, see LICENSE.TXT               ***/
/***                                                                      ***/
/****************************************************************************/

#include "main.hpp"
#include "shader.hpp"

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

const sInt ic = 6 * 6;
const sInt vc = 24;

static const sVertexPNT cubeVertices[vc] =
{
    { -1, 1, -1, 0, 0, -1, 0, 0, },
    { 1, 1, -1, 0, 0, -1, 1, 0, },
    { 1, -1, -1, 0, 0, -1, 1, 1, },
    { -1, -1, -1, 0, 0, -1, 0, 1, },

    { -1, -1, 1, 0, 0, 1, 0, 0, },
    { 1, -1, 1, 0, 0, 1, 1, 0, },
    { 1, 1, 1, 0, 0, 1, 1, 1, },
    { -1, 1, 1, 0, 0, 1, 0, 1, },

    { -1, -1, -1, 0, -1, 0, 0, 0, },
    { 1, -1, -1, 0, -1, 0, 1, 0, },
    { 1, -1, 1, 0, -1, 0, 1, 1, },
    { -1, -1, 1, 0, -1, 0, 0, 1, },

    { 1, -1, -1, 1, 0, 0, 0, 0, },
    { 1, 1, -1, 1, 0, 0, 1, 0, },
    { 1, 1, 1, 1, 0, 0, 1, 1, },
    { 1, -1, 1, 1, 0, 0, 0, 1, },

    { 1, 1, -1, 0, 1, 0, 0, 0, },
    { -1, 1, -1, 0, 1, 0, 1, 0, },
    { -1, 1, 1, 0, 1, 0, 1, 1, },
    { 1, 1, 1, 0, 1, 0, 0, 1, },

    { -1, 1, -1, -1, 0, 0, 0, 0, },
    { -1, -1, -1, -1, 0, 0, 1, 0, },
    { -1, -1, 1, -1, 0, 0, 1, 1, },
    { -1, 1, 1, -1, 0, 0, 0, 1, },
};

static const sU16 cubeIndices[ic] =
{
    0, 1, 2, 0, 2, 3,
    4, 5, 6, 4, 6, 7,
    8, 9, 10, 8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23,
};

static const sVertexPNT triangleVertices[] =
{      // pos                   // normal               // uv
    { -0.5f, -0.5f,  0.0f,      0.0f,  0.0f, -1.0f,     0.0f, 0.0f,  },     // left-bottom
    {  0.5f, -0.5f,  0.0f,      0.0f,  0.0f, -1.0f,     1.0f, 0.0f,  },     // right-bottom
    {  0.0f,  0.5f,  0.0f,      0.0f,  0.0f, -1.0f,     0.5f, 1.0f,  }      // center-top
};

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

void Altona2::Main()
{
    sInt flags = 0;
    flags |= sSM_NoVSync;
    flags |= sSM_Debug;
    sRunApp(new App, sScreenMode(flags, "DrawModes", 1280, 720));
}

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

DrawerBase::DrawerBase(sAdapter * Adapter)
{
    this->Adapter = Adapter;
    this->Context = Adapter->ImmediateContext;

    Mtrl = 0;
    Tex = 0;

    const sInt sx = 64;
    const sInt sy = 64;
    sU32 tex[sy][sx];
    for (sInt y = 0; y < sy; y++)
    for (sInt x = 0; x < sx; x++)
        tex[y][x] = ((x^y) & 8) ? 0xffff8080 : 0xff80ff80;
    Tex = new sResource(Adapter, sResTexPara(sRF_BGRA8888, sx, sy, 1), &tex[0][0], sizeof(tex));

    Mtrl = new sMaterial(Adapter);
    Mtrl->SetShaders(CubeShader.Get(0));
    Mtrl->SetTexturePS(0, Tex, sSamplerStatePara(sTF_Linear | sTF_Clamp, 0));
    Mtrl->SetState(sRenderStatePara(sMTRL_DepthOn | sMTRL_CullOn, sMB_Off));
    Mtrl->Prepare(Adapter->FormatPNT);

    cbv0 = new sCBuffer<CubeShader_cbvs>(Adapter, sST_Vertex, 0);
}

DrawerBase::~DrawerBase()
{
    delete Mtrl;
    delete Tex;
    delete cbv0;
}

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

Draw1::Draw1(sAdapter * Adapter) :
    DrawerBase(Adapter)
{
}

Draw1::~Draw1()
{
}

void Draw1::Draw(const sTargetPara &tp)
{
    sU32 utime = sGetTimeMS();
    sF32 time = utime*0.001f;

    sVector41 scale(1,1,1);
    sVector3 rot(0, time, 0);
    sVector41 trans(0, 0, 0);

    sViewport view;
    view.Camera.k.w = -2;
    view.Model = sSetSRT(scale, rot, trans);
    view.ZoomX = 1 / tp.Aspect;
    view.ZoomY = 1;
    view.Prepare(tp);

    cbv0->Map();
    cbv0->Data->mat = view.MS2SS;
    cbv0->Data->ldir.Set(-view.MS2CS.k.x, -view.MS2CS.k.y, -view.MS2CS.k.z);
    cbv0->Unmap();

    static const sU32 vfdesc[] =
    {
        /*sVF_Stream0 |*/ sVF_Position | sVF_F3,
        /*sVF_Stream0 |*/ sVF_Normal | sVF_F3,
        /*sVF_Stream0 |*/ sVF_UV0 | sVF_F2,
        sVF_End,
    };

    sVertexFormat * format = Adapter->CreateVertexFormat(vfdesc);
    sDrawPara dp(1, 1, 1, Mtrl, cbv0);
    dp.Flags |= sDF_Arrays;
    dp.VertexArrayCount = 3;
    dp.VertexArray = (void*)triangleVertices;
    dp.VertexArrayFormat = format;

    Context->Draw(dp);
}

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

Draw2::Draw2(sAdapter * Adapter) :
    DrawerBase(Adapter)
{
    Geo = new sGeometry(Adapter);
    Geo->SetIndex(sResBufferPara(sRBM_Index | sRU_Static, sizeof(sU16), ic), cubeIndices);
    Geo->SetVertex(sResBufferPara(sRBM_Vertex | sRU_Static, sizeof(sVertexPNT), vc), cubeVertices);
    Geo->Prepare(Adapter->FormatPNT, sGMP_Tris | sGMF_Index16, ic, 0, vc, 0);
}

Draw2::~Draw2()
{
}

void Draw2::Draw(const sTargetPara &tp)
{
    sU32 utime = sGetTimeMS();
    sF32 time = utime*0.01f;

    sViewport view;
    view.Camera.k.w = -4;
    view.Model = sEulerXYZ(time*0.3f, time*0.2f, time*0.1f);
    view.ZoomX = 1 / tp.Aspect;
    view.ZoomY = 1;
    view.Prepare(tp);

    cbv0->Map();
    cbv0->Data->mat = view.MS2SS;
    cbv0->Data->ldir.Set(-view.MS2CS.k.x, -view.MS2CS.k.y, -view.MS2CS.k.z);
    cbv0->Unmap();

    Context->Draw(sDrawPara(Geo, Mtrl, cbv0));
}

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

App::App()
{
    DrawMode = 0;
    for (int i = 0; i < MAXMODE; i++)
        Drawer[i] = 0;
}

App::~App()
{
}

void App::OnInit()
{
    Screen = sGetScreen();
    Adapter = Screen->Adapter;
    Context = Adapter->ImmediateContext;

    Drawer[0] = new Draw1(Adapter);
    Drawer[1] = new Draw2(Adapter);


    DPaint = new sDebugPainter(Adapter);
}

void App::OnExit()
{
    for (int i = 0; i < MAXMODE; i++)
    {
        if (Drawer[i])
            delete Drawer[i];
    }
    delete DPaint;
}

void App::OnFrame()
{
}

void App::OnPaint()
{
    sTargetPara tp(sTAR_ClearAll, 0xff405060, Screen);

    Context->BeginTarget(tp);

    if (Drawer[DrawMode])
            Drawer[DrawMode]->Draw(tp);

    DPaint->PrintFPS();
    DPaint->PrintStats();
    DPaint->Draw(tp);

    Context->EndTarget();
}

void App::OnKey(const sKeyData &kd)
{
    sU32 key = sCleanKeyCode(kd.Key);
    switch (key)
    {
    case sKEY_Escape:
    case sKEY_Escape | sKEYQ_Shift:
        sExit();

    case sKEY_F1:
    case sKEY_F2:
    case sKEY_F3:
    case sKEY_F4:
    case sKEY_F5:
    case sKEY_F6:
    case sKEY_F7:
    case sKEY_F8:
    case sKEY_F9:
    case sKEY_F10:
    case sKEY_F11:
    case sKEY_F12:
        DrawMode = key - sKEY_F1;
        break;
    }
}

void App::OnDrag(const sDragData &dd)
{
}

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

/****************************************************************************/

