package it.unibo.radarSystem22.domain;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import it.unibo.radarSystem22.domain.intefaces.ILed;
import it.unibo.radarSystem22.domain.intefaces.ISonar;
import it.unibo.radarSystem22.domain.mock.LedMockMarco;
import it.unibo.radarSystem22.domain.mock.SonarMock;

public class TestSonarMock {
	@Before
	public void up() {
		System.out.println("the test is up");
	}
	
	@After
	public void down() {
		System.out.println("the test is down");
	}
	
	@Test
	public void testLedMockOn() throws InterruptedException {
		System.out.println("testSonarMock");
		ISonar sonar=new SonarMock();
		sonar.activate();
		for(int i=90;i>=0;i--) {
			assertTrue(sonar.getDistance().getVal()==i);
			Thread.sleep(250);
		}
		
		
	}

}
