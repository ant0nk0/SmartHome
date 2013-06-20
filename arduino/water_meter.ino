int val;

const byte COLD_WATER_METER = 0;
const byte HOT_WATER_METER = 1;
const byte FILTERED_WATER_METER = 2;

struct WaterMeter
{
  byte m_Type;
  int m_AnalogPin;
  boolean m_HasImpulse;
};

WaterMeter waterMeters[1] = 
{
    {COLD_WATER_METER, A0, false},
    //{HOT_WATER_METER, A1, false},
    //{FILTERED_WATER_METER, A2, false}
};

void setup()
{ 
  // Настраиваем последовательный интерфейс, для вывода информации 
  Serial.begin(38400);
  
  // analog reference of 5 volts
  analogReference(DEFAULT);
}

void loop()
{
  for (int i = 0; i < sizeof(waterMeters) / sizeof(waterMeters[0]); ++i)
  {
    WaterMeter& waterMeter = waterMeters[i];
    
    val = analogRead(waterMeter.m_AnalogPin);
    if (val < 905 && val > 898) // impulse
    {
      if (!waterMeter.m_HasImpulse)
      {
        waterMeter.m_HasImpulse = true;
        Serial.println(waterMeter.m_Type);
      }
    }
    else
    {
      waterMeter.m_HasImpulse = false;
    }
    
    delay(200);
  }
}
