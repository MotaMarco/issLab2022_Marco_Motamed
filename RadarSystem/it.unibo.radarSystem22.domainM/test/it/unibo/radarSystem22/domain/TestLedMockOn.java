package it.unibo.radarSystem22.domain;

import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import it.unibo.radarSystem22.domain.intefaces.ILed;
import it.unibo.radarSystem22.domain.mock.LedMockMarco;

public class TestLedMockOn {

	@Before
	public void up() {
		System.out.println("the test is up");
	}
	
	@After
	public void down() {
		System.out.println("the test is down");
	}
	
	@Test
	public void testLedMockOn() {
		System.out.println("testLedMockOn");
		ILed led=new LedMockMarco();
		led.turnOn();
		assertTrue(led.getState());
	}

}
