# Monitoramento de Umidade do Solo com ESP32 e MQTT

## Descrição do Projeto
Este projeto utiliza um ESP32 para monitorar a umidade do solo, enviar os dados para um broker MQTT e exibir alertas sobre o estado do solo. Ele é ideal para sistemas de irrigação automatizados ou para acompanhamento remoto da condição do solo em plantações ou jardins.

---

## Funcionalidades
1. **Monitoramento da Umidade do Solo**  
   O sensor analógico mede a umidade do solo, retornando um valor entre 0% (muito seco) e 100% (muito úmido).

2. **Alertas Personalizados**  
   Baseado na umidade lida, o sistema gera alertas:
   - **Solo seco**: Umidade abaixo de 20%.
   - **Solo ideal**: Umidade entre 20% e 45%.
   - **Solo muito úmido**: Umidade acima de 45%.

3. **Conectividade Wi-Fi**  
   O ESP32 conecta-se a uma rede Wi-Fi para comunicação com o broker MQTT.

4. **Publicação em MQTT**  
   Os dados do sensor e informações do dispositivo são publicados em tópicos MQTT, permitindo integração com plataformas IoT.

---

## Dependências
1. **Hardware**:
   - ESP32
   - Sensor de umidade do solo (conectado ao pino analógico 34 do ESP32)

2. **Bibliotecas Arduino**:
   - [WiFi.h](https://www.arduino.cc/en/Reference/WiFi)
   - [PubSubClient](https://github.com/knolleary/pubsubclient)

---

## Configuração

### Hardware
1. Conecte o sensor de umidade do solo ao pino analógico `34` do ESP32.  
2. Certifique-se de que o ESP32 esteja alimentado corretamente.

### Rede Wi-Fi
Edite o código com as credenciais da sua rede:
```cpp
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";

