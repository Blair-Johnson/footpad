# Build Notes
-esp-idf version 5.3.2
-esp-idf works best when installed in its default location in home.
-If you need to nuke your esp-idf environment delete `~/.espressif/`.
-You will need to source `export.sh` in esp-idf source each time you want to use esp-idf.
-Installing esp32 support in arduino ide will overwrite `~/.espressif/` by default.
-Use esptool.py (`pip install esptool`) to erase-flash if you need to reset board state.
-Add user to group that owns device for persistent access across disconnects `sudo usermod -aG groupname yourusername`. You will need to logout and log back in for this to take effect.

For arduino component:
```
idf.py add-dependency "espressif/arduino-esp32^3.0.2"
```
see [guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/esp-idf_component.html) for more info.

For adding arduino libraries as components:
1. Clone library into components directory
2. Add a CMakeLists.txt to the library following this template:
```
idf_component_register(SRCS "new_library.cpp" "another_source.c"
                      INCLUDE_DIRS "."
                      REQUIRES arduino-esp32
                      )
```

If you need to modify compile options for components, there are instructions in the [espressif build system docs](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html). I never got this to work and had to manually modify the arduino library I was using to get it to compile.


Arduinos typically have hardware limitations on which pins support I2C, so the arduino wire library assumes specific pins. The espressif version adds the `Wire.setPins(sda, scl);` method.
