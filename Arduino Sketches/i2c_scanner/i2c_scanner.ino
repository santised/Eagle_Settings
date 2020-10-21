#include <Wire.h>

void setup()
{
  Wire.begin();
  SerialUSB.begin(115200);

  while(!SerialUSB){};
  SerialUSB.println("\nI2C Scanner");
}


void loop()
{
  byte error, address;
  int nDevices;

  SerialUSB.println("Scanning...");
  Wire.begin();

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    SerialUSB.print("Address: ");
    SerialUSB.println(address);
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      SerialUSB.print("I2C device found at address 0x");
      if (address<16) 
        SerialUSB.print("0");
      SerialUSB.print(address,HEX);
      SerialUSB.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      SerialUSB.print("Unknow error at address 0x");
      if (address<16) 
        SerialUSB.print("0");
      SerialUSB.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    SerialUSB.println("No I2C devices found\n");
  else
    SerialUSB.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}
