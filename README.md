# ESP32s-tft-1.4-Inch
Smart Band
---------------------------------------------------------------------------------------------------------------------------------

File List

-Data Sheet ข้อมูลอุปกรณ์ต่างๆ

-Icon.h ภาพ R5G6B5 16bit สำหรับแสดงบนจอ tft LCD

-Data_tft โปรแกรมสำหรับอัพโหลดค่าต่างๆไปแสดงบน LCD

-tft_1.4_st7735 โปรแกรมสำหรับอัพโหลดภาพต่างๆแสดงบน LCD

-Schrematic and Footprint เปิดด้วยเว็บ EasyEDA สำหรับลายวงจร PCB

-Libraly มี 3 ตัว

            Adafruit_GFX_Library ใช้สำหรับภาพสีบนจอ LCD
    
            Adafruit-ST7735-Library-master ใช้สำหรับจอ LCD ที่ Drive ด้วย ST7735
    
            SparkFun_MAX3010x_Sensor_Library-master สำหรับ Sensor HR SPO2 Max30102
            
---------------------------------------------------------------------------------------------------------------------------------

Circuit on device

-3.7V battery Charger Circuit

-Regulator 3.3V Circuit for ESP32s

-Regulator 1.8V Circuit for Max30102 Sensor

---------------------------------------------------------------------------------------------------------------------------------

List Component

-1X Socket Micro USB Type B SMT

-1X BU18TD สำหรับแปลงไฟ 3.3V เป็น 1.8V

-1X BU33TD สำหรับแปลงไฟ 5V เป็น 3.3V

-1X Battery LiPo 3.7V 370mAh 

-1X ESP32s microcontroller

-1X Max30102 Heartrate and Oxygen blood Sensor

-1X TC4056A Charger battery

-1X LCD tft 1.4 Inch Driver ST7735

-Capasistor
  
            3X 10 uF
    
            1X 4.7 uF
    
            4X 0.47 uF
    
            2X 0.1 uF

-LED

            1X LED SMD GREEN

            1X LED SMD RED
            
            1X LED SMD Blue

-Resistor
    
            1X 1.2 kOhm
    
            2X 1 kOhm
    
            1X 400 mOhm
    
---------------------------------------------------------------------------------------------------------------------------------

วงจรที่ต้องปรับปรุงแก้ไขเพิ่มเติม

-เพิ่มสวิตซ์เปิด-ปิด หรือสวิตซ์รีเซ็ต

-เพิ่มวงจรสำหรับเสียบ Micro USB เพื่อเขียนโปรแกรมบนอุปกรณ์ได้เลย

-เพิ่ม Temperator Sensor และ Blood Pressure Sensor
