package it.unibo.radarSystem22.domain.mock;

import it.unibo.radarSystem22.domain.Distance;
import it.unibo.radarSystem22.domain.intefaces.IDistance;
import it.unibo.radarSystem22.domain.intefaces.ISonar;

public class SonarMock implements ISonar{
	private boolean stopped;
	private long time;
	private final int generateData=90;
	@Override
	public void activate() {
		// TODO Auto-generated method stub
		stopped=false;
		time=System.currentTimeMillis();
	}

	@Override
	public void deactivate() {
		// TODO Auto-generated method stub
		stopped=true;
		time=-1;
	}

	@Override
	public IDistance getDistance() {
		Distance distance=new Distance(-1);
		if(stopped==false) {
			long request=System.currentTimeMillis();
			long diff=request-time;
			long numVolte=(long) (diff/250);
			System.out.println(numVolte);
			int distanza=(generateData-(int)numVolte);
			distance=new Distance(distanza);
			return distance;
		}
		return distance;
	}

	@Override
	public boolean isActive() {
		// TODO Auto-generated method stub
		return ! stopped;
	}

}
