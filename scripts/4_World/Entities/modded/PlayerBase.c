modded class PlayerBase extends ManBase
{
    #ifdef SERVER
        ref AutolockVehicles_App m_AutolockVehicles_App = AutolockVehicles_App.GetInstance();
    #endif

    CarScript m_AutolockVehicles_CurrentUnlockedVehicle;
    int m_AutolockVehicles_ProximityLock_DistanceMeters;

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

        switch (rpc_type)
        {
            case AutolockVehicles_RPC.START_PROXIMITY:
            {
                if(!GetGame().IsClient()) return;

                Param2<string, int> carParam;
                if (!ctx.Read(carParam)) return;

                string persistentId = carParam.param1;
                m_AutolockVehicles_ProximityLock_DistanceMeters = carParam.param2;
                
                Print("[AutolockVehicles] persistentId from rpc: " + persistentId);
                Print("[AutolockVehicles] m_AutolockVehicles_ProximityLock_DistanceMeters: " + m_AutolockVehicles_ProximityLock_DistanceMeters);

                array<Object> objects_around = new array<Object>;
                GetGame().GetObjectsAtPosition(GetPosition(), 10, objects_around, NULL);

                foreach(Object object_around : objects_around)
                {
                    if(!object_around.IsInherited(CarScript)) continue;

                    Print("[AutolockVehicles] m_AutolockVehicles_GetNetworkId(object_around) " + AutolockVehicles_Helper.GetNetworkID(object_around));

                    if(m_AutolockVehicles_GetNetworkId(object_around) == persistentId)
                    {
                        Print("[AutolockVehicles] setting m_AutolockVehicles_CurrentUnlockedVehicle");
                        m_AutolockVehicles_CurrentUnlockedVehicle = CarScript.Cast(object_around);
                        break;
                    }
                }

                break;
            }

            #ifdef SERVER
            case AutolockVehicles_RPC.LOCK_PROXIMITY:
            {
                if(!GetGame().IsServer()) return;

                AutolockVehicles_App.GetInstance().m_Logger.Log("[AutolockVehicles] AutolockVehicles_RPC.LOCK_PROXIMITY");

                PlayerBase player = PlayerBase.Cast(sender.GetPlayer());
                if(!player) return;
                if(!player.m_AutolockVehicles_CurrentUnlockedVehicle) return;

                AutolockVehicles_App.GetInstance().LockVehicle(player.m_AutolockVehicles_CurrentUnlockedVehicle);

                break;
            }
            #endif
        }
    }
}
