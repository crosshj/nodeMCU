
if not exist ".\arduino-1.8.4\portable\packages\esp8266\hardware\esp8266\2.3.0\tools\sdk\ld" mkdir .\arduino-1.8.4\portable\packages\esp8266\hardware\esp8266\2.3.0\tools\sdk\ld
COPY ".\Sonoff-Tasmota-5.8.0\arduino\version 2.3.0\tools\sdk\ld\eagle.flash.1m0.ld" ".\arduino-1.8.4\portable\packages\esp8266\hardware\esp8266\2.3.0\tools\sdk\ld\eagle.flash.1m0.ld"

if not exist ".\arduino-1.8.4\portable\packages\esp8266\hardware\esp8266\2.3.0" mkdir .\arduino-1.8.4\portable\packages\esp8266\hardware\esp8266\2.3.0
COPY ".\Sonoff-Tasmota-5.8.0\arduino\version 2.3.0\boards.txt" ".\arduino-1.8.4\portable\packages\esp8266\hardware\esp8266\2.3.0\boards.txt"

if not exist ".\arduino-1.8.4\portable\sketchbook\libraries" mkdir .\arduino-1.8.4\portable\sketchbook\libraries
XCOPY /s ".\Sonoff-Tasmota-5.8.0\lib" ".\arduino-1.8.4\portable\sketchbook\libraries\"

if not exist ".\arduino-1.8.4\portable\sketchbook\sonoff" mkdir .\arduino-1.8.4\portable\sketchbook\sonoff
XCOPY /s ".\Sonoff-Tasmota-5.8.0\sonoff" ".\arduino-1.8.4\portable\sketchbook\sonoff\"

pause