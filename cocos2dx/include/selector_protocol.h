/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __COCOA_SELECTOR_PROTOCOL_H__
#define __COCOA_SELECTOR_PROTOCOL_H__

#include "ccTypes.h"
#include "NSObject.h"
#include "ccxCommon.h"

namespace   cocos2d {
class CCNode;
class NSEvent;

class CCX_DLL SelectorProtocol
{
public:
	virtual void update(ccTime dt) {};
	virtual void tick(ccTime dt){};
	virtual void callfunc(){};
	virtual void callfunc(CCNode* pSender){};
	virtual void callfunc(CCNode* pSender, void* pData){};
	virtual void menuHandler(NSObject* pSender){};
    virtual void eventHandler(NSEvent* pEvent) {};

	// the child call responding retain/release function
	virtual void selectorProtocolRetain(void) {};
	virtual void selectorProtocolRelease(void) {};
};

class CCNode;
typedef void (SelectorProtocol::*SEL_SCHEDULE)(ccTime);

typedef void (SelectorProtocol::*SEL_CallFunc)();
typedef void (SelectorProtocol::*SEL_CallFuncN)(CCNode*);
typedef void (SelectorProtocol::*SEL_CallFuncND)(CCNode*, void*);
typedef void (SelectorProtocol::*SEL_CallFuncO)(NSObject*);
typedef void (SelectorProtocol::*SEL_MenuHandler)(NSObject*);
typedef void (SelectorProtocol::*SEL_EventHandler)(NSEvent*);

//  #define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(*((SEL_SCHEDULE*)(&(&_SELECTOR))) )
//  #define callfunc_selector(_SELECTOR) (SEL_CallFunc)(*((SEL_CallFunc*)(&(&_SELECTOR))) )
//  #define callfuncN_selector(_SELECTOR) (SEL_CallFuncN)(*((SEL_CallFuncN*)(&(&_SELECTOR))) )
//  #define callfuncND_selector(_SELECTOR) (SEL_CallFuncND)(*((SEL_CallFuncND*)(&(&_SELECTOR))) )
//  #define menu_selector(_SELECTOR) (SEL_MenuHandler)(*((SEL_MenuHandler*)(&(&_SELECTOR)))

  #define schedule_selector(_SELECTOR) (SEL_SCHEDULE)(&_SELECTOR)
  #define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)
  #define callfuncN_selector(_SELECTOR) (SEL_CallFuncN)(&_SELECTOR)
  #define callfuncND_selector(_SELECTOR) (SEL_CallFuncND)(&_SELECTOR)
  #define callfuncO_selector(_SELECTOR) (SEL_CallFuncO)(&_SELECTOR)
  #define menu_selector(_SELECTOR) (SEL_MenuHandler)(&_SELECTOR)
  #define event_selector(_SELECTOR) (SEL_EventHandler)(&_SELECTOR)
}//namespace   cocos2d 

#endif // __COCOA_SELECTOR_PROTOCOL_H__
