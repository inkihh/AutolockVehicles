#ifdef LoggingTools_Server_Vehicles
#ifndef CARLOCKDISABLE
#ifdef CarLock
modded class PlayerBase extends ManBase
{
    ref FOGAutolockVehicles_App m_App;

    override void OnDisconnect()
    {
        if (!GetGame().IsServer()) return;
        if(!m_App) m_App = FOGAutolockVehicles_App.GetInstance();

        m_App.OnPlayerDisconnect(this);
        super.OnDisconnect();
    }
}
#endif
#endif
#endif
