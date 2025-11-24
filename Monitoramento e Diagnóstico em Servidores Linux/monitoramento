# 📊 Monitoramento e Diagnóstico em Servidores Linux

Breve introdução explicando o objetivo do documento:  
Este guia reúne comandos práticos para **monitoramento de desempenho, análise de recursos e diagnóstico** em servidores Linux, aplicados em ambiente real de Inteligência Artificial.

---

## 🧠 1. Análise de Memória RAM
- **Comando:** `free -h`
- **Interpretação:**
  - `used`: memória usada por processos ativos
  - `buff/cache`: memória usada para cache e buffers
  - `available`: memória realmente disponível para novos processos
  - `swap`: memória virtual usada quando a RAM está cheia

---

## 🎮 2. Monitoramento da GPU
- **Comando:** `nvidia-smi`
- **Interpretação:** temperatura, performance, consumo de energia, uso de memória e processos ativos

- **Comando em tempo real:** `watch -n 2 nvidia-smi`  
  Atualiza a saída a cada 2 segundos

- **Identificação de processos:** `ps -fp <PID>`  
  Mostra o comando exato que está rodando

---

## 🧹 3. Limpeza e Verificação de Cache
- **Comandos de limpeza:** `sync`, `echo 1/2/3 > /proc/sys/vm/drop_caches`
- **Comandos de verificação:** `free -h`, `vmstat -s`, `htop`, `cat /proc/meminfo`

**Observação:** só usar para testes ou depuração, pois o Linux gerencia cache de forma inteligente.

---

## 🟩 4. Diagnóstico de Lentidão no Servidor
- **Hardware:** `top`, `df -h`, `ps aux --sort=-%cpu`, `ps aux --sort=-%mem`
- **Temperatura:** `lm-sensors`, `sensors`
- **Software/Serviços:** `systemctl --failed`, `journalctl`, `dmesg`
- **Rede:** `ping`, `nslookup`, `dig`, `mtr`, `traceroute`
- **Containers:** `docker stats --no-stream`
- **RAID:** `cat /proc/mdstat`, `mdadm --detail`, `journalctl -u mdmonitor`

---

## ✅ 5. Observações Finais
- Todos os comandos foram aplicados em **ambiente real de servidores Linux**  
- Auxiliaram na detecção de falhas de conectividade, otimização de recursos e aumento da confiabilidade da infraestrutura  
- O uso exclusivo da **linha de comando (CLI)** reforça a proficiência em administração avançada de sistemas Linux
