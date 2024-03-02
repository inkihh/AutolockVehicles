#ifdef CarCover
modded class ActionAddCarCover : ActionCoverUncoverCar
{
    override void OnFinishProgressServer(ActionData action_data)
    {
		CarScript car = CarScript.Cast(action_data.m_Target.GetObject());
		if (!car) car = CarScript.Cast(action_data.m_Target.GetParent());
		if (!car) return;
		
		AutolockVehicles_App.GetInstance().LockVehicle(car);

		super.OnFinishProgressServer(action_data);
	};
};
#endif
