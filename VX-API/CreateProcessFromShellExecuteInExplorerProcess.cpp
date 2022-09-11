#include "Win32Helper.h"

#include <shlwapi.h>
#include <shlobj.h>

HRESULT UnusedSubroutineGetShellDispatchFromView(IShellView* ShellView, REFIID Riid, PVOID* Dispatch2)
{
	HRESULT Result = S_OK;
	IShellFolderViewDual* ShellFolderDual = NULL;
	IDispatch* Dispatch = NULL;
	IDispatch* BackgroundDispatchObject = NULL;
	*Dispatch2 = NULL;

	Result = ShellView->GetItemObject(SVGIO_BACKGROUND, IID_PPV_ARGS(&BackgroundDispatchObject));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = BackgroundDispatchObject->QueryInterface(IID_PPV_ARGS(&ShellFolderDual));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = ShellFolderDual->get_Application(&Dispatch);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Dispatch->QueryInterface(Riid, Dispatch2);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

EXIT_ROUTINE:

#pragma warning( push )
#pragma warning( disable : 6001)

	if (BackgroundDispatchObject)
		BackgroundDispatchObject->Release();

	if (ShellFolderDual)
		ShellFolderDual->Release();

	if (Dispatch)
		Dispatch->Release();
#pragma warning( pop ) 

	return Result;
}

HRESULT UnusedSubroutineGetShellViewForDesktop(REFIID Riid, PVOID* ShellView)
{
	HRESULT Result = S_OK;
	IShellWindows* Windows = NULL;
	HWND hWnd;
	IDispatch* Dispatch = NULL;
	VARIANT Variant = {};
	IShellBrowser* Browser = NULL;
	IShellView* View = NULL;
	*ShellView = NULL;

	Result = CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&Windows));
	if (!SUCCEEDED(Result))
		return Result;

	Result = Windows->FindWindowSW(&Variant, &Variant, SWC_DESKTOP, (PLONG)&hWnd, SWFO_NEEDDISPATCH, &Dispatch);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = IUnknown_QueryService(Dispatch, SID_STopLevelBrowser, IID_PPV_ARGS(&Browser));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Browser->QueryActiveShellView(&View);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = View->QueryInterface(Riid, ShellView);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;


EXIT_ROUTINE:

#pragma warning( push )
#pragma warning( disable : 6001)
	if (Windows)
		Windows->Release();

	if (Browser)
		Browser->Release();

	if (View)
		View->Release();

	if (Dispatch)
		Dispatch->Release();
#pragma warning( pop ) 

	return Result;
}

DWORD CreateProcessFromShellExecuteInExplorerProcessW(_In_ PWCHAR BinaryPath)
{
	HRESULT Result = S_OK;
	IShellView* ShellView = NULL;
	IShellDispatch2* Dispatch2 = NULL;
	BSTR FilePath = NULL;
	VARIANT Dispose = {};

	Result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = UnusedSubroutineGetShellViewForDesktop(IID_PPV_ARGS(&ShellView));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = UnusedSubroutineGetShellDispatchFromView(ShellView, IID_PPV_ARGS(&Dispatch2));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	FilePath = SysAllocString(BinaryPath);
	if (FilePath == NULL)
		goto EXIT_ROUTINE;

	Result = Dispatch2->ShellExecuteW(FilePath, Dispose, Dispose, Dispose, Dispose);

EXIT_ROUTINE:

#pragma warning( push )
#pragma warning( disable : 6001)
	if (ShellView)
		ShellView->Release();

	if (Dispatch2)
		Dispatch2->Release();
#pragma warning( pop ) 

	if (FilePath)
		SysFreeString(FilePath);

	CoUninitialize();

	return Win32FromHResult(Result);
}

DWORD CreateProcessFromShellExecuteInExplorerProcessA(_In_ PCHAR BinaryPath)
{
	HRESULT Result = S_OK;
	IShellView* ShellView = NULL;
	IShellDispatch2* Dispatch2 = NULL;
	BSTR FilePath = NULL;
	VARIANT Dispose = {};
	WCHAR wBinaryPath[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(wBinaryPath, BinaryPath, StringLengthA(BinaryPath)) == 0)
		goto EXIT_ROUTINE;

	Result = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = UnusedSubroutineGetShellViewForDesktop(IID_PPV_ARGS(&ShellView));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = UnusedSubroutineGetShellDispatchFromView(ShellView, IID_PPV_ARGS(&Dispatch2));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	FilePath = SysAllocString(wBinaryPath);
	if (FilePath == NULL)
		goto EXIT_ROUTINE;

	Result = Dispatch2->ShellExecuteW(FilePath, Dispose, Dispose, Dispose, Dispose);

EXIT_ROUTINE:

#pragma warning( push )
#pragma warning( disable : 6001)
	if (ShellView)
		ShellView->Release();

	if (Dispatch2)
		Dispatch2->Release();
#pragma warning( pop ) 

	if (FilePath)
		SysFreeString(FilePath);

	CoUninitialize();

	return Win32FromHResult(Result);
}