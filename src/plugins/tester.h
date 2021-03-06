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

#ifndef BASICX_PLUGINS_TESTER_H
#define BASICX_PLUGINS_TESTER_H

#include "plugins.h"

namespace basicx {

	void Test_Plugins() {
		basicx::Plugins* plugins = basicx::Plugins::GetInstance();
		Plugins_X* plugins_x = nullptr;
		plugins_x = plugins->GetPluginsX( "plugin_test_1" );
		if( plugins_x != nullptr ) {
			plugins_x->StartPlugin();
		}
		plugins_x = plugins->GetPluginsX( "plugin_test_2" );
		if( plugins_x != nullptr ) {
			plugins_x->StartPlugin();
		}
	}

} // namespace basicx

#endif // BASICX_PLUGINS_TESTER_H
