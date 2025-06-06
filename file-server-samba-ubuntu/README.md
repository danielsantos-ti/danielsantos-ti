# 🗂️ Servidor de Arquivos com Samba no Ubuntu

Este projeto implementa um servidor de arquivos utilizando **Samba** em um ambiente **Ubuntu Linux**, com foco em **compartilhamento de pastas por grupos**, segurança e facilidade de acesso em rede local.

## 🔧 Tecnologias e Ferramentas

- Ubuntu Server 20.04 LTS
- Samba (versão X.X.X)
- Terminal e shell script
- Gerenciamento de usuários e grupos
- Permissões de arquivos e diretórios (chmod, chown)

## 🧩 Funcionalidades

- Compartilhamento de arquivos via rede local (protocolo SMB)
- Permissões por grupo de trabalho (ex: `tecnica`, `projetos`)
- Pastas com controle de leitura/gravação
- Autenticação por usuário (Samba + Linux)
- Acesso restrito via senha

## 🗃️ Estrutura de Diretórios

```bash
/srv/
├── Producao/
├── Tecnica/
```

## 👥 Grupos de usuários

- Tecnica
- Producao

## 📜 Referência de Configuração
- Adicionar conf aqui

## 🎯 Objetivo do Projeto

- Desenvolver uma solução simples, estável e segura para compartilhamento de arquivos em uma rede local corporativa, ideal para pequenas e médias empresas ou laboratórios educacionais.

## 🧠 Aprendizados

- Configuração segura do Samba
- Permissões e políticas de acesso
- Integração entre usuários Linux e Samba
- Diagnóstico de rede com testparm, smbclient e netstat

## 📌 Status

✅ Projeto finalizado e funcional em ambiente real
