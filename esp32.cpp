#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
// leds
int led1 = 13;
int led2 = 26;
int led3 = 16;
int led4 = 15;
int led5 = 12;
int led6 = 25;
int led7 = 17;
int led8 = 2;
int led9 = 14;
int led10 = 33;
int led11 = 5;
int led12 = 0;
int led13 = 27;
int led14 = 32;
int led15 = 18;
int led16 = 4;
// capas
int capa1 = 19;
int capa2 = 21;
int capa3 = 22;
int capa4 = 23;
// matiz
int layer[4] = {capa1, capa2, capa3, capa4};
int column[16] = {led1, led2, led3, led4, led5, led6, led7, led8, led9, led10, led11, led12, led13, led14, led15, led16};
// tiempo de ejec
int tiempos = 250;

// conexion mqtt
const char *ssid = "INFINITUMDC44";
const char *password = "julio201743860";
const char *mqtt_server = "driver.cloudmqtt.com";
const char *mqtt_username = "xuzybaen";
const char *mqtt_password = "CTEGwRzS4Mza";
const int mqtt_port = 18887;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];


void callback(const char *topic, byte *payload, unsigned int lenght)
{
  Serial.print("Mensaje recibido bajo el topico ->");
  Serial.print(topic);
  Serial.print("\n");
  for (int i = 0; i < lenght; i++)
  {
    Serial.print((char)payload[i]);
  }
  if ((char)payload[0] == '1') //prender todo
  {
    prendertodo();
    Serial.println("\n Todo Encendido");
  }
  else if ((char)payload[0] == '2')//apagar todo
  {
    apagartodo();
    Serial.println("\n Todo Apagado");
  }
  else if ((char)payload[0] == '3')//patron 1
  {
    luciernaga();
    Serial.println("\n Todo Apagado");
  }
  else if ((char)payload[0] == '4')//patron 2
  {
    lluvia();
    Serial.println("\n Todo Apagado");
  }
  else if ((char)payload[0] == '5')//patron 3
  {
    prendeapaga();
    Serial.println("\n Todo Apagado");
  }
  else if ((char)payload[0] == '6')//patron 4
  {
    levels();
    Serial.println("\n Todo Apagado");
  }
  else if ((char)payload[0] == '7')//patron 5
  {
    espiral();
    Serial.println("\n Todo Apagado");
  }
  else if ((char)payload[0] == '8')//patron 6
  {
    girapalo();
    Serial.println("\n Todo Apagado");
  }
  else if ((char)payload[0] == '9')//patron 7
  {
    leds();
    Serial.println("\n Todo Apagado");
  }



  Serial.println();
}
void reconnect()
{
  while (!client.connected())
  {
    Serial.println("Intentando Conexion MQTT");

    String clientId = "iot_1_";
    clientId = clientId + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println("Conexion a MQTT exitosa!!!");
      client.publish("salidaCubo", "primer mensaje");
      client.subscribe("entradaCubo");
    }
    else
    {
      Serial.println("Fallo la conexion");
      Serial.println(client.state());
      Serial.println("Se intentara de nuevo en 5 segundos");
      delay(5000);
    }
  }
}
void setup_wifi()
{
  // ConexiÃ³n a la red Wifi
  Serial.println();
  Serial.println("Conectando a....");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("Conectado a red WiFi");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
}
void setup()
{
  pinMode(pinled, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  for (int i = 0; i < 16; i++)
  {
    pinMode(column[i], OUTPUT); // filas en modo salida
  }
  for (int i = 0; i < 4; i++)
  {
    pinMode(layer[i], OUTPUT); // columnas en modo salida
  }

}

void loop()
{
  if (client.connected() == false)
  {
    reconnect();
  }
  client.loop();
}

// apagar
void apagartodo()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(column[i], 1);
  }
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(layer[i], 0);
  }
}

// turn all on
void prendertodo()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(column[i], 0);
  }
  // turning on layers
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(layer[i], 1);
  }
}
void prendeapaga(){// prende y apaga
 int i = 100
    while(i != 0)
  {
    prendertodo()
    delay(50);
    apagartodo()
    delay(50);
    i-= 1;
  }
}
// prende y apaga de manera random 1 led
void luciernaga()
{
  apagartodo();
  int x = 10;
  for (int i = 0; i != 750; i += 2)
  {
    int CapaAleatoria = random(0, 4);
    int ColuAleatoria = random(0, 16);

    digitalWrite(layer[CapaAleatoria], 1);
    digitalWrite(column[ColuAleatoria], 0);
    delay(x);
    digitalWrite(layer[CapaAleatoria], 0);
    digitalWrite(column[ColuAleatoria], 1);
    delay(x);
   
  }
}
// lluvia
void lluvia()
{
  apagartodo();
  int x = 100;
  for (int i = 0; i != 60; i += 2)
  {
    int ColuAleatoria = random(0, 16);
    digitalWrite(column[ColuAleatoria], 0);
    digitalWrite(layer[0], 1);
    delay(x +10);
    digitalWrite(layer[0], 0);
    digitalWrite(layer[1], 1);
    delay(x);
    digitalWrite(layer[1], 0);
    digitalWrite(layer[2], 1);
    delay(x);
    digitalWrite(layer[2], 0);
    digitalWrite(layer[3], 1);
    delay(x + 10);
    digitalWrite(layer[3], 0);
    digitalWrite(column[ColuAleatoria], 1);
    
  }
}
void levels()
{
  int x = 75;
  for(int i = 5; i != 0; i--)
  {
    prendertodo();
    for(int i = 4; i!=0; i--)
    {
      digitalWrite(layer[i-1], 0);
      delay(x);
    }
    for(int i = 0; i<4; i++)
    {
      digitalWrite(layer[i], 1);
      delay(x);
    }
      for(int i = 0; i<4; i++)
    {
      digitalWrite(layer[i], 0);
      delay(x);
    }
    for(int i = 4; i!=0; i--)
    {
      digitalWrite(layer[i-1], 1);
      delay(x);
    }
  }
}

