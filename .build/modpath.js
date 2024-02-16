"use strict";

const fs = require('fs');
const glob = require("glob")

const clientpath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\DayZ\\!dzsal\\";

const modlist = process.argv[2];
//const modlist="@CF;@Dabs Framework;@Winter Chernarus;@BuilderItems;@BadgerBuildings;@VanillaRoadPartsPack;@Code Lock;@BaseBuildingPlus;@FlipTransport;@Server_Information_Panel;@Uncuepas Civilian Clothing;@SimpleAutorun;@MuchStuffPack;@MuchCarKey;@CheckIdentity;@Forever_Lights_and_Campfires;@ZT Vending Machine;@IRP-Land-Rover-Defender-110;@TraderFixesAndFeatures;@[Remastered] Arma Weapon Pack;@MedicalAttentionUpdated;@MedicalAttentionUpdated-Core;@MedicalAttentionUpdated-DepHelper-Vanilla;@Disease Injectors;@CPBWeapons;@WindstridesClothingPack;@Cl0ud's Military Gear;@MAGLoadingscreenChernoWinter;@MAGVehiclesAir;@MAGServerPackCherno;@DrugsPLUS;@CannabisPlus;@MunghardsItempack;@Modular Vest System;@Durable Suppressors;@RaG_ATV;@RaG_Hummer_Armored;@SpawnerBubaku;@ZombieCooKie Darkness;@Better Filter;@Cl0ud's Winter Gear;@Savage Snowmobiles;@Ear-Plugs;@DayZ Editor Loader;@Notes;@AdvancedGroups;@AdvancedGroups Plotpole DLC New;@Enhanced Banking;@PVEZ;@Trader;@VPPAdminTools;@COCAs_NoVehicleDamageMOD";

const mods = modlist.split(";");

const fullmods = [];

for (let index = 0; index < mods.length; index++) {
    const mod = mods[index];
    const modpath = `${clientpath}${mod}`;

    fullmods.push(modpath);
    
    /* glob(`${clientpath}${mod}\\[kK]ey*(s)\*`, function (er, files) {
        if(er) return;
        console.log(`Checking ${mod}`);
        console.log(files);
    }) */

    /* fs.copyFile(`${clientpath}${mod}\\keys\*`, , (err) => {
        if (err) throw err;
        console.log('source.txt was copied to destination.txt');
    }); */
  

}

console.log(fullmods.join(";"));
