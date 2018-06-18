//
// Created by Tursom Ulefits on 2018/6/15.
//

#include "Exception.h"
#include "../utils/StringBuilder.h"
#include "../lang/CPlusString.h"
#include "../thread/ThreadMutex.h"

#include <Windows.h>

namespace cplus {
	namespace system {
		
		typedef ULONG (WINAPI *RTLWALKFRAMECHAIN)(OUT PVOID *Callers, IN ULONG Count, IN ULONG Flags);
		
		RTLWALKFRAMECHAIN RtlWalkFrameChain =
				(RTLWALKFRAMECHAIN) GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlWalkFrameChain");
		
		lang::String Exception::getStack() {
			PVOID ary[MAX_PATH] = {nullptr}; //这里应该动态分配内存实现，直接用数组是偷懒的办法。
			ULONG StackCount;
			StackCount = RtlWalkFrameChain(ary, MAX_PATH, 0);
			utils::StringBuilder sb;
			sb.append("StackCount=");
			sb.append(StackCount);
			sb.append("\n");
			for (ULONG i = 0; i < StackCount; i++) {
				sb.append("Stack[");
				sb.append(i);
				sb.append("]=");
				sb.append(ary[i]);
				sb.append("\n");
			}
			return sb.toString();
		}
	}
}