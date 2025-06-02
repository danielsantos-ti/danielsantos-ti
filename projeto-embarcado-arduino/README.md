# 🔩 Projeto Arduino: Verificação de Presença de Parafusos

Este projeto demonstra uma aplicação simples com **Arduino** para simular a **verificação da presença de parafusos** em uma linha de produção, utilizando dois botões como sensores simulados.

## ⚙️ Funcionamento

- Dois botões representam sensores que detectam se os parafusos estão posicionados corretamente.
- Um botão de teste inicia o processo de verificação.
- O Arduino verifica o estado dos dois sensores (botões):
  - ✅ **Se ambos os parafusos estiverem presentes** (botões pressionados):  
    → Uma **sequência de bipes curtos** é emitida para indicar sucesso.
  - ❌ **Se um ou ambos os parafusos estiverem ausentes**:  
    → Um **bipe longo** é emitido, indicando falha no teste.

## 🎥 Demonstração

🔗 [Clique aqui para assistir ao vídeo no YouTub](https://www.youtube.com/shorts/cwiBl8wKzog)

## 💻 Repositório

📂 [Veja o código-fonte no GitHub](https://github.com/danielsantos-ti/Probe_test)

## 🛠️ Tecnologias e Componentes

- Arduino UNO  
- 2 Botões (sensores de parafuso)  
- 1 Botão de teste  
- Buzzer piezoelétrico  
- Resistores de pull-down  
- Código em linguagem C/C++ (Arduino IDE)

## 🚀 Aplicações

Esse projeto pode ser adaptado para processos de **controle de qualidade**, **verificação de montagem**, ou **automatização de testes físicos** em linhas de montagem industriais.

---

