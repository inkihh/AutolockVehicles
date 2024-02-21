class CfgPatches
{
	class AutolockVehicles
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};   
};

class CfgMods
{
	class AutolockVehicles
	{
		dir = "inkihh";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "AutolockVehicles";
		credits = "";
		author = "inkihh";
		authorID = "0";
		version = "1";
		extra = 0;
		type = "mod";

		dependencies[] =
		{
			"World", "Mission"
		};

		class defs
		{
			class worldScriptModule
			{
				value="";
				files[] =
				{
					"inkihh/AutolockVehicles/scripts/4_World"
				};
			};

			class missionScriptModule
			{
				value="";
				files[] =
				{
					"inkihh/AutolockVehicles/scripts/5_Mission"
				};
			};
		};
	};
};

class CfgVehicles {};
