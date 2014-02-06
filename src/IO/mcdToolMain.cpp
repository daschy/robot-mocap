#include<iostream>
#include <MyConfigParser/MyConfigParser.h>

#include"IOMCD.h"
#include"IOMMD.h"

#include<Headers/MACROS.h>

using namespace std;


void usage(){
 cout << "Usage -i -fA -fB [-ho]:\n"
      << " -h                               : This help\n" 
      << " -i <input>                       : input file.\n" 
      << " -a <initial frame>              : frame iniziale.\n"
      << " -b <final frame>                : frame finale.\n"
      << " -o <output>                      : file di output, se non specificato l'output verrà scritto nel file di input"
      << endl;
}


void cutFrames(int initialFrame, int finalFrame, IOMCD* fil){

   int frameRate = fil->getFramerate();
  int numMarkers = fil->getNumMarkers();

  map<int,vector<RotationInt> > data = fil->getData();
  

  map<int,vector<RotationInt> >::iterator initial= data.find(initialFrame);

  map<int,vector<RotationInt> >::iterator final= data.find(finalFrame), it;
  if(final!= data.end()) final++;

  fil->eraseData();

  for(it=initial;it!=(final);it++){
    fil->addFrame(it->second);
  }
  fil->setFramerate(frameRate);
  fil->setNumMarkers(numMarkers);
  
}

int main(int argc, char *argv[]) { 
  

  IOMCD* fil;
  char inputFile[256] ="";
  char outputFile[256]="";
  int initialFrame=-1, finalFrame=-1;
  int i;
  opterr = 0;	 /* don't want writing to stderr */
  
  
  
  while ( (i = getopt(argc, argv, "hi:a:b:o:")) != -1) {
    switch (i)
    {
      case 'h':   /* help option */
	usage();
	exit(EXIT_SUCCESS);
	break;
	
      case 'i':
	  strcpy(inputFile, optarg);
	 break;
      case 'o':
	strcpy(outputFile, optarg);
	break;
      case 'a': 
	initialFrame=strtol(optarg, NULL, 10);
	 break;
      case 'b': 
	finalFrame=strtol(optarg, NULL, 10);
	break;
      case '?':   /* unrecognized options */
	  //      printf("Unrecognized options -%c\n",optopt);
	  usage();
	  return EXIT_FAILURE;
	break;
      default:    /* should not reached */
	  usage();
	  return EXIT_SUCCESS;
	break;
    }
  }
  
  //fare controlli
  if(strcmp(inputFile,"")==0){
    cerr << "Input File not defined" << endl;
    usage();
    return EXIT_FAILURE;
  }
  
  if(initialFrame<0){
    cerr << "Initial Frame not valid" << endl;
    usage();
    return EXIT_FAILURE;
  }
   
  if(finalFrame<0){
    cerr << "Final Frame not valid" << endl;
    usage();
    return EXIT_FAILURE;
  }
  

  DEBOUT(("\nfile input %s\nfile output %s\ninitial Frame %d\nfinal Frame %d\n",inputFile,outputFile,initialFrame,finalFrame));
  
  //creare IOMCD
  fil = new IOMCD("",0,0);
 
  //importare data da inputFile
   fil->importData(inputFile);
  
//tagliare la sezione specificata
  cutFrames(initialFrame,finalFrame,fil);



  //controllare se outputFile è definito: se si scrivere in outputFile altrimenti scrivere su inputFile
  if(strcmp(outputFile,"")==0){
    fil->writeData(inputFile);
  }
  else{
     fil->writeData(outputFile);
  }
  
  
  //   DEBOUT(("data size = %d numFrames = %d\n", data.size(), fil->getNumFrames()));
  
  
  
}
