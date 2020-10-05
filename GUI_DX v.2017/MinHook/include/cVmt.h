#pragma once
template<typename T>
class cVmt
{
private:
	void** m_ppVtable;
	size_t m_index;
	T m_original;
	T m_detour;

public:
	explicit cVmt<T>(void** ppVtable, size_t index, T detour)
		: m_ppVtable(ppVtable), m_index(index), m_detour(detour)
	{
		m_original = (T)ppVtable[index];
	}
	~cVmt()
	{
		Remove();
	}
	T GetTrampoline() const { return m_original; }
	bool IsApplied() const { return m_ppVtable[m_index] == m_detour; }
	void Apply()
	{
		DWORD oldProtect;
		VirtualProtect(&m_ppVtable[m_index], sizeof(T), PAGE_READWRITE, &oldProtect);
		m_ppVtable[m_index] = m_detour;
		VirtualProtect(&m_ppVtable[m_index], sizeof(T), oldProtect, &oldProtect);
	}
	void Remove()
	{
		DWORD oldProtect;
		VirtualProtect(&m_ppVtable[m_index], sizeof(T), PAGE_READWRITE, &oldProtect);
		m_ppVtable[m_index] = m_original;
		VirtualProtect(&m_ppVtable[m_index], sizeof(T), oldProtect, &oldProtect);
	}
	void** GetVtable() const { return m_ppVtable; }
	void SetVtable(void** ppVtable) { m_ppVtable = ppVtable; m_original = (T)m_ppVtable[m_index]; }
	void SetVtableAndApply(void** ppVtable) { SetVtable(ppVtable); Apply(); }
};