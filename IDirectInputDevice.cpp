#include "IDirectInputDevice.h"

wchar_t *settingsFilenameA = TEXT(".\\FFBPlugin.ini");
static int configGameId = GetPrivateProfileInt(TEXT("Settings"), TEXT("GameId"), 1, settingsFilenameA);

DirectInputDeviceWrapper::DirectInputDeviceWrapper(LPVOID device, bool unicode)
{
	useUnicode = unicode;
	if (unicode)
	{
		pDeviceW = (LPDIRECTINPUTDEVICE8W)device;
		pDeviceA = NULL;
	}
	else
	{
		pDeviceA = (LPDIRECTINPUTDEVICE8A)device;
		pDeviceW = NULL;
	}
}

DirectInputDeviceWrapper::~DirectInputDeviceWrapper(void)
{
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::QueryInterface(REFIID riid, LPVOID* ppvObj)
{
	if (pDeviceA)	return pDeviceA->QueryInterface(riid, ppvObj);
	return pDeviceW->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE DirectInputDeviceWrapper::AddRef(void)
{
	if (pDeviceA)	return pDeviceA->AddRef();
	return pDeviceW->AddRef();
}

ULONG STDMETHODCALLTYPE DirectInputDeviceWrapper::Release(void)
{
	if (pDeviceA)	return pDeviceA->Release();
	return pDeviceW->Release();
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::Acquire(void)
{
	if (pDeviceA)	return pDeviceA->Acquire();
	return pDeviceW->Acquire();
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::CreateEffect(REFGUID rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter)
{
	if (pDeviceA)	return pDeviceA->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
	return pDeviceW->CreateEffect(rguid, lpeff, ppdeff, punkOuter);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
{
	if (pDeviceA)	return pDeviceA->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
	return pDeviceW->EnumCreatedEffectObjects(lpCallback, pvRef, fl);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::EnumEffects(LPDIENUMEFFECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwEffType)
{
	if (pDeviceA)	return pDeviceA->EnumEffects((LPDIENUMEFFECTSCALLBACKA)lpCallback, pvRef, dwEffType);
	return pDeviceW->EnumEffects(lpCallback, pvRef, dwEffType);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::EnumEffectsInFile(LPCTSTR lptszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
{
	if (pDeviceA)	return pDeviceA->EnumEffectsInFile((LPCSTR)lptszFileName, pec, pvRef, dwFlags);
	return pDeviceW->EnumEffectsInFile(lptszFileName, pec, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	if (pDeviceA)	return pDeviceA->EnumObjects((LPDIENUMDEVICEOBJECTSCALLBACKA)lpCallback, pvRef, dwFlags);
	return pDeviceW->EnumObjects(lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::Escape(LPDIEFFESCAPE pesc)
{
	if (pDeviceA)	return pDeviceA->Escape(pesc);
	return pDeviceW->Escape(pesc);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetCapabilities(LPDIDEVCAPS lpDIDevCaps)
{
	if (configGameId == 29)
	{
		if (pDeviceA)	return pDeviceA->GetCapabilities(NULL);
		return pDeviceW->GetCapabilities(lpDIDevCaps);
	}
	else
	{
		if (pDeviceA)	return pDeviceA->GetCapabilities(lpDIDevCaps);
		return pDeviceW->GetCapabilities(lpDIDevCaps);
	}	
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
{
	if (pDeviceA)	return pDeviceA->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
	return pDeviceW->GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetDeviceInfo(LPDIDEVICEINSTANCE pdidi)
{
	if (pDeviceA)	return pDeviceA->GetDeviceInfo((LPDIDEVICEINSTANCEA)pdidi);
	return pDeviceW->GetDeviceInfo(pdidi);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetDeviceState(DWORD cbData, LPVOID lpvData)
{
	if (pDeviceA)	return pDeviceA->GetDeviceState(cbData, lpvData);
	return pDeviceW->GetDeviceState(cbData, lpvData);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetEffectInfo(LPDIEFFECTINFO pdei, REFGUID rguid)
{
	if (pDeviceA)	return pDeviceA->GetEffectInfo((LPDIEFFECTINFOA)pdei, rguid);
	return pDeviceW->GetEffectInfo(pdei, rguid);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetForceFeedbackState(LPDWORD pdwOut)
{
	if (pDeviceA)	return pDeviceA->GetForceFeedbackState(pdwOut);
	return pDeviceW->GetForceFeedbackState(pdwOut);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetObjectInfo(LPDIDEVICEOBJECTINSTANCE pdidoi, DWORD dwObj, DWORD dwHow)
{
	if (pDeviceA)	return pDeviceA->GetObjectInfo((LPDIDEVICEOBJECTINSTANCEA)pdidoi, dwObj, dwHow);
	return pDeviceW->GetObjectInfo(pdidoi, dwObj, dwHow);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetProperty(REFGUID rguidProp, LPDIPROPHEADER pdiph)
{
	if (pDeviceA)	return pDeviceA->GetProperty(rguidProp, pdiph);
	return pDeviceW->GetProperty(rguidProp, pdiph);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::Initialize(HINSTANCE hinst, DWORD dwVersion, REFGUID rguid)
{
	if (pDeviceA)	return pDeviceA->Initialize(hinst, dwVersion, rguid);
	return pDeviceW->Initialize(hinst, dwVersion, rguid);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::Poll(void)
{
	if (pDeviceA)	return pDeviceA->Poll();
	return pDeviceW->Poll();
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	if (pDeviceA)	return pDeviceA->RunControlPanel(hwndOwner, dwFlags);
	return pDeviceW->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl)
{
	if (pDeviceA)	return pDeviceA->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
	return pDeviceW->SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::SendForceFeedbackCommand(DWORD dwFlags)
{
	if (pDeviceA)	return pDeviceA->SendForceFeedbackCommand(dwFlags);
	return pDeviceW->SendForceFeedbackCommand(dwFlags);
}

bool hackFix = false;

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
{
	if (hackFix)
	{
		if (dwFlags & DISCL_EXCLUSIVE)
		{
			dwFlags &= ~DISCL_EXCLUSIVE;
			dwFlags |= DISCL_NONEXCLUSIVE;
		}
	}
	if (pDeviceA)	return pDeviceA->SetCooperativeLevel(hwnd, dwFlags);
	return pDeviceW->SetCooperativeLevel(hwnd, dwFlags);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::SetDataFormat(LPCDIDATAFORMAT lpdf)
{
	if (pDeviceA)	return pDeviceA->SetDataFormat(lpdf);
	return pDeviceW->SetDataFormat(lpdf);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::SetEventNotification(HANDLE hEvent)
{
	if (pDeviceA)	return pDeviceA->SetEventNotification(hEvent);
	return pDeviceW->SetEventNotification(hEvent);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::SetProperty(REFGUID rguidProp, LPCDIPROPHEADER pdiph)
{
	if (pDeviceA)	return pDeviceA->SetProperty(rguidProp, pdiph);
	return pDeviceW->SetProperty(rguidProp, pdiph);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::Unacquire(void)
{
	if (pDeviceA)	return pDeviceA->Unacquire();
	return pDeviceW->Unacquire();
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::WriteEffectToFile(LPCTSTR lptszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
{
	if (pDeviceA)	return pDeviceA->WriteEffectToFile((LPCSTR)lptszFileName, dwEntries, rgDiFileEft, dwFlags);
	return pDeviceW->WriteEffectToFile(lptszFileName, dwEntries, rgDiFileEft, dwFlags);
}

#if DIRECTINPUT_VERSION >= 0x0800

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::BuildActionMap(LPDIACTIONFORMAT lpdiaf, LPCTSTR lpszUserName, DWORD dwFlags)
{
	if (pDeviceA)	return pDeviceA->BuildActionMap((LPDIACTIONFORMATA)lpdiaf, (LPCSTR)lpszUserName, dwFlags);
	return pDeviceW->BuildActionMap(lpdiaf, lpszUserName, dwFlags);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::GetImageInfo(LPDIDEVICEIMAGEINFOHEADER lpdiDevImageInfoHeader)
{
	if (pDeviceA)	return pDeviceA->GetImageInfo((LPDIDEVICEIMAGEINFOHEADERA)lpdiDevImageInfoHeader);
	return pDeviceW->GetImageInfo(lpdiDevImageInfoHeader);
}

HRESULT STDMETHODCALLTYPE DirectInputDeviceWrapper::SetActionMap(LPDIACTIONFORMAT lpdiActionFormat, LPCTSTR lptszUserName, DWORD dwFlags)
{
	if (pDeviceA)	return pDeviceA->SetActionMap((LPDIACTIONFORMATA)lpdiActionFormat, (LPCSTR)lptszUserName, dwFlags);
	return pDeviceW->SetActionMap(lpdiActionFormat, lptszUserName, dwFlags);
}
#endif
