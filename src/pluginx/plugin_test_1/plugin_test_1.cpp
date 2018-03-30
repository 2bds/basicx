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

#include "plugin_test_1.h"
#include "plugin_test_1_P.h"

plugin_test_1 g_plugin; // ����

// Ԥ�� plugin_test_1_P ����ʵ��

plugin_test_1_P::plugin_test_1_P()
	: m_log_cate( "<PLUGIN_TEST_1>" ) {
	//m_strLocation = "";
	//m_strInfFilePath = "";
	//m_strCfgFilePath = "";

	m_syslog = basicx::SysLog_S::GetInstance();
}

plugin_test_1_P::~plugin_test_1_P() {
}

void plugin_test_1_P::SetGlobalPath() {
	//m_pStrateInfo = m_pStrateCenter->FindStrateInfoByName( "plugin_test_1" ); // �͵����϶����Ի����
	//if( m_pStrateInfo )
	//{
	//	m_strLocation = m_pStrateInfo->GetLocation();
	//	m_strInfFilePath = m_pStrateInfo->GetInfoFilePath();
	//	m_strCfgFilePath = m_pStrateInfo->GetCfgFilePath();
	//}
}

bool plugin_test_1_P::Initialize() {
	SetGlobalPath();
	std::string log_info = "Initialize";
	m_syslog->LogPrint( basicx::syslog_level::c_hint, m_log_cate, log_info );
	return true;
}

bool plugin_test_1_P::InitializeExt( plugin_test_1* strate_test ) {
	std::string log_info = "InitializeExt";
	m_syslog->LogPrint( basicx::syslog_level::c_hint, m_log_cate, log_info );
	return true;
}

bool plugin_test_1_P::StartPlugin( plugin_test_1* strate_test ) {
	std::string log_info = "StartPlugin";
	m_syslog->LogPrint( basicx::syslog_level::c_info, m_log_cate, log_info );
	return true;
}

bool plugin_test_1_P::IsPluginRun( plugin_test_1* strate_test ) {
	std::string log_info = "IsPluginRun";
	m_syslog->LogPrint( basicx::syslog_level::c_info, m_log_cate, log_info );
	return true;
}

bool plugin_test_1_P::StopPlugin( plugin_test_1* strate_test ) {
	std::string log_info = "StopPlugin";
	m_syslog->LogPrint( basicx::syslog_level::c_info, m_log_cate, log_info );
	return true;
}

bool plugin_test_1_P::UninitializeExt( plugin_test_1* strate_test ) {
	std::string log_info = "UninitializeExt";
	m_syslog->LogPrint( basicx::syslog_level::c_warn, m_log_cate, log_info );
	return true;
}

bool plugin_test_1_P::Uninitialize() {
	std::string log_info = "Uninitialize";
	m_syslog->LogPrint( basicx::syslog_level::c_warn, m_log_cate, log_info );
	return true;
}

bool plugin_test_1_P::AssignTask( int32_t task_id, int32_t identity, int32_t code, std::string& data ) {
	std::string log_info = "AssignTask";
	m_syslog->LogPrint( basicx::syslog_level::c_info, m_log_cate, log_info );
	return true;
}

// �Զ��� plugin_test_1_P ����ʵ��

// Ԥ�� plugin_test_1 ����ʵ��

plugin_test_1::plugin_test_1()
	: basicx::Plugins_X( "plugin_test_1" )
	, m_strate_test_1_p( nullptr ) {
	try {
		m_strate_test_1_p = new plugin_test_1_P();
	}
	catch( ... ) {}
}

plugin_test_1::~plugin_test_1() {
	if( m_strate_test_1_p != nullptr ) {
		delete m_strate_test_1_p;
		m_strate_test_1_p = nullptr;
	}
}

bool plugin_test_1::Initialize() {
	return m_strate_test_1_p->Initialize();
}

bool plugin_test_1::InitializeExt() {
	return m_strate_test_1_p->InitializeExt( this );
}

bool plugin_test_1::StartPlugin() {
	return m_strate_test_1_p->StartPlugin( this );
}

bool plugin_test_1::IsPluginRun() {
	return m_strate_test_1_p->IsPluginRun( this );
}

bool plugin_test_1::StopPlugin() {
	return m_strate_test_1_p->StopPlugin( this );
}

bool plugin_test_1::UninitializeExt() {
	return m_strate_test_1_p->UninitializeExt( this );
}

bool plugin_test_1::Uninitialize() {
	return m_strate_test_1_p->Uninitialize();
}

bool plugin_test_1::AssignTask( int32_t task_id, int32_t identity, int32_t code, std::string& data ) {
	return m_strate_test_1_p->AssignTask( task_id, identity, code, data );
}

// �Զ��� plugin_test_1 ����ʵ��