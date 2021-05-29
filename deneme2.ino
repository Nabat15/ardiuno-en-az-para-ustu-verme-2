#include <Wire.h>
#include <LiquidCrystal_SR.h>
#include <SPI.h>
#include <SD.h>
// global degişkenlerin tanımlanması
LiquidCrystal_SR lcd(3,2,5); //lcd register pinleri
File myFilezzz;
int dataPin= 10;// burdan itibaren 3 satir butonlar için register pinleri
int latctPin=9; 
int clockPin=8;  
  int para_adeti[5];
  char veri[100];
  char *virgulmu;
  int hizmet_adeti[4];
  String yazi;
  int k_led=6,y_led=7;
 int i_5=0,i_10=0,i_20=0,i_50=0,i_100=0,kopukleme=0,yikama=0,kurulama=0,cila=0;
 int toplam=0,hizmet=0;



void setup() {
  int sayac=0;
  //Serial başlatma
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

// SD kartını başlatma
  if (!SD.begin(4)) {
    Serial.println("baglanti hatasi");
    while (1);
  }
  Serial.println("baglandi");

  SD.remove("test.txt"); // mevcut dosyayi siler
  myFile = SD.open("test.txt", FILE_WRITE);
//okuma için dosya olusturma
  if (myFile) {
    Serial.print("Yazdirma :test.txt...");
    myFile.println("20,20,10,30,5,");
    myFile.println("1,kopukleme,3,15tl,");
    myFile.println("2,yikama,50,10tl,");
    myFile.println("3,kurulama,100,5tl,");
    myFile.println("4,cilalama,20,50tl,");
    
    myFile.close(); // dosyayi kapatma
   
  } else {
    
    Serial.println("Acilirken hata olustu:test.txt");
  }

  // okuma işlemi için dosya açma
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // dosya sonuna kadar okuma
    while (myFile.available()) {
           veri[sayac]=myFile.read(); // bit bit okuma işlemi
      sayac++;
    
    }//dosyayi kapatma
    myFile.close();
    // konsola yazdırma
    for(int i=0;i<=sayac;i++){
      Serial.write(veri[i]);
    }
  virgul_cikar();

  } else {
   
    Serial.println("Acilirken hata olustu:test.txt");
  }
  pinMode(dataPin,INPUT); // 74hc166 data pini giriş olarak ayarlanır
  pinMode(latctPin,OUTPUT); // pini çikiş olarak ayarlabır
  pinMode(clockPin,OUTPUT); // zaman pini çikiş olarak ayarlanır
  pinMode(y_led,OUTPUT);  // yesil led çikiş olarak ayarlanır
  pinMode(k_led,OUTPUT);// kirmizi led çıkış olarak ayarlanır
  lcd.begin(16,2);
 
}

