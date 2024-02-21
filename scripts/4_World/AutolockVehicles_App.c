/*
- On player disconnect
-- Player not in a vehicle? EXIT
-- Player not driver of that vehicle? EXIT
-- Goto StartTimer with settings.AutolockDelay_PlayerDisconnect

- On vehicle spawn (restart, receipt thrown, parked out, ..)
-- Goto StartTimer with settings.AutolockDelay_Startup

- Vehicle deleted or destroyed
-- Stop timer

- Vehicle engine start, vehicle deleted or destroyed
-- Start measuring distance between player and car
-- If distance > ProximityLock_DistanceMeters, goto LockVehicle

- StartTimer
-- Vehicle has no lock? EXIT
-- Vehicle is locked already? EXIT
-- Start the actual timer

- On timer finish
-- Goto LockVehicle

- LockVehicle
-- Vehicle has no lock? EXIT
-- Vehicle is locked already? EXIT
-- LOCK!

*/

class AutolockVehicles_App
{
	protected static ref AutolockVehicles_App s_Instance;
	static const string m_AppName = "AutolockVehicles";

	ref AutolockVehicles_Logger m_Logger;
	ref AutolockVehicles_Settings m_Settings;
	    
	string m_TimerTargetFunctionName = "LockVehicle";

	ref map<string, ref AutolockVehicles_KeyModBase> m_KeyMods;
	ref AutolockVehicles_KeyModBase m_KeyMod;

	ref map<int, ref Timer> m_Timers;

	void AutolockVehicles_App()
	{
		m_Logger = new AutolockVehicles_Logger(m_AppName);
		m_Settings = new AutolockVehicles_Settings(m_AppName);
		
		m_Timers = new map<int, ref Timer>;
		m_KeyMods = new map<string, ref AutolockVehicles_KeyModBase>();

		#ifdef CarLock
		#ifndef CARLOCKDISABLE
			AddKeyMod("TRADERPLUSCARLOCK", new AutolockVehicles_TraderPlusCarLock());
		#endif
		#endif

		#ifdef MuchCarKey
			AddKeyMod("MUCHCARKEY", new AutolockVehicles_MuchCarKey());
		#endif

		#ifdef Trader
			AddKeyMod("TRADER", new AutolockVehicles_Trader());
		#endif

		#ifdef EXPANSIONMODVEHICLE
			AddKeyMod("EXPANSION", new AutolockVehicles_Expansion());
		#endif

		AddKeyMod("CUSTOM", new AutolockVehicles_Custom());

		s_Instance = this;

		if (!m_Settings.IsLoaded())
		{
			Print("[" + m_AppName + "] Settings incomplete. Please check " + m_Logger.m_LogFile);
			Print("[" + m_AppName + "] If it didn't exist at all, an empty one was created right now.");
			return;
		}

		Print("[" + m_AppName + "] Ready. Logging commences in " + m_Logger.m_LogFile);
		AutolockVehicles_App.GetInstance().m_Logger.Log("Ready.");
	}

	static AutolockVehicles_App GetInstance()
	{
		if (!s_Instance) new AutolockVehicles_App();
		return s_Instance;
	}

	void AddKeyMod(string name, AutolockVehicles_KeyModBase keyMod)
	{
		if(!m_KeyMods) m_KeyMods = new map<string, ref AutolockVehicles_KeyModBase>();
		m_KeyMods.Set(name, keyMod);
	}

	AutolockVehicles_KeyModBase GetKeyMod()
	{
		if(!m_KeyMods) m_KeyMods = new map<string, ref AutolockVehicles_KeyModBase>();
		if(!m_KeyMod) m_KeyMod = m_KeyMods.Get(EnumTools.EnumToString(AutolockVehicles_KeyMod, m_Settings.UseKeyMod));
		return m_KeyMod;
	}

	// unused, leaving for reference
	int GetPassengerCount(CarScript car)
	{
		if(!car) return 0;

		int passengerCount = 0;
        for (int index = 0; index < car.CrewSize(); ++index)
		{
			if (car.CrewMember(index)) passengerCount++;
		}

		return passengerCount;
	}

