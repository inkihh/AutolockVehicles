class FOGAutolockVehiclesMilitaryCrate extends Msp_MilitaryCrate_Base
{
    float m_secondsSinceLastUpdate = 0.0;
    float m_updateFrequencySeconds;

    bool m_CanBeTaken = true;

    ref FOGCrateConfiguration m_CrateConfiguration;
    ref FOGAutolockVehicles_Logger m_Logger;

    void FOGAutolockVehiclesMilitaryCrate()
    {
        m_Logger = FOGAutolockVehicles_App.GetInstance().m_Logger;
        m_Logger.Log("FOGAutolockVehiclesMilitaryCrate constructor");

        m_updateFrequencySeconds = FOGAutolockVehicles_App.GetInstance().m_Settings.bury_time;
        m_Logger.Log("Set bury time to " + m_updateFrequencySeconds);
    }

    void SetCrateConfiguration(FOGCrateConfiguration CrateConfiguration)
    {
        m_Logger.Log("FOGAutolockVehiclesMilitaryCrate SetCrateConfiguration");

        m_CrateConfiguration = CrateConfiguration;
        FillCargo();
    }

    void FillCargo()
    {
        m_Logger.Log("FOGAutolockVehiclesMilitaryCrate FillCargo");
        GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);

        if(m_CrateConfiguration.note)
        {
            m_Logger.Log("Creating note");
            WrittenNote note = WrittenNote.Cast(GetInventory().CreateInInventory("WrittenNote"));

            if(!note)
                m_Logger.Log("Note is null!");
            else {
                WrittenNoteData note_data = new WrittenNoteData(note);
                EnScript.SetClassVar(note_data, "m_SimpleText", 0, m_CrateConfiguration.note);
                note_data.SetNoteColor(ARGB(255, 0, 0, 0));
                note.SetWrittenNoteData(note_data);
            }
        }

        if(m_CrateConfiguration.code)
            CreateLock(m_CrateConfiguration.code);

        GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
    }

    bool CreateLock(string passcode)
    {
        if (!GetGame().IsDedicatedServer())
            return false;

        if (!GetInventory())
            return false;

        if (GetInventory().FindAttachmentByName("Att_CombinationLock"))
            return false;

        CodeLock lock;
        if (!CodeLock.CastTo(lock, GetInventory().CreateAttachment("CodeLock")))
            return false;

        lock.LockServer(this, passcode);
        lock.ServerSetOwner("adgad67sadga67sgd76");
        return true;
    }

    override bool CanPutInCargo(EntityAI parent)
    {
        UndergroundStash stash;
        Class.CastTo(stash, parent);

        if(stash) return true;
        return false;
    }

    override bool OnStoreLoad (ParamsReadContext ctx, int version)
	{
		if ( !super.OnStoreLoad(ctx, version) )
			return false;
		
        Delete();

		return true;
	}

    override bool CanPutIntoHands(EntityAI parent)
    {
        return m_CanBeTaken; 
    }

    override void EEItemLocationChanged (notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc) {

        super.EEItemLocationChanged (oldLoc, newLoc);

		if( oldLoc.GetType() == InventoryLocationType.CARGO ) {
            SetCannotBeTakenIntoHands();
            return;
        }

        GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(this, "SetCannotBeTakenIntoHands", 5000);
    }

    void SetCannotBeTakenIntoHands() {
        m_CanBeTaken = false;
    }

    void Bury()
    {
        Close();

        m_Logger.Log("Crate to be buried? " + m_CrateConfiguration.buried);
        if(!m_CrateConfiguration.buried) return;

        InventoryLocation il = new InventoryLocation;
        GetInventory().GetCurrentInventoryLocation(il);

        if( il && il.GetType() != InventoryLocationType.GROUND)
        {
            m_Logger.Log("RiddleCrate not on ground, exiting Bury()");
            return;
        }

        m_Logger.Log("Putting crate into stash");

        UndergroundStash stash = UndergroundStash.Cast( GetGame().CreateObjectEx( "UndergroundStash", m_CrateConfiguration.position.ToVector(), ECE_PLACE_ON_SURFACE ));
        stash.PlaceOnGround();
        stash.SetOrientation(m_CrateConfiguration.orientation.ToVector());
        ServerTakeEntityToTargetCargo(stash, this);
        stash.Update();
    }

    override void OnCEUpdate() {

        super.OnCEUpdate();

        m_secondsSinceLastUpdate = m_secondsSinceLastUpdate + m_ElapsedSinceLastUpdate;
        
        if(m_secondsSinceLastUpdate > m_updateFrequencySeconds) {
            m_secondsSinceLastUpdate = 0.0;
            Bury();
        }
    }
}