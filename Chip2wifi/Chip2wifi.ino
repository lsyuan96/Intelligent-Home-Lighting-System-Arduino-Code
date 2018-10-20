if(wifiSerial.available()>0){ 
   String message = readWifiSerialMessage(); 
   if(find(message,"esp8266:")){ 
      String result = sendToWifi(message.substring(8,message.length()),responseTime,DEBUG); 
     if(find(result,"OK")) 
       sendData("\n"+result); 
     else 
       sendData("\nErrRead");               //At command ERROR CODE for Failed Executing statement 
   }else 
   if(find(message,"HELLO")){  //receives HELLO from wifi 
       sendData("\\nHI!");    //arduino says HI 
   }else if(find(message,"LEDON")){ 
     digitalWrite(13,HIGH); 
   }else if(find(message,"LEDOFF")){ 
     digitalWrite(13,LOW); 
   } 
   else{ 
     sendData("\nErrRead");                 //Command ERROR CODE for UNABLE TO READ 
   } 
 } 
