CONTAINER Oparticlemodifier
{
	NAME Oparticlemodifier;
	INCLUDE Obase;

	GROUP ID_OBJECTPROPERTIES
	{
		SCALE_V;

		STRING OPARTICLEMODIFIER_CODE
		{
		  CUSTOMGUI MULTISTRING;
		  PYTHON;
		  SCALE_V;
		}

		BUTTON OPARTICLEMODIFIER_OPENEDITOR { }
	}    
}
