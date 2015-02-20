#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <netdb.h>  
#include <string.h>  
#include <stdlib.h>  


 // Function Used for Print Message.
 void error(char *msg)  		
 	{  	
 	 perror(msg);  
	 exit(0);  
 	} 	

 // main function to run exe file. 
 int main(int argc,char *argv[])	
 {  
        int 	Choice;
 	int 	sockfd,portno,n,newsockfd; 
	int 	PortNumber; 
 	struct  sockaddr_in serv_addr;  
 	struct  hostent *server;  
 	char    buffer[256];  


	// Give The User 3 Choises For Working.
	printf("Enter one of three Choices:\n");
	printf("number:1 ..For Connect To Server\n");
	printf("number:2 ..For quit\n");
	printf("number:3 ..For List Connected Users\n");
				
	// Read Choice From KeyBoard;
	scanf("%d", &Choice);
 	if (Choice!=1 && Choice != 2 && Choice != 3)
 		{  
	 	
		 printf("You Enter invalid Parameters, you must choose only: 1 Or 2 OR 3 ...\n");
		 
		}  
	else 
	
         {
		if (Choice==1)
		{
		   char cName[50];
		   printf("Enter Your Name...\n");
		   scanf("%50s",cName);
		   printf("Welcom To My Talk Project: %s\n",cName);
		   
		   char cHostName[50];
		   printf("Enter Your HostName...\n");
		   scanf("%50s",cHostName);
		  

		   int PortNumber;
		   printf("Enter Your Port Number...\n");
		   scanf("%d",&PortNumber);
	           
		   // Create New Socket.
		   portno=PortNumber;
		   sockfd=socket(AF_INET,SOCK_STREAM,0);
  
 		   if(sockfd<0)  
		   {  
 		    error("Error When opening socket..\n");  
		   }  

		   // Get Host From Name.
		   server=gethostbyname(cHostName);  
 		   if(server==NULL)  
 		   {  
 		    fprintf(stderr,"Error In Your Host Name..\n");  
 		    exit(0);  
 		   }
 
 		   bzero((char*)&serv_addr,sizeof(serv_addr));  
		   serv_addr.sin_family=AF_INET;  
 		   bcopy((char*)server->h_addr,(char*)&serv_addr.sin_addr.s_addr,server->h_length);  
                   serv_addr.sin_port=htons(portno);  
		   
		   if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)  
 		      {  
 			error("Error When connecting To Server..\n");  
 		      }  
 		   bzero(buffer,256);  
 		   printf("The client Say: %s\n ",buffer);  	
		   

		   while  
 			(fgets(buffer,256, stdin) != NULL)
			{  
			   n=write(sockfd,buffer,strlen(buffer));  

 			   if(n<0)  
 				{  
 				 error("error writing to socket..\n");  
 				}  
 			   bzero(buffer,256);  
 		           n=read(sockfd,buffer,255); 
 
 			   if(n<0)  
		 		{  
 				 error("Error reading rom socket..\n");  
 				}

	                   else 
				{   
  				 printf("The server Say: ");   
  				 fputs(buffer, stdout);   
   				 printf("\n");   
  				}    
			 }    
	      }
		else if (Choice== 2)
		{
		   printf("You Are about closing the application..\n"); 
		   printf("You Close Your Session..\n");
		   exit(0);
		}
	      
 
         } 
  
 return 0;     
    
} 
