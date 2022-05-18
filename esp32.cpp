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
int capa[4] = {capa1, capa2, capa3, capa4};
int columna[16] = {led1, led2, led3, led4, led5, led6, led7, led8, led9, led10, led11, led12, led13, led14, led15, led16};
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
  
  }
  else if ((char)payload[0] == '2')//apagar todo
  {
    apagartodo();
  }
  else if ((char)payload[0] == '3')//patron 1
  {
    luciernaga();
    delay(500);
    apagartodo();
  }
  else if ((char)payload[0] == '4')//patron 2
  {
    lluvia();
    delay(500);
    apagartodo();
  }
  else if ((char)payload[0] == '5')//patron 3
  {
    prendeapaga();
    delay(500);
    apagartodo();
  }
  else if ((char)payload[0] == '6')//patron 4
  {
    levels();
    delay(500);
    apagartodo();
  }
  else if ((char)payload[0] == '7')//patron 5
  {
    espiral();
    delay(500);
    apagartodo();
  }
  else if ((char)payload[0] == '8')//patron 6
  {
    girapalo();
    delay(500);
    apagartodo();
  }
  else if ((char)payload[0] == '9')//patron 7
  {
    Leds();
    delay(500);
    apagartodo();
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
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  for (int i = 0; i < 16; i++)
  {
    pinMode(columna[i], OUTPUT); // filas en modo salida
  }
  for (int i = 0; i < 4; i++)
  {
    pinMode(capa[i], OUTPUT); // columnaas en modo salida
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
    digitalWrite(columna[i], 1);
  }
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(capa[i], 0);
  }
}

// prender todo
void prendertodo()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(columna[i], 0);
  }
  // prender capas
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(capa[i], 1);
  }
}
void prendeapaga(){// prende y apaga
 int i = 50;
    while(i != 0)
  {
    prendertodo();
    delay(100);
    apagartodo();
    delay(100);
    i-= 1;
  }
}
// prende y apaga de manera random 1 led
void luciernaga()
{
 
  int x = 10;
  for (int i = 0; i != 750; i += 2)
  {
    int CapaAleatoria = random(0, 4);
    int ColuAleatoria = random(0, 16);

    digitalWrite(capa[CapaAleatoria], 1);
    digitalWrite(columna[ColuAleatoria], 0);
    delay(x);
    digitalWrite(capa[CapaAleatoria], 0);
    digitalWrite(columna[ColuAleatoria], 1);
    delay(x);
   
  }
}
// lluvia
void lluvia()
{

  int x = 100;
  for (int i = 0; i != 60; i += 2)
  {
    int ColuAleatoria = random(0, 16);
    digitalWrite(columna[ColuAleatoria], 0);
    digitalWrite(capa[0], 1);
    delay(x +10);
    digitalWrite(capa[0], 0);
    digitalWrite(capa[1], 1);
    delay(x);
    digitalWrite(capa[1], 0);
    digitalWrite(capa[2], 1);
    delay(x);
    digitalWrite(capa[2], 0);
    digitalWrite(capa[3], 1);
    delay(x + 10);
    digitalWrite(capa[3], 0);
    digitalWrite(columna[ColuAleatoria], 1);
    
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
      digitalWrite(capa[i-1], 0);
      delay(x);
    }
    for(int i = 0; i<4; i++)
    {
      digitalWrite(capa[i], 1);
      delay(x);
    }
      for(int i = 0; i<4; i++)
    {
      digitalWrite(capa[i], 0);
      delay(x);
    }
    for(int i = 4; i!=0; i--)
    {
      digitalWrite(capa[i-1], 1);
      delay(x);
    }
  }
}

