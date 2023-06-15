# smstools3 with CDMA support

Based on [smstools3-3.1.21](http://smstools3.kekekasvi.com), add sending CDMA message feature.

## Require

 * GCC
 * NodeJS

## Instll

 * `Make install`

## Config

In smsd.conf, you shoud change modem mode to `cdma`:

```
...

[GSM1]
device = /dev/ttyS0
mode=cdma
incoming = yes
baudrate=115200
#smsc=+8613800250500
#pin = 1111
memory_start = 0
text_is_pdu_key=123456789

...

```

## Limit

 * CDMA SMS send only, can not decode SMS in CDMA format.
 * Can only encode alphabet characters.
