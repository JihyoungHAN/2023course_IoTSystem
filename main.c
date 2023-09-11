#include <stdio.h>
#include "bt_master.h"
#include <unistd.h>
#include "TempSystem.h"
#include "WindSystem.h"


void* carThread(void *param);


int main()
{
    int client = init_server();
    char *recv_message;
    pthread_t tid[5]; 

    while(1){
		
		printf("\nplease write the car mode\n");
		printf("[one] : parking mode || [two] : driving mode || [finish] : finish this system\n");
		recv_message = read_server(client);
        if ( recv_message == NULL ){
            printf("client disconnected\n");
            break;
        }
        //write_server(client, recv_message);
        printf("------------------------------------------------------\n");

        if(strcmp(recv_message, "one") == 0 ) { // parking mode 
            printf("Car mode : [parking mode]\n\n");
            printf("If you want to operate temperatue system, please write [temp].\n");
            recv_message = read_server(client); 
            if(strcmp(recv_message, "temp") == 0) 
            {
				TempSystem(10);
			}
        }
        else if(strcmp(recv_message, "two") == 0) { // driving mode 

				printf("Car mode : [driving mode]\n\n");
				int temp = 1;
				int wind = 2; 
				pthread_create(&tid[0], NULL, carThread, &temp);
				delay(5000);
				pthread_create(&tid[1], NULL, carThread, &wind); 

				pthread_join(tid[0], NULL);
				pthread_join(tid[1], NULL);
        }
        else if(strcmp(recv_message, "finish") == 0){
			printf("finishing this system...\n");
			break;
		} 
	}
}

void* carThread(void *param){
	int num = *((int *)param);
	
	switch(num){
		case 1 :
			TempSystem(11);
			break;
		case 2 : 
			WindSystem();
			break;
	}
}
