#include <QApplication>
#include <vnccli.h>
#include <iostream>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        VncCli * v = new VncCli();
        std::cout<<"tu";
        QThread * s = new QThread;
      v->doSetup(*s);
      v->moveToThread(s);
      while(1)
      {
      s->start();
}
       // v->start();
              return 0;

}
