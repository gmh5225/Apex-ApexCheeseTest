#pragma once

class Driver
{
	std::mutex accessMutex;

public:
	UINT ProcessId;
	/*
	This is not thread safe! 
	So dont call the driver from a thread!
	*/
	const bool Init(const BOOL PhysicalMode) {
		this->bPhysicalMode = PhysicalMode;
		this->hDriver = CreateFileA(("\\\\.\\\PEAuth"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (this->hDriver != INVALID_HANDLE_VALUE) {
			if (this->SharedBuffer = VirtualAlloc(0, sizeof(REQUEST_DATA), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)) {
				UNICODE_STRING RegPath = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\ucflash");
				RegistryUtils::WriteRegistry(RegPath, RTL_CONSTANT_STRING(L"xxx"), &this->SharedBuffer, REG_QWORD, 8);
				PVOID pid = (PVOID)GetCurrentProcessId();
				RegistryUtils::WriteRegistry(RegPath, RTL_CONSTANT_STRING(L"xx"), &pid, REG_QWORD, 8);
				auto OLD_MAGGICCODE = this->MAGGICCODE;
				SendRequest(99, 0);
				if(this->MAGGICCODE == OLD_MAGGICCODE)
					this->MAGGICCODE = (ULONG64)RegistryUtils::ReadRegistry<LONG64>(RegPath, RTL_CONSTANT_STRING(L"xxxx"));
				return true;
			}
		}
		return false;
	}

	const NTSTATUS SendRequest(const UINT type, const PVOID args) {
		try {
			REQUEST_DATA req;
			NTSTATUS status;
			req.MaggicCode = &this->MAGGICCODE;
			req.Type = type;
			req.Arguments = args;
			req.Status = &status;
			memcpy(this->SharedBuffer, &req, sizeof(REQUEST_DATA));
			FlushFileBuffers(this->hDriver);
			return status;
		}
		catch (const std::exception& e) {
			return STATUS_SUCCESS;
		}		
	}

	const UINT GetProcessId(const wchar_t* process_name) {
		UINT pid = 0;
		// Create toolhelp snapshot.
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		PROCESSENTRY32 process;
		ZeroMemory(&process, sizeof(process));
		process.dwSize = sizeof(process);
		// Walkthrough all processes.
		if (Process32First(snapshot, &process))
		{
			do
			{
				if (wcsstr(process.szExeFile, process_name))
				{
					pid = process.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &process));
		}
		CloseHandle(snapshot);
		return pid;
	}

	const bool Attach(const wchar_t* Processname, const wchar_t* Classname = 0) {
		if (Classname) {
			while (!FindWindowW(Classname, 0)){ Sleep(50); }
		}
		if (this->ProcessId = this->GetProcessId(Processname))
			return true;
		return false;
	}
	//If PhysicalMode is Aktive ModuleName is not used because it only gets Gamebase! 
	typedef struct Module { uint64_t addr; DWORD size; };
	const Module GetModuleBase(const wchar_t* ModuleName = 0) {
		std::lock_guard<std::mutex> lock(accessMutex);

		if (bPhysicalMode) {
			REQUEST_MAINBASE req;
			uint64_t base = NULL;
			req.ProcessId = this->ProcessId;
			req.OutAddress = (PBYTE*)&base;
			this->SendRequest(REQUEST_TYPE::MAINBASE, &req);
			return { base, 0 };
		}
		else {
			if (!ModuleName)
				return { 0, 0 };
			REQUEST_MODULE req;
			uint64_t base = NULL;
			DWORD size = NULL;
			req.ProcessId = this->ProcessId;
			req.OutAddress = (PBYTE*)&base;
			req.OutSize = &size;
			wcscpy_s(req.Module, sizeof(req.Module) / sizeof(req.Module[0]), ModuleName);
			this->SendRequest(REQUEST_TYPE::MODULE, &req);
			return { base, size };
		}
	}

	template <typename Type>
	const Type SetAdress(PVOID source, Type tBuffer) {
		std::lock_guard<std::mutex> lock(accessMutex);

		REQUEST_WRITE req;
		
		req.bPhysicalMem = FALSE;
		req.Dest = source;
		req.Src = &tBuffer;
		req.Size = sizeof(Type);
		req.ProcessId = this->ProcessId;
		
		this->SendRequest(REQUEST_TYPE::WRITE, &req);
		return tBuffer;
	}

	template<class type>
	const type GetAddress(PVOID source) {
		std::lock_guard<std::mutex> lock(accessMutex);

		REQUEST_READ req;

		type address{};

		req.ProcessId = this->ProcessId;
		req.Src = source;
		req.Size = sizeof(type);
		req.bPhysicalMem = FALSE;
		req.Dest = &address;
		this->SendRequest(REQUEST_TYPE::READ, &req);

		return (type)address;
	}

	template<class type>
	const type GetAddress(PVOID source, type& result) {
		std::lock_guard<std::mutex> lock(accessMutex);

		REQUEST_READ req;

		req.ProcessId = this->ProcessId;
		req.Src = source;
		req.Size = sizeof(type);
		req.bPhysicalMem = FALSE;
		req.Dest = (uint8_t*)&result;

		this->SendRequest(REQUEST_TYPE::READ, &req);

		return (type)result;
	}

	const BYTE* GetString(PVOID Source, PVOID Target, const wchar_t* ModuleName = 0) {
		std::lock_guard<std::mutex> lock(accessMutex);

		REQUEST_GETSTRING req;

		unsigned char myString[60];

		req.ProcessId = GetProcessId(ModuleName);
		req.Src = Source;
		req.Dest = Target;
		req.bPhysicalMem = FALSE;
		req.OutDest = (BYTE*)&myString;
		this->SendRequest(REQUEST_TYPE::GETSTRING, &req);

		return myString;
	}

	const FLOAT* GetMatrix(PVOID Source, const wchar_t* ModuleName = 0) {
		std::lock_guard<std::mutex> lock(accessMutex);

		REQUEST_GETMATRIX req;
		
		float myResult[16];

		req.ProcessId = GetProcessId(ModuleName);
		req.Src = Source;
		req.Dest = &myResult;
		req.bPhysicalMem = FALSE;

		this->SendRequest(REQUEST_TYPE::GETMATRIX, &req);

		return myResult;
	}


private:
	PVOID SharedBuffer;
	HANDLE hDriver;
	ULONG64 MAGGICCODE = 0x59002360218c1e2dul;
	BOOL bPhysicalMode = FALSE;
	typedef enum _REQUEST_TYPE : UINT {
		WRITE,
		READ,
		PROTECT,
		ALLOC,
		FREE,
		MODULE,
		MAINBASE,
		GETSTRING,
		GETMATRIX,
		THREADCALL,
	} REQUEST_TYPE;

	typedef struct _REQUEST_DATA {
		ULONG64* MaggicCode;
		UINT Type;
		PVOID Arguments;
		NTSTATUS* Status;
	} REQUEST_DATA, * PREQUEST_DATA;

	typedef struct _REQUEST_WRITE {
		DWORD ProcessId;
		PVOID Dest;
		PVOID Src;
		DWORD Size;
		BOOL bPhysicalMem;
	} REQUEST_WRITE, * PREQUEST_WRITE;

	typedef struct _REQUEST_READ {
		DWORD ProcessId;
		PVOID Dest;
		PVOID Src;
		DWORD Size;
		BOOL bPhysicalMem;
	} REQUEST_READ, * PREQUEST_READ;

	typedef struct _REQUEST_PROTECT {
		DWORD ProcessId;
		PVOID Address;
		DWORD Size;
		PDWORD InOutProtect;
	} REQUEST_PROTECT, * PREQUEST_PROTECT;

	typedef struct _REQUEST_ALLOC {
		DWORD ProcessId;
		PVOID OutAddress;
		DWORD Size;
		DWORD Protect;
	} REQUEST_ALLOC, * PREQUEST_ALLOC;

	typedef struct _REQUEST_FREE {
		DWORD ProcessId;
		PVOID Address;
	} REQUEST_FREE, * PREQUEST_FREE;

	typedef struct _REQUEST_MODULE {
		DWORD ProcessId;
		WCHAR Module[0xFF];
		PBYTE* OutAddress;
		DWORD* OutSize;
	} REQUEST_MODULE, * PREQUEST_MODULE;

	typedef struct _REQUEST_MAINBASE {
		DWORD ProcessId;
		PBYTE* OutAddress;
	} REQUEST_MAINBASE, * PREQUEST_MAINBASE;

	typedef struct _REQUEST_GETSTRING {
		DWORD ProcessId;
		PVOID Dest;
		PVOID Src;
		DWORD Size;
		BOOL bPhysicalMem;
		BYTE* OutDest;
	} REQUEST_GETSTRING, * PREQUEST_GETSTRING;

	typedef struct _REQUEST_GETMATRIX {
		DWORD ProcessId;
		PVOID Dest;
		PVOID Src;
		DWORD Size;
		BOOL bPhysicalMem;
		FLOAT* OutDest;
	} REQUEST_GETMATRIX, * PREQUEST_GETMATRIX;
};

static Driver* driver = new Driver;