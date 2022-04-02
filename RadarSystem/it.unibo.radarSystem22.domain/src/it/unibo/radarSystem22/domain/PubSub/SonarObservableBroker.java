package it.unibo.radarSystem22.domain.PubSub;

import java.util.ArrayList;
import java.util.List;

public class SonarObservableBroker {
	private List<SonarObserverConcrete> subscrivers=new ArrayList<SonarObserverConcrete>();
	public void subscribe(SonarObserverConcrete observer) {
		subscrivers.add(observer);
	}
	
	public void unSubscribe(SonarObserverConcrete observer) {
		subscrivers.remove(observer);
	}

	public void publish(int v) {
		// TODO Auto-generated method stub
		for(SonarObserverConcrete observer:subscrivers) {
			observer.update(v);
			System.out.println(observer.getVal());
		}
		
	}

	
}
