package it.unibo.radarSystem22.main;

import radarPojo.radarSupport;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;


public class RadarUsageMain {
  @SuppressWarnings("unused")
public void doJob() {
  
   
   try {
   ServerSocket serverSocket = new ServerSocket(6666);
   Socket clientSocket  = serverSocket.accept();
    radarSupport.setUpRadarGui();
    while(true)
    {
     BufferedReader distance = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));     
    
     int distanza = distance.read();
     if(distanza<0) {
    	 break;
     }
    
     System.out.println("Ho ricevuto una distanza "+ distanza+" socket : "+clientSocket);
     
      radarSupport.update(""+distanza , "0");
    }
  } catch (Exception e) {
   // TODO Auto-generated catch block
   e.printStackTrace();
  }
   
   System.out.println("FINE");
  
  
  }
 public static void main(String[] args) {
  System.out.println("stadrt");
  new RadarUsageMain().doJob();
 }
}