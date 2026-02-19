# ⚙️ Sistema de Controle de Acesso com ESP32

## 📌 Sobre o Projeto

Edge controller embarcado desenvolvido com ESP32 para integração entre dispositivo de reconhecimento facial e hardware de controle físico, utilizando comunicação via API REST.

O sistema realiza validação de acesso, controle de sessão e acionamento inteligente de relés com base em eventos autorizados.

---

## 🎯 Objetivo

Permitir a integração entre um sistema de reconhecimento facial e dispositivos físicos de controle de acesso (como fechaduras ou catracas), garantindo:

- Consulta otimizada de eventos
- Controle de sessão ativo
- Acionamento seguro de relés
- Processamento local (edge computing)

---

## 🧠 Arquitetura

Dispositivo Facial → API REST → ESP32 → Controle de Relé → Dispositivo Físico

O ESP32 atua como controlador intermediário, reduzindo latência e garantindo autonomia operacional mesmo em cenários de instabilidade de rede.

---

## ⚙️ Tecnologias Utilizadas

- ESP32
- C++ (Arduino Framework)
- Comunicação HTTP (API REST)
- Controle GPIO
- PlatformIO
- Git

---

## 🧩 Funcionalidades Implementadas

- Consumo de API REST para consulta de eventos
- Validação de sessão ativa
- Controle inteligente de relé
- Tratamento básico de falhas de comunicação
- Processamento embarcado com lógica condicional

---

## 🚀 Próximos Passos

- Implementação de cache local de eventos
- Registro de logs persistentes
- Monitoramento remoto
- Integração com sistema de auditoria

---

Daniel Santos  
Tecnologia | Sistemas Embarcados | Integração de Sistemas

