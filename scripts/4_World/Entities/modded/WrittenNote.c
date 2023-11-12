modded class WrittenNote extends Paper {

    bool m_WasCopied = false;

    override void EEItemLocationChanged (notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc) {

        super.EEItemLocationChanged (oldLoc, newLoc);

        if( m_WasCopied ) return;
		
        EntityAI old_container = oldLoc.GetParent();
        FOGAutolockVehiclesMilitaryCrate riddle_crate_old;
        if( old_container ) Class.CastTo(riddle_crate_old, old_container);
        if( !riddle_crate_old ) return; // doesn't come from riddle crate
        
        EntityAI new_container = newLoc.GetParent();
        FOGAutolockVehiclesMilitaryCrate riddle_crate_new;
        if( new_container ) Class.CastTo(riddle_crate_new, new_container);
        
        if( riddle_crate_old && riddle_crate_new ) return; // moved within riddle crate cargo

        string new_owner_id = "UNKNOWN (UNKNOWN)";
        PlayerBase new_owner_player;
        if( new_container ) Class.CastTo(new_owner_player, new_container.GetHierarchyRootPlayer());
        if( new_owner_player ) new_owner_id = new_owner_player.GetIdentity().GetName() + " (" + new_owner_player.GetIdentity().GetPlainId() + ")";

        //WrittenNote copied_item = riddle_crate_old.GetInventory().LocationCreateEntity( oldLoc, GetType(), ECE_IN_INVENTORY, RF_DEFAULT );
        WrittenNote note = WrittenNote.Cast(riddle_crate_old.GetInventory().CreateEntityInCargo("WrittenNote"));
        note.SetWrittenNoteData(m_NoteContents);
        m_WasCopied = true;

        FOGAutolockVehicles_App.GetInstance().GetLogger().Log(GetType() + " taken from \"" + riddle_crate_old.m_CrateConfiguration.name + "\" at " + riddle_crate_old.GetPosition() + " by " + new_owner_id);
    }
}

