///////////////////////////////////////////////////////////////////////////////////////////
// Classe: Fileconfig
//
// Objetivo: Instanciar arquivo de configurações para acessar e tratar arquivos com 
//           vértices.
//
// Classes com interface: NA
//
// Autores: Charles, Zara e Bressane
//
// Data: 03/07/23
///////////////////////////////////////////////////////////////////////////////////////////
#include <cstring>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

struct configs {
   char szClassName[30]="\0";
   char szPathName[200]="\0";
   char szRule[2]="\0";
   int  iNodeLine=0;
   int  iFirstLine=0;
   int  iIsActived=0;
};


class Fileconfig {

public:

    ////////////////////////////////////////////////////////////////////////////////////////
    // Método: Construtores
    ////////////////////////////////////////////////////////////////////////////////////////
    Fileconfig( char *pszNameFileConfig )
    {
       FILE *fpConfig;
       char szNameFileConfig[100]="\0";
       char szClassName[30]="\0";
       char szPathName[200]="\0";
       char szRule[2]="\0";
       int  iNodeLine=0;
       int  iFirstLine=0;
       int  iIsActived=0;
       char szLine[100]="\0";

       if( (fpConfig=fopen(pszNameFileConfig,"r"))!=NULL )
       {	       

	  fgets(szLine,100,fpConfig);
          while(!feof(fpConfig))
          {

	     if(strncmp(szLine,"#",1)!=0)
	     {	     

                 sscanf(szLine,"%s %s %s %d %d %d",szClassName,szPathName,szRule,&iNodeLine,&iFirstLine,&iIsActived);

	         iNumberConfigs++;

                 strcpy(stConfigs[(iNumberConfigs-1)].szClassName,szClassName);
                 strcpy(stConfigs[(iNumberConfigs-1)].szPathName,szPathName);
                 strcpy(stConfigs[(iNumberConfigs-1)].szRule,szRule);
                 stConfigs[(iNumberConfigs-1)].iNodeLine  = iNodeLine;
                 stConfigs[(iNumberConfigs-1)].iFirstLine = iFirstLine;
                 stConfigs[(iNumberConfigs-1)].iIsActived = iIsActived;

             }

	     fgets(szLine,100,fpConfig);

          }
          fclose(fpConfig);

       }
       else
          cout << "Erro ao abrir arquivo " << pszNameFileConfig << "\n";

    }


    ////////////////////////////////////////////////////////////////////////////////////////
    // Método: fgetClassName
    //
    // Parâmetros: iNumberConfig - Número da configuração a ser utilizada
    //
    // Retorno:  szClassName
    //
    // Objetivo: Resgatar ClassName
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 03/07/23
    ////////////////////////////////////////////////////////////////////////////////////////
    char *fgetClassName( int iNumberConfig ) {
	     return(stConfigs[iNumberConfig].szClassName);
	  }


    ////////////////////////////////////////////////////////////////////////////////////////
    // Método: fgetPathName
    //
    // Parâmetros: iNumberConfig - Número da configuração a ser utilizada
    //
    // Retorno:  szPathName
    //
    // Objetivo: Resgatar PathName
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 03/07/23
    ////////////////////////////////////////////////////////////////////////////////////////
    char *fgetPathName( int iNumberConfig ) {
	     return(stConfigs[iNumberConfig].szPathName);
	  }


    ////////////////////////////////////////////////////////////////////////////////////////
    // Método: fgetRule
    //
    // Parâmetros: iNumberConfig - Número da configuração a ser utilizada
    //
    // Retorno:  szRule
    //
    // Objetivo: Resgatar regra a ser utilizada no inicio das linhas dos nodes 
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 03/07/23
    ////////////////////////////////////////////////////////////////////////////////////////
    char *fgetRule( int iNumberConfig ) {
	     return(stConfigs[iNumberConfig].szRule);
	  }


    ////////////////////////////////////////////////////////////////////////////////////////
    // Método: fgetNodeLine
    //
    // Parâmetros: iNumberConfig - Número da configuração a ser utilizada
    //
    // Retorno:  iNodeLine
    //
    // Objetivo: Resgatar número da linhas com o total de Nodes
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 03/07/23
    ////////////////////////////////////////////////////////////////////////////////////////
    int   fgetNodeLine( int iNumberConfig ) {
	     return(stConfigs[iNumberConfig].iNodeLine);
          }


    ////////////////////////////////////////////////////////////////////////////////////////
    // Método: fgetFirstLine
    //
    // Parâmetros: iNumberConfig - Número da configuração a ser utilizada
    //
    // Retorno:  iFirstLine
    //
    // Objetivo: Resgatar número da primeira linha dos Nodes em um arquivo.
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 03/07/23
    ////////////////////////////////////////////////////////////////////////////////////////
    int   fgetFirstLine( int iNumberConfig ) {
	     return(stConfigs[iNumberConfig].iFirstLine);
          }


    ////////////////////////////////////////////////////////////////////////////////////////
    // Método: fgetIsActived
    //
    // Parâmetros: iNumberConfig - Número da configuração a ser utilizada
    //
    // Retorno:  iIsActived
    //
    // Objetivo: Resgatar se a Classe em questão está ativa (1) ou não (0) para ser tratada
    //           pelo processo.
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 03/07/23
    ////////////////////////////////////////////////////////////////////////////////////////
    int   fgetIsActived( int iNumberConfig ) {
	     return(stConfigs[iNumberConfig].iIsActived);
          }


    ////////////////////////////////////////////////////////////////////////////////////////
    // Método: fgetNumberConfigs
    //
    // Parâmetros: NA
    //
    // Retorno:  iNumberConfigs
    //
    // Objetivo: Resgatar número de configurações existentes.
    //
    // Autores: Charles, Zara e Bressane
    //
    // Data: 03/07/23
    ////////////////////////////////////////////////////////////////////////////////////////
    int   fgetNumberConfigs() {
	     return(iNumberConfigs);
          }

    
private:
    char *szNameFileConfig;
    struct configs stConfigs[90];
    int  iNumberConfigs=0;

};

