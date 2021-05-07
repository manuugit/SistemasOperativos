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
    printf("Socket created\n");

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

    printf("Server listening\n");
    status = pthread_create(&hiloComandos, NULL, &recibirComandos, NULL);
    if(-1 == status){
        perror("Pthread read fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    while(1){
         // 6. Accept:
        printf("Waiting for a client\n");
        client_sd = accept(server_sd, NULL, NULL);

        printf("Client connected\n");
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
        printf("Num %d\n",(client+cont)->conteoCliente);

        printf("Create Pthread for reading\n");
        if(cont<10){
            status = pthread_create(&rxThreadId[cont],NULL,&readThread,(client+cont));
        }
        else{
            printf("Ya se excedio el limite de usuarios conectados");
            close((client+cont)->socket);
        }
        cont++;
            
        if(-1 == status){
            perror("Pthread read fails: ");
            close(server_sd);
            exit(EXIT_FAILURE);

        /*if(0 == client.rxState){
                printf("Client closed the socket\n");
                break;
            }*/
        }


        /*while(1){
            
            if ( fgets(buf,BUF_SIZE,stdin) == NULL){
                printf("Fgets NULL\n");
            }

            if( buf[ strlen(buf)-1 ] == '\n') buf[ strlen(buf) - 1 ] = 0;

            status = write(client.socket, buf, strlen(buf)+1);
            if(-1 == status){
                perror("Server write to client fails: ");
                break;
            }
        }*/
       
    }

    exit(EXIT_SUCCESS);
}

 void *recibirComandos(void *x){
    char comando [32];
    char usuariod [32]; 
    int status;
    char buf[BUF_SIZE];
    int control;

    while(strcmp(comando,"exitP")!=0){
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
                    break;
                }
            }

            for(int i=0; i<=maxClientes; i++){
                if((client+i)->conectado == 1 && (client+i)->conteoCliente !=control ){
                    strcpy(buf, (client+control)->nombreCliente);
                    strcat(buf, " ha abandonado el chat\n");
                    status = write((client+i)->socket,buf, strlen(buf)+1);
                    if(-1 == status){
                        perror("Server write to client fails: ");
                        break;
                    }
                }
                if((client+i)->conteoCliente !=control){
                    strcpy(buf, "Te has desconectado\n");
                    status = write((client+control)->socket,buf, strlen(buf)+1);
                    close((client+control)->socket);
                    if(-1 == status){
                        perror("Server write to client fails: ");
                        break;
                    }
                }
            }

            /*for(int i=control; i<=maxClientes; i++){
                (client+i)->conteoCliente = i;
                printf("nuevos nums %d\n",(client+i)->conteoCliente);
            }*/
            
        }
        else if (strcmp(comando,"show")==0){
            printf("conteo:%d\n",cont);
            //mostrar clientes 
            for(int i=0; i<maxClientes; i++){
                if((client+i)->conectado !=0){
                    printf("%s\n",(client+i)->nombreCliente);
                }
               
            }
        }
     }
    return 0;
}

void * readThread(void *arg){
    struct client_t *clienteE = ((struct client_t *)arg);
    ssize_t numOfBytes;
    char buf[BUF_SIZE];
    int status;

    numOfBytes = read(clienteE->socket, buf, BUF_SIZE);
    printf("cont=%d/n",cont);
    strcpy((client+(cont-1))->nombreCliente,buf);
    printf("Primer mensaje: %s\n",buf);

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
        else{
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
    }
    printf("Terminate Pthread for reading\n");
    clienteE->rxState = 0;
    close(clienteE->socket);
    return NULL;
    }