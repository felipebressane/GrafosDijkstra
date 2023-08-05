///////////////////////////////////////////////////////////////////////////////////////////
// Programa: treatment.graph.cpp
//
// Objetivo: Carregar Grafos e calcular distâncias mínimas
//
// Classes com interface: NA
//
// Autores: Charles, Zara e Bressane
//
// Data: 02/07/23
///////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/vertex.h"
#include "../include/graph.h"
#include "../include/fileconfig.h"
#include "../include/report.grafo.h"
#include <sys/times.h>
#include <time.h>

void fExecGroup( char *, char *, int, int, char *, Reportgraph *i, int );
int  fGetNumNodes( char *, int, int, char * );
void fsetInfoReports( Reportgraph *,  char *, char *, char *, int, struct tms *, bool );



int main( int argc, char *argv[] )
{
   int numConfigs = 0;
   int typeDijkstra=atoi(argv[1]);

   Fileconfig fileconfig(argv[2]);

   Reportgraph reportgraph(argv[3]);

   numConfigs=fileconfig.fgetNumberConfigs();

   for ( int currentConfig=0; currentConfig < numConfigs; currentConfig++ )
   {

     if(fileconfig.fgetIsActived(currentConfig))
     {
         fExecGroup(fileconfig.fgetClassName(currentConfig),
	            fileconfig.fgetPathName(currentConfig),
		    fileconfig.fgetFirstLine(currentConfig),
		    fileconfig.fgetNodeLine(currentConfig),
		    fileconfig.fgetRule(currentConfig),
		    &reportgraph,typeDijkstra);
     }

   } 

//   reportgraph.sortReport();

   reportgraph.printReport();

   exit(0);
}


