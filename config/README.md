Configuration Guide
===================

What is Configuration.h and its contents?
------------------------------------------
Configuration.h is device-specific settings list.

Supported Preproc.
------------------

| List | Type | Desc |
| ---- | ---- | ---- |
| DIVIDER_FACTOR | Float/Integer | Real divider value from raw sysfs value. |
| THERM_DIVIDER_FACTOR | Float/Integer | Real divider value from raw sysfs value |
| IS_RASPI | NONE | Definer for support Raspberry PI |

Example Configuration.h for Raspberry Pi
----------------------------------------
```
#define DIVIDER_FACTOR 1000000.0
#define THERM_DIVIDER_FACTOR 1000.0

#define IS_RASPI
```