	void StartAutolockTimer(CarScript car, AutolockVehicles_TimerMode mode)
    {
		if(!car)
        {
            m_Logger.DebugLog("No vehicle, exiting");
            return;
        }
       
		AutolockVehicles_KeyModBase keyMod = GetKeyMod();
		if(!keyMod)
        {
            m_Logger.DebugLog("UseKeyMod is set to " + m_Settings.UseKeyMod + " (" + EnumTools.EnumToString(AutolockVehicles_KeyMod, m_Settings.UseKeyMod) + ") but the required mod doesn't seem to be installed");
            return;
        }

		if(keyMod.GetVehicleState(car) == AutolockVehicles_State.UNASSIGNED)
        {
            m_Logger.DebugLog("Car doesn't even have a lock, no timer will be started, exiting");
            return;
        }

        if(keyMod.GetVehicleState(car) == AutolockVehicles_State.LOCKED)
        {
            m_Logger.DebugLog("Car already locked, no timer will be started, exiting");
            return;
        }

        int AutolockDelay;

        switch(mode)
        {
            case AutolockVehicles_TimerMode.STARTUP:
            {
                AutolockDelay = m_Settings.AutolockDelay_Startup;
                break;
            }
			case AutolockVehicles_TimerMode.PLAYERDISCONNECT:
            {
                AutolockDelay = m_Settings.AutolockDelay_PlayerDisconnect;
                break;
            }
            default:
            {
                m_Logger.DebugLog("Unknown AutolockVehicles_TimerMode:" + mode);
                return;
            }
        }

        m_Logger.DebugLog("Starting autolock timer, mode:" + typename.EnumToString(AutolockVehicles_TimerMode, mode) + ", minutes:" + AutolockDelay);

        Param1<CarScript> carParam = new Param1<CarScript>(car);
		Timer timer = new Timer();
		timer.Run(AutolockDelay * 60, this, m_TimerTargetFunctionName, carParam, false);
		m_Timers.Set(car.GetID(), timer);
    }

	void RemoveAutolockTimer(CarScript car, string Reason)
    {
        if(!GetGame().IsServer()) return;
		if(!car) return;

        m_Logger.DebugLog("Removing autolock timer, (" + Reason + ")");
        m_Timers.Remove(car.GetID());
    }

	void OnPlayerDisconnect(PlayerBase player)
	{
		if(!player) return;
		if(!player.GetIdentity()) return;
		
		string playerId = player.GetIdentity().GetPlainId();
        m_Logger.DebugLog("Starting OnDisconnect autolock, player:" + playerId);

		if(!player.m_AutolockVehicles_CurrentUnlockedVehicle)
        {
            m_Logger.DebugLog("Player doesn't have a currently unlocked vehicle assigned, exiting");
            return;
        }
      
        StartAutolockTimer(player.m_AutolockVehicles_CurrentUnlockedVehicle, AutolockVehicles_TimerMode.PLAYERDISCONNECT);
	}

	void CloseAllDoors(CarScript car)
	{
		if(!car) return;

		string doorsAnimSources[6] = {
			"DoorsDriver",
			"DoorsCoDriver",
			"DoorsCargo1",
			"DoorsCargo2",
			"DoorsHood",
			"DoorsTrunk"
		};

		foreach(string animSource : doorsAnimSources)
		{
			car.SetAnimationPhase(animSource, 0.0);
		}
	}

	void LockVehicle(CarScript car)
	{
		m_Logger.DebugLog("Starting LockVehicle");

		if(!car)
        {
            m_Logger.DebugLog("No car, exiting");
            return;
        }

		AutolockVehicles_KeyModBase keyMod = GetKeyMod();
		if(!keyMod)
        {
            m_Logger.DebugLog("UseKeyMod is set to " + m_Settings.UseKeyMod + " (" + EnumTools.EnumToString(AutolockVehicles_KeyMod, m_Settings.UseKeyMod) + ") but the required mod doesn't seemto be installed");
            return;
        }

		if(keyMod.GetVehicleState(car) == AutolockVehicles_State.UNASSIGNED)
        {
            m_Logger.DebugLog("Car doesn't even have a lock, not locking");
            return;
        }

        if(keyMod.GetVehicleState(car) == AutolockVehicles_State.LOCKED)
        {
            m_Logger.DebugLog("Car already locked, not locking, exiting");
            return;
        }

		m_Logger.Log("Locking vehicle");

		car.EngineStop();
		CloseAllDoors(car);
		keyMod.LockVehicle(car);
	}
}
