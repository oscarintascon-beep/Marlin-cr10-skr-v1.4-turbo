/*
Configuration.h preparado para CR-10 -> BTT SKR V1.4 Turbo
Basado en Marlin bugfix-2.1.x

BLTouch (clone)
TMC2208 en UART (por defecto)
Termistores stock Creality
NOTA: Ajusta NOZZLE_TO_PROBE_OFFSET y DEFAULT_AXIS_STEPS_PER_UNIT a tu impresora antes de flashear.
*/
#pragma once

#define DEFAULT_AXIS_STEPS_PER_UNIT { 80, 80, 400, 93 } // X, Y, Z, E
#define DEFAULT_MAX_FEEDRATE { 300, 300, 5, 25 }
#define DEFAULT_MAX_ACCELERATION { 3000,3000,100,10000 }

#define TEMP_SENSOR_0 1
#define TEMP_SENSOR_BED 1

#define BLTOUCH
#define NOZZLE_TO_PROBE_OFFSET { -44, -9, 1.2 }
#define Z_SAFE_HOMING
#define AUTO_BED_LEVELING_BILINEAR
#if ENABLED(AUTO_BED_LEVELING_BILINEAR)
#define GRID_MAX_POINTS_X 3
#endif

#define USE_XMIN_PLUG
#define USE_YMIN_PLUG
#define USE_ZMIN_PLUG

#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1

#define X_DRIVER_TYPE TMC2208
#define Y_DRIVER_TYPE TMC2208
#define Z_DRIVER_TYPE TMC2208
#define E0_DRIVER_TYPE TMC2208

#define Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN

#define BABYSTEPPING
#define BABYSTEP_MULTIPLICATOR 1

#define EEPROM_SETTINGS
