#pragma once


struct ScriptImport
{
	LPTSTR names = nullptr;
	ScriptModule *mod = nullptr;
	ScriptImport *next = nullptr;
	LineNumberType line_number = 0;
	FileIndexType file_index = 0;

	ScriptImport() {}
	ScriptImport(ScriptModule *aMod) : mod(aMod), names(_T("*")) {}

	void *operator new(size_t aBytes) {return SimpleHeap::Alloc(aBytes);}
	void *operator new[](size_t aBytes) {return SimpleHeap::Alloc(aBytes);}
	void operator delete(void *aPtr) {}
	void operator delete[](void *aPtr) {}
};


class ScriptModule : public ObjectBase
{
public:
	LPCTSTR mName = nullptr;
	Line *mFirstLine = nullptr;
	ScriptImport *mImports = nullptr;
	ScriptModule *mPrev = nullptr;
	VarList mVars;
	Var *mSelf = nullptr;
	bool mExecuted = false;

	// #Warn settings
	WarnMode Warn_LocalSameAsGlobal = WARNMODE_OFF;
	WarnMode Warn_Unreachable = WARNMODE_MSGBOX;
	WarnMode Warn_VarUnset = WARNMODE_MSGBOX;

	ScriptModule() {}
	ScriptModule(LPCTSTR aName, ScriptImport &aDefaultImport)
	{
		mName = SimpleHeap::Alloc(aName);
		mImports = &aDefaultImport;
	}

	void *operator new(size_t aBytes) {return SimpleHeap::Alloc(aBytes);}
	void *operator new[](size_t aBytes) {return SimpleHeap::Alloc(aBytes);}
	void operator delete(void *aPtr) {}
	void operator delete[](void *aPtr) {}

	IObject_Type_Impl("Module");
	ResultType Invoke(IObject_Invoke_PARAMS_DECL) override;
	Object *Base() override { return sPrototype; }
	static Object *sPrototype;
};

typedef ScriptItemList<ScriptModule, 16> ScriptModuleList;