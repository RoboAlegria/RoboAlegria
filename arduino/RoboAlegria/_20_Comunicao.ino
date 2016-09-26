//***********
//Comunicação
//***********

//enviar dados para o ESP8266
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available()) //enquanto o ESP8266 tiver dados disponíveis na sua saída
    {
      char c = esp8266.read(); //ler e armazenar os caracteres recebidos
      response += c;
    }
  }
  if (debug) //se estiver em modo DEBUG, imprimir a resposta
  {
    Serial.print(response);
  }
  return response;
}
