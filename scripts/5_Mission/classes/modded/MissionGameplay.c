#ifndef CARLOCKDISABLE
#ifdef CarLock
modded class MissionGameplay
{
	override void OnUpdate(float timeslice)
	{
        super.OnUpdate(timeslice);

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

        if(!player) return;
        if(!player.m_AutolockVehicles_CurrentUnlockedVehicle) return;

        vector playerPosition = player.GetPosition();
        vector vehiclePosition = player.m_AutolockVehicles_CurrentUnlockedVehicle.GetPosition();

		float distance = vector.Distance(playerPosition, vehiclePosition);

        if(distance > 20)
        {
            Print("[AutolockVehicles.MissionGameplay] distance:" + distance);
            player.m_AutolockVehicles_CurrentUnlockedVehicle = null;
           
            player.RPCSingleParam(AutolockVehicles_RPC.LOCK_PROXIMITY, null, true);
        }
		super.OnUpdate(timeslice);

	}
}
#endif
#endif
