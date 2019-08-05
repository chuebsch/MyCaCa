#include <QtGui>
#include <stdlib.h>
#include <string.h>

int maxcol=90;

void printicon(QString s,int flip,char x){
  QImage II=QImage(s);
  if ((II.width()>maxcol)||(maxcol!=90)) II=II.scaledToWidth(maxcol);
//  QImage II=QPixmap(":/icons/cbh.png" ).toImage();
  int r, g, b, c216,gray,k=0;
  char X[13]="ShelXle.org ";
  for (int j=0; j<II.height(); j++){
  for (int i=0; i<II.width(); i++){
    //printf("%2x",qGray(II.pixel(i,j)));a
    double al=qAlpha(II.pixel(i,j))/256.0;
    r=(int) (qRed(II.pixel(i,j))/48.0*al);
    g=(int) (qGreen(II.pixel(i,j))/48.0*al);
    b=(int) (qBlue(II.pixel(i,j))/48.0*al);
    gray=qGray(II.pixel(i,j))/11+232;
    c216 = 16 + 36 * r + 6 * g + b;

    gray=(int) (al*gray + (1.0-al)*238);
   // c216=(int) (al*c216 + (1.0-al)*102);
    if (flip) printf("\e[48;5;%dm\e[38;5;%dm%c%c",gray,c216,x,x);
    else  printf("\e[48;5;%dm\e[38;5;%dm%c%c",c216,gray,X[k%12],X[(k+1)%12]);
    k++;
    k++;
    //i++;
    
  }
  printf("\e[0;0;0m\n");
  //j++;
  }


}

int main(int argc,char **argv){
  //QApplication app(argc, argv);
  int flip=0;
  char x='X';
  if (argc>2) {
    if (strstr(argv[2],"--dark")!=NULL) flip=1; 
    if ((flip)&&(argc>3)) x=argv[3][0];
    if ((strstr(argv[2],"--width")!=NULL)&&(argc>3)) maxcol=atoi(argv[3]);
  }
  if (argc>1) printicon(QString(argv[1]),flip,x);
  else printf("USAGE: %s filename [--option] [value]\n\nAVAILABLE options:\n--dark [character]\n--width [90]\n",argv[0]);
return 0;
}
