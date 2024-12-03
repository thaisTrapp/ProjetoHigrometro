#include <WiFi.h>
#include <PubSubClient.h>

#define SENSOR_PIN 34  

// CREDENCIAIS REDE
const char* ssid = "POCO M3";
const char* password = "POCO12345";  
const char* mqtt_server = "192.168.43.131";  // IP do broker MQTT

WiFiClient espClient;
PubSubClient client(espClient);

// CONEXÃO WIFI
void setup_wifi() {
  delay(10);
  Serial.print("Conectando-se à rede Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}


// CONEXÃO BROKER MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar ao broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println(" Conectado!");
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}


// SETUP
void setup() {
  setCpuFrequencyMhz(80);
  Serial.begin(115200);
  setup_wifi();

  client.setServer(mqtt_server, 1883);

  // Conectar ao broker e enviar informações iniciais
  reconnect();
}

void loop() {
  // Manter conexão com o broker
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura do sensor de umidade
  int valorUmidade = analogRead(SENSOR_PIN);  // Valor entre 0 e 4095
  int umidade = map(valorUmidade, 0, 4095, 100, 0); // Mapeando para a faixa de 0 a 100

  String msg;
  if (umidade < 20) {
    msg = "Cuidado! Solo seco";
  } else if (umidade >= 20 && umidade < 45) {
    msg = "Solo bom";
  } else if (umidade >= 45) {
    msg = "Cuidado! Solo muito úmido";
  } else {
    msg = "Erro na leitura";
  }

  String mensagemCompleta = msg + ", umidade do solo: " + String(umidade) + "%";
  client.publish("umidade/solo", mensagemCompleta.c_str());
  

  // PUBLICAR INFORMAÇÕES
  String esp32IP = WiFi.localIP().toString();
  String brokerIP = mqtt_server;
  int brokerPort = 1883;

  String infoMsg = "ESP32 IP: " + esp32IP + ", Broker IP: " + brokerIP +
                   ", Broker Port: " + String(brokerPort);

  client.publish("esp32", infoMsg.c_str());

//  Serial.println("Informações publicadas no MQTT:");
 // Serial.println(infoMsg);


  // Serial print
  Serial.print("Valor da umidade do solo: ");
  Serial.println(umidade);

  // Espera antes de nova leitura
  delay(5000);
}
