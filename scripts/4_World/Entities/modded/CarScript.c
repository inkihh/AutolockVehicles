modded class CarScript
{
    ref FOGAutolockVehicles_App m_App;
    bool m_AutolockDone = false;

    override void DelayedInit()
    {
        super.DelayedInit();

        if (!GetGame().IsServer())
			return;
			
		if(!m_AutolockDone)
		{
            m_App = FOGAutolockVehicles_App.GetInstance();
            m_App.m_Logger.DebugLog("Starting Autolock timer");
            StartAutolockTimer();
		}

    }

    void StartAutolockTimer()
    {
        int AutolockDelay = m_App.m_Settings.GetAutolockDelay() * 60 * 1000;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DoAutolock, AutolockDelay, false);
    }

    void DoAutolock()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.DoAutolock);
        m_App.m_Logger.DebugLog("Starting DoAutolock");

        if(IsAnyCrewPresent())
        {
            m_App.m_Logger.DebugLog("Crew present, exiting");
            return;
        }

        m_IsCKLocked = true;

        SynchronizeValues();
    }

    override void OnEngineStart()
	{
		super.OnEngineStart();

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.DoAutolock);
	}

    
    override void EEKilled(Object killer)
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.DoAutolock);
            m_App.m_Logger.DebugLog("Deleting autolock timer (EEKilled)");
		}

		super.EEKilled(killer);
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
        
		if (!GetGame().IsServer()) return;

        m_App.m_Logger.DebugLog("Deleting autolock timer (EEDelete)");
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.DoAutolock);
	}
}
