/*
- On player disconnect
-- Player not in a vehicle? EXIT
-- Player not driver of that vehicle? EXIT
-- Goto StartTimer with settings.AutolockDelay_PlayerDisconnect

- On vehicle spawn (restart, receipt thrown, parked out, ..)
-- Goto StartTimer with settings.AutolockDelay_Startup

- Vehicle engine stop
-- Goto StartTimer with settings.AutolockDelay_EngineStop

- Vehicle engine start, vehicle deleted or destroyed
-- Stop timer

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

enum FOGAutolockVehicles_TimerMode
{
	STARTUP = 0 
	ENGINESTOP = 1
	PLAYERDISCONNECT = 3
}

class FOGAutolockVehicles_App
{
	protected static ref FOGAutolockVehicles_App s_Instance;
	static const string m_AppName = "FOGAutolockVehicles";

	ref FOGAutolockVehicles_Logger m_Logger;
	ref FOGAutolockVehicles_Settings m_Settings;
	    
	string m_TimerTargetFunctionName = "LockVehicle";

	ref map<int, ref Timer> m_Timers;

	void FOGAutolockVehicles_App()
	{
		m_Logger = new FOGAutolockVehicles_Logger(m_AppName);
		m_Settings = new FOGAutolockVehicles_Settings(m_AppName);
		m_Timers = new map<int, ref Timer>;

		s_Instance = this;

		if (!m_Settings.IsLoaded())
		{
			Print("[" + m_AppName + "] Settings incomplete. Please check " + m_Logger.m_LogFile);
			Print("[" + m_AppName + "] If it didn't exist at all, an empty one was created right now.");
			return;
		}

		Print("[" + m_AppName + "] Ready. Logging commences in " + m_Logger.m_LogFile);
		FOGAutolockVehicles_App.GetInstance().m_Logger.Log("Ready.");
	}

	static FOGAutolockVehicles_App GetInstance()
	{
		if (!s_Instance) new FOGAutolockVehicles_App();
		return s_Instance;
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

	void StartAutolockTimer(CarScript car, FOGAutolockVehicles_TimerMode mode)
    {
		if(!car) 
        {
            m_Logger.DebugLog("No vehicle, exiting");
            return;
        }
       
		if(car.m_CarLockPassword == -1)
        {
            m_Logger.DebugLog("Car doesn't even have a lock, no timer will be started, exiting");
            return;
        }

        if(car.m_CarLock_IsLocked)
        {
            m_Logger.DebugLog("Car already locked, no timer will be started, exiting");
            return;
        }

        int AutolockDelay;

        switch(mode)
        {
            case FOGAutolockVehicles_TimerMode.STARTUP:
            {
                AutolockDelay = m_Settings.AutolockDelay_Startup;
                break;
            }
            case FOGAutolockVehicles_TimerMode.ENGINESTOP:
            {
                AutolockDelay = m_Settings.AutolockDelay_EngineStop;
                break;
            }
			case FOGAutolockVehicles_TimerMode.PLAYERDISCONNECT:
            {
                AutolockDelay = m_Settings.AutolockDelay_PlayerDisconnect;
                break;
            }
            default:
            {
                m_Logger.DebugLog("Unknown FOGAutolockVehicles_TimerMode:" + mode);
                return;
            }
        }

        //RemoveAutolockTimer("Cleanup possibly existing timers on starting a new timer");
        m_Logger.DebugLog("Starting autolock timer, mode:" + typename.EnumToString(FOGAutolockVehicles_TimerMode, mode) + ", vehicle:" + car.m_LoggingTools_CarLock_VehicleId + ", minutes:" + AutolockDelay);

        Param1<CarScript> carParam = new Param1<CarScript>(car);
        //GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, m_TimerTargetFunctionName, (AutolockDelay * 60 * 1000), false, carParam);
		Timer timer = new Timer();
		timer.Run(AutolockDelay * 60, this, m_TimerTargetFunctionName, carParam, false);
		m_Timers.Set(car.m_LoggingTools_CarLock_VehicleId, timer);
    }

	void RemoveAutolockTimer(CarScript car, string Reason)
    {
        if(!GetGame().IsServer()) return;
		if(!car) return;

        m_Logger.DebugLog("Removing autolock timer, vehicle:" + car.m_LoggingTools_CarLock_VehicleId + " (" + Reason + ")");
        m_Timers.Remove(car.m_LoggingTools_CarLock_VehicleId);
    }

	void OnPlayerDisconnect(PlayerBase player)
	{
		if(!player) return;
		if(!player.GetIdentity()) return;
		
		string playerId = player.GetIdentity().GetPlainId();
        m_Logger.DebugLog("Starting OnDisconnect autolock, player:" + playerId);

		HumanCommandVehicle commandVehicle = player.GetCommand_Vehicle();

		if (!commandVehicle) 
		{
			m_Logger.DebugLog("Player not commanding vehicle, exiting");
			return;
		}

		Transport transport = commandVehicle.GetTransport();
		if (!transport) 
		{
			m_Logger.DebugLog("CarScript couldn't be cast into Transport, exiting");
			return;
		}

		if (!transport.GetSeatAnimationType(transport.CrewMemberIndex(player)) == DayZPlayerConstants.VEHICLESEAT_DRIVER)
		{
			m_Logger.DebugLog("Player not driver, exiting");
			return;
		}

        CarScript car;
        Class.CastTo(car, transport);

        if(!car) 
        {
            m_Logger.DebugLog("Transport couldn't be cast into CarScript, exiting");
            return;
        }
        
        StartAutolockTimer(car, FOGAutolockVehicles_TimerMode.PLAYERDISCONNECT);
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

		CloseAllDoors(car);

		if(car.m_CarLockPassword == -1)
        {
            m_Logger.DebugLog("Car doesn't even have a lock, no timer will be started, exiting");
            return;
        }

        if(car.m_CarLock_IsLocked)
        {
            m_Logger.DebugLog("Car already locked, no timer will be started, exiting");
            return;
        }

		m_Logger.Log("Locking vehicle:" + car.m_LoggingTools_CarLock_VehicleId);

		car.SetSoundToPlay(1);
		car.SetCarLock(true);
	}
}
