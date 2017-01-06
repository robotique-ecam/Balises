
/*Ici nous codons toutes les méthodes necessaires*/



#ifndef _METHODES_
#define _METHODES_
//Prototypage
//void MirfInit(cePin, csnPin, iTaille MAX 32, sAEcouter*MAX 5, sEmise);
void MirfInit(int cePin, int csnPin, int iTaille, byte * sAEcouter1, byte * sEmise);
void MirfInit(int cePin, int csnPin, int iTaille, byte * sAEcouter1, byte * sAEcouter2, byte * sEmise);
void MirfInit(int cePin, int csnPin, int iTaille, byte * sAEcouter1, byte * sAEcouter2, byte * sAEcouter3, byte * sEmise);
void MirfInit(int cePin, int csnPin, int iTaille, byte * sAEcouter1, byte * sAEcouter2, byte * sAEcouter3, byte * sAEcouter4, byte * sEmise);
void MirfInit(int cePin, int csnPin, int iTaille, byte * sAEcouter1, byte * sAEcouter2, byte * sAEcouter3, byte * sAEcouter4, byte * sAEcouter5, byte * sEmise);
void mProtocoleEmetteur();




// Declaration
void MirfInit(int cePinm, int csnPinm, int iTaille, byte * sAEcouter1, byte * sEmise){
  Mirf.cePin = cePinm;
  Mirf.csnPin = csnPinm;
  
  Mirf.spi = &MirfHardwareSpi; // utilisation du port SPI hardware 
  Mirf.init(); // initialise le module SPI 

  Mirf.payload = iTaille; //  déclaration taille du message à transmettre, max 32 octets 
  // RF_SETUP=0000abcd : a=1–>2Mb/s, a=0–>1Mb/s; puissance émission bc=00–>-18 dBm, bc=01–>-12dBm, bc=10–>-6dBm, bc=11–>0dBm; 
  // d=0 pas de gain sur le bruit en réception 
  /* Non Necessaire
  Mirf.configRegister(RF_SETUP, 0x06); // 1 Mb/s et 0 dBm (puissance maximum)
  */ 
  Mirf.config(); // configure le canal et la taille du message 
  Mirf.setTADDR(sEmise); // définition adresse sur 5 octets pour moi
  Mirf.setMultiRADDR(sAEcouter1,1);  // définition adresse sur 5 octets des autres   
}
void MirfInit(int cePin,int csnPin, int iTaille, byte * sAEcouter1, byte * sAEcouter2, byte * sEmise){
  MirfInit(cePin, csnPin, iTaille, sAEcouter1, sEmise);
  Mirf.setMultiRADDR(sAEcouter2,2); 
}
void MirfInit(int cePin,int csnPin, int iTaille, byte * sAEcouter1, byte * sAEcouter2, byte * sAEcouter3, byte * sEmise){
  MirfInit(cePin, csnPin, iTaille, sAEcouter1, sAEcouter2, sEmise);
  Mirf.setMultiRADDR(sAEcouter3,3);  
}
void MirfInit(int cePin,int csnPin, int iTaille, byte * sAEcouter1, byte * sAEcouter2, byte * sAEcouter3, byte * sAEcouter4, byte * sEmise){
  MirfInit(cePin, csnPin, iTaille, sAEcouter1, sAEcouter2, sAEcouter3, sEmise);
  Mirf.setMultiRADDR(sAEcouter4,4);  
}
void MirfInit(int cePin,int csnPin, int iTaille, byte * sAEcouter1, byte * sAEcouter2, byte * sAEcouter3, byte * sAEcouter4, byte * sAEcouter5, byte * sEmise){
  MirfInit(cePin, csnPin, iTaille, sAEcouter1, sAEcouter2, sAEcouter3, sAEcouter4, sEmise);
  Mirf.setMultiRADDR(sAEcouter5,5);  
}

//Methode qui gere le protocole de communication unifilaire pour transmettre 8 ou moins de bits 
// utilise iLength et motTransmis
void mProtocoleEmetteur(){
  long lDebut;
  int iTaille;                                 //indique le nombre de bit a 1 en fonction du bit a transmettre
  lDebut=millis();
  digitalWrite(iNumPin,HIGH);
  while(millis()-lDebut<=iBitStart){           //creation du start
    ;
  }
  lDebut=millis();
  digitalWrite(iNumPin,LOW);
  while(millis()-lDebut<=iBaseTemps){          //creation du bit separateur a 0
    ;
  }
  for (int iBitDonnee=0; iBitDonnee<iLength; iBitDonnee++){
    if (bitRead(motTransmis,iBitDonnee)==0){   //etude du bit a transmettre
      iTaille=iBitZero;
    }else{
      iTaille=iBitUn;
    }
    lDebut=millis();
    digitalWrite(iNumPin,HIGH);
    while(millis()-lDebut<=iTaille){          //transmission du bit de donnee
      ;
    }
    lDebut=millis();
    digitalWrite(iNumPin,LOW);
    while(millis()-lDebut<=iBaseTemps){       //creation du bit separateur a 0
      ;
    }
  }
  lDebut=millis();
  digitalWrite(iNumPin,HIGH);
  while(millis()-lDebut<=iBitFin){            //transmission du fin
    ;
  }
  digitalWrite(iNumPin,LOW);                  //remise a 0 de la ligne
}

#endif /* _METHODES_ */