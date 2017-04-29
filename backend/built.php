<?php
if (!empty($_POST)){
		
	$data = $_POST['id'];
	if (($fp = fopen("test/test.ino", "w"))){
	    fwrite($fp,$data);
	    fclose($fp);

		$input = '"C:\Program Files (x86)\Arduino\arduino-builder" -dump-prefs -logger=machine -hardware "C:\Program Files (x86)\Arduino\hardware" -hardware C:\Users\Karim\AppData\Local\Arduino15\packages -tools "C:\Program Files (x86)\Arduino\tools-builder" -tools "C:\Program Files (x86)\Arduino\hardware\tools\avr" -tools C:\Users\Karim\AppData\Local\Arduino15\packages -built-in-libraries "C:\Program Files (x86)\Arduino\libraries" -libraries C:\Users\Karim\Documents\Arduino\libraries -fqbn=esp8266:esp8266:nodemcuv2:CpuFrequency=80,UploadSpeed=115200,FlashSize=4M1M -ide-version=10801 -build-path G:\Application\EasyPHP-12.1\www\arduino\mine\arduinoBuilt -warnings=none -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.esptool.path=C:\Users\Karim\AppData\Local\Arduino15\packages\esp8266\tools\esptool\0.4.9 -prefs=runtime.tools.xtensa-lx106-elf-gcc.path=C:\Users\Karim\AppData\Local\Arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\1.20.0-26-gb404fb9-2 -prefs=runtime.tools.mkspiffs.path=C:\Users\Karim\AppData\Local\Arduino15\packages\esp8266\tools\mkspiffs\0.1.2 G:\Application\EasyPHP-12.1\www\arduino\mine\test\test.ino"';


		$output = shell_exec($input);


		$input ='"C:\Program Files (x86)\Arduino\arduino-builder" -compile -logger=machine -hardware "C:\Program Files (x86)\Arduino\hardware" -hardware C:\Users\Karim\AppData\Local\Arduino15\packages -tools "C:\Program Files (x86)\Arduino\tools-builder" -tools "C:\Program Files (x86)\Arduino\hardware\tools\avr" -tools C:\Users\Karim\AppData\Local\Arduino15\packages -built-in-libraries "C:\Program Files (x86)\Arduino\libraries" -libraries C:\Users\Karim\Documents\Arduino\libraries -fqbn=esp8266:esp8266:nodemcuv2:CpuFrequency=80,UploadSpeed=115200,FlashSize=4M1M -ide-version=10801 -build-path G:\Application\EasyPHP-12.1\www\arduino\mine\arduinoBuilt -warnings=none -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.esptool.path=C:\Users\Karim\AppData\Local\Arduino15\packages\esp8266\tools\esptool\0.4.9 -prefs=runtime.tools.xtensa-lx106-elf-gcc.path=C:\Users\Karim\AppData\Local\Arduino15\packages\esp8266\tools\xtensa-lx106-elf-gcc\1.20.0-26-gb404fb9-2 -prefs=runtime.tools.mkspiffs.path=C:\Users\Karim\AppData\Local\Arduino15\packages\esp8266\tools\mkspiffs\0.1.2 G:\Application\EasyPHP-12.1\www\arduino\mine\test\test.ino';


		$output = shell_exec($input);
	}
}
?>


