
//////////////////////////////////////////////////////////////////////////////////////////
// Classe: Reportgraph
//
// Objetivo: Criar relatórios de execução para carga dos grafos e execuções dos algoritmos
//           de Dijkstra
//
// Classes com interface: NA
//
// Autores: Charles, Zara e Bressane
//
// Data: 26/06/23
///////////////////////////////////////////////////////////////////////////////////////////


struct TimeProcess {
   char szClassName[50]="\0";
   char szFileRead[50]="\0";
   int  iNumNodes=0;
   char szProcessType[50]="\0";
   clock_t startUserCPUTime;
   clock_t endUserCPUTime;
   clock_t userCPUDuration;
   clock_t startSystemCPUTime;
   clock_t endSystemCPUTime;
   clock_t systemDuration;
   time_t  startRealTime;
   time_t  endRealTime;
   time_t  realTimeDuration;
   clock_t startCPUTime;
   clock_t endCPUTime;
   clock_t CPUTimeDuration;
   char    szrealTimeDurationFormatted[10]="\0";
   char    szTimeStart[12]="\0";
   char    szTimeEnd[12]="\0";
};


class Reportgraph {
	public:

          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: Construtores
          ///////////////////////////////////////////////////////////////////////////////////////////
          Reportgraph( char *pszReportPath ) {
	     strcpy(szReportPath,pszReportPath);
             iNumReport=0;
	  }

	  void incrementNumReport() {
	     iNumReport++;
	  }

          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: Grupo de métodos set
          //
          // Parâmetros: Valores a serem persistidos
	  //
	  // Retorno: NA
          //
          // Objetivo: Persistir valores em seus respectivos campos na estrutura de relatórios
          //
          // Autores: Charles, Zara e Bressane
          //
          // Data: 26/06/23
          ///////////////////////////////////////////////////////////////////////////////////////////
	  void setNumReport(int NumReport ) {
	     iNumReport = NumReport;	  
	  }

          void setClassName(char *pszClassName) {
             strcpy(timeProcess[(iNumReport)].szClassName,pszClassName);
	  }

	  void setFileRead(char *pszFileRead) {
             strcpy(timeProcess[(iNumReport)].szFileRead,pszFileRead);
	  }

	  void setNumberNodes(int NumNodes) {
             timeProcess[(iNumReport)].iNumNodes = NumNodes;
	  }

	  void setProcessType(char *pszProcessType) {
             strcpy(timeProcess[(iNumReport)].szProcessType,pszProcessType);
	  }

	  void setStartUserCPUTime(clock_t startUserCPUTime) {
             timeProcess[(iNumReport)].startUserCPUTime = startUserCPUTime;
          }

	  void setEndUserCPUTime(clock_t endUserCPUTime) {
             timeProcess[(iNumReport)].endUserCPUTime = endUserCPUTime;
          }

	  void setUserCPUDuration(clock_t userCPUDuration) {
             timeProcess[(iNumReport)].userCPUDuration = userCPUDuration;
          }

	  void setStartSystemCPUTime(clock_t startSystemCPUTime) {
             timeProcess[(iNumReport)].startSystemCPUTime = startSystemCPUTime;
          }

	  void setEndSystemCPUTime(clock_t endSystemCPUTime) {
             timeProcess[(iNumReport)].endSystemCPUTime = endSystemCPUTime;
          }

	  void setSystemDuration(clock_t systemDuration) {
             timeProcess[(iNumReport)].systemDuration = systemDuration;
          }

	  void setStartRealTime(time_t startRealTime) {
             timeProcess[(iNumReport)].startRealTime = startRealTime;
          }

	  void setEndRealTime(time_t endRealTime) {
             timeProcess[(iNumReport)].endRealTime = endRealTime;
          }

	  void setRealTimeDuration(time_t realTimeDuration) {
             timeProcess[(iNumReport)].realTimeDuration = realTimeDuration;
          }

	  void setrealTimeDurationFormatted(char * pszrealTimeDurationFormatted) {
             strcpy(timeProcess[(iNumReport)].szrealTimeDurationFormatted,pszrealTimeDurationFormatted);
          }

	  void setStartRealTimeFormatted(char * pszTimeStart) {
             strcpy(timeProcess[(iNumReport)].szTimeStart,pszTimeStart);
          }

	  void setEndRealTimeFormatted(char * pszTimeEnd) {
             strcpy(timeProcess[(iNumReport)].szTimeEnd,pszTimeEnd);
          }

	  void setStartCPUTime(clock_t startCPUTime) {
             timeProcess[(iNumReport)].startCPUTime = startCPUTime;
          }

