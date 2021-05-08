#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#define PORT 6666
#define BUF_SIZE 128

int maxClientes =10;
int cont=0;
struct client_t* client;

struct client_t{
    int socket;
    int rxState;
    int conectado;
    int conteoCliente;
    char nombreCliente [32];
};

//Prototipado de funciones
void *recibirComandos(void*);
void * readThread(void*);

int main(int argc, char *argv[]){

    char buf[BUF_SIZE];
    int status;
    int enable = 1;
    int server_sd;
    int client_sd;
    pthread_t hiloComandos;
    pthread_t rxThreadId [maxClientes];
    

    client = malloc(sizeof(struct client_t)*maxClientes);

    // 1. Ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    // 2. Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1) {
        perror("Socket creation fails\n");
        exit(EXIT_FAILURE);
    }
    //printf("Socket created\n");

     // 3. turn off bind address checking
    status = setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR,(int *) &enable, sizeof(enable));
    if (-1 == status){
        perror("setsockopt error: ");
    }

     //4. BIND the socket to an address
     // Prepare the address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    status = bind(server_sd, (struct sockaddr*)&addr, sizeof(addr));
    if (-1 == status) {
        perror("Bind fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }
    printf("Socket binded\n");

     // 5. Set backlog

    status = listen(server_sd, 1);

    if (-1 == status) {
        perror("Listen fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<=maxClientes; i++){
        (client+i)->conectado = 0;
    }

    printf("Servidor escuchando\n");
    status = pthread_create(&hiloComandos, NULL, &recibirComandos, NULL);
    if(-1 == status){
        perror("Pthread read fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    while(1){
         // 6. Accept:
        printf("Esperando por clientes\n");
        client_sd = accept(server_sd, NULL, NULL);

        //printf("Client connected\n");
        if(-1 == client_sd){
            perror("Accept fails: ");
            close(server_sd);
            exit(EXIT_FAILURE);
        }
         // 7. Create a thread for receiving messages from client
        (client+cont)->socket = client_sd;
        (client+cont)->rxState = 1;
        (client+cont)->conectado = 1;
        (client+cont)->conteoCliente = cont;

        //printf("Create Pthread for reading\n");
        if(cont<10){
            status = pthread_create(&rxThreadId[cont],NULL,&readThread,(client+cont));
            cont++;
        }
        else{
            printf("Ya se excedio el limite de usuarios conectados");
            close(client_sd);
            //close((client+cont)->socket);
        }
        
            
        if(-1 == status){
            perror("Pthread read fails: ");
            close(server_sd);
            exit(EXIT_FAILURE);

        if(0 == client->rxState){
                printf("Client closed the socket\n");
                break;
            }
        }
       
    }

    free(client);
    exit(EXIT_SUCCESS);
}

 void *recibirComandos(void *x){
    char comando [32];
    char usuariod [32]; 
    int status;
    char buf[BUF_SIZE];
    int control;
    int encontro=0;

    while(strcmp(comando,"exit")!=0){
        printf("\n%s","Escriba el comando\n show para listar los clientes conectados\n -d nombre para desconectar un cliente\n");
        scanf("%s",comando);
        if (strcmp(comando,"-d")==0){
            //desconectar cliente
            scanf("%s",usuariod);
            for(int i=0; i<=maxClientes; i++){
                //(client+i)->conteoCliente = i;
                if(strcmp((client+i)->nombreCliente,usuariod)==0 && (client+i)->conectado ==1){
                    (client+i)->conectado = 0;
                    (client+i)->rxState = 0;
                    cont--;
                    control=i;
                    encontro=1;
                    break;
                }
            }

            if(encontro==1){
                for(int i=0; i<=maxClientes; i++){
                    if((client+i)->conectado == 1 && (client+i)->conteoCliente !=control ){
                        printf(" envio a %s",(client+i)->nombreCliente);
                        strcpy(buf, (client+control)->nombreCliente);
                        strcat(buf, " ha abandonado el chat\n");
                        status = write((client+i)->socket,buf, strlen(buf)+1);
                        if(-1 == status){
                            perror("Server write to client fails: ");
                            break;
                        }
                    }   
                    if((client+i)->conteoCliente == control){
                        strcpy(buf, "Te has desconectado\n");
                        status = write((client+control)->socket,buf, strlen(buf)+1);
                        close((client+control)->socket);
                            if(-1 == status){
                                perror("Server write to client fails: ");
                                break;
                        }
                    }
                }
            }
            else{
                printf("Usuario no encontrado\n");
            }

            encontro=0;
            
        }
        else if (strcmp(comando,"show")==0){
            //mostrar clientes 
            if(cont ==0){
                printf("No hay clientes conectados\n");
            }
            else{
                printf("CLIENTES CONECTADOS\n");
                for(int i=0; i<maxClientes; i++){
                    if((client+i)->conectado !=0){
                        printf("%s\n",(client+i)->nombreCliente);
                    }   
                }   
            }
            printf("conteo:%d\n",cont);
           
        }
        else if(strcmp(comando,"exit")==0){
            printf("\n");
            break;
        }
        else{
            printf("Comando no valido\n");
        }
     }
    return 0;
}

void * readThread(void *arg){
    struct client_t *clienteE = ((struct client_t *)arg);
    ssize_t numOfBytes;
    char buf[BUF_SIZE];
    int status;
    char bvd[BUF_SIZE];

    numOfBytes = read(clienteE->socket, buf, BUF_SIZE);
    //printf("cont=%d/n",cont);
    strcpy((client+(cont-1))->nombreCliente,buf);
    //printf("Primer mensaje: %s\n",buf);

    strcpy(bvd,buf);
    strcat(bvd, " se ha unido al chat");
    for(int i=0; i<=maxClientes; i++){
        if ((client+i)->conectado == 1){
            status = write((client+i)->socket, bvd, strlen(bvd)+1);
            if(-1 == status){
                perror("Server write to client fails: ");
                break;
            }       
        }
    }

    
    while(1){
        numOfBytes = read(clienteE->socket, buf, BUF_SIZE);
        if(0 == numOfBytes){
            printf("client closed the socket end\n");
            break;
        }
        else if(-1 == numOfBytes){
            perror("ReadThread read() fails: ");
            break;
        }
        else {
            if (clienteE->conectado ==1){
            strcat(buf, " -(");
            strcat(buf, clienteE->nombreCliente);
            strcat(buf, ")");
                for(int i=0; i<=maxClientes; i++){
                    if ((client+i)->conectado == 1){
                        status = write((client+i)->socket, buf, strlen(buf)+1);
                    }
                }

                if(-1 == status){
                    perror("Server write to client fails: ");
                    break;
                }
            }
            else{
                printf("no es posible escribir\n");
            }
        }
    }
    //printf("Terminate Pthread for reading\n");
    clienteE->rxState = 0;
    close(clienteE->socket);

    return NULL;
    }