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

## 📜 Exemplo de configuração do smb.conf

- Para permitir que um usuário ou grupo copie arquivos e pastas do computador local para o servidor Samba, mas não possa modificar, excluir ou substituir os arquivos após a cópia, você pode usar as seguintes permissões:
- No seu arquivo de configuração do Samba (/etc/samba/smb.conf), defina o compartilhamento com as permissões adequadas:

```bash
[compartilhamento]
   path = /caminho/do/compartilhamento
   valid users = @grupo # Ou um usuário específico: valid users = usuario
   read only = no
   force user = nobody
   force group = nogroup
   create mask = 0444  # Arquivos criados com permissão somente leitura
   directory mask = 0555  # Pastas criadas sem permissão de escrita
   veto oplock files = /*  # Evita travamentos de arquivos
```

## Após configurar o Samba, ajuste as permissões no sistema de arquivo

```bash
# Define o dono como root e concede permissões restritas
chown root:grupo /caminho/do/compartilhamento
chmod 755 /caminho/do/compartilhamento

# Garante que novos arquivos e pastas sejam somente leitura após a cópia
chmod -R 444 /caminho/do/compartilhamento/*
find /caminho/do/compartilhamento -type d -exec chmod 555 {} \;

```

## 🎯 Objetivo do Projeto

- Desenvolver uma solução simples, estável e segura para compartilhamento de arquivos em uma rede local corporativa, ideal para pequenas e médias empresas ou laboratórios educacionais.

## 🧠 Aprendizados

- Configuração segura do Samba
- Permissões e políticas de acesso
- Integração entre usuários Linux e Samba
- Diagnóstico de rede com testparm, smbclient e netstat

## 📌 Status

✅ Projeto finalizado e funcional em ambiente real

---

📫 Conecte-se comigo no [LinkedIn](https://www.linkedin.com/in/daniel-santos-it/)
