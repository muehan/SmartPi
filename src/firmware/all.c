#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>


char device_address;

#define BUFSIZE 4

char value, phase, phase_write, number;




//int main(void)
int main( int argc, char* argv[] )
{
  char buffer[200];
  char current_1[10];
  char current_2[10];
  char current_3[10]; 
  //char current_4[10]; 
  char voltage_1[10];
  char voltage_2[10];
  char voltage_3[10];  
  char power_1[10];
  char power_2[10];
  char power_3[10];
  char cosphi_1[10];
  char cosphi_2[10];
  char cosphi_3[10]; 
  char frequenz_1[10];
  char frequenz_2[10];
  char frequenz_3[10]; 

  int v=0, t=0;




FILE *fp;
int temp;

fp = fopen("/run/SmartPi/Smartpi_Value.txt", "r");



if(fp == NULL) 
{
	printf("Datei konnte nicht geoeffnet werden.\n");
}
else 
{
	// komplette Datei zeichenweise ausgeben
	while((temp = fgetc(fp))!=EOF) 
	{
		
		//printf("%c ", temp);
		buffer[v]=temp;
		v++;
		
		
		
		

	}
}

fclose(fp);
v=0;


char delimiter[] = ":";//Trennzeichen (:) zwischen den die Werte stehen, insgesamt 16 Werte!!!
char *ptr;

// initialisieren und ersten Abschnitt erstellen
ptr = strtok(buffer, delimiter);

while(ptr != NULL) 
{
	//printf("Abschnitt gefunden: %s\n", ptr);
	switch(v) 
	{
		case 0: strcpy(current_1, ptr); break;
		case 1: strcpy(current_2, ptr); break;
		case 2: strcpy(current_3, ptr); break;
		//case 3: strcpy(current_4, ptr); break;
		case 4: strcpy(voltage_1, ptr); break;
		case 5: strcpy(voltage_2, ptr); break;
		case 6: strcpy(voltage_3, ptr); break;		
		case 7: strcpy(power_1, ptr); break;
		case 8: strcpy(power_2, ptr); break;
		case 9: strcpy(power_3, ptr); break;
              case 10: strcpy(cosphi_1, ptr); break;
		case 11: strcpy(cosphi_2, ptr); break;
		case 12: strcpy(cosphi_3, ptr); break;
		case 13: strcpy(frequenz_1, ptr); break;
		case 14: strcpy(frequenz_2, ptr); break;
		case 15: strcpy(frequenz_3, ptr); break;		
              default:  break;
	} 
	//strcpy(current_1, ptr);
	v++;
	// naechsten Abschnitt erstellen
 	ptr = strtok(NULL, delimiter);
} 
 

value=atoi(argv[2]);
//printf("\r\nEingabe Value %i\r\n",value);
phase=atoi(argv[3]);
//printf("\r\nEingabe Phase %i\r\n",phase);
		
    	
//-------------------------------------------------------------------------------------


//IP-SCAN
int fd;
 struct ifreq ifr;

 fd = socket(AF_INET, SOCK_DGRAM, 0);

 /* I want to get an IPv4 IP address */
 ifr.ifr_addr.sa_family = AF_INET;

 /* I want IP address attached to "eth0" */
 strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

 ioctl(fd, SIOCGIFADDR, &ifr);

 close(fd);

 /* display result */
 //printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));






//TIME
/*time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "Current local time and date: %s", asctime (timeinfo) );
*/

time_t w = time(NULL);
struct tm tm = *localtime(&w);



//JSON
printf("{");
printf("\"serial\": \"12345678\",");
//printf("\"time\": \"2016-03-11 16:06:00\",");
printf("\"time\": \"%d-%d-%d %d:%d:%d\",", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
printf("\"softwareversion\": \"1.0.1\",");
printf("\"ipaddress\": \"%s\",",inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
printf("\"datasets\": [{");
//printf("\"time\": \"2016-03-11 11:20:00\",");
printf("\"time\": \"%d-%d-%d %d:%d:%d\",", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
printf("\"phases\": [{");



if (phase!=77)number=3;//1 Phase
else number=0;//All
		
for (t=number;t<4;t++)
{
	if(phase==77)
	{
	   	phase_write=t+1;
	}
	else phase_write=phase;

	switch(phase_write)
	{
		
		//Phase 1
		case 1:
		{
			
			printf("\"phase\": %i,",phase_write);
			printf("\"name\": \"phase %i\",",phase_write);
			printf("\"values\": [{");
 		
			switch (value)
			{
				//All:
				case 77:
				{
										
						
					
						printf("\"type\": \"current\",");
						printf("\"unity\": \"A\",");
						printf("\"data\": %s",current_1);
						printf("}, {");



										
						printf("\"type\": \"voltage\",");
						printf("\"unity\": \"V\",");
						printf("\"data\": %s",voltage_1);
						printf("}, {");

						//Power:
						
						printf("\"type\": \"power\",");
						printf("\"unity\": \"W\",");
						printf("\"data\": %s",power_1);
						printf("}, {");



									
						printf("\"type\": \"cosphi\",");
						printf("\"unity\": \" \",");
						printf("\"data\": %s",cosphi_1);
						printf("}, {");

						
						//Frequenz VA				
						printf("\"type\": \"frequenzy\",");
						printf("\"unity\": \"Hz\",");
						printf("\"data\": %s",frequenz_1);
						if(phase==77)printf("}]");
						if(phase==77)printf("}, {");
												

					

					break;
				

		  	 	}//Ende case 77 all (phase 1)




	 		}//Ende switch(value)
		
			break;
		}//Ende Case 1 (Phase 1)













		//Phase 2
		case 2:
		{
			
			printf("\"phase\": %i,",phase_write);
			printf("\"name\": \"phase %i\",",phase_write);
			printf("\"values\": [{");
 		
			switch (value)
			{
				//All:
				case 77:
				{
										
						
					
						printf("\"type\": \"current\",");
						printf("\"unity\": \"A\",");
						printf("\"data\": %s",current_2);
						printf("}, {");



							
						printf("\"type\": \"voltage\",");
						printf("\"unity\": \"V\",");
						printf("\"data\": %s",voltage_2);
						printf("}, {");

						//Power:
						
						printf("\"type\": \"power\",");
						printf("\"unity\": \"W\",");
						printf("\"data\": %s",power_2);
						printf("}, {");



									
						printf("\"type\": \"cosphi\",");
						printf("\"unity\": \" \",");
						printf("\"data\": %s",cosphi_2);
						printf("}, {");

						
						//Frequenz VB					
						printf("\"type\": \"frequenzy\",");
						printf("\"unity\": \"Hz\",");
						printf("\"data\": %s",frequenz_2);
						if(phase==77)printf("}]");
						if(phase==77)printf("}, {");
												

					

					break;
				

		  	 	}//Ende case 77 all (phase 2)




	 		}//Ende switch(value)
		
			break;
		}//Ende Case 2 (Phase 2)









		//Phase 3
		case 3:
		{
			
			printf("\"phase\": %i,",phase_write);
			printf("\"name\": \"phase %i\",",phase_write);
			printf("\"values\": [{");
 		
			switch (value)
			{
				//All:
				case 77:
				{
										
						
					
						printf("\"type\": \"current\",");
						printf("\"unity\": \"A\",");
						printf("\"data\": %s",current_3);
						printf("}, {");



									
						printf("\"type\": \"voltage\",");
						printf("\"unity\": \"V\",");
						printf("\"data\": %s",voltage_3);
						printf("}, {");

						//Power:
						
						printf("\"type\": \"power\",");
						printf("\"unity\": \"W\",");
						printf("\"data\": %s",power_3);
						printf("}, {");



								
						printf("\"type\": \"cosphi\",");
						printf("\"unity\": \" \",");
						printf("\"data\": %s",cosphi_3);
						printf("}, {");

						
						//Frequenz VC					
						printf("\"type\": \"frequenzy\",");
						printf("\"unity\": \"Hz\",");
						printf("\"data\": %s",frequenz_3);
						
												

					break;
				

		  	 	}//Ende case 77 all (phase 3)




	 		}//Ende switch(value)
		
			break;
		}//Ende Case 3 (Phase 3)











		


		



		default:
  		{
   	 		//Wenn keine Wahl zutrifft!!!
   	 		break;
  		}



	}//Ende der Switch-Anweisung (PHASE)

}//Ende der for-Schleife
printf("}]");
printf("}]");
printf("}]");
printf("}");

  
  return 0;
}