///////////////////////////////////////////////////////////////////////////////////////////
// Função: fExecGroup
//
// Parâmetros: pszClassNam - Nome da classe
//             pszPathName - Nome do diretório aonde localizados os arquivos
//             iFirstLine  - Número da primeira linha de nós
//             iNodeLine - Linha com o número de nós
//             pszRule - Informa se o primeiro caractere de cada linha corresponde a uma 
//                       regra
//             iTypeDijkstra - Tipo de Dijkstra que deve ser executado (vector, headp ou 
//                             ambos)
// Retôrno: Total de nós
//
// Objetivo: Obter o total de nós do arquivo
//
// Autores: Charles, Zara e Bressane
//
// Data: 02/07/23
///////////////////////////////////////////////////////////////////////////////////////////
void fExecGroup( char *pszClassName, char *pszPathName, int iFirstLine, int iNodeLine, char *pszRule, Reportgraph *pReportgraph, int iTypeDijkstra )
{

   DIR *szdirNetwork;
   struct dirent *strdirNetworks;
   char szFullPath[300]="\0";
   FILE *fpDataFile;
   char szLine[100]="\0";
   int  iLine=0;
   char szDummy[10]="\0";
   char szCode[5]="\0";
   int  iNodeOrigin=0;
   int  iNodeTarget=0;
   int  iWeigth=0; 
   int  iNodeOriginBefore=-1;
   int  iNodeTargetBefore=-1;
   int  iWeigthBefore=-1;
   int  iNumNodes=0;
   bool next=0;
   bool firstRead=1;
   bool lessOne=0;
   bool treatLine=0;
   char szProcessType[50]="\0";
   struct tms tmsprocess;
   clock_t timeProcess;
   bool    EndProcess=false;
   Graph *graph;

   szdirNetwork=opendir(pszPathName);

   while((strdirNetworks=readdir(szdirNetwork))!=NULL)
   {
      if(strdirNetworks->d_name[0] != '.')
      {
         sprintf(szFullPath,"%s/%s",pszPathName,strdirNetworks->d_name);

	 if( (fpDataFile=fopen(szFullPath,"r")) != NULL)
	 {

            // Pegar o numero de nos
	    iNumNodes=fGetNumNodes( szFullPath, iNodeLine, iFirstLine, pszRule );

	    // Instanciar Grafo
	    graph = new Graph( iNumNodes );

            // Registrar o tempo de carga dos grafos
	    strcpy(szProcessType,"Load Graph");
	    timeProcess = times(&tmsprocess);
	    EndProcess = false;
            fsetInfoReports( pReportgraph, szProcessType, pszClassName, strdirNetworks->d_name, iNumNodes, &tmsprocess, EndProcess );
            ////////////////////////////////////////

            fgets(szLine,100,fpDataFile);
            while(!feof(fpDataFile))
	    {
	       iLine++;
	       
	       if(iLine>=iFirstLine)
	       {

		 // Definir quais as linhas dos arquivos que serão carregadas nos grafos de acordo com 
		 // suas caracteristicas      
		 treatLine=0;      
		 if(strncmp(pszRule,"X",1)==0 && strncmp(szLine,"E",1)!=0 && strncmp(szLine,"<",1)!=0) // Para as classes test_set1 e test_set2
		    treatLine=1;
	         else		 
		    if(strncmp(szLine,"E ",2)==0) // Para as classes ALUE, ALUT e DMXA
                       treatLine=1;

	         if(treatLine)
		 {	 
	            // Se a classe não tiver regra, pegar as tres colunas (origem, destino e peso)
		    // Senão pegar as quatros colunas mas descartando a primeira
		    if(strncmp(pszRule,"X",1)==0 )
	                sscanf(szLine,"%d %d %d",&iNodeOrigin,&iNodeTarget,&iWeigth);
		    else
	                sscanf(szLine,"%s %d %d %d",szCode,&iNodeOrigin,&iNodeTarget,&iWeigth);

		    // Verficar na primeira linhas dos nodes, se tem node com 0 na origem ou destino
		    // Se não tiver 0, a partir dessa linha sempre tirar de um verificando a variável
		    // lessOne

	            if(firstRead)
		    {
                       firstRead=0;
                       if(iNodeOrigin!=0 && iNodeTarget!=0)
			 lessOne=1;
		    } 

		    if(lessOne)
		    {
	              iNodeOrigin--;
		      iNodeTarget--;
		    }

		    // Verificar se os novos nós são invertidos. Se não forem inverter e registrar junto com os pesos
                    if(iNodeOriginBefore!=-1 && iNodeTargetBefore!=-1 && strncmp(pszRule,"E",1)==0)
		    {
                       graph->addEdge(iNodeTargetBefore,iNodeOriginBefore,iWeigthBefore);
                    }

                    // Registrar os nodes e pesos
                    graph->addEdge(iNodeOrigin,iNodeTarget,iWeigth);

		    // Guardar os nós para verificar se na próxima leitura os nós invertidos existem 
                    iNodeOriginBefore=iNodeOrigin;
                    iNodeTargetBefore=iNodeTarget;		    
		    iWeigthBefore=iWeigth;

		 }

	       }
               fgets(szLine,100,fpDataFile);
	    }

	    // Para tratar o último lido após Loop
	    if(iNodeOriginBefore!=-1 && iNodeTargetBefore!=-1 && strncmp(pszRule,"E",1)==0)
               graph->addEdge(iNodeTargetBefore,iNodeOriginBefore,iWeigthBefore);

	    fclose(fpDataFile);
	    timeProcess = times(&tmsprocess);
	    EndProcess = true;
            fsetInfoReports( pReportgraph, szProcessType, pszClassName, strdirNetworks->d_name, iNumNodes, &tmsprocess, EndProcess );

            std::cout << "Grafo relativo ao arquivo " << strdirNetworks->d_name << "\n";
            graph->printGraph();
	    std::cout << "\n";

	    ///////////////////////////////////////////////////
            // Execução do algoritmo Dijkstra com vetor
            ///////////////////////////////////////////////////
	    if(iTypeDijkstra==1 || iTypeDijkstra==3) {
	       // Tomada de tempo inicial
	       strcpy(szProcessType,"Dijkstra Vector");
	       timeProcess = times(&tmsprocess);
	       EndProcess = false;
               fsetInfoReports( pReportgraph, szProcessType, pszClassName, strdirNetworks->d_name, iNumNodes, &tmsprocess, EndProcess );

               graph->dijkstra(0);

	       // Tomada de tempo final
	       timeProcess = times(&tmsprocess);
	       EndProcess = true;
               fsetInfoReports( pReportgraph, szProcessType, pszClassName, strdirNetworks->d_name, iNumNodes, &tmsprocess, EndProcess );
            }
	    ////////////////////////////////////////////////////


	    ////////////////////////////////////////////////////
            // Execução do algoritmo Dijkstra com Heap Binário
            ////////////////////////////////////////////////////
            if(iTypeDijkstra==2 || iTypeDijkstra==3) {
	       // Tomada de tempo inicial
	       strcpy(szProcessType,"Dijkstra Heap");
	       timeProcess = times(&tmsprocess);
	       EndProcess = false;
               fsetInfoReports( pReportgraph, szProcessType, pszClassName, strdirNetworks->d_name, iNumNodes, &tmsprocess, EndProcess );

               graph->dijkstraheap(0);

	       // Tomada de tempo final
	       timeProcess = times(&tmsprocess);
	       EndProcess = true;
               fsetInfoReports( pReportgraph, szProcessType, pszClassName, strdirNetworks->d_name, iNumNodes, &tmsprocess, EndProcess );
            }
	    ////////////////////////////////////////////////////

            delete graph;

	 }

      }
      
   }

}	

