package it.unibo.radarSystem22.domain.PubSub;

import it.unibo.radarSystem22.domain.interfaces.ISonarObserver;
import it.unibo.radarSystem22.domain.models.SonarObserverModel;

public class SonarObserverConcrete extends SonarObserverModel implements ISonarObserver{

	@Override
	public void update(int value) {
		System.out.println("Valore Observer: "+val);
		val=value;
	}

}
