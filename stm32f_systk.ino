void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

static unsigned int *SYSTICK_REG_MAP = (unsigned int *)0xE000E010;
static unsigned int STK_CTRL_OFF = 0x00;
static unsigned int *STK_CTRL = (unsigned int *)(SYSTICK_REG_MAP + STK_CTRL_OFF);
static unsigned int *CLK_SOURCE = (unsigned int *)(SYSTICK_REG_MAP + STK_CTRL_OFF);
static unsigned int *TICKINT = (unsigned int *)(SYSTICK_REG_MAP + STK_CTRL_OFF);
static unsigned int *ENABLE = (unsigned int *)(SYSTICK_REG_MAP + STK_CTRL_OFF);


static unsigned int STK_LOAD_OFF = 0x04;
static unsigned int *STK_RELOAD_VAL = (unsigned int *)(SYSTICK_REG_MAP + STK_LOAD_OFF);

static unsigned int STK_VAL_OFF = 0x08;
static unsigned int *STK_VAL = (unsigned int *)(SYSTICK_REG_MAP + STK_VAL_OFF);

static unsigned int STK_CALIB_OFF = 0x0C;
static unsigned int *STK_CALIB = (unsigned int *)(SYSTICK_REG_MAP + STK_CALIB_OFF);

// returns 1 if timer counted to 0 since last time this was read
static int get_countflag()
{
  // 16th bit
  unsigned int count = !!((*STK_CTRL) & 0x00010000);
  return count;
}

#define STK_CLK_SRC_AHB_8 0
#define STK_CLK_SRC_AHB 1

static int set_clocksource()
{
  *CLK_SOURCE = 0x02;
}

static int get_clocksource()
{
  // bit 2
  return !!((*CLK_SOURCE) & 0x00000004);
}

static int get_tickint()
{
  return *TICKINT;
}

static int set_disable()
{
  *ENABLE = 0;

  return 0;
}

static int set_enable()
{
  *ENABLE = 1;

  return 0;
}

static int get_reload_value()
{
  unsigned int reload_val = *STK_RELOAD_VAL;

  return reload_val;
}

static int set_reload_value(int val)
{
  *STK_RELOAD_VAL = val;

  return 0;
}

static int get_current_val_reg()
{
  return *STK_VAL;
}

static int get_calib_value()
{
  return (*STK_CALIB) & 0x00ffffff;
}

void loop() {
  delay(100);
  // put your main code here, to run repeatedly:
  unsigned int STK_CTRL_COUNTFLAG  = get_countflag();
  //set_disable();
  set_clocksource();
  set_reload_value(99);
  //set_enable();
  Serial.print("count ");
  Serial.println(STK_CTRL_COUNTFLAG);
  Serial.print("clocksource ");
  Serial.println(get_clocksource());
  Serial.print("reload value ");
  Serial.println(get_reload_value());
  Serial.print("current value ");
  Serial.println(get_current_val_reg());
  Serial.print("calibration value ");
  Serial.println(get_calib_value());
}