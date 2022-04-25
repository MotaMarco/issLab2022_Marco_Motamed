package unibo.actor22.local;

 
import it.unibo.kactor.IApplMessage;
import it.unibo.radarSystem22.domain.utils.BasicUtils;
import it.unibo.radarSystem22.domain.utils.DomainSystemConfig;
import unibo.actor22.Qak22Util;
import unibo.actor22.common.ApplData;
import unibo.actor22.common.LedActor;
import unibo.actor22.common.SonarActor;
import unibo.actor22comm.utils.ColorsOut;
import unibo.actor22comm.utils.CommSystemConfig;
import unibo.actor22comm.utils.CommUtils; 
 
/*
 * Sistema che usa led come attore locale
 */
 public class UsingSonarNoControllerOnPc {
 	
 private SonarActor sonar;
 private IApplMessage getState;
 
	public void doJob() {
		ColorsOut.outappl("UsingSonarNoControllerOnPc | Start", ColorsOut.BLUE);
		configure();
		BasicUtils.aboutThreads("Before execute - ");
		//BasicUtils.waitTheUser();
		execute();
		terminate();
	}
	
	protected void configure() {
		DomainSystemConfig.simulation   = true;			
		DomainSystemConfig.ledGui       = true;			
		DomainSystemConfig.tracing      = false;			
		
		CommSystemConfig.tracing        = true;
		
		sonar = new SonarActor( ApplData.sonarName );
 		
		//getState = CommUtils.buildRequest("main",  "ask", ApplData.reqSonarDistance, ApplData.sonarName); 
   	}
	
	
	//Chiede lo stato del sonar per 2 volte
	protected void execute() {
		ColorsOut.outappl("UsingSonarNoControllerOnPc | execute", ColorsOut.MAGENTA);
		for( int i=1; i<=2; i++) {
// Inviare una request richiede un attore capace di ricevere la reply	 	    
	 	    Qak22Util.sendAMsg(ApplData.stateSonar);
	 	    //led.elabMsg(getState);   //Richiesta asincrona. Reply inviata a main
	 	    CommUtils.delay(500);
		}
 	} 

	public void terminate() {
		BasicUtils.aboutThreads("Before exit - ");
		System.exit(0);
	}
	
	public static void main( String[] args) {
		BasicUtils.aboutThreads("Before start - ");
		new UsingSonarNoControllerOnPc().doJob();
 		BasicUtils.aboutThreads("Before end - ");
	}

}

/*
 * Threads: main + Actor22 + LedGui
 */
