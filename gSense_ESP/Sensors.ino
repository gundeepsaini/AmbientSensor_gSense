

void DisplayValues_Serial()
{
  Serial.println("----------------------------------------");
  Serial.print("Temp\t\t:");
  Serial.print(Temperature);
  Serial.println("ºC");

  Serial.print("Humidity\t:");
  Serial.print(Humidity, 1);
  Serial.print("%  ");
  Serial.print(Temperature_DHT11, 1);
  Serial.println("ºC");

  Serial.print("Light\t\t:");
  Serial.print(lux);
  Serial.println(" lx");

  Serial.print("Pressure\t:");
  Serial.print(Pressure);
  Serial.print("mBar  ");
  Serial.print(Altitude);
  Serial.println(" meters");

  Serial.print("Noise\t\t:");
  Serial.print(Noise);
  Serial.println("dB");

  Serial.print("PPM\t\t:");
  Serial.print(PPM_LPG);
  Serial.println("ppm");

}


void Config_TempSensor_DS18B20()
{
  uint8_t address[] = {40, 250, 31, 218, 4, 0, 0, 52};
  uint8_t response = 0;

  response = ds.select(address);

  if(!response) 
  {
    Serial.println("Device not found!");
  }
}



void Read_TempSensor()
{ 
  Temperature = ds.getTempC();
}


void Read_LightSensor()
{
  lux = LightMeter.readLightLevel();
}

void Read_Humidity()
{
  Humidity = DHT.getHumidity();
  Temperature_DHT11 = DHT.getTemperature();
}



void Read_Pressure()
{
  char status;
  double T,P,p0,a;
  status = BMP180.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);
    status = BMP180.getTemperature(T);
    if (status != 0)
    {
      status = BMP180.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = BMP180.getPressure(P,T);
        if (status != 0)
        {
          Pressure = P;
          Altitude = BMP180.altitude(P,SeaLevel_Pressure);
        }
      }
    }
  }
}

void Read_Noise()
{
  // Temporary value - replace after communication with Atmega328
  Noise = random(20,40);
}

void Read_LPG_PPM()
{
  // Temporary value - replace after communication with Atmega328
  PPM_LPG = random(0,2);
}
