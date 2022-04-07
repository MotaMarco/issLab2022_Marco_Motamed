package it.unibo.radarSystem22.domain.models;

import it.unibo.radarSystem22.domain.Distance;
import it.unibo.radarSystem22.domain.PubSub.SonarObservableBroker;
import it.unibo.radarSystem22.domain.concrete.SonarConcrete;
import it.unibo.radarSystem22.domain.concrete.SonarObservableConcrete;
import it.unibo.radarSystem22.domain.interfaces.IDistance;
import it.unibo.radarSystem22.domain.interfaces.ISonar;
import it.unibo.radarSystem22.domain.mock.SonarMock;
import it.unibo.radarSystem22.domain.mock.SonarObservableMock;
import it.unibo.radarSystem22.domain.utils.ColorsOut;
import it.unibo.radarSystem22.domain.utils.DomainSystemConfig;

public abstract class SonarObservableModel implements ISonar {
	protected  IDistance curVal = new Distance(90);	 
	protected boolean stopped   = true;
	protected  SonarObservableBroker broker;
	 	
		public SonarObservableBroker getSonarObservableBroker() {
			return broker;
		}
		
		public static ISonar create() {
			if( DomainSystemConfig.simulation )  return createSonarMock();
			else  return createSonarConcrete();		
		}

		public static ISonar createSonarMock() {
			ColorsOut.out("createSonarMock", ColorsOut.BLUE);
			return new SonarObservableMock();
		}	
		public static ISonar createSonarConcrete() {
			ColorsOut.out("createSonarConcrete", ColorsOut.BLUE);
			return new SonarObservableConcrete();
		}	
		
		protected SonarObservableModel() {//hidden costructor, to force setup
			ColorsOut.out("SonarModel | calling (specialized) sonarSetUp ", ColorsOut.BLUE );
			sonarSetUp();  
		}
		
		protected void updateDistance( int d ) {
			curVal = new Distance( d );
			broker.publish(d);
			ColorsOut.out("SonarModel | updateDistance "+ d, ColorsOut.BLUE);
		}	

		protected abstract void sonarSetUp() ;
	 	protected abstract void sonarProduce() ;

		@Override
		public boolean isActive() {
			//ColorsOut.out("SonarModel | isActive "+ (! stopped), ColorsOut.GREEN);
			return ! stopped;
		}
		
		@Override
		public IDistance getDistance() {
			return curVal;
		}
		
		@Override
		public void activate() {
			curVal = new Distance( 90 );
	 		ColorsOut.out("SonarModel | activate" );
			stopped = false;
			new Thread() {
				public void run() {
					while( ! stopped  ) {
						//Colors.out("SonarModel | call produce", Colors.GREEN);
						sonarProduce(  );
						//Utils.delay(RadarSystemConfig.sonarDelay);
					}
					ColorsOut.out("SonarModel | ENDS" );
			    }
			}.start();
		}
	 	
		@Override
		public void deactivate() {
			ColorsOut.out("SonarModel | deactivate", ColorsOut.BgYellow );
			stopped = true;
		}


}
