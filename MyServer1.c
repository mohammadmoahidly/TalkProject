 #include<stdio.h>  
 #include<sys/types.h>  
 #include<sys/socket.h>  
 #include<netinet/in.h>  
 #include<stdlib.h>  
 #include<string.h> 
 
 void error(char *msg) 
 {
 	perror(msg);  
 	exit(1);  
 }  

 int main(int argc,char *argv[])  
 {  
 	int sockfd,newsockfd,portno,clilen,k;  
 	char buffer[256];  
 	pid_t childpid;  
 	struct sockaddr_in serv_addr,cli_addr;  
	int n; 
 	

	// Test is valid Parameter
 	if(argc<2)  
 	{  
 	 fprintf(stderr,"error,no port provided\n");  
 	 exit(1);  
 	}  

	//Create New socket
 	sockfd=socket(AF_INET,SOCK_STREAM,0);  
 	if(sockfd<0)  
 	{  
 	 error("error opening socket");  
 	} 
 

 	bzero((char *)&serv_addr,sizeof(serv_addr));  
 	portno=atoi(argv[1]);  
 	serv_addr.sin_family=AF_INET;  
 	serv_addr.sin_addr.s_addr=INADDR_ANY;  
	serv_addr.sin_port=htons(portno); 
 
	// Do Bindding
 	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0)  
 	{  
 	 error("error on binding");  
	}  

	// Listning
 	k=listen(sockfd,5);  
 	for (;;) {  
	 clilen=sizeof(cli_addr);  
	 if(k<0) {  
 	error("error on inding the network");  
 	exit(1);  
 	}  

 	printf("Server is running..........\n         Waiting for the client on the port number: %d\n",portno);   
 	newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);  
 	if(newsockfd<0)  
 	{  
	 error("error on accept");  
 	}  

 	printf("Connection accepted...\n"); 
	
  
  	if ((childpid = fork()) == 0) 
	{
		//creating a child process   
	  	close(sockfd);    
	 	//stop listening for new connections by the main process.    
	 	//the child will continue to listen.    
		//the main process now handles the connected client.   
 	 
	for (;;) 
	{   
		bzero(buffer,256);  
 		n=read(newsockfd,buffer,255); 

 		if(n<0)  
	 	{
		 	 error("Error reading from socket");  
 		}  
 		else  
 		{
			//chat
			if(buffer[0] == 0)
			{
				printf("client: %s\n", buffer+1);

				bzero(buffer,256);  
		 		printf("The server: Please enter your message: %s",buffer);  
		 		fgets(buffer,256,stdin);  
 				n=write(newsockfd,buffer,strlen(buffer));  
 				if(n<0)  
 				{  
 		 			error("error writing socket");  
 				}
			}


 		 	
 		}  

 		 
   	}   
 	 }   
	  close(newsockfd);   
	}   
 }  