void loop() {
  baslat();
 

}
//Strin metin içerisinde sayisal degeri cıkarmak için metod
void virgul_cikar(){
//strtok her bir string metini alır
// atoi char tipinden int tipine cevirir
          virgulmu=strtok(veri,",");
       para_adeti[0] =atoi(virgulmu);
    for(int sayac=0;sayac<20;sayac++){
        virgulmu=strtok(NULL,",");
        switch (sayac){
     case 0:
     para_adeti[1] =atoi(virgulmu);
     break;
    case 1:
    para_adeti[2] =atoi(virgulmu);
    break;
    case 2:
    para_adeti[3] =atoi(virgulmu);
    break;
    case 3:
    para_adeti[4] =atoi(virgulmu);
    break;
   case 6:
    hizmet_adeti[0] =atoi(virgulmu);
    break;
   case 10:
   hizmet_adeti[1] =atoi(virgulmu);
   break;
   case 14:
    hizmet_adeti[2] =atoi(virgulmu);
   break;
   case 18:
   hizmet_adeti[3] =atoi(virgulmu);
break;
default:
break;
  }
}
}
// butonlar bulunur 12 adet buton ve işlevleri
void baslat(){

  //yazi=String(para_adeti[0])+","+String(para_adeti[1])+","+String(para_adeti[2])+","+String(para_adeti[3])+","+String(para_adeti[4]);
//Yazdir_LCD(0,yazi ); 

  int toplam_buton;
int secim; 
// pinlerle önayarlar yapılır
    digitalWrite(latctPin,0); 
  digitalWrite(clockPin,0);
   digitalWrite(clockPin,1);
  digitalWrite(latctPin,1);
//  rergister bacagina gore 16 adet dongu var
    for(secim=0; secim<16; secim++){
      // butonun 1 olma durumu
     toplam_buton=digitalRead(dataPin);

     
 if(toplam_buton==1){
  // secim hangi butona tıklanma durumu
  switch (secim){
    // case 0 ile 4 arasi para birimi butonları
      case 0:
      // her tikalndıgında i_5 artar
         yazi="5TL:";
      i_5++;
      Yazdir_LCD(i_5,yazi);
       break;
      case 1:
       yazi="10TL:";
       i_10++;
     
       Yazdir_LCD(i_10,yazi);
       break;
      case 2:
      
       yazi="20TL:";
       i_20++;
       Yazdir_LCD(i_20,yazi);
       break;
      case 3:
      yazi="50TL:";
      i_50++;
      Yazdir_LCD(i_50,yazi);
      break;
      case 4:  
      yazi="100TL:";
      i_100++;
      Yazdir_LCD(i_100,yazi);
      break;
      case 5:
      // bakiye hesaplama yapılır
      toplam=(i_5*5)+(i_10*10)+(i_20*20)+(i_50*50)+(i_100*100);
     yazi="Toplam Bakiye:";
   Yazdir_LCD(toplam,yazi);
   // para birimleri kasaya eklenir
  para_adeti[0]=para_adeti[0]+i_5;
  para_adeti[1]=para_adeti[1]+i_10;
  para_adeti[2]=para_adeti[2]+i_20;
  para_adeti[3]= para_adeti[3]+i_50;
  para_adeti[4]=para_adeti[4]+i_100;
     break;
     case 6:
     // case 6 ile 9 arasi hizmet menusu butonudur
     if(hizmet_adeti[0]!=0){ // kalan hizmet sifir degilse 

          kopukleme++; // her tilandiginda artar
         yazi="KOPUKLEME 15TL:";
         Yazdir_LCD(kopukleme,yazi);
           hizmet_adeti[0]=hizmet_adeti[0]-1; // her tıklandıgında kalan hizmetten eksilir
          
  
     }
     else{ // kalan hizmet sifir ise

               yazi="Hizmet Yetersiz:";
         Yazdir_LCD(0,yazi);
     }
        break;
    case 7:
         if(hizmet_adeti[1]!=0){
      yazi="YIKAMA 10TL:";
      yikama++;
      Yazdir_LCD(yikama,yazi);
  hizmet_adeti[1]=hizmet_adeti[1]-1;
     }
     else{
 
               yazi="Hizmet Yetersiz:";
         Yazdir_LCD(0,yazi);
     }

      break;
      case 8:
               if(hizmet_adeti[2]!=0){
       yazi="KURULAMA 5TL:";
      kurulama++;
      Yazdir_LCD(kurulama,yazi);
  hizmet_adeti[2]= hizmet_adeti[2]-1;
     }
     else{
               yazi="Hizmet Yetersiz:";
         Yazdir_LCD(0,yazi);
     }

      break;
      case 9:
       if(hizmet_adeti[3]!=0){
      yazi="CILALAMA 50TL:";
      cila++;
      Yazdir_LCD(cila,yazi);
  hizmet_adeti[3]=hizmet_adeti[3]-1;
     }
     else{
               yazi="Hizmet Yetersiz:";
         Yazdir_LCD(0,yazi);
     }

      break;
      case 10:
      // butonu bitirme butonu olarak ayarlandı
       hizmet=hizmet+(kopukleme*15);//hizmet bedeli hesaplanır
      hizmet=hizmet+(yikama*10);
      hizmet=hizmet+(kurulama*5);
      hizmet=hizmet+(cila*50);
        if(toplam<hizmet){ // bakiiye hizmet bedelinden az ise uyarı verir
         yazi="Hizmet>Bakiye:";
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(yazi);
          lcd.setCursor(0,1);
          lcd.print(String(hizmet));
          lcd.setCursor(10,1);
          lcd.print(String(toplam));
          delay(1000); 
       }else{ // bakiiye hizmet bedelinden az degilse işleme devam eder
        LEDI_Yak(); // metod çagırılır
       }
       break;
       case 11:
// case 11 reset butonu olarak ayarlandı
      yazi="Rsetleniyor:";
      // kalan hizmetten secilen hizmetler eklenir
   hizmet_adeti[0]=hizmet_adeti[0]+kopukleme;
  hizmet_adeti[1]=hizmet_adeti[1]+yikama;
  hizmet_adeti[2]= hizmet_adeti[2]+kurulama;
  hizmet_adeti[3]=hizmet_adeti[3]+cila;
      hizmet=0;
      kopukleme=0;
      yikama=0;
      kurulama=0;
      cila=0;
      Yazdir_LCD(0,yazi);

      break;
      default:
      break;
     }
 }
 digitalWrite(clockPin, LOW);
 digitalWrite(clockPin,HIGH);
 }
}
//lcd ekranına yazdırma metodu
void Yazdir_LCD(int sayi, String yazi )
{
  String sayi_cevir=String(sayi);
  lcd.clear();
  lcd.setCursor(10,1);        // 2.satir
  lcd.print(sayi_cevir);
  lcd.setCursor(0,0);        //1.satir
  lcd.print(yazi);

  delay(2000); 
}
// led yakma metodu
void LEDI_Yak(){
          int sayi=1+rand()%4;             // 1 ile 4 arasında sayı sec
                         if(sayi==2){      //sayi 2 ise
       digitalWrite(k_led,HIGH);          // kirmiz led yak
      // iade işlemleri yapılır
      yazi="Iade Islemi";
      Yazdir_LCD(sayi,yazi);
      yazi="Toplam Iade:";
      Yazdir_LCD(toplam,yazi);
  hizmet_adeti[0]=hizmet_adeti[0]+kopukleme;
  hizmet_adeti[1]=hizmet_adeti[1]+yikama;
  hizmet_adeti[2]= hizmet_adeti[2]+kurulama;
  hizmet_adeti[3]=hizmet_adeti[3]+cila;
      kopukleme=0;
      yikama=0;
      kurulama=0;
      cila=0;
  para_adeti[0]=para_adeti[0]-i_5;
  para_adeti[1]=para_adeti[1]-i_10;
  para_adeti[2]=para_adeti[2]-i_20;
  para_adeti[3]=para_adeti[3]-i_50;
  para_adeti[4]=para_adeti[4]-i_100;
  i_5=0,i_10=0,i_20=0,i_50=0,i_10=0,toplam=0;
  delay(2000);
      digitalWrite(k_led,LOW); // kirmizi ledi sondur
     }else if(sayi==1 || sayi==3 || sayi==4){
      // sayi 2 esit degilse 
      // yesil led yak 
      digitalWrite(y_led,HIGH);
      yazi="Islem Basarili";
      Yazdir_LCD(sayi,yazi);
    Paraustu_Hesapla(); // para ustu verme butonu cagırılır
yazi=String(hizmet_adeti[0])+","+String(hizmet_adeti[1])+","+String(hizmet_adeti[2])+","+String(hizmet_adeti[3]);
// Serial.print(yazi);
 Yazdir_LCD(0,yazi );       //kalan hizmet gosterir
  digitalWrite(y_led,LOW);
     }
}

