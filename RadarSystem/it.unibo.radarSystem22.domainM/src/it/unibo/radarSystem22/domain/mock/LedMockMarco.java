package it.unibo.radarSystem22.domain.mock;

import it.unibo.radarSystem22.domain.intefaces.ILed;

public class LedMockMarco implements ILed{
	private boolean state;
	@Override
	public void turnOn() {
		// TODO Auto-generated method stub
		this.state=true;
	}

	@Override
	public void turnOff() {
		// TODO Auto-generated method stub
		this.state=false;
	}

	@Override
	public boolean getState() {
		// TODO Auto-generated method stub
		return this.state;
	}
	
}
