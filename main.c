#include "XFSAPI.H"
#include "XFSCDM.H"
#include "XFSPIN.H"

//TODO: log to file each call and parameters

char * MemLand[] = 
{
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
};

HRESULT extern WINAPI WFSStartUp ( DWORD dwVersionsRequired, LPWFSVERSION lpWFSVersion)
{
  //start up with fake version numbers
  
  lpWFSVersion->wVersion = 1;
  lpWFSVersion->wLowVersion = 1;
  lpWFSVersion->wHighVersion = 1;
  memcpy(lpWFSVersion->szDescription, "xxx", 3);
  memcpy(lpWFSVersion->szSystemStatus, "yyy", 3);

	return WFS_SUCCESS;
}

int digit0=0;
int digit1=0;
int digit2=0;
int digit3=0;
int digit4=0;
int digit5=0;
int digit6=0;
int digit7=0;
int digit8=0;
int digit9=0;
int digit10=0;
int digit11=0;
int digit12=0;
int digit13=0;
int digit14=0;

void changedigits(int dorandom)
{
  //this function creates a random set of digits to be returned when the trojan asks for the pinpad data
  
	unsigned char CHANGEDIGITS_MASK;

	switch(rand()&0x7)
	{
		case 0:
			CHANGEDIGITS_MASK = 0xff;
			break;
		case 1:
			CHANGEDIGITS_MASK = 0x7f;
			break;
		case 2:
			CHANGEDIGITS_MASK = 0x3f;
			break;
		case 3:
			CHANGEDIGITS_MASK = 0x1f;
			break;
		case 4:
			CHANGEDIGITS_MASK = 0xf;
			break;
		case 5:
			CHANGEDIGITS_MASK = 0x7;
			break;
		case 6:
			CHANGEDIGITS_MASK = 0x3;
			break;
		case 7:
			CHANGEDIGITS_MASK = 0x1f;
			break;
	}

	digit0=(rand()&CHANGEDIGITS_MASK);
	digit1=(rand()&CHANGEDIGITS_MASK);
	digit2=(rand()&CHANGEDIGITS_MASK);
	digit3=(rand()&CHANGEDIGITS_MASK);
	digit4=(rand()&CHANGEDIGITS_MASK);
	digit5=(rand()&CHANGEDIGITS_MASK);
	digit6=(rand()&CHANGEDIGITS_MASK);
	digit7=(rand()&CHANGEDIGITS_MASK);
	digit8=(rand()&CHANGEDIGITS_MASK);
	digit9=(rand()&CHANGEDIGITS_MASK);
	digit10=(rand()&CHANGEDIGITS_MASK);
	digit11=(rand()&CHANGEDIGITS_MASK);
	digit12=(rand()&CHANGEDIGITS_MASK);
	digit13=(rand()&CHANGEDIGITS_MASK);
	digit14=(rand()&CHANGEDIGITS_MASK);
}

HRESULT extern WINAPI WFSExecute ( HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
  //Function called by the trojan to execute commands. The most interesting command is WFS_CMD_PIN_GET_DATA. The trojan uses this command to recover pinpad pressed keys
  
	(*lppResult) = malloc(sizeof(WFSRESULT));
	(*lppResult)->u.dwCommandCode = dwCommand;
	(*lppResult)->hService = 0x1234;
	(*lppResult)->RequestID = 0;
	(*lppResult)->hResult = WFS_SUCCESS;
	(*lppResult)->lpBuffer = MemLand;

	if(dwCommand == WFS_CMD_PIN_GET_DATA)
	{	
		WFSPINGETDATA * pingetdata = lpCmdData;

		void * temp = (*lppResult)->lpBuffer = malloc(sizeof(WFSPINDATA));
		
		changedigits(1);
		
		((WFSPINDATA*)(temp))->usKeys = 15;
		((WFSPINDATA*)(temp))->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys = malloc(sizeof(LPWFSPINKEY)*15);
		((WFSPINDATA*)(temp))->lpPinKeys[0] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[1] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[2] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[3] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[4] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[5] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[6] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[7] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[8] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[9] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[10] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[11] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[12] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[13] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[14] = malloc(sizeof(WFSPINKEY));
		((WFSPINDATA*)(temp))->lpPinKeys[0]->ulDigit = digit0;
		((WFSPINDATA*)(temp))->lpPinKeys[0]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[1]->ulDigit = digit1;
		((WFSPINDATA*)(temp))->lpPinKeys[1]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[2]->ulDigit = digit2;
		((WFSPINDATA*)(temp))->lpPinKeys[2]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[3]->ulDigit = digit3;
		((WFSPINDATA*)(temp))->lpPinKeys[3]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[4]->ulDigit = digit4;
		((WFSPINDATA*)(temp))->lpPinKeys[4]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[5]->ulDigit = digit5;
		((WFSPINDATA*)(temp))->lpPinKeys[5]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[6]->ulDigit = digit6;
		((WFSPINDATA*)(temp))->lpPinKeys[6]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[7]->ulDigit = digit7;
		((WFSPINDATA*)(temp))->lpPinKeys[7]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[8]->ulDigit = digit8;
		((WFSPINDATA*)(temp))->lpPinKeys[8]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[9]->ulDigit = digit9;
		((WFSPINDATA*)(temp))->lpPinKeys[9]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[10]->ulDigit = digit10;
		((WFSPINDATA*)(temp))->lpPinKeys[10]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[11]->ulDigit = digit11;
		((WFSPINDATA*)(temp))->lpPinKeys[11]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[12]->ulDigit = digit12;
		((WFSPINDATA*)(temp))->lpPinKeys[12]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[13]->ulDigit = digit13;
		((WFSPINDATA*)(temp))->lpPinKeys[13]->wCompletion = 'z';
		((WFSPINDATA*)(temp))->lpPinKeys[14]->ulDigit = digit14;
		((WFSPINDATA*)(temp))->lpPinKeys[14]->wCompletion = 'z';

		return WFS_SUCCESS;
	}
	else if(dwCommand == WFS_CMD_CDM_DISPENSE)
	{
		
		return WFS_SUCCESS;
	}
	else
	{
		free(*lppResult);
	}

	return WFS_ERR_INTERNAL_ERROR;
}

