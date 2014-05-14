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

#include "CCTime.h"

#include <Windows.h>

namespace   cocos2d {

// although it is not the same as gettimeofday as unix
// but we only use the diffrences of tow values
int CCTime::gettimeofdayCocos2d(struct cc_timeval *tp, void *tzp)
{
	unsigned int ms = GetTickCount();
	tp->tv_sec = ms / 1000;
	tp->tv_usec = (ms % 1000) * 1000;
	return 0;
}

void CCTime::timersubCocos2d(struct cc_timeval *out, struct cc_timeval *start, struct cc_timeval *end)
{
	out->tv_sec = end->tv_sec - start->tv_sec;
	out->tv_usec = end->tv_usec - start->tv_usec;
}

}//namespace   cocos2d 
