class CfgPatches
{
	class FOGAutolockVehicles
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"MuchCarKey"
		};
	};   
};

class CfgMods
{
	class FOGAutolockVehicles
	{
		dir = "FOG";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "FOGAutolockVehicles";
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
					"FOG\FOGAutolockVehicles\scripts\4_World"
				};
			};

			class missionScriptModule
			{
				value="";
				files[] =
				{
					"FOG\FOGAutolockVehicles\scripts\5_Mission"
				};
			};
		};
	};
};

class CfgVehicles {};
