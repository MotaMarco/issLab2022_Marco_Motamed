package unibo.wenvUsage22.annot.walker;

 
import unibo.actor22comm.utils.ColorsOut;

public class GuardContinueWork {
	protected static int vn ;
  	
	public static void setValue( int n ) {
		vn = n;
	}
	public static boolean checkValue(   ) {
		return vn < 40 ;
	}
 	public boolean eval( ) {
 		boolean b = checkValue();
 		ColorsOut.outappl("GuardContinueOfWork eval="+b , ColorsOut.CYAN);
 		return b;
	}

}
