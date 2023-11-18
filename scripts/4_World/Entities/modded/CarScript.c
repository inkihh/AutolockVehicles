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

    void DoAutolock(PlayerBase Driver = NULL)
    {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.DoAutolock);
        m_App.m_Logger.DebugLog("Starting DoAutolock");

        int PassengerCount = 0;
        if(Driver) PassengerCount = -1
        for (int index = 0; index < CrewSize(); ++index)
		{
			if (CrewMember(index) != null) PassengerCount++;
		}

        m_App.m_Logger.DebugLog("Passenger count: " + PassengerCount);

        if(PassengerCount > 0)
        {
            m_App.m_Logger.DebugLog("Passengers present, exiting");
            return;
        }

        if(!m_HasCKAssigned)
        {
            m_App.m_Logger.DebugLog("No carkey assigned, exiting");
            return;
        }

        m_App.m_Logger.Log("Locking vehicle (carId:" + m_CarScriptId + "|keyId:" + m_CarKeyId + ")");

        m_IsCKLocked = true;
        SynchronizeValues();
    }

    void RemoveAutolockTimer(string Reason)
    {
        if (!GetGame().IsServer()) return;
		
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.DoAutolock);
        m_App.m_Logger.DebugLog("Remove autolock timer (" + Reason + ")");
    }

    override void OnEngineStart()
	{
		super.OnEngineStart();
		RemoveAutolockTimer("OnEngineStart");
	}

    
    override void EEKilled(Object killer)
	{
		RemoveAutolockTimer("EEKilled");
		super.EEKilled(killer);
	}

	override void EEDelete(EntityAI parent)
	{
        RemoveAutolockTimer("EEDelete");
		super.EEDelete(parent);
	}
}


