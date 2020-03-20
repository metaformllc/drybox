import java.util.Arrays;
import java.util.Queue;
import java.util.List;
import java.util.LinkedList;

public class Arduino
{
  private PrintWriter output;
  
  boolean isEnabled = true;

  PApplet parent;
  Serial com;
  String port;

  Arduino(PApplet p) {
    this.parent = p;    
    //output.println( UtilityMethods.createLine("temp", "humidity") );
  }

  public boolean open(String port)
  {
    try {
      println("Opening Arduino port: " + port);
      com = new Serial(this.parent, port, 1000000);
      return true;
    }
    catch(Exception e) {
      return false;
    }
  }

  public void update()
  {
    if ( com != null && com.available() > 0) 
    {  // If data is available,
      if(output == null){
        String timestamp = UtilityMethods.getFormattedYMD() + "_" + UtilityMethods.getFormattedTime(false);
        output = createWriter(config.ROOT_DIR + "/drybox_"+ timestamp + ".csv");
        println("Created: " + config.ROOT_DIR + "/drybox_"+ timestamp + ".csv");
      }
      String val = trim(com.readStringUntil('\n'));         // read it and store it in val
      if (val != null) {
        try {
          output.println( val );
          txtbox_series_results.setText(val);
        }
        catch(Exception e) {
        }
      }
    }
  }
  
  public void close()
  {
    com.stop();
    if (output != null) {
      output.flush(); // Writes the remaining data to the file
      output.close();
    }
  }
}
