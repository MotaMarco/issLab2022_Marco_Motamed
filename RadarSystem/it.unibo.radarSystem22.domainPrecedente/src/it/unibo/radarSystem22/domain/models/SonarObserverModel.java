package it.unibo.radarSystem22.domain.models;

import it.unibo.radarSystem22.domain.interfaces.ISonarObserver;

public abstract class SonarObserverModel implements ISonarObserver{
	protected int val;

	@Override
	public abstract void update(int value);

	public int getVal() {
		return val;
	}


}