	  void setEndCPUTime(clock_t endCPUTime) {
             timeProcess[(iNumReport)].endCPUTime = endCPUTime;
          }

	  void setCPUTimeDuration(clock_t CPUTimeDuration) {
             timeProcess[(iNumReport)].CPUTimeDuration = CPUTimeDuration;
          }

          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: Grupo de métodos get
          //
          // Parâmetros: Número da linha do relatório
	  //
	  // Retorno: Campo a ser lido
          //
          // Objetivo: Ler valores campos da estrutura de relatórios
          //
          // Autores: Charles, Zara e Bressane
          //
          // Data: 26/06/23
          ///////////////////////////////////////////////////////////////////////////////////////////
	  int getNumReport() {
	     return(iNumReport);	  
	  }

	  clock_t getStartUserCPUTime(int iNumReport) {
             return(timeProcess[iNumReport].startUserCPUTime);
          }

	  clock_t getEndUserCPUTime(int iNumReport) {
             return(timeProcess[iNumReport].endUserCPUTime);
          }

	  clock_t getStartSystemCPUTime(int iNumReport) {
             return(timeProcess[iNumReport].startSystemCPUTime);
          }

	  clock_t getEndSystemCPUTime(int iNumReport) {
             return(timeProcess[iNumReport].endSystemCPUTime);
          }

	  time_t getStartRealTime(int iNumReport) {
             return(timeProcess[iNumReport].startRealTime);
          }

	  time_t getEndRealTime(int iNumReport) {
             return(timeProcess[iNumReport].endRealTime);
          }

	  time_t getStartCPUTime(int iNumReport) {
             return(timeProcess[iNumReport].startCPUTime);
          }

