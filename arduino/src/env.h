struct envValues
{
    float temperature;
    float humidity;
    float pressure;
};

extern struct envValues readEnv();
extern float readPressure();
extern void initEnv();