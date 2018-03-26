﻿/*
* Copyright (c) 2017-2018 the BasicX authors
* All rights reserved.
*
* The project sponsor and lead author is Xu Rendong.
* E-mail: xrd@ustc.edu, QQ: 277195007, WeChat: ustc_xrd
* You can get more information at https://xurendong.github.io
* For names of other contributors see the contributors file.
*
* Commercial use of this code in source and binary forms is
* governed by a LGPL v3 license. You may get a copy from the
* root directory. Or else you should get a specific written
* permission from the project author.
*
* Individual and educational use of this code in source and
* binary forms is governed by a 3-clause BSD license. You may
* get a copy from the root directory. Certainly welcome you
* to contribute code of all sorts.
*
* Be sure to retain the above copyright notice and conditions.
*/

#ifndef BASICX_COMMON_ASSIST_H
#define BASICX_COMMON_ASSIST_H

#include <tchar.h>
#include <stdint.h> // int32_t, int64_t
#include <iostream>

#include "sysdef.h"

#ifdef __OS_WINDOWS__
#include <windows.h>
#endif

namespace basicx {

	inline double Round( const double value, const size_t places ) {
		double result = 0.0;
		double module = value >= 0.0 ? 0.0000001 : -0.0000001;
		result = value;
		result += 5.0 / pow( 10.0, places + 1.0 );
		result *= pow( 10.0, places );
		result = floor( result + module );
		result /= pow( 10.0, places );
		return result;
	}

	inline double NearPrice( const double input_price, const double min_price_unit, const size_t price_places ) {
		int64_t price_temp = (int64_t)std::floor( input_price * std::pow( 10.0, price_places + 1 ) ); // 多保留一位，之后的截掉
		int64_t min_price_unit_temp = (int64_t)( min_price_unit * std::pow( 10.0, price_places + 1 ) );
		int64_t remainder_temp = price_temp % min_price_unit_temp;
		double min_price_unit_temp_half = (double)min_price_unit_temp / 2.0;
		// 下面比较大小，有可能均价刚好处于一个最小报价单位的中间，比如报价单位 0.05 均价 10.025 而上下两个价格为 10.05 和 10.00， 这里就用 >= 判断了，四舍五入嘛
		price_temp = remainder_temp >= min_price_unit_temp_half ? ( price_temp - remainder_temp + min_price_unit_temp ) : ( price_temp - remainder_temp );
		double output_price = (double)price_temp / std::pow( 10.0, price_places + 1 );
		// std::cout << std::setprecision( 6 ) << input_price << "：" << output_price << std::endl;
		return output_price;
	}

	inline int64_t GetPerformanceFrequency() {
#ifdef __OS_WINDOWS__
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency( &frequency ); // 每秒跳动次数
		return frequency.QuadPart;
#endif
	}

	inline int64_t GetPerformanceTickCount() {
#ifdef __OS_WINDOWS__
		LARGE_INTEGER tick_count;
		QueryPerformanceCounter( &tick_count ); // 当前跳动次数
		return tick_count.QuadPart;
#endif
	}

	// windows：
	// THREAD_PRIORITY_ERROR_RETURN (MAXLONG) 0x7FFFFFFF 2147483647
	// THREAD_PRIORITY_TIME_CRITICAL == THREAD_BASE_PRIORITY_LOWRT 15 // value that gets a thread to LowRealtime-1
	// THREAD_PRIORITY_HIGHEST == THREAD_BASE_PRIORITY_MAX 2 // maximum thread base priority boost
	// THREAD_PRIORITY_ABOVE_NORMAL (THREAD_PRIORITY_HIGHEST-1)
	// THREAD_PRIORITY_NORMAL 0
	// THREAD_PRIORITY_BELOW_NORMAL (THREAD_PRIORITY_LOWEST+1)
	// THREAD_PRIORITY_LOWEST == THREAD_BASE_PRIORITY_MIN (-2) // minimum thread base priority boost
	// THREAD_PRIORITY_IDLE == THREAD_BASE_PRIORITY_IDLE (-15) // value that gets a thread to idle