// para ustu verme metodu
void Paraustu_Hesapla(){
  int para_ustu,yedek_paraustu,j_100,j_50,j_20,j_10,j_5;
 para_ustu=toplam-hizmet;
 yedek_paraustu=para_ustu;
  if(para_ustu>=100 && para_adeti[4]!=0){ // 100 tl verme işlemi parasutu 100den buyuk ise ve kasada 100luk para birimi var ise 
    j_100=(para_ustu/100); // kac adet 100 luk lazım olacah hesaplaması
   para_adeti[4]=para_adeti[4]-j_100;
      para_ustu=para_ustu-(100*j_100);
    if(para_ustu==0){
    yazi=String(j_5)+","+String(j_10)+","+String(j_20)+","+String(j_50)+","+String(j_100);
 Yazdir_LCD(yedek_paraustu,yazi);
    }
     }if(para_ustu>=50 && para_adeti[3]!=0){
     j_50=(para_ustu/50);
      para_adeti[3]=para_adeti[3]-j_50;
     para_ustu=para_ustu-(50*j_50);
   
     if(para_ustu==0){
     yazi=String(j_5)+","+String(j_10)+","+String(j_20)+","+String(j_50)+","+String(j_100);
 Yazdir_LCD(yedek_paraustu,yazi);
    
  }} if(para_ustu>=20 && para_adeti[2]!=0){
  
       j_20=(para_ustu/20);   
          para_adeti[2]=para_adeti[2]-j_20;  
      para_ustu=para_ustu-(20*j_20);
      if(para_ustu==0){
    yazi=String(j_5)+","+String(j_10)+","+String(j_20)+","+String(j_50)+","+String(j_100);
Yazdir_LCD(yedek_paraustu,yazi);
  
  }  
  }if(para_ustu>=10 && para_adeti[1]!=0){
  
      j_10=(para_ustu/10);
      para_ustu=para_ustu-(10*j_10);
      para_adeti[1]=para_adeti[1]-j_10;
      if(para_ustu==0){
     yazi=String(j_5)+","+String(j_10)+","+String(j_20)+","+String(j_50)+","+String(j_100);
 Yazdir_LCD(yedek_paraustu,yazi);
    
  }}if(para_ustu>=5 && para_adeti[0]!=0){
   
       j_5=(para_ustu/5);
       para_ustu=para_ustu-(5*j_5);
      para_adeti[0]=para_adeti[0]-j_5;
       if(para_ustu==0){
     yazi=String(j_5)+","+String(j_10)+","+String(j_20)+","+String(j_50)+","+String(j_100);
 Yazdir_LCD(yedek_paraustu,yazi);
  }
    }
 else if(para_ustu!=0){ // üstteki kosullar saglanmıyor ise ve paraustu sifirdan buyuk ise bakiye yetersizdir.
  yazi ="bakiye yetersiz";
  Yazdir_LCD(para_ustu,yazi);

 }

 }
