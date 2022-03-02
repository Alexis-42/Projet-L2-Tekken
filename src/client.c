#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close (s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define PORT 23



int main(void)
{
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif

    SOCKADDR_IN sin;
    SOCKET sock;
    int recsize = sizeof sin;

    int sock_err;

    if(!erreur)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if(sock != INVALID_SOCKET)
        {
            printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

            sin.sin_addr.s_addr = htonl(INADDR_ANY);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(PORT);
            sock_err = bind(sock, (SOCKADDR*) &sin, recsize);

            if(sock_err != SOCKET_ERROR)
            {
                sock_err = listen(sock, 5);
                printf("Listage du port %d...\n", PORT);

                if(sock_err != SOCKET_ERROR)
                {
                    /* Création de l'ensemble de lecture */
                    fd_set readfs;

                    while(1)
                    {
                        /* On vide l'ensemble de lecture et on lui ajoute
                        la socket serveur */
                        FD_ZERO(&readfs);
                        FD_SET(sock, &readfs);

                        /* Si une erreur est survenue au niveau du select */
                        if(select(sock + 1, &readfs, NULL, NULL, NULL) < 0)
                        {
                            perror("select()");
                            exit(errno);
                        }

                        /* On regarde si la socket serveur contient des
                        informations à lire */
                        if(FD_ISSET(sock, &readfs))
                        {
                            /* Ici comme c'est la socket du serveur cela signifie
                            forcement qu'un client veut se connecter au serveur.
                            Dans le cas d'une socket cliente c'est juste des
                            données qui serons reçues ici*/

                            SOCKADDR_IN csin;
                            int crecsize = sizeof csin;

                            /* Juste pour l'exemple nous acceptons le client puis
                            nous refermons immédiatement après la connexion */
                            SOCKET csock = accept(sock, (SOCKADDR *) &csin, &crecsize);
                            closesocket(csock);

                            printf("Un client s'est connecte\n");
                        }
                    }
                }
            }
        }
    }

    #if defined (WIN32)
        WSACleanup();
    #endif

    return EXIT_SUCCESS;
}