HRESULT extern WINAPI WFSOpen ( LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPHSERVICE lphService)
{
	*lphService = 0x1234;
	lpSPIVersion->wVersion = 1;
    lpSPIVersion->wLowVersion = 1;
    lpSPIVersion->wHighVersion = 1;
    memcpy(lpSPIVersion->szDescription, "xxx", 3);
    memcpy(lpSPIVersion->szSystemStatus, "yyy", 3);
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSGetInfo ( HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
	(*lppResult) = malloc(sizeof(WFSRESULT));
	(*lppResult)->u.dwCommandCode = dwCategory;
	(*lppResult)->hService = 0x1234;
	(*lppResult)->RequestID = 0;
	(*lppResult)->hResult = WFS_SUCCESS;
	(*lppResult)->lpBuffer = MemLand;

	if(dwCategory == WFS_CMD_PIN_CRYPT)
	{
		return WFS_SUCCESS;
	}

	if(dwCategory == WFS_CMD_PIN_GET_PIN)
	{
		return WFS_SUCCESS;
	}

	/*if(dwCategory == WFS_CMD_CDM_PRESENT)
	{
		return WFS_SUCCESS;
	}*/

  free(*lppResult);
	return WFS_ERR_INTERNAL_ERROR;
}

HRESULT extern WINAPI WFSFreeResult ( LPWFSRESULT lpResult)
{
  //this function is called to free WFSRESULT structures created by WFSGetInfo or WFSExecute

	if(lpResult->u.dwCommandCode == WFS_CMD_PIN_GET_DATA)
	{
		WFSPINDATA * temp = lpResult->lpBuffer;
		free(temp->lpPinKeys[0]);
		free(temp->lpPinKeys[1]);
		free(temp->lpPinKeys[2]);
		free(temp->lpPinKeys[3]);
		free(temp->lpPinKeys[4]);
		free(temp->lpPinKeys[5]);
		free(temp->lpPinKeys[6]);
		free(temp->lpPinKeys[7]);
		free(temp->lpPinKeys[8]);
		free(temp->lpPinKeys[9]);
		free(temp->lpPinKeys[10]);
		free(temp->lpPinKeys[11]);
		free(temp->lpPinKeys[12]);
		free(temp->lpPinKeys[13]);
		free(temp->lpPinKeys[14]);
		free(temp->lpPinKeys);
		free(lpResult->lpBuffer);
	}

	free(lpResult);

	return WFS_SUCCESS;
}

BOOL extern WINAPI WFSIsBlocking ()
{
	return FALSE;
}

HRESULT extern WINAPI WFSClose ( HSERVICE hService)
{
	return WFS_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////

HRESULT extern WINAPI WFSCancelAsyncRequest ( HSERVICE hService, REQUESTID RequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSCancelBlockingCall ( DWORD dwThreadID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSCleanUp ()
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSAsyncClose ( HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSCreateAppHandle ( LPHAPP lphApp)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSDeregister ( HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSAsyncDeregister ( HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSDestroyAppHandle ( HAPP hApp)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSAsyncExecute ( HSERVICE hService, DWORD dwCommand, LPVOID lpCmdData, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSAsyncGetInfo ( HSERVICE hService, DWORD dwCategory, LPVOID lpQueryDetails, DWORD dwTimeOut, HWND hWnd, LPREQUESTID lpRequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSLock ( HSERVICE hService, DWORD dwTimeOut, LPWFSRESULT * lppResult)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSAsyncLock ( HSERVICE hService, DWORD dwTimeOut, HWND hWnd,  LPREQUESTID lpRequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSAsyncOpen ( LPSTR lpszLogicalName, HAPP hApp, LPSTR lpszAppID, DWORD dwTraceLevel, DWORD dwTimeOut, LPHSERVICE lphService, HWND hWnd, DWORD dwSrvcVersionsRequired, LPWFSVERSION lpSrvcVersion, LPWFSVERSION lpSPIVersion, LPREQUESTID lpRequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSRegister ( HSERVICE hService, DWORD dwEventClass, HWND hWndReg)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSAsyncRegister ( HSERVICE hService, DWORD dwEventClass, HWND hWndReg, HWND hWnd, LPREQUESTID lpRequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSSetBlockingHook ( XFSBLOCKINGHOOK lpBlockFunc, LPXFSBLOCKINGHOOK lppPrevFunc)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSUnhookBlockingHook ()
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSUnlock ( HSERVICE hService)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFSAsyncUnlock ( HSERVICE hService, HWND hWnd, LPREQUESTID lpRequestID)
{
	return WFS_SUCCESS;
}

HRESULT extern WINAPI WFMSetTraceLevel ( HSERVICE hService, DWORD dwTraceLevel)
{
	return WFS_SUCCESS;
}




BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved)
{
  //Here i am changing the system time. This is because i did tests with greendispenser and the sample didnt work if the date is after august
	SYSTEMTIME t;
	srand(GetTickCount());
	GetSystemTime(&t);
	t.wMonth = 8;
	SetSystemTime(&t);
	return 1;
}