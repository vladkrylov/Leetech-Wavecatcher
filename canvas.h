
#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QWidget>
#include "WaveCat64ch_Lib.h"

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
class QTimer;
class TCanvas;
class TGraph;

const int N_CHANNELS = 8;

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
   void handle_root_events();
   void DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData);

private:
   bool enabled[N_CHANNELS];
   float baselines[N_CHANNELS];
   TGraph* gr[N_CHANNELS];

protected:
   QRootCanvas    *canvas;
   QTimer         *fRootTimer;
};

#endif


