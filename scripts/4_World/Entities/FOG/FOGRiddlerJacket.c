/* class FOGAutolockVehiclesrJacket extends QuiltedJacket_ColorBase {

    bool m_WasCopied = false;

    override void EEItemLocationChanged (notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc) {

        super.EEItemLocationChanged (oldLoc, newLoc);

        if( m_WasCopied ) return;
		
        EntityAI new_owner = newLoc.GetParent();
        PlayerBase new_owner_player;
        if( new_owner ) Class.CastTo(new_owner_player, new_owner.GetHierarchyRootPlayer());
        if( !new_owner_player ) return;

        EntityAI old_owner = oldLoc.GetParent();
        FOGAutolockVehiclesMilitaryCrate riddle_crate;
        if( old_owner ) Class.CastTo(riddle_crate, old_owner);
        if( !riddle_crate ) return;
        
        FOGAutolockVehiclesrJacket copied_item = riddle_crate.GetInventory().LocationCreateEntity( oldLoc, GetType(), ECE_IN_INVENTORY, RF_DEFAULT );
        m_WasCopied = true;

        FOGAutolockVehicles_App.GetInstance().GetLogger().Log(GetType() + " taken from a chest at " + riddle_crate.GetPosition() + " by " + new_owner_player.GetIdentity().GetName() + " (" + new_owner_player.GetIdentity().GetPlainId() + ")");
    }
}
 */