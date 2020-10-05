#pragma once
template<typename T>
class cDetour
{
public:
	explicit cDetour<T>(T target, T detour) : m_target(target), m_detour(detour)
	{
		MH_CreateHook(m_target, m_detour, reinterpret_cast<void**>(&m_trampoline));
	}
	~cDetour()
	{
		MH_DisableHook(m_target);
	}
	T GetTrampoline() const
	{
		return static_cast<T>(m_trampoline);
	}
	bool IsApplied() const
	{
		return m_isEnabled;
	}
	void Apply()
	{
		if (!m_isEnabled)
		{
			m_isEnabled = MH_EnableHook(m_target) == MH_OK;
			if (m_isEnabled)
				memcpy(m_hookBuffer, m_target, sizeof(m_hookBuffer));
		}
	}
	void Remove()
	{
		m_isEnabled = !(m_isEnabled && MH_DisableHook(m_target) == MH_OK);
	}
	void EnsureApply()
	{
		if (memcmp(m_hookBuffer, m_target, sizeof(m_hookBuffer)) != 0)
		{
			DWORD oldProtect;
			VirtualProtect(m_target, sizeof(m_hookBuffer), PAGE_READWRITE, &oldProtect);
			memcpy(m_target, m_hookBuffer, sizeof(m_hookBuffer));
			VirtualProtect(m_target, sizeof(T), oldProtect, &oldProtect);
		}
	}
private:
	T m_trampoline;
	T m_target;
	T m_detour;
	bool m_isEnabled = false;
	char m_hookBuffer[20];

};





