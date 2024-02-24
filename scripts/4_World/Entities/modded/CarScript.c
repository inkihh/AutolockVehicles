modded class CarScript
{
    ref AutolockVehicles_App m_AutolockVehicles_App;

    bool m_AutolockVehicles_WasProximityLocked;
    PlayerBase m_AutolockVehicles_LastPlayerUnlocked;

    override void DeferredInit()
    {
        super.DeferredInit();
        
        if(!GetGame().IsServer()) return;

        if(!m_AutolockVehicles_App) m_AutolockVehicles_App = AutolockVehicles_App.GetInstance();
        m_AutolockVehicles_App.StartAutolockTimer(this, AutolockVehicles_TimerMode.STARTUP);
    }
    
    override void OnEngineStart()
	{
		super.OnEngineStart();

        if(!GetGame().IsServer()) return;

        if(!m_AutolockVehicles_App) m_AutolockVehicles_App = AutolockVehicles_App.GetInstance();
		m_AutolockVehicles_App.RemoveAutolockTimer(this, "OnEngineStart");
	}

    override void EEKilled(Object killer)
	{
        if(!GetGame().IsServer()) return;

        if(!m_AutolockVehicles_App) m_AutolockVehicles_App = AutolockVehicles_App.GetInstance();
		m_AutolockVehicles_App.RemoveAutolockTimer(this, "EEKilled");

		super.EEKilled(killer);
	}

	override void EEDelete(EntityAI parent)
	{
        if(!GetGame().IsServer()) return;

        if(!m_AutolockVehicles_App) m_AutolockVehicles_App = AutolockVehicles_App.GetInstance();
        m_AutolockVehicles_App.RemoveAutolockTimer(this, "EEDelete");

		super.EEDelete(parent);
	}
}
