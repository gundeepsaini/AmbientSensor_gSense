

/*--------------------------------------------------------*/


char BlynkAuth[] = SECRET_BLYNK_AUTH2;



/*--------------------------------------------------------*/


void Blynk_Config()
{
  Blynk.config(BlynkAuth);
  while (Blynk.connect(1000) == false);  
  
}


void Blynk_pushDataToGraph()
{
  Blynk.virtualWrite(V1, Temperature);
  Blynk.virtualWrite(V2, Humidity);
  Blynk.virtualWrite(V5, lux);
}


/**********************************************************/


BLYNK_WRITE(V0)
{

}


BLYNK_READ(V1)
{
  Blynk.virtualWrite(V1, Temperature);
}

BLYNK_READ(V2)
{
  Blynk.virtualWrite(V2, Humidity);
}

BLYNK_READ(V3)
{
  Blynk.virtualWrite(V3, Pressure);
}

BLYNK_READ(V4)
{
  Blynk.virtualWrite(V4, Altitude);
}

BLYNK_READ(V5)
{
  Blynk.virtualWrite(V5, lux);
}

BLYNK_READ(V6)
{
  Blynk.virtualWrite(V6, Noise);
}

BLYNK_READ(V7)
{
  Blynk.virtualWrite(V7, PPM_LPG);
}