	inline void SetThreadPriority( const int32_t thread_priority ) {
		::SetThreadPriority( GetCurrentThread(), thread_priority );
	}

	inline bool BindProcess( const size_t processor_number ) {
#ifdef __OS_WINDOWS__
		if( processor_number >= 1 && processor_number <= 32 ) {
			typedef void (CALLBACK* ULPRET)(SYSTEM_INFO*);
			ULPRET proc_address;
			HINSTANCE library;
			SYSTEM_INFO system_info;
			library = LoadLibraryA( "kernel32.dll" );
			if( library ) {
				proc_address = (ULPRET)GetProcAddress( library, "GetNativeSystemInfo" );
				if( proc_address ) { // 可以用 GetNativeSystemInfo，但是32位程序中 ActiveProcessorMask 最大还是只能32位即4294967295
					(*proc_address)(&system_info); // 等同于 GetNativeSystemInfo( &system_info );
				}
				else {
					GetSystemInfo( &system_info ); // 在64位系统，NumberOfProcessors 最大 32 个，ProcessorArchitecture 为 0 不正确
				}
				FreeLibrary( library );
			}

			// std::cout << "处理器：线程 = " << system_info.dwNumberOfProcessors << ", 活动 = " << system_info.dwActiveProcessorMask << ", 水平 = " << system_info.wProcessorLevel << ", 架构 = " << system_info.wProcessorArchitecture << ", 分页 = " << system_info.dwPageSize << "\n";

			if( processor_number > (int32_t)system_info.dwNumberOfProcessors ) {
				// std::cout << "进程绑定处理器时，核心线程编号 " << processor_number << " 超过 核心线程数 " << system_info.dwNumberOfProcessors << " 个！" << "\n";
				return false;
			}
			else {
				DWORD temp = 0x0001;
				DWORD mask = 0x0000;
				for( int32_t i = 0; i < 32; i++ ) { // 32位 0x0000
					if( ( i + 1 ) == processor_number ) {
						mask = temp;
						break;
					}
					temp *= 2; // 前移一位
				}

				// if( SetProcessAffinityMask( GetCurrentProcess(), mask ) ) {
				if( SetThreadAffinityMask( GetCurrentThread(), mask ) ) {
					// std::cout << "线程绑定至第 " << processor_number << " 个核心线程完成。" << "\n" << "\n";
					return true;
				}
				else {
					// std::cout << "线程绑定至第 " << processor_number << " 个核心线程失败！" << "\n" << "\n";
					return false;
				}
			}
		}
		return false;
#endif
	}

	inline void SetMinimumTimerResolution() {
#ifdef __OS_WINDOWS__
		typedef uint32_t* ( WINAPI* lpNST )( uint32_t, bool, uint32_t* );
		typedef uint32_t* ( WINAPI* lpNQT )( uint32_t*, uint32_t*, uint32_t* );
		HMODULE library = LoadLibrary( TEXT( "ntdll.dll" ) );
		if( library ) {
			lpNST NtSetTimerResolution = (lpNST)GetProcAddress( library, "NtSetTimerResolution" );
			lpNQT NtQueryTimerResolution = (lpNQT)GetProcAddress( library, "NtQueryTimerResolution" );
			if( nullptr == NtQueryTimerResolution || nullptr == NtSetTimerResolution ) {
				printf( "SetMinimumTimerResolution: Search function failed!\n" );
			}
			else {
				uint32_t max = 0;
				uint32_t min = 0;
				uint32_t cur = 0;
				uint32_t ret = 0;
				if( 0 == NtQueryTimerResolution( &max, &min, &cur ) ) {
					NtSetTimerResolution( min, true, &ret );
				}
			}
			FreeLibrary( library );
		}
#endif
	}

} // namespace basicx

#endif // BASICX_COMMON_ASSIST_H
