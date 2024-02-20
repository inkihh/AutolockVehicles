#ifndef CARLOCKDISABLE
#ifdef CarLock
modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
        super.OnUpdate(timeslice);

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

        if(!player) return;
        if(!player.m_FOGAutolockVehicles_CurrentUnlockedVehicle) return;

        vector playerPosition = player.GetPosition();
        vector vehiclePosition = player.m_FOGAutolockVehicles_CurrentUnlockedVehicle.GetPosition();

		float distance = vector.Distance(playerPosition, vehiclePosition);

        if(distance > 20)
        {
            Print("[FOGAutolockVehicles.MissionGameplay] distance:" + distance);
            player.m_FOGAutolockVehicles_CurrentUnlockedVehicle = null;
           
            player.RPCSingleParam(FOGAutolockVehicles_RPC.LOCK_PROXIMITY, null, true);
        }
		super.OnUpdate(timeslice);

	}
}
#endif
#endif