///////////////////////////////////////////////////////////////////////////////////////////
// Função: fGetNumNodes
//
// Parâmetros: pszFullPath - Nome da arquivo a ser lido
//             iNodeLine - Número da linha com o total de nós
//             iFirstLine - Primeira linha de nós
//             pszRule - Informa de o primeiro caracter da linha correponde a uma regra
//
// Retôrno: Total de nós
//
// Objetivo: Obter o total de nós do arquivo
//
// Autores: Charles, Zara e Bressane
//
// Data: 02/07/23
///////////////////////////////////////////////////////////////////////////////////////////
int fGetNumNodes( char *pszFullPath, int iNodeLine, int iFirstLine, char *pszRule )
{
    FILE *fpDataFile;
    char szLine[100]="\0";
    int  iLine=0;
    char szDummy[10]="\0";
    int  iNumNodes=0;
    char szCode[5]="\0";
    int  iNodeOrigin=0;
    int  iNodeTarget=0;
    int  iWeigth=0;
    bool setNodes[100000]={false};

    if( (fpDataFile=fopen(pszFullPath,"r")) != NULL)
    {
        fgets(szLine,100,fpDataFile);
        while(!feof(fpDataFile))
        {

           iLine++;
	   if(strncmp(pszRule,"X",1)==0)
           {
               if(iLine==iNodeLine)
               {         
                  sscanf(szLine,"%s %d",szDummy,&iNumNodes);
	          break;
               }
	   }
	   else		 
	       if(iLine>=iFirstLine)
	       {
	          if(strncmp(szLine,"E ",2)==0)
	          { 
	             sscanf(szLine,"%s %d %d %d",szCode,&iNodeOrigin,&iNodeTarget,&iWeigth);
                     if(!setNodes[iNodeOrigin])	             
	             {
			setNodes[iNodeOrigin]=true;
                        iNumNodes++; 
	             }
                     if(!setNodes[iNodeTarget])	             
	             {
			setNodes[iNodeTarget]=true;
                        iNumNodes++; 
	             }
		  }
	       }

           fgets(szLine,100,fpDataFile);
        }
        fclose(fpDataFile);
    }
    return(iNumNodes);
}


