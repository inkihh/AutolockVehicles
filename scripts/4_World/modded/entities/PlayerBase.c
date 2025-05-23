modded class PlayerBase extends ManBase
{
	#ifdef SERVER
		ref AutolockVehicles_App m_AutolockVehicles_App = AutolockVehicles_App.GetInstance();
	#endif

	CarScript m_AutolockVehicles_LastUnlockedVehicle;

	int m_AutolockVehicles_proximity_lock_distance_meters;
	int m_AutolockVehicles_proximity_unlock_distance_meters;

	#ifdef SERVER
		override void OnDisconnect()
		{
			if (!GetGame().IsServer()) return;
			if(!m_AutolockVehicles_App) m_AutolockVehicles_App = AutolockVehicles_App.GetInstance();

			m_AutolockVehicles_App.OnPlayerDisconnect(this);
			super.OnDisconnect();
		}
	#endif

	string m_AutolockVehicles_GetNetworkId(Object object)
	{
		if(!object) return "";

		int lowBits;
		int highBits;
		object.GetNetworkID(lowBits, highBits);

		string networkId = lowBits.ToString() + highBits.ToString();

		return networkId;
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		PlayerBase player;

		switch (rpc_type)
		{
			case AutolockVehicles_RPC.START_PROXIMITY: // triggered by unlocking
			{
				if(!GetGame().IsClient()) return;

				Param3<string, int, int> carParam;
				if (!ctx.Read(carParam)) return;

				string persistentId = carParam.param1;
				m_AutolockVehicles_proximity_lock_distance_meters = carParam.param2;
				m_AutolockVehicles_proximity_unlock_distance_meters = carParam.param3;
				
				array<Object> objects_around = new array<Object>;
				GetGame().GetObjectsAtPosition(GetPosition(), 10, objects_around, NULL);

				foreach(Object object_around : objects_around)
				{
					CarScript car = CarScript.Cast(object_around);
					if(!car) continue;

					if(m_AutolockVehicles_GetNetworkId(object_around) == persistentId)
					{
						m_AutolockVehicles_LastUnlockedVehicle = CarScript.Cast(object_around);
						car.m_AutolockVehicles_LastPlayerUnlocked = this;
						car.m_AutolockVehicles_WasProximityLocked = false;
						break;
					}
				}

				break;
			}

			#ifdef SERVER
			case AutolockVehicles_RPC.LOCK_PROXIMITY:
			{
				if(!GetGame().IsServer()) return;

				AutolockVehicles_App.GetInstance().m_Logger.Log("[PlayerBase.OnRPC] AutolockVehicles_RPC.LOCK_PROXIMITY");

				if(!AutolockVehicles_App.GetInstance().m_Settings.enable_proximity_autolock)
				{
					AutolockVehicles_App.GetInstance().m_Logger.Log("[PlayerBase.OnRPC] enable_proximity_autolock not set, exiting");
					return;
				}

				player = PlayerBase.Cast(sender.GetPlayer());
				if(!player) return;
				if(!player.m_AutolockVehicles_LastUnlockedVehicle) return;

				AutolockVehicles_App.GetInstance().LockVehicle(player.m_AutolockVehicles_LastUnlockedVehicle);

				break;
			}

			case AutolockVehicles_RPC.UNLOCK_PROXIMITY:
			{
				if(!GetGame().IsServer()) return;

				AutolockVehicles_App.GetInstance().m_Logger.Log("[PlayerBase.OnRPC] AutolockVehicles_RPC.UNLOCK_PROXIMITY");

				if(!AutolockVehicles_App.GetInstance().m_Settings.enable_proximity_autounlock)
				{
					AutolockVehicles_App.GetInstance().m_Logger.Log("[PlayerBase.OnRPC] enable_proximity_autounlock not set, exiting");
					return;
				}

				player = PlayerBase.Cast(sender.GetPlayer());
				if(!player) return;
				if(!player.m_AutolockVehicles_LastUnlockedVehicle) return;

				AutolockVehicles_App.GetInstance().UnlockVehicle(player.m_AutolockVehicles_LastUnlockedVehicle);

				break;
			}
			#endif
		}
	}
}
