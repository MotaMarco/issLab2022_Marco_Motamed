package it.unibo.radarSystem22.domain;

import static org.junit.Assert.assertTrue;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import it.unibo.radarSystem22.domain.PubSub.SonarObservableBroker;
import it.unibo.radarSystem22.domain.PubSub.SonarObserverConcrete;
import it.unibo.radarSystem22.domain.concrete.SonarObservableConcrete;
import it.unibo.radarSystem22.domain.interfaces.ISonar;
import it.unibo.radarSystem22.domain.mock.SonarObservableMock;
import it.unibo.radarSystem22.domain.utils.BasicUtils;

public class TestSonarObservableMock {
	private static int DTESTING1=80;
	private static int DTESTING2=40;
	
	@Before
	public void up() {
		System.out.println("up");
	}
	
	@After
	public void down() {
		System.out.println("down");		
	}
	@Test 
	public void TestObservableMock() {
		ISonar observable=new SonarObservableMock();
		
		
		SonarObserverConcrete observer1=new SonarObserverConcrete();
		SonarObserverConcrete observer2=new SonarObserverConcrete();
		SonarObservableBroker broker=((SonarObservableMock) observable).getSonarObservableBroker();
		broker.subscribe(observer1);
		broker.subscribe(observer2);
		
		((SonarObservableMock) observable).setDistance(DTESTING1);
		
		assertTrue(observer1.getVal()==DTESTING1);
		assertTrue(observer2.getVal()==DTESTING1);
		
		((SonarObservableMock) observable).setDistance(DTESTING2);
		assertTrue(observer1.getVal()==DTESTING2);
		assertTrue(observer2.getVal()==DTESTING2);
		
		observable.activate();
		while(observable.isActive()) {BasicUtils.delay(1000);}
		
	}
}