	  time_t getEndCPUTime(int iNumReport) {
             return(timeProcess[iNumReport].endCPUTime);
          }

          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: printReport
          //
          // Parâmetros: NA
	  //
	  // Retorno: NA
          //
          // Objetivo: Imprimir informações dos processos executados, tanto na tela, como também em
	  //           arquivo.
          //
          // Autores: Charles, Zara e Bressane
          //
          // Data: 26/06/23
          ///////////////////////////////////////////////////////////////////////////////////////////
	  void printReport() {
	     FILE    *fpReport;
             struct  tm *ptime;
             time_t  stTempoProcesso;
             int     iData;
             int     iHora;
	     char    szReportFile[500]="\0";
             char    szClassName[50]="\0";
             char    szFileRead[50]="\0";
             int     iNumNodes=0;
             char    szProcessType[50]="\0";
             clock_t userCPUDurationLD;
             clock_t systemDurationLD;
             clock_t CPUTimeDurationLD;
             char    szrealTimeDurationFormattedLD[10]="\0";
             clock_t userCPUDurationDV;
             clock_t systemDurationDV;
             clock_t CPUTimeDurationDV;
             char    szrealTimeDurationFormattedDV[10]="\0";
             clock_t userCPUDurationDH;
             clock_t systemDurationDH;
             clock_t CPUTimeDurationDH;
             char    szrealTimeDurationFormattedDH[10]="\0";

             stTempoProcesso = time( NULL );
             ptime           = localtime(&stTempoProcesso);

             iData=(ptime->tm_year+1900)*10000+(ptime->tm_mon+1)*100+ptime->tm_mday;
             iHora=ptime->tm_hour*10000+ptime->tm_min*100+ptime->tm_sec;

	     sprintf(szReportFile,"%s/grafos.process.report.%d.%06d.csv",szReportPath,iData,iHora);

	     if( (fpReport=fopen(szReportFile,"w"))==NULL )
	     {
	        printf("Erro na abertura do arquivo %s\n",szReportFile);
	        exit(1);
	     }

	     fprintf(fpReport,"Class Name;File Read;Nodes Number;Load User CPU Time;Load System CPU Time;Load CPU Time;Load Real Time;D.Vector User CPU Time;D.Vector System CPU Time;D.Vector CPU Time;D.Vector Real Time;D.Heap User CPU Time;D.Heap System CPU Time;D.Heap CPU Time;D.Heap Real Time\n");
	     int i=0;
	     while(i<iNumReport) {
		strcpy(szClassName,timeProcess[i].szClassName);
	        while( i<iNumReport && strcmp(szClassName,timeProcess[i].szClassName)==0 )  {
		   strcpy(szFileRead,timeProcess[i].szFileRead);	
	           iNumNodes=timeProcess[i].iNumNodes;
                   userCPUDurationLD=0;
                   systemDurationLD=0;
                   strcpy(szrealTimeDurationFormattedLD,"00:00");
                   userCPUDurationDV=0;
                   systemDurationDV=0;
                   strcpy(szrealTimeDurationFormattedDV,"00:00");
                   userCPUDurationDH=0;
                   systemDurationDH=0;
                   strcpy(szrealTimeDurationFormattedDH,"00:00");
	           while(i<iNumReport && strcmp(szClassName,timeProcess[i].szClassName)==0 && strcmp(szFileRead,timeProcess[i].szFileRead)==0 ) { 
		      if(strncmp(timeProcess[i].szProcessType,"Load Graph",10)==0) {
                         userCPUDurationLD=timeProcess[i].userCPUDuration;
                         systemDurationLD=timeProcess[i].systemDuration;
                         CPUTimeDurationLD=timeProcess[i].CPUTimeDuration;
                         strcpy(szrealTimeDurationFormattedLD,timeProcess[i].szrealTimeDurationFormatted);
		      }
	              else
		         if(strncmp(timeProcess[i].szProcessType,"Dijkstra Vector",15)==0) {
                            userCPUDurationDV=timeProcess[i].userCPUDuration;
                            systemDurationDV=timeProcess[i].systemDuration;
                            CPUTimeDurationDV=timeProcess[i].CPUTimeDuration;
                            strcpy(szrealTimeDurationFormattedDV,timeProcess[i].szrealTimeDurationFormatted);
			 }
		         else {
                            userCPUDurationDH=timeProcess[i].userCPUDuration;
                            systemDurationDH=timeProcess[i].systemDuration;
                            CPUTimeDurationDH=timeProcess[i].CPUTimeDuration;
                            strcpy(szrealTimeDurationFormattedDH,timeProcess[i].szrealTimeDurationFormatted);
			 }
	              i++;
		   }
	           fprintf(fpReport,"%s;%s;%d;%ld;%ld;%ld;%s;%ld;%ld;%ld;%s;%ld;%ld;%ld;%s\n",szClassName,
				                                                  szFileRead,
									          iNumNodes,
										  userCPUDurationLD,
										  systemDurationLD,
										  CPUTimeDurationLD,
										  szrealTimeDurationFormattedLD,
										  userCPUDurationDV,
										  systemDurationDV,
										  CPUTimeDurationDV,
										  szrealTimeDurationFormattedDV,
										  userCPUDurationDH,
										  systemDurationDH,
										  CPUTimeDurationDH,
										  szrealTimeDurationFormattedDH);

		}
	     }
	     fclose(fpReport);

          }


          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: sortReport
          //
          // Parâmetros: NA
	  //
	  // Retorno: NA
          //
          // Objetivo: Gera relatório ordenado por numero de nós para cada classe
          //
          // Autores: Charles, Zara e Bressane
          //
          // Data: 26/06/23
          ///////////////////////////////////////////////////////////////////////////////////////////
	  void sortReport() {
             struct TimeProcess classTimeProcess[100];
             struct TimeProcess tempClassTimeProcess[100];
	     int    inClass=0;
	     int    iCurrentPosition=0;
	     int    iClassToSort=0;
	     char   szClassName[50]="\0";

	     while (inClass < iNumReport) {
                struct TimeProcess classTimeProcess[100];

		iClassToSort=0;

	        // Separar por classe para ordenar
		strcpy(szClassName,timeProcess[inClass].szClassName);
	        while (inClass < iNumReport && strcmp(szClassName,timeProcess[inClass].szClassName)==0) {

	            strcpy(classTimeProcess[iClassToSort].szClassName,timeProcess[inClass].szClassName);
	            strcpy(classTimeProcess[iClassToSort].szFileRead,timeProcess[inClass].szFileRead);
	            classTimeProcess[iClassToSort].iNumNodes=timeProcess[inClass].iNumNodes;
	            strcpy(classTimeProcess[iClassToSort].szProcessType,timeProcess[inClass].szProcessType);

	            classTimeProcess[iClassToSort].startUserCPUTime=timeProcess[inClass].startUserCPUTime;
	            classTimeProcess[iClassToSort].endUserCPUTime=timeProcess[inClass].endUserCPUTime;
	            classTimeProcess[iClassToSort].userCPUDuration=timeProcess[inClass].userCPUDuration;

	            classTimeProcess[iClassToSort].startSystemCPUTime=timeProcess[inClass].startSystemCPUTime;
	            classTimeProcess[iClassToSort].endSystemCPUTime=timeProcess[inClass].endSystemCPUTime;
	            classTimeProcess[iClassToSort].systemDuration=timeProcess[inClass].systemDuration;

	            classTimeProcess[iClassToSort].startCPUTime=timeProcess[inClass].startCPUTime;
	            classTimeProcess[iClassToSort].endCPUTime=timeProcess[inClass].endCPUTime;
	            classTimeProcess[iClassToSort].CPUTimeDuration=timeProcess[inClass].CPUTimeDuration;

	            classTimeProcess[iClassToSort].startRealTime=timeProcess[inClass].startRealTime;
	            classTimeProcess[iClassToSort].endRealTime=timeProcess[inClass].endRealTime;

	            strcpy(classTimeProcess[iClassToSort].szTimeStart,timeProcess[inClass].szTimeStart);
	            strcpy(classTimeProcess[iClassToSort].szTimeEnd,timeProcess[inClass].szTimeEnd);

	            classTimeProcess[iClassToSort].realTimeDuration=timeProcess[inClass].realTimeDuration;
	            strcpy(classTimeProcess[iClassToSort].szrealTimeDurationFormatted,timeProcess[inClass].szrealTimeDurationFormatted);

		    inClass++;
		    iClassToSort++;
                }
		
                // Ordernar por numero de nodes, classe separada no loop anterior
  	        sortByField(classTimeProcess, iClassToSort);

	        moveToTemp(classTimeProcess, tempClassTimeProcess, iClassToSort, &iCurrentPosition );

	     }

	     updateReport( tempClassTimeProcess, timeProcess, iCurrentPosition );

	  }

          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: updateReport
          //
          // Parâmetros: updatedReport - versao final do relatorio ordenado.
	  //             newReport - versao anterior a ordenação que receberá o updatedReport.
	  //             iCurrentPosition - quantidade de registros no relatório
	  //
	  // Retorno: NA
          //
          // Objetivo: Gerar versão final do relatório ordenado por iNumNodes.
          //
          // Autores: Charles, Zara e Bressane
          //
          // Data: 26/06/23
          ///////////////////////////////////////////////////////////////////////////////////////////
	  void updateReport( struct TimeProcess* updatedReport, struct TimeProcess* newReport, int iCurrentPosition ) {

                for (int i=0;i<iCurrentPosition ;i++) {
	            strcpy(newReport[i].szClassName,updatedReport[i].szClassName);
	            strcpy(newReport[i].szFileRead,updatedReport[i].szFileRead);
	            newReport[i].iNumNodes=updatedReport[i].iNumNodes;
	            strcpy(newReport[i].szProcessType,updatedReport[i].szProcessType);

	            newReport[i].startUserCPUTime=updatedReport[i].startUserCPUTime;
	            newReport[i].endUserCPUTime=updatedReport[i].endUserCPUTime;
	            newReport[i].userCPUDuration=updatedReport[i].userCPUDuration;

	            newReport[i].startSystemCPUTime=updatedReport[i].startSystemCPUTime;
	            newReport[i].endSystemCPUTime=updatedReport[i].endSystemCPUTime;
	            newReport[i].systemDuration=updatedReport[i].systemDuration;

	            newReport[i].startCPUTime=updatedReport[i].startCPUTime;
	            newReport[i].endCPUTime=updatedReport[i].endCPUTime;
	            newReport[i].CPUTimeDuration=updatedReport[i].CPUTimeDuration;

	            newReport[i].startRealTime=updatedReport[i].startRealTime;
	            newReport[i].endRealTime=updatedReport[i].endRealTime;

	            strcpy(newReport[i].szTimeStart,updatedReport[i].szTimeStart);
	            strcpy(newReport[i].szTimeEnd,updatedReport[i].szTimeEnd);

	            newReport[i].realTimeDuration=updatedReport[i].realTimeDuration;
	            strcpy(newReport[i].szrealTimeDurationFormatted,updatedReport[i].szrealTimeDurationFormatted);
		}

	  }


          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: swap
          //
          // Parâmetros: a - Estrutura com tempo de processamento origem 
	  //             b - Estrutura com tempo de processamento destino
	  //
	  // Retorno: NA
          //
          // Objetivo: Troca item da estrutura na ordenacao
          //
          // Autores: Charles, Zara e Bressane
          //
          // Data: 26/06/23
          ///////////////////////////////////////////////////////////////////////////////////////////
	  void swap(struct TimeProcess* a, struct TimeProcess* b) {
             struct TimeProcess temp = *a;
             *a = *b;
             *b = temp;
	  }

          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: sortByField
          //
          // Parâmetros: arr[] - Estrutura a ser ordenada
	  //             size - Quantidade de registros na estrutura
	  //
	  // Retorno: NA
          //
          // Objetivo: Troca item da estrutura na ordenacao
          //
          // Autores: Charles, Zara e Bressane
          //
          // Data: 26/06/23
	  // ///////////////////////////////////////////////////////////////////////////////////////
	  void sortByField(struct TimeProcess arr[], int size) {
             for (int i = 0; i < size - 1; ++i) {
                for (int j = 0; j < size - i - 1; ++j) {

		   if (arr[j].iNumNodes > arr[j + 1].iNumNodes) 
		      swap(&arr[j], &arr[j + 1]);
						
		}
             }

	  }

