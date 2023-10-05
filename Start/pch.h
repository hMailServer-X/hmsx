#pragma once

/* If we are running on Windows 32/64-Bits and Visual C/C++, include the following inlcude headers */

#ifdef _WIN32 
	#ifdef _MSC_VER 
		#include "WinSock2.h"
		#include "Windows.h"
		#include <iphlpapi.h>
		#include <windns.h>
		#include "applink.c"
	#endif	
#endif

//
// This is used as replacement for _L() and _TEXT() to be more platform neutral
//

#ifdef _WIN32
	#define PLATFORM_STRING(s) L##s // Windows uses UTF-16
#else
	#define PLATFORM_STRING(s) u8##s // Other Plattforms using UTF-8
#endif

//
// C99 and C++ 2014 Standard compliant STL Include headers
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <vector>
#include <set> 
#include <list> 
#include <queue>
#include <functional>
#include <deque>


//
// C-ARES Includes (DNS-Resolver Library)
//

#include "ares.h"


//
// BOOST INCLUDES
//

#include <boost/winapi/config.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/signals2/signal.hpp>

//
// hMailServer specific include headers
//

   #include "../Common/Util/StdString.h"
   #include "../Common/Util/XMLite.h"
   #include "../Common/Util/Singleton.h"
   #include "../Common/Application/Constants.h"
   #include "../Common/Application/PropertySet.h"
   #include "../Common/Application/Configuration.h"
   #include "../Common/Application/IniFileSettings.h"
   #include "../Common/Application/Application.h"
   #include "../Common/Application/Logger.h"
   #include "../Common/Application/ErrorManager.h"
   #include "../Common/SQL/SQLParameter.h"
   #include "../Common/SQL/SQLStatement.h"
   #include "../Common/SQL/DatabaseConnectionManager.h"
   #include "../Common/SQL/DALRecordset.h"
   #include "../Common/SQL/DALRecordsetFactory.h"
   #include "../Common/SQL/SQLCommand.h"
   #include "../Common/Util/Parsing/StringParser.h"
   #include "../Common/Util/FileUtilities.h"
   #include "../Common/BO/BusinessObject.h"
   #include "../Common/BO/init_account.h"
   #include "../IMAP/IMAPResult.h"
   #include "../Common/TCPIP/IPAddress.h"
   #include "../Common/Util/Strings/FormatArgument.h"
   #include "../Common/Util/Strings/Formatter.h"

//
// End of hMailServer specific include headers
//