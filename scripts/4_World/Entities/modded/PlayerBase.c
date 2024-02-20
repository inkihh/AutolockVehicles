#ifndef CARLOCKDISABLE
#ifdef CarLock
modded class PlayerBase extends ManBase
{
    #ifdef LoggingTools_Server_Vehicles
        ref FOGAutolockVehicles_App m_FOGAutolockVehicles_App = FOGAutolockVehicles_App.GetInstance();
    #endif

    CarScript m_FOGAutolockVehicles_CurrentUnlockedVehicle;
    int m_FOGAutolockVehicles_ProximityLock_DistanceMeters;

    #ifdef LoggingTools_Server_Vehicles
        override void OnDisconnect()
        {
            if (!GetGame().IsServer()) return;
            if(!m_FOGAutolockVehicles_App) m_FOGAutolockVehicles_App = FOGAutolockVehicles_App.GetInstance();

            m_FOGAutolockVehicles_App.OnPlayerDisconnect(this);
            super.OnDisconnect();
        }
    #endif

    string m_FOGAutolockVehicles_GetNetworkId(Object object)
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
            case FOGAutolockVehicles_RPC.START_PROXIMITY:
            {
                if(!GetGame().IsClient()) return;

                Param2<string, int> carParam;
                if (!ctx.Read(carParam)) return;

                string persistentId = carParam.param1;
                m_FOGAutolockVehicles_ProximityLock_DistanceMeters = carParam.param2;
                
                Print("[FOGAutolockVehicles] persistentId from rpc: " + persistentId);
                Print("[FOGAutolockVehicles] m_FOGAutolockVehicles_ProximityLock_DistanceMeters: " + m_FOGAutolockVehicles_ProximityLock_DistanceMeters);

                array<Object> objects_around = new array<Object>;
                GetGame().GetObjectsAtPosition(GetPosition(), 10, objects_around, NULL);

                foreach(Object banana : objects_around)
                {
                    if(!banana.IsInherited(CarScript)) continue;

                    Print("[FOGAutolockVehicles] m_FOGAutolockVehicles_GetNetworkId(banana) " + m_FOGAutolockVehicles_GetNetworkId(banana));

                    if(m_FOGAutolockVehicles_GetNetworkId(banana) == persistentId)
                    {
                        Print("[FOGAutolockVehicles] setting m_FOGAutolockVehicles_CurrentUnlockedVehicle");
                        m_FOGAutolockVehicles_CurrentUnlockedVehicle = CarScript.Cast(banana);
                        break;
                    }
                }

                break;
            }

            #ifdef LoggingTools_Server_Vehicles
            case FOGAutolockVehicles_RPC.LOCK_PROXIMITY:
            {
                if(!GetGame().IsServer()) return;

                FOGAutolockVehicles_App.GetInstance().m_Logger.Log("[FOGAutolockVehicles] FOGAutolockVehicles_RPC.LOCK_PROXIMITY");

                PlayerBase player = PlayerBase.Cast(sender.GetPlayer());
                if(!player) return;
                if(!player.m_FOGAutolockVehicles_CurrentUnlockedVehicle) return;

                FOGAutolockVehicles_App.GetInstance().LockVehicle(player.m_FOGAutolockVehicles_CurrentUnlockedVehicle);

                break;
            }
            #endif
        }
    }
}
#endif
#endif
