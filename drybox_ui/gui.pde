/* =========================================================
 * ====                   WARNING                        ===
 * =========================================================
 * The code in this tab has been generated from the GUI form
 * designer and care should be taken when editing this file.
 * Only add/edit code inside the event handlers i.e. only
 * use lines between the matching comment tags. e.g.

 void myBtnEvents(GButton button) { //_CODE_:button1:12356:
     // It is safe to enter your event code here  
 } //_CODE_:button1:12356:
 
 * Do not rename this tab!
 * =========================================================
 */

public void drop_arduino_serial_click(GDropList source, GEvent event) { //_CODE_:drop_arduino_serial:314369:
  //println("drop_serial - GDropList >> GEvent." + event + " @ " + millis());
  
  ARDUINO_COM_PORT = source.getSelectedIndex();
  ARDUINO_COM_PORT_NAME = Serial.list()[ARDUINO_COM_PORT];

} //_CODE_:drop_arduino_serial:314369:

public void bttn_serial_arduino_open_click(GButton source, GEvent event) { //_CODE_:bttn_serial_arduino_open:612085:
  //println("bttn_serial_open - GButton >> GEvent." + event + " @ " + millis());
  ARDUINO_COM_PORT_NAME = Serial.list()[ARDUINO_COM_PORT];
  arduino.open(ARDUINO_COM_PORT_NAME);
  
} //_CODE_:bttn_serial_arduino_open:612085:

public void bttn_flush_clicked(GButton source, GEvent event) { //_CODE_:bttn_flush:640586:
  //println("bttn_flush - GButton >> GEvent." + event + " @ " + millis());
  arduino.close();
  exit();
} //_CODE_:bttn_flush:640586:

public void txtbox_series_results_change(GTextArea source, GEvent event) { //_CODE_:txtbox_series_results:644449:
  //println("txtbox_series_results - GTextArea >> GEvent." + event + " @ " + millis());
} //_CODE_:txtbox_series_results:644449:



// Create all the GUI controls. 
// autogenerated do not edit
public void createGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setMouseOverEnabled(false);
  surface.setTitle("Sketch Window");
  drop_arduino_serial = new GDropList(this, 100, 70, 110, 100, 4, 10);
  drop_arduino_serial.setItems(loadStrings("list_314369"), 0);
  drop_arduino_serial.addEventHandler(this, "drop_arduino_serial_click");
  bttn_serial_arduino_open = new GButton(this, 220, 70, 80, 20);
  bttn_serial_arduino_open.setText("Connect");
  bttn_serial_arduino_open.addEventHandler(this, "bttn_serial_arduino_open_click");
  lbl_heading = new GLabel(this, 10, 10, 204, 40);
  lbl_heading.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  lbl_heading.setText("Dry Box Recorder");
  lbl_heading.setOpaque(false);
  bttn_flush = new GButton(this, 225, 18, 80, 30);
  bttn_flush.setText("FLUSH/EXIT");
  bttn_flush.addEventHandler(this, "bttn_flush_clicked");
  lbl_arduino = new GLabel(this, 10, 70, 80, 20);
  lbl_arduino.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  lbl_arduino.setText("Arduino");
  lbl_arduino.setOpaque(false);
  txtbox_series_results = new GTextArea(this, 7, 113, 584, 240, G4P.SCROLLBARS_NONE);
  txtbox_series_results.setOpaque(true);
  txtbox_series_results.addEventHandler(this, "txtbox_series_results_change");
}

// Variable declarations 
// autogenerated do not edit
GDropList drop_arduino_serial; 
GButton bttn_serial_arduino_open; 
GLabel lbl_heading; 
GButton bttn_flush; 
GLabel lbl_arduino; 
GTextArea txtbox_series_results; 
