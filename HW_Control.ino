bool SensorRead()
{
  return (digitalRead(Sensor) && digitalRead(Sensor));
}
void LampControl(bool lamp1, bool lamp2, bool lamp3)
{
  digitalWrite(pilot_lamp_rad, lamp1);
  digitalWrite(pilot_lamp_yellow, lamp2);
  digitalWrite(pilot_lamp_green, lamp3);
}
void PumpControl()
{
  while (PumeStep==0)
  {
    if(((millis() - last_time) > SprayRelay)<(SprayRelay+SprayTime)) 
    {
      digitalWrite(Pump, HIGH);
      DebugSerial.print(" Pump On ");
    }
    else if ((millis() - last_time) > (SprayRelay+SprayTime))
    {
      last_time = millis();
      PumeStep = 1 ; 
      digitalWrite(Pump, LOW);
      DebugSerial.print(" Pump Off ");
    }
  }

}