void espiral()
{
  prendertodo();
  int x = 50;
  for(int i = 0; i<6; i++)
  {
    //espiral derecha
    digitalWrite(column[0], 1);
    delay(x);
    digitalWrite(column[1], 1);
    delay(x);
    digitalWrite(column[2], 1);
    delay(x);
    digitalWrite(column[3], 1);
    delay(x);
    digitalWrite(column[7], 1);
    delay(x);
    digitalWrite(column[11], 1);
    delay(x);
    digitalWrite(column[15], 1);
    delay(x);
    digitalWrite(column[14], 1);
    delay(x);
    digitalWrite(column[13], 1);
    delay(x);
    digitalWrite(column[12], 1);
    delay(x);
    digitalWrite(column[8], 1);
    delay(x);
    digitalWrite(column[4], 1);
    delay(x);
    digitalWrite(column[5], 1);
    delay(x);
    digitalWrite(column[6], 1);
    delay(x);
    digitalWrite(column[10], 1);
    delay(x);
    digitalWrite(column[9], 1);
    delay(x);
//espiral izquierda
    digitalWrite(column[9], 0);
    delay(x);
    digitalWrite(column[10], 0);
    delay(x);
    digitalWrite(column[6], 0);
    delay(x);
    digitalWrite(column[5], 0);
    delay(x);
    digitalWrite(column[4], 0);
    delay(x);
    digitalWrite(column[8], 0);
    delay(x);
    digitalWrite(column[12], 0);
    delay(x);
    digitalWrite(column[13], 0);
    delay(x);
    digitalWrite(column[14], 0);
    delay(x);
    digitalWrite(column[15], 0);
    delay(x);
    digitalWrite(column[11], 0);
    delay(x);
    digitalWrite(column[7], 0);
    delay(x);
    digitalWrite(column[3], 0);
    delay(x);
    digitalWrite(column[2], 0);
    delay(x);
    digitalWrite(column[1], 0);
    delay(x);
    digitalWrite(column[0], 0);
    delay(x);
  }
}
void apagarCol()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(column[i], 1);
  }
}
void girapalo()
{
  apagartodo();
  int x = 100;
    for(int i = 0; i<6; i++)
    {
      //capas
      digitalWrite(layer[0], 1);
      digitalWrite(layer[1], 1);
      digitalWrite(layer[2], 1);
      digitalWrite(layer[3], 1);
      //
      apagarCol();
      digitalWrite(column[0], 0);
      digitalWrite(column[5], 0);
      digitalWrite(column[10], 0);
      digitalWrite(column[15], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(column[4], 0);
      digitalWrite(column[5], 0);
      digitalWrite(column[10], 0);
      digitalWrite(column[11], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(column[6], 0);
      digitalWrite(column[7], 0);
      digitalWrite(column[8], 0);
      digitalWrite(column[9], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(column[3], 0);
      digitalWrite(column[6], 0);
      digitalWrite(column[9], 0);
      digitalWrite(column[12], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(column[2], 0);
      digitalWrite(column[6], 0);
      digitalWrite(column[9], 0);
      digitalWrite(column[13], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(column[1], 0);
      digitalWrite(column[5], 0);
      digitalWrite(column[10], 0);
      digitalWrite(column[14], 0);
      delay(x);
    }
}
void AllLeds()
{
  int x = 50;
  apagartodo();
  for(int y = 0; y<5; y++)
  {
    //0-3
    for(int k = 4; k != 0; k--)
    {
      digitalWrite(layer[k-1], 1);
      for(int i = 0; i<4; i++)
      {
        digitalWrite(column[i], 0);
        delay(x);
        digitalWrite(column[i], 1);
        delay(x);
      }
    digitalWrite(layer[k-1], 0);
    }
    //4-7
    for(int k = 0; k < 4; k++)
    {
      digitalWrite(layer[k], 1);
      for(int i = 4; i<8; i++)
      {
        digitalWrite(column[i], 0);
        delay(x);
        digitalWrite(column[i], 1);
        delay(x);
      }
    digitalWrite(layer[k], 0);
    }
    //8-11
    for(int k = 4; k != 0; k--)
    {
      digitalWrite(layer[k-1], 1);
      for(int i = 8; i<12; i++)
      {
        digitalWrite(column[i], 0);
        delay(x);
        digitalWrite(column[i], 1);
        delay(x);
      }
    digitalWrite(layer[k-1], 0);
    }
    //12-15
    for(int k = 0; k < 4; k++)
    {
      digitalWrite(layer[k], 1);
      for(int i = 12; i<16; i++)
      {
        digitalWrite(column[i], 0);
        delay(x);
        digitalWrite(column[i], 1);
        delay(x);
      }
    digitalWrite(layer[k], 0);
    }
  }
}