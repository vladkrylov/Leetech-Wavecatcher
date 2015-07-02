
#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QWidget>
#include "WaveCat64ch_Lib.h"

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
class QPushButton;
class QTimer;
class TCanvas;

class QRootCanvas : public QWidget
{
   Q_OBJECT

public:
   QRootCanvas( QWidget *parent = 0);
   virtual ~QRootCanvas() {}
   TCanvas* getCanvas() { return fCanvas;}

protected:
   TCanvas        *fCanvas;

   virtual void    mouseMoveEvent( QMouseEvent *e );
   virtual void    mousePressEvent( QMouseEvent *e );
   virtual void    mouseReleaseEvent( QMouseEvent *e );
   virtual void    paintEvent( QPaintEvent *e );
   virtual void    resizeEvent( QResizeEvent *e );
};

class QMainCanvas : public QWidget
{
   Q_OBJECT

public:
   QMainCanvas( QWidget *parent = 0);
   virtual ~QMainCanvas() {}
   virtual void changeEvent(QEvent * e);


public slots:
   void clicked1();
   void handle_root_events();
   void DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData);

protected:
   QRootCanvas    *canvas;
   QPushButton    *b;
   QTimer         *fRootTimer;
};

#endif


