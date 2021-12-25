Overly simplistic backlight control program
-------------------------------------------

This small program is designed to control the backlight on my Lenovo laptop. It's hard
coded to work specifically with the backlight on that device and no other. If it happens
that it works on yours then that's great. Of course you can edit the source code to point
to another device if you like.

All it does is take a brightness as a percentage (or a +/- adjustment to the current
brightness) and convert that to an actual brightness value, which it then places into
`/sys/class/backlight/intel_backlight/brightness`. It runs setuid root so that a normal
user can adjust the backlight brightess.

I wrote this specifically to control the backlight from a keyboard shortcut in Sway:

```
bindsym XF86MonBrightnessUp exec backlight +10
bindsym XF86MonBrightnessDown exec backlight -10
```
