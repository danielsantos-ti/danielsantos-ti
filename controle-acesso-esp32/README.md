# ⚙️ Sistema de Controle de Acesso com ESP32 (Versão Demonstrativa)

## 📌 Sobre o Projeto

Esta é uma **versão pública demonstrativa** de um edge controller embarcado desenvolvido com ESP32 para integração entre sistemas de reconhecimento facial e hardware de controle físico.

⚠️ Esta implementação não contém:
- Endpoints reais
- Credenciais
- Endereços de infraestrutura
- Lógica sensível de produção

A versão completa utilizada em ambiente real permanece privada.

---

## 🎯 Objetivo da Versão Pública

Demonstrar:

- Estrutura arquitetural do firmware
- Organização de código embarcado
- Integração via API REST
- Controle inteligente de relés
- Lógica de sessão e validação de eventos

Sem expor dados sensíveis ou infraestrutura operacional.

---

## 🧠 Arquitetura Conceitual

Dispositivo de Reconhecimento → API REST (Mock) → ESP32 → Relé → Dispositivo Físico

O ESP32 atua como controlador intermediário, realizando processamento local (edge computing) para:

- Redução de latência
- Autonomia operacional
- Controle condicional embarcado

---

## ⚙️ Tecnologias Utilizadas

- ESP32  
- C++ (Arduino Framework)  
- Comunicação HTTP  
- Controle GPIO  
- PlatformIO  
- Git  

---

## 🧩 Funcionalidades Demonstradas

- Consumo de endpoint simulado (mock API)
- Validação de evento de acesso
- Controle condicional de relé
- Estrutura modular de firmware
- Tratamento básico de falhas

---

## 🔐 Boas Práticas Aplicadas

- Separação de responsabilidades
- Isolamento de configuração sensível
- Estrutura preparada para variáveis de ambiente
- Versionamento controlado

---

## 🚀 Possíveis Evoluções

- Cache local de eventos
- Logs persistentes
- Sistema de fallback offline
- Telemetria e monitoramento remoto

---

## 📎 Observação Importante

Este repositório tem finalidade exclusivamente demonstrativa e educacional.  
Qualquer semelhança com ambientes reais refere-se apenas à modelagem arquitetural.

---

Daniel Santos  
Tecnologia | Sistemas Embarcados | Integração de Sistemas