void espiral()
{
  prendertodo();
  int x = 50;
  for(int i = 0; i<4; i++)
  {
    //espiral derecha
    digitalWrite(columna[0], 1);
    delay(x);
    digitalWrite(columna[1], 1);
    delay(x);
    digitalWrite(columna[2], 1);
    delay(x);
    digitalWrite(columna[3], 1);
    delay(x);
    digitalWrite(columna[7], 1);
    delay(x);
    digitalWrite(columna[11], 1);
    delay(x);
    digitalWrite(columna[15], 1);
    delay(x);
    digitalWrite(columna[14], 1);
    delay(x);
    digitalWrite(columna[13], 1);
    delay(x);
    digitalWrite(columna[12], 1);
    delay(x);
    digitalWrite(columna[8], 1);
    delay(x);
    digitalWrite(columna[4], 1);
    delay(x);
    digitalWrite(columna[5], 1);
    delay(x);
    digitalWrite(columna[6], 1);
    delay(x);
    digitalWrite(columna[10], 1);
    delay(x);
    digitalWrite(columna[9], 1);
    delay(x);
//espiral izquierda
    digitalWrite(columna[9], 0);
    delay(x);
    digitalWrite(columna[10], 0);
    delay(x);
    digitalWrite(columna[6], 0);
    delay(x);
    digitalWrite(columna[5], 0);
    delay(x);
    digitalWrite(columna[4], 0);
    delay(x);
    digitalWrite(columna[8], 0);
    delay(x);
    digitalWrite(columna[12], 0);
    delay(x);
    digitalWrite(columna[13], 0);
    delay(x);
    digitalWrite(columna[14], 0);
    delay(x);
    digitalWrite(columna[15], 0);
    delay(x);
    digitalWrite(columna[11], 0);
    delay(x);
    digitalWrite(columna[7], 0);
    delay(x);
    digitalWrite(columna[3], 0);
    delay(x);
    digitalWrite(columna[2], 0);
    delay(x);
    digitalWrite(columna[1], 0);
    delay(x);
    digitalWrite(columna[0], 0);
    delay(x);
  }
}
void apagarCol()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(columna[i], 1);
  }
}
void girapalo()
{

  int x = 100;
    for(int i = 0; i<6; i++)
    {
      //capas
      digitalWrite(capa[0], 1);
      digitalWrite(capa[1], 1);
      digitalWrite(capa[2], 1);
      digitalWrite(capa[3], 1);
      //
      apagarCol();
      digitalWrite(columna[0], 0);
      digitalWrite(columna[5], 0);
      digitalWrite(columna[10], 0);
      digitalWrite(columna[15], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(columna[4], 0);
      digitalWrite(columna[5], 0);
      digitalWrite(columna[10], 0);
      digitalWrite(columna[11], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(columna[6], 0);
      digitalWrite(columna[7], 0);
      digitalWrite(columna[8], 0);
      digitalWrite(columna[9], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(columna[3], 0);
      digitalWrite(columna[6], 0);
      digitalWrite(columna[9], 0);
      digitalWrite(columna[12], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(columna[2], 0);
      digitalWrite(columna[6], 0);
      digitalWrite(columna[9], 0);
      digitalWrite(columna[13], 0);
      delay(x);
      //
      apagarCol();
      digitalWrite(columna[1], 0);
      digitalWrite(columna[5], 0);
      digitalWrite(columna[10], 0);
      digitalWrite(columna[14], 0);
      delay(x);
    }
    apagartodo();
}
void Leds()
{
  int x = 50;
  
    //0-3
    for(int k = 4; k != 0; k--)
    {
      digitalWrite(capa[k-1], 1);
      for(int i = 0; i<4; i++)
      {
        digitalWrite(columna[i], 0);
        delay(x);
        digitalWrite(columna[i], 1);
        delay(x);
      }
    digitalWrite(capa[k-1], 0);
    }
    //4-7
    for(int k = 0; k < 4; k++)
    {
      digitalWrite(capa[k], 1);
      for(int i = 4; i<8; i++)
      {
        digitalWrite(columna[i], 0);
        delay(x);
        digitalWrite(columna[i], 1);
        delay(x);
      }
    digitalWrite(capa[k], 0);
    }
    //8-11
    for(int k = 4; k != 0; k--)
    {
      digitalWrite(capa[k-1], 1);
      for(int i = 8; i<12; i++)
      {
        digitalWrite(columna[i], 0);
        delay(x);
        digitalWrite(columna[i], 1);
        delay(x);
      }
    digitalWrite(capa[k-1], 0);
    }
    //12-15
    for(int k = 0; k < 4; k++)
    {
      digitalWrite(capa[k], 1);
      for(int i = 12; i<16; i++)
      {
        digitalWrite(columna[i], 0);
        delay(x);
        digitalWrite(columna[i], 1);
        delay(x);
      }
    digitalWrite(capa[k], 0);
    }
  
 
}