///////////////////////////////////////////////////////////////////////////////////////////
// Função: fsetInfoReports
//
// Parâmetros: pReportgraph - Objeto relatório
//             pszProcessType - Tipo de execução
//             pszClassName - Nome da classe
//             pszFileRead - Arquivo lido
//             iNumNodes - Quantidade de nós no arquivo
//             tmsprocess - Tempo de processamento
//             EndProcess - Informa se é o fim do processo
//
// Retorno: NA
//
// Objetivo: Registrar informações de processamento para gerar relatório
//
// Autores: Charles, Zara e Bressane
//
// Data: 02/07/23
///////////////////////////////////////////////////////////////////////////////////////////
void fsetInfoReports( Reportgraph *pReportgraph, char *pszProcessType, char *pszClassName, char *pszFileRead, int iNumNodes, struct tms *tmsprocess, bool EndProcess ) 
{
    struct tm *ptime;
    time_t TimeProcessReal;
    time_t TimeProcessDuration;


    // Registra a parte inicial de cada processo (carga, Dijkstra Vector e Dijkstra Heap)
    if (!EndProcess) {
       char szTimeStart[12]="\0";

       pReportgraph->setProcessType(pszProcessType);
       pReportgraph->setClassName(pszClassName);
       pReportgraph->setFileRead(pszFileRead);
       pReportgraph->setNumberNodes(iNumNodes);

       ////////////////////
       // Tempos iniciais
       // /////////////////

       // Medição do tempos em ticks
       pReportgraph->setStartUserCPUTime(tmsprocess->tms_utime);
       pReportgraph->setStartSystemCPUTime(tmsprocess->tms_stime);
       pReportgraph->setStartCPUTime(clock());

       // Medição do tempos em segundos
       time(&TimeProcessReal);
       pReportgraph->setStartRealTime(TimeProcessReal);

       // Medição do tempos em segundos formatados
       ptime=localtime(&TimeProcessReal);
       sprintf(szTimeStart,"%02d:%02d:%02d",ptime->tm_hour,ptime->tm_min,ptime->tm_sec); 
       pReportgraph->setStartRealTimeFormatted(szTimeStart);
    }
    else
    {

    // Registra a parte final de cada processo (carga, Dijkstra Vector e Dijkstra Heap)
       int  NumReport=pReportgraph->getNumReport();
       char szTimeDuration[10]="\0";
       char szTimeEnd[12]="\0";

       ////////////////////
       // Tempos finais
       // /////////////////

       // Medição do tempos em ticks
       pReportgraph->setEndUserCPUTime(tmsprocess->tms_utime);
       pReportgraph->setEndSystemCPUTime(tmsprocess->tms_stime);
       pReportgraph->setEndCPUTime(clock());

       // Cálculo das durações em ticks
       pReportgraph->setUserCPUDuration( (pReportgraph->getEndUserCPUTime(NumReport)-pReportgraph->getStartUserCPUTime(NumReport)) );
       pReportgraph->setSystemDuration( (pReportgraph->getEndSystemCPUTime(NumReport)-pReportgraph->getStartSystemCPUTime(NumReport)) );
       pReportgraph->setCPUTimeDuration( (pReportgraph->getEndCPUTime(NumReport)-pReportgraph->getStartCPUTime(NumReport)) );

       // Medição do tempos em segundos formatados e cálculo das durações
       time(&TimeProcessReal);
       pReportgraph->setEndRealTime(TimeProcessReal);
       TimeProcessDuration=(pReportgraph->getEndRealTime(NumReport) - pReportgraph->getStartRealTime(NumReport));

       pReportgraph->setRealTimeDuration(TimeProcessDuration);
       ptime=localtime(&TimeProcessDuration);
       sprintf(szTimeDuration,"%02d:%02d",ptime->tm_min,ptime->tm_sec); 
       pReportgraph->setrealTimeDurationFormatted(szTimeDuration);

       // Medição do tempos em segundos formatados
       ptime=localtime(&TimeProcessReal);
       sprintf(szTimeEnd,"%02d:%02d:%02d",ptime->tm_hour,ptime->tm_min,ptime->tm_sec); 
       pReportgraph->setEndRealTimeFormatted(szTimeEnd);

       pReportgraph->incrementNumReport();
    }

}
