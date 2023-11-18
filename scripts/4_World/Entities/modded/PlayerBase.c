modded class PlayerBase extends ManBase
{
    ref FOGAutolockVehicles_App m_App;

    void PlayerBase()
    {
        m_App = FOGAutolockVehicles_App.GetInstance();
    }

    bool PlayerIsDriver(Transport trans, PlayerBase player)
	{
		return trans.GetSeatAnimationType(trans.CrewMemberIndex(player)) == DayZPlayerConstants.VEHICLESEAT_DRIVER;
	}

    override void OnDisconnect()
    {
        string PlayerId = GetIdentity().GetPlainId()

        if (!GetGame().IsServer())
        {
            m_App.m_Logger.DebugLog("Must run on server, exiting");
            return;
        }

        m_App.m_Logger.DebugLog("Starting OnDisconnect autolock (" + PlayerId + ")");

        HumanCommandVehicle vehCommand = GetCommand_Vehicle();

		if (!vehCommand) 
        {
            m_App.m_Logger.DebugLog("No CommandVehicle, exiting");
            return;
        }

        Transport trans = vehCommand.GetTransport();
		if (!trans) 
        {
            m_App.m_Logger.DebugLog("No transport, exiting");
            return;
        }

        if (!PlayerIsDriver(trans, this)) 
        {
            m_App.m_Logger.DebugLog("Player (" + PlayerId + ") not driver, exiting");
            return;
        }

        CarScript car;
        Class.CastTo(car, trans);

        if(!car) 
        {
            m_App.m_Logger.DebugLog("No Car object, exiting");
            return;
        }
        
        car.DoAutolock(this);

        super.OnDisconnect();
    }
}