          ///////////////////////////////////////////////////////////////////////////////////////////
          // Método: moveToTemp
          //
          // Parâmetros: pclassTimeProcess - estrutura ordenada para determinada classe
	  //             ptempClassTimeProcess - estrutura temporária com todas ordenações
	  //             iClassToSort - número de registros já ordenados
	  //             piCurrentPosition - posição corrente marcando até que ponto foi ordenado
	  //
	  // Retorno: NA
          //
          // Objetivo: Movimentação dos registros já ordenados para uma estrutura temporária
          //
          // Autores: Charles, Zara e Bressane
          //
          // Data: 26/06/23
	  // ///////////////////////////////////////////////////////////////////////////////////////
	  void moveToTemp( struct TimeProcess* pclassTimeProcess, struct TimeProcess* ptempClassTimeProcess, int iClassToSort, int *piCurrentPosition ) {
             int iCurrentPosition = *piCurrentPosition;
             for (int i=0; i < iClassToSort; i++) {

	        strcpy(ptempClassTimeProcess[iCurrentPosition].szClassName,pclassTimeProcess[i].szClassName);
	        strcpy(ptempClassTimeProcess[iCurrentPosition].szFileRead,pclassTimeProcess[i].szFileRead);
	        ptempClassTimeProcess[iCurrentPosition].iNumNodes=pclassTimeProcess[i].iNumNodes;
	        strcpy(ptempClassTimeProcess[iCurrentPosition].szProcessType,pclassTimeProcess[i].szProcessType);

	        ptempClassTimeProcess[iCurrentPosition].startUserCPUTime=pclassTimeProcess[i].startUserCPUTime;
	        ptempClassTimeProcess[iCurrentPosition].endUserCPUTime=pclassTimeProcess[i].endUserCPUTime;
	        ptempClassTimeProcess[iCurrentPosition].userCPUDuration=pclassTimeProcess[i].userCPUDuration;

	        ptempClassTimeProcess[iCurrentPosition].startSystemCPUTime=pclassTimeProcess[i].startSystemCPUTime;
	        ptempClassTimeProcess[iCurrentPosition].endSystemCPUTime=pclassTimeProcess[i].endSystemCPUTime;
	        ptempClassTimeProcess[iCurrentPosition].systemDuration=pclassTimeProcess[i].systemDuration;

	        ptempClassTimeProcess[iCurrentPosition].startCPUTime=pclassTimeProcess[i].startCPUTime;
	        ptempClassTimeProcess[iCurrentPosition].endCPUTime=pclassTimeProcess[i].endCPUTime;
	        ptempClassTimeProcess[iCurrentPosition].CPUTimeDuration=pclassTimeProcess[i].CPUTimeDuration;

	        ptempClassTimeProcess[iCurrentPosition].startRealTime=pclassTimeProcess[i].startRealTime;
	        ptempClassTimeProcess[iCurrentPosition].endRealTime=pclassTimeProcess[i].endRealTime;

	        strcpy(ptempClassTimeProcess[iCurrentPosition].szTimeStart,pclassTimeProcess[i].szTimeStart);
	        strcpy(ptempClassTimeProcess[iCurrentPosition].szTimeEnd,pclassTimeProcess[i].szTimeEnd);

	        ptempClassTimeProcess[iCurrentPosition].realTimeDuration=pclassTimeProcess[i].realTimeDuration;
	        strcpy(ptempClassTimeProcess[iCurrentPosition].szrealTimeDurationFormatted,pclassTimeProcess[i].szrealTimeDurationFormatted);
		iCurrentPosition++;

	     }
	     *piCurrentPosition=iCurrentPosition;

	  }


	private:
 	  struct TimeProcess timeProcess[300];
	  char szReportPath[200]="\0";
	  int iNumReport=0;


};
