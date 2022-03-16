package it.unibo.radarSystem22.domain.mock;


import it.unibo.radarSystem22.domain.intefaces.ILed;
import it.unibo.radarSystem22.domain.models.LedModel;


public class LedMock extends LedModel implements ILed{  

	@Override
	protected void ledActivate(boolean val) {	
		showState();
	}

	protected void showState(){
		ColorsOut.outappl("LedMock state=" + getState(), ColorsOut.MAGENTA );
	}
} 