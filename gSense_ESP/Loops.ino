

void Always_loop()
{
  	OTA_Check();
}


void Fast_Loop()
{
    Blynk.run();
    server.handleClient();
    MQTT_loop();   
}



void Mid1_Loop()
{
	Read_TempSensor();
	Read_LightSensor();
	Read_Humidity();
	Read_Pressure();

}



void Mid2_Loop()
{
  DisplayValues_Serial();
}



void Slow_Loop()
{
    Read_Noise();
    Read_LPG_PPM();  
  	MQTT_publish();

    RunOnce_30mins();
}


void VerySlow_Loop()
{

  Blynk_pushDataToGraph();
}



void RunOnce_30mins()
{
	if(millis()/1000 - lastrun_30mins > 30 * 60 || lastrun_30mins == 0)
	{
    lastrun_30mins = millis()/1000;

    Time_NTP_Update(); 
	}
}