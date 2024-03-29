
/*
	HTML Page, test here: https://www.w3schools.com/html/tryit.asp?filename=tryhtml_table_intro
	Convert here: http://davidjwatts.com/youtube/esp8266/esp-convertHTM.html#
*/




void Prep_webpage1()
{

    // Get time
  String timeStr;
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  // Convert to HH:MM:SS
  char locTime[11];
  sprintf(locTime, " %02d:%02d:%02d ", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  char locdate[11];
  sprintf(locdate, " %d.%02d.%02d ", timeinfo.tm_year-100, timeinfo.tm_mon+1, timeinfo.tm_mday);
  timeStr = String(locdate) + String(locTime);

    // !!! ELements that don't change !!!
  String page_head ="<!DOCTYPE html><html><head><style>td,th{ border: 1px solid #dddddd; text-align: left; padding: 8px;} tr:nth-child(even){background-color: #dddddd;}</style></head>";
  String body_start = "<body>";
  String body_table_start = String("<h2>") + DeviceHostName + String("</h2><h4>Updated: ") + timeStr + String("</h4><table>");
  String body_table_row00 ="<tr><th>#</th><th>Description</th><th>Value</th><th>Unit</th></tr>";
  String body_end = "</table></body></html>";

  // Start chaning here onwards.....
  String body_table_row01 =String("<tr><td>01</td><td>Temperature</td><td>")          + String(Temperature)       + String("</td><td>&#8451;</td></tr>");
  String body_table_row02 =String("<tr><td>02</td><td>Humidity</td><td>")             + String(Humidity)          + String("</td><td>%</td></tr>");
  String body_table_row03 =String("<tr><td>03</td><td>Temperature DHT11</td><td>")    + String(Temperature_DHT11) + String("</td><td>&#8451;</td></tr>");
  String body_table_row04 =String("<tr><td>04</td><td>Light</td><td>")                + String(lux)               + String("</td><td>lx</td></tr>");
  String body_table_row05 =String("<tr><td>05</td><td>Pressure</td><td>")             + String(Pressure)          + String("</td><td>mbar</td></tr>");
  String body_table_row06 =String("<tr><td>06</td><td>Altitude</td><td>")             + String(Altitude)          + String("</td><td>m</td></tr>");
  String body_table_row07 =String("<tr><td>07</td><td>Noise</td><td>")                + String(Noise)             + String("</td><td>dB</td></tr>");
  String body_table_row08 =String("<tr><td>08</td><td>PPM</td><td>")                  + String(PPM_LPG)           + String("</td><td>ppm</td></tr>");
  
  
  webpage = page_head +
  			 body_start +
  			 body_table_start +
  			 body_table_row00 +
  			 body_table_row01 +
  			 body_table_row02 +
         body_table_row03 +
         body_table_row04 +
         body_table_row05 +
         body_table_row06 +
         body_table_row07 +
         body_table_row08 +
  			 body_end; 
         
}


/*

Source webpage:

<!DOCTYPE html>
<html>
<head>
<style>
td,th{
  border: 1px solid #dddddd;
  text-align: left;
  padding: 8px;
}
tr:nth-child(even){
  background-color: #dddddd;
}
</style>
</head>
<body>

<h2>Device Name</h2>
<h4>Updated: Time</h4>
<table>
  <tr>
    <th>#</th>
    <th>Description</th>
    <th>Value</th>
    <th>Unit</th>
  </tr>
  <tr>
    <td>1</td>
    <td>Voltage</td>
    <td>231.1</td>
    <td>V</td>
  </tr>
  <tr>
    <td>2</td>
    <td>Current</td>
    <td>0.21</td>
    <td>A</td>
  </tr>
  <tr>
    <td>3</td>
    <td>Power</td>
    <td>3212</td>
    <td>W</td>
  </tr>
  <tr>
    <td>4</td>
    <td>Energy</td>
    <td>241</td>
    <td>kWh</td>
  </tr>
  <tr>
    <td>5</td>
    <td>Frequeny</td>
    <td>50</td>
    <td>hz</td>
  </tr>
  
</table>

</body>
</html>





*/
