/*
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

#ifndef PLUGIN_TEST_2_PLUGIN_TEST_2_P_H
#define PLUGIN_TEST_2_PLUGIN_TEST_2_P_H

#include "plugin_test_2.h"

#include <syslog/syslog.h>

class plugin_test_2_P
{
public:
	plugin_test_2_P();
	~plugin_test_2_P();

public:
	void SetGlobalPath();

public:
	bool Initialize();
	bool InitializeExt( plugin_test_2* strate_test );
	bool StartPlugin( plugin_test_2* strate_test );
	bool IsPluginRun( plugin_test_2* strate_test );
	bool StopPlugin( plugin_test_2* strate_test );
	bool UninitializeExt( plugin_test_2* strate_test );
	bool Uninitialize();
	bool AssignTask( int32_t task_id, int32_t identity, int32_t code, std::string& data );

private:
	std::string m_log_cate;
	basicx::SysLog_S* m_syslog;

// �Զ����Ա�����ͱ���

};

#endif // PLUGIN_TEST_2_PLUGIN_TEST_2_P_H
