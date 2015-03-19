/****************************************************************************/
/***                                                                      ***/
/***   (C) 2012-2014 Dierk Ohlerich et al., all rights reserved.          ***/
/***                                                                      ***/
/***   Released under BSD 2 clause license, see LICENSE.TXT               ***/
/***                                                                      ***/
/****************************************************************************/

#ifndef FILE_ALTONA2_LIBS_BASE_SYSTEM_POSIX_HPP
#define FILE_ALTONA2_LIBS_BASE_SYSTEM_POSIX_HPP

#include "Altona2/Libs/Base/Base.hpp"

namespace Altona2 {

#if sConfigPlatform==sConfigPlatformLinux || sConfigPlatform==sConfigPlatformOSX || sConfigPlatform==sConfigPlatformIOS || sConfigPlatform==sConfigPlatformAndroid

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

class sThreadPrivate
{
public:
  sThreadPrivate();
};

/****************************************************************************/

class sThreadLockPrivate
{
public:
  void *lock;
};

/****************************************************************************/

class sThreadEventPrivate
{
public:
  sThreadEventPrivate();
};

/****************************************************************************/

class sSharedMemoryPrivate  // dummy
{
protected:
};

/****************************************************************************/

namespace Private {

struct sWinMessage
{
    void *Window;
    uint Message;
    uint wparam;
    sptr lparam;
};

extern sHook1<const sWinMessage &> sWinMessageHook;

enum sMouseLockId
{
    sMLI_None = 0,
    sMLI_Mouse,
    sMLI_Wintab,            // Wacom
};

bool AquireMouseLock(sMouseLockId mouselockid);
bool TestMouseLock(sMouseLockId mouselockid);
void ReleaseMouseLock(sMouseLockId mouselockid);
}

#endif  // sConfigPlatform==sConfigPlatformLinux || sConfigPlatform==sConfigPlatformOSX || sConfigPlatform==sConfigPlatformIOS

}

#endif  // FILE_ALTONA2_LIBS_BASE_SYSTEM_POSIX_HPP
