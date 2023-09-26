//Identificação da minha placa no aplicativo Blynk
#define BLYNK_TEMPLATE_ID           "TMPL2_EuvPVFo"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "5jm2KkC6KTGWNW87pDnT6IVm_p7knmtC"
#define BLYNK_PRINT Serial
#define engine 10 //definindo o pino do motor

//Bibliotecas necessárias
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Informações da minha rede
char ssid[] = "Franklin";
char pass[] = "12345678";

BlynkTimer timer;

// Acesso remoto do Blynk para Placa
BLYNK_WRITE(V0)
{
  // Convertendo o Parâmetro recebido por V0 em INT e atribuindo a variável 'value' 
  int value = param.asInt();
  digitalWrite(engine, value); //quando o parâmetro enviado por V0 for '0', o motor está desligado, quando V0 for '1', o motor estará funcionando

  
  Blynk.virtualWrite(V1, value);
}

BLYNK_CONNECTED()
{
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// Ação da placa para o aplicativo Blynk
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  Serial.begin(115200);
  pinMode(engine, OUTPUT); // indicando que o pino do motor, é um pino de SAÍDA
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
